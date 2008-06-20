/****************************************************************************
** $Id: deditdoc.ui.h,v 1.28 2008/06/09 11:47:59 app Exp $
**
** Code file of the Edit Document window
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
#include "acfg.h"
#include <qsinterpreter.h>
#include <qseditor.h>
#include "qmessagebox.h"
#include "deditdialog.h"
#include "deditfield.h"
#include "awindowslist.h"
#include "acfg.h"
#include "mdtree.h"
#include <qlistview.h>
#include <qinputdialog.h>
#include <qregexp.h>
#include "alog.h"
#include "qapplication.h"
#include "binreloc.h"

extern MainForm *mainform;
extern CfgForm *configform;


/*!
 * \en
 * Init dEditDoc form
 * Initialization of properties of objects of the form
 * \_en
 * ru
 * Инициализация формы редактора документа
 * Инициализация свойств объектов формы
 * \_ru
*/

void dEditDoc::init()
{
	delete statusBar();
	eModule->setInterpreter( new QSInterpreter() );
	eStrViewF->setInterpreter( new QSInterpreter() );
	eStrViewF->setEnabled( FALSE );
	tableAttributesList->header()->hide();
	headerAttributesList->header()->hide();
	formsList->header()->hide();
	Label_Comment->hide();
	eComment->hide();
	Label_Cname->hide();
	eCname->hide();
}


/*!
 * \en
 * Destroy dEditDoc form
 * \_en
 * \ru
 * Уничтожение формы редактора документа
 * \_ru
*/
void dEditDoc::destroy()
{
    updateMD();
    item->editor = 0;
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
}


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
void dEditDoc::setData( aListViewItem *o )
{
    long int i;
    int fid, fieldid, stdf;
    item = o;
    aCfg *md = o->md;
    aCfgItem obj = o->obj, sv, field;

    aAliasEditor *a = new aAliasEditor( md, obj, tAliases );
    al = a;
    al->setData();
    aRoleEditor *r = new aRoleEditor( md, obj, tRoles, md_document );
    re = r;
    re->setData();
    setCaption( tr("Document:") + md->attr( obj, mda_name ) );
    eName->setText( md->attr( obj, mda_name ) );
    eDescription->setText( md->sText( obj, md_description ) );
    eModule->setText( md->sText( obj, md_sourcecode ) );
    sv = md->find( obj, md_string_view );
    eStrViewF->setText( md->sText( sv, md_svfunction ) );
    eSv->insertItem( "[ standart function ]" );
    eSv->insertItem( "[ user function ]" );
    fid = md->sText( sv, md_fieldid ).toInt();
    stdf = md->attr( sv, mda_stdf ).toInt();
    eSv->setCurrentItem( 0 );
    for ( i = 0; i < md->count( obj, md_field ); i++ ) {
	field = md->find( obj, md_field, i );
	eSv->insertItem( QString("%1").arg( md->attr( field, mda_name ) ) );
	fieldid = md->id( field );
	fields.insert( i, new int( fieldid ) );
	if ( fid == fieldid && !stdf ) {
	    eSv->setCurrentItem( i + 2 );
	    eStrViewF->setEnabled( FALSE );
	}
    }
    if ( !fid & !stdf ) {
	eStrViewF->setEnabled( TRUE );
	eSv->setCurrentItem( 1 );
    }
    GetHeaderAttributesList();
    GetTablesList();
    GetTableAttributesList();
    GetFormsList();
    DocList();
    DsubJournList();
}


/*!
 * \en
 * Reading of headers from a configuration in the list
 * \_en
 * \ru
 * Считывание заголовков из конфигурации в список
 * \_ru
*/
void dEditDoc::GetHeaderAttributesList()
{
	headerAttributesList->clear();
	eListFields->clear();
	eListFields->insertItem(tr("<<< Not set >>>"));	
	int i;
	aCfg *md = item->md;
	aCfgItem obj = item->obj,cobj, h;
	h = md->find(obj, md_header);// Find Element context
	for ( i = 0; i < md->count( h, md_field ); i++ )
	{
		cobj = md->find( h, md_field, i );
		if ( !cobj.isNull() )
		{
		    new aListViewItem( headerAttributesList, md, cobj, QString::null );
			eListFields->insertItem( QString("%1").arg(md->attr(cobj, mda_name)));
		}
	}
}


