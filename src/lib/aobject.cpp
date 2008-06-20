/****************************************************************************
** $Id: aobject.cpp,v 1.98 2008/05/04 08:04:53 app Exp $
**
** Code file of the Ananas Object of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2005-2006 Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola.
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
#include "aobject.h"
#include "aform.h"
#include "alog.h"


/*!
 *	\en
 *	Creates abstract aObject.
 *
 *	\param parent - parent object
 *	\param name - name of object
 *	\_en
 *	\ru
 *	\brief	Конструктор для создания абстрактного объекта.
 *
 *	Создает абстрактный не связанный с базой данных объект управления данными.
 *	Созданный таким образом объект не использует информацию из метаданных о составе и
 *	типах полей. То есть он не является какой-либо моделью данных. И на самом деле малопригоден
 *	для использования. В базе данных ни как не отражается создание этого объекта. Для того,
 *	что бы зарегистрировать вновь созданный абстрактный объект в базе данных, необходимо
 *	сначала проинициализировать его с использованием метаданных, а затем вызвать метод New().
 *
 *	\param parent - родительский объект в терминологии Qt (смотри QObject::QObject)
 *	\param name - имя объекта в терминологии Qt (смотри QObject::QObject)
 *	\_ru
 */
aObject::aObject( QObject *parent, const char *name )
:QObject( parent, name )
{
	db = 0;
	vInited = false;
	filtred = false;
	selectFlag = false;
	lastErrorCode = 0;
	lastErrorMessage = "";
}



/*!
 *	\en
 *	Create aObject, inited by md object.
 *	md object finding by name
 *	\param oname - md name of object, name contens prefix
 *				Document. for documents,
 *				InfoRegister. for information registers,
 *				Catalogue. for catalogues,
 *				AccumulationRegister. for Accumulation registers,
 *				DocJournal. for journals
 *	\param adb - link on object aDataBase used for work
 *	\param parent - parent object
 *	\param name - name of object
 *	\_en
 *	\ru
 *	\brief Создает объект как модель данных, описанную в метаданных. 
 *
 *	Используется главным образом конструкторами унаследованных классов.	
 *	На описание в метаданных указывает один из передаваемых при вызове 
 *	параметров - имя элемента метаданных.
 *	После успешного создания объекта с ним можно работать как с объектом данных со структурой,
 *	описанной в метаданных, и индентифицируемой именем, переданным в параметрах вызова.
 *
 *	\param oname - имя объекта метаданных с добавленным префиксом в начале. 
 *	Допускаются следующие значения префикса:
 *				"Document."  для документов,
 *				"InfoRegister." для информационных регистров,
 *				"Catalogue." для справочников,
 *				"AccumulationRegister." для накопительных регистров,
 *				"DocJournal." для журналов
 *	\param adb - ссылка на объект, представляющий базу данных. Значение 0 (ноль)
 *	говорит, что следует использовать текущую базу данных.
 *	\param parent - родительский объект в терминологии Qt (смотри QObject::QObject)
 *	\param name - имя объекта в терминологии Qt (смотри QObject::QObject)
 *	\see aCfg::find( const QString &)
 *	\_ru
 */
aObject::aObject( const QString &oname, aDatabase *adb, QObject *parent, const char *name )
:QObject( parent, name )
{
	vInited = false;
	filtred = false;
	selectFlag = false;
	lastErrorCode = 0;
	lastErrorMessage = "";
	db = adb;
	if ( adb )
	{
		obj = adb->cfg.find( oname );
		if ( obj.isNull() )
		{
			setLastError( err_objnotfound, tr("Metadata object '%1' not found").arg(oname) );
		} 
		else 
		{
			setObject( obj );
		}
	}
}



/*!
 *	\en
 *
 *		\brief Creates aObject, inited by md object.
 *
 *		\param context - high level md object
 *		\param adb - link on object aDataBase used for work
 *		\param parent - parent object
 *		\param name - name of object
 *	\_en
 *	\ru
 *		\brief Создает объект как модель данных, описанную в метаданных. 
 *
 *		Объект создается по контексту метаданных, которому он принадлежит.
 *
 *		\param context - Контекст(объект) метаданных, которому принадлежит (как ветвь дерева)
 *		создаваемый объект.
 *		\param adb - ссылка на объект, представляющий базу данных. Значение 0 (ноль)
 *		говорит, что следует использовать текущую базу данных.
 *		\param parent - родительский объект в терминологии Qt (смотри QObject::QObject)
 *		\param name - имя объекта в терминологии Qt (смотри QObject::QObject)
 *	\_ru
 */
