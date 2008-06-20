/****************************************************************************
** $Id: deditlang.ui.h,v 1.14 2004/12/23 14:37:55 gr Exp $
**
** Code file of the Edit Language window
** of Ananas Designer applications
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
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include "acfg.h"
#include <qstatusbar.h>
#include <qmessagebox.h>

extern aCfg cfg;

void dEditLang::setData( CfgForm *c, aCfgItem o )
{
//    aCfgItem alias;
//    int i, n, count;
    
    cf = c;
    obj = o;

    setCaption( tr("Language:") + cf->cfg.attr( obj, mda_name ) );
    eTag->setText( cf->cfg.attr( obj, mda_tag ) );
    eName->setText( cf->cfg.attr( obj, mda_name ) );
    eTrFile->setText( cf->cfg.attr( obj, mda_trfile ) );
}

void dEditLang::init()
{
    delete statusBar();
}

void dEditLang::destroy()
{
    updateMD();
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
}
void
dEditLang::updateMD()
{
    cf->cfg.setAttr( obj, mda_tag, eTag->text() );
    cf->cfg.setAttr( obj, mda_name, eName->text().stripWhiteSpace() );
    cf->cfg.setAttr( obj, mda_trfile, eTrFile->text() );
    cf->initLang();
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
}
    
