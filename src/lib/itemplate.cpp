/****************************************************************************
** $Id: itemplate.cpp,v 1.6 2007/08/04 14:29:02 app Exp $
**
** Report metadata object header file of 
** Ananas application library
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2005 Grigory Panov, Yoshkar-Ola.
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

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <stdlib.h>
//#include <qfile.h>

#include "itemplate.h"


/**
 * \en
 * 		Constructor
 * \_en
 * \ru
 * 		Конструктор.
 * \_ru
 */
iTemplate::iTemplate()
    : QObject()
{
}

/** 
 * \en
 * 		Destructor
 * \_en
 * \ru
 * 		Деструктор
 * \_ru
 */
iTemplate::~iTemplate()
{
}

/** 
 * \en
 * 		Opens pattern
 * \_en
 * \ru
 * 		Открывает шаблон.
 * \_ru
 */
bool
iTemplate::open( const QString &)
{
	return true;
}

/**
 * \en
 * 		Closes pattern.
 * \_en
 * \ru
 * 		Закрывает шаблон.
 * \_ru
 */
void 
iTemplate::close()
{
}

/**
 * \en
 * 		Get value of parameter `name'
 * \_en
 * \ru
 * 		Возвращает значение параметра по его имени.
 * \_ru
 */
QString 
iTemplate::getValue( const QString & )
{
	return "";
}


/**
 * \en
 * 		Set value of parameter `name'
 * \_en
 * \ru
 * 		Устанавливает значение параметра по его имени.
 * \_ru
 */
void
iTemplate::setValue( const QString &, const QString & )
{
}

    
/**
 * \en
 * 		Saves document to file
 * \_en
 * \ru
 * 		\brief Сохраняет документ в файл с заданным именем.
 * \_ru
 */
bool
iTemplate::save( const QString & )
{
	return true;
}


/**
 * \en
 * 		Replaces tads to values
 * \_en
 * \ru
 * 		Выполняет подстановку значения параметра в шаблоне. 
 * 		Может вызываться несколько раз.
 * \_ru
 */
QString
iTemplate::exec( const QString & )
{
	return "";
}

/**
 * \en
 * 		Clears internal variable.
 * \_en
 * \ru
 * 		Обнуляет внутренние переменные.
 * \_ru
 */
void 
iTemplate::clear()
{
}

/**
 * \en
 * 		Returns document.
 * \_en
 * \ru
 * 		Возвращает результат, т.е. шаблон в текстовом виде. Включена в интерфейс временно.
 * \_ru
 */
QString 
iTemplate::result()
{
	return "";
}

/**
 * \en 
 * 		Clears all tags
 * \_en
 * \ru
 * 		Очищает все теги
 * \_ru
 */
void
iTemplate::cleanUpTags()
{
}

/**
 * \en 
 * 		Sets  working directory
 * \_en
 * \ru
 * 		Устанавливает рабочую директорию
 * \_ru
 */    
void
iTemplate::setDir(const QString &)
{
}

/**
* \en 
* 		Gets  working directory
* \_en
* \ru
* 		Возвращает рабочую директорию
* \_ru
*/    
QString
iTemplate::getDir()
{
	return "";
}
