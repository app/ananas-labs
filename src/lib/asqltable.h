/****************************************************************************
** $Id: asqltable.h,v 1.49 2007/09/04 13:30:23 app Exp $
**
** Header file of the Ananas database table of Ananas
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

#ifndef ASQLTABLE_H
#define ASQLTABLE_H
#include <qsqlcursor.h>
#include <qdict.h>
#include "acfg.h"
//#include "aaregister.h"
//#include "adatarecord.h"

// temporray define for old definitions
#define aSQLTable aDataTable


class aDatabase;
class aSQLField;

/*!
 *	\~english
 *	Provides browsing and editing Ananas's sql tables mantained by Ananas.Designer.
 *	\~russian
 *	\brief Определяет программный интерфейс модели данных aDataTable. Наследует QSqlCursor.
 *
 *	Позволяет работать с табличными представлениями данных, определенных метаданными бизнес схемы.
 *	\~
 */
class  ANANAS_EXPORT aDataTable : public QSqlCursor
{
public:
	aDatabase*	db;
	QString 	tableName;
	bool 		selected;
	
				aSQLTable( aCfgItem context, aDatabase *adb );
				aSQLTable( const QString &tname, aDatabase *adb );
	virtual 	~aSQLTable();
	void 		init( aCfgItem context, aDatabase *adb );
	void 		setObject(aCfgItem context);
	void 		appendField( aSQLField * fieldinfo );
	void 		insertField( int pos, aSQLField * fieldinfo );
	void 		removeField( int pos );
	void 		clearFields();
	bool 		checkStructure( bool update );
	long 		getMdObjId();
	Q_ULLONG 	getIdd();
	void		printRecord();
	//QDict<QVariant> getUserFilter();
	//void		setUserFilter( QDict<QVariant> );
	
	virtual QVariant	value ( int i );
	virtual QVariant	value ( const QString & name );
	virtual void		setValue ( int i, QVariant value );
	virtual bool		setValue ( const QString & name, QVariant value );
	virtual QVariant	sysValue ( const QString & name );
	virtual void		setSysValue ( const QString & name, QVariant value );
	virtual bool		sysFieldExists( const QString & name );

	virtual QSqlRecord*	primeInsert();
//	virtual QSqlRecord*	primeUpdate();

	virtual bool		select( const QString & filter="", bool usefltr = true );
	virtual bool		select( Q_ULLONG id );
	virtual void		clearFilter();
	virtual bool		setFilter( const QString &name, const QVariant &value );
	virtual void		setFilter( const QString& );
	virtual QString		getFilter();
	virtual QString		getNFilter();
	virtual bool		exec( QString query );
	virtual QStringList	getUserFields();
	virtual ERR_Code 	setMarkDeleted( bool Deleted );
	virtual bool 		isMarkDeleted();
	QString 		sqlFieldName ( const QString & userFieldName ) const;

	virtual bool New();
	virtual bool Copy();
	virtual bool Delete();
	virtual bool Update();

	virtual bool seek ( int i, bool relative = FALSE );
	virtual bool next ();
	virtual bool prev ();
	virtual bool first ();
	virtual bool last ();


protected:
	QVariant	calcFieldValue( const QString &name );
	virtual		QVariant calculateField( const QString &name );
	virtual		QVariant calc_obj(int fid,Q_ULLONG idd);
	virtual		QVariant calc_rem(int fid,Q_ULLONG id);
	void		insertFieldInfo(aCfgItem cobj, bool calculated=true);
	
	long		mdobjId;

private:
//	bool fNewNotUpdated;
	aCfgItem		obj;
	aCfgItem		init_obj;
	aCfg*			md;
	QDict<QObject>	p_cat;
	QDict<QObject>	p_doc;
	QDict<QObject>	p_reg;
	QMap<int,aCfgItem> mapCat, mapReg, mapDoc;
	QMap<int,QString> mapDim,mapSum;
	QStringList		fildsList;
	QDict<QString>	fnames;
	QDict<QVariant>	userFilter;
//	QDict<aDataField> dataRecord;
//	aDataRecord dataRecord;
//	QSqlRecord r;
};

#endif
