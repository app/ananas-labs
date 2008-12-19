/****************************************************************************
** $Id: aext_meta.h,v 1.6 2008/12/19 12:21:20 app Exp $
**
** Extension object header file of
** Ananas application library
**
** Created : 20031201
**
** Copyright (C) 2006 Andrey Paskal
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

#ifndef AEXT_META_H
#define AEXT_META_H



#include "aextension.h"
#include "acfg.h"
#include "aobject.h"

class aObject;

/**
 * \en
 * 	Class for work with meta data API from Ananas Script.
 * \_en
 * \ru
 * 	\brief Предоставляет доступ к интервейсу метаданных из Ананас скрипта.
 *
 * 	Пример использования функций GetBaseClassName, GetClassName, GetBaseClassNameByObjectUid, 
 * 	GetClassNameByObjectUid
 * \code
 * 	meta = new Meta();
 * 	sys.Message(0,"class id = 129, base class name ="+meta.GetBaseClassName(129));
 * 	sys.Message(0,"class id =129, class name ="+meta.GetClassName(129));
 * 	sys.Message(0,"uid=6, base class name ="+meta.GetBaseClassNameByObjectUid(6));
 * 	sys.Message(0,"uid=6, class name ="+meta.GetClassNameByObjectUid(6));
 * \endcode
 *
 * \_ru
 */
class  ANANAS_EXPORT AExtMeta : public AExtension
{
    Q_OBJECT

public:

    AExtMeta();
    ~AExtMeta();
public:

public slots:
	QString		GetBaseClassName(const long &ClassId);
	QString		GetClassName(const long &ClassId);
	QString		GetBaseClassNameByObjectUid(const long &ObjectUid);
	QString		GetClassNameByObjectUid(const long &ObjectUid);
	int			CountByClassName(const QString &className);
	QStringList	DataTypes(const QString &className = NULL);
	QString		StringOfDataTypes(const QString &className = NULL, const QString &separator = ":");
	int		GetId( QString& name );
	int		GetId( aObject * obj );
	QStringList GetUserFields( QString name, QString table = QString::null );	
	QStringList GetUserFields( aObject * obj, QString table = QString::null );
	QString	GetAttrType(QString name, QString attr, QString table = QString::null);
	QString	GetAttrType(aObject *obj, QString attr, QString table = QString::null);
};


#endif //AEXT_META_H
