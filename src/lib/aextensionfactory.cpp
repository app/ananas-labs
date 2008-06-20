/****************************************************************************
** $Id: aextensionfactory.cpp,v 1.6 2007/09/18 10:24:09 app Exp $
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

#include "aextensioninterface_p.h" // up here for GCC 2.7.* compatibility
#include "aextensionfactory.h"
#include <aextension.h>
#include "binreloc.h"
#include "alog.h"


#include <stdlib.h>
#include <private/qpluginmanager_p.h>
#ifndef QT_NO_COMPONENT
#include <qapplication.h>
#include <qobject.h>

class AExtensionFactoryPrivate : public QObject
{
public:
    AExtensionFactoryPrivate();
    ~AExtensionFactoryPrivate();

    static QPluginManager<AExtensionFactoryInterface> *manager;
};

static AExtensionFactoryPrivate *instance = 0;
QPluginManager<AExtensionFactoryInterface> *AExtensionFactoryPrivate::manager = 0;

AExtensionFactoryPrivate::AExtensionFactoryPrivate()
: QObject( qApp )
{
#ifdef Q_OS_WIN32
    manager = new QPluginManager<AExtensionFactoryInterface>( IID_AExtensionFactory, QApplication::libraryPaths(), "/extensions", FALSE );
#else
	BrInitError error; 
	if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED) { 
		aLog::print(aLog::MT_INFO, tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
		aLog::print(aLog::MT_INFO, tr("Will fallback to hardcoded default path.\n"));
	} 
	aLog::print(aLog::MT_DEBUG, tr("BinReloc path to library dir is '%1'\n").arg( br_find_lib_dir("/usr/lib") ));
    manager = new QPluginManager<AExtensionFactoryInterface>( IID_AExtensionFactory, QString(br_find_lib_dir("/usr/lib"))+QString("/ananas"), QString::null, FALSE );
#endif
    
}

AExtensionFactoryPrivate::~AExtensionFactoryPrivate()
{
    delete manager;
    manager = 0;

    instance = 0;
}

#endif //QT_NO_COMPONENT

/*!
    Creates a AExtension object that matches \a key. This is either a
    built-in extensions, or a extension from a extension plugin.

    \sa keys()
*/
AExtension *AExtensionFactory::create( const QString& key )
{
    AExtension *ret = 0;
    QString extension = key; //key.lower();
#ifndef A_NO_EXTENSION_XXXX
    if ( extension == "XXXX" )
        ret = new AExtension(extension);
#endif

    { } // Keep these here - they make the #ifdefery above work

#ifndef QT_NO_COMPONENT
    if(!ret) {
	if ( !instance )
	    instance = new AExtensionFactoryPrivate;

	QInterfacePtr<AExtensionFactoryInterface> iface;
	AExtensionFactoryPrivate::manager->queryInterface( extension, &iface );

	if ( iface )
	    ret = iface->create( extension );
    }
    if(ret)
	ret->setName(key);
#endif
    return ret;
}

#ifndef QT_NO_STRINGLIST
/*!
    Returns the list of keys this factory can create styles for.

    \sa create()
*/
QStringList AExtensionFactory::keys()
{
    QStringList list;
#ifndef QT_NO_COMPONENT
    if ( !instance )
	instance = new AExtensionFactoryPrivate;

    list = AExtensionFactoryPrivate::manager->featureList();
#endif //QT_NO_COMPONENT

#ifndef A_NO_EXTENSION_XXXX
    if ( !list.contains( "XXXX" ) )
	list << "XXXX";
#endif

    return list;
}
#endif