/*!
 * \en
 * Reading of tables from a configuration in the list
 * \_en
 * \ru
 * Считывание таблиц из конфигурации в список
 * \_ru
*/
void dEditDoc::GetTablesList()
{
	tablesList->clear();
	long int i;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, t, field;
	t = md->find( obj, md_tables ); // Find Table context
	for ( i = 0; i < md->count( t, md_table ); i++ ) {
		field = md->find( t, md_table, i );
		tablesList->insertItem( QString("%1").arg( md->attr( field, mda_name ) ) );
	}
	if (tablesList->count () == 0) {
		createNewTableAttribute->setEnabled(FALSE);
		renameTable->setEnabled(FALSE);
		deleteTable->setEnabled(FALSE);
	}else {
		createNewTableAttribute->setEnabled(TRUE);
		renameTable->setEnabled(TRUE);
		deleteTable->setEnabled(TRUE);
	}
}

/*!
 * \en
 * Reading of table fields from a configuration in the list
 * \_en
 * \ru
 * Считывание полей таблицы из конфигурации в список
 * \_ru
*/
void dEditDoc::GetTableAttributesList()
{
	tableAttributesList->clear();
	long int i, j;
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	aCfgItem cobj, t, T, field;
	T = md->find( obj, md_tables ); // Find Tables context
	for ( i = 0; i < md->count( T, md_table ); i++ )
	{
	  t = md->find( T, md_table, i );// Find Table
	  if (QString("%1").arg(md->attr(t, mda_name)) == tablesList->currentText() )
	  {
	     for ( j = 0; j < md->count( t, md_field ); j++ )
	     {
	        cobj = md->find(t, md_field, j);// Find Field
	        if ( !cobj.isNull() )
		{
	           new aListViewItem(tableAttributesList, md, cobj, QString::null );
	        }
	     }
	  }
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
void dEditDoc::GetFormsList()
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
 * Reading of journals from a configuration in the list
 * \_en
 * \ru
 * Считывание журналов из конфигурации в список
 * \_ru
*/
void dEditDoc::DsubJournList()
{
     eDocJournal->clear();
     long int i;
     aCfg *md = item->md;
     aCfgItem obj = item->obj, j, field;
     j = md->find( obj, md_journals ); // Find Journal context
     for ( i = 0; i < md->count(md->parent( md->parent(obj )), md_journal ); i++ )
     {
	  field = md->find( md->parent( md->parent(obj )), md_journal, i );
	  eDocJournal->insertItem( QString("%1").arg( md->attr( field, mda_name ) ) );
     }
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
void dEditDoc::updateMD()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj, sv;

	al->updateMD();
	re->updateMD();
	item->setText( 0, eName->text().stripWhiteSpace() );
	md->setAttr( obj, mda_name, eName->text().stripWhiteSpace() );
	md->setSText( obj, md_description, eDescription->text() );
	md->setSText( obj, md_sourcecode, eModule->text() );
	sv = md->find( obj, md_string_view );
	if ( sv.isNull() ) sv = md->insert( obj, md_string_view );
	md->setSText( sv, md_svfunction, eStrViewF->text() );
	if ( eSv->currentItem() == 0 ) md->setAttr( sv, mda_stdf, "1" );
	else {
	    md->setAttr( sv, mda_stdf, "0" );
	    if ( eSv->currentItem() == 1 ) md->setSText( sv, md_fieldid, "0" );
	    else md->setSText( sv, md_fieldid, QString("%1").arg( *(fields.find( eSv->currentItem() - 2 ) ) ) );
	}
}


/*!
 *  \en
 * Opportunity to write the function if it is chosen user function
 * \_en
 * \ru
 * Возможность написать свою функцию если выбрано user function
 * \_ru
 * \param index - \en Index of the chosen element in the list \_en \ru
 *	Индекс выбранного элемента в списке \_ru
*/
void dEditDoc::eSv_activated( int index )
{
    if ( index == 1 ) eStrViewF->setEnabled( TRUE );
    else eStrViewF->setEnabled( FALSE );
}


void dEditDoc::DocList()
{
     eInputBasedOn->clear();
     eInputBasedOn->insertItem(tr("<<< Not set >>>"));
     long int i;
     aCfg *md = item->md;
     aCfgItem obj = item->obj, aobj, cat, field;
     aCfgItem cobj = md->parent( obj ); // Parent. All Catalogues
     for ( i = 0; i < md->count(md->parent( obj ), md_document); i++ )
     {
	  field = md->find( md->parent( obj ), md_document, i );
	  if (QString("%1").arg(md->attr(field, mda_name )) != md->attr( obj, mda_name ))
	  {
	       eInputBasedOn->insertItem(QString("%1").arg(md->attr(field, mda_name )));
	  }
     }
}

/*!
 * \en
 * Processes the user pressing the button " the New attribute " and creates in metadata a new requisite of   
 * a cap of the document. Requests a name of a field/requisite of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Новое поле" и
 * создает в метаданных новый реквизит шапки документа. Запрашивает имя
 *поля/реквизита у пользователя.
 * \_ru
*/
void dEditDoc::createNewHeaderAttribute_clicked()
{
	aListViewItem *newitem,*headeritem;
	aCfgItem newobj;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, field;
	bool ok, yes=TRUE;
	QString fieldName;
	QStringList tN;
	int i;
	QString prompt = tr("Enter a new field name:");

	for ( i = 0; i < md->count( obj, md_field); i++ )
	{
		field = md->find( obj, md_field, i);
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
		headeritem = item->findItemInMD(item, "document", md->attr( obj, mda_name ), "header", "");
		newobj = md->insert( md->find(obj, md_header), md_field, fieldName );
		newitem = new aListViewItem(headeritem, headeritem->getLastChild(), md, newobj );
		newitem->setSelected( FALSE );
		newitem->setOpen( FALSE );
		new aListViewItem( headerAttributesList, md, newitem->obj );

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
		QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetHeaderAttributesList()));
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
 * Processes the user pressing button " Edit " and causes the form of editing of a requisite of a cap of the document.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Редактировать"  и  вызывает форму 
 * редактирования реквизита шапки документа.
 * \_ru
*/
void dEditDoc::editHeaderAttribute_clicked()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	QWorkspace *ws = mainform->ws;
	aWindowsList *wl = mainform->wl;
	aListViewItem *ai = (aListViewItem *) headerAttributesList->currentItem(), *headeritem;

	headeritem = item->findItemInMD(item, "document",md->attr( obj, mda_name ), "field", ai->text(0) );

	int objid = md->id( ai->obj );
	if ( wl->find( objid ) )
	{
		wl->get( objid )->setFocus();
		return;
	}
	QWidget *editor;
	dEditField *e = new dEditField( ws, 0, WDestructiveClose );
	editor = e;

	e->setData(headeritem);
	QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetHeaderAttributesList()));

	wl->insert( objid, editor );
	e->show();
	mainform->addTab(++mainform->lastTabId,e->name());
	e->parentWidget()->setGeometry(5,5,e->parentWidget()->frameSize().width(),
	e->parentWidget()->frameSize().height());
}



