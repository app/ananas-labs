/****************************************************************************
** $Id: main.cpp,v 1.5 2004/07/27 12:10:17 pashik Exp $
**
** Main file of the Ananas Demo5 of Ananas
** Demo collection
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

/*
 * Document journals object.
 * Author: Valery Grazdankin (leader)
 * 10.05.2003 Examle working with document journal object.
 */

#include <qapplication.h>
#include <qstring.h>
#include <qfile.h>
#include <qdatatable.h>
#include <qtimer.h>
#include <qobject.h>
#include "ananas.h"


#define DEMONAME "Demo 5. Documents journal object demo."

bool demo()
{

	aDatabase db;

	if ( !db.init("../demo.rc") ) return false;

	aCfgItem j, r, i1, i2;
//	aCfg c;

//	db.create();
	aDocJournal journal( "DocJournal.Common", &db );
CHECK_POINT
//	journal.New();
//	journal->table()->printRecord();
CHECK_POINT
	return true;
}


//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){
        QApplication app( argc, argv, FALSE );
	setMessageHandler();

        printf("Ananas v.%s %s\n\n", ananas_libversion(), DEMONAME);
	if ( demo() ) printf("ok\n");
	else printf("failed\n");
	return 0;
}
