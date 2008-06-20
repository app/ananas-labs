/****************************************************************************
** $Id: awidget.cpp,v 1.4 2007/09/18 11:58:23 app Exp $
**
** Code file of the Ananas visual bject of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Library of the Ananas
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

#include <qobject.h>
#include <qsqlcursor.h>
#include <qsqlpropertymap.h>
#include <qdialog.h>
#include "adatabase.h"
#include "awidget.h"
#include "wfield.h"
#include "wdbfield.h"
#include "wdbtable.h"
#include "aform.h"
#include "alog.h"


/*!
 *\en
 *	Abstract Ananas widget object.
 *\_en
 *\ru
 *	Конструктор, создающий абстрактный объект. Абстрактность в данном случае означает 
 *	отстутствие привязки к базе данных. \n
 *	Вызывает конструктор базового класса QWidget.
 *	\param parent - указатель на родительский виджет.
 *	\param name - имя создаваемого объекта.
 *	\param fl - флаги используемые при создании виджета. Передаются в конструктор базового класса.
 *\_ru
 */
aWidget::aWidget( QWidget *parent, const char *name, WFlags fl )
:QWidget( parent, name, fl )
{
	vId = 0;
	db = 0;
        dbobj = 0;
	engine = 0;
	vFormMode = 0;
	vInited = false;
}

/*!
 * \ru
 * 	Конструктор, использующий для создания объекта имя элемента метаданных.\n
 * 	У класса есть также конструктор, использующий для создания объекта ссылку на объект с описанием элемента метаданных.
 * 	\param itemname - имя элемента метаданных.
 * 	\param adb - ссылка на объект доступа к базе данных.
 * 	\param parent - указатель на родительский виджет (передается в конструктор базового класса).
 * 	\param name - имя создаваемого объекта (передается в конструктор базового класса).
 * 	\param fl - флаги, используемые конструктором базового класса.
 * \_ru
 */
aWidget::aWidget( const QString &itemname, aDatabase *adb, QWidget *parent, const char *name, WFlags fl )
:QWidget( parent, name, fl )
{
	vId = 0;
        dbobj = 0;
	vInited = false;
	engine = 0;
	vFormMode = 0;
	if ( adb ) {
		obj = adb->cfg.find( itemname );
		init( adb );
	}
}


/*!
 * \ru
 * 	Конструктор, использующий для создания объекта ссылку на объект элемента метаданных.\n
 * 	У класса есть также конструктор, использующий для создания объекта имя элемента метаданных.
 * 	\param context - ссылка на объект элемента метаданных.
 * 	\param adb - ссылка на объект доступа к базе данных.
 * 	\param parent - указатель на родительский виджет (передается в конструктор базового класса).
 * 	\param name - имя создаваемого объекта (передается в конструктор базового класса).
 * 	\param fl - флаги, используемые конструктором базового класса.
 * \_ru
 */
aWidget::aWidget( aCfgItem context, aDatabase *adb, QWidget *parent, const char *name, WFlags fl )
:QWidget( parent, name, fl )
{
	vId = 0;
        dbobj = 0;
	vInited = false;
	engine = 0;
	obj = context;
	vFormMode = 0;
	init( adb );
}

aWidget::~aWidget()
{

}



/*!
 *\en
 *	Create database object.
 *\_en
 *\ru
 *	Пока ничего не делает. Возвращает 0;
 *\_ru
 */
aObject *
aWidget::createDBObject(  aCfgItem , aDatabase * )
{
	return 0;
}




/*!
 *\en
 *	Create toolbar for QMainWindow owner object.
 *\_en
 *\ru
 *	Пока ничего не делает. Возвращает 0;
 *\_ru
 */
QToolBar*
aWidget::createToolBar( QMainWindow * )
{
	return 0;
}


/*!
 *\ru
 *	Если объект не был проинициализирован, вызывает initObject(adb).
 *\_ru 
 */

void
aWidget::init( aDatabase *adb )
{
	if ( isInited() ) return;
//	aWidget *pc = parentContainer( this );
//	if ( pc ) if ( !pc->isInited() ) pc->init( adb );
	initObject( adb );
}



