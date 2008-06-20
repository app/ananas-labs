/****************************************************************************
** $Id: pixmappreview.h,v 1.4 2004/07/01 11:30:54 pashik Exp $
**
** Ffile of the Pixmap preview of Ananas Designer applications
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

#ifndef PIXMAPPREVIEW_H
#define PIXMAPPREVIEW_H

#include <qlabel.h>
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qinputdialog.h>

class PixmapPreview : public QLabel, public QFilePreview
{
    Q_OBJECT
public:
    PixmapPreview( QWidget *parent=0 ) : QLabel( parent ) {}
    void previewUrl( const QUrl &u )
    {
	QString path = u.path();
	QPixmap pix( path );
	if ( pix.isNull() ) setText( tr("This is not a pixmap") );
	else setPixmap( pix );
    }
};

#endif
