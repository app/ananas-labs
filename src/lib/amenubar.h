/****************************************************************************
** $Id: amenubar.h,v 1.4 2004/09/01 16:55:58 leader Exp $
**
** Header file of the Ananas Menu bar of Ananas
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

/****************************************************************************
****************************************************************************/

#ifndef AMENUBAR_H
#define AMENUBAR_H

#include 	<qmenubar.h>
#include 	<qpopupmenu.h>
#include 	<qapplication.h>
#include	"acfg.h"

class  ANANAS_EXPORT AMenuBar : public QMenuBar
{
	Q_OBJECT

	private:
	aCfg	*md;


    public:
	AMenuBar( QWidget* parent = 0, const char* name = 0 );
	AMenuBar( aCfg *cfg, QWidget* parent = 0, const char* name = 0 );
	~AMenuBar();

	void ReadMenu( aCfgItem obj );
	void ReadMenu( QPopupMenu *parent, aCfgItem obj );

    public slots:
	void on_Item(){};
	int insertItem ( const QString & text, QPopupMenu * popup, int id = -1, int index = -1 );
/*
	int insertItem ( const QString & text, const QObject * receiver, const char * member, const QKeySequence & accel = 0, int id = -1, int index = -1 );
	int insertItem ( const QPixmap & pixmap, const QObject * receiver, const char * member, const QKeySequence & accel = 0, int id = -1, int index = -1 );
	int insertItem ( const QIconSet & icon, const QPixmap & pixmap, const QObject * receiver, const char * member, const QKeySequence & accel = 0, int id = -1, int index = -1 );
	int insertItem ( const QString & text, int id = -1, int index = -1 );
	int insertItem ( const QIconSet & icon, const QString & text, int id = -1, int index = -1 );
	int insertItem ( const QIconSet & icon, const QString & text, QPopupMenu * popup, int id = -1, int index = -1 );
	int insertItem ( const QPixmap & pixmap, int id = -1, int index = -1 );
	int insertItem ( const QIconSet & icon, const QPixmap & pixmap, int id = -1, int index = -1 );
	int insertItem ( const QPixmap & pixmap, QPopupMenu * popup, int id = -1, int index = -1 );
	int insertItem ( const QIconSet & icon, const QPixmap & pixmap, QPopupMenu * popup, int id = -1, int index = -1 );
	int insertItem ( QWidget * widget, int id = -1, int index = -1 );
	int insertItem ( const QIconSet & icon, QCustomMenuItem * custom, int id = -1, int index = -1 );
	int insertItem ( QCustomMenuItem * custom, int id = -1, int index = -1 );
	int insertSeparator ( int index = -1 );
*/
private:
	QIntDict <aCfgItem> cfgItems;

};


#endif // AMENUBAR_H
