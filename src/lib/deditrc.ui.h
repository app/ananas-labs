/****************************************************************************
** $Id: deditrc.ui.h,v 1.7 2007/10/16 07:36:45 app Exp $
**
** Code file of the Ananas edit resource file window
** of Ananas Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
**
** This file is part of the Library of the Ananas
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
#include <qfiledialog.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qinputdialog.h>
#include <qvbuttongroup.h>
#include <qradiobutton.h>
#include "alog.h"
//#include <qstring.h>

/*!\en
 *	init editor.
\_en \ru
 *	инициализирует редактор.
 *\_ru
 */
void dEditRC::init()
{
//	dataBase = QSqlDatabase::addDatabase( "QMYSQL3U" );
}

/*!\en
 *	set a data.
\_en \ru
 *	устанавливает данные формы.
 *\_ru
 */
void dEditRC::setdata(QString nameRC, rcListViewItem *item)
{
//	QFile f;
//	QString s, sv, sn;
//	char buf[1025];
	it = item;
	QMap<QString,QString> cfg;

	cfg = aTests::readConfig(QDir::convertSeparators(nameRC));
	eRCFile->setText(QDir::convertSeparators(nameRC));
	eDBType->setCurrentItem(0);
	setCaption( tr("Resource file:") + cfg["dbtitle"]);
	eDBTitle->setText(cfg["dbtitle"]);
	eDBName->setText(cfg["dbname"]);
	eDBUserName->setText(cfg["dbuser"]);
	ePass->setText(cfg["dbpass"]);
	eDBHost->setText(cfg["dbhost"]);
	eDBPort->setText(cfg["dbport"]);
	eCfgName->setText(QDir::convertSeparators(cfg["configfile"]));
	if(cfg["dbtype"]=="postgres") eDBType->setCurrentItem(3);
	if(cfg["dbtype"]=="mysql") eDBType->setCurrentItem(2);
	if(cfg["dbtype"]=="internal") eDBType->setCurrentItem(1);
	eWorkDir->setText(QDir::convertSeparators(cfg["workdir"]));
}

/*!\en
 *	Update a Cfg.
\_en \ru
 *	Обновляет конфигурацию.
 *\_ru
 */
void dEditRC::updatecfg()
{
	QMap<QString,QString> cfg;

	cfg["dbtitle"]	= eDBTitle->text();
	cfg["dbname"]	= eDBName->text();
	if(eDBType->currentItem()==1) cfg["dbtype"] ="internal";
	if(eDBType->currentItem()==2) cfg["dbtype"] ="mysql";
	if(eDBType->currentItem()==3) cfg["dbtype"]= "postgres";
	cfg["dbuser"]	= eDBUserName->text();
	cfg["dbpass"]	= ePass->text();
	cfg["dbhost"]	= eDBHost->text();
	cfg["dbport"]	= eDBPort->text();
	cfg["workdir"]	= QDir::convertSeparators(eWorkDir->text());
	cfg["configfile"]= QDir::convertSeparators(eCfgName->text());

	aTests::writeConfig(QDir::convertSeparators(eRCFile->text()),cfg);
}

/*!\en
 *	Action if "OK" button pressed.
\_en \ru
 *	Действие при нажатии кнопки "OK".
 *\_ru
 */
void dEditRC::onOK()
{
	updatecfg();
	it->rcfile = QDir::convertSeparators(eRCFile->text());
	it->setText(0,eDBTitle->text());
	accept();
}

/*!\en
 *	Dialog of selection RC-file.
\_en \ru
 *	Диалог выбора RC-файла.
 *\_ru
 */
void dEditRC::onRCFile()
{
		QFileDialog fd( QString::null,
  			tr("ananas config resource (*.rc)"),
			0, 0, TRUE );
		fd. setMode ( QFileDialog::AnyFile );
		fd.setSelection( QDir::convertSeparators(eRCFile->text()));
		if ( fd.exec() == QDialog::Accepted ) {
			eRCFile->setText(QDir::convertSeparators(fd.selectedFile()));
			setdata(eRCFile->text(),it);
		} else {
			return;
		}
}

