/****************************************************************************
** $Id: main.cpp,v 1.4 2004/07/04 13:50:49 leader Exp $
**
** Main file of the Ananas Demo4 of Ananas
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
Document object demo.
Create and work wiht document objects.
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
#include "ananas.h"


#define DEMOVER "Demo 4. Document object demo."
#define VERSION "0.4.1"

int
teststruct(void){
//	int rc=1;
//	int i1, i2, i3, i4;
	aCfgItem r, i1, i2;
	aCfg c;

	c.createNew();
//	r = c.find( mdc_root );
//	i1 = c.insert( r, md_document, QString::fromUtf8("Документ1"));
//	i2 = c.insert( r, md_document, QString::fromUtf8("Документ2"));
//	i1 = c.insertDocument( QString::fromUtf8("Документ1") );
//	i2 = c.insertDocument( QString::fromUtf8("Документ2") );
//	c.print();
//	printf("n1=%d n2=%d\n", c.order( i1 ), c.order( i2 ) );
//	c.swap( i1, i2 );
//	c.print();
//	r.read("demo.rc");
//	r.write("demo.rc00");
//	printf("db name = %s\n", (const char *) r.value("dbname"));
//	if ( !database.init( &r ) ) return 0;

//	database.checkStructure();

//	database.uid( 0 );
//	database.uid( 1 );
//	database.uid( 2 );

//	aCatalogue cat("Catalogue.Cat1", &database);
	return 0;
/*	i1 = c.insert(aot_doc, QString::fromUtf8("Документ1"));
	i2 = c.insert(aot_doc, QString::fromUtf8("Документ2"));
	c.insert(aot_cat, QString::fromUtf8("Справочник1"));
	c.insert(aot_cat, QString::fromUtf8("Справочник1"));
	c.insert(aot_cat, QString::fromUtf8("Справочник1"));
	i3 = c.insert(i2, aot_docheader, "");
	c.setText( i3, "\n\n<cfg>\n\t\"test\"\n\tconfig\n</cfg>" );
	c.insert(i3, aot_field, QString::fromUtf8("Поле1"));
	i4 = c.insert(i3, aot_field, QString::fromUtf8("Поле2"));
	c.insert(i3, aot_field, QString::fromUtf8("Поле3"));
//	c.remove( i3 );
	c.print();
//	c.init();
//	i = c.find( i2+1000 );
	printf("i1=%i, i2=%i count cat=%i\n", i1, i2, c.count(aot_cat));
//	if (i.isNull()) printf("not found\n");
//	c.read("sklad.cfg");
//	c.print();
	c.createNew();

//	c.write("ss.cfg");

	return 0;

	if (cfg_init("myrc")) {
		printf(_("error init user resource\n"));
		return 0;
	}
	rc=cfgdb_create(0);
	if (!rc) printf("creation ok\n");
	else printf("creation failed\n");
	return !rc;
*/
	return 1;
}


//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){
        QApplication app( argc, argv, FALSE );
	aDatabase database;
	
//	setlocale(LC_ALL,"");
        printf("Ananas v."VERSION" "DEMOVER"\nCreate database.\n\n");
//	r.read("demo.rc");
//	printf("db name = %s\n", (const char *) r.value("dbname"));
	if ( !database.init( "demo.rc" ) ) return 0;
	if (teststruct()) printf(DEMOVER" ok\n");
	else printf(DEMOVER" failed\n");
/*
	aTable s("se1", &database );

//	QDataTable t( new QSqlCursor("se1", true, database.db ) );
	QDataTable t( &s ); //.sqlCursor() );
	QTimer timer( &t );
	t.connect( &timer, SIGNAL( timeout() ), &t, SLOT( refresh() ) );
	app.setMainWidget( &t );
	t.addColumn("id","id");
	t.addColumn("code","code");
	t.addColumn("uf2","uf2");
	t.addColumn("uf3","uf3");
	t.refresh();
	t.show();
	timer.start( 3000, false );
*/
	app.exec();
	database.done();
	return 0;
}