aObject::aObject( aCfgItem context, aDatabase *adb, QObject *parent, const char *name )
:QObject( parent, name )
{
	filtred = false;
	vInited = false;
	selectFlag = false;
	lastErrorCode = 0;
	lastErrorMessage = "";
	db = adb;
	if ( adb )
	{
		setObject( context );
	}
}



/*!
 *	\en
 *		\brief Virtual destructor.
 *	\_en
 *	\ru
 *		\brief Виртуальный деструктор
 *	\_ru
 */
aObject::~aObject()
{
}



/*!
 *	\en
 *		\brief Tune on metadata object and it's database tables.
 *
 *		\return error code
 *	\_en
 *	\ru
 *		\brief Вспомогоательный метод. Проверяет необходимость вызова метода initObject()
 *		и вызывает его.	
 *
 *		\return код ошибки
 *	\_ru
 */
ERR_Code
aObject::init()
{
	if ( isInited() ) return err_noerror;
	return initObject();
}


/*!
 *	\en
 *		\brief Sets new object type after create
 *
 *		\param newobject - new md object
 *		\return error code
 *	\_en
 *	\ru
 *		\brief Задает метатип объекта. 
 *
 *		Используется в процессе создания/инициализации объекта.
 *		Метатип - это описание объекта в метаданных, узел дерева метаданных.
 *
 *		\param newobject - метатип, присваиваемый объекту
 *		\return код ошибки
 *	\_ru
 */
ERR_Code
aObject::setObject( aCfgItem newobject )
{
	setInited( false );
	obj = newobject;
	return init();
}


/*!
 *	\en
 *		\brief Init object after create.
 *
 *		Need setObject( id ), where id - if of the metadata object of the adb->cfg loaded Configuration.
 *
 *		\return error code
 *	\_en
 *	\ru
 *		\brief Инициализирует объект при его создании.
 *
 *		\return код ошибки
 *	\_ru
 */
ERR_Code
aObject::initObject()
{
	if ( isInited() ) 
	{
		aLog::print(aLog::MT_DEBUG, tr("aObject::initObject() - Object allready initialized! Skip init."));
		return err_noerror;
	} 
	aLog::print(aLog::MT_DEBUG, tr("aObject::initObject() - First init."));
	

	aCfgItem fg, f;
	QString tname;

	setInited( true );
//	db = adb;
	md = 0;
	if ( db ) md = &db->cfg;
	else
	{
		setLastError( err_nodatabase, tr("aObject have no database!"));
		return lastErrorCode;
	}
	if ( obj.isNull() )
	{
		return err_objnotfound;
	}
	return err_noerror;
}


/*!
 *	\brief Not implemented
 *	\returns false
 */
bool
aObject::checkStructure()
{
	return false;
}


/**
 *	\en
 *		\brief Return the table of object by it's name.
 *
 *		\param name - name of table for main table use name="" or empty parameter
 *		\return link on aDataTable or 0 if table not found
 *	\_en
 *	\ru
 *		\brief Возвращает одну из таблиц бизнес-объекта по ее имени.
 *
 *		Для хранения в базе данных значений свойств бизнес-объектов Ананаса, 
 * 		таких как документы, каталоги, журналы используется одна или 
 *		несколько реляционных таблиц. 
 * 		Каждая такая таблица представлена объектом aDataTable, 
 * 		а список указателей на объекты aDataTable проинициализированного 
 * 		экземпляра бизнес-объекта хранится в его свойстве dbtables. Инициализация
 * 		и наполнение dbtables осуществляется наследниками aObject.
 *		Метод возвращает ссылку на объект aDataTable с именем, соответствующим значению,
 * 		переданному в параметре. 
 *		Вызов метода без параметров, аналогичен вызову метода с пустой строкой table("");
 * 		В этом случае метод вернет объект aDataTable представляющий главную таблицу бизнес-объекта.
 * 		Главная таблица используется для хранения значений свойств 
 * 		не табличных частей бизнес-объекта. Например, реквизитов шапки и подвала документа.
 * 		Такой объект хранит все значения ровно в одной записи.
 *		Таким образом, вызов table() без параметров позволяет получить объект aDataTable для доступа к 
 * 		основным свойствам бизнес-объекта.
 *		\param name - имя таблицы. Для доступа к главной таблице бизнес-объекта 
 * 			пареметр должен быть равен "" или пропущен.
 *		\return ссылку на объект aDataTable или 0 если таблица не найдена.
 *	\_ru
 * 	\see aDatabase::table( const QString & )
 */
