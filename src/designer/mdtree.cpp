/****************************************************************************
** $Id: mdtree.cpp,v 1.54 2008/06/09 11:47:59 app Exp $
**
** Code file of the Metadata Tree of Ananas Designer applications
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

#include <qlistview.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qstatusbar.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qvaluelist.h>
#include <qimage.h>
#include <qbitmap.h>
#include <qdragobject.h>
#include <qheader.h>
#include <qfont.h>
#include <qcursor.h>
#include <qlayout.h>
#include "qstring.h"
#include "qapplication.h"

#include "adatabase.h"
#include "mainform.h"
#include "deditfield.h"
#include "deditcfg.h"
#include "deditdoc.h"
#include "deditreport.h"
#include "deditdialog.h"
#include "deditcat.h"
#include "deditireg.h"
#include "deditareg.h"
#include "deditjournal.h"
#include "deditwebform.h"
#include "deditcolumns.h"
#include "awindowslist.h"
#include "binreloc.h"
//#include "acfg.h"
#include "acfgrc.h"
#include "mdtree.h"
#include "alog.h"

extern MainForm *mainform;
extern QPixmap rcIcon(const char *name);
//extern void set_Icon(QListViewItem *item, const char *name);



aListViewItem::aListViewItem(ananasListViewItem *parent, ananasListViewItem *after, aCfg *cfgmd,  aCfgItem cfgobj, const QString &name )
: ananasListViewItem( parent, after, cfgmd, cfgobj, name )
{
	loadTree();
}



aListViewItem::aListViewItem(QListView *parent, aCfg *cfgmd,  aCfgItem cfgobj, const QString &name )
: ananasListViewItem( parent, cfgmd, cfgobj, name )
{
	loadTree();
}


aListViewItem::~aListViewItem()
{

}


QString
aListViewItem::text( int column ) const
{
	return QListViewItem::text( column );
//	if ( obj.isNull() ) return QObject::tr("Unknown object context");
	if ( !id ) return QListViewItem::text( column );
	switch ( column ) {
	case 0: return md->attr( obj, mda_name );
	default:
		return "";
	}
}

int
aListViewItem::compare( QListViewItem *i, int col, bool accending ) const
{
	int id1 = 0, id2 = 0;
	aListViewItem *ai = (aListViewItem *) i;
	id1 = md->order( obj );
	id2 = ai->md->order( ai->obj );
	if ( md == ai->md && md->parent( obj ) == ai->md->parent( ai->obj ) && col ==0 && accending ) {
		if ( id1 < id2 ) return -1;
		if ( id1 == id2 ) return 0;
		return 1;
	}
	return 1;
}


void
aListViewItem::setup()
{
	QListViewItem::setup();
}


/*!
Update metadata tree for the object context.
*/
void
aListViewItem::update()
{

}


