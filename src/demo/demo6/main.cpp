/****************************************************************************
** $Id: main.cpp,v 1.40 2004/09/27 12:40:11 pashik Exp $
**
** Main file of the Ananas Demo6 of Ananas
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
 * Function for work with ananas database objects
 * Author: Pavel Mikolaychuk (pashik)
 * 28.06.2006 Example for work with information registers
 * Use demo1&demo2 for create configuration&database
 * fro make register test you mast firstly create documents in database, use function addDocs
*/
#include <qapplication.h>
#include <qstring.h>
#include <qfile.h>
#include <qdatatable.h>
#include <qtimer.h>
#include <qobject.h>
#include <qvariant.h>
#include <qdatetime.h>
#include "ananas.h"

#define DEMOVER "Demo 6. Registers, documents, document journals, catalogues object's demo."
#define VERSION "0.1.1"

//////////////////////////////////////////////////////////////////////////////////////////////

void addDocs( aDocument * doc )
{
	for ( uint i = 1; i < 4; i++ )
		for (uint j = 1; j < 6; j++ )
		{
			doc->SetPrefix("Demo-");
			doc->New();
			doc->SetValue("Field3",i+j/10);
			doc->SetValue("Field2",QString("Text%1").arg(10*i+j));
			doc->SetValue("Field1",QDateTime::currentDateTime());
			doc->Update();
		}
}

void
docNavigation( aDocument * document, const QString & filter = "", const QVariant & val = "" )
{
	document->SetFilter( filter, val );
	int err = document->Select( QDateTime(), QDateTime::currentDateTime() );
//	int err = document->Select( "Demo-1" );
	if( err )
		printf("selection error = %i\n", err );
	else
	{
		int i = 1;
		printf("view from first to last\n");
		document->First();
		printf( "first dok number=%s date='%s' Field1=%s\n",
				(const char*)document->Value("DocNumber").toString(),
				(const char*)document->Value("DocDate").toString(),
				(const char*)document->Value("Field1").toString());
		while ( document->Next() )
			printf( "sel dok #%i number=%s date='%s' Field1=%s\n", i++,
				(const char*)document->Value("DocNumber").toString(),
				(const char*)document->Value("DocDate").toString(),
				(const char*)document->Value("Field1").toString());
		printf("view from last to first\n");
		while ( document->Prev() )
			printf( "sel dok #%i number=%s date='%s' Field1=%s\n", i--,
				(const char*)document->Value("DocNumber").toString(),
				(const char*)document->Value("DocDate").toString(),
				(const char*)document->Value("Field1").toString());
		document->Last();
		printf( "Last dok number=%s date='%s' Field1=%s\n",
				(const char*)document->Value("DocNumber").toString(),
				(const char*)document->Value("DocDate").toString(),
				(const char*)document->Value("Field1").toString());
		document->First();
		printf( "first dok number=%s date='%s' Field1=%s\n",
				(const char*)document->Value("DocNumber").toString(),
				(const char*)document->Value("DocDate").toString(),
				(const char*)document->Value("Field1").toString());
	}
}

void addDocTables( aDocument * doc, const QString & tname, uint count )
{
	for ( uint i = 0; i < count; i++ )
	{
		doc->TableNewLine(tname);
		doc->TableSetValue(tname,"Field1","Text of table");
		doc->TableSetValue(tname,"Field2",13 * i + 1);
		doc->TableSetValue(tname,"Field3",i*i);
		doc->TableSetValue(tname,"Field4",QDateTime::currentDateTime());
		doc->TableUpdate(tname);
	}
}

void
docTableNavigation( aDocument * document, const QString & dnum, const QString & tname )
{
	int err = document->Select( dnum );
	if( err )
		printf("selection error = %i\n", err );
	else
	{
		err = document->TableSelect(tname);
		if ( err )
		{
			printf("selection table error = %i\n", err);
			return;
		}
		int i = 1;
		document->TableFirst(tname);
		printf("view from first to last\n");
		printf( "first table line ln=%i Field1=%s Field2=%s\n",
				document->TableValue(tname,"TableLine").toInt(),
				(const char*)document->TableValue(tname,"Field1").toString(),
				(const char*)document->TableValue(tname,"Field2").toString());
		while ( document->TableNext(tname) )
			printf( "sel table line #%i Field1=%s Field2=%s\n",
				document->TableValue(tname,"TableLine").toInt(),
				(const char*)document->TableValue(tname,"Field1").toString(),
				(const char*)document->TableValue(tname,"Field2").toString());
		printf("view from last to first\n");
		while ( document->TablePrev(tname) )
			printf( "sel table line #%i Field1=%s Field2=%s\n",
				document->TableValue(tname,"TableLine").toInt(),
				(const char*)document->TableValue(tname,"Field1").toString(),
				(const char*)document->TableValue(tname,"Field2").toString());
		document->TableLast(tname);
			printf( "Last table line Field1=%s Field2=%s\n",
				(const char*)document->TableValue(tname,"Field1").toString(),
				(const char*)document->TableValue(tname,"Field2").toString());
		document->TableFirst(tname);
			printf( "First table line Field1=%s Field2=%s\n",
				(const char*)document->TableValue(tname,"Field1").toString(),
				(const char*)document->TableValue(tname,"Field2").toString());
	}
}

