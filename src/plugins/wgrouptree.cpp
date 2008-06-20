/****************************************************************************
** $Id: wgrouptree.cpp,v 1.17 2008/04/12 18:05:35 app Exp $
**
** Header file of the document plugin of Ananas
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

#include <qheader.h>
#include <qlayout.h>
#include <qaction.h>
#include "wgrouptree.h"
#include "awidget.h"
#include "alog.h"
#include "wdbtable.h"

wGroupTreeItem::wGroupTreeItem( QListView *parent, const QString &name )
    : QListViewItem( parent, name )
{
	level = -1;
	parent = 0;
	id = 0;
}


wGroupTreeItem::wGroupTreeItem( wGroupTreeItem *parent, wGroupTreeItem *after, const QString &name, int newlevel, ANANAS_UID newid )
    : QListViewItem( parent, after, name )
{
	level = newlevel;
	id = newid;
}


wGroupTreeItem::wGroupTreeItem( wGroupTreeItem *parent, wGroupTreeItem *after, aCatGroup *g )
    : QListViewItem( parent, after )
{
	level = g->Value( "Level" ).toInt();
	id = g->getUid();
	setText( 0, g->displayString() );
}


wGroupTreeItem::~wGroupTreeItem()
{
}



wGroupTreeItem *
wGroupTreeItem::parentItem()
{
	return ( wGroupTreeItem *) parent();
}


wGroupTree::wGroupTree( QWidget *parent, WFlags fl )
    : aWidget( parent, "wGroupTree", fl )
{
	currentId = 0;
	tree = new wTreeView( this );
	tree->addColumn( "" );
	tree->header()->hide();
	tree->setSorting( 0 );
	tree->setSelectionMode( QListView::Single );
	root = new wGroupTreeItem( tree, "ROOT" );
	root->setOpen( true );
	root->setPixmap(0, QPixmap::fromMimeSource("wcatalogue.png"));

	QGridLayout *l = new QGridLayout( this );
	l->addWidget( tree, 0, 0 );
//	connect(tree, SIGNAL(selectionChanged(QListViewItem*)),
//		this, SLOT( on_selectionChanged(QListViewItem*)));
	connect(tree, SIGNAL(currentChanged(QListViewItem *)),
		this, SLOT(on_selectionChanged(QListViewItem*)));	
	connect(tree, SIGNAL(dropped(QDropEvent*)), 
		this, SLOT(dropped(QDropEvent*)));
}


wGroupTree::~wGroupTree()
{
}


void
wGroupTree::initObject( aDatabase *adb )
{
	aWidget::initObject( adb );
	findGroupTree();
	//connectSlots();
}


QDialog*
wGroupTree::createEditor( QWidget * )//parent )
{
    return 0; //new eCatalogue( parent );
}



/*!
 * Create aDocument database object.
 */
aObject *
wGroupTree::createDBObject(  aCfgItem obj, aDatabase *adb )
{
	return new aCatGroup( obj, adb );
}


void
wGroupTree::buildGroupTree( aCfgItem obj, aCatGroup * /*cg1*/, wGroupTreeItem * wG )
{

	aCatGroup cg2 (obj, db);
	QString t;
	int err = 0;
	wGroupTreeItem *item;
	int level = 0;
	do
	{
		err = cg2.select(QString("level=%1").arg(level++));
		if ( !err )
		{
			if(cg2.First())
    		do
			{
				wGroupTreeItem * parentItem = wG;
				if(cg2.parentUid())
					parentItem = findItem(cg2.parentUid());
				if(!parentItem)
				{
					aLog::print(aLog::MT_ERROR, QString("%1 %2: Can't find group %4 in tree.").arg(__FILE__).arg(__LINE__).arg(cg2.parentUid()));
					continue;
				}
				item = new wGroupTreeItem ( parentItem, 0, &cg2 ); 
				item->setPixmap( 0, QPixmap::fromMimeSource( "t_cat_g.png" ));
			} while ( cg2.Next() );
			else break;
		} else 
			aLog::print(aLog::MT_ERROR, QString("table %1 err = %2\n").arg(cg2.table()->name()).arg(err));
    }while(!err);
}