aDataTable *
aObject::table( const QString &name )
{
	if ( !dbtables[ name ] )
	{
		if (name!="" && !name.isEmpty())
		{
			setLastError( -1, tr("aObject table with name %1 not found").arg(name));
			cfg_message(1, tr("Table `%s' not found.\n").utf8(),(const char*) name);
		}
	//	else 
	//	{
	//		cfg_message(1, tr("Table name is empty.\n").utf8());
	//	}
		return 0;
	}
	return dbtables[ name ];
}


/*!
 *	\brief Insert table name and its link into internal buffer.
 *
 *	Buffer used for finding table by its md name.
 *	\param dbname - database name of table
 *	\param obj - md object, used for aDataTable initing
 *	\param name - name of table, used for finding table in buffer
 *	\return error code
 */
ERR_Code
aObject::tableInsert( const QString &dbname,  aCfgItem obj, const QString &name )
{
	if ( db )
	{
		aDataTable *t = db->table( dbname );
		if ( !t ) 
		{
			setLastError( err_notable, tr("aObject::tableInsert - can't insert table"));
			return lastErrorCode;
		}
		t->setObject( obj );
		dbtables.insert( name, t );
		return err_noerror;
	}
	setLastError( err_nodatabase, tr("aObject have no database!"));
	return lastErrorCode;
}



/*!
 *	\brief Insert table name and its link into internal buffer.
 *
 *	Buffer used for finding table by its md name.
 *	table not inited by md object
 *	\param dbname - database name of table
 *	\param name - name of table, used for finding table in buffer
 *	\return error code
 */
ERR_Code
aObject::tableInsert( const QString &dbname, const QString &name )
{
	if ( db ) {
		aDataTable *t = db->table( dbname );
		if ( !t ) 
		{
			setLastError( err_notable, tr("aObject::tableInsert - can't insert table"));
			return lastErrorCode;
		}
		dbtables.insert( name, t );
		return err_noerror;
	}
	setLastError( err_nodatabase, tr("aObject have no database!"));
	return lastErrorCode;
}


/*!
 *	\brief Remove table from buffer.
 *	\param name - table name
 *	\return err_notable if table not found
 */
ERR_Code
aObject::tableRemove( const QString &name )
{
	if ( !dbtables[name] )
	{
		setLastError( err_notable, tr("aObject table with name %1 not found").arg(name));
		return lastErrorCode;
	}
	dbtables.remove( name );
	return err_noerror;
}


/*!
 *	\brief Not implemented
 *	\return ""
 */
QString
aObject::trSysName( const QString & )
{
	return "";
}


/*!
 * \brief Gets system field value.
 * \param name (in) -  field name.
 * \return field value or QVariant::Invalid if field no exist.
 */
QVariant
aObject::sysValue( const QString & name, const QString &tableName )
{
	aDataTable *t = table( tableName );
	if ( t && t->sysFieldExists( name ) )
	{
		return	t->sysValue(name);
	}
	else return QVariant::Invalid;
}


/*!
 * \brief Sets system field value.
 * \param name (in) - field name.
 * \param value (in) - sets value.
 */
int
aObject::setSysValue( const QString & name, QVariant value, const QString &tableName )
{
	aDataTable *t = table( tableName );
	if ( t )
	{
		t->setSysValue( name, value );
		return err_noerror;
	}
	return err_notable;
}


/*!
 *	\brief Return field value of the primary object database table.
 *	\param name (in) - field name
 *	\param tableName (in) - name of table field belongs to. Optional.
 *	default value - "".
 *	\return field value
 */
QVariant
aObject::Value( const QString & name, const QString &tableName )
{

        aDataTable *t = table( tableName );
	QString trName = trSysName(name);

	if ( trName != "" ) return sysValue( trName );
	else 
	{
	        if ( t ) return t->value( name );
	}
        return QVariant("");
}


/*!
 *	\brief Set field value of the primary object database table.
 *	\param name - field name
 *	\param value - field value
 *	\param tableName (in) - name of table field belongs to. Optional.
 *	default value - "".
 *	\return error code
 */
