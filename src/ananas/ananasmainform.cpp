/****************************************************************************
** $Id: ananasmainform.cpp,v 1.2 2007/12/24 07:53:51 app Exp $
**
** Code file of the Main form of Ananas Engine application
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

/****************************************************************************
****************************************************************************/
#include <qmenubar.h>
#include <qmessagebox.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qworkspace.h>
#include <qapplication.h>
#include <qaction.h>
#include <qdir.h>
#include <qtextcodec.h>

#include "ananasmainform.h"

#include "ananas.h"
#include "aminicalc.h"
#include "ananas.h"
#include "binreloc.h"

MainForm *mainform=NULL;
QWorkspace *mainformws=NULL;
aWindowsList *mainformwl=NULL;
//extern void messageproc(int n, const char *msg);

/*
 *  Constructs a AnanasMainWindow as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl )
{
//    QApopupmenu *popup;
    QVBox	*vb = new QVBox(this);

    setIcon( rcIcon("ananas-32x32.png"));
    vb->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
    ws = new QWorkspace( vb );
    wl = new aWindowsList();
    ws->setScrollBarsEnabled( TRUE );
    setCentralWidget( vb );
    statusBar()->setName("statusbar");

    statusLabel1 = new QLabel(" Status ", this);
    statusLabel1->setMinimumSize(statusLabel1->sizeHint());

    statusLabel2 = new QLabel(tr(" Info1 "),this);
    statusLabel2->setAlignment(AlignHCenter);
    statusLabel2->setMinimumSize(statusLabel2->sizeHint());
    statusLabel3 = new QLabel(tr(" Info2 "), this);
    statusLabel3->setAlignment(AlignHCenter);
    statusLabel3->setMinimumSize(statusLabel3->sizeHint());
    //statusLabel3->clear();
    statusLabel4 = new QLabel(tr(" Icon "), this);
    statusLabel4->setMinimumSize(statusLabel4->sizeHint());
    statusLabel4->setAlignment(AlignHCenter);
    statusLabel4->setPixmap(rcIcon("ru.png"));
    statusBar()->addWidget(statusLabel1, 1);
    statusBar()->addWidget(statusLabel2);
    statusBar()->addWidget(statusLabel3);
    statusBar()->addWidget(statusLabel4, 0, true);

    if ( !name ) setName( "mainwindow" );
    engine_settings.insertSearchPath( QSettings::Unix, QString(QDir::homeDirPath())+QString("/.ananas"));
    engine_settings.insertSearchPath( QSettings::Windows, "/ananasgroup/ananas" );

//    QStringList lst = settings.entryList("/engine");
    engine_settings.beginGroup("/engine");
    bool maximize = engine_settings.readBoolEntry( "/maximize", 0 );
    int width = engine_settings.readNumEntry( "/geometry/width", 600 );
    int height = engine_settings.readNumEntry( "/geometry/height", 480 );
    int offset_x = engine_settings.readNumEntry( "/geometry/x", 0 );
    int offset_y = engine_settings.readNumEntry( "/geometry/y", 0 );
    engine_settings.endGroup();
    resize( QSize(width, height) );//  .expandedTo(minimumSizeHint()) );
    move(offset_x,offset_y);
    if(maximize)
    {
//	   setWindowState(windowState() ^ WindowMaximized);
    }
    rcfile="";
}

bool
MainForm::init()
{
    MessagesWindow *msgWindow = new MessagesWindow( this );// , WDestructiveClose );
    moveDockWindow( msgWindow, DockBottom );
    setMessageHandler( true );
    msgWindow->hide();
    if ( !initEngine() ) return false;
    connect( menubar, SIGNAL(activated(int)), &engine, SLOT(on_MenuBar(int)) );
    languageChange();
    engine.project.addObject(menubar);
    engine.project.addObject(this);
    engine.project.addObject(statusBar());
    languageChange();
    engine.on_systemstart();
    return true;
}

bool
MainForm::initEngine()
{
    if (rcfile.isEmpty()) return false;
    if ( !engine.init( rcfile ) ) return false;
    engine.ws = ws;
    engine.wl = wl;
    connect( &engine, SIGNAL( statusMessage( const QString & ) ), this, SLOT( statusMessage( const QString & ) ) );
    connect( &engine, SIGNAL( statusMessage( const QString &, const int & ) ), this, SLOT( statusMessage( const QString & , const int & ) ) );

    md = engine.md;
    if ( !md ) return false;
    initMenuBar();
    initStatusBar();
    initActionBar();
    return true;
}

void
MainForm::initMenuBar()
{
	QPopupMenu *m;
	QPopupMenu *tools;
	QPopupMenu *p;

	m = new QPopupMenu();
	tools = new QPopupMenu();
	lang = new QPopupMenu();
	lang->setCheckable( TRUE );
	// TODO!!! Check *qm files and complit list

	statusLabel3->setText(QString("%1\n").arg(QTextCodec::locale()));
	e_lang = lang->insertItem( tr("EN"), 0, 0);
	lang->setItemChecked( e_lang, true );
	r_lang = lang->insertItem(  tr("RU"), 1, 1);
	lang->setItemChecked( r_lang, false );
	u_lang = lang->insertItem( tr("UA"), 2, 2);
	lang->setItemChecked( u_lang, false );

	connect(lang, SIGNAL(activated(int)), this, SLOT(setLang(int)));

	windowsMenu = new QPopupMenu();
	connect( windowsMenu, SIGNAL( aboutToShow() ),
	     this, SLOT( windowsMenuAboutToShow() ) );
	systemMenu = new QPopupMenu();
	systemMenu->insertItem( tr( "Login As..." ), this, SLOT( loginAs() ));
	systemMenu->insertItem( "&Language Selector", lang );
	systemMenu->insertSeparator();
	systemMenu->insertItem(rcIcon("ananas-32x32.png"), tr( "Exit" ), qApp, SLOT( closeAllWindows() ), CTRL+Key_Q);

	m->insertItem(rcIcon("ananas-32x32.png"), tr( "About" ), this, SLOT( helpAbout() ), Key_F11);
	tools->insertItem(rcIcon("calc.png"), tr( "Calculator" ), this, SLOT( miniCalc() ), Key_F10);
	tools->insertItem(rcIcon("calendar.png"), tr( "Calendar" ), this, SLOT( ShowCalendar() ), Key_F12);
	//windowsMenu->insertItem(rcIcon("ananas-32x32.png"), tr( "Windows" ), this, SLOT( windowsMenuAboutToShow() ));
        menubar = new AMenuBar( md, this, "menubar");
	InsertMainMenu( tr("&Tools"), tools );
	InsertMainMenu( tr("&Help"), m );
	InsertMainMenu( tr("&Windows"), windowsMenu );
	menuBar()->insertItem(tr("&System"),systemMenu,0,0);
	menuBar()->show();

}

void
MainForm::loginAs()
{
	statusBar()->message( "Try again later...", 3000 );
}

void
MainForm::initStatusBar()
{
}

void
MainForm::initActionBar()
{
    aCfgItem obj, item;

    obj = md->find( md->find( mdc_interface ), md_toolbars );	// look for md_toolbars
    item = md->firstChild( obj );
    while ( !item.isNull() ) {	// foreach md_toolbar
	new aToolBar( md, item, &engine, this, md->attr( item, mda_name ) );		// create toolbar
	item = md->nextSibling( item );	// next md_toolbar
    }
}

void
MainForm::helpAbout()
{
    QMessageBox::about( this, tr("About Ananas.Engine program"),
			trUtf8("<h4>\"%1\"</h4>"
			   "%2<br><br>"
			   "Автор: %3<br>"
			   "%4<br><br>"
 			   "Разработано на платформе \"Ананас\"! (версия %5)<br>"
 			   "Доступные расширения:<br>%6")
			   .arg(md->info( md_info_name ))
			   .arg(md->info( md_info_remark ))
			   .arg(md->info( md_info_author ))
			   .arg(md->info( md_info_date ))
			   .arg(ananas_libversion())
			   .arg( AExtensionFactory::keys().join(", ")) );
}

void MainForm::InsertMainMenu(QString text, QObject *pop){
    menubar->insertItem(text, (QPopupMenu *) pop);
}


void
MainForm::Exit(int code)
{

	qApp->exit(code);
}

void
MainForm::close()
{
        engine_settings.beginGroup("/engine");
//	engine_settings.writeEntry( "/maximize", windowState()&WindowMaximized ? true: false);
	engine_settings.writeEntry( "/geometry/width", width() );
	engine_settings.writeEntry( "/geometry/height", height() );
	engine_settings.writeEntry( "/geometry/x", pos().x() );
	engine_settings.writeEntry( "/geometry/y", pos().y() );
	engine_settings.endGroup();
	//printf("exit\n" );
//MainWindow::close();
}

void
MainForm::statusMessage( const QString &msg, const int &pos )
{
	switch ( pos )
	{
		case 0:
			statusBar()->message( msg, 3000);
			break;
		case 1:
			statusLabel1->setText( msg );
			break;
		case 2:
			statusLabel2->setText( msg );
			break;
		case 3:
			statusLabel3->setText( msg );
			break;
		default:
			statusBar()->message( msg, 3000 );
			break;
	}

}


void
MainForm::statusMessage( const QString &msg )
{
 	//statusBar()->message( msg );
	statusLabel1->setText( msg );
}


void
MainForm::setBackground( const QPixmap &pix ){
	ws->setBackgroundPixmap( pix );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainForm::~MainForm()
{
	engine.on_systemstop();
	close();
//	printf("Mainform destructor\n");
	if(ws) delete ws;
	ws = 0;
	if(wl) delete wl;
	wl=0;
	if(menubar) delete menubar;
	menubar=0;
//	printf("delete mainform\n");
//    cfg->on_systemstop();
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainForm::languageChange()
{
    setCaption(QString( tr("Ananas")+" "+ananas_libversion() )+": "+md->info( md_info_name ) );

    int i;
    for (i=0; i < menuBar()->count(); ++i)
    {
	menuBar()->changeItem(i, QString(tr(menuBar()->text(i))));

    }
    //menuBar()->changeItem(6, QString( tr("&Windows")));
//    setCaption( tr( "Ananas VERSION" ) );
}

void MainForm::windowsMenuAboutToShow()
{
    windowsMenu->clear();
    int cascadeId = windowsMenu->insertItem(tr("&Cascade"), ws, SLOT(cascade() ) );
    int tileId = windowsMenu->insertItem(tr("&Tile"), ws, SLOT(tile() ) );
    int horTileId = windowsMenu->insertItem(tr("Tile &horizontal"), this, SLOT(tileHorizontal() ) );
    if ( ws->windowList().isEmpty() ) {
	windowsMenu->setItemEnabled( cascadeId, FALSE );
	windowsMenu->setItemEnabled( tileId, FALSE );
	windowsMenu->setItemEnabled( horTileId, FALSE );
    }
    windowsMenu->insertSeparator();
    QWidgetList windows = ws->windowList();
    if(windows.count()==0) return;
    int i=0, count = windows.count();

    do
    {
	int id=0;
	if(windows.at(i) && windows.at(i)->isHidden())
	{
		++i;
		continue;
	}
	id = windowsMenu->insertItem(windows.at(i)->caption(), this, SLOT( windowsMenuActivated( int ) ) );
	windowsMenu->setItemParameter( id, i );
	windowsMenu->setItemChecked( id, ws->activeWindow() == windows.at(i) );
	++i;
    }while( i < count );
}


void MainForm::tileHorizontal()
{
    // primitive horizontal tiling
    QWidgetList windows = ws->windowList();
    int count =0;
    for ( int i = 0; i < int(windows.count()); ++i )
    {
	QWidget *window = windows.at(i);
	if( !window ) continue;
	if(!window->isHidden()) count++;
    }
    if ( !count ) return;

    int heightForEach = ws->height() / count;
    int y = 0;
    for ( int i = 0; i < windows.count(); ++i )
    {
	QWidget *window = windows.at(i);
	if ( !window ) continue;
	if ( window->isHidden() ) continue;
	if ( window->testWState( WState_Maximized ) )
	{
	    // prevent flicker
	    window->hide();
	    window->showNormal();
	}
	int preferredHeight = window->minimumHeight()+window->parentWidget()->baseSize().height();
	int actHeight = QMAX(heightForEach, preferredHeight);

	window->parentWidget()->setGeometry( 0, y, ws->width(), actHeight );
	y += actHeight;
    }
}

void MainForm::windowsMenuActivated( int id )
{
    QWidget* w = ws->windowList().at( id );
    if ( w ) w->showNormal();
    w->setFocus();
}

/*
 *  Language selector
 */
