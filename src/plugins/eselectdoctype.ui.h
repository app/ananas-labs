/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void eSelectDocType::init()
{
    listDocs->header()->hide();
    listDocs->setColumnWidth( 0, 1000 );
    listDocs->setFocus();
}


void eSelectDocType::setJournal( aCfg *md, int id )
{
    aCfgItem obj, dobj;
    int i, cnt, t, did;
    QString name;
    
    listDocs->clear();
    dlist.clear();
    obj = md->find( id );
    if ( !obj.isNull() ) {
	dlist = md->getJournalDocuments( obj );
//	printf("docs=%s\n", ( const char *) dlist.join("\n") );
	for (i=0;i< dlist.count();i++) {
	    did = dlist[i].toInt();
	    dobj = md->find( did );
	    if ( !dobj.isNull() ) {
		name = md->attr( dobj, mda_name );
		new QListViewItem( listDocs, name, dlist[i] );
	    }
	}
	listDocs->setSelected( listDocs->firstChild(), true );
    }
}


void eSelectDocType::accepted()
{
    docId = listDocs->selectedItem()->text(1).toInt();
  //  printf("docId=%i\n", docId );
    accept();
}