/*!\en
 *	Dialog of selection CFG-file.
\_en \ru
 *	Диалог выбора CFG-файла.
 *\_ru
 */
void dEditRC::onCFGFile()
{
		QFileDialog fd( QString::null,
  			tr("ananas config file (*.cfg)"),
			0, 0, TRUE );
		fd. setMode ( QFileDialog::AnyFile );
		fd.setSelection( QDir::convertSeparators(eCfgName->text()));
		if ( fd.exec() == QDialog::Accepted ) {
			eCfgName->setText(QDir::convertSeparators(fd.selectedFile()));
		} else {
			return;
		}
}

/*!\en
 *	Dialog of selection a working directory.
\_en \ru
 *	Диалог выбора рабочего каталога.
 *\_ru
 */
void dEditRC::on_wDirCFG()
{
	QFileDialog wd( QString::null,
			tr("ananas working directory"),
			   0, 0, TRUE );
	wd. setMode ( QFileDialog::DirectoryOnly );
	wd.setSelection( QDir::convertSeparators(eCfgName->text()));
	if ( wd.exec() == QDialog::Accepted ) {
		eWorkDir->setText(wd.dirPath());
	} else {
		return;
	}
}

/*!\en
 *	Action if "Test connection" button pressed.
\_en \ru
 *	Действие при нажатии кнопки "Проверить соединение".
 *\_ru
 */
void dEditRC::bTest_clicked()
{
	if (eDBHost->text() == "" || eDBName->text() == "" || eDBUserName->text() == "" || ePass->text() == "" )
	{
	QString err_mess = "";
	if (eDBHost->text() == "")
	{
		err_mess = err_mess + tr("- Enter HostName.\n");
	}
	if (eDBName->text() == "")
	{
		err_mess = err_mess + tr("- Enter DBName.\n");
	}
	if (eDBUserName->text() == "")
	{
		err_mess = err_mess + tr("- Enter DBUserName.\n");
	}

	if (ePass->text() == "")
	{
		err_mess = err_mess + tr("- Enter DBPassword.\n");
	}

		QMessageBox::warning( this, tr("Test connection"),
			QString(tr("Test imposible.\n"
			"No all data collected...\n"))+err_mess);
		return;
	}

	eDBType_activated(eDBType->currentItem() );
	QString dbhost = eDBHost->text();
	QString dbname = eDBName->text();
	QString dbuser = eDBUserName->text();
	QString dbpass = ePass->text();
	QString dbport = eDBPort->text();
	dataBase->setUserName( dbuser );
	dataBase->setPassword( dbpass );
	dataBase->setHostName( dbhost );
	dataBase->setDatabaseName( dbname );

	if ( !dbport.isEmpty() ) {
		dataBase->setPort( eDBPort->text().toInt() );
	}

	if ( ! dataBase->open() )
	{
		QMessageBox::warning( this, "RC-file Editor",
			QString(tr("Unable to converse with a database.\n"
			"Reason:\n %1")).arg(dataBase->lastError().text()));
		aLog::print(aLog::MT_ERROR, QString("RC-Editor. Test Access to DataBase: %1").arg(dataBase->lastError().text()));

	}else{
		QMessageBox::information( this, "RC-file Editor",
			QString(tr("User <b>%1</b> granted to use base <b>%2</b>.")).arg(dbuser).arg(dbname) );
	}
}

/*!\en
 *	Open a Dialog for select or create DB.
\_en \ru
 *	Открывает диалог выбора или создания базы данных.
 *\_ru
 */
