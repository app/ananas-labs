/****************************************************************************
** $Id: aextensionfactory.h,v 1.3 2006/08/23 07:53:03 app Exp $
**
** ...
**
** Created : 20060209
**
** Copyright (C) 2003-2006 Leader InfoTech.  All rights reserved.
**
** This file is part of the Library of the Ananas
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

#ifndef AEXTENSIONFACTORY_H
#define AEXTENSIONFACTORY_H

#ifndef QT_H
#include "qstringlist.h"
#endif // QT_H

class QString;
class AExtension;

/*!
 * \en
 *   \brief The AExtensionFactory class creates AExtension objects.
 *
 *   The style factory creates a AExtension object for a given key with
 *   AExtensionFactory::create(key).
 *
 *   The styles are either built-in or dynamically loaded from a style
 *   plugin (see \l AExtensionPlugin).
 *
 *   AExtensionFactory::keys() returns a list of valid keys, typically
 *   including "XXXX".
 * \_en
 * \ru
 * 	\brief Опеределяет интерфейс для создания объектов класса AExtension
 *
 *
 * \_ru
 */

class ANANAS_EXPORT AExtensionFactory
{
public:
#ifndef QT_NO_STRINGLIST
    static QStringList keys();
#endif
    static AExtension *create( const QString& );
};

#endif //AEXTENSIONFACTORY_H
