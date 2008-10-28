/****************************************************************************
** $Id: main.cpp,v 1.39 2008/10/26 10:58:52 leader Exp $
**
** Main file of Ananas Designer application
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Designer application of the Ananas
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
#include <qtranslator.h>
#include <qsplashscreen.h>
#include <qtextcodec.h>
#include "alog.h"
#include "ananas.h"
#include "mainform.h"
#include "dselectdb.h"
#include "formdesigner.h"
#include "binreloc.h"


MainForm *mainform = 0;
aWindowsList *mainformwl = 0;
QWorkspace *mainformws = 0;
//QApplication *application = 0;
QTranslator *translator = 0, tr_app(0), tr_lib(0), tr_plugins(0);
aFormDesigner *formdesigner = 0;
QString lang="en", 
	rcfile="", 
	username="", 
	userpassword="";
    

int setTranslator(QString lang)
{
        QString langdir;
#ifdef Q_OS_WIN32
	langdir = qApp->applicationDirPath()+"/translations/";
#else
	langdir = QString( br_find_data_dir( "/usr/share") ) + "/ananas/translations/";
#endif
	tr_app.load( langdir+"ananas-designer-"+lang+".qm",".");
	tr_lib.load( langdir+"ananas-lib-"+lang+".qm",".");
	tr_plugins.load( langdir+"ananas-plugins-"+lang+".qm",".");
	return 0;
}

int 
parseCommandLine( int argc, char **argv )
{
	QString param, name, value;
	int i;
	char *s, locale[50]="en";

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
	    if (param == "--help")
	    {
		    str_ru = "Использование: ananas-designer [--help] [--lang=<LANG>] [--rc=<RC_PATH>]\n";
		    str_ru+= "LANG=ru|en\n";
		    str_ru+= "RC_PATH=путь к *.rc файлу описания бизнес схемы\n";
			    
	    	    str_en = "Usage: ananas-designer [--help] [--lang=<LANG>] [--rc=<RC_PATH>]\n";
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
	AApplication app ( argc, argv, AApplication::AAT_Designer );
	MainForm *w = new MainForm();
//#ifndef _Windows
        QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF8") );
//#endif
	mainform = w;
	mainformws = mainform->ws;
	mainformwl = mainform->wl;
//	application = &app;
//	dSelectDB dselectdb;
	int rc;
	QPixmap pixmap;
	BrInitError error; 
    
	aLog::init("",aLog::MT_DEBUG);    
#ifndef Q_OS_WIN32
	if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED) { 
		aLog::print(aLog::MT_INFO, QObject::tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
		aLog::print(aLog::MT_INFO, QObject::tr("Will fallback to hardcoded default path.\n"));
	} 
	aLog::print(aLog::MT_DEBUG, QObject::tr("main - BinReloc path to data dir is %1.\n").arg( br_find_data_dir("/usr/share") ));
#endif
	if ( parseCommandLine( argc, argv ) ) return 1;
	qApp->installTranslator( &tr_lib );
	qApp->installTranslator( &tr_plugins );
	qApp->installTranslator( &tr_app );
	pixmap = QPixmap::fromMimeSource( "designer-splash-"+lang+".png" );
	if ( pixmap.isNull() ) 
#ifdef Q_OS_WIN32
	pixmap = QPixmap::fromMimeSource( qApp->applicationDirPath()+"/designer-splash-"+lang+".png" );
	qApp->addLibraryPath( qApp->applicationDirPath() );
#else
	pixmap = QPixmap::fromMimeSource( QString(br_find_data_dir("/usr/share")) + "/ananas/designer/locale/designer-splash-"+lang+".png" );
	qApp->addLibraryPath( QString( br_find_lib_dir("/usr/lib")) + "/ananas/qt3plugins" );
#endif
        QStringList list = app.libraryPaths();
	QString libPath = "";
        QStringList::Iterator it = list.begin();
        while( it != list.end() ) {
	    libPath += *it+":";
    	    ++it;
	}	
	aLog::print(aLog::MT_DEBUG, QString("main - qt library path is '%1'\n").arg( libPath));
	if ( pixmap.isNull() ) 
	pixmap = QPixmap::fromMimeSource( "designer-splash-en.png" );
   	QSplashScreen *splash = new QSplashScreen( pixmap );
	if ( ananas_login( rcfile, username, userpassword, aDatabase::database(), AApplication::AAT_Designer ) ){
//	if ( rcfile.isEmpty() ) {
//    	    if (dselectdb.exec()==QDialog::Accepted) rcfile = dselectdb.rcfile;
//	}
//	if ( !rcfile.isEmpty() ) {
//		if (dselectdb.rcfile.isEmpty()) return 0;
	       	
		splash->show();
		splash->message( QObject::tr("Init application"), Qt::AlignBottom, Qt::white );
		w->rcfile = rcfile;
		qApp->setMainWidget( w );
		splash->message( QObject::tr("Init forms designer"), Qt::AlignBottom, Qt::white  );
	   	
   		formdesigner = new aFormDesigner();

		formdesigner->reparent( mainformws, 0, QPoint( 5, 5 ), false );
		formdesigner->setCaption( QObject::tr("Dialog forms designer") );
		formdesigner->hide();
		w->show();
		splash->clear();
       		splash->finish( w );
       		delete splash;
		qApp->connect( qApp, SIGNAL( lastWindowClosed() ), qApp, SLOT( quit() ) );
		mainform->configOpen();
//		QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF8") );

		rc = app.exec();
		if( w ) delete w;
		ananas_logout();
		w=0;
		aLog::close();
		return rc;
	}
	aLog::close();
	return 0;
}