void dEditRC::bFindBD_clicked()
{

	if ( prepareDB() )
	{
	int k;
	QSqlQuery q;
	QDialog *dlg = new QDialog ( );
	QVBoxLayout *vbox = new QVBoxLayout( dlg, 11, 6 );
	QVBoxLayout *box1 = new QVBoxLayout( vbox );
	QHBoxLayout *box2 = new QHBoxLayout( vbox );
	dlg->setModal (TRUE);
	dlg->setCaption(tr("Select"));
	QButtonGroup *bg = new QButtonGroup( 10,
	QGroupBox::Vertical, tr("Available DataBases"),dlg);
	box1->addWidget( bg );
	bg->setExclusive( TRUE );
	QRadioButton *createNew = new QRadioButton( tr("Create"), bg );
	createNew->setChecked( TRUE );
	switch ( eDBType->currentItem() ) {
		case 2:
			q = dataBase->exec("SHOW DATABASES;");
			break;
		case 3:
			q = dataBase->exec("SELECT * FROM pg_database;");
			break;
		default:
			q = dataBase->exec("SHOW DATABASES;");
			break;
	}
	while ( q.next() )
	{
		QString name = q.value(0).toString();
		bases.append(name);
		(void) new QRadioButton( QString("%1").arg(name), bg );
	}
	//
	QPushButton *okB = new QPushButton(tr("Select"), dlg);
	QPushButton *clB = new QPushButton(tr("Cancel"), dlg);
	box2->addWidget( okB );
	box2->addWidget( clB );
	connect( okB, SIGNAL( clicked() ), dlg, SLOT( accept() ) );
	connect( clB, SIGNAL( clicked() ), dlg, SLOT( close() ) );
	dlg->show ( );
	if ( dlg->exec() == QDialog::Accepted )
	{
		for (k=0; k < bg->count(); k++)
		{
			if (bg->find(k)->state()
			&& bg->find(k)->text()
			!= tr("Create") )
			{
				eDBName->setText(bg->find(k)->text());
			}
			if ( bg->find(k)->state()
			&& bg->find(k)->text()
			== tr("Create"))
			{
				eDBName->setText("");
				bCreareBD_clicked();
			}
		}
	}
}
}

/*!\en
 *	Change a Window caption.
\_en \ru
 *	Изменяет заголовок окна.
 *\_ru
 */
void dEditRC::eDBTitle_textChanged( const QString & )
{
	setCaption( tr("Resource file: ") + eDBTitle->text() );
}

/*!\en
 *	Prepare connection with DB.
\_en \ru
 *	Подготавливает соединение с базой данных.
 *\_ru
 */
bool dEditRC::prepareDB()
{
	eDBType_activated( eDBType->currentItem() );
	QString prompt = tr("Enter a root password:");
	QString pass;
	bool ok;
	QString dbhost = eDBHost->text();
	QString dbport = eDBPort->text();
	QString dbname = eDBName->text();

	dataBase->setHostName( dbhost );
	if ( !dbport.isEmpty() ) {
		dataBase->setPort( eDBPort->text().toInt() );
	}
	switch ( eDBType->currentItem() )
	{
		case 2:
			prompt = tr("Enter a <b>root</b> password:");
			dataBase->setUserName( "root");
			dataBase->setDatabaseName( "test" );
			break;
		case 3:
			prompt = tr("Enter a <b>postgres</b> password:");
			dataBase->setUserName( "postgres");
			dataBase->setDatabaseName( "postgres" );
			break;
		default:
			prompt = tr("Enter a <b>root</b> password:");
			dataBase->setUserName( "root");
			dataBase->setDatabaseName( "test" );
			break;
	}

	if (rootpass == "")
	{
		pass = QInputDialog::getText(
		tr("Root access required"),
		prompt,  QLineEdit::Password,
		QString::null, &ok, this );
		if ( ok && !pass.isEmpty() )
		{
			rootpass = pass;
		}else{
			return FALSE;
		}
	}
		dataBase->setPassword( rootpass );
	if ( ! dataBase->open() )
	{
		QMessageBox::information( this, "RC-file Editor",
		QString("Unable to converse with a database."
		"Reason: \n""%1").arg(dataBase->lastError().text()));
		aLog::print(aLog::MT_ERROR, QString("RC-Editor. Prepare DB error: %1").arg(dataBase->lastError().text()));
		return FALSE;
	}
	return TRUE;
}

/*!\en
 *	Creation of a DB.
\_en \ru
 *	Создание базы данных.
 *\_ru
 */