void
aListViewItem::loadTree()
{
	aListViewItem *item, *nextitem;
	QString oclass, ldclass="";
	int i, n;
	aCfgItem cobj;

	// clear tree
       item = (aListViewItem *) firstChild();
        while( item ) {
		nextitem = (aListViewItem *) item->nextSibling();
		delete item;
		item = nextitem;
        }
	if ( !md ) return;
	if (id) setRenameEnabled(0, true);
	oclass = md->objClass( obj );
	if ( oclass == md_metadata ){
		cobj = md->find ( mdc_metadata );
		setPixmap(0, rcIcon("project.png"));
		setOpen(true);
		cobj = md->find ( obj, md_catalogues, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( obj, md_catalogues, QString::null, -1 );
		}
		new aListViewItem( this, getLastChild(), md, cobj, QObject::tr("Catalogues") );
		cobj = md->find ( obj, md_documents, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( obj, md_documents, QString::null, -1 );
		}
		new aListViewItem( this, getLastChild(), md, cobj, QObject::tr("Documents") );
		cobj = md->find ( obj, md_reports, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( obj, md_reports, QString::null, -1 );
		}
		new aListViewItem( this, getLastChild(), md, cobj, QObject::tr("Reports") );
		cobj = md->find ( obj, md_journals, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( obj, md_journals, QString::null, -1 );
		}
		new aListViewItem( this, getLastChild(), md, cobj, QObject::tr("Journals") );
		cobj = md->find ( obj, md_registers, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( obj, md_registers, QString::null, -1 );
		}
		cobj = md->find ( obj, md_iregisters, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( md->find (obj, md_registers, 0 ), md_iregisters, QString::null, -1 );
		}
		new aListViewItem( this, getLastChild(), md, cobj, QObject::tr("Information registers") );
		cobj = md->find ( obj, md_aregisters, 0 );
		if ( cobj.isNull() )
		{
			cobj = md->insert( md->find (obj, md_registers, 0 ), md_aregisters, QString::null, -1 );
		}
		new aListViewItem( this, getLastChild(), md, cobj, QObject::tr("Accumulation registers") );
	}
	if ( oclass == md_catalogues ){
		setPixmap(0, rcIcon("cat_g.png") );
		ldclass = md_catalogue;
	}
	if ( oclass == md_documents ){
		setPixmap(0, rcIcon("doc_g.png"));
		ldclass = md_document;
	}
	if ( oclass == md_reports ){
		setPixmap(0, rcIcon("report_g.png"));
		ldclass = md_report;
	}
	if ( oclass == md_journals ){
		setPixmap(0, rcIcon("journ_g.png"));
		ldclass = md_journal;
	}
	if ( oclass == md_iregisters ){
		setPixmap(0, rcIcon("reg_g.png"));
		ldclass = md_iregister;
	}
	if ( oclass == md_aregisters ){
		setPixmap(0, rcIcon("regs_g.png"));
		ldclass = md_aregister;
	}
	if ( !ldclass.isEmpty() ) {
//		printf("%s\n",(const char *) md->toString().local8Bit() );
		n = md->count( obj, ldclass );
//		printf(" objclass=%s ldclass = %s count = %d\n", (const char *) oclass, (const char *) ldclass, n);
		for ( i = 0; i<n; i++ ) {
			cobj = md->find( obj, ldclass, i );
			if ( !cobj.isNull() ) {
//				printf("%d ok\n", i);
//				new aListViewItem( this, md, md->find( obj, ldclass, i ), QString::null );
				new aListViewItem( this, getLastChild(), md,  cobj, QString::null );
			}
		}
	}

	if ( oclass == md_tables ){
		setPixmap(0, rcIcon("table_g.png"));
		return;
	}
	if ( oclass == md_forms ){
		setPixmap(0, rcIcon("form_g.png"));
		return;
	}
	if ( oclass == md_form ){
		setPixmap(0, rcIcon("form.png"));
		return;
	}
	if ( oclass == md_webforms ){
		setPixmap(0, rcIcon("webform_g.png"));
		return;
	}
	if ( oclass == md_webform ){
		setPixmap(0, rcIcon("webform.png"));
		return;
	}
	if ( oclass == md_table )
	{
		setPixmap(0, rcIcon("table.png"));
		return;
	}

// elements
	if ( oclass == md_catalogue ){
		setPixmap(0, rcIcon("cat.png"));
		loadCatalogue ();
		return;
	}
	if ( oclass == md_document ){
		setPixmap(0, rcIcon("doc.png"));
		loadDocument ();
		return;
	}
	if ( oclass == md_aregister ){
		setPixmap(0, rcIcon("regs.png"));
		loadARegister ();
		return;
	}
	if ( oclass == md_iregister ){
		setPixmap(0, rcIcon("reg.png"));
		loadIRegister ();
		return;
	}
	if ( oclass == md_journal ){
		setPixmap(0, rcIcon("journ.png"));
		loadJournal ();
		return;
	}
	if ( oclass == md_report ){
		setPixmap(0, rcIcon("report.png"));
		loadReport ();
		return;
	}
	if ( oclass == md_field ){
		setPixmap(0, rcIcon("field.png"));
		return;
	}
	if ( oclass == md_header )
	{
		setPixmap(0, rcIcon("doc_h.png"));
		return;
	}
	if ( oclass == md_element)
	{
		setPixmap(0, rcIcon("element.png"));
		return;
	}
    if( oclass == md_columns )
	{
		setPixmap(0, rcIcon("columns.png"));
		return;
	}
	if ( oclass == md_resources )
	{
		setPixmap(0, rcIcon("resourses.png"));
		return;
	}
	if ( oclass == md_dimensions )
	{
		setPixmap(0, rcIcon("dimensions.png"));
		return;
	}
	if ( oclass == md_information )
	{
		setPixmap(0, rcIcon("information.png"));
		return;
	}
	if (oclass == md_group)
	{
		setPixmap(0, rcIcon("group.png"));
		return;
	}
}