/*!
 *\en
 *	Init object after create.
 *	Need setId( id ), where id - if of the metadata object of the adb->cfg loaded Configuration.
 *\_en
 *\ru
 *	Инизиализирует созданный объект.
 *	Необходимо выполнить setId(id), где id идентификатор обекта в конфигурации.
 *\_ru
 *\param adb - \en ananas database object. \_en \ru объект доступа к базе данных. \_ru
 */
void
aWidget::initObject( aDatabase *adb )
{
//	printf("init object, object type = %s\n",(const char*) className() );
	aCfgItem fg, f;
//	int i, n;
//	long idf;
	QString tname;

	debug_message("Init aWidget name=%s FormType=%i\n", ( const char *) name(), formMode() );
	// Init myself.
	setInited( true );
	QSqlPropertyMap *pm = new QSqlPropertyMap();
	db = adb;
	md = 0;
	if ( db ) md = &db->cfg;
	else return;
	if ( obj.isNull() ) {
		obj = md->find( getId() );
	};
	form = new QSqlForm( this );
	pm->insert("wDBField","value");
	form->installPropertyMap( pm );
	if ( obj.isNull() ) return;
	dbobj = createDBObject( obj, adb );

	QObjectList *l = this->queryList( "wDBTable" );
	QObjectListIt it( *l );
	QObject *obj;
	while ( (obj = it.current()) != 0 )
	{
	CHECK_POINT
		++it;
		connect( this, SIGNAL( changeObj(const QString &) ),
				//(wDBTable*)
				obj, SLOT( newFilter(const QString &) ));
		connect( this, SIGNAL( changeObjId(const Q_ULLONG) ),
				//(wDBTable*)
				obj, SLOT( newDataId(const Q_ULLONG) ));
	}
	delete l; // delete the list, not the objects
}



/*!
 *\~english
 *\~russian
 *\~
 */
 /*
void
aWidget::formInsert( QWidget *widget, const QString &field )
{
	form->insert( widget, field );
}
*/


/*!
 *\~english
 *\~russian
 *\~
 */
/*
void
aWidget::formRemove( const QString &field )
{
	form->remove( field );
}
*/


/*!
 *\en
 *\_en
 *\ru
 *	Ничего не делает. Возвращает false.
 *\_ru
 */
bool
aWidget::checkStructure()
{
	return false;
}



/*!
 *\en
 *\_en
 *\ru
 *	Возвращает значение свойства vName.
 *\_ru
 */
QString
aWidget::getName() const	{
//	if (vName.isEmpty()) return name();
	return vName;
}



/*!
 *\en
 *\_en
 *\ru
 *	Устанавливает значение свойства vName.
 *\_ru
 */
void
aWidget::setName(QString fn){
	vName = fn;
}



/*!
 *\en
 *\_en
 *\ru
 *	Ничего не делает. Возвращает 0.
 *\_ru
 */
QDialog*
aWidget::createEditor( QWidget * )
{
	return 0;
}



/*!
 *\en
 *\_en
 *\ru
 *	Вызывает редактор свойств, если значение передаваемого параметра равно true.
 *	Редактор свойств предоставляет пользователю диалог задания значений свойств виджета.
 *	Например, для такого виджета как wDBField редактор свойств позволяет выбрать элемент метаданных
 *	описывающий поле базы данных, значение которого будет редактироваться с использованием виджета.
 *	То есть осуществить привязку данных (data bindings).
 *\param fn - параметр, значение которого должно быть равно true, для того чтобы был вызван
 *	редактор свойств.
 *\_ru
 */
void
aWidget::setOpenEditor( bool fn )
{
	if(fn) widgetEditor();
}



/*!
 *\en
 *	Emit signal setData( object, md ).
 *\_en
 *\ru
 *	Посылает сигнал setData( object, md ).
 *\_ru
 */
void
aWidget::setObjectData( QWidget *object, aCfg *md )
{
        emit( setData( object, md ) );
}



/*!
 *\en
 *	Emit signal getData( object ).
 *\_en
 *\ru
 *	Посылает сигнал getData( object ).
 *\_ru
 */
void
aWidget::getObjectData( QWidget *object )
{
        emit( getData( object ) );
}



/*!
 *\en
 *	Return toplevel metadata configuration.
 *\_en
 *\ru
 *	Возвращает объект конфигурации для виджета верхнего уровня.
 *\_ru
 */
