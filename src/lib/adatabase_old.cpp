/****************************************************************************
** $Id: adatabase_old.cpp,v 1.2 2007/05/26 19:01:05 leader Exp $
**
** Database abstaraction layer
** of Ananas Project
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2005 Grigory Panov <gr1313 at mail.ru >, Yoshkar-Ola
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

/*
*/
/*
for mysql server set variable in /var/lib/mysql/my.cnf
default-character-set=utf8

*/
#include <qobject.h>
#include <qfile.h>
#include <qdom.h>
#include <qstringlist.h>
#include <qtextstream.h>
#include <qsqlrecord.h>
#include <qstringlist.h>

#include "alog.h" 

#include "asqltable.h"
#include "adatabase.h"

// global configuration variable.
//aDatabase database;

//==========================================================================
// abstract Ananas SQL Database Driver
aDataDriver::aDataDriver(){

}



aDataDriver::~aDataDriver()
{

}


//==========================================================================

aDataDriver_SQLITE::aDataDriver_SQLITE(){

}



aDataDriver_SQLITE::~aDataDriver_SQLITE()
{

}

//==========================================================================

aDataDriver_MYSQL::aDataDriver_MYSQL(){

}



aDataDriver_MYSQL::~aDataDriver_MYSQL()
{

}


//==========================================================================

aDataDriver_PGSQL::aDataDriver_PGSQL(){

}



aDataDriver_PGSQL::~aDataDriver_PGSQL()
{

}

//==========================================================================

/*!
 *	\~english
 *	Constructor has no arguments.
 *	\~russian
 *	Конструктор без параметров.
 *	\~
 */
aDatabase::aDatabase() : QObject()
{
	ddb = 0;
}



/*!
 *	\~english
 *	Destructor.
 *	\~russian
 *	Деструктор.
 *	\~
 */
aDatabase::~aDatabase()
{
}



/*!
 *	\~english
 *	Return current database driver name.
 *	Translate name for unicode MySQL driver to standart name.
 *	\~russian
 *	Возвращает имя драйвера базы данных. 
 *	Переводит имя для драйвера MySQL с поддержкой utf8 в стандартное имя.
 *	\~
 *	\return \~english QT current Database driver name \~russian имя драйвера. \~
 */
QString
aDatabase::driverName()
{
        QString name = db()->driverName();
        if ( name == "QMYSQL3U" ) name = "QMYSQL3";
        return name;
}


/*!
 *	\~english
 *	Return text feature for dynamic SQL by feature name.
 *	\~russian
 *	Возвращает код реализации какой либо особенности сервера БД по ее ключу.
 *	\~
 *	\return \~english Code for dynamic SQL creation  \~russian Код для формирования динамического SQL \~
 */
QString
aDatabase::feature(const QString& featureName)
{
	QString res = QString::null;
        if(driverName() == "QMYSQL3")
	{
		res = featuresMySQL[featureName];
	}
        if(driverName() == "QSQLITE")
	{
		res = featuresSQLite[featureName];
	}
        if(driverName() == "QPSQL7")
	{
		res = featuresPostgreSQL[featureName];
	}
        return res;
}

/*!
 *	\~english
 *	This is overloaded method, provided for convenience.
 *	\~russian
 *	Перегружет метод init( aCfgRc *rc, const QString &dbname )
 *	\~
 *	\see init( aCfgRc *rc, const QString &dbname )
 *	\param rcname (in) - \~english rc file name. \~russian имя файла ресурса \~
 *	\param dbname (in) - \~english parameter to pass trough. \~russian имя базы данных \~
 *	\return \~english true, if no error \~russian  true, если ошибок не было \~
 */
bool
aDatabase::init( const QString &rcname, const QString &dbname )
{
	if ( rcname.isEmpty() ) return false;
	if ( cfg.readrc( rcname ) )
		return false;
	return init( &cfg.rc, dbname );
}



/*!
 *	\~english
 *	Creates database on SQL server.
 *	Reads rc file and makes connection to database server. Then creates database with name obtained from rc file.
 *	\~russian 
 *	Создает базу данных на SQL сервере.
 *	Читает переданный файл ресурса и создает соединение с сервером баз данных. После этого создает базу данных с параметрами, заданными в файле ресурса.
 *	\~
 *	\see init( const QString &rcname, const QString &dbname )
 *	\param rc (in) - \~english rc object reference. \~russian ссылка на файл ресурса \~
 *	\param dbname (in) - \~english unused now. \~russian не используется \~
 *	\return \~english true, if no error \~russian \~
 */
bool
aDatabase::init( aCfgRc *rc, const QString &dbname )
{
	
	fillFeatures();
	QString driver = "UNKNOWN";
	QString dbtype;

	if (!rc) return false;
	dbtype = rc->value("dbtype");
	if (dbtype =="internal") driver = "QSQLITE";
	if (dbtype =="mysql") driver = "QMYSQL3U";
	if (dbtype =="postgres") driver = "QPSQL7";
	if (dbtype =="odbc") driver = "QODBC3";
	if (dbtype =="oracle") driver = "QOCI8";
	if (dbtype =="mssql") driver = "QTDS7";
	if (dbtype =="sybase") driver = "QTDS7";
	done();
	if (!dbname.isEmpty()) {
		// add database in dictionary
	}
	//QSqlDatabase *
	ddb = QSqlDatabase::addDatabase( driver );
	if ( !ddb ) return false;
	ddb->setDatabaseName( rc->value("dbname") );
	ddb->setUserName( rc->value("dbuser") );
	ddb->setPassword( rc->value("dbpass") );
	ddb->setHostName( rc->value("dbhost") );
	if ( !rc->value("dbport").isEmpty() ) ddb->setPort( rc->value("dbport").toInt() );
	if ( driver == "QSQLITE" ) db()->exec( "PRAGMA encoding=\"UTF-8\"" );
	aLog::print(aLog::MT_DEBUG,tr("aDatabase prepared for open connection to %1").arg(rc->value("dbname")));
	if ( !ddb->open() ) 
	{
		
		aLog::print(aLog::MT_INFO,tr("aDatabase open connection failed, try create %1").arg(rc->value("dbname")));
		ddb->setDatabaseName(feature("systemDatabase"));
		ddb->open();
		if(ddb->isOpen())
		{
			aLog::print(aLog::MT_DEBUG,tr("aDatabase system database is open"));
			QString query = QString("create database %1 %2").arg( rc->value("dbname") ).arg(feature("encoding"));
		//if ( driver == "QPSQL7" ) query.append( " with encoding='UTF-8'" );
//#ifdef MYSQL_UTF8
		//if ( driver == "QMYSQL3U" ) query.append( " character set utf8" );
//#endif
			printf("query = %s\n",query.ascii());
			QSqlQuery q = ddb->exec( query );
			if(ddb->lastError().type()!=QSqlError::None)
			{
				reportError(ddb->lastError(),query);
			}
			ddb->setDatabaseName( rc->value("dbname") );
			if ( !ddb->open() ) {
				cfg_message(3, ( const char *) tr("Can't open database connection\n").utf8());
				aLog::print(aLog::MT_ERROR,tr("aDatabase open connection to %1").arg(rc->value("dbname")));
				return false;
			}
			else
			{
				aLog::print(aLog::MT_INFO,tr("aDatabase open connection to %1").arg(rc->value("dbname")));
			}
		}
		else
		{
			cfg_message(3, ( const char *) tr("Can't create database\n").utf8());	
			aLog::print(aLog::MT_ERROR,tr("aDatabase create database %1").arg(rc->value("dbname")));
			return false;
		}
		
		aLog::print(aLog::MT_INFO,tr("aDatabase open connection to %1 ok").arg(rc->value("dbname")));
	}
	return true;
}


void
aDatabase::fillFeatures()
{
	featuresMySQL["autoincrement"] = "select last_insert_id()"; 	
	featuresMySQL["encoding"] = "character set utf8";
	featuresMySQL["systemDatabase"] = "mysql";
	featuresPostgreSQL["autoincrement"] = "select currval('uniques_id_seq')";
	featuresPostgreSQL["encoding"] = "with encoding='UTF-8'";
	featuresPostgreSQL["systemDatabase"] = "template1";
	featuresSQLite["autoincrement"] = "select last_insert_rowid()";
	featuresSQLite["encoding"] = "";
}

/*!
 *	\~english
 *	Closes database connection.
 *	\~russian 
 *	Закрывает соединение с базой данных и освобождает все занятые ресурсы.
 *	\~
 */
void
aDatabase::done()
{
	if ( db() ) {
		db()->close();
	}
}



/*!
 *	\~english
 *	Returns database connection.
 *	\~russian 
 *	Возвращает ссылку на соединение с базой данных. 
 *	\~
 *	\param dbname (in) - 	\~english database connection name. Default value used if dbname is empty.
 *				\~russian имя базы данных. \~
 *	\return  \~english database connection. \~russian соединение с базой данных \~
 */