void dEditRC::bCreareBD_clicked()
{
	if ( prepareDB() )
	{
	QString prompt = tr("Add new DataBase:");
	bool ok, yes=TRUE;
	QString db_name, query;

	if ( ! dataBase->open() )
	{
		QMessageBox::information( this, "RC-file Editor",
			QString("Unable to converse with a database."
			"Reason: \n""%1").arg(dataBase->lastError().text()));
		aLog::print(aLog::MT_ERROR, QString("RC-Editor. Create DB error: %1").arg(dataBase->lastError().text()));

	}else{
		while (yes)
		{
			db_name = QInputDialog::getText(
			tr("Enter a <b>new</b> database name:"),
			prompt,  QLineEdit::Normal,  QString::null, &ok, this );
			if ( ok && !db_name.isEmpty() )
			{
				if (bases.contains(db_name) == 0 )
				{
					yes=FALSE;
				}else
				{
					prompt = QString(tr("Name <b>%1</b> alredy exist.\nEnter another name:").arg(db_name));
					yes=TRUE;
				}
			}else{
				db_name = "";
				yes=FALSE;
			}
		}

	}
	if ( db_name != "")
	{
		switch ( eDBType->currentItem() ) {
			case 2:
				query = QString("CREATE DATABASE %1 character set utf8").arg(db_name);
				break;
			case 3:
				query = QString("CREATE DATABASE %1 ENCODING = \'UTF8\'").arg(db_name);
				break;
			default:
				query = QString("");
				break;
		}


		QSqlQuery q = dataBase->exec(query);
		eDBName->setText(db_name);
		aLog::print(aLog::MT_INFO, QString("RC-Editor. Created new DataBase %1").arg(db_name));
	}
}
}

/*!\en
 *	Creation of a DB User.
\_en \ru
 *	Создание пользователя базы данных.
 *\_ru
 */
void dEditRC::bCreareUser_clicked()
{
	if (prepareDB() )
	{
	QString prompt = tr("Add new User:");
	bool ok, yes=TRUE;
	QString user_name, pass, query;
	QSqlQuery q;

// Check for existen users &
	prepareDB();
	if ( ! dataBase->open() )
	{
		QMessageBox::information( this, "RC-file Editor",
			QString("Unable to converse with a database."
			"Reason: \n""%1").arg(dataBase->lastError().text()));
	}else{
		while (yes)
		{
			user_name= QInputDialog::getText(
				tr("Enter a <b>new</b> user name:"),
				prompt,  QLineEdit::Normal,  QString::null, &ok, this );
			if ( ok && !user_name.isEmpty() )
			{
				if (users.contains(user_name) == 0 )
				{
					yes=FALSE;
				}else{
					prompt = QString(tr("Name <b>%1</b> alredy exist.\nEnter another name:")).arg(user_name);
					yes=TRUE;
				}
			}else{
				user_name = "";
				yes=FALSE;
			}
		}
	}
	if ( user_name != "")
	{
		prompt = tr("Set password:");
		pass = QInputDialog::getText(
				tr("Enter a password for this user:"),
				   prompt,  QLineEdit::Password,  QString::null, &ok, this );
		if ( ok && !pass.isEmpty() )
		{
			eDBUserName->setText(user_name);
			ePass->setText(pass);

			switch ( eDBType->currentItem() ) {
				case 2:
					query = QString("CREATE USER \'%1\'@\'%2\' IDENTIFIED BY \'%3\'").arg(eDBUserName->text()).arg(eDBHost->text()).arg(ePass->text());
					q = dataBase->exec(query);
					query = QString("GRANT ALL PRIVILEGES ON %1 .* TO \'%2\'@\'%3\' WITH GRANT OPTION").arg(eDBName->text()).arg(eDBUserName->text()).arg(eDBHost->text());
					q = dataBase->exec(query);
					query = QString("SET PASSWORD FOR  \'%1\'@\'%2\' = PASSWORD(\'%3\'").arg(eDBUserName->text()).arg(eDBHost->text()).arg(pass);
					q = dataBase->exec(query);
					break;
				case 3:
					query = QString("CREATE ROLE %1 WITH LOGIN PASSWORD \'%2\'").arg(eDBUserName->text()).arg(pass);
					q = dataBase->exec(query);
					query = QString("GRANT ALL ON DATABASE %1 TO %2").arg(eDBName->text()).arg(eDBUserName->text());
					q = dataBase->exec(query);
					break;
				default:
					query = QString("");
					break;
			}
		}
		aLog::print(aLog::MT_INFO, QString("RC-Editor. Created new user %1 with ALL rights to %2").arg(eDBUserName->text()).arg(eDBName->text()));
	}
	}
}