void
aListViewItem::loadDocument ()
{
	int		n, i;
	aCfgItem	cobj;
	aListViewItem	*tparent, *fparent;

	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_header, 0), QObject::tr("Header") );
	loadFields ( fparent );

	tparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_tables, 0), QObject::tr("Tables") );
	n = md->count ( obj, md_table );
	for ( i = 0; i < n; i++ )
	{
		cobj = md->find(  obj, md_table, i  );
		if ( !cobj.isNull() )
		{
			fparent = new aListViewItem( tparent, tparent->getLastChild(), md, cobj, QString::null );
			loadFields ( fparent );
		}
	}
	loadForms ( this );
	loadWebForms ( this );
}

/*void
aListViewItem::loadTable ()
{
	int		n, i;
	QString		ldclass;
	aCfgItem	cobj;

}*/

void
aListViewItem::loadFields (aListViewItem *parent)
{
	int		n, i;
	aCfgItem	cobj;

	n = md->count ( parent->obj, md_field );
	for ( i = 0; i < n; i++ )
	{
		cobj = md->find(  parent->obj, md_field, i  );
		if ( !cobj.isNull() )
		{
			new aListViewItem( parent, parent->getLastChild(), md, cobj, QString::null );
		}
	}
}

void
aListViewItem::loadForms (aListViewItem *parent)
{
	int		n, i;
	aCfgItem	cobj, gobj;
	aListViewItem	*fparent;

	gobj = md->find(obj, md_forms, 0);
	if ( gobj.isNull() ) gobj = md->insert( obj, md_forms, QString::null, -1 );
	fparent = new aListViewItem( parent, getLastChild(), md, gobj, QObject::tr("Forms") );
	n = md->count ( fparent->obj, md_form );
	for ( i = 0; i < n; i++ )
	{
		cobj = md->find(  fparent->obj, md_form, i  );
		if ( !cobj.isNull() )
		{
			new aListViewItem( fparent, getLastChild(), md, cobj, QString::null );
		}
	}
}

void
aListViewItem::loadWebForms (aListViewItem *parent)
{
	int		n, i;
	aCfgItem	cobj, gobj;
	aListViewItem	*fparent;

	gobj = md->find(obj, md_webforms, 0);
	if ( gobj.isNull() ) gobj = md->insert( obj, md_webforms, QString::null, -1 );
	fparent = new aListViewItem( parent, getLastChild(), md, md->find(obj, md_webforms, 0), QObject::tr("Web forms") );
	n = md->count ( fparent->obj, md_webform );
	for ( i = 0; i < n; i++ )
	{
		cobj = md->find(  fparent->obj, md_webform, i  );
		if ( !cobj.isNull() )
		{
			new aListViewItem( fparent, getLastChild(), md, cobj, QString::null );
		}
	}
}

void
aListViewItem::loadJournal ()
{
	aListViewItem	*fparent;

	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_columns, 0), QObject::tr("Columns") );
	loadColumns( fparent );
	loadForms ( this );
	loadWebForms ( this );
}

void
aListViewItem::loadIRegister ()
{
	aListViewItem	*fparent;

	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_resources, 0), QObject::tr("Resources") );
	loadFields ( fparent );
	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_dimensions, 0), QObject::tr("Dimensions") );
	loadFields ( fparent );
	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_information, 0), QObject::tr("Information") );
	loadFields ( fparent );
}

void
aListViewItem::loadARegister ()
{
	aListViewItem	*fparent;

	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_resources, 0), QObject::tr("Resources") );
	loadFields ( fparent );
	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_dimensions, 0), QObject::tr("Dimensions") );
	loadFields ( fparent );
	fparent = new aListViewItem( this, getLastChild(), md, md->find(obj, md_information, 0), QObject::tr("Information") );
	loadFields ( fparent );
}