QSqlDatabase*
aDatabase::db(const QString &dbname )
{
	if ( dbname.isEmpty() ) return QSqlDatabase::database();
	return QSqlDatabase::database( dbname );
}


/*!
 *	\~english
 *	Check database structure. Don't implemented.
 *	\~russian 
 *	проверяет структуру базы данных. Не реализована. 
 *	\~
 *	\return  \~english true, if structure is valid. \~russian true, если база данных коррестна \~
 */
bool
aDatabase::checkStructure()
{

	return false;
}



/*!
 *	\~english
 *	Helper method. 
 *	\~russian
 *	Вспомогательный метод. Создает новую базу данных.
 *	\~
 *	\see createdb()
 */
bool
aDatabase::create()
{
	return createdb( false );
}

bool
aDatabase::drop(const QString& dbname)
{

	QString query = QString("drop database %1").arg(dbname);
	if(!ddb) return true;
	if(ddb->exec(query).lastError().type()==QSqlError::None)
	{
		aLog::print(aLog::MT_ERROR,tr("aDatabase drop database %1").arg(dbname));
	}
	query = QString("create database %1 %2").arg( dbname ).arg(feature("encoding"));
			//if ( driverName() == "QPSQL7" ) query.append( " with encoding='UTF-8'" );
//#ifdef MYSQL_UTF8
			//if ( driverName() == "QMYSQL3" ) query.append( " character set utf8" );
//#endif
			//printf("query = %s\n",query.ascii());
			QSqlQuery q = db()->exec( query );
			if(db()->lastError().type()!=QSqlError::None)
			{
				reportError(db()->lastError(),query);
			}
			ddb->setDatabaseName( dbname );
			if ( !ddb->open() ) {
				cfg_message(3, ( const char *) tr("Can't open database connection\n").utf8());
				aLog::print(aLog::MT_ERROR,tr("aDatabase open connection to %1").arg(dbname));
				return false;
			}
			else
			{
				aLog::print(aLog::MT_INFO,tr("aDatabase open connection to %1").arg(dbname));
				
			}
	return false;
}


/*!
 *	\~english
 *	Helper method. 
 *	\~russian
 *	Вспомогательный метод. Обновляет структуру базы данных.
 *	\~
 *	\see createdb()
 */
bool
aDatabase::update()
{
	return createdb( true );
}



/*!
 *	Creates aDataTable object for browsing and editing sql table in current database.
 *	\param name (in) - sql table name.
 *	\return newly created object.
 */
aDataTable *
aDatabase::table( const QString & name )
{
	aDataTable *t = 0;

	if ( tableExists( name ) ) {
		t = new aDataTable( name, this );
	} else {
		t = new aDataTable( QString::null, this );
	}
	return t;
}


/*!
 *	\~english
 *	Helper metod. Returns sql table name for metadata object.
 *	\~russian
 *	Вспомогательный метод. Возвращает имя sql таблицы для объекта метаданных.
 *	\~
 *	\see tableDbName( aCfg &md, aCfgItem context, long * tid )
 *	\param md (in) - \~english metadata tree object. \~russian дерево метаданных. \~
 *	\param context (in) - \~english node of metadata tree which represents metadata Class. \~russian объект метаданных \~
 *	\return \~english sql table name. \~russian имя таблицы в базе данных \~
 */
QString
aDatabase::tableDbName( aCfg &md, aCfgItem context)
{
	long dummy;
	return tableDbName(md,context,&dummy);
}

 
 /*!
 *	\~english
 *	Returns sql table name for metadata object.
 *	\~russian
 *	Возвращает имя sql таблицы для объекта метаданных.
 *	\~
 *	\see tableDbName( aCfg &md, aCfgItem context, long * tid )
 *	\param md (in) - \~english metadata tree object. \~russian дерево метаданных. \~
 *	\param context (in) - \~english node of metadata tree which represents metadata Class. \~russian объект метаданных \~
 *	\param tid (out) - \~english id of metadata Class. \~russian идентификатор объекта метаданных, которому принадлежит таблица \~
 *	\return \~english sql table name. \~russian имя таблицы в базе данных \~
 */
QString
aDatabase::tableDbName( aCfg &md, aCfgItem context, long * tid )
{
	aCfgItem parent = context;
	QString oclass, tname = "";
	long id, idp=0, temp=0;
	if ( context.isNull() ) return "";
	oclass = md.objClass( context );
	id = md.id( context );
	while ( idp == 0 && ! parent.isNull() ) {
		parent = md.parent( parent );
		idp = md.id( parent );
	}
	if ( oclass == md_element )
	{
		tname = QString(db_catalog_element).arg(idp);
		temp = idp;
	}
	if ( oclass == md_group )
	{
		tname =  QString(db_catalog_group).arg(idp);
		temp = idp;
	}
	if ( oclass == md_header )
	{
		tname =  QString(db_document_header).arg(idp);
		temp = idp;
	}
	if ( oclass == md_iregister )
	{
		tname = QString(db_iregister).arg(id);
		temp = id;
	}
	if ( oclass == md_aregister )
	{
		tname = QString(db_aregister).arg(id);
		temp = id;
	}
	if ( oclass == md_table )
	{
		if ( md.objClass(parent) == md_document )
		{
			tname = QString(db_document_table).arg(idp).arg(id);
			temp = id;
		}
	}
	if ( oclass == md_resources )
	{
		if ( md.objClass(parent) == md_aregister )
		{
			tname = QString(db_areg_remainder).arg(idp);
			temp = idp;
		}
	}
	if ( oclass == md_field )
	{
		if ( md.objClass(parent) == md_aregister )
		{
			tname = QString(db_areg_dim).arg(idp).arg(id);
			temp = idp;
		}
	}
	*tid = temp;
//	printf("tname = %s\n",tname.ascii());
	return tname;
}



/*!
 *	\~english
 *	Generates new unique id for system object.
 *	\~russian
 *	Генерирует новый уникальный номер. Эти номера являются невосполнимым ресурсом системы.
 *	\~
 *	\param otype (in) - \~english object type (e.g. document, catalog, journal etc.) \~russian тип объекта \~
 *	\return \~english newly generated unique id. \~russian новый сгенерированный номер \~
 */
Q_ULLONG
aDatabase::uid( int otype )
{
	Q_ULLONG uid = 0;
	QString query;
	QString drv = driverName();
//	printf("driver name =%s\n",drv.ascii());
	query.sprintf("insert into uniques (otype) values (%d)", otype );
	QSqlQuery q = db()->exec( query );
	if(db()->lastError().type()!=QSqlError::None)
	{
		reportError(db()->lastError(),query);
	}
	query = feature("autoincrement");
	q = db()->exec( query );
	if(db()->lastError().type()!=QSqlError::None)
	{
		reportError(db()->lastError(),query);
	}
	if ( q.first() )
	{
		uid = q.value( 0 ).toULongLong();
	}
	else
	{
		aLog::print(aLog::MT_ERROR,tr("aDatabase generate new unique number for object type %1").arg(otype));
	}
//	printf("uid=%llu, otype=%d\n",uid,otype);
	aLog::print(aLog::MT_DEBUG,tr("aDatabase generate new unique number %1 for objecttype %2").arg(uid).arg(otype));
	return uid;
}



/*!
 *	\~english
 *	Returns type of object identified by its uid.
 *	\~russian
 *	Возвращает тип объекта по его идентификатору.
 *	\~
 *	\see uid( int otype )
 *	\param uid (in) - \~english object's uid. \~russian уникальный идентификатор объекта \~
 *	\return \~english object's type \~russian тип объекта \~
 */
int
aDatabase::uidType ( Q_ULLONG uid )
{
	QSqlQuery q = db()->exec( QString("SELECT otype FROM uniques WHERE id=%1").arg(uid) );
	if ( q.first() )
		return q.value(0).toInt();
	else
		aLog::print(aLog::MT_ERROR,tr("aDatabase get object type for unique id=%1").arg(uid));
	return 0;
}



/*!
 *	\~english
 *	Checks table existence.
 *	\~russian 
 *	Проверяет, существует ли таблица в базе данных.
 *	\~
 *	\param name (in) - \~english table name to check for. \~russian имя проверяемой таблицы \~
 *	\return \~english true, if table exists in current database \~russian true, если таблица существует \~
 */
bool
aDatabase::tableExists( const QString & name )
{
	QStringList list = db()->tables();
	QStringList::Iterator it = list.begin();
	while( it != list.end() ) 
	{
		if ( *it == name ) return true;
		++it;
	}
	return false;
}



/*!
 *
 */