/*!\en
 *	Reaction of a DB type changing.
\_en \ru
 *	Реакция на изменение типа базы данных.
 *\_ru
 */
void dEditRC::eDBType_activated( int dbInd)
{
	switch ( dbInd ) {
	case 0:
		bTest->setEnabled(FALSE);
		bFindBD->setEnabled(FALSE);
		bCreareUser->setEnabled(FALSE);
		break;
	case 1:
		dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
		eDBPort->setText("");
		bFindBD->setEnabled(FALSE);
		bCreareUser->setEnabled(FALSE);
		bTest->setEnabled(FALSE);
		break;
	case 2:
		dataBase = QSqlDatabase::addDatabase( "QMYSQL3U" );
		eDBPort->setText("3306");
		bTest->setEnabled(TRUE);
		bFindBD->setEnabled(TRUE);
		bCreareUser->setEnabled(TRUE);
		break;
	case 3:
		dataBase = QSqlDatabase::addDatabase( "QPSQL7" );
		eDBPort->setText("5432");
		bTest->setEnabled(TRUE);
		bFindBD->setEnabled(TRUE);
		bCreareUser->setEnabled(TRUE);
		break;
	default:
		dataBase = QSqlDatabase::addDatabase( "QMYSQL3U" );
		eDBPort->setText("");
		bTest->setEnabled(FALSE);
		bFindBD->setEnabled(FALSE);
		bCreareUser->setEnabled(FALSE);
		break;
	}
}

/*!\en
 *	Open a Dialog for select or create DB User.
\_en \ru
 *	Открывает диалог выбора или создания пользователя базы данных.
 *\_ru
 */
void dEditRC::bFindUser()
{

	if ( prepareDB() )
	{
	int k;
	QSqlQuery q;
	QString query;
	QDialog *dlg = new QDialog ( );
	QVBoxLayout *vbox = new QVBoxLayout( dlg, 11, 6 );
	QVBoxLayout *box1 = new QVBoxLayout( vbox );
	QHBoxLayout *box2 = new QHBoxLayout( vbox );
	dlg->setModal (TRUE);
	dlg->setCaption(tr("Select"));
	QButtonGroup *bg = new QButtonGroup( 10,
		QGroupBox::Vertical, tr("Available Users"),dlg);
	box1->addWidget( bg );
	bg->setExclusive( TRUE );
	QRadioButton *createNew = new QRadioButton( tr("Create"), bg );
	createNew->setChecked( TRUE );
	switch ( eDBType->currentItem() ) {
		case 2:
			q = dataBase->exec("SELECT User FROM mysql.user;");
			break;
		case 3:
			q = dataBase->exec("SELECT * FROM pg_roles;");
			break;
		default:
			q = dataBase->exec("SELECT User FROM mysql.user;");
			break;
	}

	while ( q.next() )
	{
		if (q.value(0).toString() != "root")
		{
			QString name = q.value(0).toString();
			users.append(name);
			(void) new QRadioButton( QString("%1").arg(name), bg );
		}
	}
	QPushButton *okB = new QPushButton(tr("Select"), dlg);
	QPushButton *clB = new QPushButton(tr("Cancel"), dlg);
	box2->addWidget( okB );
	box2->addWidget( clB );
	connect( okB, SIGNAL( clicked() ), dlg, SLOT( accept() ) );
	connect( clB, SIGNAL( clicked() ), dlg, SLOT( close() ) );
	dlg->show ( );
	if ( dlg->exec() == QDialog::Accepted )
	{
		for (k=0; k < bg->count(); k++)
		{
			if (bg->find(k)->state()
				&& bg->find(k)->text()
				!= tr("Create") )
			{
				eDBUserName->setText(bg->find(k)->text());
				ePass->setText("");
			}
			if ( bg->find(k)->state()
				 && bg->find(k)->text()
				 == tr("Create"))
			{
				eDBUserName->setText("");
				ePass->setText("");
				bCreareUser_clicked();
			}
		}
	}
	}
}
