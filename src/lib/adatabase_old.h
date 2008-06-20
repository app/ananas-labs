/****************************************************************************
** $Id: adatabase_old.h,v 1.1 2007/03/17 11:12:35 leader Exp $
**
** Header file of the ananas database of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2005 Grigory Panov <gr1313 at mail dot ru >, Yoshkar-Ola
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

#ifndef ADATABASE_H
#define ADATABASE_H
#include <qobject.h>
#include <qstringlist.h>
#include <qsqldatabase.h>
#include <qdict.h>
#include "acfg.h"
#include <qwidget.h>


#define db_document_header	"dh%1"
#define db_document_table	"dt%1_%2"
#define db_catalog_element	"ce%1"
#define db_catalog_group	"cg%1"
#define db_iregister		"ri%1"
#define db_aregister		"ra%1"
#define db_areg_remainder	"ra%1_rem"
#define db_user_roles		"usr_rl"
#define db_users		"usr"
#define db_roles		"rl"
#define db_right_roles		"r_rl"
#define db_indices		"idc"
#define db_areg_dim		"ra%1_d%2"

class aDatabase;
class aCfgRc;
class aDataTable;

//extern aDatabase database;

/*!
 *\~english
 *	Database driver abstraction layer class.
 *	Used for working with SQL database on ananas data context.
 *\~russian
 *	\brief Базовый класс для драйверов баз данных.
 *	Наследует QObject.
 *	
 *	Используется для абстрагирования доступа к базе данных в
 *	терминах типов данных Ананаса.
 *\~
 */
class aDataDriver: public QObject
{
	Q_OBJECT
public:
	aDataDriver();
	~aDataDriver();
};


class aDataDriver_SQLITE: public aDataDriver
{
	Q_OBJECT
public:
	aDataDriver_SQLITE();
	~aDataDriver_SQLITE();

};

class aDataDriver_MYSQL: public aDataDriver
{
	Q_OBJECT
public:
	aDataDriver_MYSQL();
	~aDataDriver_MYSQL();

};


class aDataDriver_PGSQL: public aDataDriver
{
	Q_OBJECT
public:
	aDataDriver_PGSQL();
	~aDataDriver_PGSQL();

};


/*!
 *\~english
 *	Database abstraction layer class.
 *	Used for working with SQL database on metadata context.
 *\~russian
 *	\brief Класс для работы с СУБД. Ananas Data Abstraction Layer.
 *	Наследует QObject.
 *	
 *	Обеспечивает унифицированный программный интерфейс доступа к данным, независимый от используемой СУБД.
 *	Используется для работы с базой данных в контексте бизнес схемы.
 *\~
 */
class  ANANAS_EXPORT aDatabase: public QObject
{
	Q_OBJECT

public slots:
public:
	/*! \~english type of database drivers \~russian перечисление типов баз данных \~ */
	enum dbServer
	{
	/*!	\~english Unknown driver (not supported)\~russian   Неизвестный драйвер (не поддерживается)\~ */
	unknown,
	/*!	\~english MySQL driver \~russian MySQl драйвер \~ */
	mysql,
	/*!	\~english PostgreSQL driver \~russian PostgreSQL драйвер \~ */
	postgresql,
	/*!	\~english ODBC driver (not supported)\~russian ODBC драйвер (не поддерживается) \~ */
	odbc,
	/*!	\~english Oracle driver (not supported)\~russian Oracle драйвер (не поддерживается) \~ */
	oracle,
	/*!	\~english MSSQL driver (not supported)\~russian MSSQL драйвер (не поддерживается) \~ */
	mssql,
	/*!	\~english Sybase driver (not supported)\~russian Sybase драйвер (не поддерживается) \~ */
	sybase };
	/*! \~english link to database \~russian ссылка на базу данных \~ */
	QSqlDatabase *ddb;
	/*! \~english metadata object \~russian метаданные \~ */
	aCfg cfg;

	aDatabase();
	~aDatabase();
	bool init( aCfgRc *rc, const QString &dbname = QString::null );
	bool init( const QString &rcname, const QString &dbname = QString::null );
	void done();
	QSqlDatabase* db(const QString &dbname = QString::null );
	bool checkStructure();
	bool create();
	bool drop( const QString &);
	bool update();
	Q_ULLONG uid( int otype );
//	int otype( Q_ULLONG uid );
	int uidType ( Q_ULLONG uid );
	aDataTable *table( const QString & name = QString::null );
	bool tableExists( const QString & name );
	void markDeleted(Q_ULLONG uid);
	void deleteMarked();
        QString driverName();

//	static QString tableDbName( aCfg &md, aCfgItem context, long * tid = 0 );
	static QStringList supportedDriverList();
	static QStringList getUniqueIndices(const QString & flddef);

	static QString tableDbName( aCfg &md, aCfgItem context, long * tid);
	static QString tableDbName( aCfg &md, aCfgItem context);

	bool exchangeDataSystables	 ( QDomDocument &xml, bool import );
	bool exchangeDataCatalogues	 ( QDomDocument &xml, bool import );
	bool exchangeDataDocuments	 ( QDomDocument &xml, bool import );
	bool exchangeDataJournals	 ( QDomDocument &xml, bool import );
	bool exchangeDataInfoRegisters	 ( QDomDocument &xml, bool import );
	bool exchangeDataAccumulationRegisters	 ( QDomDocument &xml, bool import );
	bool exchangeDataUniques 	 ( QDomDocument &xml, bool import );


private:
	bool exportTableData(QDomDocument& xml, const QString &tableName);
	bool importTableData(QDomDocument& xml, const QString &tableName);
	void reportError(QSqlError er, const QString &query);
	
	QString fieldtype( const QString &tdef );
	void checkIndices(const QString &table, const QString &flddef, QStringList &ui_add, QStringList &ui_drop);
	bool isExists(const QString fname, QStringList *f_lst, QString &match);
	QString fieldsDef( aCfgItem context, const QString &idx=QString::null);
	QString sysFieldsDef ( aCfgItem context );
	QString convFieldsDef( const QString flddef, QString &idxdef, QString &pkey );
	bool createdb( bool update );
	bool createIndexes(const QString &table, const QString &indexl, const QStringList & uidc=QStringList());
	bool dropIndexes(const QString &table, const QStringList &indices=QStringList());
	bool verifyTable( const QString &table, const QString &flddef,
	QString &f_drop, QString &f_add, QString &f_upd,
	QString &i_drop, QString &i_add, QStringList & ui_drop, QStringList & ui_add);
	bool createTable(int update, const QString table, QString flddef );
	bool createSystables( bool update );
	bool createCatalogues( bool update );
	bool createDocuments( bool update );
	bool createJournals( bool update );
	bool createInformationRegisters( bool update );
	bool createAccumulationRegisters( bool update );
	bool dumpTable( QDomDocument& xml, const QString &tableName);
	void fillFeatures();
	QString feature(const QString& fetureName);
	
	QMap<QString, QString> featuresMySQL, featuresSQLite, featuresPostgreSQL;

};

#endif
