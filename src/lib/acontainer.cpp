/****************************************************************************
** $Id: acontainer.cpp,v 1.12 2007/11/11 13:18:38 gr Exp $
**
** Data container implementation file of
** Ananas application
**
** Created : 20060209
**
** Copyright (C) 2006 Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola.
**
** This file is part of the Library of the Ananas
** automation accounting system.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.leaderit.ru/page=ananas or email sales@leaderit.ru
** See http://www.leaderit.ru/gpl/ for GPL licensing information.
**
** Contact org@leaderit.ru if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#include "alog.h"
#include "acontainer.h"
#include "acmanifest.h"
#include "aservice.h"
#include <qapplication.h>
#include <qfile.h>
#include <qdir.h>
#include <qprocess.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * \~russian
 *	\brief Класс для работы с новым форматом обновлений
 * \~
 */
 
/**
* \~english 
* Constructor
* \~russian 
*  Конструктор
* \~
*/
aContainer::aContainer():QObject()
{
}

/**
* \~english 
* Constructor with name
* \~russian 
*  Конструктор с именем
* \~
*/
aContainer::aContainer(const QString& name):QObject(0, name)
{
	manifest = new aCManifest();
}

/**
* \~english 
* Destructor
* \~russian 
*  Деструктор
* \~
*/
aContainer::~aContainer()
{
	delete manifest;
	manifest = 0;
}

/**
* \~english 
* Opens file. You should set name before (in constructor) or use aContainer::open(const QString& name)
* \return true if success, false otherwise
* \~russian 
*  Открывает контейнер. Вы должны установить имя файла до вызова этой функции (в конструкторе) или использовать aContainer::open(const QString& name)
* \return true в случае успеха, false в любом другом
* \~
*/
bool 
aContainer::open()
{
	return open(name());
}

/**
* \~english 
* Opens file. You should set name before (in constructor) or use aContainer::open(const QString& name)
* \param name - file name
* \return true if success, false otherwise
* \~russian 
* Открывает контейнер. Вы должны установить имя файла до вызова этой функции (в конструкторе) или использовать aContainer::open(const QString& name)
* Под открытием подразумевается распаковка файлов во временный каталог.
* \param name - имя файла
* \return true в случае успеха, false в любом другом
* \~
*/
bool 
aContainer::open(const QString& name)
{
	close();
	generateName4TmpDir();
	if(createTmpDir())
	{
		extractManifest(name, manifest);
		if(manifest)
		{
			if(extractData(name))
			{
				setName(name);
				aLog::print(aLog::MT_DEBUG, tr("aContainer unzip"));
				return true;
			}
		}
		cleanupTmpFiles();
	}
	aLog::print(aLog::MT_ERROR, tr("aContainer unzip"));
	return false;	
}

/**
* \~english 
* Create new empty container.
* \~russian 
*  Создает новый пустой контейнер.
* \~
*/
void 
aContainer::create()
{
	generateName4TmpDir();
	createTmpDir();
	manifest->create(); 
}

/**
* \~english 
* Closes container. Don't save anything.
* \~russian 
*  Закрывает контейнер. Не производит сохранение файлов перед закрытием. Удаляет все временные файлы.
* \~
*/
void 
aContainer::close()
{
	cleanupTmpFiles();
}

/**
* \~english 
* Generates new name for temporary directory.
* \~russian 
* Генерирует новои имя для временной директории.
* \~
*/
void 
aContainer::generateName4TmpDir()
{
	QString temp;
#ifndef _Windows
	temp = getenv("TMPDIR");
	if(temp=="" || temp.isEmpty())
		temp = P_tmpdir;
#else
	temp = getenv("TEMP");
#endif
	tmpDirName = QString(temp+"/%1/").arg(QDateTime::currentDateTime().toTime_t());
	tmpDirName = QDir::convertSeparators(tmpDirName);
	
}

/**
* \~english 
* Creates new temporary directory.
* \return true if success
* \~russian 
* Создает временную директорию для распаковки.
* \return true в случае успеха
* \~
*/
bool
aContainer::createTmpDir()
{
	QDir dir;	
	if(!dir.mkdir(tmpDirName))
	{	
		setLastError(tr("Can't create temporary directory"));
		aLog::print(aLog::MT_ERROR, "aContainer create temporary directory %1");
		return false;
	}
	else
	{
		aLog::print(aLog::MT_DEBUG, tr("aContainer create temporary directory %1").arg(tmpDirName));
		return true;
	}

}
/**
* \~english 
* Saves container. Only files described in manifest will be saved.
* \param name - File name
* \return true if success
* \~russian 
* Сохраняет контейнер. Будут сохранены только файлы, которые описаны в манифесте.
* \param name - имя файла
* \return true в случае успеха
* \~
*/
bool 
aContainer::save(const QString& name)
{
	setName(name);	
	if(manifest)
	{
		aCManifest::record rec;
		rec = manifest->first();
		while(rec.type!=mf_invalid)
		{
			compressFile(rec.name);
			rec = manifest->next();
		}
	}
	else
	{
		setLastError(tr("No manifest found!"));
		aLog::print(aLog::MT_ERROR, "aContainer save: manifest is null");
		return false;
	}
	aLog::print(aLog::MT_INFO, tr("aContainer save successefully to %1").arg(name));
	return true;
}

