/****************************************************************************
** $Id: actiontree.h,v 1.9 2005/07/04 09:20:34 red75 Exp $
**
** Header file of the Action Tree of Ananas Designer applications
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

#ifndef ACTIONTREE_H
#define ACTIONTREE_H
#include <qlistview.h>
#include <qintdict.h>
//#include "acfg.h"
#include "atreeitems.h"

class QWidget;

class ActionListViewItem : public ananasListViewItem
{
public:
/*	int id;
	aCfgItem obj;
	QWidget *editor;
	aCfg *md;
*/
	ActionListViewItem( QListView *parent, aCfg * cfgmd, aCfgItem cfgobj, const QString &name = QString::null );
	ActionListViewItem( ananasListViewItem *parent, ananasListViewItem *after, aCfg * cfgmd, aCfgItem cfgobj,
						const QString &name = QString::null );
	void loadTree();
	void loadGroup ( ananasListViewItem * parent, aCfgItem child );
	void newActionGroup ();
	void newAction ();
	void edit ();
};

class aActionTreeView : public ananasTreeView
{
    Q_OBJECT
public:

	aActionTreeView( QWidget *parent, aCfg *cfgmd );

public slots:
	void ContextMenu();
	void itemNewGroup();
	void itemNewAction();
	void itemMoveUp();
	void itemMoveDown();
	void itemDelete();
	void itemEdit();
	void itemRename();

};
#endif //ACTIONTREE_H
