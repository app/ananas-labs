/****************************************************************************
** $Id: deditfield.ui.h,v 1.29 2006/05/31 06:44:22 gr Exp $
**
** Code file of the Edit Field window
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
#include <qstatusbar.h>
#include <qdatetime.h>
#include <qvaluelist.h>
#include <qlistview.h>
#include <qvalidator.h>
#include "alog.h"
#include "acfg.h"
#include "acfgrc.h"

/*
#include <qsproject.h>
#include <qsscript.h>
#include <qseditor.h>
#include <qsinterpreter.h>
*/

void
setText(){

}

void dEditField::destroy()
{
    updateMD();
    ( (MainForm*)this->topLevelWidget() )->wl->remove( this );
    ( (MainForm*)this->topLevelWidget() )->removeTab(name());
}



void dEditField::init()
{
// eModule->setInterpreter(new QSInterpreter());
	delete statusBar();
	otypes.clear();
	artypes.clear();
	eType->clear();
	otypes.append(" ");
	lzcheckBox->setText(tr("Add leading zeros"));
	efVd->setText(tr("Validate"));
	efNumerator->setText(tr("Numerator"));
	eType->insertItem(tr("Unknown"), 0);

}


void dEditField::setData( aListViewItem *o )
{
	item = o;
	aCfg *md = o->md;
	aCfgItem obj = o->obj;

	QString ts;
	char t=' ';
	int w=0, d=0, oid, idx=0;
	unsigned int i;


	aAliasEditor *a = new aAliasEditor( md, obj, tAliases );
	al = a;
	al->setData();
	// setCaption( tr("Field:") + md->attr( obj, mda_name ) );
	eName->setText( md->attr( obj, mda_name ) );
	nameChanged();
	// eID->setText( md->attr( obj, mda_id ) );
	ts = md->attr( obj, mda_type );
	if(md->objClass(md->parent(obj))==md_element)
	{
		saldoTextLabel->show();
		comboBox2->show();
//		updateGeometry();
	}
	else
	{
		saldoTextLabel->hide();
		comboBox2->hide();
//		layout()->remove(comboBox2);
//		layout()->remove(saldoTextLabel);

//		updateGeometry();
	}
	// eType0->setText( ts );
	// eModule->setText( md->sText( obj, md_sourcecode ) );
	eDescription->setText( md->sText( obj, md_description ) );

	if( md->attr( obj, mda_sort ) == "1" ) efSort->setChecked( true );
	else efSort->setChecked( false );
	if( md->attr( obj, mda_plus ) == "1" ) efPlus->setChecked( true );
	else efPlus->setChecked( false );
	if( md->attr( obj, mda_nz ) == "1" ) efNZ->setChecked( true );
	else efNZ->setChecked( false );
	if( md->attr( obj, mda_vd ) == "1" ) efVd->setChecked( true );
	else efVd->setChecked( false );
	if( md->attr( obj, mda_twostate ) == "1" ) two_state->setChecked( true );
	else two_state->setChecked( false );
	VdRegEx->setText( md->attr( obj, mda_validator ) );
	inputMask->setText( md->attr( obj, mda_inputmask ) );

	efSum->setChecked(md->attr( obj, mda_sum ) == "1");

	QStringList tlist;
	if(md->objClass(md->parent(obj))==md_resources)
	{
		tlist.append("\t"+QObject::tr("Unknown"));
	}
	else
	{
		tlist = md->types();
	}
	otypes.clear();

	eType->clear();
	for ( QStringList::Iterator it = tlist.begin(); it != tlist.end(); ++it ) {
		otypes.append( (*it).section( "\t", 0, 0 ) );
	 	eType->insertItem( (*it).section("\t", 1, 1 ), idx++ );
	}

	if ( !ts.isEmpty() )
	{
		 sscanf( ts, "%c %d %d", &t, &w, &d );
	}
	else
	{
		t = 'N';
		w = 10;
	}
	if ( t=='O' ) {
		for( i = 0 ; i < otypes.count(); i++ ) {
	  		if( otypes[i][0] == 'O' ) {
	   			sscanf( (const char *)otypes[ i ], "O %d", &oid );
	   			if ( oid == w ) {
	   				 eType->setCurrentItem( i );
	   				 break;
	   			}
	  		}
		}
	} else {
		 if ( t == ' ' ) eType->setCurrentItem( 0 );
	 	 if ( t == 'N' )
		 {
			eWidth->setMaxValue(20);
			eDec->setMaxValue(99);
			eType->setCurrentItem( 1 );
		 }
	 	 if ( t == 'C' )
		 {

			eWidth->setMaxValue(254);
			eDec->setMaxValue(99);
			eType->setCurrentItem( 2 );
			if ( w == 254 )
			{
		          tNotBound->setChecked(TRUE);
		          eWidth->setEnabled(FALSE);
		        }
		 }
	 	 if ( t == 'D' ) eType->setCurrentItem( 3 );
	 	 if ( t == 'B' ) eType->setCurrentItem( 4 );
		 eWidth->setValue( w );
		 eDec->setValue( d );
	}
	aCfgItem obj2;
	int n, n1,aregid, aregfid;
	QString str;
	QStringList l_name;
 //long oid;
	aCfgItem context = md->findChild(md->find(mdc_metadata),md_registers);
	comboBox2->clear();
	comboBox2->insertItem(" ");
	artypes.clear();
	artypes.append(" ");
	n = md->count( context, md_aregister );
// printf("n=%d name = %s\n",n, md->attr(context,mda_name).ascii());
	for (i=0; i<n; i++)
	{
		obj = md->find( context, md_aregister, i);
		if ( !obj.isNull() )
		{
			aregid=md->attr(obj,mda_id).toInt();
			str = tr(QString("AccumulationRegister."))+md->attr( obj, mda_name );
			//printf("`%s'\n",str.ascii());
			obj = md->findChild(obj,md_resources);
			n1 = md->count( obj, md_field);
//   printf("n=%d name = %s\n",n, md->attr(obj,mda_name).ascii());
			for (uint j=0; j<n1; j++)
			{
				obj2 = md->find( obj, md_field, j);
				if ( !obj2.isNull() )
				{
					aregfid = md->attr(obj2, mda_id).toInt();
					artypes.append(QString(" %1 %2").arg(aregid).arg(aregfid));
					comboBox2->insertItem(str+"."+md->attr( obj2, mda_name ));
					if(w==aregid && d==aregfid) comboBox2->setCurrentItem(comboBox2->count()-1);
				}
			}
		}
	}
	typeSelect( eType->currentItem() );
	aUsersList->header()->hide();
	QListViewItem * groupsItem = new QListViewItem( aUsersList, 0 );
	groupsItem->setText( 0, tr( "Groups" ) );
	groupsItem->setExpandable(TRUE);
	groupsItem->setOpen( TRUE );

	QListViewItem * admGroup = new QListViewItem( groupsItem, 0 );
	admGroup->setText( 0, tr( "Administrators" ) );
	admGroup->setExpandable(TRUE);
	admGroup->setOpen( TRUE );

	QListViewItem * operGroup = new QListViewItem( groupsItem, 0 );
	operGroup->setText( 0, tr( "Operators" ) );
	operGroup->setExpandable(TRUE);
	admGroup->setOpen( TRUE );

	QListViewItem * usersGroup = new QListViewItem( aUsersList, 0 );
	usersGroup->setText( 0, tr( "Users" ) );
	usersGroup->setExpandable(TRUE);
	usersGroup->setOpen(TRUE);

	QListViewItem * user1 = new QListViewItem( usersGroup, 0 );
	user1->setText( 0, tr( "Tester" ) );

	// Complete Right List
	aRightsList->header()->hide();
	QValueList<QListViewItem *> rightList;
	rightList.append( new QCheckListItem( aRightsList, tr( "Reading" ), QCheckListItem::CheckBoxController ) );
	rightList.append( new QCheckListItem( aRightsList, tr( "Writing" ), QCheckListItem::CheckBoxController ) );
	rightList.append( new QCheckListItem( aRightsList, tr( "Modification" ), QCheckListItem::CheckBoxController ) );
	rightList.append( new QCheckListItem( aRightsList, tr( "Deleting" ), QCheckListItem::CheckBoxController ) );

	QListViewItem *ritem = 0;
	unsigned int num = 1;
	// go through the list of parent items...
	for ( QValueList<QListViewItem*>::Iterator it = rightList.begin();
	it != rightList.end();
	( *it )->setOpen( TRUE ), ++it, num++ )
	{
	        ritem = *it;
	}
	//


}