/*!
 * \en
 * Processes the user pressing the button " the New field " and creates in metadata a new field of the table. 
 * Requests a name of a field of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Новое поле" и  создает в метаданных новое поле таблицы. 
 * Запрашивает имя  поля у пользователя.
 * \_ru
*/
void dEditDoc::createNewTableAttribute_clicked()
{
	aListViewItem *newitem, *tableitem;
	aCfgItem newobj;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, T, t, field;
	aCfgItem cobj = md->parent( obj );
	long int j;
	bool ok, yes=TRUE;
	QString fieldName;
	QString prompt = tr("Enter a new field name:");
	QStringList tN;

	tableitem = item->findItemInMD(item, "document", md->attr( obj, mda_name ), "table", tablesList->currentText());
	
	for (j = 0; j < md->count(tableitem->obj , md_field); j++ )
	{
		field = md->find(tableitem->obj, md_field, j);
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
		newobj = md->insert( tableitem->obj, md_field, fieldName );
		newitem = new aListViewItem(tableitem, tableitem->getLastChild(), md, newobj );
		newitem->setSelected( FALSE );
		newitem->setOpen( FALSE );
		new aListViewItem(tableAttributesList, md, newitem->obj );

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
		wl->insert( objid, e );
		editor = e;
		e->setData(newitem);
		QObject::connect(mainform, SIGNAL(tosave()), editor, SLOT( updateMD()));
		QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetTableAttributesList()));
		e->show();
		mainform->addTab(++mainform->lastTabId,e->name());
		e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
				e->parentWidget()->frameSize().height());
		updateMD();
	}
}


