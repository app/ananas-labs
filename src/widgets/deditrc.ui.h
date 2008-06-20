/****************************************************************************
** $Id: deditrc.ui.h,v 1.1 2005/05/18 19:14:29 leader Exp $
**
** Code file of the Ananas edit resource file window
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
#include <qfiledialog.h>


void dEditRC::setdata(QString nameRC)
{
	QFile f;
	QString s, sv, sn;
	char buf[256];

	eRCFile->setText(nameRC);
	eDBType->setCurrentItem(0);
	strlist.clear();
	f.setName(nameRC);
	if (f.open(IO_ReadOnly)){
		while (!f.atEnd()) {
			f.readLine(buf, 255);
			s=trUtf8(buf).section("\n",0,0);
			sn=s.section("=",0,0);
			sv=s.section("=",1,1);
			if (sn=="dbtitle") eDBTitle->setText(sv);
			else 
			if (sn=="dbname") eDBName->setText(sv);
			else
			if (sn=="dbuser") eDBUserName->setText(sv);
			else
			if (sn=="dbpass") ePass->setText(sv);
			else
			if (sn=="dbhost") eDBHost->setText(sv);
			else
			if (sn=="dbport") eDBPort->setText(sv);
			else
			if (sn=="configfile") eCfgName->setText(sv);
			else
			if (sn=="dbtype") {
				if (sv=="postgres") eDBType->setCurrentItem(2);
				if (sv=="mysql") eDBType->setCurrentItem(1);
			}
			else
			if (sn=="workdir") eWorkDir->setText(sv);
			else {
				strlist.append(s);
			}
		}
		f.close();
	}
}


void dEditRC::updatecfg()
{
	QFile f;

	f.setName(eRCFile->text());
	if (f.open(IO_WriteOnly)){
		QTextStream ts( &f );
		ts.setEncoding(QTextStream::UnicodeUTF8);

		ts << "dbtitle=" << eDBTitle->text() << "\n";
		ts << "dbname=" << eDBName->text() << "\n";
		ts<<"dbtype=";
		if(eDBType->currentItem()==1) ts<<"mysql\n";
		if(eDBType->currentItem()==2) ts<<"postgres\n";
		ts << "dbuser=" << eDBUserName->text() << "\n";
		ts << "dbpass=" << ePass->text() << "\n";
		ts << "dbhost=" << eDBHost->text() << "\n";
		ts << "dbport=" << eDBPort->text() << "\n";
		ts << "workdir=" << eWorkDir->text() << "\n";
		ts << "configfile=" << eCfgName->text() << "\n";
		if (!strlist.empty()) {
			for ( QStringList::Iterator it = strlist.begin(); it != strlist.end(); ++it ) {
				ts << *it << "\n";
			}
		}
		f.close();
	}
}



void dEditRC::onOK()
{
	updatecfg();
	accept();
}


void dEditRC::onRCFile()
{
		QFileDialog fd( QString::null,
  			"ananas config resource (*.rc)",
			0, 0, TRUE );
		fd.setSelection( eRCFile->text());
		if ( fd.exec() == QDialog::Accepted ) {
			eRCFile->setText(fd.selectedFile());
			setdata(eRCFile->text());
		} else {
			return;
		}
}


void dEditRC::onCFGFile()
{
		QFileDialog fd( QString::null,
  			"ananas config file (*.cfg)",
			0, 0, TRUE );
		fd.setSelection( eCfgName->text());
		if ( fd.exec() == QDialog::Accepted ) {
			eCfgName->setText(fd.selectedFile());
		} else {
			return;
		}
}
