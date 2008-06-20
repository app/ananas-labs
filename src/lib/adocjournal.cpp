/****************************************************************************
** $Id: adocjournal.cpp,v 1.44 2008/01/21 06:37:09 app Exp $
**
** Documents journal metadata object implementation file of
** Ananas application library
**
** Created : 20040701
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
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

#include	<qdatetime.h>

#include	"acfg.h"
#include	"aobject.h"
#include	"adatabase.h"
#include	"adocjournal.h"
#include 	"alog.h"

/*!
 * \en
 *	\brief	Constructor. Init object with \a context.
 *
 *	\param context - md object
 *	\param adb - link to database
 * \_en
 * \ru
 *	\brief	Конструктор. Инициализирует объект объектом метаданных.
 *
 *	\param context - объект метаданных
 *	\param adb - ссылка на базу данных
 * \_ru
*/
aDocJournal::aDocJournal( aCfgItem context, aDatabase * adb )
:aObject( context, adb, 0, "aDocJournal")
{
	initObject();
}


/*!
 * \en
 *	\brief	Constructor. Init object with md object, founded by \a name.
 *
 *	\param name - md object name
 *	\param adb - link to database
 * \_en
 * \ru
 *	\brief	Конструктор. Инициализирует объект объектом метаданных с именем \a name.
 *
 *	\param name - имя объекта метаданных
 *	\param adb - ссылка на базу данных
 * \_ru
 */
aDocJournal::aDocJournal( const QString & name, aDatabase * adb)
:aObject( name, adb, 0, "aDocJournal")
{
	db = adb;
	initObject();
}


/*!
 * \en
 *	\brief	Constructor. Creates system journal.
 *
 *	\param adb - link to database
 * \_en
 * \ru
 *	\brief	Конструктор. Создает экземпляр системного журнала, в котором хранятся ссылки на все созданные документы.
 *
 *	\param adb - ссылка на базу данных
 * \_ru
 */
aDocJournal::aDocJournal( aDatabase * adb )
{
	db = adb;
	initObject();
}


/**
 * \ru
 * 	\brief	Выполняет реальную инициализацию объекта. Вызывается из всех конструкторов.
 * \_ru
 *
 */
ERR_Code
aDocJournal::initObject()
{
	ERR_Code err = err_noerror;
	aCfgItem mditem, docitem, header;
	
	
	journalType=0;

	setInited( true );
	md = 0;
	if ( db ) md = &db->cfg;
	if(!md)
	{
		setLastError( err_objnotfound, tr("aDocJournal md object not exists"));
		return LastErrorCode();
	}
//	aObject::initObject();
	journalType= md->attr(obj,mda_type).toInt();
	if (journalType)
	{
		mditem= md->find(obj,md_fieldid);
		if (mditem.isNull())
		{
			setLastError( err, tr("aDocJournal columns not defined"));
			return LastErrorCode();
		}
		else
		{
			aLog::print(aLog::MT_DEBUG, tr("aDocJournal column defined"));
		}
		docitem= md->parent( md->parent( md->find(md->text(mditem).toLong())));

		header = md->find( docitem, md_header );
		if(header.isNull()) 
		{
			setLastError( -1, tr("aDocJournal invalid column define"));
		}
	//table for special journal
		err =  tableInsert( aDatabase::tableDbName( *md, header ), header );
//		printf("table name is %s\n", aDatabase::tableDbName( *md, header ).ascii());
	}
	else
	{
	//table for common journal
		err = tableInsert( "a_journ" );
	}
	
	return err;
}


/*!
 * \en
 *	\brief	Get current document id.
 *
 *	Get database id for current document.
 *	\return database document id.
 * \_en
 * \ru
 *	\brief	Возвращает id текущего документа.
 *
 *	Возвращает id документа в базе данных.
 *	\return  id документа в базе данных.
 * \_ru
 */
Q_ULLONG
aDocJournal::docId()
{
	if (!journalType) {
		return table()->sysValue("idd").toULongLong();
	} else {
		return table()->sysValue("id").toULongLong();
	}
}


/*!
 * \en
 *	\brief	Gets current document type.
 *
 *	\return database document type.
 * \_en
 * \ru
 *	\brief	Получение типа текущего документа.
 *
 *	\return тип документа в базе данных.
 * \_ru
 */
int
aDocJournal::docType()
{
	return db->uidType( docId() );
}


/*!
 * \en
 *	\brief	Delets current document.
 *
 *	\return error code.
 * \_en
 * \ru
 *	\brief	Удаляет текущий документ.
 *
 *	\return код ошибки.
 * \_ru
 * 	\see deleteDocument( Q_ULLONG idd )
 */
