/****************************************************************************
** $Id: dedituser.ui.h,v 1.2 2005/06/23 15:04:50 gr Exp $
**
** Code file of the edit user window
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


bool 
dEditUser::check( const QString &login )
{
    if(usr->sysValue("login").toString()==login)
    {
  return false; 
     }
    return true;
}


aUser * dEditUser::getData()
{
    return usr;
  
}


void dEditUser::setData( aUser *user, bool isNew )
{
    usr = user;
    newUser = isNew;
    //usr->Select();
    if(!isNew)
    {
 lineEdit1->setText(usr->sysValue("login").toString());
 lineEdit2->setText(usr->sysValue("password").toString());
 lineEdit3->setText(usr->sysValue("fname").toString());
 lineEdit4->setText(usr->sysValue("lname").toString());
}
}


void dEditUser::onOk()
{
    if(check(lineEdit1->text()))
    {
 if(newUser)
 {
    usr->New(lineEdit1->text(), lineEdit2->text(),lineEdit3->text(),lineEdit4->text());
 }
 else
 {
 usr->setSysValue("login",lineEdit1->text());
 usr->setSysValue("password",lineEdit2->text());
  usr->setSysValue("fname",lineEdit3->text());
  usr->setSysValue("lname",lineEdit4->text());
  usr->Update();
}
 this->accept();
   }
}