void
aListViewItem::loadCatalogue ()
{
	aListViewItem	*fparent;
	aCfgItem i;

	i = md->find(obj, md_element, 0);
	if ( i.isNull() ) i = md->insert( obj, md_element, QString::null, -1 );
	fparent = new aListViewItem( this, getLastChild(), md, i, QObject::tr("Element") );
	loadFields ( fparent );
	i = md->find(obj, md_group, 0);
	if ( i.isNull() ) i = md->insert( obj, md_group, QString::null, -1 );
	fparent = new aListViewItem( this, getLastChild(), md, i, QObject::tr("Group") );
	loadFields ( fparent );
	loadForms ( this );
	loadWebForms ( this );
}

void aListViewItem::loadReport ()
{
	loadForms ( this );
	loadWebForms ( this );
}

void
aListViewItem::loadColumns ( aListViewItem *parent )
{
	int i,n;
	aCfgItem	cobj;

	n = md->count ( parent->obj, md_column );
	for ( i =  0; i < n; i++)
	{
		cobj = md->find(  parent->obj, md_column, i  );
		if ( !cobj.isNull() )
		{
			new aListViewItem( parent, getLastChild(), md, cobj, QString::null );
		}
	}
}


/*
*edit selected object
*/

void
aListViewItem::edit()
{
    QWorkspace *ws = mainform->ws;
    aWindowsList *wl = mainform->wl;
    QString oclass = md->objClass( obj );
    int objid = md->id( obj );
    if ( wl->find( objid ) ) {
	wl->get( objid )->setFocus();
	return;
    }

	if ( oclass == md_metadata )
	{
	    dEditCfg *e = new dEditCfg( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	}
//	if ( !md || !id ) return;
	if ( oclass == md_document)
	{
	    dEditDoc *e = new dEditDoc( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
    	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_iregister)
	{
	    dEditIReg *e = new dEditIReg( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_aregister)
	{
	    dEditAReg *e = new dEditAReg( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_catalogue)
	{
	    dEditCat *e = new dEditCat( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_field )
	{
	    dEditField *e = new dEditField( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
	    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_report )
	{
	    dEditReport *e = new dEditReport( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
     e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_journal )
	{
	    dEditJournal *e = new dEditJournal( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
     e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId, e->name());
	    return;
	};
	if ( oclass == md_form )
	{
	    dEditDialog *e = new dEditDialog( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    e->setData( this );
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->show();
     e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_webform )
	{
	    dEditWebForm *e = new dEditWebForm( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
     e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	};
	if ( oclass == md_column )
	{
	    dEditColumns *e = new dEditColumns( ws, 0, WDestructiveClose );
	    wl->insert( objid, e );
	    editor = e;
	    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	    e->setData( this );
	    e->show();
     e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
	    mainform->addTab(++mainform->lastTabId,e->name());
	    return;
	}
}

void aListViewItem::newObject()
{
	QString oclass = md->objClass( obj );
//	printf("oclass = %s\n",( const char *) oclass );
	if ( 	oclass == md_header || oclass == md_table ||
		oclass == md_element || oclass == md_group ||
		oclass == md_resources || oclass == md_dimensions || oclass == md_information ||
		oclass == md_columns )
			newField();
	if ( oclass == md_documents ) newDocument();
	if ( oclass == md_catalogues ) newCatalogue();
	if ( oclass == md_journals ) newJournal();
	if ( oclass == md_iregisters ) newIRegister();
	if ( oclass == md_aregisters ) newARegister();
	if ( oclass == md_reports ) newReport();
	if ( oclass == md_forms ) newForm();
	if ( oclass == md_webforms ) newWebForm();
	if ( oclass == md_tables ) newTable();
	if ( oclass == md_columns ) newColumn();
}

void aListViewItem::saveItem()
{

	//md->saveOneObject()
	QString oclass = md->objClass( obj );
	if ( 	oclass == md_field ||
		oclass == md_document ||
		oclass == md_catalogue ||
		oclass == md_journal ||
		oclass == md_iregister ||
		oclass == md_aregister ||
		oclass == md_report ||
		oclass == md_webform ||
		oclass == md_form ||
		oclass == md_table)
	{

		QString fname;
		QFileDialog fd( QString::null,
  			QObject::tr("any files (*)"),
			0, 0, TRUE );
		fd.setMode(QFileDialog::AnyFile);
//		fd.addFilter(tr(" (*.bsa)"));
		fd.setSelection( oclass + md->attr(obj,mda_id) );
		if ( fd.exec() == QDialog::Accepted )
		{
			fname = QDir::convertSeparators(fd.selectedFile());
			md->saveOneObject(obj,fname);
		}
	}
}

void aListViewItem::loadItem()
{

	QString oclass = md->objClass( obj );

	if ( 	oclass == md_header ||
		oclass == md_table ||
		oclass == md_element ||
		oclass == md_group ||
		oclass == md_resources ||
		oclass == md_dimensions ||
		oclass == md_information ||
		oclass == md_columns ||
		oclass == md_documents ||
		oclass == md_catalogues ||
		oclass == md_journals ||
		oclass == md_iregisters ||
		oclass == md_aregisters ||
		oclass == md_reports ||
		oclass == md_forms ||
		oclass == md_webforms ||
		oclass == md_tables ||
		oclass == md_columns )
	{

		QString fname;
		QFileDialog fd( QString::null,
  			QObject::tr("any files (*)"),
			0, 0, TRUE );
		fd.setMode(QFileDialog::ExistingFiles);
		aCfgItem loadObj;
//		fd.addFilter(tr(" (*.bsa)"));
//		fd.setSelection( QDir::convertSeparators(eCfgName->text()));
		if ( fd.exec() == QDialog::Accepted )
		{
			fname = QDir::convertSeparators(fd.selectedFile());
			// load object from file
			// aCfgItem loadObj = c.loadOneObject("catalogue_copy.xml");
			// change name
			// c.setAttr(loadObj, mda_name, "CATALOGUE1 COPY!!!");
			// append to cfg
			// c.importCfgItem( c.find(c.find(0), md_catalogues) , loadObj);
			//
			loadObj = md->loadOneObject(fname);
			if(loadObj.isNull())
			{
				return;
			}
			else
			{
				md->setAttr(loadObj, mda_name, QString("%1_copy").arg(md->attr(loadObj, mda_name)));
				QString loclass = md->objClass(loadObj);
				if ( loclass==md_field	&&
						(oclass == md_header || oclass == md_table ||
						oclass == md_element || oclass == md_group ||
						oclass == md_resources || oclass == md_dimensions ||
						oclass == md_information || oclass == md_columns ))
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
//					newitem->setOpen( TRUE );
				}
				if ( loclass==md_document &&  oclass == md_documents )
				{
					//md->importCfgItem( obj, loadObj );
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_catalogue && oclass == md_catalogues )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_journal && oclass == md_journals )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_iregister && oclass == md_iregisters )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_aregister &&  oclass == md_aregisters )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_report && oclass == md_reports )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_form &&  oclass == md_forms )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_webform && oclass == md_webforms )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
				if ( loclass==md_table &&  oclass == md_tables )
				{
					aCfgItem newobj = md->importCfgItem( obj, loadObj );
					aListViewItem *newitem = new aListViewItem( this, getLastChild(), md, newobj );
				}
			}
		}
	}
}


void
aListViewItem::newField()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	QString oclass = md->objClass( obj );
	if (oclass == md_header || oclass == md_table ||
		oclass == md_element || oclass == md_group ||
		oclass == md_resources || oclass == md_dimensions || oclass == md_information)
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insert( obj, md_field, QObject::tr("New field") );
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->edit();
	}
}