/*!
 * \en
 *  Processes the user pressing button " Edit " and causes the form of editing of a field of the table.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Редактировать" 
 * и  вызывает форму редактирования поля таблицы.
 * \_ru
*/
void dEditDoc::editTableAttribute_clicked()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	QWorkspace *ws = mainform->ws;
	aWindowsList *wl = mainform->wl;
	aListViewItem *ai = (aListViewItem *) tableAttributesList->currentItem(), *tableitem;

	tableitem = item->findItemInMD(item, "document", md->attr( obj, mda_name ), "table", tablesList->currentText());
	tableitem = item->findItemInMD(tableitem, "document", md->attr( obj, mda_name ), "field", ai->text(0));

	int objid = md->id( tableitem->obj );
	if ( wl->find( objid ) )
	{
		wl->get( objid )->setFocus();
		return;
	}

	QWidget *editor;
	dEditField *e = new dEditField( ws, 0, WDestructiveClose );
	wl->insert( objid, e );
	editor = e;
	e->setData(tableitem);
	QObject::connect( mainform, SIGNAL( tosave() ), editor, SLOT( updateMD() ) );
	QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetTableAttributesList()));
	e->show();
	mainform->addTab(++mainform->lastTabId,e->name());
	e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(),
		e->parentWidget()->frameSize().height());
}


/*!
 * \en
 * Processes the user pressing button " Remove " and the field of the table deletes from metadata.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных поле таблицы
 * \_ru
*/
void dEditDoc::deleteTableAttribute_clicked()
{
	aCfg *md = item->md;
	aListViewItem *listItem = (aListViewItem *) tableAttributesList->currentItem(), *tableitem;
	if (tableAttributesList->childCount() == 0 )
	{
		return;
	}
	
	if (tableAttributesList->currentItem()->isSelected())
	{
		tableitem = item->findItemInMD(item, "document", md->attr( item->obj, mda_name ), "table", tablesList->currentText());
		tableitem = item->findItemInMD(tableitem, "document", md->attr( item->obj, mda_name ), "field", listItem->text(0));		
		
		if ( tableitem )
		{
			if ( tableitem->id )
			{
				md->remove(tableitem->obj );
				delete tableitem;
			}
		}
		GetTableAttributesList();
		if (tableAttributesList->childCount() == 0 )
		{
			editTableAttribute->setEnabled(FALSE);
			deleteTableAttribute->setEnabled(FALSE);
			moveUpTableAttribute->setEnabled(FALSE);
			moveDownTableAttribute->setEnabled(FALSE);
		}
	}
}