void docTest( aCfg * c, aDatabase * db )
{
	aCfgItem doc;
	doc = c->find(c->find( c->find(mdc_metadata), md_documents, 0 ), md_document, 0 );
	if ( doc.isNull() )
	{
		printf("eh... document not found\n");
		return;
	}
	aDocument * Doc = new aDocument(doc, db);
	if ( Doc == 0 )
	{
		printf("very very bad!!!\n");
		return;
	}
	int err = Doc->Select("Demo-1");
	printf("doc selction result %i\n", err);
//	Doc->Conduct();
//	err = Doc->Delete();
//	printf("doc delete result %i\n", err);
	if (err) return;
	uint n = 3;
	QString tname;
	for ( uint i = 1; i <= n; i++ )
	{
		tname = QString("Table %1").arg(i);
		printf("doc new line result %i\n",Doc->TableNewLine(tname));
		Doc->TableSetValue(tname,"Field1","Text of table");
		Doc->TableSetValue(tname,"Field2",13 * i + 1);
		Doc->TableSetValue(tname,"Field3",i*i);
		Doc->TableSetValue(tname,"Field4",QDateTime::currentDateTime());
	}
	Doc->Update();

//	docTableNavigation( document, "Demo-1", "Table 3" );
//	document->Select( "Demo-1");
//	printf ( "Update result %i\n", document->Update() );
/*	if ( !document->Select( QDateTime(), QDateTime::currentDateTime() ))
		do
			if ( document->IsConducted() ) printf("conducted\n");
			else printf("not conducted!\n");
		while (document->Next());
	else printf("erRor!!\n");*/
//		addDocTables( document, "Table 3", 15 );
//		docNavigation( document, "Field1", "Text11" );
/*		printf("select ok!\n");
		document->TableSelect("Table 1");
		printf("Table deleting code = %i\n",document->TableDelete("Table 1"));
		document->TableNewLine("Table 3");
		document->TableSetValue("Table 3","Field1","Text of table");
		document->TableSetValue("Table 3","Field2",12598);
		document->TableSetValue("Table 3","Field3",123.456);
		document->TableSetValue("Table 3","Field4",QDateTime::currentDateTime());
		document->TableUpdate("Table 3");
		printf ("copy code = %i\n",document->Copy());

		document->SetValue("Field1","tes1");
		if ( !document->SetValue( "DocDate", QDateTime::currentDateTime() ) )
			printf ("update code = %i\n",document->Update());
		else printf("Set value error!\n");
		document->SetValue("Field1","test-x");
		document->Update();*/
//	document->SetMarkDeleted(true);
//	printf ("select status %i\n", document->Select( QDateTime(), QDateTime::currentDateTime()));
//	document->SetPrefix( "newpref" );
//	document->Update();
}

void catTest( aCfg * c, aDatabase * db  )
{
	aCfgItem cat;
	cat = c->find(c->find( c->find(mdc_metadata), md_catalogues, 0 ), md_catalogue, 0 );
	if ( cat.isNull() )
	{
		printf("eh... catalogue not found\n");
		return;
	}
	aCatalogue * catalogue = new aCatalogue( "Catalogue 1", db );
	aCatalogue * cat1 = new aCatalogue( "Catalogue 1", db );
//	catalogue->SetFilter("Name", "2");
	catalogue->GroupNew();
	cat1->GroupNew();
	cat1->GroupSetGroup(catalogue);
	catalogue->GroupSetGroup(cat1);
//	catalogue->SetValue("Name","test");
//	catalogue->Update();
}

void NeforoCatTest( aCfg * c, aDatabase * db  )
{
	aCatalogue * catalogue = new aCatalogue( "Catalogue 1", db );
}

void irNew( aIRegister * reg, uint i )
{
	printf ("new reg result %i\n",reg->New());
	reg->SetValue("Name", QString("Tovar %1").arg((1+i%10)));
	reg->SetValue("Scklad", (1+(i%6)) );
	reg->SetValue("Price", i + 0.13 * ( i%124 ) );
	reg->SetValue("Count", i%100 );
	reg->SetValue("Watch this","This is info field but figli tolku?");
	reg->Update();
}