void dEditField::updateMD()
{
 QString st;

 aCfg *md = item->md;
 aCfgItem obj = item->obj;

 al->updateMD();
 item->setText( 0, eName->text().stripWhiteSpace() );
 md->setAttr( obj, mda_name, eName->text().stripWhiteSpace() );
 md->setSText( obj, md_description, eDescription->text() );
// md->setSText( obj, md_sourcecode, eModule->text() );

 if ( md->objClass(md->parent(obj)) == md_resources )
  efSort->setChecked( true );
 if( efSort->isChecked() ) md->setAttr( obj, mda_sort, "1" );
 else md->setAttr( obj, mda_sort, "0" );
 if( efPlus->isChecked() ) md->setAttr( obj, mda_plus, "1" );
 else md->setAttr( obj, mda_plus, "0" );
 if( efNZ->isChecked() ) md->setAttr( obj, mda_nz, "1" );
 else md->setAttr( obj, mda_nz, "0" );
 if( efVd->isChecked() ) md->setAttr( obj, mda_vd, "1" );
 else md->setAttr( obj, mda_vd, "0" );
 if (VdRegEx->text() )md->setAttr( obj, mda_validator, VdRegEx->text().stripWhiteSpace() );
 if (inputMask->text() )md->setAttr( obj, mda_inputmask, inputMask->text().stripWhiteSpace() );
 if (two_state->isChecked() ) md->setAttr( obj, mda_twostate, "1" );
 else md->setAttr( obj, mda_twostate, "0" );
 if( efSum->isChecked() )
     md->setAttr( obj, mda_sum, "1" );
 else
     md->setAttr( obj, mda_sum, "0" );
 if(eType->currentItem()==0)
 {
	 st.sprintf(artypes[comboBox2->currentItem()]);
 }
 else
 {
 	st.sprintf( otypes[ eType->currentItem() ], eWidth->value(), eDec->value() );
	printf("type is %s\n",st.ascii());
  	if ( efSort->isChecked() )
  		st.append(" I");
 }
 //printf("%s\n",st.ascii());
 md->setAttr( obj, mda_type, st );
}


