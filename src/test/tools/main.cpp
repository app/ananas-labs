/****************************************************************************
** $Id: main.cpp,v 1.2 2005/12/19 15:01:49 gr Exp $
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


#define STOP_ON_ERROR "stop on error"

#define BIG_CATALOGUE "catalogue1"
#define BIG_DOCUMENT "document1"
#define SALDO1 "document2"
#define SALDO2 "document3"
#define GUI1 "bs-choice-open-close.pl"

#include "ananas.h"
#include <qapplication.h>
#include <qprocess.h>

int launchTest(const QString &test_name, const QString &path, const QString &log)
{
	QProcess proc( qApp );
	proc.addArgument( path + test_name );
	proc.addArgument( "--log=" + log );
	proc.addArgument( "--localconfig="+path+"test.config");
	proc.addArgument( "--globalconfig=tests.config" );
	
	if ( !proc.start() )
	{
		aTests::print2log(log,test_name,"ERROR","start test error");		
		return 1;
	}
	
	while(proc.isRunning())
	{
#ifndef _Windows		
		sleep(1);
#endif		
	}
	
	if(!proc.normalExit())
	{

		aTests::print2log(log,test_name,"ERROR");
		return 1;
	}
	else	
	{
		aTests::print2log(log,test_name,"OK");
	}
	return 0;

}

int main(int argc, char **argv)
{

QApplication appication(argc,argv,false);	

	QString param, log;//= QDir::convertSeparators(QDir::homeDirPath()+"/.ananas/default.log");
//	printf("default log = %s\n",log.ascii());
	log = aTests::parseCommandLine(argc,argv,"-log");
	bool stop;
	bool hasError = false;
//	printf("log = %s\n",log.ascii());
	aTests::printline2log(log);
	aTests::print2log(log,"main","OK","begin of tests");
	QMap<QString, QString> map = aTests::readConfig("tests.config",log);
	if(map.find(STOP_ON_ERROR)!=map.end())
	{
		if(map[STOP_ON_ERROR].lower()=="true")
		{
			stop = true;
		}
		else
		{
			stop = false;
		}
	}
	// test 1
	if(map.find(BIG_CATALOGUE)!=map.end() && map[BIG_CATALOGUE].lower()=="true")
	{
		QString path = "src/test/catalogue1/";
		
		if ( launchTest(BIG_CATALOGUE,path,log) )
		{
			hasError = true;
			if(stop)
			{
				aTests::print2log(log,"main","ERROR","end of tests");
				return 1;
			}
		}
	}
	else
	{
		aTests::print2log(log,BIG_CATALOGUE,"SKIPE");
	}
	// tets 2
	if(map.find(BIG_DOCUMENT)!=map.end() && map[BIG_DOCUMENT].lower()=="true")
	{
		QString path = "src/test/document1/";
		
		if ( launchTest(BIG_DOCUMENT,path,log) )
		{
			hasError = true;
			if(stop)
			{

				aTests::print2log(log,"main","ERROR","end of tests");
				return 1;
			}
		}
	}
	else
	{
		aTests::print2log(log,BIG_DOCUMENT,"SKIPE");
	}
	// tets 3 
	if(map.find(SALDO1)!=map.end() && map[SALDO1].lower()=="true")
	{
		QString path = "src/test/document2/";
		
		if ( launchTest(SALDO1,path,log) )
		{
			hasError = true;
			if(stop)
			{

				aTests::print2log(log,"main","ERROR","end of tests");
				return 1;
			}
		}
	}
	else
	{
		aTests::print2log(log,SALDO1,"SKIPE");
	}
	if(map.find(SALDO2)!=map.end() && map[SALDO2].lower()=="true")
	{
		QString path = "src/test/document3/";
		
		if ( launchTest(SALDO2,path,log) )
		{
			hasError = true;
			if(stop)
			{

				aTests::print2log(log,"main","ERROR","end of tests");
				return 1;
			}
		}
	}
	else
	{
		aTests::print2log(log,SALDO2,"SKIPE");
	}
	if(map.find(GUI1)!=map.end() && map[GUI1].lower()=="true")
	{
		QString path = "src/test/gui/";
		
		if ( launchTest(GUI1,path,log) )
		{
			hasError = true;
			if(stop)
			{

				aTests::print2log(log,"main","ERROR","end of tests");
				return 1;
			}
		}
	}
	else
	{
		aTests::print2log(log,GUI1,"SKIPE");
	}
	
	if(!hasError)
	{
		aTests::print2log(log,"main","OK","end of tests");
	}
	else
	{
		aTests::print2log(log,"main","ERROR","end of tests");
	}
	return 0;
}