/*!
 * \en
 *  Processes the user pressing the button " the New form " and creates in metadata the new form of the document. 
 * Requests a name of the form of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Новая форма" и  создает в метаданных 
 * новую форму документа. Запрашивает имя  формы у пользователя.
 * \_ru
*/
void dEditDoc::createNewForm_clicked()
{
	aListViewItem *newitem, *formitem;
	aCfgItem newobj;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, field;
	aCfgItem cobj =md->find(obj, md_forms);
	bool ok, yes=TRUE;
	QString formName;
	QStringList tN;
	int i;
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
		formitem = item->findItemInMD(item, "document",md->attr( obj, mda_name ), "forms", "");
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
		new aListViewItem(formsList, md, newitem->obj );

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
void dEditDoc::editForm_clicked()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	QWorkspace *ws = mainform->ws;
	aWindowsList *wl = mainform->wl;
	aListViewItem *ai = (aListViewItem *) formsList->currentItem(), *formitem; 
	
	formitem = item->findItemInMD(item,"document", md->attr( item->obj, mda_name ), "form",  ai->text(0));
	
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
	QObject::connect(mainform, SIGNAL(tosave()), editor, SLOT( updateMD()));
	QObject::connect(e, SIGNAL(destroyed()), this, SLOT(GetFormsList()));
	e->show();
	mainform->addTab(++mainform->lastTabId,e->name());
	e->parentWidget()->setGeometry(10,10,e->parentWidget()->frameSize().width(), e->parentWidget()->frameSize().height());
}

/*!
 * \en
 *  Processes the user pressing button " Remove " and deletes from metadata the form of the document.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных форму документа.
 * \_ru
*/
void dEditDoc::deleteForm_clicked()
{
	aCfg *md = item->md;
	aListViewItem *listItem = (aListViewItem *) formsList->currentItem(), *formitem;
	if (formsList->childCount() == 0 )
		return;
		
	if (formsList->currentItem()->isSelected())
	{
		formitem = item->findItemInMD(item, "document", md->attr( item->obj, mda_name ), "form", listItem->text(0));
		if ( listItem->id ) {
			md->remove( listItem->obj );
			delete formitem;
		}
		GetFormsList();
		if (formsList->childCount() == 0 )
		{
			editForm->setEnabled(FALSE);
			deleteForm->setEnabled(FALSE);
		}
	}
}



/*!
 * \en
 *  Change of type in a numerator
 * \_en
 * \ru
 * Смена типа в нумераторе
 * \_ru
 * \param id - \en Index of the chosen element in group \_en \ru
 *	Индекс выбранного элемента в группе \_ru
*/
void dEditDoc::typeGroup_pressed( int id)
{
    if ( id == 1 ){
	NumTypLen->setEnabled(TRUE);
	eListFields->setCurrentItem(0);
	eListFields->setEnabled(FALSE);
    }else{
	NumTypLen->setEnabled(FALSE);
	eListFields->setEnabled(TRUE);
    }
}


/*!
 * \en
 *  Processes the user pressing button " Add " and creates in metadata the new table. 
 * Requests a name of the new table of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Добавить" и  создает в метаданных новую таблицу. 
 * Запрашивает имя  новой таблицы у пользователя.
 * \_ru
*/
void dEditDoc::createNewTable_clicked()
{
	aCfgItem newobj;
	aListViewItem *tableitem;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, field;
	aCfgItem cobj =md->find(obj, md_tables);
	int i, z = 0;
	bool ok, yes=TRUE;
	QString tableName;
	QStringList tN;
	QString prompt = tr("Enter a new table name:");
	QString header = tr("Add new table");

	for ( i = 0; i < md->count(cobj, md_table); i++ )
	{
		field = md->find( cobj, md_table, i);
		tN.append(md->attr(field, mda_name ));
	}

	while (yes)
	{
		tableName = QInputDialog::getText(
			header, prompt,
			QLineEdit::Normal,
			QString::null, &ok, this );
		if ( ok && !tableName.isEmpty() )
		{
			if (tN.contains(tableName) == 0 )
			{
				yes=FALSE;

			}else
			{
				prompt = QString(tr("Name <b>%1</b> alredy exist.\nEnter another table name:").arg(tableName));
				++z;
				if (z > 3) header = QString(tr("Add new table. Attempt %1").arg(z));
				yes=TRUE;
			}

		}else{
			tableName = "";
			yes=FALSE;
		}
	}

	if (tableName != "")
	{
		tableitem = item->findItemInMD(item, "document", md->attr( item->obj, mda_name ), "tables", "");
		newobj = md->insert(md->find(obj, md_tables), md_table, tableName);
		new aListViewItem(tableitem, tableitem->getLastChild(), md, newobj );
		updateMD();
		deleteTable->setEnabled(TRUE);
		GetTablesList();
		tablesList->setCurrentItem(tablesList->count()-1);
		GetTableAttributesList();
		if (headerAttributesList->childCount() == 0 )
		{
			editHeaderAttribute->setEnabled(FALSE);
			deleteHeaderAttribute->setEnabled(FALSE);
			moveDownHeaderAttribute->setEnabled(FALSE);
			moveUpHeaderAttribute->setEnabled(FALSE);
		}		
	}
}


