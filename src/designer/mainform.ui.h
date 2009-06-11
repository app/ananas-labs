/****************************************************************************
** $Id: mainform.ui.h,v 1.47 2007/05/26 19:01:03 leader Exp $
**
** Main window of Ananas Designer applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Designer application  of the Ananas
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
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <qapplication.h>
#include <qsettings.h>
#include "qfiledialog.h"
#include "qstatusbar.h"
#include "qmessagebox.h"
#include <qapplication.h>

#include "ananas.h"
//#include "adatabase.h"
//#include "acfgrc.h"
#include "cfgform.h"
//#include "messageswindow.h"
#include "dselectdb.h"
#include "alog.h"

//#include "qananastable.h"

extern CfgForm *configform;
//extern QApplication *application;
extern void messageproc(int n, const char *msg);


void MainForm::filePrint()
{

}

void MainForm::fileExit()
{
//    cfg_done();
}

void MainForm::editUndo()
{
    
}

void MainForm::editRedo()
{
    
}

void MainForm::editCut()
{
    
}

void MainForm::editCopy()
{
    
}

void MainForm::editPaste()
{
    
}

void MainForm::editFind()
{
    
}

void MainForm::helpIndex()
{
    
}

void MainForm::helpContents()
{
    
}

void MainForm::helpAbout()
{
    QMessageBox::about( this, tr("About Ananas.Designer"),
			tr("<h4>Ananas.Designer %1</h4> is a programm<br>"
			   "for adjusting accounting automation system<br><br>"
			   "Copyright 2003-2006 Leader Infotech, Valery Grazdankin <br>" 
			   "Copyright 2003-2006 Project Ananas, Andrey Paskal, Grigory Panov, Andrey Strelnikov<br>"
			   "License: GPL<br><br>"
			   "technical support:<br>"
			   "lider-infotech@narod.ru<br>"
			   "app@linux.ru.net<br>"
			   "Web sites:<br>"
			   "<a href=\"http://ananas.lrn.ru\">http://ananas.lrn.ru</a><br>"
			   "<a href=\"http://www.leaderit.ru\">http://www.leaderit.ru</a>"
			   "<br><br>Avalable extensions:<br>%2").arg(ananas_libversion()).arg( AExtensionFactory::keys().join(", ")) );
}


void MainForm::init()
{	

			 
    setName("ananas-designer_mainwindow");
    rcfile="";
    windowsMenu = new QPopupMenu( this );
    windowsMenu->setCheckable( TRUE );
    connect( windowsMenu, SIGNAL( aboutToShow() ),
	     this, SLOT( windowsMenuAboutToShow() ) );
    menuBar()->insertItem( tr("&Windows"), windowsMenu );

    menuBar()->insertSeparator();
    QPopupMenu * help = new QPopupMenu( this );
    menuBar()->insertItem( tr("&Help"), help );

    help->insertItem( tr("&About"), this, SLOT(helpAbout()), Key_F1);
  //  help->insertItem( tr("&Test"), this, SLOT(helpTest()));
    //    help->insertItem( "About &Qt", this, SLOT(aboutQt()));
    help->insertSeparator();
    //    help->insertItem( trUtf8("Что &это"), this, SLOT(whatsThis()), SHIFT+Key_F1);


    designer_settings.insertSearchPath( QSettings::Unix, QString(QDir::homeDirPath())+QString("/.ananas"));
    designer_settings.insertSearchPath( QSettings::Windows, "/ananasgroup/ananas" );
    
//    QStringList lst = settings.entryList("/engine");
    designer_settings.beginGroup("/designer");
    bool maximize = designer_settings.readBoolEntry( "/maximize", 0 );
    int width = designer_settings.readNumEntry( "/geometry/width", 600 );
    int height = designer_settings.readNumEntry( "/geometry/height", 480 );
    int offset_x = designer_settings.readNumEntry( "/geometry/x", 0 );
    int offset_y = designer_settings.readNumEntry( "/geometry/y", 0 );
    designer_settings.endGroup();
    resize( QSize(width, height) );//  .expandedTo(minimumSizeHint()) );
    move(offset_x,offset_y);
    if(maximize)
    {
//	   setWindowState(windowState() ^ WindowMaximized); 
    }
    
    setIcon( rcIcon("ananas-32x32.png"));
    setCaption(tr("Ananas: Designer"));
    QVBox* vb = new QVBox( this );
    vb->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
    ws = new QWorkspace( vb );
    wl = new aWindowsList();
    ws->setScrollBarsEnabled( TRUE );
    setCentralWidget( vb );
    cfgform=NULL;

    MessagesWindow *msgWindow = new MessagesWindow( this ); // , WDestructiveClose );
    moveDockWindow( msgWindow, DockBottom );
    setMessageHandler( TRUE );
    msgWindow->hide();
    tbMetadata->setShown( FALSE );
    tbActions->setShown( FALSE );
    tbInterface->setShown( FALSE );
    tbRights->setShown( FALSE );
    tbLanguages->setShown( FALSE );
    tbImageCollection->setShown( FALSE );
    TBToolbar->setShown( FALSE );
    tbTabs->setShown( FALSE );
    lastTabId = 0;
    configSaveAction->setVisible( FALSE );
}

void MainForm::configNew()
{
	CfgForm *cf = cfgForm();
	if (cf)
	{
		if ( !cf->close() ) return; // close configuration form if opened
    	}
    	cf = new CfgForm(ws, 0, WDestructiveClose); // create new cfgform
   	if ( cf )
	{
		cf->init( rcfile, TRUE ); // initialization NEW configuration
		connectSignals( cf );
		cf->ws=ws;
		cf->show();
 		((QWidget*)cf->parent())->move(0,0);
		addTab(++lastTabId,cf->name());
	}
}

void MainForm::configOpen()
{
	CfgForm *cf = cfgForm();
	if ( cf )
	{
		if ( !cf->close() ) return;
   	}
	if ( rcfile.isEmpty()) return;
	cf = new CfgForm( ws, 0, WDestructiveClose); 
	if ( cf )
	{
		cf->init( rcfile, FALSE );	//	initialization configuration
		connectSignals( cf );
		cf->ws=ws;
		cf->show();
 		((QWidget*)cf->parent())->move(0,0);
		addTab(++lastTabId,cf->name());
    }
}

void MainForm::configSave()
{
    emit tosave();
    CfgForm *cf = cfgForm();
    if ( cf ) cf->save();	//	get configuration form and save its data
}

void MainForm::configSaveAs()
{
}



void MainForm::fileOpen()
{
    
}

void MainForm::fileSave()
{
    
}

void MainForm::fileSaveAs()
{
    
}

void MainForm::fileNew()
{

}

void MainForm::windowsMenuActivated( int id )
{
    QWidget* w = ws->windowList().at( id );
    if ( w ) w->showNormal();
    w->setFocus();
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
    for ( int i = 0; i < int( windows.count() ); ++i ) {
	int id = windowsMenu->insertItem(windows.at(i)->caption(), this, SLOT( windowsMenuActivated( int ) ) );
	windowsMenu->setItemParameter( id, i );
	windowsMenu->setItemChecked( id, ws->activeWindow() == windows.at(i) );
    }
}

void MainForm::tileHorizontal()
{
    // primitive horizontal tiling
    QWidgetList windows = ws->windowList();
    if ( !windows.count() )
	return;
    
    int heightForEach = ws->height() / windows.count();
    int y = 0;
    for ( int i = 0; i < int(windows.count()); ++i ) {
	QWidget *window = windows.at(i);
	if ( window->testWState( WState_Maximized ) ) {
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


void MainForm::closeEvent( QCloseEvent *e )
{
    if (configform)
    {
	if (!configform->close())
	{
	    e->ignore();
	    return;
	}
    }

        designer_settings.beginGroup("/designer");
//	designer_settings.writeEntry( "/maximize", windowState()&WindowMaximized ? true: false);
	designer_settings.writeEntry( "/geometry/width", width() );
	designer_settings.writeEntry( "/geometry/height", height() );
	designer_settings.writeEntry( "/geometry/x", pos().x() );
	designer_settings.writeEntry( "/geometry/y", pos().y() );
	designer_settings.endGroup();
	//aLog::print(aLog::MT_DEBUG,"exit");
    QMainWindow::closeEvent( e );
}


void MainForm::connectSignals( CfgForm *cf )
{
    connect(objNewFormAction, SIGNAL(activated()), cf, SLOT(newForm()));
    connect(objNewTableAction, SIGNAL(activated()), cf, SLOT(newTable()));
    connect(objNewFieldAction, SIGNAL(activated()), cf, SLOT(newField()));
    connect(objRenameAction, SIGNAL(activated()), cf->mdtree, SLOT(itemRename()));
    connect(objNewObjAction, SIGNAL(activated()), cf->mdtree, SLOT(itemNew()));
    connect(objEditAction, SIGNAL(activated()), cf->mdtree, SLOT(itemEdit()));
    connect(objDeleteAction, SIGNAL(activated()), cf->mdtree, SLOT(itemDelete()));
}


void MainForm::getMd( aCfg **md )
{
	CfgForm *cf = cfgForm();
	if ( !cf ) return;
	*md = &cf->cfg;
}

/*!
Get current configuration form
*/
CfgForm *
MainForm::cfgForm()
{
	CfgForm *res = 0;
	QWidgetList windows = ws->windowList();
	for ( int i = 0; i < int( windows.count() ); ++i ) {
		if ( strcmp( windows.at(i)->className(),"CfgForm") == 0 ){
			res = ( CfgForm *) windows.at(i);
			break;
		}
	}
	return res;
}


