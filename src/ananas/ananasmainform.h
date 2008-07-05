/****************************************************************************
** $Id: ananasmainform.h,v 1.3 2008/07/05 12:19:39 app Exp $
**
** Header file of the Main form of Ananas Engine application
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Engine application of the Ananas
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

/****************************************************************************
****************************************************************************/

#ifndef ANANASMAINFORM_H
#define ANANASMAINFORM_H
#include <qvariant.h>
#include <qworkspace.h>
#include <qsinterpreter.h>
#include <qdialog.h>
#include <qstringlist.h>
#include <qworkspace.h>
#include <qmainwindow.h>
#include <qvbox.h>
#include <qapplication.h>
#include <qsettings.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include "ananas.h"
#include "amenubar.h"
#include "atoolbar.h"
#include "awindowslist.h"
#include "engine.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;

/*!
 * \ru
 * Главное окно приложения Ананас, запускаемого пользователем.
 *
 * \_ru
 */

class MainForm : public QMainWindow {
	Q_OBJECT

public:
	MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
	~MainForm();
	aEngine engine;
	aCfg *md;

	AMenuBar* menubar;
	QPopupMenu *windowsMenu;
	QWorkspace* ws;
	aWindowsList* wl;
	QString rcfile;
	QLabel *statusLabel1;
	QLabel *statusLabel2;
	QLabel *statusLabel3;
	QLabel *statusLabel4;
	QPushButton *statpb;
	MessagesWindow *msgWindow;

public slots:
	bool init();
	bool initEngine();
	void initMenuBar();
	void initStatusBar();
	void initActionBar();
	void InsertMainMenu(QString text, QObject *pop);
	void Exit(int code);
	void close();
	void helpAbout();
	void statusMessage( const QString &msg, const int &pos );
	void statusMessage( const QString &msg );
	void statusIcon( const int &status );

	void windowsMenuAboutToShow();
	void windowsMenuActivated( int id );
	void tileHorizontal();
	void setBackground( const QPixmap &pix );
	void miniCalc();

protected:
	protected slots:
	virtual void languageChange();
	virtual void statpbToggled();
	virtual void hideMsgWindow();

private:
	QSettings engine_settings;
};

extern MainForm *mainform;
extern QWorkspace *mainformws;
extern aWindowsList *mainformwl;

#endif // ANANASMAINFORM_H