/**
* \~english 
* Function for save container. File name to save should be setted before call this function in constructor or aContainer::open(const QString& name)
* \return true if success
* \~russian 
* Функция сохранения контейнера и его содержимого. Имя файла должно быть установлено до вызова этой функции в конструкторе или aContainer::open(const QString& name)
* \return true в случае успеха
* \~
* \see aContainer::save(const QString& name)
*/
bool 
aContainer::save()
{
	return save(name());
	
}

/**
* \~english 
* Add specified file to container.
* \param filename - fully specified file name
* \param newname - relative file name in container. Should be relative at container root. e.g. "forms/form111.ui"
* \param type - type of file. See aCManifest class description for details.
* \return true if success
* \~russian 
* Добавляет указанный файл в контейнер.
* \param filename - полное имя файла
* \param newname - относительное имя файла в контейнере. Должно указываться относительно корня контейнера, напр. "forms/form111.ui"
* \param type - тип добавляемого файла. См. описание класса aCManifest для получения дополнительных сведений.
* \return true в случае успеха
* \~
*/
bool
aContainer::addFile(const QString& filename, const QString &newname, int type)
{
	bool res = false;
	if(!aService::copyFile( QDir::convertSeparators(filename), QDir::convertSeparators(tmpDirName + newname), true))
	{
		aLog::print(aLog::MT_ERROR, tr("aContainer error copy file"));
	}
	else
	{
		if(manifest)
		{
			manifest->addEntry(newname, type);
			res = true;
		}
		else
		{
			aLog::print(aLog::MT_ERROR, tr("aContainer manifest is null"));
		}
	}
	return res;
}

/**
* \~english 
* Return real path to specified file.
* \param fname - container relative filename.
* \return real path to file. 
* \~russian 
* Возвращает реальный путь к файлы, т.е. где он физически расположен на диске.
* \param fname - относительный путь файла в контейнере
* \return реальный путь к файлу.
* \~
*/
QString
aContainer::realPath(const QString &fname) const
{
	return "";	
}


/**
* \~english 
* Extracts manifest file. This file always named META-INF/manifest.xml
* \param archName - container name
* \param mf (out) - pointer to manifest.
* \return true if success
* \~russian 
* Извлекает файл манифеста из контейнера. Этот файл называется всегда META-INF/manifest.xml
* \param archName - имя контейнера
* \param mf (out) - указатель на манифест.
* \return true в случае успеха
* \~
*/
bool
aContainer::extractManifest(const QString& archName, aCManifest *mf)
{
#ifndef Q_OS_WIN32
	QProcess process( QString("unzip") );
//	process.setWorkingDirectory (dir);
	process.addArgument("-op");
	process.addArgument( archName );
	process.addArgument("/META-INF/manifest.xml");
	process.addArgument( "-d" );
	process.addArgument( tmpDirName );

#else 
	QProcess process( QString("7z") );	
//	process.setWorkingDirectory ( templateDir);
//	printf("working dir = `%s'\n", QString(templateDir).ascii());
	process.addArgument( "x" );
	process.addArgument( "-y" );
	process.addArgument( QString("-o%1").arg(tmpDirName) );
	process.addArgument( archName );

#endif

	if( !process.start() )
	{
		setLastError(tr("Can't start unzip"));
		aLog::print(aLog::MT_ERROR, tr("aContainer start unzip"));
		return false;
	}

	while( process.isRunning() );

	if( !process.normalExit() ) 
	{
		setLastError(tr("Unzip ended anormal"));
		aLog::print(aLog::MT_ERROR, tr("aContainer unzip dead"));
		return false;
	}
	else
	{
		aLog::print(aLog::MT_DEBUG, tr("aContainer unzip normal"));
	}
	if( process.exitStatus() )
	{
		setLastError(tr("Unzip ended with code %1").arg(process.exitStatus()));
		return false;
	}
	if(mf && mf->read(tmpDirName + QDir::convertSeparators("/META-INF/manifest.xml")))
	{
		return true;
	}
	return false;
}

/**
* \~english 
* Extracts all files to temporary directory.
* \param archName - container name
* \return true if success
* \~russian 
* Извлекает все файлы во временную директорию.
* \param archName - имя контейнера
* \return true в случае успеха
* \~
*/
bool
aContainer::extractData(const QString& archName)
{
#ifndef Q_OS_WIN32
	QProcess process( QString("unzip") );
//	process.setWorkingDirectory (dir);
	process.addArgument("-op");
	process.addArgument( archName );
	process.addArgument( "-d" );
	process.addArgument( tmpDirName );

#else 
	QProcess process( QString("7z") );	
//	process.setWorkingDirectory ( templateDir);
//	printf("working dir = `%s'\n", QString(templateDir).ascii());
	process.addArgument( "x" );
	process.addArgument( "-y" );
	process.addArgument( QString("-o%1").arg(tmpDirName) );
	process.addArgument( archName );

#endif

	if( !process.start() )
	{
		setLastError(tr("Can't start unzip"));
		aLog::print(aLog::MT_ERROR, tr("aContainer start unzip"));
		return false;
	}

	while( process.isRunning() );

	if( !process.normalExit() ) 
	{
		setLastError(tr("Unzip ended anormal"));
		aLog::print(aLog::MT_ERROR, tr("aContainer unzip dead"));
		return false;
	}
	else
	{
		aLog::print(aLog::MT_DEBUG, tr("aContainer unzip normal"));
	}
	if( process.exitStatus() )
	{
		setLastError(tr("Unzip ended with code %1").arg(process.exitStatus()));
		return false;
	}
	return true;
}