void dEditField::typeSelect( int idx )
{
	if ( otypes[ idx ][0] == 'N' )
	{
		eWidth->setMaxValue(20);
		eWidth->show();
		eDec->setMaxValue(99);
		eDec->show();
		tWidth->show();
		tDec->show();
		lzcheckBox->show();
		efSum->show();
		tNotBound->hide();
		tSepTriads->show();
		comboBox2->setEnabled(false);
		comboBox2->hide();
		efVd->show();
		ValidateGroupBox->show();
		NumeratorGroupBox->hide();
		efNumerator->hide();
		saldoTextLabel->hide();
	}
	else
	{
		if ( otypes[ idx ][0] == 'C' )
		{
			eWidth->setMaxValue(254);
			eWidth->show();
			eDec->hide();
			tWidth->show();
			tDec->hide();
			efSum->hide();
			tSepTriads->hide();
			lzcheckBox->hide();
			tNotBound->show();
			efNumerator->show();
			NumeratorGroupBox->show();
			efVd->show();
			ValidateGroupBox->show();
			efSum->setChecked(false);
			comboBox2->setEnabled(false);
			comboBox2->hide();
			saldoTextLabel->hide();
		}
		else
		{
			if( idx == 0)
			{
			    saldoTextLabel->show();
			    comboBox2->show();
			    comboBox2->setEnabled(true);
			    eWidth->hide();
			    lzcheckBox->hide();
			    eDec->hide();
			    tWidth->hide();
			    tDec->hide();
			    efSum->hide();
			    tNotBound->hide();
			    tSepTriads->hide();
			    efVd->hide();
			    efNumerator->->hide();
			    ValidateGroupBox->hide();
			    NumeratorGroupBox->hide();
			    efSum->setChecked(false);
			}
  			else
			{
				comboBox2->setEnabled(false);
				comboBox2->hide();
				saldoTextLabel->hide();
				lzcheckBox->hide();
				eWidth->hide();
				eDec->hide();
				tWidth->hide();
				tDec->hide();
				efSum->hide();
				tNotBound->hide();
				tSepTriads->hide();
				efVd->hide();
				efNumerator->->hide();
				NumeratorGroupBox->hide();
				ValidateGroupBox->hide();
				efSum->setChecked(false);
				// comboBox2->setEnabled(false);
  			}
		}
	}
}