ERR_Code
aDocJournal::Delete()
{
	ERR_Code err;
	aDocument * doc = CurrentDocument();
	if ( !doc ) return err_notselected;
	else err = doc->Delete();
	delete doc;
	doc = 0;
	return err;
}


/*!
 * \en
 *	\brief Delets document with id =\a idd.
 *	
 *	\param idd - document id.
 *	\return error code.
 * \_en
 * \ru
 *	\brief Удаляет документ с заданным идентификатором.
 *
 *	\param idd - идентификатор документа.
 *	\return код ошибки.
 * \_ru
 * 	\see Delete()
 */
ERR_Code
aDocJournal::deleteDocument( Q_ULLONG idd )
{
	aSQLTable * t = table();
	Q_ULLONG Uid = findDocument(idd);
	db->markDeleted( Uid );
	if (t->exec("DELETE FROM a_journ WHERE idd =" + QString("%1").arg(idd)))
	{
		aLog::print(aLog::MT_INFO, tr("aDocJournal delete document with idd=%1").arg(idd));
		return err_noerror;
	}
	else
	{
		setLastError( err_execerror, tr("aDocJournal delete document with idd=%1").arg(idd));
		return LastErrorCode();
	}
}


/*!
 * \en
 *	\brief Create new record in system journal.
 *
 *	Record create afte crate new document and use information about doc's
 *	database id, prefix and metadata id(type).
 *	Document number generate automatically by nextNumber().
 *	\param idd - database document id.
 *	\param docPrefix - document number prefix.
 *	\param type - document metadata id.
 *	\return error code.
 * \_en
 * \ru
 *	\brief Добавляет запись в системный журнал.
 *
 *	Запись добавляется после создания документа и использует информацию о его
 *	id в базе данных, префиксе номера и id в конфигурации.
 *	Номер досумента генерируется функцией nextNumber()
 *	\param idd - id базы данных.
 *	\param docPrefix - перфикс номера документа.
 *	\param type - id документа в конфигурации.
 *	\return код ошибки.
 *
 * \_ru
 */
ERR_Code
aDocJournal::New( Q_ULLONG idd, const QString & docPrefix, int type )
{
	//Q_ULLONG Uid =0;// db->uid( md_systemjournal );
	aDataTable * t = table();
	if ( !t ) return err_notable;
	//t->exec("LOCK TABLE a_journ WRITE");
	//printf("insert into ajourn id=%llu idd=%llu, docPrefix=%s, type=%d\n",Uid,idd, (const char*)docPrefix.local8Bit(), type);
//	t->exec("LOCK TABLE a_journ WRITE");
	QSqlRecord *rec;
	rec = t->primeInsert(); // get edit buffer for table elements
//	t->primeInsert();
	//ide = rec->value("id").toULongLong();
	//rec->setValue("id",Uid);
	rec->setValue("idd",idd);
	rec->setValue("typed",type);
	rec->setValue("num",nextNumber(docPrefix,type));
	rec->setValue("pnum",docPrefix);
	rec->setValue("ddate",QDateTime::currentDateTime());
	
	t->insert(); // insert edit buffer as new line in table
//TODO: error handle
	aLog::print(aLog::MT_INFO, tr("aDocJournal new document with idd=%1").arg(idd));
	/*
	t->primeInsert();
	t->insert();
	t->setSysValue( "id", Uid );
	t->setSysValue( "idd", idd );
	t->setSysValue( "typed", type );
	t->setSysValue( "num", nextNumber(docPrefix,type) );
	t->setSysValue( "pnum", docPrefix );
	t->setSysValue( "ddate", QDateTime::currentDateTime() );
	Update();
	t->exec("UNLOCK TABLE");
	*/
	
	int err = selectDocument( idd );
	setSelected(!err);
	return err;
}


/*!
 * \en
 *	\brief Select document with id =\a idd.
 *	
 *	\param idd - document id.
 *	\return error code.
 * \_en
 * \ru
 *	\brief Выбирает документ с заданным идентификатором.
 *
 *	\param idd - идентификатор документа.
 *	\return код ошибки.
 * \_ru
 * 	\see findDocument( Q_ULLONG idd )
 */
ERR_Code
aDocJournal::selectDocument( Q_ULLONG idd )
{
	aDataTable * t = table();
	if ( !t ) return err_notable;
	QString flt;
	flt = QString("idd=%1").arg(idd);
	if ( t->select(flt) )
		if ( t->first() )
		{
			setSelected(true);
			return err_noerror;
		}
		else return err_notselected;
	return err_selecterror;
}