int
aObject::SetValue( const QString & name, const QVariant &value, const QString &tableName )
{
	aDataTable *t = table( tableName );
	QString trName = trSysName(name);

	if ( trName != "" ) return setSysValue( trName, value );
	else
	{
		if ( t )
		{
			t->setValue( name, value );
			return err_noerror;
		}

	}
	return err_notable;
//	return setTValue( "", name, value );
}


/*!
 *	\brief Checks if object selected.
 *	\return true if object record selected in database.
 */
bool
aObject::IsSelected()
{
	return selected();
}


/*!
 *	\brief Checks "Deleted" marker
 *	\return true if record marked as deleted or false if not.
 */
bool
aObject::IsMarkDeleted(const QString & tname)
{
        aDataTable *t = table( tname );
        if ( t && t->sysFieldExists( "df" ) ) return t->sysValue( "df" ).toInt() == 1;
        return false;
}


/*!
 *	\brief Checks "Marked" marker
 *	\return true if record marked or false if not.
 *	\see aObject::SetMarked()
 */
bool
aObject::IsMarked()
{
        aDataTable *t = table();
        if ( t && t->sysFieldExists( "mf" ) ) return t->sysValue( "mf" ).toInt() == 1;
        return false;
}


/*!
 *
 */
/*
int
aObject::TableSetMarkDeleted( bool Deleted, const QString & tname )
{
        aDataTable *t = table( tname );
        if ( t && t->sysFieldExists( "df" ) ) {
                QString v = "0";
                if ( Deleted ) v = "1";
                t->setSysValue( "df", QVariant( v ) );
                return err_noerror;
        }
        return err_incorrecttype; // Object can not be mark deleted
}
*/


/*!
 *	\brief Устанавливает признак логического удаления объекта (записи SQL таблицы)
 *	\return код ошибки
 */
int
aObject::SetMarkDeleted( bool Deleted, const QString & tname )
{
	aDataTable *t = table( tname );
	if ( t && t->sysFieldExists( "df" ) )
	{
		QString v = "0";
		if ( Deleted ) v = "1";
		t->setSysValue( "df", QVariant( v ) );
		return err_noerror;
	}
	else
	{
		setLastError( err_incorrecttype, tr("aObject have no system field %1").arg("df"));
		return lastErrorCode; // Object can not be mark deleted
	}
}


/*!
 *	\brief Выставляет отметку на объекте.
 *	\return код ошибки.
 *	\see aObject::IsMarked()
 */
int
aObject::SetMarked( bool Marked )
{
	aDataTable *t = table();
	if ( t && t->sysFieldExists( "mf" ) ) {
			QString v = "";
			if ( Marked ) v = "1";
			t->setSysValue( "mf", QVariant( v ) );
//                t->printRecord();
			return err_noerror;
	}
	setLastError( err_incorrecttype, tr("aObject have no system field %1").arg("mf"));
	return lastErrorCode; // Object can not be marked
}


/*!
 *	\brief Add new object record in database.
 *	\return error code
 */
int
aObject::New()
{
	aDataTable *t = table();

	if ( !t ) return err_notable;
	setSelected ( t->New() );
/*	Q_ULLONG Uid = t->primeInsert()->value("id").toULongLong();
	if ( t->insert() )
	{
		if ( t->select(QString("id=%1").arg(Uid), false) )
			if ( t->first() )
			{
				setSelected(true);
				return err_noerror;
			}
		return err_selecterror;
	}
*/	if ( selected() ) return err_noerror;
	return err_inserterror;
}


/*!
 * Copy current selected object data in database.
 */
/*Q_ULLONG
aObject::copy( const QString & tablename )
{
	aDataTable * t = table( tablename );

	if ( !t ) return 0;
	if ( !selected(tablename) ) return 0;
	QSqlRecord * r = t->primeUpdate();
	Q_ULLONG Uid = db->uid( t->id );
	r->setValue("id",Uid);
	if ( t->insert() ) return Uid;
	else return 0;
}
*/


/*!
 * \ru
 * 	\brief Создает новый объект, являющийся клоном текущего объекта.
 *
 * 	\return err_copyerror в случае возникновения ошибки или err_noerror в случае успешного выполнения.
 * \_ru
 */
int
aObject::Copy()
{
	aDataTable *t = table();
	if ( t->Copy() ) return err_noerror;
	return err_copyerror;
}


