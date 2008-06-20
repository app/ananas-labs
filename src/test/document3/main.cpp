/****************************************************************************
** $Id: main.cpp,v 1.3 2007/04/19 07:33:58 gr Exp $
** 
** Test saldo for Ananas
**
** Created : 20051107
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

#include "ananas.h"
#include <qapplication.h>
#include <math.h>
#include <stdlib.h>
#include <qmap.h>


double rnd(double m=1);


double rnd(double m)
{
	double res;
#ifdef _Windows
	res = rand()*m;
#else
	res = random()*m;
#endif
	return res;
	
}
int summ(int l, int r)
{
	int res =0;
	for(uint i=l; i<=r;i++)
	{
		res+=i;
	}
	return res;
}


void createConfiguration(	const QMap<QString,QString> &mapGlobal, 
				const QMap<QString, QString> &mapLocal,
				const QString &log)
{
//	printf("create config\n");
	
	aCfg c;
	aCfgItem d1, c1, c2, doc, ar, t;
	
	const QString test_name = "test saldo1";
	const QString DB_TITLE = "Test 2";
	const QString DB_TYPE = mapGlobal["db_type"];
	const QString DB_PORT = mapGlobal["db_port"];
	const QString DB_USER = mapGlobal["db_user"];
	const QString DB_PASS = mapGlobal["db_password"];
	const QString DB_HOST = mapGlobal["db_host"];
	
	const QString DB_NAME = mapLocal["db_name"];
	const QString DB_CONFIGFILE = mapLocal["db_config"];
	const QString DB_RC = mapLocal["db_rc"];
	
	c.createNew();
	c.setInfo( md_info_name, "тест" );
	c.setInfo( md_info_author, "anonimus" );

	c1 = c.insertCatalogue( "Товары" );
	
	c.insertField( c1, md_group, "Наименование", "C 100" );
	c.insertField( c1, md_element, "Наименование", "C 100" );
	
	c2 = c.insertCatalogue( "Контрагенты" );

	c.insertField( c2, md_group, "Наименование", "C 100" );
	c.insertField( c2, md_element, "Наименование", "C 100" );
	
	doc = c.insertDocument("Тестовый документ");

	c.insertField( doc, md_header, "Номер", "C 40" );
	c.insertField( doc, md_header, "Дата", "D" );
	c.insertField( doc, md_header, "Основание", "C 100" );
	c.insertField( doc, md_header, "Контрагент", QString("O %1").arg(c.attr(c2,mda_id)) );
	
	t = c.insertDocumentTable(doc,"Таблица");
	
	c.insertField( t, "", "Наименование", QString("O %1").arg(c.attr(c1,mda_id)) );
	c.insertField( t, "", "Количество", "N 5 0" );
	c.insertField( t, "", "Цена", "N 10 2" );
	c.insertField( t, "", "Сумма", "N 12 2" );
	
	ar = c.insertARegister( "Главная книга" );
	c.insertField( ar, md_dimensions, "Дебет", "C 10" );
	c.insertField( ar, md_dimensions, "Кредит", "C 10" );
	c.insertField( ar, md_dimensions, "Товар", QString("O %1").arg(c.attr(c1,mda_id)) );
	c.insertField( ar, md_dimensions, "Контрагент", QString("O %1").arg(c.attr(c2,mda_id)) );
	c.insertField( ar, md_resources, "Количество", "N 10" );
	c.insertField( ar, md_resources, "Сумма", "N 12 2" );
	
	// Set resource values
	c.rc.setValue("dbtitle", DB_TITLE);
	c.rc.setValue("dbtype", DB_TYPE);
	c.rc.setValue("dbname", DB_NAME);
	c.rc.setValue("dbuser", DB_USER);
	c.rc.setValue("dbpass", DB_PASS);
	c.rc.setValue("dbhost", DB_HOST);
	c.rc.setValue("dbport", DB_PORT);
	c.rc.setValue("configfile", DB_CONFIGFILE);
	
	if(!c.writerc( DB_RC ))
	{
		aTests::print2log(log,test_name,"OK",QString("write configuration"));
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("write configuration"));
	}
	//return true;
}

void delete_cat(aCatalogue *cat)
{
	cat->Select();
	bool res = false;
	while(!res)
	{
		res = cat->selectByLevel(0);
		cat->GroupDelete();
	}
}

bool create_cat(aCatalogue *cat, const QString &text, int count)
{
	bool res =0;
	cat->UnSelect();
	res+=cat->GroupNew();
	res+=cat->GroupSetValue("Наименование","тестовая группа");
	res+=cat->Update();
	for(uint i=0; i<count; i++)
	{
		res+=cat->New(false);
		res+=cat->SetValue("Наименование", QString("%1%2").arg(text).arg(i));
		res+=cat->Update();
	}
return 0;
}

int main(int argc, char **argv)
{
	QApplication appication(argc,argv,false);	
	aDatabase db;
	QString log, globalConfig, localConfig;
	const QString test_name = "test saldo1";
	log = 		aTests::parseCommandLine(argc,argv,"--log");
	globalConfig = 	aTests::parseCommandLine(argc,argv,"--globalconfig");
	localConfig = 	aTests::parseCommandLine(argc,argv,"--localconfig");
	
	QMap<QString,QString> mapGlobal = aTests::readConfig(globalConfig,log);
	QMap<QString,QString> mapLocal = aTests::readConfig(localConfig,log);
	
	createConfiguration(mapGlobal,mapLocal,log);

	if(db.init(mapLocal["db_rc"]))
	{
		aTests::print2log(log,test_name,"OK",QString("database init"));
		if(db.update())
		{
			aTests::print2log(log,test_name,"OK",QString("database update"));
		}
		else
		{
			aTests::print2log(log,test_name,"ERROR",QString("database update"));
			return 1;
		}
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("database init"));	
		return 1;
	}
	
	int count_doc =10;
	int count_table_line=10;
	
	if(mapLocal.find("document count")!=mapLocal.end())
	{
		count_doc = mapLocal["document count"].toInt();
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `document count'"));
	}
	if(mapLocal.find("document table count")!=mapLocal.end())
	{
		count_table_line = mapLocal["document table count"].toInt();
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `document table count'"));
	}
	int i=0;
	int j;
	aCatalogue* cat1 = new aCatalogue("Контрагенты",&db);
	if(cat1)
	{
		aTests::print2log(log,test_name,"OK",QString("catalogue1 create"));
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("catalog1 create"));
		return 1;
	}
	aCatalogue* cat2 = new aCatalogue("Товары",&db);
	if(cat2)
	{
		aTests::print2log(log,test_name,"OK",QString("catalogue2 create"));
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("catalog2 create"));
		return 1;
	}
	
	delete_cat(cat1);
	delete_cat(cat2);
	if(create_cat(cat1,"contragent", count_doc)==0)
	{
		aTests::print2log(log,test_name,"OK",QString("catalogue1 fill"));
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("catalog1 fill"));
	}
			
	if(create_cat(cat2,"towar",count_table_line)==0)
	{
		aTests::print2log(log,test_name,"OK",QString("catalogue2 fill"));
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("catalog2 fill"));
	}
	
	cat1->Select();
	
	if(cat1->First())
	{
		 aTests::print2log(log,test_name,"OK",QString("catalogue1 select"));
	}
	else
	{
		 aTests::print2log(log,test_name,"ERROR",QString("catalogue1 select"));
		 return 1;
	}
	cat2->Select();
	
	aDocument *doc = new aDocument("Тестовый документ",&db);
	if(doc)
	{
		aTests::print2log(log,test_name,"OK",QString("test document created"));
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("test document created"));
		return 1;
	}

	aARegister *ar = new aARegister("Главная книга",&db);
	if(ar)
	{
		aTests::print2log(log,test_name,"OK",QString("aAregister created"));
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("aAregister created"));
		return 1;
	
	}
	ar->SetDocument(doc); 
	ar->SetTable("Таблица");
	QValueList<Q_ULLONG> l;
	for ( i=0; i<count_doc;i++)
	{
		doc->New();
		doc->SetValue("Номер",i);
		doc->SetValue("Дата", QDateTime::currentDateTime());
		doc->SetValue("Основание", QString("тестовое основание #%1").arg(i));
		doc->SetValue("Контрагент", cat1->sysValue("id"));
		doc->Update();
		l.append(doc->getUid());
		aTests::print2log(log,test_name,"NOTE",QString("create doc %1").arg(doc->getUid()));
		cat2->First();
		for(j=0; j<count_table_line; j++)
		{
			doc->TableSelect("Таблица");
			doc->TableNewLine("Таблица");
			doc->TableSetValue("Таблица","Наименование",cat2->sysValue("id"));
			doc->TableSetValue("Таблица","Количество",j+1);
			doc->TableSetValue("Таблица","Цена",1);
			doc->TableSetValue("Таблица","Сумма",j+1);
			doc->TableUpdate("Таблица");
			ar->New();
			ar->SetValue("Дебет","41.2"); 
			ar->SetValue("Кредит","60");
			ar->SetValue("Количество",j+1);
			ar->SetValue("Сумма",j+1);
			ar->SetValue("Товар",cat2->sysValue("id"));
			ar->SetValue("Контрагент",cat1->sysValue("id"));
			ar->Update();
			cat2->Next();
		}
		cat1->Next(); 
		if(doc->Conduct()==0)
		{
			aTests::print2log(log,test_name,"OK",QString("document conducted"));
		}
		else
		{
			aTests::print2log(log,test_name,"ERROR",QString("document conducted"));
			return 1;
		}
		
	}

	bool unconduct=false;
	
	if(mapLocal.find("unconduct")!=mapLocal.end() && mapLocal["unconduct"].lower()=="true")
	{
		unconduct = true;
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `unconduct"));
	}
	
	QValueList<Q_ULLONG>::iterator it;
	if(unconduct)
	{
		
		for ( it = l.begin(); it != l.end(); ++it )
		{
			doc->select(*it);
			aTests::print2log(log,test_name,"NOTE",QString("unconduct  doc %1").arg(*it));
			if(doc->IsConducted()) doc->UnConduct();
		}
	}


	int delete_first =0;
	int delete_last=0;
	
	if(mapLocal.find("delete first")!=mapLocal.end())
	{
		delete_first = mapLocal["delete first"].toInt();
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `delete first"));
	}
	if(mapLocal.find("delete last")!=mapLocal.end())
	{
		delete_last = mapLocal["delete last"].toInt();
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `delete last'"));
	}
	
	QString delete_line;
	int doc_nl=0;
	int docline=0;
	if(mapLocal.find("delete line")!=mapLocal.end())
	{
		
		delete_line = mapLocal["delete line"];
		if(delete_line.section(":",0,0)!="")
		{
			doc_nl=delete_line.section(":",0,0).toInt();
			docline=delete_line.section(":",1,1).toInt();
		}
		if(!doc_nl || !docline)
		{
			 aTests::print2log(log,test_name,"WARNING",QString("value of parametr `delete line' is invalid"));
					 
		}
				
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `delete line"));
	}
	int count=0;	
	for ( it = l.begin(); it != l.end(); ++it )
	{
		count++;
	        if(count==doc_nl)
		{
			doc->select(*it);
			aTests::print2log(log,test_name,"NOTE",QString("delete line %1 doc in  %2 ").arg(docline).arg(*it));
			//doc->TableDeleteLine();
		}
	}
	
	QString change_res;
	int doc_chr=0;
	int doc_chr_ln=0;
	if(mapLocal.find("change line res")!=mapLocal.end())
	{
		
		change_res = mapLocal["change line res"];
		if(change_res.section(":",0,0)!="")
		{
			doc_chr=change_res.section(":",0,0).toInt();
			doc_chr_ln=change_res.section(":",1,1).toInt();
		}
		if(!doc_chr || !doc_chr_ln)
		{
			 aTests::print2log(log,test_name,"WARNING",QString("value of parametr `change line res' is invalid"));
					 
		}
				
	}
	else
	{
		aTests::print2log(log,test_name,"WARNING",QString("can't find parametr `change line res"));
	}
	
	count =0;
	for ( it = l.begin(); it != l.end(); ++it )
	{
		count++;
	        if(count==doc_chr)
		{
			doc->select(*it);
			aTests::print2log(log,test_name,"NOTE",QString("change doc %1 line %1 ").arg(*it).arg(doc_chr_ln));
		//	doc->TableSelect("Таблица");
		//	doc->TableSetValue("Таблица","Товар",100);
		//	doc->TableUpdate();
		}
	}
	
	count =0;
	//QValueList<Q_ULLONG>::iterator it;
	for ( it = l.begin(); it != l.end(); ++it )
	{
		count++;
	        if(count<=delete_first|| count>count_doc-delete_last)
		{
			doc->select(*it);
			aTests::print2log(log,test_name,"NOTE",QString("delete doc %1").arg(*it));
			doc->Delete();
		}
	}
	cat1->First();
	for ( i=0; i<count_doc;i++)
	{
		
		QVariant summa= ar->getSaldo(QDateTime::currentDateTime(),"Контрагент",cat1->sysValue("id"),"Сумма");
		double sum = summ(0,count_table_line);
		if(i<delete_first) 
		{
			sum = 0;
		}
		if(i>=count_doc-delete_last)
		{
			sum = 0;
		}
		if(unconduct) sum=0;
		if(summa==sum)
		{
			aTests::print2log(log,test_name,"OK",QString("saldo kontragent %1=%2").arg(summa.toString()).arg(sum));
		}
		else
		{
			aTests::print2log(log,test_name,"ERROR",QString("saldo kontragent %1!=%2").arg(summa.toString()).arg(sum));
		}
		cat1->Next();
	}
	cat2->First();
	for ( i=0; i<count_table_line;i++)
	{
		
		QVariant summa= ar->getSaldo(QDateTime::currentDateTime(),"Товар",cat2->sysValue("id"),"Количество");
		int cnt = count_doc-delete_first-delete_last;
		
		if(unconduct) cnt=0;
		
		if(summa==(i+1)*cnt)
		{
			aTests::print2log(log,test_name,"OK",QString("saldo tovar%1=%2").arg(summa.toString()).arg((i+1)*cnt));
		}
		else
		{
			aTests::print2log(log,test_name,"ERROR",QString("saldo tovar%1!=%2").arg(summa.toString()).arg((i+1)*cnt));
		}
		if(!cat2->Next()) break;
	}
//	aTests::print2log(log,test_name,"NOTE","delete cat1");
	delete cat1;
//	aTests::print2log(log,test_name,"NOTE","delete cat2");
	delete cat2;
//	aTests::print2log(log,test_name,"NOTE","delete doc");
	delete doc;
//	aTests::print2log(log,test_name,"NOTE","delete ar");
	delete ar;
	aTests::print2log(log,test_name,"OK","end test");
//abort();
//	exit(0);
	db.done();
	return 0;
}