/*!
 * \en
 *	\brief Generate next document number.
 *
 *	\param prefix - number prefix
 *	\param mdId - document's number in metadata
 *	\return document number.
 * \_en
 * \ru
 *	\brief Генерирует следующий номер для документа.
 *
 *	Номер представляет собой строку, состоящую из префикса номера и числа.
 *	Номер документа генерируется используя префикс номера документа
 *	и его тип (id в конфигурации), как следующий за максимальным для даного сочетания.
 *	Номер является уникальным в для доументов одного типа.
 *	\param prefix - префикс номера.
 *	\param mdId - id документа в метаданных бизнес-схемы.
 *	\return номер документа (только число).
 * \_ru
 */
QString
aDocJournal::nextNumber( const QString &prefix, int mdId )
{
	QString num="0", query;
	query = QString("SELECT MAX(num)+1 FROM a_journ where pnum='%1' AND typed=%2").arg( prefix ).arg(mdId);
	QSqlQuery q = db->db()->exec( query );
	if ( q.first() ) num = q.value( 0 ).toString();
        if ( num == "0" ) num = "1";
	aLog::print(aLog::MT_INFO, tr("aDocJournal generated next number for %1 is %2").arg(prefix).arg(num));
	//debug_message("<<<Next document number query>>>\n%s\nreturn: %s\n",
		//	(const char*)query,(const char*)num);
	return num;
}


/*!
 * \en
 *	\brief Gets current document date.
 *	\return document date
 * \_en
 * \ru
 *	\brief Возвращает дату текущего документа.
 *	\return дату документа
 * \_ru
 * 	\see setDate( QVariant date )
 */
QVariant
aDocJournal::getDate()
{
	aSQLTable * t = table();
	if ( !t || !selected() ) return QVariant::Invalid;
	else return t->sysValue("ddate");
}


/*!
 * \en
 *	\brief Gets current document prefix + number.
 *	\return document number
 * \_en
 * \ru
 *	\brief Возвращает строку префикс + номер текущего документа.
 *	\return номер документа 
 * \_ru
 * 	\see setNumber( QVariant number )
 */
QString
aDocJournal::getNumber()
{
	aSQLTable * t = table();
	if ( !t || !selected() ) return "";
	else return t->sysValue("pnum").toString() + t->sysValue("num").toString();
}

/*!
 * \en
 *	\brief Gets current document number.
 *	\return document number
 * \_en
 * \ru
 *	Возвращает номер текущего документа.
 *	\return номер документа
 * \_ru
 * 	\see getNumber( QVariant number )
 */
int
aDocJournal::getSerialNumber()
{
	aSQLTable * t = table();
	if ( !t || !selected() ) return 0;
	else return t->sysValue("num").toInt();
}

/*!
 * \en
 *	\brief Sets current document date.
 *	\param date - document date.
 *	\return error code.
 * \_en
 * \ru
 *	\brief Устанавливает дату текущего документа.
 *	\param date - дата документа.
 *	\return код ошибки.
 * \_ru
 * 	\see getDate()
 */
ERR_Code
aDocJournal::setDate( QVariant date )
{
	aSQLTable * t = table();
	if ( !t ) return err_notable;
	if ( !selected() ) return err_notselected;
	t->setSysValue( "ddate", date );
	return err_noerror;
}


/*!
 * \en
 *	\brief Sets current document number.
 *
 *	\param number - document number
 *	\return error code.
 * \_en
 * \ru
 *	\brief Устанавливает номер текущего документа.
 *
 *	\param number - номер документа.
 *	\return код ошибки.
 * \_ru
 *	\see getNumber()
 */
ERR_Code
aDocJournal::setNumber( QVariant number  )
{
	aSQLTable * t = table();
	if ( !t ) return err_notable;
	if ( !selected() ) return err_notselected;
	QString pr;
	int num;
	decodeDocNum( number.toString(), pr, num  );
	t->setSysValue( "pnum", pr );
	t->setSysValue( "num", num );
	return err_noerror;
//	return Update();
	/*QString query;
	Q_ULLONG idd = docId();
	QSqlQuery q = db->db()->exec ( QString("SELECT pnum, num FROM a_journ WHERE idd=%1").arg( idd ) );
	if ( q.first() ) return q.value(0).toString()+q.value(1).toString();
	else return "";*/
}


