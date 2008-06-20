/****************************************************************************
** $Id: itemplate.h,v 1.8 2007/08/04 14:29:02 app Exp $
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

#ifndef ITEMPLATE_H
#define ITEMPLATE_H

#include "ananasglobal.h"

#include <qobject.h>
//#include <qdict.h>
//#include <qstringlist.h>

/**
 * \en
 * 		Interface for work with report
 * \_en \ru
 * 	
 * \brief Интерфейс для работы с отчетами. Наследует QObject.
 *
 * Классы, генерирующие отчеты, должны использовать этот интерфейс. 
 * Содержит чистые виртуальные функции, не допускается создание объектов этого класса напрямую.
 * Пример:
 * \code
 *  iTemplate *tpl = new aTemplate(); // aTemplate должен реализовывать интерфейс iTemplate
 *  tpl->open("test.tpl");
 *  tpl->close();
 *  delete tpl;
 * \endcode
 * \_ru
 */
class  ANANAS_EXPORT iTemplate : public QObject
{
    Q_OBJECT
public:
    iTemplate();
    virtual ~iTemplate();
   
    virtual bool    open( const QString &fname )=0;
    virtual void    close();
    virtual void    clear();
    virtual QString getValue( const QString &name );
    virtual void    setValue( const QString &name, const QString &value );
    virtual QString exec( const QString &sname );
    virtual QString result();
    virtual bool    save( const QString & fname );
    virtual void    cleanUpTags();    
    virtual void    setDir(const QString &dir);
    virtual QString getDir();
};

#endif //ITEMPLATE_H