QString
aDatabase::fieldtype( const QString &tdef )
{
	int n1, n2;
	bool notnull, serial;
	char t=' ';
	QString st, dt;
	QString drv = driverName();

	if ( tdef.isEmpty() ) return "";
	n1=0; n2=0;
	st = tdef.section(" ", 0, 0).lower();
	n1 = tdef.section(" ", 1, 1).toInt();
	n2 = tdef.section(" ", 2, 2).toInt();
	if(st)
	{
		t = (( const char *) st)[0];
	}
	serial = ( st.mid(1).contains( 's' ) > 0 );
	notnull = ( st.mid(1).contains( 'n' ) > 0 );
	if ( drv == "QSQLITE" ) {
		if ( serial && t=='l') t='i';
		switch ( t ) {
		case 'i':
			dt = QString("integer");
			break;
		case 'l':
			dt = QString("bigint");;
			break;
		case 'c':
			dt = QString("char(%1)").arg(n1);
			break;
		case 'n':
			dt = QString("numeric(%1,%2)").arg(n1).arg(n2);
			break;
		case 'd':
			dt = QString("timestamp");
			break;
		case 'o':
			dt = QString("bigint");
			break;
		case 'b':
			dt = QString("char(1)");
			break;
		default:
			dt = "";
			break;
		}
		if ( !serial && notnull ) dt.append(" not null" );
		if ( serial ) dt.append(" autoincrement");
		return dt;
	}
	if ( drv == "QPSQL7" ) {
		switch ( t ) {
		case 'i':
			if ( serial ) dt = " serial";
			else dt = QString("integer");
			break;
		case 'l':
			if ( serial ) dt = " bigserial";
			else dt = "bigint";
			break;
		case 'c':
			dt = QString("character varying(%1)").arg(n1);
			break;
		case 'n':
			dt = QString("numeric(%1,%2)").arg(n1 + n2).arg(n2);
			break;
		case 'd':
			dt = QString("timestamp");
			break;
		case 'o':
			dt = QString("bigint");
			break;
		case 'b':
			dt = QString("character varying(1)");
			break;
		default:
			dt = "";
			break;
		}
		if ( notnull ) dt.append(" not null" );
		return dt;
	}
        if ( drv == "QMYSQL3") {
		switch ( t ) {
		case 'i':
			dt = QString("int");
			break;
		case 'l':
			dt = QString("bigint");
			break;
		case 'c':
			dt = QString("char(%1)").arg(n1);
			break;
		case 'n':
//			dt = QString("decimal(%1,%2)").arg(n1).arg(n2);
			dt = QString("numeric(%1,%2)").arg(n1 + n2).arg(n2); // Valid for MySQL 5+
			break;
		case 'd':
			dt = QString("datetime");
			break;
		case 'o':
			dt = QString("bigint");
			break;
		case 'b':
			dt = QString("char(1)");
			break;
		default:
			dt = "";
			break;
		}
		if ( notnull ) dt.append(" not null" );
		if ( serial ) dt.append(" auto_increment");
		return dt;
	}
	return "";
}



/*!
 *
 */
QString
aDatabase::convFieldsDef( const QString flddef, QString &idxdef, QString &pkey ){
	QString s;
	QString fname, ftyp, res, ind;
	int n = 0;

	res = "";
	s = flddef.section(",", n, n);
	while ( !s.isEmpty() ) {
		fname = s.section(" ", 0, 0 );
		ftyp = s.section(" ", 1, 3 );
		ind = s.section(" ", 4, 4 ).lower();
		ftyp = fieldtype( ftyp );
		if( ! ftyp.isEmpty() ) {
			if ( !res.isEmpty() ) res.append(",");
			res.append( QString("%1 %2").arg( fname ).arg( ftyp ) );
			if ( !ind.isEmpty()) {
			 	if ( ind[0]=='i' ) {
					if ( !idxdef.isEmpty() ) idxdef.append(",");
					idxdef.append( QString("(%1)").arg( fname ) );
				}
			 	if ( ind[0]=='p' ) pkey = fname;
			}
		}
		n++;
		s = flddef.section(",", n, n);
	}
	return res;
}



/*!
 *
 */
bool
aDatabase::createIndexes(const QString &table, const QString &indexl, const QStringList &uidc)
{
	int idxcount, n;
	bool rc = true;
	QString s, query;
	QSqlQuery q;
	QString drv=driverName();

	// Создадим индексы
	idxcount=0;
	n = 0;
	s = indexl.section(",", n, n);
	while ( !s.isEmpty() ) {
		query = QString("create index %1_idx%2 on %3 %4").arg( table ).arg( idxcount ).arg( table ).arg( s );
		aLog::print(aLog::MT_DEBUG, QString("aDatabase ") + query);
		q = db()->exec( query );
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),query);
		}
		idxcount++; n++;
		s = indexl.section(",", n, n);
	}
	for(uint i=0;i<uidc.size();i++)
	{
	    QString idxname=table+"_uniq_"+uidc[i].left(uidc[i].find('%'));
	    QString query=QString("create unique index %1_uniq_%2").arg(table).arg(uidc[i].arg(" on "+table));
	    qWarning("Executing: %s",query.ascii());
	    bool success=db()->exec(query).lastError().type()==QSqlError::None;
	    if (success)
	    {
		query=QString("insert into %1 (tname,uindices,idxname) values ('%2','").arg(db_indices).arg(table)+uidc[i]+QString("','%1')").arg(idxname);
		qWarning("Executing: %s",query.ascii());
		db()->exec(query);
	    }
	}
	return rc;
}



/*!
 *
 */
bool
aDatabase::dropIndexes(const QString & table, const QStringList & indices)
{
    QString drv=driverName();
    QStringList sli=indices;
    QSqlCursor ind(db_indices,true,db());
    for(uint i=0;i<sli.size();i++)
    {
	ind.select(QString("(tname='%1')and(uindices='%2')").arg(table).arg(sli[i]));
	if (ind.next())
	{
	    QString idxname=ind.value("idxname").toString();
	    qWarning("Dropping index %s on table %s.",idxname.ascii(),table.ascii());
	    bool success=false;
	    if (drv=="QMYSQL3")
		success=db()->exec(QString("drop index %1 on %2").arg(idxname).arg(table)).lastError().type()==QSqlError::None;
	    else if (drv=="QSQLITE")
		success=db()->exec(QString("drop index %1.%2").arg(table).arg(idxname)).lastError().type()==QSqlError::None;
	    else if (drv=="QPSQL7")
		success=db()->exec(QString("drop index %2").arg(idxname)).lastError().type()==QSqlError::None;
	    else
		success=db()->exec(QString("drop index %2").arg(idxname)).lastError().type()==QSqlError::None;
	    if (success)
	    {
		db()->exec(QString("delete from %1 where (tname='%2') and (uindices='%3')").arg(db_indices).arg(table).arg(sli[i]));
	    }
	}
    }
    return true;
}



/*!
 *
 */
