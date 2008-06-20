/****************************************************************************
** $Id: efield.ui.h,v 1.13 2007/04/19 07:30:49 gr Exp $
**
** Code file of the edit field plugin of Ananas
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
#include <stdlib.h>

void eField::init()
{
	

	
}



void eField::setData( QWidget *o, aCfg *cfg )
{
	md = cfg;
	if(!o) 
	{
		reject();
		return;
	} 
	if ( o->className() != QString("wField") || !md ) {
	    reject();
	    return;
	} 
    wField *f = ( wField*) o;
    QString ts = f->getFieldType();
//    printf(">>> fieldType = %s;\n", ts.ascii() );
    char t=' ';
    int w=0, d=0, oid, idx=0;
    unsigned int i;
    
//    eName->setText(f->getName());
    otypes.clear();
    eType->clear();
    
    QStringList tlist = md->types();
    otypes.clear();
    eType->clear();
    for ( QStringList::Iterator it = tlist.begin(); it != tlist.end(); ++it ) {
	otypes.append( (*it).section( "\t", 0, 0 ) );
	eType->insertItem( (*it).section("\t", 1, 1 ), idx++ );
    }
    if ( !ts.isEmpty() ) {
	sscanf( ts, "%c %d %d", &t, &w, &d );
    } else {
	t = 'N';
	w = 10;
    }
    if ( t=='O' ) {
	for( i = 0 ; i < otypes.count(); i++ ) {
	    if( otypes[i][0] == 'O' ) {
		sscanf( (const char *)otypes[ i ], "O %d", &oid );
		if ( oid == w ) {
		    eType->setCurrentItem( i );
		    break;
		}
	    }
	}
    } else {
	eWidth->setValue( w );
	eDec->setValue( d );
	if ( t == ' ' ) eType->setCurrentItem( 0 );
	if ( t == 'N' ) eType->setCurrentItem( 1 );
	if ( t == 'C' ) eType->setCurrentItem( 2 );
	if ( t == 'D' ) eType->setCurrentItem( 3 );
	if ( t == 'B' ) eType->setCurrentItem( 4 );
    }
    typeSelect( eType->currentItem() );
}


void eField::getData( QWidget *o )
{
//    const QObject *o = sender();
    if ( !o ) return;
    if ( o->className() != QString("wField") ) return;
    wField *f = ( wField*) o;
    wField::tEditorType type;	
    char ntype[40]="";
    int idx=eType->currentItem();
    
    if (f) {
	//f->setName(eName->text());
	sprintf(ntype, (const char *) otypes[idx], eWidth->value(), eDec->value());
	f->setFieldType(ntype);
	if(otypes[idx][0]==' ') type = wField::Unknown;
	if(otypes[idx][0]=='N') type = wField::Numberic;
	if(otypes[idx][0]=='C') type = wField::String;
	if(otypes[idx][0]=='D') type = wField::Date;
	if(otypes[idx][0]=='B') type = wField::Boolean;
	if(otypes[idx][0]=='O')
	{
		QString tmp = otypes[idx].section(' ',1,1);
		long tid = atol(tmp);
		aCfgItem item = md->find(tid);
		if(!item.isNull())
		{
			//gets object class
			tmp = md->objClass(item);
			if(tmp == md_catalogue)
				type = wField::Catalogue;
			if(tmp == md_document)
				type = wField::Document;
		}
	}
	f->setEditorType(type);
    }
}

void eField::typechanged(const QString &s )
{
}

void eField::typeSelect( int idx )
{
    bool w = false, d = false;
    if ( otypes[ idx ][0] == 'N' ){
	w = true;
	d = true;

    } else
	if ( otypes[ idx ][0] == 'C' ){
	w = true;

    }
    eWidth->setShown( w );
    tWidth->setShown( w );
    eDec->setShown( d );
    tDec->setShown( d );
}