/*!
 * \en
 *	\brief Find document by id.
 *
 *	\param idd - document number.
 *	\return document id or 0 if document not found 
 * \_en
 * \ru
 *	\brief Ищет документ в системном журнале по его идентификатору. 
 *
 *	\param idd - номер документа
 *	\return id документа или 0, если документ не найден
 * \_ru
 *	see findDoc( const QString & number, int type ) selectDocument( Q_ULLONG idd )
 */
Q_ULLONG
aDocJournal::findDocument( Q_ULLONG idd )
{
	aSQLTable * t = table();
	if ( !t ) return 0;
	if (t->exec(QString("SELECT * FROM a_journ WHERE idd=%1").arg(idd)) )
		if ( t->first() )
		{
			setSelected( true );
			return getUid();
		}
		else
		{
			aLog::print(aLog::MT_DEBUG, tr("aDocJournal document not found with idd=%1").arg(idd));
		}
	return 0;
}


/*!
 * \en
 *	\brief Find document by number and type.
 *
 *	\param number - document number 
 *	\param type - document type 
 *	\return document id or 0 if document not found 
 * \_en
 * \ru
 *	\brief Ищет документ по его номеру и типу. 
 *
 *	\param number - номер документа, состоящий из префикса и номера
 *	\param type - тип документа
 *	\return id документа или 0, если документ не найден
 * \_ru
 *	\see findDocument( Q_ULLONG idd )
 */
Q_ULLONG
aDocJournal::findDoc( const QString & number, int type )
{
	QString pref;
	int num;
	decodeDocNum( number, pref, num );
	if ( table()->select(QString("pnum='%1' AND num=%2 AND typed=%3").arg(pref).arg(num).arg(type)) )
		if ( table()->first() )
		{
			setSelected(true);
			return table()->sysValue("idd").toULongLong();
		}
		else
		{
			aLog::print(aLog::MT_DEBUG, tr("aDocJournal document not found with number=%1 and type=%2 ").arg(number).arg(type));
		}
	return 0;
}


/*!
 * \en
 *	\brief Gets current document.
 *
 *	\return current document 
 * \_en
 * \ru
 *	\brief Возвращает текущий документ. Полученный документ необходимо удалить после использования.
 *
 *	\return текущий документ
 *	\code
 *	aDocument *doc = sysJournal->CurrentDocument();
 *	//какие-то действия с документом
 *	delete doc;
 *	doc=0;
 *	\endcode
 * \_ru
 */