bool
aDatabase::verifyTable(
		const QString &table, const QString &flddef,
		QString &f_drop, QString &f_add, QString &f_upd,
		QString &i_drop, QString &i_add, QStringList &ui_drop, QStringList &ui_add)
{
	QSqlRecordInfo ts;
	QSqlFieldInfo f;
	aCfgItem cont, item;
	int w, d;
	QString t, tc, fname, fname1, fname2;
	QStringList fl = QStringList::split(",", flddef );
	QStringList tfl;
	QString drv = driverName();

	ts = db()->recordInfo( table );
	QSqlRecordInfo::Iterator it = ts.begin();
	while( it != ts.end() ) {
		f = *it;
		w = f.length();
		d = f.precision();
		switch ( f.type() ) {
		case QVariant::DateTime:
			t.sprintf("D 0 0");
			break;
		case QVariant::Int:
			t.sprintf("I 0 0");
			break;
		case QVariant::LongLong:
			t.sprintf("L 0 0");
			break;
		case QVariant::String:
			if(drv == "QMYSQL3") w /=3;
			t.sprintf("C %d 0", w);
			break;
		case QVariant::Double:
			if ( drv == "QPSQL7" ) {
				d = w & 0xFF;
				w = ( w & 0xFF0000 ) >> 16;
			}
	        	if ( drv == "QMYSQL3" ) {
				w = w - d;
				if ( d==0 ) w--;
			}
			t.sprintf("N %d %d", w, d);
			break;
		default:
			t = "";
		}
		if ( f.isRequired() ) t = t.section(" ",0,0)+"N "+t.section(" ",1);
		t = f.name()+" "+t;
		tfl << t;
	//	printf("in base %s\n",t.ascii());
		++it;
	}
//	printf("DB %s : %s\n", (const char *) table, (const char *) tfl.join(",") );
	QString match;
    	for ( QStringList::iterator it1 = tfl.begin(); it1 != tfl.end(); ++it1 )
	{
		fname1 = (*it1).section( " ", 0, 0 );
		if(!isExists(fname1, &fl,match) )
		{
			// drop deprecated field
			if ( !f_drop.isEmpty() ) f_drop.append(",");
			f_drop.append( fname1 );
		}
	}
    	for ( QStringList::iterator it = fl.begin(); it != fl.end(); ++it ) {
		tc = *it;
		fname = tc.section( " ", 0, 0 );
		if( !isExists(fname,&tfl,match))
		{
			// add new field
			if ( !f_add.isEmpty() ) f_add.append(",");
			f_add.append( *it );
		} else {
		//	printf("match = %s\n",match.ascii());
			// update field type
			if ( (( const char *) tc.section(" ",1,1).lower())[0]=='o' ) tc = QString("%1 L 0 0").arg( fname );
			if ( (( const char *) tc.section(" ",1,1).lower())[0]=='b' ) tc = QString("%1 C 1 0").arg( fname );
			if ( tc.section(" ",1,1).lower().mid(1).contains( 's' ) > 0 ) {
				QString s = tc.section(" ",1,1);
				s = s.left(1)+s.mid(1).remove("S");
				tc = QString("%1 %2 %3").arg( fname ).arg( s ).arg( tc.section(" ",2));
			}
            		if ( drv == "QSQLITE" ) t = t.section(" ",0,0)+QString(" ")+tc.section(" ",1,3);
			if ( tc.section(" ",0,3) != match ) {
				//printf("section = %s\n",tc.section(" ",0,3).ascii());
				if ( !f_upd.isEmpty() ) f_upd.append(",");
				f_upd.append( *it );
			}
//			printf("fupd = %s\n", f_upd.ascii());
  //          printf("old=%s;new=%s\n", ( const char *) t, ( const char *) tc );
		}
	}
//	return (	f_drop.isEmpty() && f_add.isEmpty() &&
//			f_upd.isEmpty() && i_drop.isEmpty() &&
//			i_add.isEmpty() );

	/*
        for ( QStringList::iterator it = fl.begin(); it != fl.end(); ++it ) {
        tc = *it;
        fname = tc.section( " ", 0, 0 );
        bool found = false;
            for ( QStringList::iterator it1 = tfl.begin(); it1 != tfl.end(); ++it1 ) {
            t = *it1;
            fname1 = t.section( " ", 0, 0 );
            if ( found = ( fname == fname1 ) ) break;
            bool found1 = true;
                for ( QStringList::iterator it2 = fl.begin(); it2 != fl.end(); ++it2 ) {
                fname2 = (*it2).section( " ", 0, 0 );
                if ( found1 = ( fname1 == fname2 ) ) break;
            }
            if ( !found1 ) {
                // drop deprecated field
                if ( !f_drop.isEmpty() ) f_drop.append(",");
                f_drop.append( fname1 );
            }
        }
        if ( !found ) {
            // add new field
            if ( !f_add.isEmpty() ) f_add.append(",");
            f_add.append( *it );
        } else {
            // update field type
            if ( (( const char *) tc.section(" ",1,1).lower())[0]=='o' ) tc = QString("%1 L 0 0").arg( fname );
            if ( tc.section(" ",1,1).lower().mid(1).contains( 's' ) > 0 ) {
                QString s = tc.section(" ",1,1);
                s = s.left(1)+s.mid(1).remove("S");
                tc = QString("%1 %2 %3").arg( fname ).arg( s ).arg( tc.section(" ",2));
            }
        }
    }*/
    // Check indices
    checkIndices(table,flddef, ui_add, ui_drop);
    
    return (    f_drop.isEmpty() && f_add.isEmpty() &&
            f_upd.isEmpty() && i_drop.isEmpty() &&
            i_add.isEmpty() && ui_add.size()==0 && ui_drop.size()==0);

}

void
aDatabase::checkIndices(const QString& table, const QString& flddef, QStringList &ui_add, QStringList &ui_drop)
{
    QStringList sli=getUniqueIndices(flddef);
    QSqlCursor indices(db_indices,true,db());
    
	aLog::print(aLog::MT_INFO,tr("aDatabase check indices for %1").arg(table));
    //qWarning("Checking indices for table %s",table.ascii());
    if (true)
    {
	QDict<int> mapIndices;
	// Check for new indices
	int mark=1;
	for(uint i=0;i<sli.size();i++)
	{
	    mapIndices.insert(sli[i],&mark);
	    
		aLog::print(aLog::MT_DEBUG,tr("aDatabase search index %1").arg(sli[i]));
//	    qWarning("Searching for index %s...",sli[i].ascii());
	    indices.select(QString("(tname='%1') and (uindices='%2')").arg(table).arg(sli[i]));
	    if (!indices.next())
	    { // There's no record of such index (sli[i])
		ui_add<<sli[i];
		qWarning("Not found. Index is scheduled for addition");
	    }
	    else
	    {
		qWarning("Found.");
	    }
	}
	// Check for dropped indices
	indices.select(QString("tname='%1'").arg(table));
	while(indices.next())
	{
	    QString idx=indices.value("uindices").toString();
	    if (mapIndices.find(idx)==0)
	    {
		ui_drop<<idx;
		qWarning("Index %s is scheduled for deletion.",idx.ascii());
	    }
	}
    }
	
}

bool
aDatabase::isExists(const QString fname, QStringList *f_list, QString &match)
{
	match = "";
	for ( QStringList::iterator it = f_list->begin(); it != f_list->end(); ++it )
	{
		if(fname == (*it).section( " ", 0, 0 ))
		{
			match = (*it);
			return true;
		}
	}
	return false;
}


/*!
 * /parameters: idx - unique index (i.e. "U1")
 */
QString
aDatabase::fieldsDef( aCfgItem context, const QString & idx )
{
	int j, ifld;
	QString t, flddef="";
	aCfgItem of, item;
	int id, n=0;
	aCfgItem dim_field;
	if(cfg.objClass(context) == md_field && cfg.objClass(cfg.parent(context))== md_dimensions)
	{
		dim_field = context;
		t = cfg.attr( dim_field, mda_type );
		if ( !t.isEmpty() )
		{
			if(t[0]!=' ')
			{
				flddef.append( QString("uf%1 %2,").arg(cfg.id(dim_field)).arg(t) );
			}
		}
	}
        ifld = cfg.count( context, md_field );
        for ( j = 0; j < ifld; j++)
		{
			item = cfg.find( context, md_field, j );
			id = cfg.id( item );
			if ( id )
			{
				t = cfg.attr( item, mda_type );
				if ( !t.isEmpty() )
				{
					if(t[0]!=' ')
					{
						if (n>0) flddef.append(",");
							flddef.append( QString("uf%1 %2").arg(id).arg(t+idx) );
						n++;
					}
				}
			}
		}
		
//	printf("flddef=%s\n", (const char *) flddef);
	return flddef;
}



/*!
 *
 */
QString
aDatabase::sysFieldsDef( aCfgItem context )
{
	QString oclass = cfg.objClass( context );
	if ( oclass == md_element ) return
                "id LN 0 0 P,"          // record id
                "df C 1 0 I,"           // Mark deleted flag
                "idg L 0 0 I,"          // group uid
                "ido L 0 0 I,";         // uid для справочника владельца
	if ( oclass == md_group ) return
                "id LN 0 0 P,"          // record id
                "df C 1 0 I,"           // Mark deleted flag
                "level L 0 0 I,"        // tree level ( 0..n )
                "idp L 0 0 I,";         // parent group id ( 0 - root )
	if ( oclass == md_header ) return
                "id LN 0 0 P,";          // record id
	if ( oclass == md_table ) return
                "id LN 0 0 P,"          // record id
                "idd L 0 0 I,"         // id document object
                "ln L 0 0 I,";          // line number 1..max
	if ( oclass == md_iregister ) return
                "id LN 0 0 P,"          // record id
                "idd O 0 0 I,"          // uid document object
                "iddt O 0 0 I,"        // uid document table line
                "ln L 0 0 I,";          // line number 1..max
	if ( oclass == md_aregister ) return
                "id LN 0 0 P,"          // record id
                "idd O 0 0 I,"          // id document object
                "iddt O 0 0 I,"        // id document table line
                "ln L 0 0 I,"          // line number 1..max
                "date D 0 0 I,";         // document date
	if ( oclass == md_dimensions) return
                "date D 0 0 I,";         // document date
	return "";
}



/*!
 *
 */
