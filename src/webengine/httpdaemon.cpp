/****************************************************************************
** $Id: httpdaemon.cpp,v 1.5 2005/07/04 09:32:34 red75 Exp $
**
** Code file of the HTTP Daemon file of Ananas
** Web Engine application
**
** Created : 20031201
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

#include <stdlib.h>
#include <sys/stat.h>
#include <qsocket.h>
#include <qregexp.h>
#include <qserversocket.h>
#include <qtextstream.h>
#include <qhttp.h>
#include <qfile.h>
#include "httpdaemon.h"
#include "clientsocket.h"
#include <ananas.h>
#include <atemplate.h>


HttpDaemon::HttpDaemon( QObject* parent )
: QServerSocket(8080,1,parent)
{
        if ( !ok() ) {
            qWarning("Failed to bind to port 8080");
            exit( 1 );
        } else {
		qWarning("Ananas http daemon running on port 8080");
	}
}


// When a new client connects, the server constructs a QSocket and all
// communication with the client is done over this QSocket. QSocket
// works asynchronouslyl, this means that all the communication is done
// in the two slots readClient() and discardClient().
void
HttpDaemon::newConnection( int socket )
{
        ClientSocket* s = new ClientSocket( this );
        connect( s, SIGNAL(readyRead()), this, SLOT(readClient()) );
        connect( s, SIGNAL(delayedCloseFinished()), this, SLOT(discardClient()) );
        s->setSocket( socket );
        emit newConnect();
}


// This slot is called when the client sent data to the server. The
// server looks if it was a get request and sends a very simple HTML
// document back.
void
HttpDaemon::readClient()
{
        ClientSocket* socket = (ClientSocket*) sender();
	char buf[8192];
	QString values, path;
	QString h, s, p, v;
	int l = 0, rLen = 0;

        if ( socket->canReadLine() ) {
//            QStringList tokens = QStringList::split( QRegExp("[ \r\n][ \r\n]*"), socket->readLine() );
		while (socket->canReadLine()){
			s = socket->readLine();
			if ( s.isEmpty() ) break;
	    		h = h.append( s );
	    	}
		printf("%s\n",( const char *) h.local8Bit());
		QHttpRequestHeader header( h );
		path = header.path().section("?",0,0);
		v = header.path().section("?",1);
            	if ( header.method() == "POST") {
			l = header.value("Content-Length").toInt();
			printf("POST method l=%i\n", l);
			buf[0]=0;
			rLen = socket->readBlock( buf, sizeof( buf ) - 1 );
			buf[rLen] = 0;
			values = QString( buf );
		}
		if ( values.isEmpty() ) values = v;
		else {
			if ( !v.isEmpty() ) {
				values.append("&");
				values.append(v);
			}
		}
        	if ( header.method() == "GET" || header.method() == "POST") {
			printf("path:%s\n",( const char *) path.local8Bit());
			printf("values:%s\n",( const char *) values.local8Bit());
                	QTextStream os( socket );
  //              	os.setEncoding( QTextStream::UnicodeUTF8 );
			if ( path == "/" ) fLogin( os );
			else
			if ( path == "/main" ) fMain( os );
			else
			if ( path.left(7) == "/icons/" ) fIcon( os, path.right( path.length() - 7 ));
			else {
				os << "HTTP/1.0 200 Ok\r\n"
				"Content-Type: text/html; charset=\"utf-8\"\r\n"
				"\r\n"
				"<html>"
				"<header><title>Ananas HTTP Server</title></header>"
				"<body bgcolor=gray>"
				"<center>"
				"<table width=\"100%\" height=\"100%\" border=1>"
				"<tr valign=center halign=center bgcolor=white><td valign=center halign=center>"
				"<center>Call undefined function"
				"</td></tr><tr height=20 bgcolor=lightblue align=right><td align=right>"
				"Designed by <a href=\"http://www.leaderit.ru\">Leader InfoTech</a>, 2003-2004</td></tr></table>"
				"</body></html>";
			}
			socket->flush();
                	socket->close();
                	emit wroteToClient();
		}

        }
}


void
HttpDaemon::discardClient()
{
        QSocket* socket = (QSocket*)sender();
        delete socket;
        emit endConnect();
}


void
HttpDaemon::fLogin( QTextStream &ts )
{
	aTemplate tpl;
	tpl.open("tpl/login.tpl");

	ts << "HTTP/1.0 200 Ok\r\n"
	"Content-Type: text/html; charset=\"utf-8\"\r\n"
	"\r\n";
	ts << tpl.exec("login");
/*
	"<html>"
	"<header><title>Ananas HTTP Server</title></header>"
	"<body bgcolor=gray>"
	"<center>"
	"<table width=\"100%\" height=\"100%\" border=1>"
	"<tr valign=center halign=center bgcolor=white><td valign=center halign=center>"
	"<center><form method=\"POST\" action=\"main\" name=\"loginform\">"
	"<table border = 1>"
	"<tr bgcolor=lightblue><td>Ananas HTTP server</td></tr><tr><td><table>"
	"<tr><td>Login name:</td><td><input name=loginname></td></tr>"
	"<tr><td>Password:</td><td><input type=password name=password><td>"
	"</table><br><center>"
	"<input type=submit name=bLogin value=\"Login\"></td></tr></table></form>\n"
	"</td></tr><tr height=20 bgcolor=lightblue align=right><td align=right>"
	"Designed by <a href=\"http://www.leaderit.ru\">Leader InfoTech</a>, 2003-2004</td></tr></table>"
	"</body></html>";
*/
}



