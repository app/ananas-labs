/****************************************************************************
** $Id: deditpermissions.ui.h,v 1.2 2008/10/25 21:41:49 leader Exp $
**
** Code file of the edit permission window
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
#include "adatabase.h"

void dEditPermissions::setData( int pm )
{
    int r,i;
    r = 1;
    QCheckBox *c;
    for (i=1;i<=7;i++)
    {
	c = (QCheckBox*) child( (const char*) QString("checkBox%1").arg(i),"QCheckBox");
	if ( c ) {
	  c->setChecked( (pm & r ) !=0 );  
	}
	r = r << 1;
    }
}


int dEditPermissions::getData()
{
    int r,i, res=0;
    r = 1;
    QCheckBox *c;
    for (i=1;i<=7;i++)
    {
	c = (QCheckBox*) child( (const char*) QString("checkBox%1").arg(i),"QCheckBox");
	if ( c ) {
	  if (c->isChecked()) res |= r;  
	}
	r = r << 1;
    }
    return res;
}


void dEditPermissions::setAll( bool v )
{
    int i;
    QCheckBox *c;
    for (i=1;i<=7;i++)
    {
	c = (QCheckBox*) child( (const char*) QString("checkBox%1").arg(i),"QCheckBox");
	if ( c ) c->setChecked( v );  
    }

}
