/****************************************************************************
** $Id: main.cpp,v 1.14 2005/10/09 13:22:38 leader Exp $
**
** Main file of the Ananas Demo3 of Ananas
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
Test catalogue object functions.
Author: Valery Grazdankin (leader)
*/

/*
 * Тест функций работы с метаданными
 * Author: Valery Grazdankin (leader)
 * 10.05.2003 Пример работы с чтеним структуры метаданных
 *
*/
#include <qapplication.h>
#include <qstring.h>
#include <qfile.h>
#include <qdatatable.h>
#include <qtimer.h>
#include <qobject.h>
#include <qlayout.h>

#include "ananas.h"
#include "../demo_config.h"
#include "wdbtable.h"


#define DEMOVER "Demo 3. Catalogue object demo."
#define VERSION "0.4.1"

void NeforoCatTest( aCfg * c, aDatabase * db  )
{
	aCatalogue * catalogue = new aCatalogue( "Catalogue 1", db );
}

void catGroupTest( aCfg * c, aDatabase * db  )
{
	aCfgItem cat;
	cat = c->find(c->find( c->find(mdc_metadata), md_catalogues, 0 ), md_catalogue, 0 );
	if ( cat.isNull() )
	{
		printf("eh... catalogue not found\n");
		return;
	}
	aCatalogue * catalogue = new aCatalogue( "Catalogue", db );
	aCatGroup * cg = new aCatGroup( cat, db );
	aCatGroup * cg1 = new aCatGroup( cat, db );
	aCatGroup * cg2 = new aCatGroup( cat, db );
	for ( uint i = 1; i <= 3; i++ )
	{
		printf("new group result %i\n",cg->New());
		cg->SetValue("Name",QString("Group %1").arg(i));
		cg->SetValue("Code",i);
		cg->Update();
	}

//	cg1->SetFilter("Name","Group 10");
	printf("select result for cg1 = %i\n", cg1->select( 3 ));
	cg1->SetValue("Code", cg1->Value("Code").toDouble()+1);
	cg1->Update();
/*	cg2->SetFilter("Name","Group 1");
	printf("select result for cg2 = %i\n", cg2->Select());
	printf("group reparent result = %i\n",cg2->SetParent(cg1));
	printf("select all group result %i\n",cg->Select());
	uint i = 0;
	if ( cg->First() )
		do
		{
			i++;
			printf("group reparent result = %i\n",cg->SetParent(cg2));
		}
		while ( cg->Next() );
	printf("group count = %i\n",i);
*/
}

int
teststruct(void){
	return 1;

}


void test()
{
	aDatabase db;
	aCfg c;
	c.readrc( DEMO_RC );
	db.init( DEMO_RC );
//	accumulationRegs( &c, &db );
//	catTest( &c, &db );
//	infoRegTest( &c, &db );
//	docTest( &c, &db );
//	docTest( &c, &db );
	catGroupTest( &c, &db);
	db.done();
	printf("test ok!\n");
}

int main(int argc, char **argv)
{
	QApplication app( argc, argv, FALSE );

//	app.exec();
	test();
	return 0;
}
