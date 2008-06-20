/****************************************************************************
** $Id: deditcat.ui.h,v 1.23 2008/06/09 11:47:59 app Exp $
**
** Code file of the Edit Catalog window
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
#include <qsinterpreter.h>
#include <qseditor.h>
#include <qinputdialog.h>
#include "acfg.h"
#include "deditfield.h"
#include "deditdialog.h"
#include "awindowslist.h"
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
#include "qapplication.h"
#include "alog.h"
#include "binreloc.h"

extern MainForm *mainform;

/*!
 * \en
 * Reads out from a configuration and fills values widgets
 * Updating of lists
 * \_en
 * \ru
 * \brief ScriptAPI.
 *  Считывает из конфигурации и заполняет значения виджетов.
 * Обновление списков
 * \_ru
*/
void dEditCat::setData( aListViewItem *o )
{
    long int i;
    int fid, fieldid, stdf;
    item = o;
    aCfg *md = o->md;
    aCfgItem obj = o->obj, sv, g, e, cat, field;

    aAliasEditor *a = new aAliasEditor( md, obj, tAliases );
    al = a;
    al->setData();
    aRoleEditor *r = new aRoleEditor( md, obj, tRoles, md_catalogue );
    re = r;
    re->setData();
    setCaption( tr("Catalogue:") + md->attr( obj, mda_name ) );
    eName->setText( md->attr( obj, mda_name ) );
    eDescription->setText( md->sText( obj, md_description ) );
    g = md->find( obj, md_group ); // Find group context
    e = md->find( obj, md_element ); // Find Element context
    sv = md->find( g, md_string_view ); // Group string view

    eStrViewFG->setText( md->sText( sv, md_svfunction ) );
    eSvG->insertItem( "[ standart function ]" );
    eSvG->insertItem( "[ user function ]" );
    fid = md->sText( sv, md_fieldid ).toInt();
    stdf = md->attr( sv, mda_stdf ).toInt();
    eSvG->setCurrentItem( 0 );
    for ( i = 0; i < md->count( g, md_field ); i++ ) {
	field = md->find( g, md_field, i );
	eSvG->insertItem( QString("%1").arg( md->attr( field, mda_name ) ) );
	fieldid = md->id( field );
	fieldsg.insert( i, new int( fieldid ) );
	if ( fid == fieldid && !stdf ) {
	    eSvG->setCurrentItem( i + 2 );
	    eStrViewFG->setEnabled( FALSE );
	}
    }
    if ( !fid && !stdf ) {
	eStrViewFG->setEnabled( TRUE );
	eSvG->setCurrentItem( 1 );
    }

    sv = md->find( e, md_string_view );
    eStrViewF->setText( md->sText( sv, md_svfunction ) );
    eSv->insertItem( "[ standart function ]" );
    eSv->insertItem( "[ user function ]" );
    fid = md->sText( sv, md_fieldid ).toInt();
    stdf = md->attr( sv, mda_stdf ).toInt();
    eSv->setCurrentItem( 0 );
    for ( i = 0; i < md->count( e, md_field ); i++ ) {
	field = md->find( e, md_field, i );
	eSv->insertItem( QString("%1").arg( md->attr( field, mda_name ) ) );
//	eListAttr->insertItem( QString("%1").arg( md->attr( field, mda_name ) ) );
	fieldid = md->id( field );
	fields.insert( i, new int( fieldid ) );
	if ( fid == fieldid && !stdf ) {
	    eSv->setCurrentItem( i + 2 );
	    eStrViewF->setEnabled( FALSE );
	}
    }
    if ( !fid && !stdf ) {
	eStrViewF->setEnabled( TRUE );
	eSv->setCurrentItem( 1 );
    }

    GetElementAttributesList();
    GetFormsList();
    CatList();
    GetGroupAttributesList();
    eGenCodeGrp_pressed( 0 );
}