void dEditField::nameChanged()
{
	setCaption( tr("Field:  ") + eName->text() );
}


void dEditField::AARegSelect( int i )
{

}


void dEditField::tNotBound_stateChanged( int )
{
    if (tNotBound->isChecked() )
    {
	eWidth->setValue(254);
	eWidth->setEnabled(FALSE);
    } else {
        eWidth->setEnabled(TRUE);
    }
}


void dEditField::aUsersList_clicked( QListViewItem * )
{
// Read aRightsList for selected user
}


void dEditField::setExample()
{
     QDate date = QDate::currentDate();
     QString curdate, dateformat, numerator;

     if (DateFormat->isChecked() )
     {
	 if (useOwnFofmat->isChecked() )
	 {
	     dateformat =eOwnFormat->text();
	 }else{
	     dateformat =aDFormatBox->currentText();
	 }
        curdate = date.toString(dateformat);
     }

     if (lzcheckBox->isChecked())
     {
    	numerator = eMin->text().rightJustify( eWidth->value(), '0' );
     }
     else {
	numerator = eMin->text();
     }
    eXample->setText(QString("%1%2%3%4").arg(ePrefix->text()).arg(numerator).arg(eSuffix->text()).arg(curdate));
}


void dEditField::efVd_stateChanged( int )
{
    if (efVd->isChecked() )
    {
	ValidateGroupBox->show();
    } else {
	ValidateGroupBox->hide();
    }
}


void dEditField::Testline_textChanged( const QString & )
{
    QRegExp rx( VdRegEx->text() );
    QRegExpValidator v( rx, 0 );
    int pos = 0;
    QString s = Testline->text();
    QPalette pal = Testline->palette();

    if(v.validate(s, pos ) == QValidator::Invalid)
    {
	pal.setColor(QColorGroup::Highlight, Qt::red);
	Testline->setPalette(pal);
    }
    if(v.validate(s, pos ) == QValidator::Intermediate)
    {
	if (two_state->isChecked() ) {
	    pal.setColor(QColorGroup::Highlight, Qt::red);
	}else{
	    pal.setColor(QColorGroup::Highlight, Qt::yellow);
	}
	 Testline->setPalette(pal);
    }
     if(v.validate(s, pos ) == QValidator::Acceptable)
    {
	 pal.setColor(QColorGroup::Highlight, Qt::green);
	 Testline->setPalette(pal);
    }
}

void dEditField::inputMask_textChanged( const QString & )
{
    Testline->setInputMask(inputMask->text());
}


void dEditField::efNumerator_stateChanged( int )
{
    if (efNumerator->isChecked() )
    {
	NumeratorGroupBox->show();
    } else {
	NumeratorGroupBox->hide();
    }
}


void dEditField::DateFormat_stateChanged( int )
{
    if (DateFormat->isChecked() )
    {
	aDFormatBox->setEnabled(TRUE);
	textLabel2->setEnabled(TRUE);
	useOwnFofmat->setEnabled(TRUE);
	eOwnFormat->setEnabled(TRUE);
    } else {
	aDFormatBox->setEnabled(FALSE);
	textLabel2->setEnabled(FALSE);
	useOwnFofmat->setEnabled(FALSE);
	eOwnFormat->setEnabled(FALSE);
    }
}