void MainForm::setLang( int lang_id )
{
	QString langdir;
	QString a_lang;
	extern QTranslator tr_app;
	extern QTranslator tr_lib;
	extern QTranslator tr_plugins;
	qApp->removeTranslator( &tr_app );
	qApp->removeTranslator( &tr_lib );
	qApp->removeTranslator( &tr_plugins );

#ifdef _Windows
	langdir = qApp->applicationDirPath()+"/translations/";
#else
	//langdir = QString("/usr/share/ananas/translations/");
	langdir = QString(br_find_data_dir("/usr/share")) + QString("/ananas/translations/");
#endif
	if (lang_id == 0)
	{
		lang->setItemChecked( 0, true );
		lang->setItemChecked( 1, false );
		lang->setItemChecked( 2, false );
		a_lang = "en";
	}
	if (lang_id == 1)
	{
		lang->setItemChecked( 0, false );
		lang->setItemChecked( 1, true );
		lang->setItemChecked( 2, false );
		a_lang = "ru";
	}
	if (lang_id == 2)
	{
		lang->setItemChecked( 0, false );
		lang->setItemChecked( 1, false );
		lang->setItemChecked( 2, true );
		a_lang = "ua";
	}

	if (!tr_app.load("ananas-engine-"+a_lang.lower()+".qm", langdir)) printf("No tr_app.load\n");

	if (!tr_lib.load("ananas-lib-"+a_lang.lower()+".qm", langdir)) printf("No tr_lib.load\n");

	if (!tr_plugins.load("ananas-plugins-"+a_lang.lower()+".qm", langdir)) printf("No tr_plug.load\n");

	qApp->installTranslator( &tr_app );
	qApp->installTranslator( &tr_lib );
	qApp->installTranslator( &tr_plugins );

	languageChange();
	statusBar()->message( QString(tr("Ananas"))+ QString(tr(" : %1")).arg(lang->text(lang_id)), 2000 );
}

/*
 *  Open a Calculator Widget
 */
void
MainForm::miniCalc()
{
	MiniCalc *calc = new MiniCalc(ws, "MiniCalc", false, 0);
	calc->show();
}

/*
 *  Open a Calendar
 */
void
MainForm::ShowCalendar()
{
	PopupCalendar *calendar = new PopupCalendar(QDate::currentDate(),
		QPoint(ws->width() / 2, ws->height() / 2 ), ws, "");
	calendar->show();
}
