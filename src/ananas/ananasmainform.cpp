/****************************************************************************
** $Id: ananasmainform.cpp,v 1.5 2008/10/18 22:29:28 leader Exp $
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
#include <qtimer.h>
#include "ananasmainform.h"

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
    statusBar()->setSizeGripEnabled( FALSE );
    statusLabel1 = new QLabel(" Status ", this);
    statusLabel1->setMinimumSize(statusLabel1->sizeHint());
    statusLabel1->setText(" ");
    statusLabel2 = new QLabel(tr(" TA: 34.45.3214 "),this);
    statusLabel2->setAlignment(AlignHCenter);
    statusLabel2->setMinimumSize(statusLabel2->sizeHint());
    statusLabel2->setText(" ");
    statusLabel3 = new QLabel(tr(" BI: 35.65.3214 "), this);
    statusLabel3->setAlignment(AlignHCenter);
    statusLabel3->setMinimumSize(statusLabel3->sizeHint());
    statusLabel3->setText(" ");
    //statusLabel3->clear();
    statusLabel4 = new QLabel(tr("00"), this);
    statusLabel4->setMinimumSize(statusLabel4->sizeHint());
    statusLabel4->setText("0");
    statusLabel4->setAlignment(AlignHCenter);
    statpb = new QPushButton( " ", this );
    statpb->setToggleButton ( true );
    statpb->setDefault ( false );
    statpb->setMaximumWidth(22);
    statpb->setMaximumHeight(22);

    connect(statpb , SIGNAL(toggled(bool)), this, SLOT(statpbToggled()) );
    statusBar()->addWidget(statpb, 0);
    statpb->hide();
    statusBar()->addWidget(statusLabel1, 1);
    statusBar()->addWidget(statusLabel2);
    statusBar()->addWidget(statusLabel3);
    statusBar()->addWidget(statusLabel4, 0, true);

    statpb->setFocusPolicy(QWidget::NoFocus);

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
    msgWindow = new MessagesWindow( this );// , WDestructiveClose );
    moveDockWindow( msgWindow, DockBottom );
    setMessageHandler( true );
    msgWindow->setCloseMode(0);
    msgWindow->setMovingEnabled(false);
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
    connect( &engine, SIGNAL(statusIcon( const int &) ), this, SLOT( statusIcon( const int & )) );

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
	m = new QPopupMenu();
	windowsMenu = new QPopupMenu();
	connect( windowsMenu, SIGNAL( aboutToShow() ),
	     this, SLOT( windowsMenuAboutToShow() ) );

	m->insertItem(rcIcon("ananas-32x32.png"), tr( "About" ), this, SLOT( helpAbout() ), Key_F11);
	m->insertItem(rcIcon("calc.png"), tr( "Calculator" ), this, SLOT( miniCalc() ), Key_F10);
	//windowsMenu->insertItem(rcIcon("ananas-32x32.png"), tr( "Windows" ), this, SLOT( windowsMenuAboutToShow() ));
        menubar = new AMenuBar( md, this, "menubar");
	InsertMainMenu( tr("&Help"), m );
	InsertMainMenu( tr("&Windows"), windowsMenu );
	menuBar()->show();

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
MainForm::statusIcon( const int &status )
{
	statpb->show();
	statpb->setOn(true);
	switch ( status )
	{
		case 0:
			statpb->setPixmap(rcIcon("msg_info.png"));
			break;
		case 1:
			statpb->setPixmap(rcIcon("msg_warning.png"));
			break;
		case 2:
			statpb->setPixmap(rcIcon("msg_error.png"));
			break;
		case 3:
			statpb->setPixmap(rcIcon("msg_fatal.png"));
			break;
		default:
			statpb->setPixmap(rcIcon("msg_fatal.png"));
			break;
	}
	QTimer::singleShot( 3000, this, SLOT(hideMsgWindow()) );
	statusLabel4->setText(QString("%1").arg(statusLabel4->text().toInt() + 1));
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
MainForm::hideMsgWindow()
{
	msgWindow->hide();
	statpb->setOn(false);
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
	engine.db.logout();
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
    setCaption(md->info( md_info_name )+": "+QString( tr("Ananas")+" "+ananas_libversion()) );

    int i;
    for (i=0; i < menuBar()->count(); ++i)
    {
	menuBar()->changeItem(i, QString(tr(menuBar()->text(i))));
    }
    //menuBar()->changeItem(6, QString( tr("&Windows")));
}

void MainForm::statpbToggled()
{
	if (statpb->isOn() == true)
	{
		msgWindow->show();
	}else{
		//statusLabel4->setText( "0" );
		msgWindow->hide();
	}
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
 *  Open a Calculator Widget
 */
void
MainForm::miniCalc()
{
	const QString code = "var calc= new Calc(); calc.Show();";
	engine.project.interpreter()->evaluate(code);
}