/*!
 * \en
 * Reading of attributes from a configuration in the list
 * \_en
 * \ru
 * Считывание атрибутов из конфигурации в список
 * \_ru
*/
void dEditCat::GetElementAttributesList()
{
	elementAttributesList->clear();
	eFieldList->clear();
	eFieldList->insertItem(tr("<<< Not set >>>"));	
	int  i;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, cobj, e;
	e = md->find( obj, md_element ); // Find Element context
	for ( i = 0; i < md->count( e, md_field ); i++ ) {
		cobj = md->find( e, md_field, i );
		if ( !cobj.isNull() )
		{
		 	new aListViewItem(elementAttributesList , md, cobj, QString::null );
			eFieldList->insertItem( QString("%1").arg(md->attr(cobj, mda_name)));
		}
	}	
}


/*!
 * \en
 * Reading of attributes of groups from a configuration in the list
 * \_en
 * \ru
 * Считывание атрибутов группы из конфигурации в список
 * \_ru
*/
void dEditCat::GetGroupAttributesList()
{
	groupAttributesList->clear();
	int  i;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, g, field;
	g = md->find( obj, md_group ); // Find Group context
	for ( i = 0; i < md->count( g, md_field ); i++ ) {
		field = md->find( g, md_field, i );
		new aListViewItem(groupAttributesList, md, field, QString::null );
	}

}

/*!
 * \en
 * Reading of forms from a configuration in the list
 * \_en
 * \ru
 * Считывание форм из конфигурации в список
 * \_ru
*/
void dEditCat::GetFormsList()
{
	formsList->clear();
	int i;
	aCfg *md = item->md;
	aCfgItem cobj, gobj, f, field;
	aCfgItem obj = item->obj;
	f = md->find(obj, md_forms);// Find forms context
	for ( i = 0; i < md->count( f, md_form ); i++ )
	{
		cobj = md->find( f, md_form, i );
		if ( !cobj.isNull() )
		{
		    new aListViewItem( formsList, md, cobj, QString::null );
		}
	}
}

/*!
 * \en
 * Reading of catalogues from a configuration in the list
 * \_en
 * \ru
 * Считывание каталогов из конфигурации в список
 * \_ru
*/
void dEditCat::CatList()
{
	eParentCat->clear();
	eParentCat->insertItem(tr("<<< Not subordinate >>>"));
	long int i;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, aobj, cat, field;
	aCfgItem cobj = md->parent( obj ); // Parent. All Catalogues
	for ( i = 0; i < md->count(md->parent( obj ), md_catalogue); i++ )
	{
	  field = md->find( md->parent( obj ), md_catalogue, i );
	  if (QString("%1").arg(md->attr(field, mda_name )) != md->attr( obj, mda_name ))
	  {
	  	  eParentCat->insertItem(QString("%1").arg(md->attr(field, mda_name )));
	  }
	}
}


/*!
 * \en
 * Init dEditCat form
 * Initialization of properties of objects of the form
 * \_en
 * ru
 * Инициализация формы редактора справочников
 * Инициализация свойств объектов формы
 * \_ru
*/
void dEditCat::init()
{
	delete statusBar();
	eStrViewF->setInterpreter( new QSInterpreter() );
	eStrViewF->setEnabled( FALSE );
	formsList->header()->hide();
	elementAttributesList->header()->hide();
	groupAttributesList->header()->hide();
	//Label_Cname->hide();
	//eCname->hide();
	//Label_Comment->hide();
	//eComment->hide();
}


