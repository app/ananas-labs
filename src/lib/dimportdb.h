/****************************************************************************
** Form interface generated from reading ui file 'deditrc.ui'
**
** Created: Пнд Фев 13 14:06:55 2006
**      by: The User Interface Compiler ($Id: dimportdb.h,v 1.1 2006/02/28 15:07:05 gr Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef DIMPORTDB_H
#define DIMPORTDB_H

#include "ananasglobal.h"
#include "deditrc.h"

class ANANAS_EXPORT dImportDB : public dEditRC
{
    Q_OBJECT

public:
	dImportDB( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
	~dImportDB();


protected slots:
	virtual void languageChange();
	virtual void onCFGFile();
};

#endif // DIMPORTDB_H
