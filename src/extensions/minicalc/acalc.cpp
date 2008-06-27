/****************************************************************************
** $Id$
**
** Source file of Ananas project
* 
** Copyright (C) 2008 Andrey Paskal.
**
** This file is part of the extention of the Ananas
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
**********************************************************************/


#include "acalc.h"

/**
 *\en
 *	\brief 
 * 
 *\_en
 *\ru
 *	\brief Создает экземпляр диалога
 * 	\see aCalc::Show()
 * 
 *\_ru
 */
aCalc::aCalc(): AExtension("Calc")
{
	calcInstance = new MiniCalc();
}

/**
 *\en
 *	\brief Destructor
 *\_en
 *\ru
 *	\brief Деструктор
 *\_ru
 */
aCalc::~aCalc()
{
	if (calcInstance) {
		delete calcInstance;
		calcInstance = 0;
	}
}


/**
 *\en
 *	\brief 
 *\_en
 *\ru
 *	\brief Открывает окно калькулятора перед пользователем на экране.
 *\_ru
 */
void
aCalc::Show()
{
	if ( calcInstance ) 
	{
		calcInstance->show();
	}
}


#include <aextensionplugin.h>
typedef AExtensionPlugin<aCalc> aCalcPlugin;
A_EXPORT_PLUGIN( aCalcPlugin )
