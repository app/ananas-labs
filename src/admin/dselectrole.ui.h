/****************************************************************************
** $Id: dselectrole.ui.h,v 1.3 2008/10/25 21:41:49 leader Exp $
**
** Code file of the add role window
** Ananas administrator application 
**
** Created : 20050610
**
** Copyright (C) 2003-2005 Grigory Panov <gr1313 at mail dot ru>, Yoshkar-Ola.
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
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

void
dSelectRole::setData( aUser *user )
{
 usr = user;
 listBox1->clear();
 listId.clear();

 QValueList<aRole*> list = user->getRoles(false);
 QValueList<aRole*>::iterator it;
 for ( it = list.begin(); it != list.end(); ++it )
 {
  listBox1->insertItem( (*it)->sysValue("name").toString() );
  listId.append((*it)->sysValue("id").toString());
  delete (*it);
 }
// delete list;
}


void
dSelectRole::onSelect()
{
 if(listBox1->currentItem()!=-1)
 {
  printf("add role\n");
 
  //emit( addRole(listId[listBox1->currentItem()].toULongLong()) );
  roleId =  listId[listBox1->currentItem()].toULongLong();
   usr->addRole(roleId);
  listBox1->removeItem(listBox1->currentItem());
  accept();
 // new aListViewItem(p_item,
 }
 else
 {
  printf("not selected\n");
 }
}


Q_ULLONG dSelectRole::getData()
{
    return roleId;
}
