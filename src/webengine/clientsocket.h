/****************************************************************************
** $Id: clientsocket.h,v 1.1 2004/09/23 13:51:11 leader Exp $
**
** Header file of the client socket file of Ananas
** Web Engine application
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

#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <qsocket.h>

class ClientSocket : public QSocket
{
	Q_OBJECT
public:
	ClientSocket( QObject* parent = 0, const char *name = 0  );
};

#endif