void
aListViewItem::newDocument()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_documents ) {
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insertDocument(  QObject::tr("New document") );
/*		md->insert( newobj, md_header, QString::null, -1 );
		md->insert( newobj, md_tables, QString::null, -1 );
		md->insert( newobj, md_forms, QString::null, -1 );
		md->insert( newobj, md_webforms, QString::null, -1 );
*/		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}


void
aListViewItem::newCatalogue()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_catalogues ) {
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insertCatalogue( QObject::tr("New catalogue") );
/*		md->insert( newobj, md_element, QString::null, -1 );
		md->insert( newobj, md_group, QString::null, -1 );
		md->insert( newobj, md_forms, QString::null, -1 );
		md->insert( newobj, md_webforms, QString::null, -1 );*/
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newJournal()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_journals ) {
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insertJournal( QObject::tr("New journal") );
/*		md->insert( newobj, md_columns, QString::null, -1 );
		md->insert( newobj, md_forms, QString::null, -1 );
		md->insert( newobj, md_webforms, QString::null, -1 );*/
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newIRegister()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_iregisters )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insertIRegister(  QObject::tr("New information register") );
/*		md->insert( newobj, md_resources, QString::null, -1 );
		md->insert( newobj, md_dimensions, QString::null, -1 );
		md->insert( newobj, md_information, QString::null, -1 );*/
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newARegister()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_aregisters )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insertARegister( QObject::tr("New accumulation register") );
/*		md->insert( newobj, md_resources, QString::null, -1 );
		md->insert( newobj, md_dimensions, QString::null, -1 );
		md->insert( newobj, md_information, QString::null, -1 );*/
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newReport()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_reports )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insert( obj, md_report, QObject::tr("New report") );
		md->insert( newobj, md_forms, QString::null, -1 );
		md->insert( newobj, md_webforms, QString::null, -1 );
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newForm()
{
	aListViewItem *newitem;
	aCfgItem newobj;
	QString module, tpl_name = "sourcecode.tpl", tpldir;
#ifdef Q_OS_WIN32
	tpldir = qApp->applicationDirPath()+"/templates/";
#else
	BrInitError error;
	if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED)
	{
		aLog::print(aLog::MT_INFO, QObject::tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
		aLog::print(aLog::MT_INFO, QObject::tr("Will fallback to hardcoded default path.\n"));
	}
	aLog::print(aLog::MT_DEBUG, QObject::tr("dEditDoc::EditForm BinReloc path to data dir is %1.\n").arg( br_find_data_dir("/usr/share") ));
	tpldir = QString( br_find_data_dir("/usr/share") ) + "/ananas/templates/";
#endif
	if ( md->objClass( obj ) == md_forms )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insert( obj, md_form, QObject::tr("New form") );
		QFile fi( tpldir+tpl_name );
		if ( fi.open( IO_ReadOnly ))
		{
			aLog::print(aLog::MT_DEBUG,QObject::tr("dEditDoc open file %1 for read from templates directory %2").arg(tpl_name).arg(tpldir));
			module = QString::QString(fi.readAll());
			fi.close();
			md->setSText( newobj, md_sourcecode, module );
		}
		else
		{
			aLog::print(aLog::MT_ERROR,QObject::tr("dEditDoc file %1 not exists in templates directory %2").arg(tpl_name).arg(tpldir));
		}
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newWebForm()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_webforms )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insert( obj, md_webform, QObject::tr("New web form") );
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newTable()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_tables )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insert( obj, md_table, QObject::tr("New Table") );
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
//		newitem->setSelected( TRUE );
		newitem->setOpen( TRUE );
		newitem->edit();
	}
}

