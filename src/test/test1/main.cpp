/****************************************************************************
** $Id: main.cpp,v 1.7 2005/07/04 10:09:32 red75 Exp $
**
** Main file of the Ananas test1 of Ananas
** Demo collection
**
** Created : 20040928
**
** Copyright (C) 2003-2004 Grigory Panov, Yoshkar-Ola.  All rights reserved.
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
 * Creates large catalogue.
 * Author: Grigory Panov
 *
*/
#include <stdlib.h>
#include <math.h>
#include <qapplication.h>
#include <qstring.h>
#include <qstringlist.h>

#include <qfile.h>
#include <qdatatable.h>
#include <qtimer.h>
#include <qobject.h>

#include "ananas.h"

#define DEMONAME "Test 1 - Create large catalogue"
bool
createIndexes(aDatabase &db,const QString &table, const QString &indexl)
{
	int idxcount, n;
	bool rc = true;
	QString s, query;
	QSqlQuery q;

	// Создадим индексы
	idxcount=3;
	n = 0;
	s = indexl.section(",", n, n);
	while ( !s.isEmpty() ) {
		query = QString("create index %1_idx%2 on %3 %4").arg( table ).arg( idxcount ).arg( table ).arg( s );
		printf("%s\n", (const char *) query);
		q = db.db()->exec( query );
		idxcount++; n++;
		s = indexl.section(",", n, n);
	}
	return rc;
}
QString
getRandomString(int len)
{
	QString res;
#ifdef Q_OS_WIN32
	int realLength = rand()/(RAND_MAX/len);
#else
	int realLength = random()/(RAND_MAX/len);
#endif
	for(int i = 0; i<realLength; i++)
	{

#ifdef Q_OS_WIN32
		QChar ch((int)(rand()/(RAND_MAX/100)));
#else
		QChar ch((int)(random()/(RAND_MAX/100)));
#endif

		if(!ch.isLetterOrNumber()) 
		{
			i--;
			continue;
		}
		else
		{
			res+=ch;
		}
	}
  return res;
}

double
getRandomDouble(int len,int)// dec)
{
#ifdef Q_OS_WIN32
	double res = rand()/(RAND_MAX/pow(10,len));
#else

	double res = random()/(RAND_MAX/pow(10,len));
#endif

	return res;
}
void
demo()
{
	aDatabase* db;
	QString query;	
//	int g_count = 27;
//	int g_num,
	int count;
//	int level=0;
	aCatalogue *cat=0;
	Q_ULLONG id=0,idp=0,last_root=1;
//	int kol_elem=3;
//	QString u1,u4,u5,u6,qstr;
//	double u3,u2;
	QString qstr;
	const int KOL_VO = 300;
	char str[100];
	FILE *f;
//	long idd=1;
	 db= new aDatabase();

	if ( db->init("../test.rc") ) // init resourse
	{
		aCfg* md = &db->cfg; // get metadata
		aCfgItem obj = md->find(mdc_metadata); // find root
		obj = md->findChild(obj,md_catalogues); // find Catalogues branch
		if(obj.isNull()) return; // exit if no Catalogues branch
		obj = md->findChild(obj, md_catalogue); // else find first Catalogue
	 	if(obj.isNull()) // if haven't Catalogues in metadata 
		{
			obj = md->insertCatalogue("LargeCatalogue"); // creates new catalog
			// insert fields in element branch 
			md->insertField(obj,md_element,"string20","C 20 0 *");
			md->insertField(obj,md_element,"string80","C 80 0 *");
			md->insertField(obj,md_element,"string60","C 60 0 *");
			md->insertField(obj,md_element,"made_in20","C 20 0 *");
			md->insertField(obj,md_element,"wes20","N 20 5 *");
			md->insertField(obj,md_element,"rost40","N 40 0 *");
			// insert field in group branch
			md->insertField(obj,md_group,"name40","C 40 0 *");
			md->insertField(obj,md_group,"last name30","C 30 0 *");
//			md->insert(obj,md_field)
			printf(">>>new catalog\n");
		}
		md->write("../test.cfg"); // saves chandes in cfg file 
		db->update(); // updates changes in database
		db->done(); // save db
		db->init("../test.rc");
		QString strField;
		cat = new aCatalogue (obj,db); // creates object catalogue
		QStringList lst, list, lstId,lstType,lstLen;
		lst = cat->getUserFields(); // gets list fields of elements
		for(uint i=0; i<lst.count(); i++)
		// work correct with field type String or Numeric only	
		{
			lstId.append(lst[i].remove(0,2));// get id field
			qstr = md->attr(md->find(lstId[i].toInt()),mda_type); // find type of field
			printf("<<type = %s\n",qstr.ascii());
			lstType.append(qstr.left(1)); // save type
			lstLen.append(qstr.section(' ',1,1)); // save length 
		}
		lst = cat->getUserFields();
	 	// delete all values from catalogue
		// this is not good sample, but fast
		db->db()->exec(QString("delete from cg%1").arg(md->id(obj)));
		db->db()->exec(QString("delete from ce%1").arg(md->id(obj)));
		f = fopen("group.txt","r"); // open file with group names
		if(!f) return ;
		else printf("file open\n");
		while(!feof(f))
		{
			fgets(str,100,f);
			//id++;
			if(strlen(str)<2) break;
			qstr = QString::fromUtf8(str);
			qstr.remove(qstr.length()-1,qstr.length());
			printf("`%s'\n",(const char*) qstr.local8Bit());
			if(qstr.isNull()) break;
			if(qstr.contains(':'))
			{
				idp=0;
			//	level=0;
				last_root=id;
			}
			else
			{
				idp=last_root;
			//	level=1;
			}
//			printf("exec query %d\n",id);
	//db.db()->exec(QString("insert into cg145 values(%1,'%2',%3,%4,'%5')").arg(id).arg('1').arg(level).arg(idp).arg(qstr));
			cat->newGroup(idp);
			id = cat->GroupSysValue("id").toULongLong();
			if(qstr.contains(':'))
			{
				idp=0;
			//	level=0;
				last_root=id;
			}
			
			list = cat->getGroupUserFields();
			for(uint i=0; i<list.count(); i++)
			{
				cat->GroupSetSysValue(list[i],qstr );
				cat->GroupUpdate();
			}
#ifdef Q_OS_WIN32
			count = (int) (rand()/(RAND_MAX/KOL_VO));

#else
			count = (int) (random()/(RAND_MAX/KOL_VO));
#endif

			for(int i=1; i<count; i++)
			{
				
				cat->newElement(id);
				for(uint j=0; j<lst.count(); j++)
				{
					//printf(">> %s\n",lstType[j].ascii());
					if(lstType[j]=="C")
					{
						strField = getRandomString(lstLen[j].toInt());
						cat->setSysValue(lst[j],strField);
					}
					else
					{
						cat->setSysValue(lst[j],getRandomDouble(lstLen[j].toInt(),10));
					}
				}
				cat->Update();
			}
			
			printf("%d row affected\n",count);
		}
//		createIndexes(db,"ce145","uf146,uf147,uf148,uf149,uf164,uf166");
	}
		//db.update();
	printf("end\n");
	fclose(f);
	if(cat) delete cat;
	cat = NULL;
	db->done();
//	delete db;
	return;
}

///////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv){

        QApplication app( argc, argv, FALSE );
	setMessageHandler();

        printf("Ananas v.%s %s\n\n", ananas_libversion(), DEMONAME);
	demo(); // printf("ok\n");
	printf("ok\n");
	return 0;
}
