/****************************************************************************
** $Id: main.cpp,v 1.3 2007/04/19 07:33:39 gr Exp $
** 
** Tool for automatic running Ananas tests
**
** Created : 20051024
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


//#define STOP_ON_ERROR "stop on error

//#define BIG_CATALOGUE "catalogue1"
//#define BIG_DOCUMENT "document1"

#include "ananas.h"
#include <qapplication.h>
#include <math.h>
#include <qmap.h>
#include <stdlib.h>


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

void createConfiguration(	const QMap<QString,QString> &mapGlobal, 
				const QMap<QString, QString> &mapLocal,
				const QString &log)
{
//	printf("create config\n");
	
	aCfg c;
	aCfgItem d1, c1, c2, c3, t, f;
	
	const QString DB_TITLE = "Test 1";
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

	// Document
	c1 = c.insertCatalogue( "Большой каталог" );
	c.insertField( c1, md_group, "name", "C 100" );
	c.insertField( c1, md_group, "alias", "C 40" );
	c.insertField( c1, md_element, "name", "C 100" );
	c.insertField( c1, md_element, "description", "C 200" );
	c.insertField( c1, md_element, "type", "C 40" );
	c.insertField( c1, md_element, "madeIn", "C 60" );
	c.insertField( c1, md_element, "wes", "N 6 2" );
	c.insertField( c1, md_element, "heidht", "N 6 2" );
	c.insertField( c1, md_element, "width", "N 6 2" );
	c.insertField( c1, md_element, "deep", "N 6 2" );

	// Set resource values
	c.rc.setValue("dbtitle", DB_TITLE);
	c.rc.setValue("dbtype", DB_TYPE);
	c.rc.setValue("dbname", DB_NAME);
	c.rc.setValue("dbuser", DB_USER);
	c.rc.setValue("dbpass", DB_PASS);
	c.rc.setValue("dbhost", DB_HOST);
	c.rc.setValue("dbport", DB_PORT);
	c.rc.setValue("configfile", DB_CONFIGFILE);
	c.writerc( DB_RC );
	//return true;
}

int main(int argc, char **argv)
{
	QApplication appication(argc,argv,false);	
	aDatabase db;
	QString log, globalConfig, localConfig;
	const QString test_name = "big catalogue";
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
		}
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("database init"));	
		return 1;
	}
	aCatalogue* cat = new aCatalogue("Большой каталог",&db);
	if(cat)
	{
		aTests::print2log(log,test_name,"OK",QString("catalogue create"));
	}
	else
	{
		aTests::print2log(log,test_name,"ERROR",QString("database create"));
		return 1;
	}
	
	int count = 5;
	int count_group = 1;
	int count_sub_group = 1;
	if(mapLocal.find("element")!=mapLocal.end())
	{
		count = mapLocal["element"].toInt();
	}
	if(mapLocal.find("group")!=mapLocal.end())
	{
		count_group = mapLocal["group"].toInt();
	}
	if(mapLocal.find("sub_group")!=mapLocal.end())
	{
		count_sub_group = mapLocal["sub_group"].toInt();
	}
	int j,k;
	for(j=0; j<count_group;j++)
	{
		cat->UnSelect();
		cat->GroupNew();
		cat->GroupSetValue("name","name");
		cat->GroupSetValue("alias","test_alias");
		//groups++;
		cat->Update();
	}
	for(k=0;k<count_sub_group;k++)
	{
		cat->selectByLevel(0);
		cat->FirstInGroupTable();
		bool end = false;
		Q_ULLONG id;// = new Number;
		int cnt=0;  
		while(!end)
		{
			cat->selectByLevel(0);
			cat->FirstInGroupTable();
			j=0;
			while(j<cnt)
			{
				bool res = cat->NextInGroupTable();
				if(!res)
				{
					end =true;
					break;
				}
				j++;    
			}
			cnt++;
			if(end) break;
			cat->GroupNew();
			cat->GroupSetValue("name",QString("group%1").arg(++k));
			cat->GroupSetValue("alias","test_alias");
			cat->Update();
		//	groups++;
			for(uint i=0; i<count; i++)
			{
				cat->New(false);
				cat->SetValue("name", QString("name%1").arg(rnd(500)));
				cat->SetValue("description",QString("descr%1").arg(rnd()));
				cat->SetValue("type",QString("type%1").arg(rnd(10)));
				cat->SetValue("madeIn",QString("country%1").arg(rnd(100)));
				cat->SetValue("wes",rnd());
				cat->SetValue("heidht",rnd(100));
				cat->SetValue("width",rnd(50));
				cat->SetValue("deep",rnd(10));
				cat->Update();
		//		elements++;
			}
		}
	}
return 0;
}
