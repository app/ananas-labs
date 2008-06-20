/****************************************************************************
** $Id: addfdialog.ui.h,v 1.9 2006/04/04 12:49:39 gr Exp $
**
** Code file of the select files plugin of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2004 Grigory Panov, Yoshkar-Ola.
**
** This file is part of the Ananas Plugins of the Ananas
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
/*!
 * Sets current field name and field id for return with function getData()
 */

void addfdialog::doOk()
{
	int idx; 
	idx = ListBox->currentItem();
	if(idx>=0)
	{
	        id = idlist[idx];
		field = list[idx];
	}
	else id="0";
	accept();
}


void addfdialog::init()
{
	id="0";
	field="";
}


void addfdialog::destroy()
{
 
}


/*!
 * Function return field name (if param name == true) or field id otherwise
 * \return field name or field id
 */
const QString addfdialog::getData(bool name)
{
	if(name) return field;
	else return id;
}

/*!
 * Sets list of field name and list of field id.
 * \param flst (in) - list of field name
 * \param ilst (in) - list of field id
 */
void addfdialog::setData( QStringList displst, QStringList flst, QStringList ilds)
{
	list = flst;
	ListBox->insertStringList(displst);
	idlist = ilds;
}




void addfdialog::setData( QWidget *o, aCfg *md )
{
	
	wDBField *w = (wDBField *)o;
	w->getFields();
	setData( w->defDisplayFields, w->defFields,w->defId);
	ListBox->setCurrentItem(ListBox->findItem(w->getFieldName()));
}


void addfdialog::getData( QWidget *o )
{
	QString s;
	wDBField *w = (wDBField *)o;
	QValueList<Q_ULLONG> bindList = w->getBindList();
		s = getData(true);
		if(s.isEmpty()) return;
		w->setFieldName(s);
		s = getData(false);
		if(s=="0") return;
		// if select binding field
		if(bindList.find(s.toULongLong()) != bindList.end())
		{
			cfg_message(0, tr("field already binding, please select another field."));
			return;
		}
		w->setId(s.toInt());
		w->setEditorType();
    		//w->updateProp();

}
