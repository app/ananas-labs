/****************************************************************************
** $Id: main.cpp,v 1.2 2007/12/01 08:47:02 app Exp $
**
** Ananas update application main file
**
** Created : 20071111
**
** Copyright (C) 2007 Grigory Panov <grigory.panov at gmail.com>, Moscow.
**
** This file is part of the Ananas
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
#include <qapplication.h>
#include <qnetwork.h>
#include <qurloperator.h> 
#include <qsinterpreter.h>
#include <qsinputdialogfactory.h>
#include <qsproject.h>
#include <qsscript.h>
#include <qsutilfactory.h>


#include "downloader.h"
#include "ananas.h"
#include "acontainer.h"
#include "alog.h"


#define invalid_command "The command '%1' is unknown"
#define invalid_argument "The argument '%1' is invalid"
#define invalid_option "The option '%1' is unknown"
#define option_not_found "The mandatory option '%1' not found"
#define invalid_usage "Usage: ananas-update command arguments [option]\n command: get, install, update\n argument: file to processing\n options: -rc=ResourceFileName"


void showError(const QString& param, const QString& text)
{
	aLog::print(aLog::MT_ERROR, QString(text).arg(param));
}

void fillArgsFromArgv(QStringList *args, char **argv, int argc)
{
	for(int i=0; i<argc; i++)
	{
		args->append(QString(argv[i]));
	}
} 

QString parseCommand(QStringList * args)
{
	QString command = (*args->at(1)).lower();
	return command;
}

QString parseArgument(QStringList * args)
{
	QString argument = (*args->at(2)).lower();
	return argument;
}

void parseOptions( QStringList *args, QStringList *options)
{
	for(int i=2; i<args->count(); i++)
	{
		options->append((*args->at(i)).lower());
	}
}

bool isValidCommand(const QString& command)
{
	return command == "get" || command == "install" || command == "update";
}

bool isValidArgument(const QString& argument)
{
	return argument != QString::null;
}

void removeInvalidOptions(QStringList *options)
{
	for(int i=0; i<options->count(); i++)
	{
		QString option = *options->at(i);
		if(option[0] != '-') 
		{
			options->remove(options->at(i));
			--i;
			continue;
		}
		if(option.left(4) != "-rc=")
		{
			options->remove(options->at(i));
			--i;
			continue;
		}
	}
}

int
executeScriptFunction(const QString& functionName, const QString& rcfile, const QString& containerName/*, QValueList<QVariant> *parameters=0*/)
{
	aEngine* engine = new aEngine();
	bool ok = false;
	aContainer container(containerName);
	if ( engine->db.init( rcfile ) ) 
	{
		engine->md = &(engine->db.cfg);
		engine->code = engine->project.interpreter();
		engine->code->setErrorMode(QSInterpreter::Nothing);
		//connect(engine->code, SIGNAL( error ( const QString &, QObject *, const QString &, int )),
		//	engine, SLOT  ( error ( const QString &, QObject *, const QString &, int )));
		engine->code->addObjectFactory( new QSInputDialogFactory );
		engine->code->addObjectFactory( new aObjectsFactory( engine ) );
		engine->code->addObjectFactory( new QSUtilFactory );
		engine->project.addObject( engine );
		engine->project.addObject( engine->md );
		engine->project.addObject( &container );
		if(container.open())
		{
			QString script = container.getFileContent(QString("scripts/%1.qsa").arg(functionName));
			engine->project.createScript("containerScript", script);
			if ( engine->project.interpreter()->functions(&container).findIndex(functionName)!=-1)
			{
				engine->project.interpreter()->call(functionName,QSArgumentList(/*parameters*/), &container);
			}
			container.close();
			return 0;
		}
	} 
	return 4;

}

int doGet(const QString& argument, QStringList *options)
{
	//qInitNetworkProtocols();
	QUrlOperator op( argument );
    op.get();
	return 0;
	// need create handler for store file and connect to this signal
	//void QUrlOperator::data ( const QByteArray & data, QNetworkOperation * op )
}

int doUpdate(const QString& argument, QStringList *options)
{
	for(int i=0; i<options->count(); i++)
	{
		QString option = *(options->at(i));
		if(option.left(4) == "-rc=")
		{
			QString rcfile = option.right(option.length()-4);
			return executeScriptFunction("update", rcfile, argument);
		}
	}
	showError("-rc", option_not_found);
	return 3;

}

int doInstall(const QString& argument, QStringList *options)
{
	for(int i=0; i<options->count(); i++)
	{
		QString option = *(options->at(i));
		if(option.left(4) == "-rc=")
		{
			QString rcfile = option.right(option.length()-4);
			return executeScriptFunction("install", rcfile, argument);
		}
	}
	showError("-rc", option_not_found);
	return 3;

}

int doAction(const QString& command, const QString& argument, QStringList *options)
{
	if(command == "get") return doGet(argument, options);
	if(command == "update") return doUpdate(argument, options);
	if(command == "install") return doInstall(argument, options);
}



int main(int argc, char** argv)
{
	aLog::init("c:\\file.log",aLog::MT_DEBUG);
	printf("dwd1\n");
	if(argc <=1) 
	{
		showError("", invalid_usage);
		return 1;
	}
	printf("dwd\n");
	QStringList args;
	fillArgsFromArgv(&args, argv, argc);
	QString command = parseCommand(&args);
	if(!isValidCommand(command))
	{
		showError(command, invalid_command);
		return 1;
	}
	QString argument = parseArgument(&args);
	if(!isValidArgument(argument))
	{
		showError(argument, invalid_argument);
		return 2;
	}
	QStringList options;
	parseOptions(&args, &options);
	removeInvalidOptions(&options);
	int res = doAction(command, argument, &options);
	aLog::close();
	return res;
} 
