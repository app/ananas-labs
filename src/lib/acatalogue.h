/****************************************************************************
** $Id: acatalogue.h,v 1.36 2008/04/12 18:05:35 app Exp $
**
** Catalogue metadata object header file of 
** Ananas application library
**
** Created : 20031201
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

#ifndef ACATALOGUE_H
#define ACATALOGUE_H

#include	"acfg.h"
#include 	"aobject.h"

class aDatabase;
class aCatGroup;
//class aObject;



/*!\en
 *	Not visual object used for working with catalogues in database.
 *	Used as interface between database and script or wObjects*
 *\_en 
 *\ru
 *\brief Класс aCatalogue определяет программный интерфейс иерархических справочников.
 *	Наследует aObject.
 *
 *	Не визуальный объект используемый для работы с иерархическими каталогами (справочниками).
 *	Используется как интерфейс между базой данных и скриптами или wObjects*
 *\_ru
 */
class  ANANAS_EXPORT aCatalogue :public aObject
{
	Q_OBJECT
public:

	aCatalogue(aCfgItem context, aDatabase * adb = 0);
	aCatalogue(QString name, aDatabase * adb = 0);
//	virtual ERR_Code initObject(aDatabase * adb);
	virtual ERR_Code initObject();

protected:
	virtual aCfgItem displayStringContext();

private:
//	Q_ULLONG getCatGroup();
	Q_ULLONG getGroup();
//	Q_ULLONG getOwner();
//	ERR_Code setOwner( Q_ULLONG ido );
//	ERR_Code setGroup( Q_ULLONG idg );
	ERR_Code selectByOwner ( Q_ULLONG ido );
	ERR_Code groupSelect ();
	ERR_Code groupByParent(Q_ULLONG idp );
public slots:
	//virtual aCatGroup * group();
	virtual int New( bool child);
	virtual int New();
	virtual int Delete();

	virtual int newGroup( Q_ULLONG parentId );
	virtual int newElement( Q_ULLONG parentId );

	virtual int Update();
	virtual int Copy();
//	virtual int SetOwner( aCatalogue * cat );
//	virtual int SetGroup( aCatalogue * cat );
	virtual int Select( bool grouponly = false );
	void UnSelect( bool grouponly = false );
	virtual int selectByLevel ( int level );
	virtual int selectByGroup ( Q_ULLONG idg );
	virtual Q_ULLONG idGroupByElement(Q_ULLONG ide );
	virtual int groupSelect ( Q_ULLONG idg );

	virtual QVariant GetElementValue(QVariant ide, const QString &fname);
	virtual bool FindById(QString el_id);
		
	virtual Q_ULLONG delElement();
	virtual Q_ULLONG delGroup(Q_ULLONG idg, QValueList<Q_ULLONG> &listDelId);
	
	Q_ULLONG setMarkDeletedElement(Q_ULLONG el_id, bool del);
	Q_ULLONG setMarkDeletedGroup(Q_ULLONG gr_id, bool del);
	void getMarkDeletedList(Q_ULLONG idg, QValueList<Q_ULLONG> &listDelId);

	virtual bool isGroupMarkDeleted();
	virtual bool isElementMarkDeleted();
	
	virtual bool Next();
	virtual bool Prev();
	virtual bool First();
	virtual bool Last();
	
	virtual bool NextInGroupTable();
	virtual bool PrevInGroupTable();
	virtual bool FirstInGroupTable();
	virtual bool LastInGroupTable();

	virtual int GroupNew( bool reparent = false );
	virtual int GroupDelete();
	virtual int GroupMarkDeleted();
	virtual int GroupUpdate();
	virtual int GroupSelect();
	virtual int GroupSetGroup( aCatalogue * cat );
	virtual QVariant GroupValue( const QString & name );
	virtual int GroupSetValue( const QString & name, const QVariant & value);
	virtual QVariant GroupSysValue( const QString & name );
	virtual int GroupSetSysValue( const QString & name, const QVariant & value);
//	virtual ERR_Code GroupSelectChild( aCatalogue * parent = 0 );
	virtual QStringList getUserFields();
	virtual QStringList getGroupUserFields();
};

class  ANANAS_EXPORT aCatElement :public aObject
{
	Q_OBJECT
public:
	aCatElement(aCfgItem context, aDatabase * adb = 0);

};



/*!
 *\~english
 *	Object for work with catalogue group.
 *\~russian
 *\brief Класс aCatGroup определяет программный интерфейс для управления группами иерархических 
 * 	справочников (каталогов). Наследует aObject.
 * 	
 *	Иерархический справочник может состоять из элементов и групп. Группы, в отличие от элементов
 *	предназначены не для хранения данных, а для группировки элементов.
 */
class  ANANAS_EXPORT aCatGroup :public aObject
{
	Q_OBJECT
	void setLevel( Q_ULLONG newlevel );
	virtual QString trSysName( const QString & sname );
	QVariant sysValue( const QString & sname );
public:
	aCatGroup(aCfgItem context, aDatabase * adb = 0);
	aCatGroup(QString name, aDatabase * adb = 0);   
	virtual ERR_Code initObject();
	Q_ULLONG parentUid();
public slots:
	ERR_Code New();
	ERR_Code New(aCatGroup *gr);
	ERR_Code Select();
	ERR_Code SelectChild( aCatGroup * parent = 0 );
	ERR_Code SetParent( aCatGroup * parent );
protected:
	virtual aCfgItem displayStringContext();
};

#endif// ACATALOGUE_H
