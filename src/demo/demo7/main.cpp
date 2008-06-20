/****************************************************************************
** $Id: main.cpp,v 1.8 2005/07/21 10:48:55 app Exp $
**
** Main file of the Ananas Demo7 of Ananas
** Demo collection
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
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
 * Function for work with ananas database
 * Author: cibfx
 * 28.06.2006 Example for work with information registers
 * Use demo1&demo2 for create configuration&database
*/

#include "atemplate.h"
#include "aootemplate.h"
#include "itemplate.h"

#define DEMOVER "Demo 7. Report template demo."
#define VERSION "0.1.1"


void test(iTemplate *tpl, const QString &fname, const QString &fres )
{ 
    tpl->setDir("templates");
    if(	!tpl->open( fname ) )
    {
	    printf("error open!!!!!!!\n");
	    return;
    }
	printf("open `%s' ok\n",fname.ascii());
    //tpl->clear();
    tpl->setValue( "param", "*my params value*" );
    tpl->exec( "first" );
    tpl->setValue( "param", "*value for section 2*" );
    tpl->exec( "second" );
    tpl->exec( "second" );
    tpl->setValue("field1","*field 1 value*");
    tpl->setValue("field 2","*field 2 value*");
    
    tpl->exec( "table_section" );
    tpl->exec( "table_section" );
//    printf("result = %s\n", ( const char * ) tpl->result().local8Bit() );
    tpl->cleanUpTags();
    printf("begin save\n");
    if(!tpl->save( fres ))
    {
	    printf("error save !!!!!!!!!\n");
    }
    tpl->close();
}

int main(int argc, char **argv)
{

    iTemplate *tpl = new aTemplate();
    test(tpl, "demo7.tpl", "test.txt" );
    delete tpl;
    tpl = new aOOTemplate();
    test(tpl, "demo7.sxw", "test7.sxw" );
    delete tpl;
    return 0;
}