void irSelect( aIRegister * reg )
{
	if ( !reg->Select( QDateTime(), QDateTime::currentDateTime() ))
	printf("Record name '%s', Sklad %s, price=%s\n",(const char*) reg->Value("Name").toString(),
			(const char*)reg->Value("Scklad").toString(),(const char*)reg->Value("Price").toString());
	while ( reg->Next() )
		printf("Record name '%s', Sklad %s, price=%s\n",(const char*) reg->Value("Name").toString(),
				(const char*)reg->Value("Scklad").toString(),
				(const char*)reg->Value("Price").toString());

}

void addMoves( aIRegister * reg, uint n )
{
//	uint k = n/100;
	QDateTime begtime=QDateTime::currentDateTime();
	printf("add %u movs in accumulation register, time test\n", n );
	for ( uint i = 1; i <= n; i++ )
	{
//		if ( !(i%k) )
//		printf("%u of %u\n",i,n);
		irNew( reg, i );
	}
	printf("%u movs added\n", n );
	printf("Beg time = %s\n",(const char*)begtime.toString().local8Bit());
	printf("End time = %s\n",(const char*)QDateTime::currentDateTime().toString().local8Bit());
/*	printf("select sum by many movs in accumulation register, time test\n");
	printf("Beg time = %s\n",(const char*)QDateTime::currentDateTime().toString("mm.ss.zzz").local8Bit());
	printf("Price count = %s\n", (const char *)reg->SelectCount("Price", QDateTime(), QDateTime::currentDateTime()).toString());
	printf("End time = %s\n",(const char*)QDateTime::currentDateTime().toString("mm.ss.zzz").local8Bit());*/
}

void infoRegTest( aCfg * c, aDatabase * db  )
{
	aCfgItem ir, irs;
	irs = c->find(c->find(c->find(mdc_metadata),md_registers,0),md_iregisters,0);
	if ( irs.isNull() )
	{
		printf("ups... information registers group not found!!!\n");
		return;
	}
	printf("information registers group ok!\n");
	ir = c->find( irs, md_iregister, 0 );
//	aIRegister * reg = new aIRegister ( ir, db );
	aIRegister * reg = new aIRegister ( "Info register 2", db );
	aDocument * doc = new aDocument( "Document 1", db );
//	addDocs(doc);
	printf ("set doc = %i\n",reg->SetDocument(doc));
/*	if ( !doc->Select(QDateTime(),QDateTime::currentDateTime()) )
		do
			addMoves( reg, 10 );
		while (doc->Next());*/


	printf ("doc select = %i\n",doc->Select("Demo-5"));
//	printf ("doc select = %i\n",doc->Select(QDateTime(),QDateTime::currentDateTime()));
	printf ("reg new = %i\n",reg->New());
	printf("reg set value = %i\n",reg->SetValue( "Field1", 0.5342 ));
	printf ("reg update = %i\n",reg->Update());
	int err = reg->SelectByDoc();
	if (err){printf("err=%i\n",err);return;}
	printf("Record name '%s', Sklad %s, price=%s\n",(const char*) reg->Value("Name").toString(),
			(const char*)reg->Value("Scklad").toString(),(const char*)reg->Value("Price").toString());
	while ( reg->Next() )
		printf("Record name '%s', Sklad %s, price=%s\n",(const char*) reg->Value("Name").toString(),
				(const char*)reg->Value("Scklad").toString(),
				(const char*)reg->Value("Price").toString());
}

void addMovesAllDoc(aDocument *doc,aIRegister * reg)// added moves for headers for all documents
{
	if ( doc->Select(QDateTime(),QDateTime::currentDateTime()) ) return;
	uint cnt = 50000;// you mast have a lot of time for more fast work use less value
	do
		addMoves( reg, cnt );
	while ( doc->Next() );
}