/*!
 * \en
 *  Processes the user pressing button " Remove " and deletes from metadata the table.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных таблицу.
 * \_ru
*/
void dEditDoc::deleteTable_clicked()
{
	aCfg *md = item->md;
	aListViewItem  *tableitem;

	tableitem = item->findItemInMD(item, "document", md->attr( item->obj, mda_name ), "table", tablesList->currentText());

	if ( tableitem )
	{
		if ( tableitem->id ) {
			md->remove( tableitem->obj );
			delete tableitem;
		}
	}
	GetTablesList();
	GetTableAttributesList();
}


void dEditDoc::eJournSubordinate_activated( const QString & )
{

}

/*!
 * \en
 *  Activation of the button of removal and editing at a choice of the form
 * \_en
 * \ru
 * Активация кнопки удаления и редактирования при выборе формы
 * \_ru
*/
void dEditDoc::formsList_selectionChanged( QListViewItem * )
{
    if (!editForm->isEnabled() ) editForm->setEnabled(TRUE);
    if (!deleteForm->isEnabled() ) deleteForm->setEnabled(TRUE);
}

/*!
 * \en
 *  Loading fields the chosen table
 * \_en
 * \ru
 * Загрузка полей выбранной таблицы
 * \_ru
*/
void dEditDoc::tablesList_activated( int )
{
   GetTableAttributesList();
}


/*!
 * \en
 *  Editing of the form
 * \_en
 * \ru
 * Редактирование таблицы
 * \_ru
*/
void dEditDoc::formsList_doubleClicked( QListViewItem * )
{
   editForm_clicked();
}


/*!
 * \en
 *  Editing of a field in the table
 * \_en
 * \ru
 * Редактирование поля в таблице
 * \_ru
*/
void dEditDoc::tableAttributesList_doubleClicked( QListViewItem * )
{
   editTableAttribute_clicked();
}




/*!
 * \en
 *  Processes the user pressing the button " To move headers upwards "
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить заголовок вверх"
 * \_ru
*/
void dEditDoc::moveUpHeaderAttribute_clicked()
{
	aListViewItem *ai = (aListViewItem *) headerAttributesList->currentItem(), *headeritem;
	aCfg *md = item->md;
	QString itemName = ai->text(0);
	headeritem = item->findItemInMD(item, "document", md->attr(item->obj, mda_name ), "field", itemName);
	headeritem->moveUp();
	GetHeaderAttributesList();
	headerAttributesList->setCurrentItem(headerAttributesList->findItem(itemName, 0));
	headerAttributesList_selectionChanged();
}


/*!
 * \en
 *  Processes the user pressing the button " To move headers downwards "
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить заголовок вниз"
 * \_ru
*/
void dEditDoc::moveDownHeaderAttribute_clicked()
{
	aListViewItem *ai = (aListViewItem *) headerAttributesList->currentItem(), *headeritem;
	aCfg *md = item->md;
	QString itemName = ai->text(0);
	headeritem = item->findItemInMD(item, "document", md->attr(item->obj, mda_name ), "field", itemName);
	headeritem->moveDown();
	GetHeaderAttributesList();
	headerAttributesList->setCurrentItem(headerAttributesList->findItem(itemName, 0));
	headerAttributesList_selectionChanged();
}


