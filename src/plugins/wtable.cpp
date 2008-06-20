/****************************************************************************
** $Id: wtable.cpp,v 1.20 2006/06/17 06:19:46 gr Exp $
**
** Code file of the table plugin of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2006 Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola.
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

#include <qtable.h>
#include <qlayout.h>
#include <qstring.h>
#include <qheader.h>
#include <qvariant.h>
#include <qobject.h>
#include <qobjectlist.h>

#include "acfg.h"
#include "aobject.h"
#include "awidget.h"
#include "wtable.h"



wTable::wTable(QWidget *parent, const char * name):QTable(parent, name)
{

}

wTable::~wTable()
{
}


void
wTable::setDocument(int row, aObject *object)
{
}

void
wTable::setText(int row, int col, const QString& text)
{
	return QTable::setText(row, col,text);
}


QString
wTable::text(int col, int row)
{
	return QTable::text(col,row);
}

void
wTable::setHeaderText(int col, const QString& text)
{
	QTable::horizontalHeader()->setLabel( col, text );
}


QString 
wTable::textHeader(int col)
{
	return QTable::horizontalHeader()->label(col);
}
		
void
wTable::sortColumn ( int col, bool ascending, bool wholeRows )
{
	printf("do sort column\n");
	QTable::sortColumn( col, ascending, true );
}


void
wTable::setColumnWidth(int col, int width)
{
	QTable::setColumnWidth(col,width);
}


int
wTable::columnWidth(int col)
{
	return QTable::columnWidth(col);
}

void
wTable::setNumCols ( int r )
{
	QTable::setNumCols(r);
}

int
wTable::numCols () const 
{
	int res = QTable::numCols();// - 1;
	return res;
}
void
wTable::hideColumn ( int col )
{
	QTable::hideColumn ( col );
}

void
wTable::showColumn ( int col )
{
	QTable::showColumn ( col );
}
/*
bool 
wTable::isColumnHidden ( int col ) const
{
//	int i = -2;
//	if(col>=0) i=col;
	return QTable::isColumnHidden ( col );
}
*/
void 
wTable::adjustColumn ( int col )
{
	return QTable::adjustColumn  ( col );
}

void
wTable::setColumnStretchable ( int col, bool stretch )
{
	return QTable::setColumnStretchable ( col, stretch );
}

bool
wTable::isColumnStretchable ( int col ) const
{
	return QTable::isColumnStretchable ( col );
}


void 
wTable::swapColumns ( int col1, int col2, bool swapHeader )
{
	QTable::swapColumns( col1, col2, swapHeader );
	
}

void
wTable::swapCells ( int row1, int col1, int row2, int col2 )
{
	QTable::swapCells( row1, col1, row2, col2 );
}

void
wTable::setCurrentCell ( int row, int col )
{
	QTable::setCurrentCell( row, col );
}

void 
wTable::setColumnReadOnly ( int col, bool ro )
{
	QTable::setColumnReadOnly( col, ro );
}

void 
wTable::insertColumns ( int col, int count )
{
	QTable::insertColumns( col, count );
}

void
wTable::removeColumn ( int col )
{
	QTable::removeColumn( col );
}

void
wTable::editCell ( int row, int col, bool replace )
{
	QTable::editCell( row, col, replace );
}

void 
wTable::columnClicked ( int col )
{
//	int i = -2;
//	if(col>=0) i=col;
	QTable::columnClicked ( col );//i-1 ); 
}
void
wTable::swapRows ( int row1, int row2, bool swapHeader )
{
	QTable::swapRows (  row1, row2,swapHeader ); 
}


	