/*!
 * \en
 * Reads values widgets and writes them in a configuration
 * \_en
 * \ru
  * \brief ScriptAPI.
 * Читает значения виджетов и записывает их в конфигурацию
 * \_ru
*/
void dEditCat::updateMD()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj, sv, g, e;

	al->updateMD();
	re->updateMD();
	item->setText( 0, eName->text().stripWhiteSpace() );
	md->setAttr( obj, mda_name, eName->text().stripWhiteSpace() );
	md->setSText( obj, md_description, eDescription->text() );
	g = md->find( obj, md_group ); // Find group context
	e = md->find( obj, md_element ); // Find Element context
	//======== Element view save
	sv = md->find( e, md_string_view );
	if ( sv.isNull() ) sv = md->insert( e, md_string_view );
	md->setSText( sv, md_svfunction, eStrViewF->text() );
	if ( eSv->currentItem() == 0 ) md->setAttr( sv, mda_stdf, "1" );
	else {
	    md->setAttr( sv, mda_stdf, "0" );
	    if ( eSv->currentItem() == 1 ) md->setSText( sv, md_fieldid, "0" );
	    else md->setSText( sv, md_fieldid, QString("%1").arg( *(fields.find( eSv->currentItem() - 2 ) ) ) );
	}
	//======== Group view save
	sv = md->find( g, md_string_view );
	if ( sv.isNull() ) sv = md->insert( g, md_string_view );
	md->setSText( sv, md_svfunction, eStrViewFG->text() );
	if ( eSvG->currentItem() == 0 ) md->setAttr( sv, mda_stdf, "1" );
	else {
	    md->setAttr( sv, mda_stdf, "0" );
	    if ( eSvG->currentItem() == 1 ) md->setSText( sv, md_fieldid, "0" );
	    else md->setSText( sv, md_fieldid, QString("%1").arg( *(fieldsg.find( eSvG->currentItem() - 2 ) ) ) );
	}

}

/*!
 * \en
 * Destroy dEditCat form
 * \_en
 * \ru
 * Уничтожение формы редактора справочников
 * \_ru
*/
void dEditCat::destroy()
{
    updateMD();
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
}


/*!
 *  \en
 * Opportunity to write the function for element if it is chosen user function 
 * \_en
 * \ru
 * Возможность написать свою функцию для елемента если выбрано user function
 * \_ru
 * \param index - \en Index of the chosen element in the list \_en \ru
 *	Индекс выбранного элемента в списке \_ru
*/
void dEditCat::eSv_activated( int index )
{
    if ( index == 1 ) eStrViewF->setEnabled( TRUE );
    else eStrViewF->setEnabled( FALSE );
}

/*!
 *  \en
 * Opportunity to write the function for group if it is chosen user function
 * \_en
 * \ru
 * Возможность написать свою функцию для группы если выбрано user function
 * \_ru
 * \param index - \en Index of the chosen element in the list \_en \ru
 *	Индекс выбранного элемента в списке \_ru
*/
void dEditCat::eSvG_activated( int index )
{
    if ( index == 1 ) eStrViewFG->setEnabled( TRUE );
    else eStrViewFG->setEnabled( FALSE );
}


/*!
 * \en
 * Processes the user pressing the button " New attribute of an element " and creates in metadata new attribute of an element. 
 * Requests a name of attribute of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Новый атрибут элемента" и создает в метаданных 
 * новый атрибут элемента. Запрашивает имя атрибута у пользователя.
 * \_ru
*/
void dEditCat::createNewElementAttribute_clicked()
{
	aListViewItem *newitem, *fielditem;
	aCfgItem newobj;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, e, field;
	bool ok, yes=TRUE;
	QString fieldName;
	QStringList tN;
	int i;
	QString prompt = tr("Enter a new field name:");
	e = md->find( obj, md_element ); // Find Element context
	for ( i = 0; i < md->count( e, md_field); i++ )
	{
		field = md->find( e, md_field, i);
		tN.append(md->attr(field, mda_name ));
	}

	while (yes)
	{
		fieldName = QInputDialog::getText(
			tr("Add new field"),
			prompt,
			QLineEdit::Normal,
			QString::null, &ok, this );
		if ( ok && !fieldName.isEmpty() )
		{
			if (tN.contains(fieldName) == 0 )
			{
				yes=FALSE;
			}else
			{
				prompt = QString(tr("Field <b>%1</b> alredy exist.\nEnter another field name:").arg(fieldName));
				yes=TRUE;
			}
		}else{
			fieldName = "";
			yes=FALSE;
		}
	}

	if (fieldName != "")
	{
		fielditem = item->findItemInMD(item, "catalogue", md->attr( obj, mda_name ), "element", "");

		newobj = md->insert( md->find(obj, md_element), md_field, fieldName );
		newitem = new aListViewItem(fielditem, fielditem->getLastChild(), md, newobj );
		new aListViewItem( elementAttributesList, md, newobj );

		newitem->setSelected( FALSE );
		newitem->setOpen( FALSE );

		QWorkspace *ws = mainform->ws;
		aWindowsList *wl = mainform->wl;
		QString oclass = md->objClass( obj );
		int objid = md->id( newitem->obj );
		if ( wl->find( objid ) )
		{
			wl->get( objid )->setFocus();
			return;
		}
		QWidget *editor;
		dEditField *e = new dEditField( ws, 0, WDestructiveClose );

		editor = e;
		e->setData(newitem);
		QObject::connect(mainform, SIGNAL(tosave()), editor, SLOT( updateMD()));
		QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetElementAttributesList()));
		e->show();
		mainform->addTab(++mainform->lastTabId,e->name());
		e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
				e->parentWidget()->frameSize().height());
		wl->insert( objid, e );
		updateMD();
	}

}