bool
aDatabase::createTable(int update, const QString table, QString flddef )
{
#if 0
        QString tindex="";
	int rc=1;
	QString dquery, query;
	QSqlQuery q;
	QString f_drop, f_add, f_upd, i_drop, i_add, f;
	QStringList ui_drop,ui_add;
	QString idx, pkey="";
	QString drv = driverName();

	if ( update && !tableExists( table ) ) update = false;
	if ( update ) {
		if ( verifyTable( table, flddef, f_drop, f_add, f_upd, i_drop, i_add, ui_drop, ui_add ) ) return true;
		printf("drop=%s\nadd=%s\nupd=%s\n",
		( const char *) f_drop, ( const char *) f_add, ( const char *) f_upd );
		if ( !f_drop.isEmpty() ) {
		// Drop deprecated fields
			int n = 0;
			f = f_drop.section(",", n, n );
			while ( !f.isEmpty() ) {
				query = QString("alter table %1 drop column %2").arg( table ).arg( f );
				q = db()->exec( query );
				n++;
				f = f_drop.section(",", n, n );
			}
		}
		if ( !f_add.isEmpty() ) {
		// Add new fields
			int n = 0;
			QString ind, pkey;
			f = f_add.section(",", n, n );
			while ( !f.isEmpty() ) {
				query = QString("alter table %1 add column %2").arg( table ).arg( convFieldsDef( f, ind, pkey ) );
				q = db()->exec( query );
				n++;
				f = f_add.section(",", n, n );
			}
		}
		if ( !f_upd.isEmpty() ) {
		// Update existens filds type
			int n = 0;
			QString ind, pkey, fn;
			f = f_upd.section(",", n, n );
			while ( !f.isEmpty() ) {
				fn = f.section( " ", 0, 0 );
				if ( drv == "QPSQL7" ) {
//					db_transaction_begin();
					query = QString("alter table %1 add column __%2").arg( table ).arg( convFieldsDef( f, ind, pkey ) );
					q = db()->exec( query );
					query = QString("update %1 set __%2=%3").arg( table ).arg( fn ).arg( fn );
					q = db()->exec( query );
					query = QString("alter table %1 drop column %2").arg( table ).arg( fn );
					q = db()->exec( query );
					query = QString("alter table %1 rename column __%2 to %3").arg( table ).arg( fn ).arg( fn );
					q = db()->exec( query );
//					db_transaction_commit();
				}
	        		if ( drv == "QMYSQL3" ) {
					query = QString("alter table %1 modify column %2").arg( table ).arg( convFieldsDef( f, ind, pkey ) );
					q = db()->exec( query );
				}
				n++;
				f = f_upd.section(",", n, n );
			}
		}
	} else {
		if ( drv == "QPSQL7" ) {
			if ( tableExists( table ) ){
				query = QString("drop table %1").arg( table );
				q = db()->exec( query );
			}
			query = QString( "create table %1 (").arg( table );
			if ( !flddef.isEmpty() )	{
				query.append( convFieldsDef(flddef, tindex, pkey) );
			}
			if (pkey) {
				query.append( QString( ",primary key (%1)").arg( pkey ) );
			}
			query.append( ")" );
			printf("%s\n%s\n", (const char *) dquery, (const char *) query );
			q = db()->exec( query );
			rc = 1;
			// Создадим индексы
			if (rc) rc= createIndexes(table, tindex);
		}
	        if ( drv == "QMYSQL3" ) {
			dquery =  QString("drop table if exists %1").arg( table );
			query = QString( "create table %1 (").arg( table );
			if ( !flddef.isEmpty() )	{
				query.append( convFieldsDef( flddef, tindex, pkey ) );
			}
			if ( !pkey.isEmpty() ) {
				query.append( QString( ",primary key (%1)" ).arg( pkey ) );
			}
			query.append( ")" );
			printf("%s\n%s\n", (const char *) dquery, (const char *) query );
			q = db()->exec( dquery );
			q = db()->exec( query );
			rc = 1;
			if (rc) rc= createIndexes( table, tindex );
		}
	}
	return true;
#else
        QString tindex="";
    int rc=1;
    QString dquery, query;
    QSqlQuery q;
    QString f_drop, f_add, f_upd, i_drop, i_add, f;
    QStringList ui_drop,ui_add;
    QString idx, pkey="";
    QString drv = driverName();

    if ( update && !tableExists( table ) ) update = false;
    if ( update ) {
        if ( verifyTable( table, flddef, f_drop, f_add, f_upd, i_drop, i_add, ui_drop, ui_add ) ) return true;
   
	if(!f_drop.isEmpty()) aLog::print(aLog::MT_INFO,QObject::tr("aDatabase drop field(s) %1").arg(f_drop));
	if(!f_add.isEmpty()) aLog::print(aLog::MT_INFO,QObject::tr("aDatabase add field(s) %1").arg(f_add));
	if(!f_upd.isEmpty()) aLog::print(aLog::MT_INFO,QObject::tr("aDatabase update field(s) %1").arg(f_upd));
//	printf("drop=%s\nadd=%s\nupd=%s\n",
  //      ( const char *) f_drop, ( const char *) f_add, ( const char *) f_upd );
	dropIndexes(table,ui_drop);
	createIndexes(table,i_add,ui_add);
        if (drv=="QSQLITE")
        {
            int i=0;
            QString temptblname;
            while(tableExists(temptblname=QString("tmp%1").arg(i))) i++; // Search for name for temporary table
            createTable(false,temptblname,flddef); // create temporary table with requested schema
            // We have to transfer data from old table to new one.
            // To do this we'll make something like "INSERT INTO newtable SELECT field1,field2,'def1',def2 FROM oldtable"
            // Thanks to typelessness of SQLITE we can not bother about changes in fields' types.
            QString transfer=QString("INSERT INTO %1 SELECT ").arg(temptblname);
            int fldn=0;
            bool first=true;
            QString fname=flddef.section(",",fldn,fldn).section(" ",0,0);
            while(!fname.isEmpty())
            {
                if (f_drop.find(fname)==-1)
                { // field was not dropped
                    if (f_add.find(fname)==-1)
                    {
                        if (!first)
                            transfer.append(",");
                        transfer.append(fname);
                        first=false;
                    }
                    else
                    { // field was added. We must supply default value. I think NULL as default value will do well.
                        if (!first)
                            transfer.append(",");
                        transfer.append("null");
                        first=false;
                    };
                };
                fldn++;
                fname=flddef.section(",",fldn,fldn).section(" ",0,0);
            };
            transfer.append(QString(" FROM %1").arg(table));
            db()->exec(transfer);
            QSqlError err=db()->lastError();
            if (err.type()!=QSqlError::None)
            { // There's error in data transer, abort operation.
                return false;
            };
            // We have just transferred content of old table to temporary one.
            db()->exec(QString("DROP TABLE %1").arg(table));
            createTable(false,table,flddef);
            // Transfer content from temp table to freshly created new table.
            db()->exec(QString("INSERT INTO %1 SELECT * FROM %2").arg(table).arg(temptblname));
            db()->exec(QString("DROP TABLE %1").arg(temptblname));
        }
        else
        {
            if ( !f_drop.isEmpty() ) {
            // Drop deprecated fields
                int n = 0;
                f = f_drop.section(",", n, n );
                while ( !f.isEmpty() ) {
                    query = QString("alter table %1 drop column %2").arg( table ).arg( f );
                    q = db()->exec( query );
		    if(db()->lastError().type()!=QSqlError::None)
		    {
			QSqlError er = db()->lastError();
		    }
                    n++;
                    f = f_drop.section(",", n, n );
                }
            }
            if ( !f_add.isEmpty() ) {
            // Add new fields
                int n = 0;
                QString ind, pkey;
                f = f_add.section(",", n, n );
                while ( !f.isEmpty() ) {
                    query = QString("alter table %1 add column %2").arg( table ).arg( convFieldsDef( f, ind, pkey ) );
                    q = db()->exec( query );
		    if(db()->lastError().type()!=QSqlError::None)
		    {
			reportError(db()->lastError(),query);
		    }
                    n++;
                    f = f_add.section(",", n, n );
                }
            }
            if ( !f_upd.isEmpty() ) {
            // Update existing fields type
                int n = 0;
                QString ind, pkey, fn;
                f = f_upd.section(",", n, n );
                while ( !f.isEmpty() ) {
                    fn = f.section( " ", 0, 0 );
                    if ( drv == "QPSQL7" ) {
    //                  db_transaction_begin();
                        query = QString("alter table %1 add column __%2").arg( table ).arg( convFieldsDef( f, ind, pkey ) );
                        q = db()->exec( query );
			if(db()->lastError().type()!=QSqlError::None)
			{
				reportError(db()->lastError(),query);
			}
			query = QString("update %1 set __%2=%3").arg( table ).arg( fn ).arg( fn );
                        q = db()->exec( query );
			if(db()->lastError().type()!=QSqlError::None)
			{
				reportError(db()->lastError(),query);
			}
                        query = QString("alter table %1 drop column %2").arg( table ).arg( fn );
                        q = db()->exec( query );
			if(db()->lastError().type()!=QSqlError::None)
			{
			reportError(db()->lastError(),query);
				QSqlError er = db()->lastError();
			}
                        query = QString("alter table %1 rename column __%2 to %3").arg( table ).arg( fn ).arg( fn );
                        q = db()->exec( query );
			if(db()->lastError().type()!=QSqlError::None)
			{
				reportError(db()->lastError(),query);
			}
    //                  db_transaction_commit();
                    }
                        if ( drv == "QMYSQL3" ) {
                        query = QString("alter table %1 modify column %2").arg( table ).arg( convFieldsDef( f, ind, pkey ) );
                        q = db()->exec( query );
			if(db()->lastError().type()!=QSqlError::None)
			{
				reportError(db()->lastError(),query);
			}
                    }
                    n++;
                    f = f_upd.section(",", n, n );
                }
            }
        }
    } else {
            if ( drv == "QSQLITE" ) {
            dquery =  QString("drop table %1").arg( table );
            query = QString( "create table %1 (").arg( table );
            if ( !flddef.isEmpty() )    {
                query.append( convFieldsDef( flddef, tindex, pkey ) );
            }
            if ( !pkey.isEmpty() ) {
                query.append( QString( ",primary key (%1)" ).arg( pkey ) );
            }
            query.append( ")" );
//            printf("%s\n%s\n", (const char *) dquery, (const char *) query );
            q = db()->exec( dquery );
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),dquery);
		}
            q = db()->exec( query );
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),query);
		}
            rc = 1;
            if (rc) rc= createIndexes( table, tindex );
        }
        if ( drv == "QPSQL7" ) {
            if ( tableExists( table ) ){
                query = QString("drop table %1").arg( table );
                q = db()->exec( query );
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),query);
		}
            }
            query = QString( "create table %1 (").arg( table );
            if ( !flddef.isEmpty() )    {
                query.append( convFieldsDef(flddef, tindex, pkey) );
            }
            if (pkey!="" && !pkey.isEmpty()) {
                query.append( QString( ",primary key (%1)").arg( pkey ) );
            }
            query.append( ")" );
           // printf("%s\n", (const char *) query );
            q = db()->exec( query );
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),query);
		}
            rc = 1;
            // Создадим индексы
            if (rc) rc= createIndexes(table, tindex);
        }
            if ( drv == "QMYSQL3" ) {
            dquery =  QString("drop table if exists %1").arg( table );
            query = QString( "create table %1 (").arg( table );
            if ( !flddef.isEmpty() )    {
                query.append( convFieldsDef( flddef, tindex, pkey ) );
            }
            if ( !pkey.isEmpty() ) {
                query.append( QString( ",primary key (%1)" ).arg( pkey ) );
            }
            query.append( ")" );
            printf("%s\n%s\n", (const char *) dquery, (const char *) query );
            q = db()->exec( dquery );	
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),dquery);
		}
            q = db()->exec( query );
		if(db()->lastError().type()!=QSqlError::None)
		{
			reportError(db()->lastError(),query);
		}
		QSqlError r=q.lastError();
            rc = 1;
            if (rc) rc= createIndexes( table, tindex );
        }
    }
    return true;
