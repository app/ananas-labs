/****************************************************************************
** $Id: awidget.h,v 1.1 2005/05/18 19:14:29 leader Exp $
**
** Header file of the Ananas visual bject of Ananas
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

#ifndef AWIDGET_H
#define AWIDGET_H
#include <qsqlform.h>
#include <qtoolbar.h>
#include <qmainwindow.h>
#include "ananas.h"

class QWidget;



/*!
 *\~english
 *	Base visual object.
 *\~russian
 *	Базовый визуальный объект. От него наследуют свойства и методы такие визуальные объекты 
 *	как контейнеры wDocument, wJournal, wCatalog, wDocument, wReport и виджеты wField, wDBField.\n
 *	
 *	
 */
class  ANANAS_EXPORT aWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY( QString Name READ getName WRITE setName STORED true DESIGNABLE false )
	Q_PROPERTY( int Id READ getId WRITE setId STORED true DESIGNABLE false )
	Q_PROPERTY( bool openEditor READ getOpenEditor WRITE setOpenEditor STORED false )
public:
	aDatabase*	db;
	aCfg*		md;
	aEngine*	engine;

	aWidget( QWidget *parent = 0, const char *name = 0, WFlags fl = 0 );
	aWidget( const QString &oname, aDatabase *adb, QWidget *parent = 0, const char *name = 0, WFlags fl = 0 );
	aWidget( aCfgItem context, aDatabase *adb, QWidget *parent = 0, const char *name = 0, WFlags fl = 0 );
	virtual ~aWidget();

	virtual bool		checkStructure();
	virtual void		initObject( aDatabase *adb );
	virtual void		widgetEditor();
        static void		widgetEditor( QWidget *object, QDialog *editor );
	virtual QDialog*	createEditor( QWidget *parent );
	virtual QToolBar*	createToolBar( QMainWindow *parent );
        virtual aObject*	createDBObject( aCfgItem obj, aDatabase * );
	virtual QString		displayString();

	void			init( aDatabase *adb );
	bool			getOpenEditor() const { return false; };
	void			setOpenEditor( bool );// { widgetEditor(); };
	bool			isInited() { return vInited; };
	virtual bool		isContainer();
	void			setInited( bool flag ){ vInited = flag; };
//	void			formInsert( QWidget *widget, const QString &field );
//	void			formRemove( const QString &field );
	static aWidget*		parentContainer( QWidget *w );
	static aForm*		parentForm( QWidget *w );
	aCfgItem*		getMDObject();
	void			setMDObject( aCfgItem object );
	aSQLTable*		table( const QString &name = "" );
//	bool tableInsert( const QString &name );
//	bool tableRemove( const QString &name );
	void			setObjectData( QWidget *object, aCfg *md );
	void			getObjectData( QWidget *object );
	aCfg*			getMd();
	Q_ULLONG		uid();
	virtual ERR_Code	New();
	virtual ERR_Code	Update();
	virtual ERR_Code	TurnOn();
	virtual ERR_Code	Select( Q_ULLONG id );
	aObject*		dataObject(){ return dbobj; };

	virtual Q_ULLONG	docId();
	int			formMode(){ return vFormMode; };
	void			setFormMode( int mode ){ vFormMode = mode; };
	virtual QString		getFieldName()	const 	{ return "";	};

public slots:
	QString			getName() const;
	void			setName( QString fn );
	int 			getId() const { return vId ;};
	void			setId( int fn ){ vId = fn; };
	virtual			QVariant value( const QString & name );
	virtual void		SetReadOnly(bool);
	virtual ERR_Code	Refresh();
	virtual void		setValue( const QString &fn ) {};


signals:
	void setData( QWidget *, aCfg * );
	void getData( QWidget * );
	void getMd( aCfg ** );
	void valueChanged( const QString &, const QVariant & );
	void changeObj(const QString &);
	void changeObjId(const Q_ULLONG);

protected:
	aObject *dbobj;
private:
	bool		vInited;
	QString		vName;
	int		vId, vFormMode;
	aCfgItem	obj;
	QSqlForm*	form;
//	QDict <aSQLTable> dbtables;
};


#endif