/**
 * \en
 * 	\bried Deletes curent selected object record from database.
 * \_en
 * \ru
 * 	\brief Удаляет текущий объект из базы данных.
 *	\return код ошибки
 * \_ru
 */
int
aObject::Delete()
{
	aDataTable * t = table();
	if ( !t ) return err_notable;
	db->markDeleted(getUid());
	t->Delete();
//	if ( !selected() ) return err_notselected;
//	t->primeDelete();
//	t->del();
	setSelected (false);
	return err_noerror;
}


/*!
 *	\en
 *		\brief Update curent selected object record to database.
 *		\return error code
 *	\_en
 *	\ru
 *		\brief Обновляет запись в базе данных текущеми значениями.
 *		\return код ошибки
 *	\_ru
 *
 */
int
aObject::Update()
{
	aDataTable *t = table();
	QSqlRecord *r;
	int i;

	if ( !t ) return err_notable;
	t->Update();
/*
	r = t->primeUpdate();
	t->printRecord();
	for ( i=0;i<r->count();i++ ) r->setValue( i, t->value( i ) );

	t->update();
*/
	if ( t->lastError().type() )
	{
		setLastError( err_updateerror, tr("aObject update error. Driver message: %1").arg(t->lastError().text()) );
		return lastErrorCode;
	}
	else 
	{
		return err_noerror;
	}
}


/*!
 *\~english
 *	Update object attributes from curent selected object database record.
 *\~russian
 *\~
 *//*
void
aObject::updateAttributes( const QString & tname )
{
	aDataTable *t = table();

}
*/


/*!
 *	\en
 *		\brief Conducts document.
 *
 *		Have to be reimplemented. Added for wDocument compatibility.
 *		\return error code - abstract object - err_abstractobj.
 *	\_en
 *	\ru
 *		\brief Проводит документ.
 *
 *		Следует переопределить в наследующем классе.
 *		Предназначена для wDocument.
 *		\return код ошибки - абстрактный обект - err_abstractobj.
 * \_ru
 */
int
aObject::Conduct()
{
	return err_abstractobj;
}


/*!
 *	\en
 *		\brief Unconducts document.
 *
 *		Have to be reimplemented. Added for wDocument compatibility.
 *		\return error code - abstract object - err_abstractobj.
 *	\_en
 *	\ru
 *		\brief Отменяет проведение документа.
 *
 *		Следует переопределить в наследующем классе. 
 *		Предназначена для wDocument.
 *		\return код ошибки - абстрактный обект - err_abstractobj.
 * \_ru
 */
int
aObject::UnConduct()
{
	return err_abstractobj;
}


/*!
 *	\en
 *		\brief Checks if document has been conducted.
 *
 *		Have to be overrided. Added for wDocument compatibility.
 *		\return error code - abstract object - err_abstractobj.
 *	\_en
 *	\ru
 *		\brief Проверяет проведен ли документ.
 *
 *		Ничего не делает. Следует переопределить в наследующем классе.
 *		Предназначена для wDocument.
 *		\return код ошибки - абстрактный обект - err_abstractobj.
 * \_ru
 */
bool
aObject::IsConducted()
{
	return 0;
}


/*!
 *	\en
 *		\brief Returns document database id.
 *
 *		Always return 0. Have to be overrided. Added for wJournal compatibility.
 *		\return 0
 *	\_en
 *	\ru
 *		\brief Возвращает id документа в базе данных.
 *
 *		Всегда возвращает 0. Следует преопределить в наследующем классе.
 *		Предназначена для совместимости и работы в wJournal.
 *		\return 0
 *	\_ru
 */
Q_ULLONG
aObject::docId()
{
	return 0;
}


/*!
 * \ru
 *		\brief Позиционирует указатель в БД на запись, соотвествующую объекту
 *	с указанным идентификатором.
 *	\param id - Идентификатор объекта.
 * 	\return возвращает код ошибки или 0 в случае успеха.
 * \_ru
 */
ERR_Code
aObject::select( Q_ULLONG id )
{
	aDataTable * t = table();
	if ( !t ) return err_notable;
	setSelected (false);
	long otype = db->uidType( id );
//	debug_message("otype=%li\n",otype);
	if ( !otype ) return err_objnotfound;
	if ( concrete && ( otype != t->getMdObjId() ) ) return err_incorrecttype;
	if ( !concrete )
	{
		aCfgItem tmpObj = md->find( otype );
		if ( tmpObj.isNull() ) return err_objnotfound;
		setObject ( tmpObj );
	}
	if ( t->select( QString("id=%1").arg(id), false ) )
		if ( t->first() )
		{
//			t->primeUpdate();
			setSelected (true);
//			t->printRecord();
			return err_noerror;
		}
		else return err_notselected;
	return err_selecterror;
}