#endif
}



/*!
 *
 */
bool
aDatabase::createdb( bool update )
{
	bool rc = false;

	rc = createSystables( update );
	if ( rc ) rc = createCatalogues( update );
	if ( rc ) rc = createDocuments( update );
	if ( rc ) rc = createInformationRegisters( update );
	if ( rc ) rc = createAccumulationRegisters( update );
//	if ( rc ) rc = createJournals( update );
	return rc;
}



/*!
 *
 */
bool
aDatabase::createSystables( bool update )
{
	bool rc;
	aCfgItem i;
	i.clear();
	rc= createTable(update,
        "uniques",
	"id LNS 0 0 P,"
	"otype I 0 0 I,"
	"df C 1 0 I");
	cfg_message(0, ( const char *) tr("Uniques table updated\n").utf8());

	if ( rc ) rc = createTable(update,
        "a_journ",
	"id LN 0 0 P,"
	"typej I 0 0 I,"
	"idd L 0 0 I,"
	"typed I 0 0 I,"
	"ddate D 0 0 I,"
	"pnum CN 254 0 I,"//reg num prefix
	"num I 10 0 I,"//reg num
	"mf C 1 0 I,"// marked flag
	"df C 1 0 I,"//delete flag
	"cf C 1 0 I");//conducte flag
	cfg_message(0, ( const char *) tr("Documents journal updated\n").utf8());
        if ( rc ) rc = createTable(update,
        db_users,
	"id LN 0 0 P,"
	"fname C 25 0 I,"
	"lname C 30 0 I,"
	"login C 20 0 I,"
	"password C 100 0 I");
	cfg_message(0, ( const char *) tr("Users updated\n").utf8());
        if ( rc ) rc = createTable(update,
        db_user_roles,
	"id O 0 0 I,"
	"idr O 0 0 I");
	cfg_message(0, ( const char *) tr("Users roles updated\n").utf8());
        if ( rc ) rc = createTable(update,
        db_roles,
	"id LN 0 0 P,"
	"name C 50 0 I,");
	cfg_message(0, ( const char *) tr("Roles updated\n").utf8());
        if ( rc ) rc = createTable(update,
        db_right_roles,
	"idr O 0 0 I,"
	"permission I 25 0 I,"
	"object O 0 0 I,");
	cfg_message(0, ( const char *) tr("Rigths updated\n").utf8());
	if (rc) rc=createTable(update,db_indices,
	"tname C 40 * I,"
	"uindices C 240 * I,"
	"idxname C 64 * I"
	);
	return rc;
}



/*!
 *
 */
bool
aDatabase::createCatalogues( bool update )
{
	QSqlRecordInfo ts;
	QSqlFieldInfo f;
//	aTable *t;
	aCfgItem gcont, cont, item;
	long id;
//	aCatalogue *c;
	int n, i;
	bool rc = true;

	gcont = cfg.find( cfg.find(mdc_metadata), md_catalogues, 0 );
	n = cfg.count( gcont, md_catalogue );
	for (i = 0; i<n; i++ ) {
		item = cfg.find( gcont, md_catalogue, i );
		if ( !item.isNull() ) {
//			printf("cat = %s\n", (const char *) cfg.attr( item, mda_name ) );
			id = cfg.id( item );
			cont = cfg.findChild( item, md_element, 0 );
			if ( !cont.isNull() ) {
        			rc = createTable(update,
        				tableDbName( cfg, cont ),
						sysFieldsDef( cont )
					+ fieldsDef( cont ));
			}
			cont = cfg.findChild( item, md_group, 0 );
			if ( !cont.isNull() ) {
        			rc = createTable(update,
        				tableDbName( cfg, cont ),
					sysFieldsDef(cont)
					+ fieldsDef( cont ) );
  			}
			cfg_message(0, ( const char *) tr("Catalogue %s updated\n").utf8(),
			(const char *) cfg.attr( item, mda_name ).utf8() );
		}
	}
	return rc;
}



/*!
 *
 */
