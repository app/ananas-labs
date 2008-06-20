/****************************************************************************
** $Id: dselectdb.ui.h,v 1.2 2007/09/18 11:57:44 app Exp $
**
** Code file of the Ananas select database window
** of Ananas Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Library of the Ananas
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

/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
//#include "acfgobj.h"
#include <qdir.h>
#include <qstring.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qstring.h>

#include "deditrc.h"
#include "acfgrc.h"
#include "alog.h"
#include "binreloc.h"

class rcListViewItem : public QListViewItem
{
public:
	QString rcfile;
	bool group;
	
	rcListViewItem( QListView *parent,
			const QString &name = QString::null, 
			const QString &rc = QString::null,
			bool fgroup = false ): QListViewItem( parent, name )
	{
		init( rc, fgroup );
	};
	
	rcListViewItem( QListView *parent,
			rcListViewItem* after,
			const QString &name = QString::null, 
			const QString &rc = QString::null,
			bool fgroup = false ): QListViewItem( parent, after, name )
	{
		init( rc, fgroup );
	};
	
	rcListViewItem( rcListViewItem *parent,
			const QString &name = QString::null, 
			const QString &rc = QString::null,
			bool fgroup = false ): QListViewItem( parent, name )
	{
		init( rc, fgroup );
	};
	
	void init( const QString &rc = QString::null, bool fgroup = false )
	{
		group = fgroup;
		rcfile = rc;
		if ( group ) setPixmap(0, QPixmap::fromMimeSource("lib_dbgroup.png") );
		else setPixmap(0, QPixmap::fromMimeSource("lib_database.png") );
	};
};

void dSelectDB::init()
{
//	unsigned int i=0;
	//FILE *ff, *ffc, *f_exist;
	QString fname;	
	settings.insertSearchPath( QSettings::Unix, QString(QDir::homeDirPath())+QString("/.ananas"));
	settings.insertSearchPath( QSettings::Windows, "/ananasgroup/ananas" );
	
	local = settings.entryList("/groups").count();
	changes = false;	
	if(!local)
	{
		printf("local settings not found\n");
		settings.insertSearchPath( QSettings::Windows, "/ananasgroup/ananas/globalsettings");
#ifdef _Windows
	
#else
		QString suff = "*_grouprc";
		BrInitError error; 
		if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED) { 
			aLog::print(aLog::MT_INFO, tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
			aLog::print(aLog::MT_INFO, tr("Will fallback to hardcoded default path.\n"));
		} 
		aLog::print(aLog::MT_DEBUG, tr("dSelectDB::init  BinReloc path to etc dir is %1.\n").arg( br_find_etc_dir("/etc") ));
		
		QString etcDir;
		if ( QString(br_find_prefix("/usr")) == "/usr" ) {
			etcDir= "/etc";
		} else {
			etcDir= br_find_etc_dir("/etc");
		}

		QDir dir(etcDir + "/ananas",suff,QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::Readable);
		QStringList subkeys = dir.entryList(suff);
		settings.insertSearchPath(QSettings::Unix,etcDir + "/ananas/");
		QStringList entryGroup;
		printf("subkeys.count=%d\n",subkeys.count());
		for(uint i=0; i<subkeys.count();i++)
		{
			QString str =subkeys[i];
			str = str.left(str.length()-2); // length("rc")=2
			printf(">>>%s\n",str.ascii());
			entryGroup =settings.entryList("/"+str);
			printf("count entry = %d\n",entryGroup.count());
			settings.beginGroup("/"+str);
			readSettings(entryGroup);	
			settings.endGroup();
		}
#endif
		//local = false;
	}
	else
	{
#ifdef _Windows 
		
#else
		QStringList lst = settings.entryList("/groups");
		settings.beginGroup("/groups");
		readSettings(lst);
		settings.endGroup();
#endif
	}
	setIcon( rcIcon("a-system.png"));
	printf("init selectDB\n");	
	listDBRC->hideColumn( 1 );
	listDBRC->setSorting( -1 );
	listDBRC->header()->hide();
	listDBRC->setRootIsDecorated(1);
	buttonOk->setEnabled( FALSE ); 
	return;
}

void dSelectDB::readSettings(QStringList entryGroup)
{

	rcfile="";
	ro_mode=0;
	QFile f, fc;
	FILE *ffc;
	QString s, sp, sn, rc;
	char buf[1024];
	rcListViewItem *item, *gitem=NULL; //, *subitem;
	for(uint j=0; j<entryGroup.count();j++)
	{
        	QStringList eitems;
		eitems = settings.entryList(entryGroup[j]);
		QString groupName = "unknown group";
		groupName = settings.readEntry(entryGroup[j]);
		printf("group name=%s\n",groupName.ascii());
		rcListViewItem * lastIt = (rcListViewItem *) listDBRC->lastItem();
		if(lastIt!=NULL)
		{
			while(lastIt->depth()>0)
			{
				lastIt =(rcListViewItem *) lastIt->parent();
			}
			gitem= new rcListViewItem(listDBRC, lastIt, groupName, "", true );
		}
		else
		{
			gitem= new rcListViewItem(listDBRC, groupName, "", true );
		}
//		withgroups=1;

		for(int k = eitems.count()-1; k>=0; k--) 
		{
			//printf("k = %d\n",k);			
			if(k<0) break;
			//printf("read entry %s\n",(entryGroup[j]+"/"+eitems[k]).ascii());
			rc = settings.readEntry(entryGroup[j]+"/"+eitems[k]);
			printf("rc = %s\n",rc.ascii());
			ffc=fopen((const char *)rc,"r");
			if (ffc)
			{
				while (!feof(ffc)) 
				{
					fgets(buf, sizeof(buf), ffc);
					s=trUtf8(buf).section("\n",0,0);
					if (s.section("=",0,0)=="dbtitle")
					{
						sn=s.section("=",1,1);
						break;
					}
				}
				fclose(ffc);
			}
			if (gitem) item= new rcListViewItem( gitem, sn, rc );
			else item= new rcListViewItem( listDBRC, sn, rc );
		}
	}
}


void dSelectDB::itemSelect( QListViewItem *item )
{
//        bool isItem = TRUE;
	if (! item ) return;
	rcListViewItem *i = ( rcListViewItem *) item ;
	tDBRC->setText( i->rcfile );
//	if ( item->text(1).isEmpty() )  isItem = FALSE;
	buttonOk->setEnabled( !i->group ); 
}


void dSelectDB::newGroup()
{
	QListViewItem *gitem;
	gitem = new rcListViewItem(listDBRC, tr("New group"), "", true );
	listDBRC->setRootIsDecorated(1);
	gitem->setOpen(true);
	listDBRC->setSelected(gitem, true);
	editItem();
	withgroups=1;
	changes = true;
	//saveRC();
}


void dSelectDB::newItem()
{
	rcListViewItem *item, *gitem;
	QString rc;
	item= ( rcListViewItem *) listDBRC->selectedItem();
	if (!item) return;
	if (withgroups) {
		if (item->parent()) gitem = ( rcListViewItem *) item->parent();
		else gitem=item;
		item = new rcListViewItem(gitem, tr("New item"), "myrc");
		gitem->setOpen(true);

	} else {
		item = new rcListViewItem(listDBRC, tr("New item"), "myrc");
	}
	listDBRC->setSelected(item, true);
	editItem();
	changes = true;
}


void dSelectDB::editItem()
{
	rcListViewItem *item;
//	QString rc;
	dEditRC d;	

	item = ( rcListViewItem *) listDBRC->selectedItem();
	if (!item) return;
//	rc= item->rcfile;
	if ( item->group ) {
	// Group
		item->setRenameEnabled(0, true);
		item->startRename(0);
		changes = true;
	} else {
	// Resource
		d.setdata( item->rcfile );
		d.eDBTitle->setText(item->text(0));
		if ( d.exec() == QDialog::Accepted ) {
			item->rcfile = d.eRCFile->text();
			tDBRC->setText( item->rcfile );
			item->setText(0, d.eDBTitle->text());
			changes = true;
		} else {
			return;
		}
	}
}



void dSelectDB::deleteItem()
{
	QListViewItem *item;
	item=listDBRC->selectedItem();
	if (item) delete item;
	if (listDBRC->childCount()==0) withgroups=0;
	changes = true;
}


void dSelectDB::saveRC()
{
	rcListViewItem *item, *gitem;
	QFile f( rcfile );

//	item= ( rcListViewItem *) listDBRC->selectedItem();
	if (ro_mode) return;
	if (!local)
	{
		if(!changes) return;
		QString home = QDir::homeDirPath();
#ifndef _Windows
		QString msg = QString("Все внесенные изменения будут сохранены локально в вашем домашнем каталоге.\nПри очередном запуске программы будут использованы локальные настройки из каталога\n%1/.ananas.\nЕсли Вы хотите использовать глобальные настройки, вам следует удалить каталог\n%2/.ananas").arg(home).arg(home); 
#else
		QString msg = "save settings local?";
#endif
		if(QMessageBox::question(this,tr("save"),QString::fromUtf8(msg),QMessageBox::Ok,QMessageBox::Cancel)!=QMessageBox::Ok)
		{
			return;
		}
	}
	BrInitError error; 
	if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED) { 
		aLog::print(aLog::MT_INFO, tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
		aLog::print(aLog::MT_INFO, tr("Will fallback to hardcoded default path.\n"));
	} 
	aLog::print(aLog::MT_DEBUG, tr("dSelectDB::saveRC  BinReloc path to etc dir is %1.\n").arg( br_find_etc_dir("/etc") ));
	QString etcDir;
	if ( QString(br_find_prefix("/usr")) == "/usr" ) {
		etcDir= "/etc";
	} else {
		etcDir= br_find_etc_dir("/etc");
	}
	
	settings.removeSearchPath( QSettings::Unix, etcDir + "/ananas" );
	settings.removeSearchPath( QSettings::Windows, "/ananasgroup/globalsettings");
		
	
//	if (f.open(IO_WriteOnly))
//	{
//		QTextStream ts( &f );
//		ts.setEncoding(QTextStream::UnicodeUTF8);
		gitem= ( rcListViewItem *) listDBRC->firstChild();
		uint gcount=0;
		uint ecount=0;
		clearSettings();
		printf("begin\n");

		settings.beginGroup("/groups");
		
		while (gitem)
		{
			if (withgroups)
			{
//				printf("group\n");
//				ts << "group=" << gitem->text(0) << "\n";
                                settings.writeEntry(QString::number(gcount),gitem->text(0));
				if(gitem->childCount())
				{
					item = ( rcListViewItem *) gitem->firstChild();
					while (item) 
					{
//						printf("elem 1\n");
//						ts << "rc=" << item->rcfile << "\n";
						settings.writeEntry(QString::number(gcount)+"/"+QString::number(ecount),item->rcfile);
						item =  ( rcListViewItem *) item->nextSibling();
						++ecount;
					}
				}
			}
//			else
//			{
			//	printf("elem\n");
				//ts << "rc=" << gitem->rcfile << "\n";
//			}
			++gcount;
			gitem =  ( rcListViewItem *) gitem->nextSibling();
		}
		settings.endGroup();
//		f.close();
//	}
}


void dSelectDB::onOK()
{
	rcListViewItem *item;

	saveRC();
	item =  ( rcListViewItem *) listDBRC->selectedItem();
	if (item) {
	             if ( !item->rcfile.isEmpty() ) {
			 rcfile = item->rcfile;
			 accept();
		}
	}
}


void dSelectDB::onCancel()
{
	//saveRC();
	reject();
}


void dSelectDB::ItemRenamed(QListViewItem *item, int col)
{
	if (!item) return;
	if (col>1) return;
}


void dSelectDB::clearSettings()
{
        QStringList eitems;
	QStringList entryGroup =settings.entryList("/groups");
	settings.beginGroup("/groups");
	for(uint j=0; j<entryGroup.count();j++)
	{
		eitems = settings.entryList(entryGroup[j]);
		settings.removeEntry(entryGroup[j]);	
		for(int k = eitems.count()-1; k>=0; k--) 
		{
			if(k<0) break;
			settings.removeEntry(entryGroup[j]+"/"+eitems[k]);
		}
	}
	settings.endGroup();
}
