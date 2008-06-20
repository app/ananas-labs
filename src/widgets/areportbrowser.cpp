/****************************************************************************
** $Id: areportbrowser.cpp,v 1.5 2007/09/18 11:59:05 app Exp $
**
** Report metadata object implementation file of
** Ananas application library
**
** Created : 20040701
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Designer application of the Ananas 
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

#include	<qlayout.h>
#include	<qtoolbar.h>
#include	<qaction.h>
#include	<qvbox.h>
#include	<qsimplerichtext.h>
#include	<qpainter.h>
#include	<qpaintdevicemetrics.h>
#include	<qkeysequence.h>
#include	<qprinter.h>
#include 	<qprocess.h>
#include	"acfg.h"
#include	"aobject.h"
#include	"adatabase.h"
#include	"areport.h"
#include	"binreloc.h"
#include	"alog.h"

aReportBrowser::aReportBrowser(  QWidget *parent, const char *name, WFlags f )
:QMainWindow( parent, name, f )
{
	QAction *a;

//	QVBox	*vb = new QVBox(this);
//    setIcon( rcIcon("a-system.png"));
//	vb->setFrameStyle( QFrame::StyledPanel | QFrame::Sunken );
//    	ws = new QWorkspace( vb );
//	ws->setScrollBarsEnabled( FALSE );
//    	setCentralWidget( vb );
	QToolBar *t = new QToolBar( this, "ReportTool" );
	a = new QAction(
	QPixmap::fromMimeSource("print.png"),
	tr("Print"),
	QKeySequence("Ctrl+P"),
	t,
	tr("Print report")
	);
	a->addTo( t );
	connect( a, SIGNAL( activated() ), this, SLOT( print() ) );
	t->show();

	textBrowser = new QTextBrowser( this, "textBrowser" );
	textBrowser->setTextFormat( QTextBrowser::RichText );
	textBrowser->setFocus();
//	textBrowser->showMaximized();
    	setCentralWidget( textBrowser );
//	if ( layout() ) delete layout();
//	QGridLayout *l = new QGridLayout( this );
//	l->addWidget( textBrowser, 1, 0 );
	languageChange();
}

void
aReportBrowser::append( const QString &text )
{
	textBrowser->append( text );
}

void 
aReportBrowser::clear()
{
	textBrowser->clear();
}

void 
aReportBrowser::print()
{
	QPrinter printer;
	QPainter p;

	if (!printer.setup()) return;
	if ( p.begin( &printer ) ){
            QPaintDeviceMetrics metrics( p.device() );
            int dpiy = metrics.logicalDpiY();
            int margin = (int) ( (2/2.54)*dpiy ); // 2 cm margins
            QRect body( margin, margin, metrics.width() - 2*margin, metrics.height() - 2*margin );
            QSimpleRichText richText( textBrowser->text(),
                                      QFont(),
                                      textBrowser->context(),
                                      textBrowser->styleSheet(),
                                      textBrowser->mimeSourceFactory(),
                                      body.height() );
            richText.setWidth( &p, body.width() );
            QRect view( body );
            int page = 1;
            do {
                richText.draw( &p, body.left(), body.top(), view, colorGroup() );
                view.moveBy( 0, body.height() );
                p.translate( 0 , -body.height() );
                p.drawText( view.right() - p.fontMetrics().width( QString::number( page ) ),
                            view.bottom() + p.fontMetrics().ascent() + 5, QString::number( page ) );
                if ( view.top()  >= richText.height() )
                    break;
                printer.newPage();
                page++;
            } while (TRUE);
	}
}


/**!
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void aReportBrowser::languageChange()
{
}



aReport::aReport( aCfgItem context, RT_type report_type, aEngine * e )
:aObject( context, 0, 0, "aReport")
{
	engine = e;
	md = e->md;
	browser = new aReportBrowser( e->ws );
	type = report_type;
	if(report_type==RT_text)
	{
		tpl = new aTemplate();
	}
	if(report_type == RT_office)
	{
		tpl = new aOOTemplate();
	}
}


aReport::aReport(QString name, RT_type report_type, aEngine * e )
:aObject( name, 0, 0, "aReport")
{
	engine = e;
	md = e->md;
	browser = new aReportBrowser( e->ws );
	type = report_type;
	if(report_type==RT_text)
	{
		tpl = new aTemplate();
	}
	if(report_type == RT_office)
	{
		tpl = new aOOTemplate();
	}
}
aReport::~aReport()
{
	if(tpl!=NULL)
	{
		delete tpl;
	}
}

ERR_Code
aReport::initObject()
{
	ERR_Code err = aObject::initObject();
	if ( err ) return err;
	return err_noerror;
}

void
aReport::setTable( const QString &name )
{
	tpl->setDir(path2workdir());
	tpl->open( name );
	tplName = name;
}

void
aReport::setValue( const QString &name, const QString &value )
{
	tpl->setValue( name, value );
}

QString
aReport::value( const QString &name )
{
	return tpl->getValue( name );
}

void
aReport::clear()
{
	browser->clear();
}


void
aReport::exec( const QString &section )
{
	tpl->exec( section );
}

void
aReport::show()
{       
	if(type==RT_text)
	{
		browser->textBrowser->setText( tpl->result() );
		browser->show();
	}
	if(type==RT_office)
	{
		QString fileName = ".ananas-report.odt";
		tpl->cleanUpTags();
		tpl->save(fileName);
#ifndef Q_OS_WIN
		QProcess process( QString("oowriter") );
		process.addArgument( "-n" );
		process.addArgument( QDir::convertSeparators(tpl->getDir()+"/"+fileName ) );
		if( !process.start() )
		{
			aLog::print(aLog::MT_ERROR, QObject::tr("Unable to start OpenOffice Writer"));
		}
#else
		QProcess process( QString("soffice") );
		process.addArgument( "-n" );
		process.addArgument( QDir::convertSeparators(tpl->getDir()+"\\"+fileName) );
		if( !process.start() )
		{
			aLog::print(aLog::MT_ERROR, QObject::tr("Unable to start OpenOffice Writer"));
			aLog::print(aLog::INFO, QObject::tr("May be PATH not set or OpenOffice not install"));
		}
			
#endif		
		//tpl->open( tplName );
	}
}

QString
aReport::path2workdir()
{
	QString res;
#ifndef _Windows
	BrInitError error; 
	if (br_init_lib(&error) == 0 && error != BR_INIT_ERROR_DISABLED) { 
		aLog::print(aLog::MT_INFO, tr("Warning: BinReloc failed to initialize (error code %1)\n").arg(error));
		aLog::print(aLog::MT_INFO, tr("Will fallback to hardcoded default path.\n"));
	} 
	aLog::print(aLog::MT_DEBUG, tr("BinReloc path to data dir is %1.\n").arg( br_find_data_dir("/usr/share") ));
	
	res = QString( br_find_data_dir("/usr/share") ) + "/ananas/";
#else
	res = "";	
#endif
	if(md!=NULL)
	{
		res = md->rc.value("workdir");
	}
	//printf("workdir=`%s'\n",res.ascii());
	return res;
}


void
aReport::close()
{
	tpl->close();
}
	
