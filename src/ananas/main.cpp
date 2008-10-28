/****************************************************************************
** $Id: main.cpp,v 1.45 2008/10/26 10:58:44 leader Exp $
**
** Main file of Ananas Engine application
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Engine application of the Ananas
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

#include <aapplication.h>
#include <qmessagebox.h>
#include <qtranslator.h>
#include <qsplashscreen.h>
#include <qtextcodec.h>
#include "ananasmainform.h"
#include "dselectdb.h"
#include "dlogin.h"
#include "ananas.h"
#include "alog.h"
#include "binreloc.h"

//QApplication *application = 0;
extern QTranslator *translator = 0, tr_app(0), tr_lib(0), tr_plugins(0);
QString lang="en",
	rcfile="",
	username="",
	userpassword="";

int setTranslator(QString lang)
{
        QString langdir;
#ifdef _Windows
	langdir = qApp->applicationDirPath()+"/translations/";
#else
	langdir = QString(br_find_data_dir("/usr/share")) + QString("/ananas/translations/");
#endif
	tr_app.load( langdir+"ananas-engine-"+lang.lower()+".qm",".");
	tr_lib.load( langdir+"ananas-lib-"+lang.lower()+".qm",".");
	tr_plugins.load( langdir+"ananas-plugins-"+lang.lower()+".qm",".");
	return 0;
}

int
parseCommandLine( int argc, char **argv )
{
	QString param, name, value;
	int i;
	char *s, locale[50]="ru";

	strncpy( locale, QTextCodec::locale(), sizeof( locale ) );
	s = strchr( locale, '_' );
	if ( s ) {
	    *s = 0;
	}
        lang = locale;
        setTranslator( lang );
//	printf("locale=%s\n", locale );
	QString str_ru=QString::null, str_en=QString::null;
	bool lang_setted = false;
	bool help_setted = false;
	for ( i=1; i<argc; i++)
	{
	    param = argv[i];
	    name = param.section("=",0,0).lower();
	    value = param.section("=",1);
//	    printf("%s = %s\n", (const char *) name, (const char *) value );
	    if (param == "--help")
	    {
		    str_ru = "Использование: ananas [--help] [--lang=<LANG>] [--rc=<RC_PATH>]\n";
		    str_ru+= "LANG=ru|en\n";
		    str_ru+= "RC_PATH=путь к *.rc файлу описания бизнес схемы\n";

	    	    str_en = "Usage: ananas [--help] [--lang=<LANG>] [--rc=<RC_PATH>]\n";
		    str_en+= "LANG=ru|en\n";
		    str_en+= "RC_PATH=path to *.rc file of paticular business scheme\n";
		    help_setted = true;

	    }
	    if (name == "--lang") {
		lang = value;
		lang_setted = true;
	        setTranslator( lang );
	    }
	    if (name == "--rc") rcfile = value;
	}
	if(help_setted)
	{
		if(lang == "ru")
		{
			printf("%s",(const char*)str_ru.local8Bit());
		}
		else
		{
			printf("%s",str_en.ascii());
		}
		return 1;
	}
	return 0;
}

int main( int argc, char ** argv )
{

	AApplication a( argc, argv, AApplication::AAT_Ananas );
//	dSelectDB dselectdb;
	dLogin dlogin;
//	application = &a;
	int rc = 1;
	bool ok;
	QPixmap pixmap;
	BrInitError error;

	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF8") );
	aLog::init("",aLog::MT_DEBUG);    

#ifndef _Windows
	if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED) {
		aLog::print(aLog::MT_INFO, QObject::tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
		aLog::print(aLog::MT_INFO, QObject::tr("Will fallback to hardcoded default path.\n"));
	}
	aLog::print(aLog::MT_DEBUG, QObject::tr("main - BinReloc path to data dir is %1.\n").arg( br_find_data_dir("/usr/share") ));
	aLog::print(aLog::MT_DEBUG, QObject::tr("main - BinReloc path to lib dir is %1.\n").arg( br_find_data_dir("/usr/lib") ));
#endif
	if ( parseCommandLine( qApp->argc(), qApp->argv() ) ) return 1;
	qApp->installTranslator( &tr_app );
	qApp->installTranslator( &tr_lib );
	qApp->installTranslator( &tr_plugins );
	pixmap = QPixmap::fromMimeSource( "engine-splash-"+lang+".png" );
	if ( pixmap.isNull() )
#ifdef _Windows
	pixmap = QPixmap::fromMimeSource( qApp->applicationDirPath()+"/engine-splash-"+lang+".png" );
	qApp->addLibraryPath( qApp->applicationDirPath() );
#else
	pixmap = QPixmap::fromMimeSource( QString(br_find_data_dir("/usr/share") ) + "/ananas/designer/locale/engine-splash-"+lang+".png");
	qApp->addLibraryPath( QString( br_find_lib_dir("/usr/lib")) + "/ananas/qt3plugins" );

        QStringList list = a.libraryPaths();
	QString libPath = "";
	QStringList::Iterator it = list.begin();
	while( it != list.end() ) {
    	    libPath += *it+":";
    	    ++it;
	}
	aLog::print(aLog::MT_DEBUG, QString("main - qt library path is '%1'\n").arg( libPath));
#endif
	printf("extensions: \n%s\n",( const char *) AExtensionFactory::keys().join("\n") );
// Test create extension
//	AExtension *e = AExtensionFactory::create("AExtTest");
//	if (e) printf("EXT OK\n"); else printf("NO EXT OK\n");

	if ( pixmap.isNull() ) pixmap = QPixmap::fromMimeSource( "engine-splash-en.png" );
	QSplashScreen *splash = new QSplashScreen( pixmap );
	MainForm *w = new MainForm( 0, "MainForm");
	mainform = w;
	if ( ananas_login( rcfile, username, userpassword, &w->engine.db, AApplication::AAT_Ananas ) ){
		splash->show();
		splash->message( QObject::tr("Init application"), Qt::AlignBottom, Qt::white );

		w->rcfile = rcfile;
	        mainformws = mainform->ws;
		mainformwl = mainform->wl;
		qApp->setMainWidget( w );
//		printf( "rcfile = %s\n", rcfile.ascii() );
		w->show();
		ok = w->init();
		splash->clear();
           	splash->finish( w );
	   	delete splash;
		if ( ok ) {
			qApp->connect( qApp, SIGNAL( lastWindowClosed() ), qApp, SLOT( quit() ) );
			rc = qApp->exec();
		} else {
			QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("Ananas runtime init error. See message window and log file for details."));
		}
		ananas_logout( &w->engine.db );
		if( w ) delete w;
		w=0;
		aLog::close();
		return rc;
	}
	else
	{
		aLog::close();
		return 0;
	}
}
