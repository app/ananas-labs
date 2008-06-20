/****************************************************************************
** $Id: deditcolumns.ui.h,v 1.16 2008/06/09 11:47:59 app Exp $
**
** Code file of the Edit Journal Columns window
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


void dEditColumns::setData( ananasListViewItem * o )
{
    item = o;
    md = o->md;
    obj = o->obj;
    aCfgItem  com_action, apix;
    QPixmap pix;


	usedFields = new ananasTreeView( gbFields,  md );
	QGridLayout *l = new QGridLayout( gbFields );
	l->addWidget( usedFields, 0, 0);
	availableFields = new ananasTreeView( frmFields,  md );
	l = new QGridLayout( frmFields );
	l->addWidget( availableFields, 0, 0);

	aCfgItem	cobj, fobj, dobj, pobj, tobj;

	uint n, fCount, tCount, addfields, addtables;
	long id;
	QString dName, fName;
	cobj = md->parent(md->parent(obj));
	setCaption( tr("Column:") + md->attr( cobj, mda_name ) + "." + md->attr( obj, mda_name ));
	eName->setText( md->attr( obj, mda_name ) );
	ananasListViewItem *fitem, *ditem, *titem, *tparent, *docs;
	QStringList docsId = md->getJournalDocuments(cobj);
	docs = new ananasListViewItem( availableFields, availableFields->lastItem(), md, md->find(md->find(mdc_metadata),md_documents,0), QObject::tr("Documents") );
	docs->setPixmap(0, rcIcon("doc_g.png"));
	docs->setOpen(true);
	n = docsId.count();
	for ( uint i = 0; i < n; i++ )
	{
		id = docsId[i].toInt();
		dobj = md->find(id);
		if ( dobj.isNull() )
			continue;
		ditem = new ananasListViewItem( docs, docs->getLastChild(), md, dobj );
		ditem->setPixmap(0, rcIcon("doc.png"));
		tobj = md->find(dobj,md_header,0);
		tparent = new ananasListViewItem( ditem, ditem->getLastChild(), md, tobj, QObject::tr("Header") );
		tparent->setPixmap(0, rcIcon("doc_h.png"));
		fCount = md->count(tobj,md_field);
		for ( uint k = 0; k < fCount; k++ )
		{
			fobj = md->find(tobj,md_field,k);
			if ( fobj.isNull())
					continue;
			fitem = new ananasListViewItem ( tparent, tparent->getLastChild(), md, fobj );
			fitem->setPixmap(0, rcIcon("field.png"));
		}
		pobj = md->find(ditem->obj, md_tables, 0);
		if ( !pobj.isNull() )
		{
			tparent = new ananasListViewItem( ditem, ditem->getLastChild(), md, pobj, QObject::tr("Tables") );
			tparent->setPixmap(0, rcIcon("table_g.png"));
			addtables = 0;
			tCount = md->count(pobj,md_table);
			for ( uint j = 0; j < tCount; j++ )
			{
				tobj = md->find ( pobj, md_table, j );
				if ( tobj.isNull() )
					continue;
				titem = new ananasListViewItem( tparent, tparent->getLastChild(), md, tobj );
				titem->setPixmap(0, rcIcon("table.png"));
				fCount = md->count(tobj,md_field);
				addfields = 0;
				for ( uint k = 0; k < fCount; k++ )
				{
					fobj = md->find(tobj,md_field,k);
					if ( fobj.isNull())
						continue;
					QString sum = md->attr(fobj,mda_sum);
					if ( sum != "1" )
						continue;
					addfields++;
					fitem = new ananasListViewItem ( titem, titem->getLastChild(), md, fobj );
					fitem->setPixmap(0, rcIcon("field.png"));
				}
				if ( !addfields )
					delete titem;
				else
					addtables++;
			}
			if ( !addtables )
				delete tparent;
		}
	}
	fieldsList.clear();
	n = md->count(obj,md_fieldid);
	for (uint i = 0; i < n; i++)
	{
		fobj = md->find( obj, md_fieldid, i );
		if ( fobj.isNull() )
			continue;
		id = md->text(fobj).toLong();
		aCfgItem testitem = md->find(id);
		if (testitem.isNull())
			md->remove( testitem );
		else
			addField( testitem );
	}
}


void dEditColumns::updateMD()
{
	aCfgItem field;
	item->setText( 0, eName->text().stripWhiteSpace() );
	md->setAttr(obj, mda_name, eName->text().stripWhiteSpace());
    do
	{
		field = md->findChild( obj, md_fieldid, 0 );
		if ( !field.isNull() )
			 md->remove( field );
    } while ( !field.isNull() );
    ananasListViewItem *aitem = (ananasListViewItem *)usedFields->firstChild();
	if (!aitem)
		return;
    while ( aitem )
	{
		field = md->insert( obj, md_fieldid, QString::null, -1 );
		md->setText( field, QString( "%1" ).arg( aitem->id ) );
		aitem = (ananasListViewItem *)aitem->nextSibling();
    }
}

void dEditColumns::destroy()
{
    updateMD();
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
}

void dEditColumns::init()
{
	statusBar()->hide();
}


void
dEditColumns::bAddAction_clicked()
{
    ananasListViewItem *cur = (ananasListViewItem *)availableFields->selectedItem();
	if (!cur)
		return;
	if ( md->objClass( cur->obj ) != md_field )
		return;
	eName->setText( md->attr( cur->obj, mda_name ) );
	addField( cur->obj );
}


void dEditColumns::bRemoveAction_clicked()
{
	ananasListViewItem *rmItem = (ananasListViewItem*)usedFields->selectedItem();
	if ( !rmItem )
		return;
	aCfgItem cobj = md->find(md->id(rmItem->obj));
	aCfgItem doc, parent = md->parent(cobj);
	if ( md->objClass (parent) == md_header )
		doc = md->parent(parent);
	else
		doc = md->parent(md->parent(parent));
	fieldsList.remove(md->attr(doc,mda_id));
	usedFields->removeItem( rmItem );
}


void dEditColumns::bMoveUp_clicked()
{
    QListViewItem *aitem, *after;

    aitem =  usedFields->selectedItem();
    if ( aitem )
	{
		after = aitem->itemAbove();
		if ( after )
			after->moveItem( aitem );
	}
}


void dEditColumns::bMoveDown_clicked()
{
	QListViewItem *aitem, *after;
	aitem = usedFields->selectedItem();
	if ( aitem )
	{
		after = aitem->itemBelow();
		if ( after )
			aitem->moveItem( after );
    }
}



void dEditColumns::addField( aCfgItem addItem )
{
	aCfgItem fparent, parent;
	fparent = md->parent(addItem);
	QString fName;
	if ( md->objClass( fparent ) == md_header )
	{
		fName = QObject::tr("header");
		parent = md->parent(fparent);
	}
	else
	{
		fName =  md->attr( fparent, mda_name );
		parent = md->parent(md->parent(fparent));
	}
	QString fId = md->attr( parent, mda_id );
	if ( fieldsList.findIndex(fId) != -1  )
		return;
	fName = md->attr(parent,mda_name)+"."+fName+"."+md->attr(addItem,mda_name);
	ananasListViewItem *aitem = new ananasListViewItem(usedFields, usedFields->lastItem(), md, addItem,fName );
	aitem->setPixmap(0, rcIcon("field.png"));
	aitem->setRenameEnabled(0,false);
	fieldsList.append(fId);
}


/**
 * \ru
 *	\brief Сдвигает окно редактирования свойств в левый верхний угол родительского окна.
 * 
 * 	Размеры перемещаемого окна остаются без изменений.
 * \_ru
 */
void
dEditColumns::moveToTopLeftCorner()
{
	this->parentWidget()->setGeometry( 0, 0, 
		this->parentWidget()->frameSize().width(),
		this->parentWidget()->frameSize().height());

}