/*
void
wGroupTree::buildGroupTree( aCfgItem obj, aCatGroup * cg1, wGroupTreeItem * wG )
{
	aCatGroup cg2 (obj, db);
	QString t;
	int err = 0;
	wGroupTreeItem *item;
	CHECK_POINT

	err = cg2.SelectChild( cg1 );
	if ( !err )
	{
//		CHECK_POINT
//		QListViewItem * parent1 = new QListViewItem ( wG );
//		wG = new wGroupTreeItem ( tree, parent1 );
    	do
    	{
//			CHECK_POINT
			t = cg2.Value("Name").toString();
//			CHECK_POINT
			item = new wGroupTreeItem ( wG, 0, &cg2 ); //cg2.Value("Level").toInt(), cg2.getUid() );
			item->setPixmap( 0, QPixmap::fromMimeSource( "t_cat_g.png" ));
//			buildGroupTree( obj, &cg2, wG );
//			CHECK_POINT
			buildGroupTree( obj, &cg2, item );
//			CHECK_POINT
    	}
    	while ( cg2.Next() );
	} else {
//		CHECK_POINT
		printf("table %s err = %d\n", ( const char *)cg2.table()->name(), err);
	}
}
*/


void
wGroupTree::findGroupTree()
{
	aCfgItem tab, cat;
	if ( !db || !md ) return;
	aWidget *pc = parentContainer( this );
	if(getId())
		pc = this;
	if ( !pc || !pc->getId()) return;
	aLog::print(aLog::MT_DEBUG, QString("inserted in %1").arg(pc->className()));
	if ( pc->className() == QString("wCatalogue") || pc->className() == QString("wGroupTree")) 
	{
		tree->clear();
		cat = md->find( pc->getId() );

		root = new wGroupTreeItem( tree, "ROOT" );
		root->setOpen( true );
		root->setPixmap(0, QPixmap::fromMimeSource("wcatalogue.png"));
		
		root->setText( 0, md->attr( cat, mda_name ) );		
		buildGroupTree( cat, 0, root );
	}
}


/*!
 *\~english
 *
 *\~russian
 * ������ ������������� �����.
 *\~
 */
void
wGroupTree::keyPressEvent ( QKeyEvent *e )
{
	ANANAS_UID id = 0;
	wGroupTreeItem * item = ( wGroupTreeItem * ) tree->currentItem();
	aLog::print(aLog::MT_DEBUG, QString("key=%1").arg(e->key()));
	switch ( e->key() ){
	case Qt::Key_Return:
		id = item->id;
		if ( e->state() == Qt::ShiftButton ) {
			aLog::print(aLog::MT_DEBUG, QString("Shift+Return pressed %1").arg(id));
			if ( id ) EditGroup();
		} else {
			aLog::print(aLog::MT_DEBUG, QString("Return pressed %1").arg(id));
			emit( selected( id ) );
		}
		e->accept();
		break;
	case Qt::Key_Escape:
		break;
	case Qt::Key_Delete:
		id = item->id;
		if ( id ) DeleteGroup();
		break;
	case Qt::Key_Insert:
		NewGroup();
		item = ( wGroupTreeItem * ) tree->currentItem();
		id = item->id;
		if ( id ) EditGroup();
		break;

	default:
		e->ignore();
		break;
	}
	aWidget::keyPressEvent( e );
}



void
wGroupTree::NewGroup()
{
	wGroupTreeItem *item, *cur;
	int level;

	cur = ( wGroupTreeItem *) tree->currentItem();
	if ( !cur ) cur = root;
	level = cur->level + 1;
	( ( aCatGroup *) dbobj )->New();
	dbobj->setSysValue("level", level );
	dbobj->setSysValue("idp", cur->id );
	dbobj->Update();
	item = new wGroupTreeItem ( cur, 0, ( aCatGroup *) dbobj );
	item->setPixmap( 0, QPixmap::fromMimeSource( "t_cat_g.png" ));
	item->id = dbobj->getUid();
	cur->setOpen( true );
	tree->setCurrentItem( item );
	EditGroup();
}


void
wGroupTree::DeleteGroup()
{
	aCatGroup g( *getMDObject(), db);
	wGroupTreeItem * item = ( wGroupTreeItem * ) tree->currentItem();
	if(item!=root)
	{
		g.select( item->id );
		g.Delete();
		item->id=0;
		item->setText(0,"X");
	}
}


void
wGroupTree::EditGroup()
{
	ANANAS_UID id = 0;
	wGroupTreeItem * item = ( wGroupTreeItem * ) tree->currentItem();
	if(item!=root)
	{
		aForm * f = 0;
		if ( item ) id = item->id;
		if ( id ) {
			if ( engine ) {
				if(getId())
					f = engine->openForm( getId() , 0, md_action_edit, md_form_group, id, this );
				else
					f = engine->openForm( parentContainer( this )->getId(), 0, md_action_edit, md_form_group, id, this );
				if ( f ) {
					f->SelectGroup(id);
					connect(f, SIGNAL( update( ANANAS_UID )), this, SLOT(updateItem( ANANAS_UID )));
//				connect(f, SIGNAL(selected( Q_ULLONG )), this, SLOT(on_selected( Q_ULLONG )));
//				f->closeAfterSelect = true;
				}
			} else {
				aLog::print(aLog::MT_ERROR, "No Engine");
			}

		}
	}
}