aDocument*
aDocJournal::CurrentDocument()
{
	aCfgItem i = md->find( docType() );
	if(!i.isNull())
	{
		aDocument *d = new aDocument( i, db );
		if(!d->select( docId() ))
		{
			return d;
		}
		else
		{
			delete d;
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


/*!
 * \en
 *	\brief Select documents at some period.
 *
 *	\param from - begin date
 *	\param to - end date
 *	\param nmName - document type
 *	\return error code
 * \_en
 * \ru
 *	\brief Выбирает документы определенного типа за некоторый период. 
 *
 *	\param from - дата начала периода
 *	\param to - дата окончания периода
 *	\param nmName - тип документа
 *	\return код ошибки
 * \_ru
 */
ERR_Code
aDocJournal::Select( QDateTime from, QDateTime to, const QString & mdName )
{
	aSQLTable  * t = table();
	if ( !t )
		return err_notable;
	QString fltr, docType = "";
	if ( mdName != "" )
	{
		aCfgItem item = md->find( "Document." + mdName );
		if ( item.isNull() )
			return err_objnotfound;
		int type = md->id( item );
		docType = QString(" AND typed=%1").arg(type);
	}
	if ( from.isNull() )
		if ( !to.isNull() )
			fltr = "ddate<='" + to.toString("yyyy-MM-dd hh:mm:ss") + "'";
		else
			return err_condition;
	else
		if ( !to.isNull() )
			fltr = "ddate>='" + from.toString("yyyy-MM-dd hh:mm:ss") + "' AND ddate<='" +\
					 to.toString("yyyy-MM-dd hh:mm:ss") + "'";
		else
			fltr = "ddate>='" + from.toString("yyyy-MM-dd hh:mm:ss") + "'";
	if ( t->select( fltr + docType ) )
		if ( t->first() )
		{
			setSelected(true);
			return err_noerror;
		}
		else return err_notselected;
	return err_selecterror;
}


/*!
 * \en
 *	\brief Select document by number and type.
 *
 *	\param number - document number
 *	\param nmName - document type
 *	\return error code
 * \_en
 * \ru
 *	\brief Выбирает документ определенного типа и номера. 
 *
 *	\param number - составной номер документа
 *	\param nmName - тип документа
 *	\return код ошибки
 * \_ru
 */
ERR_Code
aDocJournal::Select( const QString & number, const QString & mdName )
{
	aSQLTable * t = table();
	if ( !t ) return err_notable;
	QString dFilter = "", pref;
	if ( mdName != "" )
	{
		aCfgItem tObj = md->find( "Document."+mdName );
		if ( tObj.isNull() ) return err_objnotfound;
		else dFilter = QString(" AND typed=%1").arg(md->attr(tObj,mda_id));;
	}
	int num;
	decodeDocNum( number, pref, num );
	if ( t->select(QString("pnum='%1' AND num=%2").arg(pref).arg(num) + dFilter) )
		if ( t->first() )
		{
			aLog::print(aLog::MT_DEBUG, tr("aDocJournal select document with number=%1 and md name=%2").arg(number).arg(mdName));
			setSelected(true);
			return err_noerror;
		}
		else return err_notselected;
	return err_selecterror;

}


/*!
 * \en
 *	\brief Gets current document prefix
 *	\return prefix
 * \_en
 * \ru
 *	\brief Выбирает префикс текущего документа.
 *	\return префикс
 * \_ru
 */
QString
aDocJournal::getPrefix()
{
	QString pref = "";
	Q_ULLONG dUid = docId();
	if ( dUid )
	{
		QSqlQuery q = db->db()->exec(QString("SELECT pnum FROM a_journ WHERE idd=%1").arg(dUid));
		if ( q.first() ) pref = q.value(0).toString();
	}
	return pref;
}


/**
 * \ru
 *	\brief Формирует строку с булевым выражением, для использования при отборе записей в SQL запросе.
 *
 * 	Следует использовать при фильтрации по интервалу времени.
 *	\param from - дата, задающая начало интервала времени
 *	\param to - дата, задающая конец интервала времени
 *	\param mdName - Имя типа документа, как оно определено в Дизайнере Ананаса при проектировании бизнес-схемы.
 *	В выражение будет добавлена проверка на соответствие типу документа.
 *	\param full - булевый параметр, влияющий на формат создаваемого выражения. true - указывать имя sql таблицы
 *	"a_journ." перед имененами полей в выражении.
 * \_ru
 */
QString
aDocJournal::selectionFilter( QDateTime from, QDateTime to, const QString & mdName, bool full )
{
	QString fltr="", docType = "", journ="";
	if ( full ) journ="a_journ.";
	if ( mdName != "" )
	{
		aCfgItem item = md->find( "Document." + mdName );
		if ( item.isNull() )
			return "";
		int type = md->id( item );
		docType = " AND " + journ + QString("typed=%1").arg(type);
	}
	if ( from.isNull() )
		if ( !to.isNull() )
			fltr = journ + "ddate<='" + to.toString("yyyy-MM-dd hh:mm:ss") + "'";
		else
			return "";
	else
		if ( !to.isNull() )
			fltr = journ + "ddate>='" + from.toString("yyyy-MM-dd hh:mm:ss") + "' AND " + 
				journ + "ddate<='" + to.toString("yyyy-MM-dd hh:mm:ss") + "'";
		else
			fltr = journ + "ddate>='" + from.toString("yyyy-MM-dd hh:mm:ss") + "'";
	return fltr + docType;
}

/**
 * \ru
 *	\brief Формирует строку с булевым выражением, для использования при отборе записей в SQL запросе.
 *
 * 	Следует использовать при фильтрации по номеру документа.
 *	\param from - дата, задающая начало интервала времени
 *	\param to - дата, задающая конец интервала времени
 *	\param mdName - Имя типа документа, как оно определено в Дизайнере Ананаса при проектировании бизнес-схемы.
 *	В выражение будет добавлена проверка на соответствие типу документа.
 *	\param full - булевый параметр, влияющий на формат создаваемого выражения. true - указывать имя sql таблицы
 *	"a_journ." перед имененами полей в выражении.
 * \_ru
 */
QString
aDocJournal::selectionFilter( const QString & num, const QString & mdName, bool full )
{
	QString pref, fltr="", journ="";
	int nm;
	decodeDocNum( num, pref, nm );
	if ( full )
	{
		fltr=QString("a_journ.num=%1 AND a_journ.pnum='%2'").arg(nm).arg(pref);
		journ = "a_journ.";
	}
	else fltr=QString(" num=%1 AND pnum='%2'").arg(nm).arg(pref);
	if ( mdName != "" )
	{
		aCfgItem tObj = md->find( "Document."+mdName );
		if ( tObj.isNull() ) return "";
		else fltr += QString(" AND %1typed=%2").arg(journ).arg(md->id(tObj));
	}
	return fltr;
}
