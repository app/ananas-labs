/****************************************************************************
** $Id: eactionbutton.ui.h,v 1.10 2007/04/19 07:30:49 gr Exp $
**
** Code file of the edit catalogue plugin of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Ananas Plugins of the Ananas
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
#include <qseditor.h>
#include <stdlib.h>

void eActionButton::Action_toggled( bool o )
{
    Script->setChecked( !o );
    //else 
}


void eActionButton::Script_toggled( bool o )
{
    Action->setChecked( !o );
}

void eActionButton::setData(  wActionButton *b )
{
    if ( !b ) return;
    if ( b->isAction() ) Action->setChecked( TRUE );
    if ( b->isActionUpdate() ) cbUpdate->setChecked( TRUE );
    if ( b->isActionTurnOn() ) cbTurnon->setChecked( TRUE );
    if ( b->isActionClose() ) cbClose->setChecked( TRUE );
    if ( b->isScript() ) Script->setChecked( TRUE );
//    cbAction->setCurrentItem(b->getAction())
    // eCode->setText( b->getScriptCode() );
//    button = b;
    aWidget *wd = aWidget::parentContainer( b );
    if ( !strcmp(wd->name(),"Catalogue") )
    {
	    cbTurnon->setChecked( false );
	    cbTurnon->setHidden( TRUE );
	
//	b->setActionTurnOn( FALSE );
    }
    aCfg *md = wd->getMd();
    QStringList l_name;
    aCfgItem parent = md->find(mdc_actions);
    l_id.clear();
    loadActions(&l_name, &l_id, parent, md);
    cbAction->clear();
    cbAction->insertStringList(l_name);
    cbAction->setCurrentItem( l_id.findIndex( QString("%1").arg(b->getActionId()) ) );
    
}


void eActionButton::getData( wActionButton *button)
{
    if ( !button ) return;
    button->setAction( Action->isChecked() );
    button->setActionUpdate( cbUpdate->isChecked() );
    button->setActionTurnOn( cbTurnon->isChecked() );
    button->setActionClose( cbClose->isChecked() );
    button->setScript( Script->isChecked() );
    button->setActionUpdate( cbUpdate->isChecked() );
    if(cbAction->isEnabled())
    {
	    
    	button->setActionId ( atoi(l_id[cbAction->currentItem()].ascii()));
    }
    else 
    {
	    button->setActionId(0);
    }
//    button->setScriptCode( eCode->text() );
}

void eActionButton::destroy()
{
    //getData();
}


void 
eActionButton::loadActions( QStringList *lst, QStringList *id,  aCfgItem p, aCfg *md )
{
	aCfgItem cobj;
	QString oclass;
	if(p.isNull())
	{
		p = md->find(mdc_actions);
	//	printf("parent were NULL, set parent to %s\n",md->objClass(p).ascii());
	}
	
	if(p.isNull()) return;
	cobj = md->firstChild ( p );
	while ( !cobj.isNull() )
	{
		oclass = md->objClass ( cobj );
		if ( oclass == md_actiongroup )
			loadActions ( lst, id, cobj, md );
		if ( oclass == md_action )
		{
			lst->append(md->attr(cobj,mda_name));
			id->append(md->attr(cobj,mda_id));
		}
		cobj = md->nextSibling ( cobj );
	}
}