/*!
 * \en
 * Processes the user pressing button " Edit " and causes the form of editing of attribute of an element.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Редактировать"  и  вызывает форму редактирования атрибута элемента.
 * \_ru
*/
void dEditCat::editElementAttribute_clicked()
{
    aCfg *md = item->md;
    aCfgItem obj = item->obj;
    QWorkspace *ws = mainform->ws;
    aWindowsList *wl = mainform->wl;
    aListViewItem *ai = (aListViewItem *) elementAttributesList->currentItem(), *elementitem;

	elementitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "field", ai->text(0));

    int objid = md->id( ai->obj );
    if ( wl->find( objid ) )
    {
	wl->get( objid )->setFocus();
	return;
    }
    QWidget *editor;
    dEditField *e = new dEditField( ws, 0, WDestructiveClose );
    editor = e;
    e->setData(elementitem);
    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
    QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetElementAttributesList()));
    wl->insert( objid, editor );
    e->show();
    mainform->addTab(++mainform->lastTabId,e->name());
    e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
	e->parentWidget()->frameSize().height());
}

/*!
 * \en
 * Processes the user pressing button " Delete " and deletes from metadata attribute of an element in the catalogue.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных атрибут элемента в справочнике.
 * \_ru
*/
void dEditCat::deleteElementAttribute_clicked()
{
	if (elementAttributesList->childCount() == 0)
		return;

	aCfg *md = item->md;
	aListViewItem *i = (aListViewItem *) elementAttributesList->currentItem(), *elementitem;
	
	if (elementAttributesList->currentItem()->isSelected()) 
	{
		elementitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "field", i->text(0));
		if ( elementitem )
		{
			if ( i->id ) {
				md->remove( i->obj );
				delete elementitem;
			}
		}
		GetElementAttributesList();
		if (elementAttributesList->childCount() == 0)
		{
			moveUpElementAttribute->setEnabled(FALSE);
			moveDownElementAttribute->setEnabled(FALSE);
			editElementAttribute->setEnabled(FALSE);
			deleteElementAttribute->setEnabled(FALSE);
		}
	}
}


/*!
 * \en
 *  Processes the user pressing the button " Move up"
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить вверх"
 * \_ru
*/
void dEditCat::moveUpElementAttribute_clicked()
{
	aListViewItem *ai = (aListViewItem *) elementAttributesList->currentItem(), *eitem;
	aCfg *md = item->md;
	QString itemName = ai->text(0);
	eitem = item->findItemInMD(item, "catalogue", md->attr(item->obj, mda_name ), "field", itemName);
	eitem->moveUp();
	GetElementAttributesList();
	elementAttributesList->setCurrentItem(elementAttributesList->findItem(itemName, 0));
	elementAttributesList_selectionChanged();
}

/*!
 * \en
 *  Processes the user pressing the button " Move down"
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить вниз"
 * \_ru
*/
void dEditCat::moveDownElementAttribute_clicked()
{
	aListViewItem *ai = (aListViewItem *) elementAttributesList->currentItem(), *eitem;
	aCfg *md = item->md;
	QString itemName = ai->text(0);
	eitem = item->findItemInMD(item, "catalogue", md->attr(item->obj, mda_name ), "field", itemName);
	eitem->moveDown();
	GetElementAttributesList();
	elementAttributesList->setCurrentItem(elementAttributesList->findItem(itemName, 0));
	elementAttributesList_selectionChanged();
}


