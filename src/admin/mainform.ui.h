/****************************************************************************
** $Id: mainform.ui.h,v 1.8 2008/10/26 18:54:57 leader Exp $
**
** Code file of the main window
** Ananas administrator application 
**
** Created : 20050610
**
** Copyright (C) 2003-2005 Grigory Panov <gr1313 at mail dot ru>, Yoshkar-Ola.
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
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

#include "usersform.h"
#include "rolesform.h"

#include <qdatatable.h>
#include <qsqlcursor.h>

void MainForm::fileNew()
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


void MainForm::filePrint()
{

}


void MainForm::fileExit()
{
 close();
}


/*!
 * Users functions.
 */
void MainForm::adminUsers()
{
    if(usersForm->isHidden())
    {
	    usersForm->init(db);
	    usersForm->createTree();
	    usersForm->show();
	    if(!rolesForm->isHidden())
	    {
		    rolesForm->hide();
	    }
		    
    }
}


bool MainForm::init()
{
    QVBox* vb = new QVBox( this );
    vb->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
    ws = new QWorkspace( vb );
    vb->setShown(true); // need to correct work
    //wl = new aWindowsList();
    ws->setScrollBarsEnabled( TRUE );
    setCentralWidget( vb );
   // if ( cfg.readrc( rcfile ) )
   // {
// 	    printf( "readrc ERROR\n" );
//	    return false;
 //   }
    db = aDatabase::database();
    if(db->init(rcfile))
    {
    //vb->activate();
	usersForm = new UsersForm(ws);
   	usersForm->hide();
    	rolesForm = new RolesForm(ws);
    	rolesForm->hide();
	
	QSqlCursor *t = new QSqlCursor( db->qds->tableName( db_users ), true, db->db() );
	QDataTable *dt = new QDataTable( t, false, ws );
	dt->addColumn("login",tr("Login name"));
	dt->addColumn("fname",tr("First name"));
	dt->addColumn("lname",tr("Last name"));
	dt->addColumn("active1",tr("Ananas"));
	dt->addColumn("active2",tr("Designer"));
	dt->addColumn("active3",tr("Admin"));
	dt->setColumnStretchable(0, true);
	dt->setColumnReadOnly(0, true);
	dt->setColumnReadOnly(1, true);
	dt->setColumnReadOnly(2, true);
//	dt->setColumnReadOnly(1, true);
	dt->show();
        dt->refresh();
	
    }
    else
    {
	    return false;
    }
			    
  return true;
} 




void MainForm::adminRoles()
{
     if(rolesForm->isHidden())
     {
	     rolesForm->init(db);
	     rolesForm->createTree();
	     rolesForm->show();
	     if(!usersForm->isHidden())
	     {
		     usersForm->hide();
	     }
	     
     }
}
