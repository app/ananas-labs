/****************************************************************************
** $Id: awindowslist.cpp,v 1.1 2005/05/18 19:14:29 leader Exp $
**
** Main window of Ananas Designer applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Designer application  of the Ananas
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

#include "awindowslist.h"
#include "acfg.h"

aWindowsList::aWindowsList()
    : QWidget()
{
}


aWindowsList::~aWindowsList()
{
}

void
aWindowsList::insert( int id, QWidget *window, Q_ULLONG ido )
{
    list.insert( conv( id, ido ), window );
}

void
aWindowsList::remove( int id, Q_ULLONG ido )
{
    list.remove( conv( id, ido ) );
}

void
aWindowsList::remove( QWidget *window )
{
    QDictIterator<QWidget> it( list );
    for ( ; it.current(); ++it ) 
    {
	if ( it.current() == window ) {
	    list.remove( it.currentKey() );
	    break;
	}
    }
}

bool
aWindowsList::find( int id, Q_ULLONG ido )
{
    if ( !list.find( conv( id, ido ) ) ) return FALSE;
    return TRUE;
}

bool
aWindowsList::find( QWidget *window )
{
    QDictIterator<QWidget> it( list );
    for ( ; it.current(); ++it ) if ( it.current() == window ) return TRUE;
    return FALSE;
}

QWidget *
aWindowsList::get( int id, Q_ULLONG ido )
{
    return list.find( conv( id, ido ) );
}
	

QString
aWindowsList::conv( int id, Q_ULLONG ido )
{
    return QString("%1_%2").arg( id, ido );
}
	