/*!
 *	\brief Осуществляет SQL запрос.
 *	
 *	В случае успешного выполнения запроса, первая запись таблицы результатов становится текущей.
 *	\return код ошибки
 */
ERR_Code
aObject::select(const QString & query, const QString &tableName)
{
	aDataTable * t = table(tableName);
	if ( !t ) return err_notable;
	if (t->select(query))
		if( t->first() )
		{
			setSelected (true);
			return err_noerror;
		}
		else return err_notselected;
	return err_selecterror;
}


/*!
 *		\brief Return field value of the secondary object database table.
 */
QVariant
aObject::tValue( const QString & tablename, const QString & name )
{
        aDataTable *t = table( tablename );
//CHECK_POINT
        if ( t ) return t->value( name );
        return QVariant("");
}


/*!
 *		\brief Set field value of the secondary object database table.
 */
ERR_Code
aObject::setTValue( const QString & tablename, const QString & name, const QVariant &value )
{
	aDataTable *t = table( tablename );
	if ( t )
	{
		t->setValue( name, value );
		return err_noerror;
	}
	return err_notable;
}



/*!
 *		\brief Осуществляет выделение символьного префикса из строки.
 *
 *		TODO перенести этот метод в сервисный класс.
 */
ERR_Code
aObject::decodeDocNum( QString nm, QString & pref, int & num)
{
	
	aLog::print(aLog::MT_DEBUG, tr("aObject decode doc number %1").arg(nm));
	int pos = -1;
	for ( uint i = nm.length(); i > 0; i-- )
	{
		if ( ( nm.at(i-1) >='0' ) && ( nm.at(i-1) <= '9' ) )
			continue;
		else
		{
			pos = i;
			break;
		}
	}
	if ( pos == -1 )
	{
//CHECK_POINT
		pref = "";
		num = nm.toInt();
		return err_incorrectname;
	}
	if ( pos == ( int ) nm.length() )
	{
//CHECK_POINT
		pref = nm;
		num = -1;
		return err_incorrectname;
	}
//CHECK_POINT
	pref = nm.left( pos );
	num = nm.mid(pos).toInt();
	aLog::print(aLog::MT_DEBUG, tr("aObject decode doc number ok, pref=%1 num=%2").arg(pref).arg(num));
	return err_noerror;
}



/*!
 *
 */
/*
bool
aObject::Next()
{
	return table()->next();
//	return dbtables[""]->next();
}
*/


/*!
 *
 */
/*
bool
aObject::Prev()
{
//	return dbtables[""]->prev();
	return table()->prev();
}
*/


/*!
 *
 */
/*
bool
aObject::First()
{
//	return dbtables[""]->first();
	return table()->first();
}
*/


/*!
 *
 */
/*
bool
aObject::Last()
{
//	return dbtables[""]->last();
	return table()->last();
}
*/


/*!
 *		\brief Перемещает указатель на следующую запись SQL таблицы.
 *	
 *		Таким образом меняется текущий объект.
 */
bool
aObject::Next( const QString& tableName )
{
	return table(tableName)->next();
}


/*!
 *		\brief Перемещает указатель на предыдующую запись SQL таблицы.
 *	
 *		Таким образом меняется текущий объект.
 */
bool
aObject::Prev( const QString& tableName )
{
	return table(tableName)->prev();
}



/*!
 *		\brief Перемещает указатель на первую запись SQL таблицы.
 *	
 *		Таким образом меняется текущий объект.
 */
bool
aObject::First( const QString& tableName )
{
	return table(tableName)->first();
}



/*!
 *		\brief Перемещает указатель на последнюю запись SQL таблицы.
 *	
 *		Таким образом меняется текущий объект.
 */
bool
aObject::Last( const QString& tableName )
{
	return table(tableName)->last();
}

