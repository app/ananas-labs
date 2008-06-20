/****************************************************************************
** $Id: etable.ui.h,v 1.4 2004/07/01 11:30:55 pashik Exp $
**
** Code file of the select files plugin of Ananas
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
#include "ananas.h"
#include "wtable.h"

void eTable::init()
{
/*    
	int oc, i, f, idx=0;
	char *id, *name, *ot;
	cfg_objptr o;
	char otype[100];
	QString named;

	CHECK_POINT
	r = tablerow_new(0);

	otypes.clear();
	eType->clear();
	otypes.append("U");
	eType->insertItem(trUtf8("Текстовая метка"), idx++);
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
	CHECK_POINT
*/	
}


void 
eTable::destroy()
{
//	tablerow_free( r );
}



void eTable::insertColumn(const char *Header, const char *Name,
int idxt, int cw, int tw, int td)
{
/*    
	tablefield *f;
	char s[30];

	sprintf(s, "%s %i %i", (const char *)otypes[idxt], tw, td);

	f = tablefield_newsys(Name, s, "");
	tablefield_setheader(f, Header);
	f->sizex = cw;
	f->flen = tw;
	f->decimals = td;
	f->ftypeindex = idxt;
	tablerow_insertcolumn(r, f, -1);

//	blockSignals( true );
	ListCol->insertItem(trUtf8(Header));
//	eColHeader->setText( trUtf8(Header));
//	eColName->setText(trUtf8(Name));
//	eColWidth->setValue(cw);
//	eColTWidth->setValue(tw);
//	eColTDec->setValue(td);
//	blockSignals( false );
	if (ListCol->count()) ListCol->setCurrentItem(ListCol->count()-1);
*/	
}



void eTable::ColumnAdd()
{
//	insertColumn("Новый", "Новый", 0, 0, 0, 0);
}


void eTable::ColumnDel()
{
/*    
	int idx;
	idx = ListCol->currentItem();
	if (ListCol->count() && idx != -1) {
		tablerow_removecolumn( r, idx );
		ListCol->removeItem(idx);
	}
*/	
}


void eTable::ColumnL()
{

}


void eTable::ColumnR()
{

}


void eTable::ColumnSel(int col)
{
/*    
	tablefield *f;

	if (col >= 0 && col < tablerow_columns( r )) {
		f = tablerow_column( r, col );
		blockSignals( true );
		eColHeader->setText(trUtf8(tablefield_header( f )));
		eColWidth->setValue(f->sizex);
		eType->setCurrentItem(f->ftypeindex);
		eColName->setText(trUtf8(f->name));
		eColTWidth->setValue(f->flen);
		eColTDec->setValue(f->decimals);
		blockSignals( false );
	}
*/	
}


void eTable::ColumnUpd()
{
/*    
	tablefield *f;

	if (signalsBlocked()) return;
	int idx = ListCol->currentItem();

	if ( idx >= 0 && idx < tablerow_columns( r )) {
		f = tablerow_column( r, idx );
		if (f->name) free(f->name);
		f->name=strdup((const char *) eColName->text().utf8());
		tablefield_setheader( f, (const char *) eColHeader->text().utf8());
		f->sizex = eColWidth->value();
		f->flen = eColTWidth->value();
		f->decimals = eColTDec->value();
		f->ftypeindex = eType->currentItem();

		printf("set w=%i l=%i d=%i ti=%i\n", f->sizex, f->flen,
		f->decimals, f->ftypeindex);
		ListCol->blockSignals( TRUE );
		ListCol->changeItem(eColHeader->text(), idx);
		ListCol->blockSignals( FALSE );
	}
	CHECK_POINT
*/	
}


void eTable::setData( QWidget *o, aCfg *md )
{
    
	QStringList sl;	
	unsigned int i;
	QString ft,h,n;
	int w=0, l=0, d=0, idxt=0;
	char st[20];

	wTable *t = (wTable *) o;
	eTabName->setText(t->getName());
/*
	if (!t->getDefineCols().isEmpty()) {
		sl = QStringList::split("\n",t->getDefineCols());
		for (i = 0; i < sl.count(); i++) {
			sscanf((const char *)sl[i].section("|",3,3),"%s %d %d", st, &l, &d);
			if (st[0]=='O') ft.sprintf("O %d",l);
			else ft=st;
			w = sl[i].section("|",2,2).toInt();
			h = sl[i].section("|",5,5);
			n = sl[i].section("|",4,4);
			for (idxt = otypes.count()-1; idxt>0; idxt--) {
				if (ft[0]=='O' && otypes[idxt]==ft) break;
				else if (otypes[idxt][0]==ft[0]) break;
			}
			printf("set data %i = %s %s %i %i %i\n", i, 
			(const char *)h, (const char *)n, idxt, w, l);
			insertColumn(h,n,idxt,w,l,d);
		}	
	}
*/	
}


void eTable::getData( QWidget *o )
{
	wTable *t = (wTable *) o;
/*    
	int i;
	QStringList sl;
	QString cdef, ft, s;
	tablefield *f;

	t->vTable->setNumCols(ListCol->count());
	for (i=0;i<tablerow_columns( r ); i++) {
		f = tablerow_column( r, i );
		ft.sprintf(otypes[f->ftypeindex],f->flen,f->decimals);
		cdef.sprintf("%i|%i|%i|%s|%s|%s",i,0, f->sizex,
		(const char *) ft, f->name,
		tablefield_header( f ));
		s = s + cdef +"\n";
	}
//	t->vTable->setColumnLabels(sl);
	t->setName(eTabName->text());
	CHECK_POINT
	printf("getData defs = %s\n",(const char *)s.utf8());
	t->setDefineCols(s);
*/	
	t->setName(eTabName->text());
}


void eTable::ColumnTextUpd( const QString &s )
{
/*    
	int idx;
	idx = ListCol->currentItem();
	if (idx == -1) return;
	ListCol->blockSignals( TRUE );
	ListCol->changeItem(s, ListCol->currentItem());
	ListCol->blockSignals( FALSE );
	CHECK_POINT
*/	
}