/*!
 * \en
 *  Processes the user pressing the button " New attribute of group " and creates in metadata new attribute of an element. 
 * Requests a name of attribute of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Новый атрибут группы" и создает в метаданных 
 * новый атрибут группы. Запрашивает имя атрибута у пользователя.
 * \_ru
*/
void dEditCat::createNewGroupAttribute_clicked()
{
	aListViewItem *newitem, *fielditem;
	aCfgItem newobj;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, g, field;
	bool ok, yes=TRUE;
	QString fieldName;
	QStringList tN;
	int i;
	QString prompt = tr("Enter a new field name:");
	g = md->find( obj, md_group ); // Find Group context
	for ( i = 0; i < md->count( g, md_field); i++ )
	{
		field = md->find( g, md_field, i);
		tN.append(md->attr(field, mda_name ));
	}

	while (yes)
	{
		fieldName = QInputDialog::getText(
				tr("Add new field"),
				   prompt,
       QLineEdit::Normal,
       QString::null, &ok, this );
		if ( ok && !fieldName.isEmpty() )
		{
			if (tN.contains(fieldName) == 0 )
			{
				yes=FALSE;
			}else
			{
				prompt = QString(tr("Field <b>%1</b> alredy exist.\nEnter another field name:").arg(fieldName));
				yes=TRUE;
			}
		}else{
			fieldName = "";
			yes=FALSE;
		}
	}

	if (fieldName != "")
	{
		fielditem = item->findItemInMD(item, "catalogue", md->attr( obj, mda_name ), "group", "");

		newobj = md->insert( md->find(obj, md_group), md_field, fieldName );			
		newitem = new aListViewItem(fielditem, fielditem->getLastChild(), md, newobj );
		new aListViewItem( groupAttributesList, md, newobj );

		newitem->setSelected( FALSE );
		newitem->setOpen( FALSE );

		QWorkspace *ws = mainform->ws;
		aWindowsList *wl = mainform->wl;
		QString oclass = md->objClass( obj );
		int objid = md->id( newitem->obj );
		if ( wl->find( objid ) )
		{
			wl->get( objid )->setFocus();
			return;
		}
		QWidget *editor;
		dEditField *e = new dEditField( ws, 0, WDestructiveClose );

		editor = e;
		e->setData(newitem);
		QObject::connect(mainform, SIGNAL(tosave()), editor, SLOT( updateMD()));
		QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetGroupAttributesList()));
		e->show();
		mainform->addTab(++mainform->lastTabId,e->name());
		e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
				e->parentWidget()->frameSize().height());
		wl->insert( objid, e );
		updateMD();
	}

}

/*!
 * \en
 *  Processes the user pressing button " Edit " and causes the form of editing of attribute of group.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Редактировать"  и  вызывает форму редактирования атрибута группы.
 * \_ru
*/
void dEditCat::editGroupAttribute_clicked()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	QWorkspace *ws = mainform->ws;
	aWindowsList *wl = mainform->wl;
	aListViewItem *ai = (aListViewItem *) groupAttributesList->currentItem(), *groupitem;

	groupitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "field", ai->text(0));

	int objid = md->id( ai->obj );
	if ( wl->find( objid ) )
	{
		wl->get( objid )->setFocus();
		return;
	}

	QWidget *editor;
	dEditField *e = new dEditField( ws, 0, WDestructiveClose );
	editor = e;
	e->setData(groupitem);
	QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetGroupAttributesList()));
	wl->insert( objid, editor );
	e->show();
	mainform->addTab(++mainform->lastTabId,e->name());
	e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
	e->parentWidget()->frameSize().height());
}