void
HttpDaemon::fMain( QTextStream &ts )
{
	aTemplate tpl;
	tpl.open("tpl/mainform.tpl");

	ts << "HTTP/1.0 200 Ok\r\n"
	"Content-Type: text/html; charset=\"utf-8\"\r\n"
	"\r\n";
	ts << tpl.exec("mainform");

/*

	ts << "HTTP/1.0 200 Ok\r\n"
	"Content-Type: text/html; charset=\"utf-8\"\r\n"
	"\r\n"
	"<html>"
	"<header><title>Ananas HTTP Server: Main</title></header>"
	"<body bgcolor=gray>"
	"<center>"
	"<table width=\"100%\" height=\"100%\" border=1>"
	"<tr valign=center halign=center bgcolor=white><td valign=center halign=center>"
	"<center>"
	"<img src=\"/icons/lit.png\">"
	"<img src=\"/icons/a-system.png\">"
	"<img src=\"/icons/engine-splash-ru.png\">"
//	"<form method=\"POST\" action=\"main\" name=\"loginform\">"
//	"<table border = 1>"
//	"<tr bgcolor=lightblue><td>Ananas HTTP server</td></tr><tr><td><table>"
//	"<tr><td>Login name:</td><td><input name=loginname></td></tr>"
//	"<tr><td>Password:</td><td><input type=password name=password><td>"
//	"</table><br><center>"
//	"<input type=submit name=bLogin value=\"Login\"></td></tr></table></form>\n"
	"</td></tr><tr height=20 bgcolor=lightblue align=right><td align=right>"
	"Designed by <a href=\"http://www.leaderit.ru\">Leader InfoTech</a>, 2003-2004</td></tr></table>"
	"</body></html>";
*/
}


void
HttpDaemon::fIcon( QTextStream &ts, QString fn )
{
	QFile f( fn );
//	FILE *f;
//	struct stat sb;

//	if ( stat( (const char *) fn, &sb ) < 0 ) return;
//	f = fopen( (const char *) fn, "r" );
//	if ( !f ) return;
	f.open( IO_ReadOnly );
	printf("file:%s len=%i\n",( const char *) fn.local8Bit(), ( int ) f.size() );
	ts << "HTTP/1.0 200 Ok\r\n"
	"Content-Type: image/png\r\n"
	"Content-Length: " << ( int ) f.size() << "\r\n"
	"Connection: close\r\n"
	"\r\n";
//	int c;
	QByteArray b = f.readAll();
	for ( unsigned int i=0; i < b.count(); i++ ) {
		ts.device()->putch( b.data()[i] );
//		ts.device()->flush();
	}
//	while ( ( c = f.getch() )!= -1 ) ts.device()->putch( c );
//	ts << ( const char *) f.readAll();
	f.close();
//	ts << ( const char *) ;
}