void
aListViewItem::newColumn()
{
	aListViewItem *newitem;
	aCfgItem newobj;

	if ( md->objClass( obj ) == md_columns )
	{
		setSelected( FALSE );
		setOpen( TRUE );
		newobj = md->insert( obj, md_column, QObject::tr("New Column") );
		newitem = new aListViewItem( this, getLastChild(), md, newobj );
		newitem->edit();
	}
}


/*!
 * \en
 *  	\brief Search on a mdtree
 *
 * 	\param mdItem - The index on a mdtree
 * 	\param parentObjClass - Class of an parent element in a mdtree
 * 	\param parentObjName - Heading of an element in a mdtree
 * 	\param objClass - Class of an element in a mdtree
 * 	\param objName - Heading of an element in a mdtree
 * \_en
 * \ru
 * 	\brief Поиск по дереву метаданных.
 *
 * 	Указываем тег-класс узла, тег-класс его родительского узла и строковые значения
 * 	для узла и его родителя.
 * 	Например: запись findItemInMD(item, "document", "Счет", "field", "Поле" ); означает ищется узел в дереве item, у этого узла
 * 	тег-класс field, текстовое значение Поле,а его родитель имеет тег-класс document и значение Счет.
 * 	Если ищем узел с классом md_headers или md_forms или md_tables и т.д. то при вызове функции
 * 	последний параметр objName указывать не нужно.
 * 	\param mdItem - Указатель на дерево
 * 	\param parentObjClass - Класс родительского элемента в дереве
 * 	\param parentObjName - Заголовок родительского элемента в дереве
 * 	\param objClass - Класс элемента в дереве
 * 	\param objName - Заголовок элемента в дереве
 * \_ru
 */