/*!
 * \en
 *  Processes the user pressing button " Delete " and deletes from metadata attribute of group in the catalogue.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных атрибут группы в справочнике.
 * \_ru
*/
void dEditCat::deleteGroupAttribute_clicked()
{
	if (groupAttributesList->childCount() == 0)
		return;

	aCfg *md = item->md;
	aListViewItem *i = (aListViewItem *) groupAttributesList->currentItem(), *groupitem;
	
	if (groupAttributesList->currentItem()->isSelected())
	{
		groupitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "field", i->text(0));
		if ( i )
		{
			if ( i->id ) {
				md->remove( i->obj );
				delete groupitem;
			}
		}
		GetGroupAttributesList();
		if (groupAttributesList->childCount() == 0)
		{
			moveUpGroupAttribute->setEnabled(FALSE);
			moveDownGroupAttribute->setEnabled(FALSE);
			editGroupAttribute->setEnabled(FALSE);
			deleteGroupAttribute->setEnabled(FALSE);
		}
	}
}

/*!
 * \en
 *  Processes the user pressing the button " Move up "
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить вверх"
 * \_ru
*/
void dEditCat::moveUpGroupAttribute_clicked()
{
	aListViewItem *ai = (aListViewItem *) groupAttributesList->currentItem(), *gitem;
	aCfg *md = item->md;
	QString itemName = ai->text(0);
	gitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "field", itemName);
	gitem->moveUp();
	GetGroupAttributesList();
	groupAttributesList->setCurrentItem(groupAttributesList->findItem(itemName, 0));
	groupAttributesList_selectionChanged();
}

/*!
 * \en
 *  Processes the user pressing the button " Move down "
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить вниз"
 * \_ru
*/
void dEditCat::moveDownGroupAttribute_clicked()
{
	aListViewItem *ai = (aListViewItem *) groupAttributesList->currentItem(), *gitem;
	aCfg *md = item->md;
	QString itemName = ai->text(0);
	gitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "field", itemName);
	gitem->moveDown();
	GetGroupAttributesList();
	groupAttributesList->setCurrentItem(groupAttributesList->findItem(itemName, 0));
	groupAttributesList_selectionChanged();
}

/*!
 * \en
 *  Activation of buttons of moving under the list at a choice of an element of attribute
 * \_en
 * \ru
 * Активация кнопок перемещения по списку при выборе атрибута элемента
 * \_ru
*/
void dEditCat::elementAttributesList_selectionChanged()
{
   aListViewItem *ai = (aListViewItem *) elementAttributesList->currentItem();
   if ( ai->nextSibling() )
   {
      if (!moveDownElementAttribute->isEnabled() ) moveDownElementAttribute->setEnabled(TRUE);
   } else {
      if (moveDownElementAttribute->isEnabled() ) moveDownElementAttribute->setEnabled(FALSE);
   }

   if ( elementAttributesList->firstChild() ==  elementAttributesList->currentItem())
   {
      if (moveUpElementAttribute->isEnabled() ) moveUpElementAttribute->setEnabled(FALSE);
   } else {
      if (!moveUpElementAttribute->isEnabled() ) moveUpElementAttribute->setEnabled(TRUE);
   }
	if (!editElementAttribute->isEnabled() ) editElementAttribute->setEnabled(TRUE);
	if (!deleteElementAttribute->isEnabled() ) deleteElementAttribute->setEnabled(TRUE);
    }


/*!
 * \en
 *  Activation of the button of removal and editing at a choice of the form
 * \_en
 * \ru
 * Активация кнопки удаления и редактирования при выборе формы
 * \_ru
*/
void dEditCat::formsList_selectionChanged()
{
	if (!editForm->isEnabled() ) editForm->setEnabled(TRUE);
	if (!deleteForm->isEnabled() ) deleteForm->setEnabled(TRUE);
}


/*!
 * \en
 * Edit of attribute of an element
 * \_en
 * \ru
 * Редактирование атрибута элемента
 * \_ru
*/
void dEditCat::elementAttributesList_doubleClicked( QListViewItem * )
{
   editElementAttribute_clicked();
}

