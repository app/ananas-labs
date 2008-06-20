/****************************************************************************
** $Id: deditcfg.ui.h,v 1.14 2008/06/09 11:47:59 app Exp $
**
** Code file of the Ananas edit configuration parametrs window
** of Ananas Designer applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Designer application  of the Ananas
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
#include "acfg.h"
#include "qlayout.h"
#include "qsproject.h"
#include "qsscript.h"
//#include "qseditor.h"
#include <qsinterpreter.h>
#include <qstatusbar.h>

#ifndef QSA_NO_IDE
#include "qsworkbench.h"
#endif


void dEditCfg::init()
{
	delete statusBar();

	eDBType->clear();
	eDBType->insertItem(trUtf8("Unknown"), 0);
	eDBType->insertItem(trUtf8("MySQL"), 1);
	eDBType->insertItem(trUtf8("Postgres"), 2);
//	QGridLayout *l=new QGridLayout(tabWidget->page(2));
//	eModule=NULL;
//	eModule = new QSEditor(tabWidget->page(2), "global module");
//	l->addWidget(eModule, 5, 5, 0);
	eModule->setInterpreter(new QSInterpreter());
}



void dEditCfg::destroy()
{
    updateMD();
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
    //	item->editor = 0;
}


void dEditCfg::setData( aListViewItem *o )
{
//	int n;
//	char to[100]="";
//	cfg_objptr code, remark, context=NULL;
//	char	*id0;
            item = o;
            aCfg *md = item->md;
	aCfgItem obj = item->obj;

	QString v;
//	int rc=0;

	setCaption( tr("Business scheme parameters: ") + md->info( md_info_name ) );
	v = md->rc.value("dbtype");
	eDBType->setCurrentItem(0);
	if ( v == "postgres" ) eDBType->setCurrentItem(2);
	if ( v == "mysql" ) eDBType->setCurrentItem(1);

	eCfgName->setText( md->rc.value("configfile") );
	eWorkDir->setText( md->rc.value("workdir") );
	eDBHost->setText( md->rc.value("dbhost") );
	eDBName->setText( md->rc.value("dbname") );
	eDBHeader->setText( md->rc.value("dbtitle") );
	eDBPass->setText( md->rc.value("dbpass") );
	eDBUserName->setText( md->rc.value("dbuser") );
	eName->setText( md->info( md_info_name ) );
	eAuthor->setText( md->info( md_info_author ) );
	eDate->setText( md->info( md_info_date ) );
	eDescription->setText( md->info( md_info_remark ) );
	globals = md->find( obj, md_globals, 0 );
	eModule->setText( md->sText( globals, md_sourcecode ) );
	
/*
	n=cfgobj_count(context, aot_remark);
	if (n) {
		id0=cfgobj_idn(context, aot_remark, 1, &remark);
		if (remark) eRemark->setText(trUtf8(cfgobj_text(remark)));
	}
	n=cfgobj_count(context, aot_sourcecode);
	if (n) {
		id0=cfgobj_idn(context, aot_sourcecode, 1, &code);
		if (code) eModule->setText(trUtf8(cfgobj_text(code)));
	}
*/	
}



void dEditCfg::updateMD()
{
//	int n;
//	char to[100]="";
//	cfg_objptr code, remark, context=NULL;
//	char	*id;
//	cfg_objptr o;
	aCfg *md = item->md;
	aCfgItem obj = item->obj;

	md->setInfo( md_info_name, eName->text() );
	md->setInfo( md_info_remark, eDescription->text() );
	md->setInfo( md_info_author, eAuthor->text() );
	md->setInfo( md_info_date, eDate->text() );
	md->rc.setValue( "configfile", eCfgName->text().stripWhiteSpace() );
	md->rc.setValue( "workdir", eWorkDir->text().stripWhiteSpace() );
	md->rc.setValue( "dbhost", eDBHost->text().stripWhiteSpace() );
	md->rc.setValue( "dbtitle", eDBHeader->text().stripWhiteSpace() );
	md->rc.setValue( "dbname", eDBName->text().stripWhiteSpace() );
	md->rc.setValue( "dbpass", eDBPass->text().stripWhiteSpace() );
	md->rc.setValue( "dbuser", eDBUserName->text().stripWhiteSpace() );
	if (eDBType->currentItem()==1) md->rc.setValue( "dbtype", "mysql" );
	if (eDBType->currentItem()==2) md->rc.setValue( "dbtype", "postgres" );
	globals = md->find( obj, md_globals, 0 );
	md->setSText( globals, md_sourcecode, eModule->text() );
	
/*	
	if (cancelupdate) return;
	item->setText(0, eName->text());
//	item->setText(1, eID->text());
//	item->setText(2, eType->text());
//	o=cfgobj_find(eID->text());
//	if (o) {
//		printf("founded id=%s!\n", cfgobj_attr(o,"id"));
	cfg_setinfo("name", eName->text().utf8());
	n=cfgobj_count(context, aot_remark);
	if (!n) remark=cfgobj_new(context, aot_remark, trUtf8("Комментарий"), NULL);
	else id=cfgobj_idn(context, aot_remark, 1, &remark);
	if (remark) cfgobj_settext(remark, eRemark->text().utf8());
	n=cfgobj_count(context, aot_sourcecode);
	if (!n) code=cfgobj_new(context, aot_sourcecode, trUtf8("Глобальный модуль"), NULL);
	else id=cfgobj_idn(context, aot_sourcecode, 1, &code);
	if (code) cfgobj_settext(code, eModule->text().utf8());

*/	
}


/**
 * \ru
 *	\brief Сдвигает окно редактирования свойств в левый верхний угол родительского окна.
 * 
 * 	Размеры перемещаемого окна остаются без изменений.
 * \_ru
 */
void
dEditCfg::moveToTopLeftCorner()
{
	this->parentWidget()->setGeometry( 0, 0, 
		this->parentWidget()->frameSize().width(),
		this->parentWidget()->frameSize().height());

}
