/****************************************************************************
** $Id: dselectuser.ui.h,v 1.2 2005/06/23 14:59:40 gr Exp $
**
** Code file of the add user window
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
dSelectUser::setData( aRole *i )
{
 Q_ULLONG id = i->sysValue("id").toULongLong();
 listBox1->clear();
 listId.clear();
 role = i;
 aUser *user = new aUser(i->db);
 user->Select();
 if(user->First())
 {
  do
  {
   if(!user->hasRole(id))
   {
    listBox1->insertItem(user->sysValue("login").toString());
    listId.append(user->sysValue("id").toString());
   }
  }while(user->Next());
 }

 
}


Q_ULLONG
dSelectUser::getData( )
{
    return userId;
}


void dSelectUser::onSelect()
{
 if(listBox1->currentItem()!=-1)
 {
  printf("add user\n");
 
  //emit( addRole(listId[listBox1->currentItem()].toULongLong()) );
  userId =  listId[listBox1->currentItem()].toULongLong();
printf("addUser()\n");
  role->addUser(userId);
  printf("user added\n");
  listBox1->removeItem(listBox1->currentItem());
  accept();
 // new aListViewItem(p_item,
 }
 else
 {
  printf("not selected\n");
 }
}