/*!
 * \en
 *  Processes the user pressing the button " New form" and creates in metadata new form. Requests a name of form of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Новая форма" и создает в метаданных новую форму. 
 * Запрашивает имя формы у пользователя.
 * \_ru
*/
void dEditCat::createNewForm_clicked()
{
	long int i;
	aListViewItem *newitem, *formitem;
	aCfgItem newobj;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, field;
	aCfgItem cobj =md->find(obj, md_forms);// Find forms context
	bool ok, yes=TRUE;
	QString formName;
	QStringList tN;
	QString prompt = tr("Enter a new forms name:");

	for ( i = 0; i < md->count( obj, md_form); i++ )
	{
		field = md->find( obj, md_form, i);
		tN.append(md->attr(field, mda_name ));
	}

	while (yes)
	{
		formName = QInputDialog::getText(
			tr("Add new form"),
			prompt,
   			QLineEdit::Normal,
       			QString::null, &ok, this );
		if ( ok && !formName.isEmpty() )
		{
			if (tN.contains(formName) == 0 )
			{
				yes=FALSE;
			}
			else
			{
				prompt = QString(tr("Form <b>%1</b> alredy exist.\nEnter another form name:").arg(formName));
				yes=TRUE;
			}
		}
		else
		{
			formName = "";
			yes=FALSE;
		}
	}

	if (formName != "")
	{
		QString module, tpl_name = "sourcecode.tpl", tpldir;
#ifdef Q_OS_WIN32
		tpldir = qApp->applicationDirPath()+"/templates/";
#else
		BrInitError error; 
		if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED)
		{
			aLog::print(aLog::MT_INFO, tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
			aLog::print(aLog::MT_INFO, tr("Will fallback to hardcoded default path.\n"));
		}
		aLog::print(aLog::MT_DEBUG, tr("dEditDoc::EditForm BinReloc path to data dir is %1.\n").arg( br_find_data_dir("/usr/share") ));
		tpldir = QString( br_find_data_dir("/usr/share") ) + "/ananas/templates/";
#endif	
		formitem = item->findItemInMD(item, "catalogue", md->attr( obj, mda_name ), "forms", "");
		newobj = md->insert( cobj, md_form, formName );
		QFile fi( tpldir+tpl_name );
		if ( fi.open( IO_ReadOnly ))
		{
			aLog::print(aLog::MT_DEBUG,tr("dEditDoc open file %1 for read from templates directory %2").arg(tpl_name).arg(tpldir));
			module = QString::QString( fi.readAll() );
			fi.close();
			md->setSText( newobj, md_sourcecode, module );
		}
		else
		{
			aLog::print(aLog::MT_ERROR,tr("dEditDoc file %1 not exists in templates directory %2").arg(tpl_name).arg(tpldir));
		}		
		newitem = new aListViewItem(formitem, formitem->getLastChild(), md, newobj );
		newitem->setSelected( FALSE );
		newitem->setOpen( FALSE );
		QWorkspace *ws = mainform->ws;
		aWindowsList *wl = mainform->wl;
		QString oclass = md->objClass( obj );
		int objid = md->id( newitem->obj );
		if ( wl->find( objid ) )
		{
			wl->get( objid )->setFocus();
			return;
		}
		QWidget *editor;
		dEditDialog *e = new dEditDialog( ws, 0, WDestructiveClose );
		wl->insert( objid, e );
		editor = e;
		e->setData(newitem);
		QObject::connect(mainform, SIGNAL(tosave()), editor, SLOT( updateMD()));
		QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetFormsList()));
		e->show();
		mainform->addTab(++mainform->lastTabId,e->name());
		e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
				e->parentWidget()->frameSize().height());
		updateMD();
		//newitem->edit();
	}
}

/*!
 * \en
 *  Processes the user pressing button " Edit " and causes dialogue of editing of the document
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Редактировать" и вызывает диалог редактирования документа
 * \_ru
*/
void dEditCat::editForm_clicked()
{
    aCfg *md = item->md;
    aCfgItem obj = item->obj;
    aWindowsList *wl = mainform->wl;
    QWorkspace *ws = mainform->ws;
    aListViewItem *ai = (aListViewItem *) formsList->currentItem(), *formitem;
	formitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "form", ai->text(0));
    QString oclass = md->objClass( obj );
    int objid = md->id( ai->obj );
    if ( wl->find( objid ) )
    {
	wl->get( objid )->setFocus();
	return;
    }
    QWidget *editor;
    dEditDialog *e = new dEditDialog( ws, 0, WDestructiveClose );
    wl->insert( objid, e );
    editor = e;
    e->setData(formitem);
    QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
    QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetFormsList()));
    e->show();
    mainform->addTab(++mainform->lastTabId,e->name());
    e->parentWidget()->setGeometry(0,0,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
}