aListViewItem*
aListViewItem::findItemInMD(aListViewItem *mdItem, const QString &parentObjClass, const QString &parentObjName, const QString &objClass, const QString &objName) const
{
	aCfg*			md = mdItem->md;
	aCfgItem 		obj = mdItem->obj;
	aListViewItem*	aitem;
	QListView*		qlist;
	QListViewItem*	qitem;
	bool 			parentFound = false;
	QString 		oName = "";
	QString 		oClass = "";

	qitem = mdItem;
	qlist = qitem->listView();
	QListViewItemIterator it( qlist );
	while ( it.current() )
	{
		QListViewItem *qitem = it.current();
		aitem = (aListViewItem *) qitem;
		oName = md->attr( aitem->obj, mda_name );
		oClass = md->objClass ( aitem->obj );
		if (!parentFound && oClass == parentObjClass && oName  == parentObjName)
			parentFound = true;
		if (parentFound == true && md->objClass ( aitem->obj ) == objClass)
		{
			if ((md->attr( aitem->obj, mda_name )  == objName) || (objName == ""))
				return aitem;
		}
		++it;
	}
	return NULL;
}

aMetadataTreeView::aMetadataTreeView(  QWidget *parent, aCfg *cfgmd )
:ananasTreeView( parent, cfgmd )
{
	aListViewItem *conf;

	if ( !md ) return;
	conf = new aListViewItem( this, md, md->find( mdc_metadata ), md->info( mda_name ));
	conf->setOpen( TRUE );
	connect( this, SIGNAL( contextMenuRequested( QListViewItem*, const QPoint&, int) ), this, SLOT(ContextMenu() ) );
	connect( this, SIGNAL( returnPressed( QListViewItem* ) ), this, SLOT( itemEdit() ) );
	connect( this, SIGNAL( doubleClicked( QListViewItem* ) ), this, SLOT( itemEdit() ) );
	connect( this, SIGNAL( collapsed( QListViewItem* ) ), this, SLOT( on_collapsed( QListViewItem* ) ) );
}

void
aMetadataTreeView::on_collapsed( QListViewItem * item )
{
	aListViewItem *i = (aListViewItem *) item;
	if ( i )
	{
		QString oclass = md->objClass( i->obj );
		if ( oclass == md_metadata ) setOpen( i, true );
	}
}


void
aMetadataTreeView::ContextMenu()
{

	QPopupMenu *m=new QPopupMenu( this, "PopupMenu" );
	Q_CHECK_PTR(m);

/*    	QLabel *caption = new QLabel( "<font color=darkblue><u><b>"
		"Context Menu</b></u></font>", this );
		caption->setAlignment( Qt::AlignCenter );
    	m->insertItem( caption );
    	m->insertItem( "&New",  this, SLOT( itemNew() ), CTRL+Key_N );
		m->insertItem( "&Rename", this, SLOT( itemRename() ), CTRL+Key_O);
		m->insertItem( "&Edit",  this, SLOT( itemEdit() ), CTRL+Key_N );
    	m->insertItem( "&Delete", this, SLOT( itemDelete() ), CTRL+Key_O );*/

		ContextMenuAdd(m);
		m->insertItem( tr("&New"),  this, SLOT( itemNew() ), CTRL+Key_N );
		m->exec( QCursor::pos() );
		delete m;
}


void
aMetadataTreeView::itemRename()
{
	renameItem();
}

void
aMetadataTreeView::itemNew()
{
	aListViewItem *i = (aListViewItem *) selectedItem();
	if ( i )
	{
		//if ( i->id == 0 )
			 i->newObject();
	}
}


void
aMetadataTreeView::itemDelete()
{
	deleteItem();
}


void
aMetadataTreeView::itemEdit()
{
	aListViewItem *i = (aListViewItem *) selectedItem();
	if ( i )
	{
		i->edit();
	}
}

void
aMetadataTreeView::itemSave()
{
	aListViewItem *i = (aListViewItem *) selectedItem();
	if ( i )
	{
		i->saveItem();
	}
}

void
aMetadataTreeView::itemLoad()
{
	aListViewItem *i = (aListViewItem *) selectedItem();
	if ( i )
	{
		i->loadItem();
	}
}
void
aMetadataTreeView::itemMoveUp()
{
	moveUpItem();
}

void
aMetadataTreeView::itemMoveDown()
{

	moveDownItem();
}
