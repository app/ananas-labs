/****************************************************************************
** $Id: aform.h,v 1.33 2008/05/26 08:37:14 app Exp $
**
** Header file of Ananas forms of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2005 Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola.
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

/*!
*/
#ifndef AFORM_H
#define AFORM_H

#include "ananasglobal.h"

#include <qobject.h>
#include <qbuttongroup.h>
#include <qsproject.h>
#include <qsinterpreter.h>
#include <qsargument.h>
#include <qmutex.h>
#include <qdialog.h>

#include "engine.h"
#include "adatabase.h"
#include "adocument.h"
#include "acfg.h"


class QWidget;
class QSqlForm;
class aWidget;
class EventDialog;


/*!
 *\~english
 *	Ananas form.
 *\~russian
 *	\brief Определяет программный интерфейс экранных форм Ананаса, предназначенный для использования 
 *	Ананас.Скриптом модуля экранной формы Документа и других бизнес объектов Ананаса.
 *	
 *	Любая экранная форма, спроектированная в Ананас.Дизайнере имеет методы этого класса.
 *	Объект данного класса создается при создании формы. Программный код, написанный на Ананас.Скрипте и хранящийся
 *	в модуле экранной формы (вкладка "Модуль" в Дизайнере) может обращаться к методам этого объекта напрямую, 
 *	без указания имени объекта. 
 *
 *	Кроме того, класс обеспечивает вызов некоторых функций на Ананас.Скрипте, определенных в модуле экранной формы, 
 *	при наступлении определенных событий, например открытии или закрытии формы, изменения значения виджетов формы и т.п
 *	Полный список этих событий и функций можно посмотеть на сайте Ананаса в разделе руководства по Ананас.Дизайнеру.
 *\~
 */
class  ANANAS_EXPORT aForm : public QObject
{
	Q_OBJECT
public:
	aEngine*	engine;
	aDatabase*	db;
	aCfg*		md;
	aCfgItem	mdObj;
	QWidget*	parentWidget;
	bool		closeAfterSelect;

	aForm();
	aForm( QWidget *parent, aEngine *eng );
	aForm( QWidget *parent,  aEngine *eng,  Q_ULONG form_mid = 0, aWidget* caller = NULL);
	aForm( QWidget *parent,  aEngine *eng, QString oftype, QObject *aobj = NULL);
	~aForm();
	QWidget *form;
	void		init();
	QWidget*	aParent( QWidget *widget );
	int		New();
	int		Select( Q_ULLONG id );
	int		SelectGroup( Q_ULLONG id );
	Q_ULLONG	selectedCatId(){ return db_uid;} // Return uid, selected in Catalogue
	Q_ULLONG	selectedId(){ return id;} // Return uid, selected in  main wDBTable
signals:
	void selected( Q_ULLONG uid );
	void closeForm( Q_ULLONG );
	void changedData();
	void update( ANANAS_UID );
public:

	QVariant	tabValue(const QString &tname, int row, int col, bool dbval=false);
	void		setMode(int m);

public slots:
//	QObject *	object(const QString &name);
	void		done( int rc );
	void		Show(bool modal=FALSE);
	bool		Close();
	void		show(); //depricated
	void		close(); //depricated
	void		maximize(bool m);	
	QVariant	Value(const QString &name);
	QVariant	DBValue(const QString &name);
	int		SetValue(const QString &name, QVariant value);
	int 		SetObjValue(const QString &name, aObject *value);
	void		SetColumnReadOnly(const QString &tname, int numCol, bool ro);
	int		ColIndex(const QString &tname, const QString &colname);
	int		TabCount(const QString &tname);
//	QVariant	TabValue(const QString &tname, const QString &colname, int row =-1 );
	QVariant	TabValue(const QString &tname, int row, int col);
	QVariant	TabDBValue(const QString &tname, int row, int col);
	void            TabNewLine(const QString &tname);
	void            TabUpdate(const QString &tname);
//	QVariant	TabDBValue(const QString &tname, const QString &colname , int row =-1);
//	void		SetTabValue(const QString &tname, const QString &name, QVariant value);
	void		SetTabValue(const QString &tname, const QString &colname, int row, QVariant value);
	void		setfocus(QString fname);
	void		SetFocus();
	ERR_Code	UpdateDB(); // Обновить в БД
	ERR_Code	update(); // Depricated
	int		turn_on(); // Depricated
	int		turn_off(); // Depricated
	int		SignIn(); // Провести документ
	int		SignOut(); // Отменить проведение документа
//	void		formClose();
	int		Update();
	void		SetReadOnly( bool status );
	bool		IsReadOnly();
	int 		GetMode();
		
