/****************************************************************************
** $Id: edbfield.ui.h,v 1.16 2004/07/06 11:21:30 cibfx Exp $
**
** Code file of the edit database field plugin of Ananas
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
#include "acfg.h"
#include "wdbfield.h"

void eDBField::init()
{
	eName->clear();
	onames.clear();
	oids.clear();
}



void eDBField::setData( QWidget *o, aCfg *md )
{
//    const QObject *o = sender();
    if ( o ) {
	if ( o->className() != QString("wDBField") || !md ) {
	    reject();
	    return;
	}
    }
    else {
	reject();
	return;
    }
    int w=0, d=0, idx=0;
    unsigned int i;
    long oid, widgetId, fieldId;
    QString pn;
    aWidget *widget;
    wDBField *field = (wDBField*)o;
    QWidget *pWidget = field->parentWidget();

    while ( pWidget ) {
	pn = "";
	pn = pWidget->className();
	if ( pn == QString("wCatalogue") || pn == QString("wDocument") ) break;
	pWidget = pWidget->parentWidget();
    }
    if ( pn == QString("wCatalogue") ) widget = (wCatalogue*)pWidget; else
    if ( pn == QString("wDocument") ) widget = (wDocument*)pWidget; else
    return;

    widgetId = widget->getId();
    //fieldId = field->getId();
    if ( widgetId ) widget->setMDObject( md->find( widgetId ) );
    
//    printf( "parent widget id = %i\n", widgetId );
//    printf( "field id = %i\n", fieldId );
//    printf( "metadata id = %i\n", md->id( *widget->getMDObject() ) );

    QStringList tlist = md->types( md_field, widget->getMDObject() );
    otypes.clear();
    eType->clear();
    for ( QStringList::Iterator it = tlist.begin(); it != tlist.end(); ++it ) {
	otypes.append( (*it).section( "\t", 0, 0 ) );
	eName->insertItem( (*it).section("\t", 1, 1 ), idx++ );
    }
    for ( i = 0 ; i < otypes.count(); i++ ) {
	oid = 0;
	if( otypes[i][0] == 'O' ) {
	    sscanf( (const char *)otypes[ i ], "O %d", &oid );
	    if ( oid == fieldId ) {
		eName->setCurrentItem( i );
		break;
	    }
	}
    }
}


void eDBField::getData( QWidget *o )
{
//    const QObject *o = sender();
    if ( !o ) return;
    if ( o->className() != QString("wDBField") ) return;
    wDBField *f = ( wDBField*) o;
    
    int idx=eName->currentItem();
    long oid = 0;
    if (f) {
	if( otypes[idx][0] == 'O' ) {
	    sscanf( (const char *)otypes[ idx ], "O %d", &oid );
	   // f->setId( oid );
	}
    }
}


void eDBField::namechanged( const QString &s )
{
    int idx=eName->currentItem();
//	printf("new str=%s\n", (const char *) s.utf8());
    selotype=otypes[idx];
    seloid=oids[idx];
    eType->setText(onames[idx]);
}
