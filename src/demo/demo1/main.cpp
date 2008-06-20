/*
Test resource, metadata functions.
Create simple configuration embedded in source code.
Author: Valery Grazdankin (leader)
*/
#include <qapplication.h>
#include <qstring.h>
#include <qfile.h>
#include <qdatatable.h>
#include <qtimer.h>
#include <qobject.h>
#include "ananas.h"
#include "alog.h"
#include "../demo_config.h"

#define DEMONAME "Demo 1 - Create simple configuration."

bool
demo(){
	aLog::init();
	aCfg c;
	aCfgItem d1, c1, c2, c3, t, f;

	c.createNew();
	c.setInfo( md_info_name, "Demo configuration" );
	c.setInfo( md_info_author, "leader" );

	// Catalogue 1
	c1 = c.insertCatalogue( QString::fromUtf8("Catalogue 1") );
	c.insertField( c1, md_element, "Name", "C 40" );
	c.insertField( c1, md_element, "Price", "N 10 2" );
	c.insertField( c1, md_element, "Date", "D" );
	c.insertField( c1, md_group, "Code", "N 10 2" );
	c.insertField( c1, md_group, "Name", "C 40" );
	
	// save object to file
	c.saveOneObject(c1, "catalogue_copy.xml");
	// load object from file
	aCfgItem loadObj = c.loadOneObject("catalogue_copy.xml");
	// change name
	c.setAttr(loadObj, mda_name, "CATALOGUE1 COPY!!!");
	// append to cfg
	c.importCfgItem( c.find(c.find(0), md_catalogues) , loadObj);
	
	// Document
	c1 = c.insertDocument( QString::fromUtf8("Document") );
	c.insertField( c1, md_header, "Remark", "C 100" );
	c.insertField( c1, md_header, "Summa", "N 8 4" );
	c2 = c.insertDocumentTable( c1, QString::fromUtf8("Table 1") );
	c.insertField( c2, "", "Name", "C 40" );
	c.insertField( c2, "", "Quantity", "N 10 0" );
	c2 = c.insertDocumentTable( c1, QString::fromUtf8("Table 2") );
	c.insertField( c2, "", "Items", "C 40" );
	// Info register
	c1 = c.insertIRegister( QString::fromUtf8("Info register") );
	c.insertField( c1, md_dimensions, "Name", "C 30" );
	c.insertField( c1, md_dimensions, "Scklad", "N 5" );
	c.insertField( c1, md_resources, "Price", "N 10 2" );
	c.insertField( c1, md_resources, "Count", "N 5" );
	c.insertField( c1, md_information, "Watch this", "C 100" );
	// Acc register
	c1 = c.insertARegister( QString::fromUtf8("Acc register") );
	c.insertField( c1, md_dimensions, "Name", "C 30" );
	c.insertField( c1, md_dimensions, "Sklad", "N 5" );
	c.insertField( c1, md_resources, "Price", "N 10 2" );
	c.insertField( c1, md_resources, "Count", "N 10" );
	c.insertField( c1, md_information, "Remark", "C 100" );

	// Set resource values
	c.rc.setValue("dbtitle", DEMO_DBTITLE);
	c.rc.setValue("dbtype", DEMO_DBTYPE);
	c.rc.setValue("dbname", DEMO_DBNAME);
	c.rc.setValue("dbuser", DEMO_DBUSER);
	c.rc.setValue("dbpass", DEMO_DBPASS);
	c.rc.setValue("dbhost", DEMO_DBHOST);
	c.rc.setValue("configfile", DEMO_CONFIGFILE);
	c.writerc( DEMO_RC );
	return true;
}


// main()
int 
main(int argc, char **argv){
        QApplication app( argc, argv, FALSE );

        printf("Ananas v.%s %s\n\n", ananas_libversion(), DEMONAME);
	if ( demo() ) printf("ok\n");
	else printf("failed\n");
	return 0;
}