/*!
 * \en
 *  Processes the user pressing the button " To move a field of the table upwards "
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить поле таблицы вверх"
 * \_ru
*/
void dEditDoc::moveUpTableAttribute_clicked()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	aListViewItem *ai = (aListViewItem *) tableAttributesList->currentItem(), *tableitem;
	QString itemName = ai->text(0);
	tableitem = item->findItemInMD(item, "document", md->attr( obj, mda_name ), "table", tablesList->currentText());\
	tableitem = item->findItemInMD(tableitem, "document", md->attr( obj, mda_name ), "field", itemName);	
	tableitem->moveUp();
	GetTableAttributesList();
	tableAttributesList->setCurrentItem(tableAttributesList->findItem(itemName, 0));
	tableAttributesList_selectionChanged();
}


/*!
 * \en
 *  Processes the user pressing the button " To move a field of the table downwards "
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переместить поле таблицы вниз"
 * \_ru
*/
void dEditDoc::moveDownTableAttribute_clicked()
{
	aCfg *md = item->md;
	aCfgItem obj = item->obj;
	aListViewItem *ai = (aListViewItem *) tableAttributesList->currentItem(), *tableitem;
	QString itemName = ai->text(0);	
	tableitem = item->findItemInMD(item, "document", md->attr( obj, mda_name ), "table", tablesList->currentText());
	tableitem = item->findItemInMD(tableitem, "document", md->attr( obj, mda_name ), "field", itemName);		
	tableitem->moveDown();
	GetTableAttributesList();
	tableAttributesList->setCurrentItem(tableAttributesList->findItem(itemName, 0));
	tableAttributesList_selectionChanged();
}

/*!
 * \en
 *  Activation of buttons of moving under the list at a choice of attribute of the table
 * \_en
 * \ru
 * Активация кнопок перемещения по списку при выборе поля таблицы
 * \_ru
*/
void dEditDoc::tableAttributesList_selectionChanged()
{
	aListViewItem *ai = (aListViewItem *) tableAttributesList->currentItem();
	if (!editTableAttribute->isEnabled() ) editTableAttribute->setEnabled(TRUE);
	if (!deleteTableAttribute->isEnabled() ) deleteTableAttribute->setEnabled(TRUE);
	if ( ai->nextSibling() )
	{
		if (!moveDownTableAttribute->isEnabled() ) moveDownTableAttribute->setEnabled(TRUE);
	} else {
		if (moveDownTableAttribute->isEnabled() ) moveDownTableAttribute->setEnabled(FALSE);
	}

	if ( tableAttributesList->firstChild() ==  tableAttributesList->currentItem())
	{
		if (moveUpTableAttribute->isEnabled() ) moveUpTableAttribute->setEnabled(FALSE);
	} else {
		if (!moveUpTableAttribute->isEnabled() ) moveUpTableAttribute->setEnabled(TRUE);
	}
}


void dEditDoc::eInputBasedOn_activated( const QString & )
{

}