//void
//wGroupTree::UpdateItem( aCatGroup *g )
//{
//}


/*!
 * Show appropriated group after catalogue item selected.
 */
void
wGroupTree::on_selected( ANANAS_UID element )
{
	Q_UNUSED(element);
}


/*!
 * Update item after edit.
 */
void
wGroupTree::updateItem( ANANAS_UID element )
{
	wGroupTreeItem *i = 0;
	aCatGroup g( *getMDObject(), db);

	aLog::print(aLog::MT_DEBUG, QString("Need update text %1").arg(element));
	i = findItem( element );
	if ( i ) {
		g.select( element );
		aLog::print(aLog::MT_DEBUG, QString("founded text %1 %2").arg(element).arg(i->text(0)));
		i->setText( 0, g.displayString() );

	}
}


wGroupTreeItem *
wGroupTree::findItem( ANANAS_UID id )
{
	wGroupTreeItem *i = 0;

	QListViewItemIterator it( tree );
	while ( ( i = ( wGroupTreeItem *) it.current() ) ) {
		if ( i->id == id ) break;
		++it;
	}
	return i;
}


/*!
 * Create toolbar for Journal.
 */
QToolBar*
wGroupTree::createToolBar( QMainWindow * owner )
{
	QAction *a;
	QToolBar *t = new QToolBar( owner, "GroupTreeTools" );

	a = new QAction(
	QPixmap::fromMimeSource("doc_new.png"),
	tr("New"),
	QKeySequence(""),//Insert"),
	t,
	tr("New group")
	);
	a->setToolTip(tr("New group (Ins)"));
	a->addTo( t );
	connect( a, SIGNAL( activated() ), this, SLOT( NewGroup() ) );

	a = new QAction(
	QPixmap::fromMimeSource("doc_edit.png"),
	tr("Edit"),
	QKeySequence(""),//Return"),
	t,
	tr("Edit group")
	);
	a->setToolTip(tr("Edit group (Enter)"));
	a->addTo( t );
	connect( a, SIGNAL( activated() ), this, SLOT( EditGroup() ) );

/*	a = new QAction(
	QPixmap::fromMimeSource("doc_view.png"),
	tr("View"),
	QKeySequence("Shifh+Return"),
	t,
	tr("View element")
	);
	a->setToolTip(tr("View element (Shift+Enter)"));
	a->addTo( t );
	connect( a, SIGNAL( activated() ), this, SLOT( view() ) );
*/
	a = new QAction(
	QPixmap::fromMimeSource("doc_delete.png"),
	tr("Delete group"),
	QKeySequence(""),//Delete"),
	t,
	tr("Delete group")
	);
	a->setToolTip(tr("Delete group (Delete)"));
	a->addTo( t );
	connect( a, SIGNAL( activated() ), this, SLOT( DeleteGroup() ) );


	return 0;
}

void
wGroupTree::on_selectionChanged( QListViewItem * item)
{
	aLog::print(aLog::MT_DEBUG, QString("wGroupTree id =%1").arg(((wGroupTreeItem*) item)->id));
	currentId = ((wGroupTreeItem*)item)->id;
	emit(selectionChanged( ((wGroupTreeItem*) item)->id) );
}


void wGroupTree::dropped(QDropEvent * e)
{
    wGroupTreeItem * i = (wGroupTreeItem *) tree->itemAt(e->pos());
    if(!i)
    {
	e->ignore();
	return;
    }
        
    QSqlRecord * rec = ((wDBTable*)e->source())->currentRecord();
    if ( !rec ) return;
    Q_ULLONG id = 0;
    if(rec->contains("id")) id = rec->value("id").toLongLong();
    QString t = ((wDBTable*)e->source())->sqlCursor()->name();
    
    QString query = QString("UPDATE %1 SET idg=%2 WHERE id=%3")
		    .arg(t)
		    .arg(i->id)
		    .arg(id);
    db->db()->exec(query);
    ((wDBTable*)e->source())->refresh();
}

wTreeView::wTreeView(QWidget * parent) :
	QListView(parent)
{
    setAcceptDrops(TRUE);
}

void wTreeView::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept(parent()->parent()->name()==e->source()->parent()->name());
}

void wTreeView::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptAction(TRUE);
}

void wTreeView::dropEvent(QDropEvent *e)
{
    emit(dropped(e));
}
