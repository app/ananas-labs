/****************************************************************************
** $Id: areportbrowser.h,v 1.1 2005/05/18 19:14:29 leader Exp $
**
** Report metadata object header file of 
** Ananas application library
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2005 Grigory Panov, Yoshkar-Ola.
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

#ifndef AREPORTBROWSER_H
#define AREPORTBROWSER_H

#include	<qmainwindow.h>
#include	<qtextbrowser.h>
#include	<qworkspace.h>
#include	"acfg.h"
#include 	"aobject.h"
#include 	"engine.h"
#include 	"atemplate.h"
#include 	"aootemplate.h"
#include 	"areport.h"

class aDatabase;


class  ANANAS_EXPORT aReportBrowser :public QMainWindow
{
	Q_OBJECT
public:
	QWorkspace *ws;
	QTextBrowser *textBrowser;	    
	aReportBrowser(  QWidget *parent = 0, const char *name = 0, WFlags f = WDestructiveClose );
	void append( const QString &text );
	void clear();
public slots:
	void print();

protected slots:
	virtual void languageChange();
};

#endif// AREPORTBROWSER_H
