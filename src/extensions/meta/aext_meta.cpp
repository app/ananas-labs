/****************************************************************************
** $Id: aext_meta.cpp,v 1.7 2008/12/19 12:21:19 app Exp $
**
** Extension object implementation file of
** Ananas application library
**
** Created : 20031201
**
** Copyright (C) 2006 Andrey Paskal
**
** This file is part of the Designer application of the Ananas
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

//#include <qtextstream.h>
#include <qdom.h>
#include <qstringlist.h> 

#include "aobject.h"
#include "aext_meta.h"
#include "adatabase.h"
#include "alog.h"
#include <aextensionplugin.h>

/**
 *\en
 *	Create object.
 *\_en \ru
 *	Создает объект.
 *\_ru
 */
AExtMeta::AExtMeta()
    : AExtension("Meta")
{
}


/**
 *\en
 *	Destroy object.
 *\_en \ru
 *	Уничтожает объект.
 *\_ru
 */
AExtMeta::~AExtMeta()
{
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает имя класса бизнес объекта по идентификатору класса, присвоенному классу в метаданных.
 *
 * 	Имя класса может быть например "Справочник товаров", "Справочник счетов".
 * 	\param id - идентификатор класса в метаданных
 * 	\return имя класса в бизнес схеме
 *
 * 	Пример использования
 * 	\code
 * 	meta = new Meta();
 * 	sys.Message(0,"id=129, Class name = "+meta.GetClassName(129));
 * 	\endcode
 *
 * 	\see GetBaseClassName(...)
 * \_ru
 */
QString
AExtMeta::GetClassName(const long &id)
{
    return db->cfg.attr(db->cfg.find(id),"name");
}


/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает имя базового класса бизнес объекта по идентификатору класса, присвоенному классу в метаданных.
 *
 * 	Имя базового класса может быть, например "catalogue", "document", "aregister", "iregister","journal", "report".
 * 	\param id - идентификатор класса в метаданных
 * 	\return имя базового класса в бизнес схеме
 *
 * 	Пример использования
 * 	\code
 * 	meta = new Meta();
 * 	sys.Message(0,"id=129, Base class name = "+meta.GetBaseClassName(129));
 * 	\endcode
 *
 * 	\see GetClassName(...)
 * \_ru
 */
QString
AExtMeta::GetBaseClassName(const long &id)
{
    return db->cfg.objClass(id);
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает имя базового класса бизнес объекта по уникальному идентификатору
 * 	бизнес объекта в базе данных.
 * 	
 * 	Имя базового класса может быть, например "catalogue", "document", "aregister", "iregister","journal", "report".
 * 	\param id - уникальный идентификатор бизнес обхъекта в базе данных
 * 	\return имя базового класса в бизнес схеме
 *
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 * 	sys.Message(0,"uid=6, base class name ="+meta.GetBaseClassNameByObjectUid(6));
 * \endcode
 * \see GetClassNameByObjectUid(...)
 * \_ru
 */
QString
AExtMeta::GetBaseClassNameByObjectUid(const long &id)
{
    return db->cfg.objClass(db->uidType(id));
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает имя класса бизнес объекта по уникальному идентификатору бизнес объекта в базе данных
 *
 * 	Имя класса может быть например "Справочник товаров", "Справочник счетов".
 * 	\param id - уникальный идентификатор бизнес объекта в базе данных
 * 	\return имя класса в бизнес схеме
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 * 	sys.Message(0,"uid=6, class name ="+meta.GetClassNameByObjectUid(6));
 * \endcode
 * \see GetBaseClassNameByObjectUid(...)
 * \_ru
 */
QString
AExtMeta::GetClassNameByObjectUid(const long &id)
{
    return db->cfg.attr(db->cfg.find(db->uidType(id)),"name");
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает количество бизнес объектов указанного класса в бизнес схеме.
 *
 * 	Имя класса может быть, например, "catalogue", "document".
 * 	\param className - Имя класса
 * 	\return количество бизнес объектов
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 * \endcode
 * \_ru
 */
int
AExtMeta::CountByClassName(const QString &className) {
	return db->cfg.count(db->cfg.find(mdc_root),className);
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает список подтипов одного или всех базовых типов бизнес схемы.
 *
 * 	TODO: Требуется проверить возможность передачи возвращаемого значения в Скрипт. Возможно списки и не поддерживаются.
 * 	\param className - Имя базового типа, может принимать значения "Catalogue", "Document", "Journal".
 *  Если значение не задано - возвращаются все подтипы всех базовых типов.
 * 	\return Список названий подтипов. Имя подтипа состоит из уникального идентификатора в бизнес схеме в виде "O XXX" 
 * 	и отделенного символом табуляции пользовательского названия типа. Например "O 115\tСправочник.Справочник Контрагентов"
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 * \endcode
 * \_ru
 */
QStringList
AExtMeta::DataTypes(const QString &filter) {
	QStringList sList;
	QString flt;
	
	if ( filter == NULL || filter.isEmpty() ) {
		sList = db->cfg.types();
	} else {
		if (filter == "Catalogue" || filter == QObject::tr("Catalogue") ) {
			flt = md_catalogue;
		} else if (filter == "Document" || filter == QObject::tr("Document") ) {
			flt = md_document;
		} else if (filter == "Journal" || filter == QObject::tr("Journal") ) {
			flt = md_journal;
		} else {
			aLog::print(aLog::MT_ERROR, tr("Unknoun filter for datatype: %1").arg( filter ) );
			sList = db->cfg.types();
		}
		sList = db->cfg.types( flt );
	}
	
	return sList;
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает строку со списоком подтипов базовых типов.
 *
 *  Вспомогательная функция. Предназначена для использования из QSA, который не умеет получать список строк 
 *  в качестве возвращаемого значения. Смотри DataTypes().
 * 	
 * 	\param className - Имя базового типа, может принимать значения "Catalogue", "Document", "Journal".
 *  Если значение не задано - возвращаются все подтипы всех базовых типов.
 *  \param separator - Символ или строка, используемая в качестве разделителя элементов строки. По умолчанию - двоеточие ":".
 * 	\return Строку с названиями подтипов, разделенными значением, переданным в параметре separator
 * 	Имя подтипа состоит из уникального идентификатора в бизнес схеме в виде "O XXX" и отделенного символом табуляции
 *  пользовательского названия типа. 
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 *  names = meta.StringOfDataTypes("Catalogue"); // Возвращает строку с названиями имеющихся в бизнес схеме справочников
 *	// например "Неизвестный:O 101 Справочник.Справочник счетов:O 115 Справочник.Справочник Контрагентов:O 201 Справочник.Справочник операций:O 304 Справочник.Номенклатура товаров"
 * \endcode
 * \_ru
 */
QString
AExtMeta::StringOfDataTypes(const QString &className, const QString& separator) {
	
	QStringList list = DataTypes( className );
	return list.join( separator );
}


/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает идентификатор объекта метаданных по его полному имени.
 *
 *	Предназначен для использования в бизнес схеме "Бухучет" при оперировании разрезами проводок.
 *  Справочники (товаров, контрагентов, складов) выступают в качестве разрезов аналитического бухучета.
 *  Данный метод, например, позволяет разработчику бизнес схемы получить уникальный идентификатор справочника (разреза)
 *  и хранить его в свойствах счета, связав таким образом бухгалтерский счет с определенным разрезом (разрезами). 	
 * 	\param name - Полное имя объекта, например, "catalogue.Товары", "document.ПКО".
 *  Первая часть полного имени - это базовый тип.
 *  Допустимы значения базовых типов:
 *  Catalogue, Document, DocJournal, Report, InfoRegister, AccumulationRegister
 * 	\return Уникальный идентификатор объекта метаданных
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 *  SparvochnikTovarovID = meta.GetId("Catalogue.Товары"); 
 * \endcode
 * \_ru
 */
int
AExtMeta::GetId( QString& name ) 
{
	//aCfgItem it = db->cfg.find( name );
	//return db->cfg.id(it);
	
	return  db->cfg.getId( name );
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает идентификатор объекта .
 *
 * 	\param obj - объект, идентификатор которого надо получить
 * 	\return Уникальный идентификатор объекта метаданных
 * 	
 * 	Пример использования
 * \code
 *	cat = new Catalogue("Номенклатура");
 * 	meta = new Meta();
 *  SparvochnikTovarovID = meta.GetId(cat); 
 * \endcode
 * \_ru
 */
int AExtMeta::GetId( aObject * obj )
{
    return db->cfg.id(obj->obj);
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает список пользовательских полей об
 * екта
 *
 * 	\param name - Полное имя объекта, см описание GetId()
 * 	\return Список польховательских полей или пустой список.
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 *  list = meta.GetUserFields("Catalogue.Товары"); 
 * \endcode
 * \_ru
 */
QStringList AExtMeta::GetUserFields( QString name, QString table )
{	
	int	n;
	aCfgItem obj, cobj;
	QStringList res;
	if( !GetId(name) ) return res;
	obj = db->cfg.find( GetId(name) );	
	if(!table.isEmpty())
	{
		obj = db->cfg.objTable( obj, db->cfg.id(db->cfg.findName(obj, md_table, table)) );
	}
	else
	{
		obj = db->cfg.objTable( GetId(name), 0 );
	}
	n = db->cfg.count ( obj, md_field );
	for (int i = 0; i < n; i++ )
	{
		cobj = db->cfg.find( obj, md_field, i  );
		if ( !cobj.isNull() )
		{
			res << db->cfg.attr(cobj, mda_name);
		}
	}
	return res;
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает список пользовательских полей об
 * екта
 *
 * 	\param obj - объект, идентификатор которого надо получить
 * 	\return Список польховательских полей или пустой список.
 * 	
 * 	Пример использования
 * \code
 *	cat = new Catalogue("Номенклатура");
 * 	meta = new Meta();
 *  list = meta.GetUserFields(cat); 
 * \endcode
 * \_ru
 */
QStringList AExtMeta::GetUserFields( aObject * aobj, QString table )
{	
	return GetUserFields( db->cfg.attr(aobj->obj, mda_name), table );
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает тип пользовательского поля объекта
 *
 * 	\param name - Полное имя объекта, см описание GetId()
 * 	\param attr - название атрибута
 * 	\param table - необязательный, таблица объекта (для документов)
 * 	\return тип атрибута, например "O 115"
 * 	
 * 	Пример использования
 * \code
 * 	meta = new Meta();
 *  type = meta.GetAttrType("Catalogue.Товары", "Наименование"); 
 * \endcode
 * \_ru
 */
QString AExtMeta::GetAttrType(QString name, QString attr, QString table)
{
	aCfgItem obj;
	if( !GetId(name) ) return "";
	obj = db->cfg.find( GetId(name) );	
	if(!table.isEmpty())
	{
		obj = db->cfg.objTable( obj, db->cfg.id(db->cfg.findName(obj, md_table, table)) );
	}
	else
	{
		obj = db->cfg.objTable( GetId(name), 0 );
	}
	obj = db->cfg.findName(obj, "fake", attr);
	return db->cfg.attr(obj, mda_type);
}

/**
 * \en
 * \_en 
 * \ru
 * 	\brief Возвращает тип пользовательского поля объекта
 *
 * 	\param obj - объект, тип атрибута которого надо получить
 * 	\param attr - название атрибута
 * 	\param table - необязательный, таблица объекта (для документов)
 * 	\return тип атрибута, например "O 115"
 * 	
 * 	Пример использования
 * \code
 *	cat = new Catalogue("Номенклатура");
 * 	meta = new Meta();
 *  type = meta.GetAttrType(cat, "Наименование");  
 * \endcode
 * \_ru
 */
QString AExtMeta::GetAttrType(aObject * aobj, QString attr, QString table)
{
	return GetAttrType( db->cfg.attr(aobj->obj, mda_name), attr, table );	
}

typedef AExtensionPlugin<AExtMeta> AExtMetaPlugin;
A_EXPORT_PLUGIN( AExtMetaPlugin )
