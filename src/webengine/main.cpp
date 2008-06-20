/****************************************************************************
** $Id: main.cpp,v 1.4 2004/07/01 11:30:56 pashik Exp $
**
** Main file of Ananas Web Engine application
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Web Engine application of the Ananas
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
#include <qapplication.h>
//#include "mainform.h"
//#include "dselectdb.h"
#include "httpdaemon.h"

//QAMainWindow *mainwindow=NULL;

int main( int argc, char ** argv )
{

	static QApplication a( argc, argv, false );
	static HttpDaemon httpd(&a);
//	static MainForm w;
//	dSelectDB dselectdb;

//	setlocale(LC_ALL,"");
//	mainform=&w;
//	mainformws=mainform->ws;
//	if (dselectdb.exec()==QDialog::Accepted) {
//		if (dselectdb.rcfile.isEmpty()) return 0;
//		w.rcfile=dselectdb.rcfile;		
//		w.init();
//		w.show(); 
//		a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
		return a.exec();
//	} else return 0;
}