	QString 	Propis( 	QString val ,  
					bool need_kopeyki=true,
					bool male=true,
					const QString &end1="рублей",
					const QString &end2="рубль",
					const QString &end3="рубля");
	QString 	MoneyToText( QString amount , QString currency ); 
	QString 	ConvertNumber2MoneyFormat(double number);
	QString 	ConvertDateFromIso(const QString &ISODate);
	QString		EndOfDay(const QString& ISODate);
	
	void		SelectByCurrent(aObject *doc);
	void		SetCurrent(aObject *doc);
	aObject*	Current();

	QWidget*	Widget( QString name );
	bool		FormHasFunction(const QString functionName);

// after compleete will remove	value() setValue()
//	aDataField*	getAttribute(const QString &name);
//	int		setAttribute(const QString &name, aDataField *value);

/**
 * Возвращает идентификатор объекта метаданных для которого создана форма.
 * \input fn (in) - имя файла формы.
 * \return один из предопределенных в cfg.h типов.
 */
//	char*		formMetaObjectId(QString fn);
private slots:
	void on_dbtablerow( QSqlRecord *r );
        void on_tabupdate( QSqlRecord *r );
	void on_button();//int id);
	void on_actionbutton();
	bool on_form_close();
	void on_return();
	void on_lostfocus();
	void on_valueChanged(const QString &s);
	void on_valueChanged( const QString & name, const QVariant & value );
	void on_tabvalueChanged(int row, int col);
	void on_tabselected( Q_ULLONG uid );
	void on_event( const QString &source, const QString &data );
	void on_tablerow( Q_ULLONG uid );
//	QObject *findWidget(QString name);
//	QString widgetName(QObject *w);
//	void openForm( int oid, int fid = 0 , int defaultfor = 1, int mode = 0, bool readonly = false );
	void connectSlots();
protected:
	virtual void initWidget( QWidget *widget, aDatabase *adb );
	virtual void initContainer( aWidget *widget, aDatabase *adb );
	aWidget *parentContainer( QWidget *widget );
private:
	QObject*	dbobject;
	int		tobj, objid;
	int 		mode;
	Q_ULLONG	id;
	Q_ULLONG	db_uid;
	bool		RO;
	aWidget*	mainWidget;
	aWidget*	callerWidget;
	bool modal;
	EventDialog * dlg;
};

/*!
 *\~english
 *	Event-driven QDialog
 *\~russian
 *	\brief 
*	Класс наследует QDialog, единственный добавленный функционал - порграммный отказ от закрытия окна.
 *\~
 */
class EventDialog : public QDialog
{
	Q_OBJECT
public:
	EventDialog(QWidget * w, const char * c, bool m = false) : QDialog(w, c, m) {};
	~EventDialog() {};
signals:
	bool closed();
protected:
	virtual void closeEvent(QCloseEvent * e) { if(emit(closed())) QDialog::closeEvent(e); else e->ignore(); };
};

/*!
 *\~english
 *	Event-driven QMainWindow
 *\~russian
 *	\brief 
*	Класс наследует QMainWindow, единственный добавленный функционал - порграммный отказ от закрытия окна.
 *\~
 */
class EventWindow : public QMainWindow
{
	Q_OBJECT
public :
	EventWindow(QWidget * parent = 0, const char * name = 0, WFlags f = WType_TopLevel) : QMainWindow(parent, name, f) {};
	~EventWindow() {};
signals:
	bool closed();
protected:
	virtual void closeEvent(QCloseEvent * e) { if(emit(closed())) QMainWindow::closeEvent(e); else e->ignore(); };
};

#endif // AFORM_H
