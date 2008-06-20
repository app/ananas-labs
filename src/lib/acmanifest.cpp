/****************************************************************************
** $Id: acmanifest.cpp,v 1.5 2007/11/11 08:23:40 gr Exp $
**
** Work with manifest.xml implementation file of
** Ananas application
**
** Created : 20060927
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2006 Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola.
** Copyright (C) 2007 Grigory Panov <grigory.panov at gmail.com>, Moscow.
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
#include "acmanifest.h"
#include <qfile.h>



aCManifest::aCManifest():QObject()
{
}

aCManifest::~aCManifest()
{
}

	
	// place your castom types before mf_other
    //	enum type{ mf_metadata, mf_template, mf_dir, mf_script, mf_form, mf_picture, mf_other=100 };
/**
* \~english 
* Create new empty manifest.
* \~russian 
*  Создает новый пустой манифест.
* \~
*/	
void
aCManifest::create()
{
	manifest.setContent(QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"));
	QDomElement root = manifest.createElement("manifest:manifest");
	manifest.appendChild(root);
	rootNode = root;
	currentNode.clear();
	return;
}

/**
* \~english 
* \return manifest as string
* \~russian 
* \return манифест как строку
* \~
*/
QString 
aCManifest::toString()
{
	return manifest.toString(4); //indent - 4 space
}

/**
* \~english 
* Store manifest to file
* \return true if success
* \~russian 
* Сохраняет манифест в файл.
* \return true в случае успеха
* \~
*/
bool
aCManifest::write(const QString& fname)
{
	QFile file(fname);
	QByteArray buf( manifest.toString(4).utf8() );
	if ( file.open( IO_WriteOnly ) )
	{
		QTextStream ts( &file );
		ts.setEncoding(QTextStream::UnicodeUTF8);
		manifest.save(ts, 4);
		file.close();
	}
	else
	{
		aLog::print(aLog::MT_ERROR, tr("aCManifest save xml %1").arg(fname));
		txtError = QString("aCManifest save xml %1").arg(fname);
		return false;
	}
	return true;	
}

/**
* \~english 
* Read manifest from file.
* \param fname - file name to read
* \return true if success
* \~russian 
* Читает манифест из файла.
* \param fname - имя файла для чтения
* \return true в случае успеха
* \~
*/
bool 
aCManifest::read(const QString& fname)
{
	QFile file( fname );
	QByteArray buf;
	QString err;
	int errLine = 0, errColumn = 0;
	if ( !file.open( IO_ReadOnly ) )
	{
		aLog::print(aLog::MT_ERROR, tr("aCManifest read file `%1'").arg(fname));
		return false; 
	}
	buf = file.readAll();
	file.close();
	manifest.setContent( QString("") );
	if ( !manifest.setContent( buf, false, &err, &errLine, &errColumn ) ) 
	{
		aLog::print(aLog::MT_ERROR, tr("aCManifest read line: %1 column: %2").arg(errLine).arg(errColumn));
		txtError = err;
		return RC_ERROR;
	}
	if(!manifest.documentElement().isNull())
	{
		rootNode =  manifest.documentElement().firstChild().toElement();
	}
	currentNode.clear();
	return true;

}

/**
* \~english 
* Clear manifest content.
* \~russian 
* Очищает содержимое манифеста
* \~
*/
void
aCManifest::clear()
{
	manifest.clear();
	currentNode.clear();
	//manifest.setContent("");
	rootNode.clear();
}

/**
* \~english 
* I don't remember for what need this function
* \param fname - file name
* \~russian 
* Я не помню, для чего нужна эта функция. Возможно она проверяет, есть ли определенный файл в манифесте.
* \param fname - имя файла для проверки.
* \~
*/

bool 
aCManifest::isExists( const QString &fname )
{
	//TODO: implement this!
	return isValid();
}

/**
* \~english 
* Add new entry to manifest.
* \param fname - file name to add
* \param type - type of entry.
* \return true if success
* \~russian 
* Добавляет новую запись к манифесту.
* \param fname - имя файла для добавления
* \param type - тип записи.
* \return true в случае успеха
* \~
* mf_metadata=0, mf_template, mf_dir, mf_script, mf_form, mf_picture, mf_other=100
*/
bool
aCManifest::addEntry( const QString &fname, int type)
{
	if(isValid()) 
	{
		QDomElement entry = manifest.createElement("manifest:file-entry");
		entry.setAttribute("manifest:full-path",fname);
		entry.setAttribute("manifest:type",type);
		rootNode.appendChild(entry);
		return true;
	}
	else
	{
		return false;
	}
}

/**
* \~english 
* Remove entry from manifest.
* \param fname - file name to remove
* \param withChilds - remove childs node too or not
* \return true if success
* \~russian 
* Удаляет запись из манифеста.
* \param fname - имя записи для удаления
* \param withChilds - удялять ли дочерние записи.
* \return true в случае успеха
* \~
*/
bool 
aCManifest::removeEntry( const QString &fname, bool withChilds )
{
	
	bool res = false;
	if(isValid())
	{
		QDomElement root = manifest.documentElement().firstChild().toElement();
		QDomElement el = root.firstChild().toElement();
		QString attr;
		while(!el.isNull())
		{
			printf("element is %s\n",el.nodeName().ascii());
			attr = el.attribute("manifest:full-path");
			if(withChilds)
			{
				if(attr.find(fname)!=0) // only if attr begining from fname
				{
					printf("remove entry %s\n",attr.ascii());
				}
			}
			else
			{
				if(attr==fname)
				{
					printf("remove entry %s\n",attr.ascii());
					root.removeChild(el);
					res = true;
				}
			}
			el = root.nextSibling().toElement();
		
		}
	}
	return res;
}

/**
* \~english 
* Check manifest.
* \return true if manifest is valid
* \~russian 
* Проверяет манифест.
* \return true если манифест валиден.
* \~
*/
bool 
aCManifest::isValid()
{
	if(rootNode.isNull())
	{
		aLog::print(aLog::MT_ERROR, tr("aCManifest invalid manifest"));
		txtError = "aCManifest invalid manifest";
		return false;
	}
	return true;
}
	
/**
* \~english 
* \return first manifest record
* \~russian 
* \return первую запись манифеста
* \~
*/
aCManifest::record
aCManifest::first()
{
	aCManifest::record rec;
	rec.type = mf_invalid;
	if(isValid())
	{
		QDomElement node = rootNode.firstChild().toElement();
		if(!node.isNull())
		{
			currentNode = node;
			rec.name = node.attribute("manifest:full-path");
			rec.type = node.attribute("manifest:type", "0").toInt();
		}
	}
	return rec;
}

/**
* \~english 
* \return next manifest record
* \~russian 
* \return следующую запись манифеста
* \~
*/
aCManifest::record
aCManifest::next()
{
	aCManifest::record rec;
	rec.type = mf_invalid;
	if(isValid() && !currentNode.isNull())
	{
		QDomElement node = currentNode.nextSibling().toElement();
		if(!node.isNull())
		{
			currentNode = node;
			rec.name = node.attribute("manifest:full-path");
			rec.type = node.attribute("manifest:type", "0").toInt();
		}
	}
	return rec;
	
}

/**
* \~english 
* \return last error text
* \~russian 
* \return текст последней ошибки
* \~
*/
QString 
aCManifest::lastError() const
{
	return txtError;
}