/*!
 * \en
 *  Processes the user pressing button " Rename ". Requests a new name of the table of the user.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Переименовать". Запрашивает новое имя таблицы у пользователя.
 * \_ru
*/
void dEditDoc::renameTable_clicked()
{
	aCfgItem newobj;
	aListViewItem *tableitem;
	aCfg *md = item->md;
	aCfgItem obj = item->obj, field;
	aCfgItem cobj =md->find(obj, md_tables);
	bool ok, yes=TRUE;
	int i;
	QStringList tN;
	QString tableName, prompt = tr("Enter a new name for table:");

	for ( i = 0; i < md->count(cobj, md_table); i++ )
	{
		field = md->find( cobj, md_table, i);
		tN.append(md->attr(field, mda_name ));
	}
	while (yes)
	{
		tableName = QInputDialog::getText(
			tr("Rename table"),
			prompt,
		QLineEdit::Normal,
		QString::null, &ok, this );
		if ( ok && !tableName.isEmpty() )
		{
			if (tN.contains(tableName) == 0 )
			{
				yes=FALSE;
			}else
			{
				prompt = QString(tr("Name <b>%1</b> alredy exist.\nEnter another table name:").arg(tableName));
				yes=TRUE;
			}

		}else{
			tableName = "";
			yes=FALSE;
		}
	}

	if (tableName != "")
	{
		tableitem = item->findItemInMD(item, "document", md->attr( item->obj, mda_name ), "table", tablesList->currentText());

		for ( i = 0; i < md->count(cobj, md_table); i++ )
		{
			field = md->find( cobj, md_table, i);
			if (QString("%1").arg(md->attr(field, mda_name ))
				== tablesList->currentText() )
			{
				md->setAttr( field, mda_name, tableName );
				tableitem->setText(0, tableName);
				tablesList->setCurrentText(tableName);
				return;
			}
		}
		updateMD();

	}
}


/*!
 * \en
 *  Editing of header
 * \_en
 * \ru
 * Редактирование заголовка
 * \_ru
*/
void dEditDoc::headerAttributesList_doubleClicked( QListViewItem * )
{
    editHeaderAttribute_clicked();
}


/*!
 * \en
 *  Change of current header
 * \_en
 * \ru
 * Смена текущего заголовка
 * \_ru
*/
void dEditDoc::headerAttributesList_selectionChanged()
{
	aListViewItem *ai = (aListViewItem *) headerAttributesList->currentItem();
	if ( ai->nextSibling() )
	{
		if (!moveDownHeaderAttribute->isEnabled() ) moveDownHeaderAttribute->setEnabled(TRUE);
	} else {
		if (moveDownHeaderAttribute->isEnabled() ) moveDownHeaderAttribute->setEnabled(FALSE);
	}

	if ( headerAttributesList->firstChild() ==  headerAttributesList->currentItem())
	{
		if (moveUpHeaderAttribute->isEnabled() ) moveUpHeaderAttribute->setEnabled(FALSE);
	} else {
		if (!moveUpHeaderAttribute->isEnabled() ) moveUpHeaderAttribute->setEnabled(TRUE);
	}
	if (!editHeaderAttribute->isEnabled() ) editHeaderAttribute->setEnabled(TRUE);
	if (!deleteHeaderAttribute->isEnabled() ) deleteHeaderAttribute->setEnabled(TRUE);
}




/*!
 * \en
 * Processes the user pressing button " Remove " and deletes from metadata a requisite of a cap of the document.
 * \_en
 * \ru
 * Обрабатывает пользовательское нажатие кнопки "Удалить" и удаляет из метаданных реквизит шапки документа.
 * \_ru
*/
void dEditDoc::deleteHeaderAttribute_clicked()
{
	aCfg *md = item->md;
	aListViewItem *listItem = (aListViewItem *) headerAttributesList->currentItem(), *headeritem;

	if (headerAttributesList->childCount() == 0 )
		return;

	if (headerAttributesList->currentItem()->isSelected())
	{
		headeritem = item->findItemInMD(item, "document", md->attr( item->obj, mda_name ), "field", listItem->text(0));
	
		if ( headeritem ) {
			md->remove( listItem->obj );
			delete headeritem;
		}
		GetHeaderAttributesList();
		if (headerAttributesList->childCount() == 0 )
		{
			editHeaderAttribute->setEnabled(FALSE);
			deleteHeaderAttribute->setEnabled(FALSE);
			moveDownHeaderAttribute->setEnabled(FALSE);
			moveUpHeaderAttribute->setEnabled(FALSE);
		}
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
dEditDoc::moveToTopLeftCorner()
{
	this->parentWidget()->setGeometry( 0, 0, 
		this->parentWidget()->frameSize().width(),
		this->parentWidget()->frameSize().height());

}