aCfg*
aWidget::getMd()
{
	aCfg *md = 0;
	QWidget *mw = topLevelWidget();
	if (mw->name() == QString("ananas-designer_mainwindow") ) {
		connect( this, SIGNAL( getMd( aCfg ** ) ), mw, SLOT( getMd( aCfg ** ) ));
		emit ( getMd( &md ) );
	}
	return md;
}



/*!
 *\~english
 *	Get id from database.
 *	Get id for current database record or 0 if database object not created.
 *\~russian
 *	Возвращает id объекта базы данных.
 *	Возвращает id текущей записи в базе данных или 0 если обект
 *	для работы с базой не создан. Id является уникальным и идентифицирует конкретный
 *	экземпляр обекта.
 *\~
 *\return \~english current database record id\~russian id текущей записи в базе данных.\~
 */
Q_ULLONG
aWidget::uid()
{
	if ( dbobj )
	{
		return dbobj->getUid();
	}
	else
	{
		aLog::print(aLog::MT_ERROR, tr("aWidget::uid dbobj is NULL"));
		return 0;
	}
}



/*!
 *\~english
 *\~russian
 *\~
 */
void
aWidget::widgetEditor()
{
	aWidget::widgetEditor( this, createEditor( topLevelWidget() ) );
}



/*!
 *\~english
 *\~russian
 *\~
 */
void
aWidget::widgetEditor(  QWidget *object, QDialog *editor )
{
        aCfg *md = 0;
	QWidget *mw = object->topLevelWidget();
        aWidget o( mw );
	if ( mw->name() == QString( "ananas-designer_mainwindow" ) ) {
                md = o.getMd();
		if ( !md ) return;
		if ( editor ) {
			connect( &o, SIGNAL( setData( QWidget *, aCfg* ) ), editor, SLOT( setData( QWidget *, aCfg* ) ) );
			connect( &o, SIGNAL( getData( QWidget * ) ), editor, SLOT( getData( QWidget * ) ) );
			o.setObjectData( object, md );
			if ( editor->exec() == QDialog::Accepted )
			{
				o.getObjectData( object );
			};
			delete editor;
		}
	}
}



/*!
 *\~english
 *\~russian
 *\~
 */
aWidget *
aWidget::parentContainer( QWidget *w )
{
//	aForm *f = parentForm( w );
//	if ( f ) w = f->parentContainer( w );
//	else w = 0;

        while ( w ) {
                w = w->parentWidget();
                if ( w ) {
					if ( w->inherits("aWidget") ) break;
				}
        }
//	if ( !w ) {
//		aForm *f = parentForm( w );
//		if ( f ) w = f->mainWidget;
//	}
        return ( aWidget *) w;
}



/*!
 *\~english
 *\~russian
 *\~
 */
aForm *
aWidget::parentForm( QWidget *w )
{
        while ( w )
	{
			//CHECK_POINT
			//printf("%s\n",(const char*)w->className());
                if ( w->inherits("aForm") ) break;
                w = w->parentWidget(true);
        }
        return ( aForm *) w;
}



/*!
 *\~english
 *\~russian
 *\~
 */
aCfgItem *
aWidget::getMDObject()
{
    return &obj;
}



/*!
 *\~english
 *\~russian
 *\~
 */
void
aWidget::setMDObject( aCfgItem object )
{
    obj = object;
}



/*!
 *\~english
 *\~russian
 *\~
 */
aSQLTable *
aWidget::table( const QString &name )
{
        if ( dbobj ) return dbobj->table( name );
        return 0;
}

/*
bool
aWidget::tableInsert( const QString &name )
{
	if ( db ) {
		aSQLTable *t = db->table( name );
		if ( !t ) return false;
		dbtables.insert( name, t );
		return true;
	}
	return false;
}


bool
aWidget::tableRemove( const QString &name )
{
	dbtables.remove( name );
	return true;
}
*/



/*!
 *\~english
 *\~russian
 *\~
 */
QString
aWidget::displayString()
{
	return "";
}




/*!
 *\~english
 *	Create new database record object.
 *	New object create with using wirtual function aObject::New() of aObject
 *	and it's childs.
 *\~russian
 *	Создает новый объект для работы с записями базы данных.
 *	Объект создается испоьлзуя виртуальную функцию aObject::New() объекта aObject
 *	и его потомков.
 *\~
 *\return \~engilsh error code. \~russian код ошибки.\~
 */