bool
aDatabase::createDocuments( bool update )
{
	QSqlRecordInfo ts;
	QSqlFieldInfo f;
//	aTable *t;
	aCfgItem rcont, cont, item, tcont;
//	aCatalogue *c;
	int n, i, tn, ti;
	bool rc = true;

	rcont = cfg.find( cfg.find(mdc_metadata), md_documents, 0 );
	n = cfg.count( rcont, md_document );
	for (i = 0; i<n; i++ ) {
		item = cfg.find( rcont, md_document, i );
		if ( !item.isNull() ) {
//			printf("doc = %s\n", (const char *) cfg.attr( item, mda_name ) );
			cont = cfg.findChild( item, md_header, 0 );
			if ( !cont.isNull() ) {
        			rc = createTable(update,
        				tableDbName( cfg, cont ),
					sysFieldsDef(cont)
					+ fieldsDef( cont ) );
			}
			tcont = cfg.find( item, md_tables, 0 );
			tn = cfg.count( tcont, md_table );
			for (ti = 0; ti < tn; ti++ )
			{
				cont = cfg.findChild( tcont, md_table, ti );
				if ( !cont.isNull() )
				{
						rc = createTable(update,
				        				tableDbName( cfg, cont ),
										sysFieldsDef(cont) + fieldsDef( cont ) );
				}
			}
		}
		cfg_message(0, ( const char *) tr("Document %s updated\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
	}
	return rc;
}



/*!
 *
 */
bool
aDatabase::createJournals( bool ) //update )
{
/*	QSqlRecordInfo ts;
	QSqlFieldInfo f;
//	aTable *t;
	aCfgItem gcont, cont, item;
	long id;
//	aCatalogue *c;
	int n, i;
	bool rc = true;

	gcont = cfg.find( cfg.find(mdc_root), md_journals, 0 );
	n = cfg.count( gcont, md_catalogue );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( gcont, md_journal, i );
		if ( !item.isNull() )
		{
//			printf("cat = %s\n", (const char *) cfg.attr( item, mda_name ) );
			id = cfg.id( item );
			cont = cfg.findChild( item, md_columns, 0 );
			if ( !cont.isNull() )
			{
        			rc = createTable(update,
        				QString("jc%1").arg( id ),
					"id LN 0 0 P,"
					+ fieldsDef( cont ));
			}
			cfg_message(0, ( const char *) tr("Journal %s updated\n"),
			(const char *) cfg.attr( item, mda_name ).utf8() );
		}
	}
	return rc;*/
        return false;
}



/*!
 *
 */
bool
aDatabase::createInformationRegisters( bool update )
{
	aCfgItem rcont, cont, item;
	int n, i;
	bool rc = true;
	QString filds;

	rcont = cfg.find( cfg.find(mdc_metadata), md_iregisters, 0 );
	n = cfg.count( rcont, md_iregister );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( rcont, md_iregister, i );
		if ( !item.isNull() )
			rc = createTable(update, tableDbName(cfg,item),sysFieldsDef(item)+ fieldsDef( item ));
		cfg_message(0, ( const char *) tr("Information registers %s updated\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
	}
	return rc;
}



/*!
 *
 */
bool
aDatabase::createAccumulationRegisters( bool update )
{
	aCfgItem rcont, cont, item, res, dim;
//	long id;
	int n, i;
	bool rc = true;
	QString filds;
	rcont = cfg.find( cfg.find(mdc_metadata), md_aregisters, 0 );
	n = cfg.count( rcont, md_aregister );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( rcont, md_aregister, i );
		if ( !item.isNull() )
		{
			rc = createTable(update, tableDbName(cfg,item),sysFieldsDef(item)+ fieldsDef( item ));
			//rc = createTable(update, tableDbName(cfg,item) + "_arh",sysFieldsDef(item)+
			//				fieldsDef( item )); //tablle for store data for close periods
			res = cfg.find( item, md_resources );
			dim = cfg.find( item, md_dimensions );
			if ( !res.isNull() && !dim.isNull() )
/*<<<<<<< adatabase.cpp
			{
				rc = createTable(update, tableDbName(cfg,res), sysFieldsDef(res)+fieldsDef(dim,"U1")\
								+","+fieldsDef(res));
				// We must create unique index on resource and system fields to simplify remainder creation.
//				QString ifld, iflds=sysFieldsDef(res)+fieldsDef(dim);
//				QString flds;
//				QString tbl=tableDbName(cfg,res);
//				for(int i=0;!(ifld=iflds.section(',',i,i)).isEmpty();i++)
//				{
//					ifld=ifld.section(' ',0,0); // ifld contains field name now.
//					flds+=(i==0?"":",")+ifld;
//				}
//				QString qry=QString("create unique index %1 on %2 (%3)").arg(tbl+"_idx_uniq").arg(tbl).arg(flds);
//				QSqlError err=db()->exec(qry).lastError();
//				if (err.type()!=QSqlError::None)
//				{
//					qWarning("%s %s",err.driverText().ascii(),err.databaseText().ascii());
//				}
			}
=======
*/			{
				aCfgItem d;
				for(uint k=0; k<cfg.count(dim,md_field);k++)
				{
					d = cfg.findChild(dim,md_field,k);
					rc = createTable(update, tableDbName(cfg,d), sysFieldsDef(dim)+fieldsDef(d)+fieldsDef(res));
				}
			}
//>>>>>>> 1.63.2.4
		}
		cfg_message(0, ( const char *) tr("Accumulation registers %s updated\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
	}
	return rc;
}



/*!
 *	\~english
 *	Sets delete flag to true in system table for \a uid.
 *	\~russian
 *	Устанавливает флаг удаления в true в системной таблице для заданного \a uid
 *	\~
 *	\see deleteMarked()
 *	\param uid - \~english id for mark deleted \~russian id для пометки на удаление \~
 */
void
aDatabase::markDeleted(Q_ULLONG uid)
{
	db()->exec(QString("UPDATE uniques SET df='1' WHERE id=%1").arg(uid));
}


/*!
 *	\~english
 *	Delete all marked records.
 *	\~russian
 *	Удаляет все помеченные записи.
 *	\~
 *	\see markDeleted(Q_ULLONG uid)
 */
void
aDatabase::deleteMarked()
{
	db()->exec("DELETE FROM uniques WHERE df='1'");
}


QStringList
aDatabase::supportedDriverList()
{
	QStringList l;
	l<<"internal";
	l<<"mysql";
	l<<"postgresql";
	return l;
}

/*!
 *	getUniqueIndices procedure parses table definition and returns list of string in form 'U'<num>'%1('<field-list>')'
 *	Syntax of index field of table definition is extended to allow using of multicolumn indices.
 *	For each multicolumn index column 'U'<num> character sequence 
 *	should be added to index field of column definition, where <num> is a number of multicolumn index.
 *	Example: Definition "a c 20 * pu1,b c 30 * iu1,c d * * u2,d n 10 3 u2" leads to creation of two 
 *	multicolumn indices: (a,b) and (c,d).
 *	\param flddefs (in) - database table definition
 *	\returns list of string in form 'U'<num>'%1('<field-list>')'
 *	
 *	returned strings can be easily used to create SQL-query for index creation as follows:
 *	query="create unique index "+tablename+"_uniq_"+retval.arg(" on "+tablename)
 */
QStringList aDatabase::getUniqueIndices(const QString & flddefs)
{
    const uint MAX_INDICES=32;
    QStringList indfields[MAX_INDICES];
    int n=0;
    QStringList sl;
    QString fdef=flddefs.section(',',n,n).stripWhiteSpace();
    while(!fdef.isEmpty())
    {
//	qWarning("flddef: %s",fdef.ascii());
	QString fname=fdef.section(' ',0,0,QString::SectionSkipEmpty);
	QString idcs=fdef.section(' ',4,4,QString::SectionSkipEmpty);
	if (!idcs.isEmpty())
	{
	    // Here will be parsing of unique indices definition.
//	    qWarning("idcs %s, fname %s",idcs.ascii(),fname.ascii());
	    idcs=idcs.lower();
	    QStringList idcnums=QStringList::split('u',idcs);
	    for(QStringList::size_type i=0;i<idcnums.size();i++)
	    {
		bool ok;
		uint inum=idcnums[i].toUInt(&ok);
//		qWarning("num%d - %d",i,inum);
		if (!ok)
		    continue;
		if (inum>=MAX_INDICES)
		{
		    qWarning("Maximum number of unique indices per table exceeded.");
		    continue;
		}
		indfields[inum]<<fname;
	    }
	}
	n++;
	fdef=flddefs.section(',',n,n);
    }
    for(uint i=0;i<MAX_INDICES;i++)
    {
//	qWarning("Index #%d size %d:",i,indfields[i].size());
	if (indfields[i].size()>0)
	{
	    QString idxdef=QString("U%1").arg(i)+QString("%1(");
	    for(uint j=0;j<indfields[i].size()-1;j++)
	    {
//		qWarning("%s,",indfields[i][j].ascii());
		idxdef+=indfields[i][j]+",";
	    }
	    idxdef+=indfields[i][indfields[i].size()-1]+")";
//	    qWarning("%s,%s",indfields[i][indfields[i].size()-1].ascii(),idxdef.ascii());
	    sl<<idxdef;
	}
    }
    return sl;
}


bool
aDatabase::exchangeDataSystables ( QDomDocument &xml, bool import)
{
	bool res = false;
	if(import)
	{
		res |= importTableData(xml,"a_journ");
		res |= importTableData(xml,db_users);
		res |= importTableData(xml,db_user_roles);
		res |= importTableData(xml,db_roles);
		res |= importTableData(xml,db_right_roles);
		res |= importTableData(xml,db_indices);
		
	}
	else
	{
		res |= exportTableData(xml,"a_journ");
		res |= exportTableData(xml,db_users);
		res |= exportTableData(xml,db_user_roles);
		res |= exportTableData(xml,db_roles);
		res |= exportTableData(xml,db_right_roles);
		res |= exportTableData(xml,db_indices);
	}
	return res;
}

bool 
aDatabase::exchangeDataUniques ( QDomDocument &xml, bool import)
{
	bool res = false;
	if(import) 
	{
		res |= importTableData(xml,"uniques");
	}
	else
	{
		res |= exportTableData(xml,"uniques");
	}
	return res;
}

bool
aDatabase::exchangeDataCatalogues (QDomDocument &xml, bool import)
{
	aCfgItem gcont, cont, item;
	long id;
	int n, i;
	bool rc = false;

	gcont = cfg.find( cfg.find(mdc_metadata), md_catalogues, 0 );
	n = cfg.count( gcont, md_catalogue );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( gcont, md_catalogue, i );
		if ( !item.isNull() )
		{
//			printf("cat = %s\n", (const char *) cfg.attr( item, mda_name ) );
			id = cfg.id( item );
			cont = cfg.findChild( item, md_element, 0 );
			if ( !cont.isNull() )
			{
				if(import)
				{
					rc |= importTableData(xml, tableDbName( cfg, cont ));
				}
				else
				{
					rc|= exportTableData(xml, tableDbName( cfg, cont ));
				}
			}
			cont = cfg.findChild( item, md_group, 0 );
			if ( !cont.isNull() )
			{
				if(import)
				{
					rc |= importTableData(xml, tableDbName( cfg, cont ));
				}
				else
				{
					rc|= exportTableData(xml, tableDbName( cfg, cont ));
				}
  			}
			cfg_message(0, ( const char *) tr("Catalogue %s processed\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
			if(import)
			{
				aLog::print(aLog::MT_INFO,tr("aDatabase catalogue %1 import").arg(cfg.attr( item, mda_name )));
			}
			else
			{
				aLog::print(aLog::MT_INFO,tr("aDatabase catalogue %1 export").arg(cfg.attr( item, mda_name )));
			}
		}
	}
	return rc;
//	return true;
}


bool
aDatabase::exchangeDataDocuments (QDomDocument &xml, bool import)
{
	aCfgItem rcont, cont, item, tcont;
	int n, i, tn, ti;
	bool rc = false;

	rcont = cfg.find( cfg.find(mdc_metadata), md_documents, 0 );
	n = cfg.count( rcont, md_document );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( rcont, md_document, i );
		if ( !item.isNull() ) 
		{
		//	printf("doc = %s\n", (const char *) cfg.attr( item, mda_name ) );
			cont = cfg.findChild( item, md_header, 0 );
			if ( !cont.isNull() )
			{
				if(import)
				{
					rc |= importTableData(xml, tableDbName( cfg, cont ));
				}
				else
				{
					rc|= exportTableData(xml, tableDbName( cfg, cont ));
				}
			}
			tcont = cfg.find( item, md_tables, 0 );
			tn = cfg.count( tcont, md_table );
			for (ti = 0; ti < tn; ti++ )
			{
				cont = cfg.findChild( tcont, md_table, ti );
				if ( !cont.isNull() )
				{
					if(import)
					{
						rc |= importTableData(xml, tableDbName( cfg, cont ));
					}
					else
					{
						rc|= exportTableData(xml, tableDbName( cfg, cont ));
					}
				}
			}
		}
		cfg_message(0, ( const char *) tr("Document %s processed\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
		if(import)
		{
			aLog::print(aLog::MT_INFO,tr("aDatabase document %1 import").arg(cfg.attr( item, mda_name )));
		}
		else
		{
			aLog::print(aLog::MT_INFO,tr("aDatabase document %1 export").arg(cfg.attr( item, mda_name )));
		}
	}
	return rc;
}


bool
aDatabase::exchangeDataJournals (QDomDocument &xml, bool import)
{
	return false;
}


bool
aDatabase::exchangeDataInfoRegisters (QDomDocument &xml, bool import)
{
	aCfgItem rcont, cont, item;
	int n, i;
	bool rc = false;
	QString filds;

	rcont = cfg.find( cfg.find(mdc_metadata), md_iregisters, 0 );
	n = cfg.count( rcont, md_iregister );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( rcont, md_iregister, i );
		if ( !item.isNull() )
		{
			
			if(import)
			{
				rc |= importTableData(xml, tableDbName( cfg, cont ));
			}
			else
			{
				rc|= exportTableData(xml, tableDbName( cfg, cont ));
			}
		}
		cfg_message(0, ( const char *) tr("Information registers %s processed\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
		if(import)
		{
			aLog::print(aLog::MT_INFO,tr("aDatabase information register %1 import").arg(cfg.attr( item, mda_name )));
		}
		else
		{
			aLog::print(aLog::MT_INFO,tr("aDatabase information register %1 export").arg(cfg.attr( item, mda_name )));
		}
	}
	return rc;
}


bool
aDatabase::exchangeDataAccumulationRegisters (QDomDocument &xml, bool import)
{
	aCfgItem rcont, cont, item, res, dim;
	int n, i;
	bool rc = false;
	QString filds;
	rcont = cfg.find( cfg.find(mdc_metadata), md_aregisters, 0 );
	n = cfg.count( rcont, md_aregister );
	for (i = 0; i<n; i++ )
	{
		item = cfg.find( rcont, md_aregister, i );
		if ( !item.isNull() )
		{
			if(import)
			{
				rc |= importTableData(xml, tableDbName( cfg, item ));
			}
			else
			{
				rc|= exportTableData(xml, tableDbName( cfg, item ));
			}
			res = cfg.find( item, md_resources );
			dim = cfg.find( item, md_dimensions );
			if ( !res.isNull() && !dim.isNull() )
			{
				aCfgItem d;
				for(uint k=0; k<cfg.count(dim,md_field);k++)
				{
					d = cfg.findChild(dim,md_field,k);
					if(import)
					{
						rc |= importTableData(xml, tableDbName( cfg, d ));
					}
					else
					{
						rc|= exportTableData(xml, tableDbName( cfg, d ));
					}
				}
			}
		}
		cfg_message(0, ( const char *) tr("Accumulation registers %s processed\n").utf8(),(const char *) cfg.attr( item, mda_name ).utf8() );
		if(import)
		{
			aLog::print(aLog::MT_INFO,tr("aDatabase accumulation register %1 import").arg(cfg.attr( item, mda_name )));
		}
		else
		{
			aLog::print(aLog::MT_INFO,tr("aDatabase accumulation register %1 export").arg(cfg.attr( item, mda_name )));
		}
	}
	return rc;
}
	

bool
aDatabase::exportTableData(QDomDocument& xml, const QString &tableName)
{
	aDataTable *dataTable = table(tableName);
	dataTable->select();
	QDomElement xml_root = xml.documentElement();
	if (xml_root.isNull())
	{
		aLog::print(aLog::MT_ERROR,tr("aDatabase export table: invalid XML file"));
//		printf("xml has no root element");
		return true;
	}
	QDomElement table = xml.createElement("table");
	table.setAttribute("name",tableName);
	QDomElement row;
	QDomElement field;
	xml_root.appendChild(table);
	if(!dataTable->first()) return false;
	do
	{
		uint countField = dataTable->count();
		QVariant val;
		row = xml.createElement("row");
		table.appendChild(row);
		for(uint i=0; i<countField; i++)
		{
			val = dataTable->value(i);
			if( val.isValid() )
			{
				field = xml.createElement("field");
				field.setAttribute("name",dataTable->fieldName(i));
				field.appendChild(xml.createTextNode(val.toString()));
				row.appendChild(field);
			}
		}
	}while(dataTable->next());
	return false;
}


bool
aDatabase::importTableData( QDomDocument &xml, const QString &tableName)
{
//	printf("import table data %s\n",tableName.ascii());
	QDomElement root = xml.documentElement();
	if(root.nodeName() != "AnanasDump") 
	{
		
		aLog::print(aLog::MT_ERROR,tr("aDatabase import table: invalid XML file"));
		//printf("uncnown data format\n");
		return true;
	}
	QDomNodeList tables = root.childNodes();
	uint countTables = tables.count();
	for(uint i=0; i<countTables; i++)
	{
	//	printf("tableName==%s\n", tables.item(i).toElement().attribute("name").ascii());
		if(tables.item(i).toElement().attribute("name") == tableName)
		{
			// found table
			aDataTable *tbl;
			if(!tableExists(tableName))
			{
				aLog::print(aLog::MT_ERROR,tr("aDatabase import table: table %1 not exists").arg(tableName));
				//printf("table %s not exists\n",tableName.ascii());
				return true;
			}
			//printf("table exists\n");
			tbl = table(tableName);
			if(!tbl)
			{
				aLog::print(aLog::MT_ERROR,tr("aDatabase import table: get table %1").arg(tableName));
				//printf("table is NULL\n"); 
				return true;
			}
			QDomNodeList rows = tables.item(i).childNodes();
			QDomNodeList fields;
			uint countRows = rows.count();
			uint countFields;
			QSqlRecord *buffer;
			QDomElement field;
			QString query = "delete from uniques";
			if(tableName=="uniques")
			{
				db()->exec(query);
			}
			for( uint j=0; j<countRows; j++)
			{
				fields = rows.item(j).childNodes();
				countFields = fields.count();
				if(tableName=="uniques")
				{
					// удаляем все строки в таблице
					if(fields.item(0).toElement().hasChildNodes() && fields.item(1).toElement().hasChildNodes())
					{
						query = QString("INSERT INTO %1 (id,otype) values(%2,%3)")
							.arg(tableName) 
							.arg(fields.item(0).toElement().toElement().text()) 
							.arg(fields.item(1).toElement().toElement().text());
				//		printf("query = %s\n",query.ascii());
						// добавляем записи с правильными идентификатораи
						db()->exec(query);

					}
				}
				else
				{
					buffer = tbl->primeInsert();
					for( uint k=0; k<countFields; k++)
					{
						field = fields.item(k).toElement();
						if(field.hasChildNodes())
						{
					//	printf("node have child\n");
					
							buffer->setValue(field.attribute("name"),field.toElement().text());		
						}
					}
					tbl->insert();
				}
			}
			break;
		}
	}
	return false;
}

void
aDatabase::reportError(QSqlError er, const QString &query)
{
	aLog::print(aLog::MT_ERROR, QObject::tr("aDatabase query: %1").arg(query) );
	aLog::print(aLog::MT_ERROR, QObject::tr("aDatabase text: %1").arg(er.text()) );
	aLog::print(aLog::MT_ERROR, QObject::tr("aDatabase database text: %1").arg(er.databaseText()) );
	aLog::print(aLog::MT_ERROR, QObject::tr("aDatabase driver text: %1").arg(er.driverText()) );
}