/*!
 * \en
 *  Processes the user pressing button " Deletee " and deletes from metadata the form of the catalogue.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных форму справочника.
 * \_ru
*/
void dEditCat::deleteForm_clicked()
{
	if (formsList->childCount() == 0 )
		return;

	aCfg *md = item->md;
	aListViewItem *i = (aListViewItem *) formsList->currentItem(), *formitem;

	if (formsList->currentItem()->isSelected())
	{
		formitem = item->findItemInMD(item, "catalogue", md->attr( item->obj, mda_name ), "form", i->text(0));
		if ( i )
		{
			if ( i->id ) {
				md->remove( i->obj );
				delete formitem;
			}
		}	
		GetFormsList();
		if (formsList->childCount() == 0 )
		{
			editForm->setEnabled( FALSE );
			deleteForm->setEnabled( FALSE );
		}
	}
}


/*!
 * \en
 *  Editing of the form
 * \_en
 * \ru
 * Редактирование формы
 * \_ru
*/
void dEditCat::formsList_doubleClicked( QListViewItem * )
{
   editForm_clicked();
}



void dEditCat::eParentCat_activated( const QString & )
{

}


void dEditCat::eOneEandGForm_stateChanged( int )
{

}


void dEditCat::eFieldList_activated( const QString & )
{

}


/*!
 * \en
 *  Activation of buttons of moving under the list at a choice of attribute of an group
 * \_en
 * \ru
 * Активация кнопок перемещения по списку при выборе атрибута группы
 * \_ru
*/
void dEditCat::groupAttributesList_selectionChanged()
{
	aListViewItem *ai = (aListViewItem *) groupAttributesList->currentItem();
	if ( ai->nextSibling() )
	{
		if (!moveDownGroupAttribute->isEnabled() ) moveDownGroupAttribute->setEnabled(TRUE);
	} else {
		if (moveDownGroupAttribute->isEnabled() ) moveDownGroupAttribute->setEnabled(FALSE);
	}

	if ( groupAttributesList->firstChild() == groupAttributesList->currentItem() )
	{
		if (moveUpGroupAttribute->isEnabled() ) moveUpGroupAttribute->setEnabled(FALSE);
	} else {
		if (!moveUpGroupAttribute->isEnabled() ) moveUpGroupAttribute->setEnabled(TRUE);
	}

	if (groupAttributesList->childCount() != 0 )
	{
		if (!editGroupAttribute->isEnabled() ) editGroupAttribute->setEnabled(TRUE);
		if (!deleteGroupAttribute->isEnabled() ) deleteGroupAttribute->setEnabled(TRUE);
	}

}




/*!
 * \en
 *  Change of type of general show
 * \_en
 * \ru
 * Смена типа основного представления
 * \_ru
 * \param id - \en Index of the chosen element in group \_en \ru
 *	Индекс выбранного элемента в группе \_ru
*/
void dEditCat::eGenCodeGrp_pressed( int index)
{
	if (index == 0)
	{
		eCodeSerGrp->setEnabled(FALSE);
		eCodeTypeGrp->setEnabled(FALSE);
		eFieldList->setEnabled(TRUE);
	}else {
		eCodeSerGrp->setEnabled(TRUE);
		eCodeTypeGrp->setEnabled(TRUE);
		eFieldList->setEnabled(FALSE);
	}
}


/**
 * \ru
 *	\brief Сдвигает окно редактирования свойств в левый верхний угол родительского окна.
 * 
 * 	Размеры перемещаемого окна остаются без изменений.
 * \_ru
 */
void
dEditCat::moveToTopLeftCorner()
{
	this->parentWidget()->setGeometry( 0, 0, 
		this->parentWidget()->frameSize().width(),
		this->parentWidget()->frameSize().height());

}