ERR_Code
aWidget::New()
{
	if ( dbobj ) return dbobj->New();
	else return err_abstractobj;
}



/*!
 *\~english
 *	Select object in database.
 *\~russian
 *	Выбирает объект в базе данных.
 *\~
 *\param id -\~english database record id.\~russian id объекта в базе данных.\~
 *\return \~english error code.\~russian код ошибки.\~
 */
ERR_Code
aWidget::Select( Q_ULLONG id )
{
	if ( dbobj ) return dbobj->select( id );
	else return err_abstractobj;
}



/*!
 *\~english
 *\~russian
 *\~
 */
ERR_Code
aWidget::Update()
{
	if ( dbobj ) return dbobj->Update();
	else return err_incorrecttype;
}

/*!
 *\~english
 *\~russian
 *\~
 */
ERR_Code
aWidget::Refresh()
{
	QString fname;
	QObjectList *l = this->queryList( "wDBField" );
	QObjectListIt it( *l );
	QObjectList *tl = this->queryList( "wDBTable" );
	QObjectListIt tit( *tl );
	aWidget *obj;
	while ( (obj = (aWidget*) it.current()) != 0 ){
		++it;
		fname= obj->getFieldName();
		obj->setValue(dbobj->Value(fname).toString());
	}
	delete l; // delete the list, not the objects
	
	while ( (obj = (aWidget*) tit.current()) != 0 ){
		++tit;
		((QDataTable*)obj)->refresh();
	}
	delete tl; // delete the list, not the objects
	
	return err_noerror;
}


/*!
 *\~english
 *\~russian
 *\~
 */
ERR_Code
aWidget::TurnOn()
{
	return err_incorrecttype;
}



/*!
 *\~english
 *	Get field value.
 *	get value for field with such name.
 *\~russian
 *	Возвращает значение поля.
 *	Возвращает значение поля с именем name.
 *\~
 *\param name - \~english field md name. \~russian имя поля в конфигурации.\~
 *\return \~english field value. \~russian значение поля.\~
 */
QVariant
aWidget::value( const QString & name )
{
	if ( dbobj ) return dbobj->Value(name);
	else return QVariant("");
}


/*!
 *\~english
 *\~russian
 *\~
 */
bool
aWidget::isContainer()
{
	return false;
}



/*!
 *\~english
 *	Seting widget readonly flag.
 *	When widget readonly it's fields can't be edit, and make updatе action
 *\~russian
 *	Устанавливает флаг толко чтение.
 *	Когда установлен этот флаг, запрещается редактирование полей виджета,
 *	и сохранение изменений в базу.
 *\~
 *\param status - \~english New readonly flag.\~russian Новое значение флага только чтение.\~
 */
void
aWidget::SetReadOnly ( bool status )
{
//CHECK_POINT
	QObjectList *l = this->queryList( "wField" );
//CHECK_POINT
	QObjectListIt it( *l );
//CHECK_POINT
	QObject *obj;
//CHECK_POINT
	while ( (obj = it.current()) != 0 )
	{
//	CHECK_POINT
		++it;
		(( wField *)obj)->setDisabled( status );
	}
	delete l; // delete the list, not the objects
	l = this->queryList( "aWidget" );
	QObjectListIt itl( *l );
	while ( (obj = itl.current()) != 0 )
	{
//	CHECK_POINT
		++itl;
		(( aWidget *)obj)->SetReadOnly( status );
	}
	delete l; // delete the list, not the objects
	l = this->queryList( "QFrame" );
	QObjectListIt tl( *l );
	while ( (obj = tl.current()) != 0 )
	{
//		printf("QFrame classname '%s'\n", (const char*) obj->className() );
		++tl;
		if (obj->inherits("QTable")) (( QTable * )obj)->setReadOnly(true);
		else (( QFrame *)obj)->setDisabled( status );
	}
	delete l; // delete the list, not the objects
}


/*!
 *
 */
Q_ULLONG
aWidget::docId()
{
	if ( dbobj )
	{
CHECK_POINT
	return dbobj->docId();
	}
	else return 0;
}
