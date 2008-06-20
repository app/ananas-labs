/****************************************************************************
** $Id: plugins.cpp,v 1.26 2006/10/28 13:17:07 app Exp $
**
** Code file of the Ananas plugins class
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

#include "plugins.h"
#include "wfield.h"
#include "wtable.h"
#include "wdbtable.h"
#include "wcatalogue.h"
#include "wdocument.h"
#include "wdbfield.h"
#include "wgrouptree.h"
#include "wjournal.h"
#include "wactionbutton.h"
#include "wreport.h"
#include "acombobox.h"

#define FA_FIELD 		"wField"
#define FA_DBFIELD 		"wDBField"
#define FA_TABLE 		"wTable" 
#define FA_DBTABLE 		"wDBTable"
#define FA_CATALOGUE 		"wCatalogue"
#define FA_GROUPTREE		"wGroupTree"
#define FA_DOCUMENT 		"wDocument"
#define FA_JOURNAL 		"wJournal"
#define FA_ACTIONBUTTON		"wActionButton"
#define FA_REPORT		"wReport"
#define FA_COMBOBOX		"AComboBox"

aPlugins::aPlugins()
{
}

QStringList
aPlugins::keys() const
{
    	QStringList list;
    	list << FA_FIELD;
    	list << FA_DBFIELD;
    	list << FA_TABLE;
    	list << FA_DBTABLE;
    	list << FA_CATALOGUE;
    	list << FA_DOCUMENT;
    	list << FA_JOURNAL;
	list << FA_GROUPTREE;
	list << FA_ACTIONBUTTON;
	list << FA_REPORT;
	list << FA_COMBOBOX;
    	return list;
}

QWidget*
aPlugins::create( const QString &key, QWidget* parent, const char* name )
{
    	if ( key == FA_FIELD ) return new wField( parent,"wField", 0 );
    	if ( key == FA_DBFIELD ) return new wDBField( parent, 0 );
    	if ( key == FA_TABLE ) return new wTable( parent, name );
    	if ( key == FA_DBTABLE ) return new wDBTable( "", parent, name );
    	if ( key == FA_CATALOGUE ) return new wCatalogue( parent, 0 );
    	if ( key == FA_DOCUMENT ) return new wDocument( parent, 0 );
    	if ( key == FA_JOURNAL ) return new wJournal( parent, 0 );
    	if ( key == FA_GROUPTREE ) return new wGroupTree( parent );
	if ( key == FA_ACTIONBUTTON ) return new wActionButton( parent );
    	if ( key == FA_REPORT ) return new wReport( parent, 0 );
    	if ( key == FA_COMBOBOX ) return new AComboBox( parent, name );
    	return 0;
}

QString
aPlugins::group( const QString& feature ) const
{
    	if ( feature == FA_FIELD ) return "Ananas";
    	if ( feature == FA_DBFIELD ) return "Ananas";
    	if ( feature == FA_TABLE ) return "Ananas";
    	if ( feature == FA_DBTABLE ) return "Ananas";
    	if ( feature == FA_CATALOGUE ) return "Ananas";
    	if ( feature == FA_DOCUMENT ) return "Ananas";
    	if ( feature == FA_JOURNAL ) return "Ananas";
    	if ( feature == FA_GROUPTREE ) return "Ananas";
	if ( feature == FA_ACTIONBUTTON ) return "Ananas";
	if ( feature == FA_REPORT ) return "Ananas";
	if ( feature == FA_COMBOBOX ) return "Ananas";
    	return QString::null;
}

QIconSet
aPlugins::iconSet( const QString& feature) const
{
	if ( feature == FA_FIELD ) return QIconSet( QPixmap::fromMimeSource( "wfield.png" ) );
    	if ( feature == FA_DBFIELD ) return QIconSet( QPixmap::fromMimeSource( "wdbfield.png" ) );
    	if ( feature == FA_TABLE ) return QIconSet( QPixmap::fromMimeSource( "wtable.png" ) ); 
    	if ( feature == FA_DBTABLE ) return QIconSet( QPixmap::fromMimeSource( "wdbtable.png" ) ); 
    	if ( feature == FA_CATALOGUE ) return QIconSet( QPixmap::fromMimeSource( "wcatalogue.png" ) );
    	if ( feature == FA_DOCUMENT ) return QIconSet( QPixmap::fromMimeSource( "wdocument.png" ) );
    	if ( feature == FA_JOURNAL ) return QIconSet( QPixmap::fromMimeSource( "wjournal.png" ) );
    	if ( feature == FA_GROUPTREE ) return QIconSet( QPixmap::fromMimeSource( "wgrouptree.png" ) );
    	if ( feature == FA_ACTIONBUTTON ) return QIconSet( QPixmap::fromMimeSource( "wactionbutton.png" ) );
    	if ( feature == FA_REPORT ) return QIconSet( QPixmap::fromMimeSource( "wreport.png" ) );
    	if ( feature == FA_COMBOBOX ) return QIconSet( QPixmap::fromMimeSource( "acombobox.png" ) );

	return QIconSet( QPixmap() );
}

QString
aPlugins::includeFile( const QString& feature ) const
{
    	if ( feature == FA_FIELD ) return "wfield.h";
    	if ( feature == FA_DBFIELD ) return "wdbfield.h";
    	if ( feature == FA_TABLE ) return "wtable.h";
    	if ( feature == FA_DBTABLE ) return "wdbtable.h";
    	if ( feature == FA_CATALOGUE ) return "wcatalogue.h";
    	if ( feature == FA_DOCUMENT ) return "wdocument.h";
    	if ( feature == FA_JOURNAL ) return "wjournal.h";
    	if ( feature == FA_GROUPTREE ) return "wgrouptree.h";
    	if ( feature == FA_ACTIONBUTTON ) return "wactionbutton.h";
    	if ( feature == FA_REPORT ) return "wreport.h";
    	if ( feature == FA_COMBOBOX ) return "acombobox.h";
    	return QString::null;
}

QString
aPlugins::toolTip( const QString& feature ) const
{
    	if ( feature == FA_FIELD ) return "Ananas for QT Field Edit Widget";
    	if ( feature == FA_DBFIELD ) return "Ananas for QT Database Field Edit Widget";
    	if ( feature == FA_TABLE ) return "Ananas for QT Table Widget";
    	if ( feature == FA_DBTABLE ) return "Ananas for QT database Table Widget";
    	if ( feature == FA_GROUPTREE ) return "Ananas for QT Group Tree Widget";
    	if ( feature == FA_ACTIONBUTTON ) return "Ananas for QT Action button Widget";
    	if ( feature == FA_CATALOGUE ) return "";
    	if ( feature == FA_DOCUMENT ) return "";
    	if ( feature == FA_JOURNAL ) return "";
    	if ( feature == FA_REPORT ) return "";
    	if ( feature == FA_COMBOBOX ) return "Ananas for QT custom combobox";
    	return QString::null;
}

QString
aPlugins::whatsThis( const QString& feature ) const
{
    	if ( feature == FA_FIELD ) return "Entry to modify field value of Ananas's object";
    	if ( feature == FA_DBFIELD ) return "Entry to modify field value of Ananas's object";
    	if ( feature == FA_TABLE ) 	return "Entry to modify tables values of Ananas's object";
    	if ( feature == FA_DBTABLE ) 	return "Entry to modify database tables values of Ananas's object";
   	if ( feature == FA_GROUPTREE ) return "Entry to select group of Ananas's object";
   	if ( feature == FA_ACTIONBUTTON ) return "";
   	if ( feature == FA_CATALOGUE ) return "";
    	if ( feature == FA_DOCUMENT ) return "";
    	if ( feature == FA_JOURNAL ) return "";
    	if ( feature == FA_REPORT ) return "";
    	if ( feature == FA_COMBOBOX ) return "";
     	return QString::null;
}

bool
aPlugins::isContainer( const QString& feature ) const
{
	if ( feature == FA_FIELD ) return FALSE;
	if ( feature == FA_DBFIELD ) return FALSE;
	if ( feature == FA_TABLE ) return FALSE;
    	if ( feature == FA_DBTABLE ) return FALSE;
    	if ( feature == FA_GROUPTREE ) return FALSE;
    	if ( feature == FA_ACTIONBUTTON ) return FALSE;
   	if ( feature == FA_CATALOGUE ) return TRUE;
    	if ( feature == FA_DOCUMENT ) return TRUE;
    	if ( feature == FA_JOURNAL ) return TRUE;
    	if ( feature == FA_REPORT ) return TRUE;
	if ( feature == FA_COMBOBOX ) return FALSE;
  	return FALSE;
}


Q_EXPORT_PLUGIN( aPlugins )

