/****************************************************************************
** $Id: dedittoolbar.ui.h,v 1.6 2004/12/23 14:37:55 gr Exp $
**
** Code file of the Edit Tool bar window
** of Ananas Designer applications
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
#include <qstatusbar.h>
#include <qheader.h>
#include "acfg.h"

//extern aCfg cfg;

void dEditToolbar::updateMD()
{
    int i;
    aCfgItem com_action, apix;
    al->updateMD( );
    QPixmap pix;

    item->setText( 0, eName->text().stripWhiteSpace() );
    md->setAttr( obj, mda_name, eName->text().stripWhiteSpace() );
    md->setSText( obj, md_description, eDescription->text() );
//    md->setSText( obj, md_menutext, eMenuText->text() );

    QString sKey = "";
    if ( cbKey-> currentText () != "" )
    {
	if ( cbCTRL->isChecked() )
	    sKey += md_km_ctrl;
	if ( cbALT->isChecked() )
	    sKey += md_km_alt;
	if ( cbShift->isChecked() )
	    sKey += md_km_shift;
	sKey += cbKey->currentText ();
    }
    md->setSText( obj, md_key, sKey );

    do
	{
		com_action = md->findChild( obj, md_comaction, 0 );
		if ( !com_action.isNull() )
			 md->remove( com_action );
    } while ( !com_action.isNull() );
    ananasListViewItem *aitem = (ananasListViewItem *)vComActions->firstChild();
    for ( i = 0; i < vComActions->childCount(); i++ )
	{
		com_action = md->insert( obj, md_comaction, QString::null, -1 );
		md->setText( com_action, QString( "%1" ).arg( aitem->id ) );
		aitem = (ananasListViewItem *)aitem->nextSibling();
    }
    aitem = (ananasListViewItem *)vComActions->firstChild();
    apix = md->findChild( md->find( aitem->id ), md_active_picture, 0 );
	if ( apix.isNull() )
		return;
    pix.loadFromData( md->binary( apix ) );
    item->setPixmap( 0, pix );
}

void dEditToolbar::destroy()
{
    updateMD();
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
}

void dEditToolbar::init()
{
    statusBar()->hide();
}

void dEditToolbar::setData( InterfaceListViewItem * o )
{
    int i, j, n, k, id;
    item = o;
    md = o->md;
    obj = o->obj;
    aCfgItem  com_action, apix;
    aAliasEditor *a = new aAliasEditor( md, obj, tAliases );
    QPixmap pix;

    vComActions = new ananasTreeView( tabWidget2->page(1),  md );
    vComActions->setSorting( -1 );
    layout28->addWidget( vComActions, 0, 0 );
    actiontree = new aActionTreeView ( tabWidget2->page(1),  md );
    disconnect( actiontree, SIGNAL( contextMenuRequested( QListViewItem*, const QPoint&, int) ), actiontree, SLOT(ContextMenu() ) );
    disconnect( actiontree, SIGNAL( returnPressed( QListViewItem*) ), actiontree, SLOT( itemEdit() ) );
    disconnect( actiontree, SIGNAL( doubleClicked( QListViewItem*) ), actiontree, SLOT( itemEdit() ) );
    layout29->addWidget( actiontree, 0, 0 );

    al = a;
    al->setData();

    setCaption( tr("Command:") + md->attr( obj, mda_name ) );
    eName->setText( md->attr( obj, mda_name ) );
//    eMenuText->setText( md->sText( obj, md_menutext ) );
    eDescription->setText( md->sText( obj, md_description ) );

    QString sKey = md->sText( obj, md_key );
	if ( ( sKey.find (md_km_ctrl) ) >= 0 )
	{
		cbCTRL->setChecked ( TRUE );
		sKey.remove(md_km_ctrl);
	}
	if ( ( sKey.find (md_km_alt) ) >= 0 )
	{
		cbALT->setChecked ( TRUE );
		sKey.remove(md_km_alt);
	}
	if ( ( sKey.find (md_km_shift) ) >= 0 )
	{
		cbShift->setChecked ( TRUE );
		sKey.remove(md_km_shift);
	}


	n = cbKey->count();
	for ( i = 0; i < n; i++ )
		if ( sKey == cbKey->text( i ) )
		{
			cbKey->setCurrentItem( i );
			break;
		}
    n = md->countChild( obj, md_comaction );
	k = md->count( md->find ( mdc_actions ), md_action );
	ananasListViewItem *aitem;
	for ( i = 0; i < n; i++ )
	{
		id = md->text(( md->find (obj, md_comaction, i))).toInt();
		for ( j = 0; j < k; j++)
		{
			com_action = md->find ( md->find( mdc_actions ), md_action, j  );
			if ( md->id(com_action) == id )
			{
				aitem = new ananasListViewItem (vComActions, vComActions->lastItem(), md, com_action);
				aitem->setRenameEnabled( 0, FALSE );
				apix = md->findChild( md->find( aitem->id ), md_active_picture, 0 );
				if ( apix.isNull() )
					break;
				pix.loadFromData( md->binary( apix ) );
				aitem->setPixmap( 0, pix );
			}
		}
    }
}


void
dEditToolbar::bAddAction_clicked()
{
    aCfgItem apix;
    QPixmap pix;

    ananasListViewItem *cur = (ananasListViewItem *)actiontree->selectedItem();
	if (!cur)
		return;
	if ( md->objClass( cur->obj ) != md_action )
		return;
	ananasListViewItem *aitem = new ananasListViewItem(vComActions, vComActions->lastItem(), md, cur->obj );
	apix = md->findChild( md->find( aitem->id ), md_active_picture, 0 );
	pix.loadFromData( md->binary( apix ) );
	aitem->setPixmap( 0, pix );
}


void dEditToolbar::bRemoveAction_clicked()
{
	vComActions->removeItem( vComActions->selectedItem() );
}


void dEditToolbar::bMoveUp_clicked()
{
    ananasListViewItem *aitem, *after;

    aitem = (ananasListViewItem *) vComActions->selectedItem();
    if ( aitem ) {
	after = (ananasListViewItem *)aitem->itemAbove();
	if ( after ) after->moveItem( aitem );
    }

}


void dEditToolbar::bMoveDown_clicked()
{
    ananasListViewItem *aitem, *after;
    aitem = (ananasListViewItem *)vComActions->selectedItem();
    if ( aitem ) {
	after = (ananasListViewItem *)aitem->itemBelow();
	if ( after ) aitem->moveItem( after );
    }
}