void accumulationRegs( aCfg * c, aDatabase * db  )
{
	aCfgItem ar, ars;
	ars = c->find(c->find(c->find(mdc_metadata),md_registers,0),md_aregisters,0);
	if ( ars.isNull() )
	{
		printf("ups... accumulation registers group not found!!!\n");
		return;
	}
	printf("accumulation registers group ok!\n");
	ar = c->find( ars, md_aregister, 0 );
	if ( ar.isNull() )
	{
		printf("oops... you have no accumulation registers :(\n");
		return;
	}
	aARegister * reg = new aARegister ( "Accumulation register 2", db );
	aDocument * doc = new aDocument( "Document 1", db );

//	addDocs(doc); //uncoment if database have no documents

//!	add Moves
	reg->SetDocument(doc);
/*	for ( uint i = 1; i <= 88; i++ )
	{
		doc->Select(QString("Demo-%1").arg(i));
		addMoves( reg, 5 );
	}*/

//!	delete document from register
	doc->Select("Demo-1");
	if ( reg->deleteDocument(doc) ) printf("delete doc success!\n");
	else printf("delete doc error!\n");


//!	close period using doc date
/*	for ( uint i = 1; i <= 88; i += 2)
	{
		doc->Select(QString("Demo-%1").arg(i));
		reg->SetDocument(doc);
		QDateTime date = doc->Value("DocDate").toDateTime().date();
		printf("close result for Demo-%i = %i\n",i,reg->ClosePeriod(date));
	}*/

/*	reg->SetFilter("Name", "Tovar 1");
	printf("maxdate result = %i\n",reg->SelectRemainders(date));
	do
		printf("Tovar name '%s', Sklad %s, price sum=%s, count sum=%s\n",
				(const char*)reg->SumValue("Name").toString(),
				(const char*)reg->SumValue("Scklad").toString(),
				(const char*)reg->SumValue("Price").toString(),
				(const char*)reg->SumValue("Count").toString());
	while ( reg->SumNext() );
	reg->SetFilter("Name", "Tovar 2");
	printf("maxdate result = %i\n",reg->SelectRemainders(date));
	do
		printf("Tovar name '%s', Sklad %s, price sum=%s, count sum=%s\n",
				(const char*)reg->SumValue("Name").toString(),
				(const char*)reg->SumValue("Scklad").toString(),
				(const char*)reg->SumValue("Price").toString(),
				(const char*)reg->SumValue("Count").toString());
	while ( reg->SumNext() );*/
//	printf("close result = %i\n",reg->ClosePeriod(date));
/*	QDateTime begTime = QDateTime::currentDateTime();
//	printf ("select count by document result %i\n",reg->SelectCountByDoc());
	printf ("select count by date %i\n",reg->SelectCount( QDateTime(), begTime ));
	printf("Beg time = %s\n",(const char*)begTime.toString("mm.ss.zzz").local8Bit());
	printf("End time = %s\n",(const char*)QDateTime::currentDateTime().toString("mm.ss.zzz").local8Bit());
	do
		printf("Tovar name '%s', Sklad %s, price sum=%s, count sum=%s\n",
				(const char*)reg->SumValue("Name").toString(),
				(const char*)reg->SumValue("Scklad").toString(),
				(const char*)reg->SumValue("Price").toString(),
				(const char*)reg->SumValue("Count").toString());
	while ( reg->SumNext() );*/
/*	do
		printf("Record name '%s', Sklad %s, price=%s\n",(const char*) reg->Value("Name").toString(),
				(const char*)reg->Value("Scklad").toString(),
				(const char*)reg->Value("Price").toString());
	while ( reg->Next() );*/
/*	QDateTime begTime = QDateTime::currentDateTime();
	printf("close period result = %i\n", reg->ClosePeriod());
	printf("Beg time = %s\n",(const char*)begTime.toString("mm.ss.zzz").local8Bit());
	printf("End time = %s\n",(const char*)QDateTime::currentDateTime().toString("mm.ss.zzz").local8Bit());*/
}

void syndates(aDatabase * db)
{
	for (uint i = 8; i <= 91; i++ )
	{
		db->db()->exec( QString("select @t:=ddate, @d:=idd from a_journ where num=%1").arg(i));
		db->db()->exec("update ra153 set ddate=@t where idd=@d");
	}
}

void sysJournTest( aDatabase * db  )
{
	aDocJournal * journ = new aDocJournal(db);
	int err = journ->Select( "Demo-89", "Document 1" );
	printf("document from journ selection result %i\n",err);
	if (err) return;
	err=journ->Delete();
	printf("document delete from journ result %i\n",err);
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
	aCatalogue * catalogue = new aCatalogue( "Catalogue 1", db );
	aCatGroup * cg = new aCatGroup( cat, db );
	aCatGroup * cg1 = new aCatGroup( cat, db );
	aCatGroup * cg2 = new aCatGroup( cat, db );
/*	for ( uint i = 1; i <= 10; i++ )
	{
		printf("new group result %i\n",cg->New());
		cg->SetValue("Name",QString("Group %1").arg(i));
		cg->Update();
	}*/
	cg1->SetFilter("Name","Group 10");
	printf("select result for cg1 = %i\n", cg1->Select());
	cg2->SetFilter("Name","Group 1");
	printf("select result for cg2 = %i\n", cg2->Select());
	printf("group reparent result = %i\n",cg2->SetParent(cg1));
/*	printf("select all group result %i\n",cg->Select());
	uint i = 0;
	if ( cg->First() )
		do
		{
			i++;
			printf("group reparent result = %i\n",cg->SetParent(cg2));
		}
		while ( cg->Next() );
	printf("group count = %i\n",i);*/
}


void test()
{
	aDatabase db;
	aCfg c;
	c.readrc("../demo.rc");
	db.init("../demo.rc");
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