/**
* \~english 
* Zip one file to container. THE FUNCTION DOSEN'T WORK! 
* \param fileName - container relative file name to zip.
* \return true if success
* \~russian 
* Физически добавляет в контейнер один файл. Т.е эта функция производит сжатие файлов, находящихся во временной директории в zip архив.
* \param archName - имя файла в контейнере. ФУНКЦИЯ НЕ РАБОТАЕТ!
* \return true в случае успеха
* \~
*/
bool 
aContainer::compressFile(const QString& fileName)
{
aLog::print(aLog::MT_DEBUG, tr("Compress file %1").arg(fileName));
#ifndef Q_OS_WIN32

	QProcess processUpdate( QString("zip") );
	processUpdate.setWorkingDirectory(tmpDirName);
//	processUpdate.addArgument( "-r" ); // recurce into subdirectories
//	processUpdate.addArgument( "-0" ); // store only
	processUpdate.addArgument( QString("\"%1\"").arg(name()) ); // cfg name
	processUpdate.addArgument(".");
	processUpdate.addArgument("-i");
	processUpdate.addArgument(QString("\"%1\"").arg(fileName) );
#else
	QProcess processUpdate( QString("7z") );
	processUpdate.setWorkingDirectory(tmpDirName);
	processUpdate.addArgument( "a" );
	processUpdate.addArgument( "-tzip" );
	processUpdate.addArgument( fileName );	
	processUpdate.addArgument( "-r" );
	processUpdate.addArgument(".");
#endif

	if( !processUpdate.start() )
	{
		setLastError(tr("Unable to start zip"));
		aLog::print(aLog::MT_ERROR, tr("aContainer zip start error"));
		return false;
	}

	while( processUpdate.isRunning() );

	if( !processUpdate.normalExit() )
	{
		setLastError(tr("Zip ended with error"));
		aLog::print(aLog::MT_ERROR, tr("aContainer zip dead"));
		return false;
	}

	if( processUpdate.exitStatus() )
	{
		setLastError(tr("Zip ended with code %1").arg(processUpdate.exitStatus()));
		return false;
	}
	
	return true;
}



/**
* \~english 
* Set last error text.
* \param errorText - error text.
* \~russian 
* Устанавливает текст последней ошибки.
* \param errorText - текст ошибки
* \~
* \see aContainer::lastError()
*/
void 
aContainer::setLastError(const QString& errorText)
{
	txtError = errorText;
}

/**
* \~english 
* Get last error text.
* \return errorText - error text.
* \~russian 
* Получает текст последней ошибки.
* \return errorText - текст ошибки
* \~
* \see aContainer::setLastError(const QString& errorText)
*/
QString 
aContainer::lastError() const
{
	return txtError;
}
/**
* \~english 
* Clean templorary files.
* \~russian 
* Удаляет все временные файлы.
* \~
*/
void 
aContainer::cleanupTmpFiles()
{
	QFile file;
	QDir dir;
	
	if(manifest && tmpDirName!="")
	{
		aCManifest::record rec;
		rec = manifest->first();
		while(rec.type!=mf_invalid)
		{
			if(rec.type!=mf_dir && rec.type!=mf_invalid)
			{
				file.setName(tmpDirName + QDir::convertSeparators(rec.name));
				if(file.remove())
					aLog::print(aLog::MT_DEBUG, tr("aContainer delete file %1").arg(rec.name));
			}
			rec = manifest->next();
		}
		rec = manifest->first();
		while(rec.type!=mf_invalid)
		{
			if(rec.type==mf_dir)
			{
				if(dir.rmdir(tmpDirName + QDir::convertSeparators(rec.name) ))
					aLog::print(aLog::MT_DEBUG, tr("aContainer delete directory %1").arg(rec.name));
			}
			rec = manifest->next();
		}
	}
	
	
	file.setName(QDir::convertSeparators(tmpDirName+"/META-INF/manifest.xml"));
	if(file.remove()) aLog::print(aLog::MT_DEBUG, tr("aContainer delete file %1").arg(file.name()));
	if(dir.rmdir(QDir::convertSeparators(tmpDirName))) aLog::print(aLog::MT_DEBUG, tr("aContainer delete directory %1").arg(tmpDirName + "/META-INF"));
	//aLog::print(aLog::MT_INFO, tr("aContainer cleanup temporary files"));
	
}

QString 
aContainer::getFileContent(const QString& fileName) const
{
	QString content = "test";
	return content;
}