/*!
 *	\ru
 *		\brief Возвращает уникальный идентификатор объекта из базы данных.
 *
 *	В качестве объекта например может выступать "Приходная накладная" от такого-то числа за таким то номером.
 *	Каждый вновь созданный в системе документ или элемент справочника, включая группы справочника имеет свой уникальный
 *	неповторяющийся идентификатор. Если какое-либо поле, какого-либо объекта имеет тип Объект (например Document.Накладная),
 *	то в качестве значения ему нужно задавать уникальный идентификатор объекта, возвращаемый функцией Uid().
 *	Не существует возможности изменить существующий идентификатор какого-либо объекта. Созданием и управлением
 *	идентификаторами объектов занимается система.
 *
 *	\return строка со значением уникального идентификатора.
 *	\_ru
 */
QString
aObject::Uid()
{
	return QString::number(getUid());
}


/*!
 *		\brief Возвращает уникальный идентификатор объекта из базы данных.
 *		\see aObject::Uid()
 */
Q_ULLONG
aObject::getUid()
{
	Q_ULLONG Uid = 0;
	if ( selected() ) Uid = table()->sysValue("id").toULongLong();
	return Uid;
}


/*!
 *		\brief Явно задает состояние выбранности объекта или записи его табличной части.
 */
void
aObject::setSelected( bool sel, const QString & tablename )
{
	if ( tablename == "" ) selectFlag = sel;
	else table(tablename)->selected = sel;
}


/*!
 *		\brief Показывает задан ли текущий объект или запись в его табличной части.
 *	
 *		Заданность текущего объекта имеет тот смысл, что какая то из 
 *		записей SQL таблицы выбрана и имеется возможность работать с ее полями,
 *		хранящими значения свойств объекта.
 *		Если задан не обязательный параметр, то осуществляется проверка на возможность 
 *		работы с записями указанной табличной части объекта.
 *
 *		\param tablename -имя табличной части объекта. Необязательный параметр,
 *		имеющий значение "" по-умолчанию. 
 */
bool
aObject::selected( const QString & tablename )
{
	if ( tablename == "" ) return selectFlag;
	else return table(tablename)->selected;
}


/*!
 *		\brief	Устанавливает вильтр записей табличной части объекта.
 */
ERR_Code
aObject::setTFilter( const QString & tname, const QString & valname, const QVariant & value )
{
	aDataTable * t = dbtables[tname];
	if ( !t ) return err_notable;
	if ( t->setFilter( valname, value ) ) return err_noerror;
	else return err_fieldnotfound;
}


/*!
 *		\brief Чистит фильтр записей указанной табличной части объекта.
 */
ERR_Code
aObject::clearTFilter( const QString & tname )
{
	aDataTable * t = dbtables[tname];
	if ( !t ) return err_notable;
	t->clearFilter();
	return err_noerror;
}


/*!
 *		\brief Задает фильтр записей/объектов
 */
int
aObject::SetFilter( const QString & valname, const QVariant & value )
{
	int err = setTFilter( "", valname, value );
	filtred = !err;
	return err;
}


/*!
 *		\brief Чистит фильтр записей/объектов.
 *	
 *		Фильтр влияет на навигацию и выбор текущего объекта.
 *		\see aObject::clearTFilter( const QString &)
 */
int
aObject::ClearFilter()
{
	filtred = false;
	return clearTFilter("");
}


/*!
 *		\brief	Устанавливает вильтр записей табличной части объекта.
 *		
 *		Вспомогательный метод. Делегирует вызов методу 
 *		aObject::setTFilter( const QString &, const QString &, const QVariant &)
 *		\param tname - имя табличной части
 *		\param valname - имя поля, используемого для фильтрации
 *		\param value - значение поля, используемое для фильтрации
 */
int
aObject::TableSetFilter( const QString & tname, const QString & valname, const QVariant & value )
{
	return setTFilter( tname, valname, value );
}


/*!
 *		\brief Чистит фильтр записей указанной табличной части объекта.
 *		
 *		Вспомогательный метод. Делегирует вызов методу 
 *		aObject::clearTFilter( const QString &)
 *		\param tname - имя табличной части объекта.
 */
int
aObject::TableClearFilter( const QString & tname )
{
	return clearTFilter(tname);
}


/*!
 * \ru
 * 		\brief	Обновляет базу данных данными табличной части объекта. 
 *
 *		Обычно вызывается после метода TableSetValue.
 * 	\param tablename - имя таблицы. Необходим для указания имени, так как
 * 	в объекте возможно наличие нескольких табличных частей.
 * 	\return возвращает код ошибки или 0 в случае успеха.
 * \_ru
 */
