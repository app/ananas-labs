/****************************************************************************
** $Id: usersform.ui.h,v 1.1 2005/06/10 07:55:42 gr Exp $
**
** Code file of the view user window
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
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


void UsersForm::init()
{
	mdtree=NULL;
}


void UsersForm::destroy()
{
	if(mdtree)
	{
		delete mdtree;
		mdtree=NULL;
	}

}


void UsersForm::createTree()
{
	if(mdtree)
	{
		delete mdtree;
		mdtree=NULL;
	}
    	mdtree = new aMetadataTreeView( this, cfg ); // metadata tree creation
    	mdtree->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    	layout()->add( mdtree );
    	updateGeometry();

}


void UsersForm::init( aDatabase *adb )
{
    cfg = &adb->cfg;
}