QWidget *
MainForm::activeWindow()
{
	return ws->activeWindow();
}


int MainForm::getId()
{
    return  lastFormId;
}


void MainForm::addTab(int uid, const QString& winName )
{
    QWidgetList windows = ws->windowList();
    QToolButton* bt;
    
    QString S = winName;
    for ( int i = 0; i < int( windows.count() ); i++ ) {
		if( !strcmp(windows.at(i)->name(), S.ascii()))
		{
			windows.at(i)->setName(QString(windows.at(i)->name()+QString("_%1").arg(uid)));
			//ixmap pixmap(*windows.at(i)->icon());
			bt = new QToolButton(QIconSet(),
					     windows.at(i)->caption(),
					     "",
					     windows.at(i),
					     SLOT(setFocus( )),
					     tbTabs,
					     windows.at(i)->name() );
				
			bt->setUsesTextLabel ( true );
//		 	bt->setAutoRaise ( true );
		//	aLog::print(aLog::MT_DEBUG, QString("button name = %1").arg(bt->name()));
			break;
			
		}
/*		if( windows.at(i)->isShown() and !strcmp(windows.at(i)->name(),"designer_mainwindow"))
		{
			
			bt = new QToolButton(QIconSet(),
					     windows.at(i)->caption(),
					     "",
					     windows.at(i),
					     SLOT(setFocus( )),
					     tbTabs,
					     windows.at(i)->name() );
				
			bt->setUsesTextLabel ( true );
//		 	bt->setAutoRaise ( true );
			printf("button name = %s\n",bt->name());
			break;
		}
		*/
	}
   // }
//    if(windows.count()>1)
    if(tbTabs->queryList ("QToolButton"))
    {
	//    tbTabs->show();
	    
    	tbTabs->setShown( true );
    }
    else
    {
	//   tbTabs->hide();
    	tbTabs->setShown( false );
    }
}


void MainForm::removeTab(const  QString &winName )
{
//	int ind = winName.findRev("_");
//	printf("winName = %s\n",winName.ascii());
//	QString str = winName;
//	str = str.remove(ind,winName.length()-ind); 
	QObject *button = tbTabs->child( winName );
	if(button)
	{
		
//		printf("deletes tab\n");
		delete button;
		button = NULL;
	}
	
}


void MainForm::closeChildWindows()
{
 
    QWidgetList windows = ws->windowList();
    for ( int i = 0; i < int( windows.count() ); i++ )
    {
 if(windows.at(i)->className() != QString::QString("CfgForm"))
 {
  windows.at(i)->close();
 }
    }
}


void MainForm::fileNewAction_activated()
{

}