int
aObject::TableUpdate( const QString & tablename )
{
	aDataTable *t = table( tablename );
	if ( !t )
	{
		setLastError( err_notable, tr("aObject table update: no table found with name %1").arg(tablename) );
		return lastErrorCode;
	}
//	t->primeUpdate();
	t->Update();
	if (t->lastError().type()) 
	{
		setLastError( err_updateerror, tr("aObject update error. Driver message: %1").arg(t->lastError().text()) );
		return lastErrorCode;
	}
	return err_noerror;
}


/*!
 *		\brief Возвращает строку, предназначенную для отображения пользователю
 *		объекта сложного типа.
 *		
 *		Строковое представление сложного типа определяется разработчиком бизнес-схемы
 *		в дизайнере при проектировании этого типа. Например, строковым представлением
 *		объекта "Счет" может быть значение одного из его полей. Дата или Номер.
 *		\return строку для показа пользователю
 */
QString
aObject::displayString()
{
	QString res="***";
        int stdfc = 0, fid;
        aCfgItem sw, f;

	sw = displayStringContext();
//	if ( md->objClass( obj ) == md_catalogue ) {
//        	sw = md->find( md->find( obj, md_element ), md_string_view );
//	} else {
//        	sw = md->find( obj, md_string_view );
//	}
        if ( !sw.isNull() ) {
                stdfc = md->attr( sw, mda_stdf ).toInt();
                switch ( stdfc ) {
                case 0:
                        fid = md->sText( sw, md_fieldid ).toInt();
                        res = table()->sysValue( QString( "uf%1" ).arg( fid ) ).toString();
//printf("fid=%i res=%s\n",fid, ( const char *) res );
                        break;
                case 1:
                        break;
                case 2:
                        break;
                }
        }
	else
	{

		aLog::print(aLog::MT_DEBUG, tr("aObject display string context is null"));
	}
//	res =
	return res;
}


/**
 *		\brief	Возвращает контекст (узел дерева) метаданных для вычисления строкового представления
 *		сложного типа.
 */
aCfgItem
aObject::displayStringContext()
{
       return md->find( obj, md_string_view );
}


/**
 * \ru
 * 		\brief Вид объекта, так как он описан в метаданных.
 *  \_ru
 */
QString
aObject::Kind( const QString & name )
{
	QString wasKind = md->objClass( obj );
	if ( !name.isEmpty() ) {
	// Set new kind.

	}
	return wasKind;
}

/**
 * \ru
 * 	\brief Возвращает код последней ошибки.
 * 
 * 	Метод позволяет проверить код ошибки после выполнения той или иной операции.
 * 	Если возвращенное значение не равно 0 (нулю), то имела места ошибка, о которой
 * 	возможно следует сообщить пользователю. Текст сообщения об ошибке можно получить
 * 	методом aObject::LastErrorMessage().
 * 	Рекомендуется использовать метод в обязательном порядке при создании объектов доступа
 * 	к данным из Ананас-Скрипта.
 * 	Пример:
 * 	\code
 * 	var  goods = new Catalogue("Номенклатура товаров"); 
 * 	if ( goods.LastErrorCode() != 0)
 *   	{
 *		sys.Message(0,"Ошибка при создании объекта доступа к справочнику: "+goods.LastErrorMessage()); 
 *		return;
 *	}
 *	\endcode
 * \_ru
 * 	\see aObject::LastErrorMessage()
 */
int
aObject::LastErrorCode()
{
	return lastErrorCode;
}


/**
 * \ru
 * 	\brief Возвращает сообщение, поясняющее последнюю ошибку.
 * \_ru
 * 	\see aObject::LastErrorCode()
 */
QString
aObject::LastErrorMessage()
{
	return lastErrorMessage;
}


/**
 * 
 *	\brief Задает значения свойствам lastErrorCode и lastErrorMessage класса
 * 
 * 	Также выводит в лог сообщение об ошибке.
 *	\param errorCode - (in) код ошибки для записи в свойство lastErrorCode
 * 	\param errorMessage - (in) сообщение об ошибке для записи в свойство lastErrorMessage
 * 	\see aObject::LastErrorMessage(), aObject::LastErrorCode()
 */
void 
aObject::setLastError( int errorCode, QString errorMessage)
{
	lastErrorCode = errorCode;
	lastErrorMessage = errorMessage;
	aLog::print(aLog::MT_ERROR, lastErrorMessage);
}
