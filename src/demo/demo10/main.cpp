/****************************************************************************
** $Id: main.cpp,v 1.1 2006/07/10 06:47:36 gr Exp $
**
** Main file of the Ananas Demo10 of Ananas
** Test summa propis
**
** Created : 20051017
**
** Copyrigth (C) 2003-2006. Ananas Group.
** Copyright (C) 2003-2006. Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola
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


#include "ananas.h"
#include <qapplication.h>
#include <qtextcodec.h> 

#define DEMOVER "Demo 10. Test summa propis"
#define VERSION "0.1.1"



int main(int argc, char **argv)
{


	QApplication application(argc,argv,false);	
	QTextCodec::setCodecForCStrings( QTextCodec::codecForName("UTF8") );
	printf("22405 %s: %s\n", (const char*) QString("рублей").local8Bit(),
				 (const char*) aService::number2money(22405).local8Bit());
	printf("22401 %s: %s\n", (const char*) QString("рубль").local8Bit(),
				 (const char*) aService::number2money(22401).local8Bit());
	printf("22405 %s: %s\n", (const char*) QString("гривен").local8Bit(),			 
				 (const char*) aService::number2money(22405,true,false,"гривен","гривна","гривны").local8Bit());
	printf("22401 %s: %s\n", (const char*) QString("гривна").local8Bit(),
				 (const char*) aService::number2money(22401,false,false,"гривен","гривна","гривны").local8Bit());
	printf("22405 %s: %s\n",  (const char*) QString("штук").local8Bit(),
				  (const char*) aService::number2money(2405,false,false,"штук","штука","штуки").local8Bit());
	printf("22401 %s: %s\n", (const char*) QString("штука").local8Bit(),
				 (const char*) aService::number2money(2401,false,false,"штук","штука","штуки").local8Bit());
	application.exit();	
	return 0;
}
