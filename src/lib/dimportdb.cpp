/****************************************************************************
** Form implementation generated from reading ui file 'deditrc.ui'
**
** Created: Пнд Фев 13 14:29:13 2006
**      by: The User Interface Compiler ($Id: dimportdb.cpp,v 1.3 2006/07/07 05:44:09 gr Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "dimportdb.h"
#include "atests.h"
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qfiledialog.h>

dImportDB::dImportDB( QWidget* parent, const char* name, bool modal, WFlags fl )
    : dEditRC( parent, name, modal, fl )
{
    if ( !name )
	setName( "dImportDB" );
    languageChange();

}

/*
 *  Destroys the object and frees any allocated resources
 */
dImportDB::~dImportDB()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void 
dImportDB::languageChange()
{
	dEditRC::languageChange();
	setCaption( tr( "Resource file" ) );
	textLabel8_2->setText( tr( "archive file" ) );
	bOK->setText( tr( "Import" ) );
}

void
dImportDB::onCFGFile()
{
		QFileDialog fd( QString::null,
  			tr("any files (*)"),
			0, 0, TRUE );
		fd.setMode(QFileDialog::AnyFile);
		fd.addFilter(tr("ananas business schema archiff file (*.bsa)"));
		fd.setSelection( QDir::convertSeparators(eCfgName->text()));
		if ( fd.exec() == QDialog::Accepted )
		{
			eCfgName->setText(QDir::convertSeparators(fd.selectedFile()));
		}
		else 
		{
			return;
		}
}
