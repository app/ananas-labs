/****************************************************************************
** $Id: acfgrc.cpp,v 1.11 2008/07/30 15:58:51 leader Exp $
**
** Code file of the recorse work file of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
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

#include <stdlib.h>
#include <qfile.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <qpixmap.h>
#include <qdragobject.h>

#include "acfg.h"
#include "acfgrc.h"
#include "messageswindow.h"

QPixmap
rcIcon(const char *name){
	QPixmap pm;
	const QMimeSource *e;
	e=QMimeSourceFactory::defaultFactory()->data(QString(name));
	QImageDrag::decode(e, pm);
	return pm;
}



void
aMessageOutput( QtMsgType type, const char *msg )
{
	switch ( type ) {
	case QtDebugMsg:
		cfg_message( 0, "%s\n", msg );
        	break;
        case QtWarningMsg:
                cfg_message( 1, "%s\n", msg );
                break;
        case QtFatalMsg:
                cfg_message( 2, "%s\n", msg );
                abort();                    // deliberately core dump
        }
}

void
setMessageHandler( bool ) // GUI )
{
//	qInstallMsgHandler( aMessageOutput );
//	if ( GUI ) {
//		cfg_messageproc = messageproc;
//		cfg_message( 0, "<img source=\"a_system.png\">");
//	}
}

void
unsetMessageHandler()
{
	qInstallMsgHandler( 0 );
	cfg_messageproc = 0;
}

/**
 *	Ananas resource file object constructor.
 */
aCfgRc::aCfgRc()
{
	values.setAutoDelete( TRUE );
	filename = QString::null;
}

/**
 * \ru
 *	\brief Читает данные из файла ресурсов указанного в параметре при вызове.
 *
 *	И заполняет объекта класса данными из файла ресурса.
 *	\param fname имя файла ресурса, включая полный путь.
 *	\return 0 - в случае успешной загрузки данных из файла ресурсов.
 *	1 - если не удалось открыть файл ресурсов для чтения.
 * \_ru
 */
int
aCfgRc::read(const QString &fname)
{
	QStringList l;
	QFile file( fname );

	filename = fname;
	values.clear();
	if ( file.open( IO_ReadOnly ) )
	{
		QTextStream stream( &file );
		QString line, k, v;

		stream.setEncoding(QTextStream::UnicodeUTF8);
		while ( !stream.eof() ) {
			line = stream.readLine(); // line of text excluding '\n'
			k = line.section("=",0,0);
			v = line.section("=",1,100); if ( v.isNull() ) v = "";
			values.insert( k, new QString( v ) );
		}
		file.close();
		return 0;
	}
	return 1;
}


/**
 * \ru
 *	\brief Записывает данные в файл ресурсов, указанный в параметрах вызова.
 *
 *	В файл ресурса записываются данные, хранимые в объекте.
 *	\param fname - имя файла ресурсов, включая полный путь.
 *	\return 0, в случе успешной записы данных в файл ресурсов.
 *	1, если не удалось открыть файл ресурсов на запись.
 * \_ru
 */
int
aCfgRc::write(const QString &fname)
{
	QFile file( fname );

	if ( file.open( IO_WriteOnly ) )
	{
		QTextStream stream( &file );
		QDictIterator<QString> it( values );

		stream.setEncoding(QTextStream::UnicodeUTF8);
		for( ; it.current(); ++it )
		stream << it.currentKey() << "=" << *it.current() << endl;
		file.close();
		return 0;
	}
	return 1;
}

/**
 * \ru
 *	\brief Записывает данные объекта в файл ресурсов.
 *
 *	В качестве имени файла ресурсов используется значение, хранящееся
 *	в поле filename объекта.
 *	Использует метод aCfgRc::write(const QString &fname)
 *	\return 0, в случе успешной записы данных в файл ресурсов.
 *	1, если не удалось открыть файл ресурсов на запись.
 * \_ru
 *	\see aCfgRc::write(const QString &fname)
 */
int
aCfgRc::write()
{
	return write( filename );
}

/**
 * \ru
 *	\brief Возвращает значение именованного параметра.
 *	
 *	Метод предоставляет доступ к параметрам файла ресурсов, хранимым в объекте.
 *	\param name - имя параметра, значение которого требуется получить.
 *	Состав и количество параметров вида ИМЯ=ЗНАЧЕНИЕ не контролируются методом.
 *	\return строку со значением параметра или пустую строку "", если параметр не
 *	найден.
 * \_ru
 */
QString
aCfgRc::value(const QString &name, const QString &defValue)
{
	QString *s;
	s = values.find( name );
	if ( s ) return *s; else return defValue;
}


/**
 * \ru
 *	\brief Задает значение именованного параметра.
 *	
 *	Метод предоставляет доступ к параметрам файла ресурсов, хранимым в объекте.
 *	\param name - имя параметра, значение которого требуется задать.
 *	\param value - новое значение параметра с именем name.
 *	Состав и количество параметров вида ИМЯ=ЗНАЧЕНИЕ не контролируются методом.
 *	Однако, для успешного создания соединения с SQL сервером должны быть заданы
 *	как минимум приведенные в примере ниже шесть праметров.
 *	\code
 *	setValue( "configfile" , "resourses/inventory-demo.cfg");
 *	setValue( "dbhost" , "localhost");
 *	setValue( "dbname" , "tests_tmp_db");
 *	setValue( "dbuser" , "root");
 *	setValue( "dbpass" , "");
 *	setValue( "dbtype" , "mysql");
 *
 *	\endcode 
 * \_ru
 */
void
aCfgRc::setValue(const QString &name, const QString &value)
{
	if (values.find( name )) values.replace( name, new QString( value ));
	else values.insert( name, new QString( value ));
}


/**
 * \ru
 *	\brief Возвращает количество параметров, информация о которых храниться в объекте.
 *	
 *	\return количество параметров, информация о которых храниться в объекте.
 * \_ru
 */
int
aCfgRc::count()
{
	return ( int ) values.count();
}

/**
 * \ru
 *	\brief Возвращает имя используемого rc файла с полным путем.
 * \_ru
 */
QString
aCfgRc::getRcFileName() 
{
	return filename;
}


