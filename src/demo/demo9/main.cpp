/****************************************************************************
** $Id: main.cpp,v 1.2 2005/12/19 14:08:21 gr Exp $
**
** Main file of the Ananas Demo9 of Ananas
** Test saldo
**
** Created : 20051017
**
** Copyright (C) 2003-2005. Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola
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

#define DEMO_DBTITLE "Demo configuration"
#define DEMO_DBTYPE "mysql"
#define DEMO_DBNAME "test_saldo_db"
#define DEMO_DBUSER "root"
#define DEMO_DBPASS ""
#define DEMO_DBHOST "localhost"
#define DEMO_CONFIGFILE "demo.cfg"
#define DEMO_RC "demo.rc"

#include "ananas.h"
#include <qapplication.h>

#define DEMOVER "Demo 9. Test saldo."
#define VERSION "0.1.1"


void create_config()
{
	printf("create config\n");
	aCfg c;
	aCfgItem d1, c1, c2, c3, t, f;

	c.createNew();
	c.setInfo( md_info_name, "Test saldo configuration" );
	c.setInfo( md_info_author, "demo" );

	// Document
	c1 = c.insertDocument( "Test saldo document" );
	c.insertField( c1, md_header, "Remark", "C 100" );
	c.insertField( c1, md_header, "Summa", "N 10 2" );
	c.insertField( c1, md_header, "Count", "N 10" );
	c.insertField( c1, md_header, "Contragent", "C 90" );
	// Acc register
	c1 = c.insertARegister( "Test saldo register" );
	c.insertField( c1, md_dimensions, "Contragent", "C 90" );
	c.insertField( c1, md_dimensions, "Debet", "C 10" );
	c.insertField( c1, md_dimensions, "Kredit", "C 10" );
	c.insertField( c1, md_resources, "Summa", "N 10 2" );
	c.insertField( c1, md_resources, "Count", "N 10" );
	c.insertField( c1, md_information, "Remark", "C 100" );

	// Set resource values
	c.rc.setValue("dbtitle", DEMO_DBTITLE);
	c.rc.setValue("dbtype", DEMO_DBTYPE);
	c.rc.setValue("dbname", DEMO_DBNAME);
	c.rc.setValue("dbuser", DEMO_DBUSER);
	c.rc.setValue("dbpass", DEMO_DBPASS);
	c.rc.setValue("dbhost", DEMO_DBHOST);
	c.rc.setValue("configfile", DEMO_CONFIGFILE);
	c.writerc( DEMO_RC );
	//return true;
}

void conduct( aDocument *doc, aDatabase *db)
{
	doc->Conduct();
	aARegister *ar = new aARegister("Test saldo register",db); // создаем экземпляр объекта накопительного регистра
        if (ar->SetDocument(doc))
	{
		printf("aAregister::SetDocument() failed\n"); 
		return;
	}
	if (ar->New())
	{
		printf("aAregister::New() failed\n " ); 
		return; 
	} 
	ar->SetValue("Debet","90.2"); // устанавливаем значение дебитового счета
	ar->SetValue("Kredit","41.1"); // устанавливаем значение кредитового счета
	ar->SetValue("Summa",doc->Value("Summa"));   
	ar->SetValue("Count",doc->Value("Count"));
	ar->SetValue("Contragent",doc->Value("Contragent"));
        if (ar->Update()) 
	{
		printf("aAregister::Update() failed\n"); 
		return;
	}
	//ar->ClosePeriod(); // перерасчет остатков
 	delete ar;	
//	return db;
}

int main(int argc, char **argv)
{

QApplication appication(argc,argv,false);	
	aDatabase db;
	Q_ULLONG doc_id;
	create_config();
	if ( db.init(DEMO_RC) )
	{
		db.update();
	}
	// create document
	aDocument *doc = new aDocument("Test saldo document", &db);
	doc->New();
	doc->SetValue("Contragent","bank");
	doc->SetValue("Count", 11);
	doc->SetValue("Summa", 220);
	doc->SetValue("Remark", "this is remark");
	//printf("doc id = %llu",doc->getUid());
	doc_id = doc->getUid();
	doc->Update();
	//doc->select(doc_id);
	conduct(doc,&db);
	doc->UnConduct();
	//doc->select(doc_id);
	doc->SetValue("Contragent","firma");
	doc->SetValue("Count", 16);
	doc->SetValue("Summa", 120);
	doc->SetValue("Remark", "this is remark");
	
	doc->Update();
	conduct(doc,&db);
	db.done();
	return 0;
}
