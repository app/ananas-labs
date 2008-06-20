/****************************************************************************
** $Id: ecatalogue.ui.h,v 1.7 2004/07/01 11:30:55 pashik Exp $
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
#include "acfg.h"

void eCatalogue::init()
{
/*    
	int oc, i, f, idx=0;
	char *id, *name, *ot;
	cfg_objptr o;
	char otype[100];
	QString named;

	otypes.clear();
	eType->clear();
	otypes.append("D");
	eType->insertItem(trUtf8("Дата"), idx++);
	otypes.append("T");
	eType->insertItem(trUtf8("Время"), idx++);
	otypes.append("N %d %d");
	eType->insertItem(trUtf8("Число"), idx++);
	otypes.append("C %d");
	eType->insertItem(trUtf8("Строка"), idx++);

	oc=cfgobj_count(NULL, NULL);
	for (i=1;i<=oc;i++) {
		id=cfgobj_idn(NULL, NULL, i, &o);
		ot=(char *)o->name;
		name=cfgobj_attr(o, "name");
		named="";
		f=0;
		if (strcmp((char *)ot, aot_doc)==0) {
			named=trUtf8("Документ.");
			f=1;
		}
		if (strcmp((char *)ot, aot_cat)==0) {
			named=trUtf8("Справочник.");
			f=1;
		}
		if (f) {
			named=named+trUtf8(name);
			sprintf(otype, "O %s", id);
			otypes.append(otype);
			eType->insertItem(named, idx++);
		}
	}
*/	
}



/*void eCatalogue::setData( aCatalogue *f, QWidget *mw )
{
	aCfg *md = 0;
	if ( !f ) return;
//	printf("name = '%s'\n", (const char *) mw->name() );
	if (mw->name() == QString("ananas-designer_mainwindow") ) {
//		printf("running under ananas designer\n");
		CfgForm *cf = ( ( MainForm *) mw )->cfgForm();
		if ( cf ) {
			md = &cf->cfg;
//			QString ts = f->getFieldType();
//			char t=' ';
			int w=0, d=0, idx=0;
			unsigned int i;
			long oid , id;

			id = f->getId();

			otypes.clear();
			eType->clear();

			QStringList tlist = md->types( md_catalogue );
			otypes.clear();
			eType->clear();
			for ( QStringList::Iterator it = tlist.begin(); it != tlist.end(); ++it ) {
				otypes.append( (*it).section( "\t", 0, 0 ) );
				eType->insertItem( (*it).section("\t", 1, 1 ), idx++ );
			}
			for ( i = 0 ; i < otypes.count(); i++ ) {
				oid = 0;
				if( otypes[i][0] == 'O' ) {
					sscanf( (const char *)otypes[ i ], "O %d", &oid );
					if ( oid == id ) {
						eType->setCurrentItem( i );
						break;
					}
				}
			}
		} else reject();
	}

}
*/

void 
eCatalogue::setData( QWidget *o, aCfg *md )
{
//    const QObject *o = sender();
    if ( o ) {
	if ( o->className() != QString("wCatalogue") || !md ) {
	    reject();
	    return;
	} 
    }
    else {
	reject();
	return;
    }
    wCatalogue *f = ( wCatalogue*) o;
    int w=0, d=0, idx=0;
    unsigned int i;
    long oid , id;
    
    id = f->getId();
        
    QStringList tlist = md->types( md_catalogue );
    otypes.clear();
    eType->clear();
    for ( QStringList::Iterator it = tlist.begin(); it != tlist.end(); ++it ) {
	otypes.append( (*it).section( "\t", 0, 0 ) );
	eType->insertItem( (*it).section("\t", 1, 1 ), idx++ );
    }
    for ( i = 0 ; i < otypes.count(); i++ ) {
	oid = 0;
	if( otypes[i][0] == 'O' ) {
	    sscanf( (const char *)otypes[ i ], "O %d", &oid );
	    if ( oid == id ) {
		eType->setCurrentItem( i );
		break;
	    }
	}
    }
}


void eCatalogue::getData( QWidget * o )
{
    
/*	int idx=eType->currentItem();
	long oid = 0;

	if (f) {
		if( otypes[idx][0] == 'O' ) {
			sscanf( (const char *)otypes[ idx ], "O %d", &oid );
			f->setId( oid );
		}
	}
*/
//    const QObject *o = sender();
    if ( !o ) return;
    if ( o->className() != QString("wCatalogue") ) return;
    wCatalogue *f = ( wCatalogue*) o;
    
    int idx=eType->currentItem();
    long oid = 0;
    
    if (f) {
	if( otypes[idx][0] == 'O' ) {
	    sscanf( (const char *)otypes[ idx ], "O %d", &oid );
	    f->setId( oid );
	}
    }
    
}

