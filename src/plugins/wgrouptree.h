/****************************************************************************
** $Id: wgrouptree.h,v 1.9 2008/04/12 18:05:35 app Exp $
**
** Header file of the document plugin of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Ananas Plugins of the Ananas
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

#ifndef WGROUPTREE_H
#define WGROUPTREE_H

#include <qlistview.h>
#include <qwidgetplugin.h>
#include <qwidget.h>
#include "awidget.h"

class wGroupTreeItem;
class wTreeView;

class QT_WIDGET_PLUGIN_EXPORT wGroupTree : public aWidget
{
    Q_OBJECT
public:
	wTreeView *tree;
	wGroupTreeItem *root;

	wGroupTree( QWidget *parent = 0, WFlags fl = 0 );
	virtual ~wGroupTree();

	virtual void initObject( aDatabase *adb );
	virtual QDialog* createEditor( QWidget *parent );
	virtual QToolBar*	createToolBar( QMainWindow *parent );
	virtual aObject *createDBObject(  aCfgItem obj, aDatabase *adb );
	void buildGroupTree( aCfgItem obj, aCatGroup * cg1, wGroupTreeItem * wG );
	wGroupTreeItem *findItem( ANANAS_UID id );
public slots:
	void findGroupTree();
	void NewGroup();
	void DeleteGroup();
	void EditGroup();
	virtual QString	Uid() { return QString("%1").arg(currentId); };
//	void UpdateItem( aCatGroup *g );
private slots:
	void on_selected( ANANAS_UID element );
//	void updateItem( ANANAS_UID element );
	void updateItem( ANANAS_UID element );
	void on_selectionChanged( QListViewItem *);
	void dropped(QDropEvent*);
signals:
	virtual void selected( ANANAS_UID group );
	virtual void selectionChanged( const Q_ULLONG );
protected:
	virtual void keyPressEvent ( QKeyEvent *e );
private:
	Q_ULLONG currentId;
};



class wGroupTreeItem : public QListViewItem
{
public:
	ANANAS_UID id;
	int level;
	wGroupTreeItem( QListView *parent, const QString &name = QString::null );
	wGroupTreeItem( wGroupTreeItem *parent, wGroupTreeItem *after, const QString &name = QString::null, int newlevel = 0, ANANAS_UID newid = 0 );
	wGroupTreeItem( wGroupTreeItem *parent, wGroupTreeItem *after, aCatGroup *g = 0 );
	virtual ~wGroupTreeItem();
	wGroupTreeItem *parentItem();
private:
};

class wTreeView : public QListView
{
	Q_OBJECT
public:    
	wTreeView(QWidget * parent);
protected:
	virtual void dragEnterEvent(QDragEnterEvent *);    
	virtual void dragMoveEvent(QDragMoveEvent *);
	virtual void dropEvent(QDropEvent *);
};

#endif // WGROUPTREE_H
