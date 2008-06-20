/****************************************************************************
** $Id: wfield.cpp,v 1.73 2008/06/09 11:45:27 app Exp $
**
** Code file of the field plugin of Ananas
** Designer and Engine applications
**
** Created : 20031201
**
** Copyright (C) 2003-2004 Leader InfoTech.  All rights reserved.
** Copyright (C) 2003-2004 Grigory Panov, Yoshkar-Ola.
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

#include <qlineedit.h>
#include <qlayout.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <qdom.h>
#include <qvalidator.h>
#include <qlabel.h>
#include <qlistbox.h>
#include <qsizepolicy.h>
#include <qgroupbox.h>
#include <qpushbutton.h>

#include "command.h"
#include "mainwindow.h"
#include "formwindow.h"

#include "ananas.h"
#include "alog.h"
#include "wfield.h"
#include "wdateedit.h"
#include "wcatalogeditor.h"
#include "efield.h"



/*!
 * \en	Constructs object with parent=parent, name=name and flags=fl \_en
 * \ru	Создает объект с родителем parent, именем name и флагом fl. \_ru
 */
wField::wField( QWidget *parent, const char *name, WFlags fl )
    : aWidget( parent, name, fl )
{
	loaded = 0;
	md_oid = 0;
	md_fid = 0;
	setSizePolicy( QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed ) );
	setFocusPolicy(StrongFocus);
	new QHBoxLayout( this, 0, 0 );
	lineEdit = new QLineEdit(this);
	lineEdit->hide();
	dateEdit = new wDateEdit(this);
	dateEdit->hide();
	objButton = new wCatButton("...",this);
	objButton->hide();
	objLabel = new QLabel(this);
	objLabel->setSizePolicy( QSizePolicy( QSizePolicy::Ignored, QSizePolicy::Preferred ));
	objLabel->setFrameShape(QFrame::Box);
	objLabel->setText("UnknownField");
	objLabel->show();
	checkBox = new wCheckBox(this);
	checkBox->hide();
	vEditorType = Unknown;
}
/*
wField::wField( QWidget *parent, const char *name, WFlags fl, bool dbf )
    : aWidget( parent, name, fl )
{
    setSizePolicy( QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Fixed ) );
    //vValue = "";
    //vFieldType="";
    new QHBoxLayout( this, 0, 0 );
    loaded = 0;
    fieldEditor = NULL;
    fieldSelector = NULL;
    cfgobj_name = NULL;
    cfgobj_type = NULL;
    vEditorType = Unknown;
    setMode( Mode0 );
    if ( dbf ) widgetInit();
}
*/


/*!
 * \en 	Destructor. \_en
 */
wField::~wField()
{
}


/*!
 * \en	Sets widget visual type, depend of property fieldType.
 * 	This property must be set above call this function. \_en
 * \ru	Устанавливает визуальный тип виджета в зависимости от свойства
 * 	`fieldType'. Это свойсто должно быть установлено до вызова этой функции,
 * 	иначе тип виджета будет установлен в Unknown. \_ru
 */
void
wField::widgetInit()
{
    QString str;
    char s1[20];
    int n1=0, n2=0;
    lineEdit->hide();
	disconnect( lineEdit, SIGNAL( textChanged( const QString & ) ),
				this, SLOT( setValue( const QString & ) ) );
	disconnect( lineEdit, SIGNAL( lostFocus() ), this, SLOT( focusOutEvent()) );
  //  lineEdit->disconnect();
    lineEdit->setReadOnly(false);
    layout()->remove(lineEdit);
    dateEdit->hide();// = new QDateEdit(this);
    disconnect(dateEdit, SIGNAL( valueChanged ( const QDate&) ),
				this, SLOT( setValue( const QDate & ) ) );
    disconnect(dateEdit, SIGNAL( lostFocus() ),
			 	this, SLOT( focusOutEvent() ) );
    layout()->remove(dateEdit);
    objLabel->hide();// = new QLabel(this);
    objLabel->disconnect();
    layout()->remove(objLabel);
    objButton->hide();// = new wCatButton("...",this);
	disconnect( objButton,	SIGNAL( clicked() ),
			 this, SLOT( fieldSelect() ) );
//    objButton->disconnect();
    layout()->remove(objButton);
    checkBox->hide();
	disconnect( checkBox, SIGNAL( valueChanged ( const QString & ) ),
				this, SLOT( setValue( const QString & ) ) );
		
	disconnect( checkBox, SIGNAL( toggled (bool) ), checkBox, SLOT( on_toggled() ) );
//     checkBox->disconnect();
    layout()->remove(checkBox);
    //TODO: need rewrite
    if (!vFieldType.isEmpty()) sscanf((const char *)vFieldType,"%s %i %i", s1, &n1, &n2);
    
    switch (vEditorType)
    {
    case Numberic:
		lineEdit->setText(vValue);
		if(vFieldType.isEmpty())
		{
		// set validator for numeric type
			QString str = tr("^\\-{0,1}\\d{0,%1}\\.{1}\\d{0,%2}$").arg(3).arg(3);
			QRegExp rexp = str;
			lineEdit->setValidator(new QRegExpValidator(rexp,lineEdit));
		}
		else
		{
			if(n2==0)
			{
			   // set default validator for integer type
			   QString str = tr("^\\-{0,1}\\d{0,%1}$").arg(n1);
			   QRegExp rexp = str;
			   lineEdit->setValidator(new QRegExpValidator(rexp,lineEdit));
			}
			else
			{
				// set default validator for float type
				QString str = tr("^\\-{0,1}\\d{0,%1}\\.{1}\\d{0,%2}$").arg(n1).arg(n2);
				QRegExp rexp = str;
				lineEdit->setValidator(new QRegExpValidator(rexp,lineEdit));
			}
		}
		connect( lineEdit, SIGNAL( textChanged( const QString & ) ),
				this, SLOT( setValue( const QString & ) ) );
		connect( lineEdit, SIGNAL( lostFocus() ), this, SLOT( focusOutEvent()) );
		
		setFocusProxy(lineEdit);
		layout()->add( lineEdit );
		lineEdit->show();
		break;
	
	case String:
		if(vFieldType.isEmpty())
		{
			// set default validator for string
			lineEdit->setMaxLength(20);
		}
		else
		{
			// set validator for string
			lineEdit->setMaxLength(n1);
		}
		connect( lineEdit, SIGNAL( textChanged( const QString & ) ),
				this, SLOT( setValue( const QString & ) ) );
		connect( lineEdit, SIGNAL( lostFocus() ), this, SLOT( focusOutEvent()) );
		
		setFocusProxy(lineEdit);
		layout()->add( lineEdit );
		lineEdit->show();
		break;
		
	case Date:
	case DateTime:
	// used object wDateTime, inherits QDateTime
		dateEdit->setSeparator(".");
		dateEdit->setOrder( QDateEdit::DMY );
		objButton->setMaximumWidth(25);
		objButton->setFocusPolicy(StrongFocus);
		objButton->setPixmap( QPixmap::fromMimeSource( "calendar.png" ) );
		connect(dateEdit, SIGNAL( valueChanged ( const QDate&) ),
				this, SLOT( setValue( const QDate & ) ) );
		connect(dateEdit, SIGNAL( lostFocus() ),
			 	this, SLOT( focusOutEvent() ) );
		//connect( objButton, SIGNAL( clicked() ), this, SLOT( fieldSelect() ) );
		connect( objButton, SIGNAL( clicked() ), this, SLOT(popupCalendar()));
		//setFocusProxy( dateEdit );
		setFocusProxy(objButton);
		layout()->add( dateEdit );
		layout()->add( objButton );
		objButton->show();
		dateEdit->show();
		break;
		
	case Catalogue:
		md_oid = n1;
		objLabel->setFrameShape( QFrame::Box );
		objLabel->setLineWidth( 1 );
		objLabel->setFocusPolicy(NoFocus);
		objButton->setMaximumWidth(25);
		objButton->setFocusPolicy(StrongFocus);
		objButton->setPixmap( QPixmap::fromMimeSource( "wcatalogue.png" ) );
		connect( objButton,	SIGNAL( clicked() ),
			 this, SLOT( fieldSelect() ) );
		
		setFocusProxy(objButton);
		layout()->add( objLabel );
		layout()->add( objButton );
		objLabel->show();
		objButton->show();
		break;

	case Document:
	// Field type = Document
		md_oid = n1;
		objLabel->setFrameStyle( QFrame::Panel | QFrame::Sunken );
		objLabel->setLineWidth( 1 );
		objLabel->setFocusPolicy(NoFocus);
		objButton->setMaximumWidth(25);
		objButton->setFocusPolicy(StrongFocus);
		objButton->setPixmap( QPixmap::fromMimeSource( "wdocument.png" ) );
		connect( objButton,	SIGNAL( clicked() ),
			 this, SLOT( fieldSelect() ) );

		setFocusProxy(objButton);
		layout()->add( objLabel );
		layout()->add( objButton );
		objLabel->show();
		objButton->show();
		break;
		
	case Boolean:
//		connect( checkBox, SIGNAL( lostFocus() ), this, SLOT( focusOutEvent()) );
		connect( checkBox, SIGNAL( valueChanged ( const QString & ) ),
				this, SLOT( setValue( const QString & ) ) );
		
		connect( checkBox, SIGNAL( toggled (bool) ), checkBox, SLOT( on_toggled() ) );
		setFocusProxy(checkBox);
		layout()->add(checkBox);
		checkBox->show();
		break;
		
    default:
		objLabel->setText("UnknownField");
		objLabel->setFrameShape(QFrame::Box);
		setFocusPolicy(NoFocus);
		layout()->add( objLabel );
		objLabel->show();
	break;
    }
	setValue(vValue);
}



/*!
 * \en	Sets property fieldType. \_en
 * \ru 	Устанавливает значение свойства `fieldType'.\_ru
 */
void
wField::setFieldType( QString n )
{
    vFieldType=n;
    if (!loaded)
    {
	    loaded = true;
    }
    //widgetInit();
}


/*!
 * \en	Sets property editorType. \_en
 * \ru 	Устанавливает значение свойства `editorType'.\_ru
 */
void
wField::setEditorType( tEditorType n )
{
    vEditorType=n;
    widgetInit();
}


/*
void
wField::load()
{
}

*/

/*!
 * \en	Creates property editor dialog window. \_en
 * \ru 	Создает окно диалога редактора свойств.\_ru
 * 	\param parent - \en parent \_en \ru родитель \_ru
 */
QDialog*
wField::createEditor( QWidget *parent )
{
    return new eField( parent );
}


/*!
 * \en	Sets value type DateTime. \_en
 * \ru	Устанавливает значения типа DateTime.
 * 	Так как в базе хранится тип DateTime, значение дополняется
 * 	нулевым временем для корректной конвертации и хранении в базе.
 * 	Формат даты в базе данных должен быть ISO. \_ru
 * 	\param newDate (in) - \en date for set \_en \ru Дата для установки \_ru
 */
void
wField::setValue(const QDate& newDate)
{
//CHECK_POINT
	vValue = newDate.toString(Qt::ISODate);
	vValue+="T00:00:00"; //for correct converting to date-time
	emit valueChanged(vValue);
	emit valueChanged(QVariant(vValue));
}



/*!
 * \en 	Sets value. \_en
 * \ru	Устанавливает значение виджета. \_ru
 * 	\param newvalue (in) - \en value for set \_en \ru значение для установки \_ru
 */
void
wField::setValue(const QString &newvalue)
{
    int pos;
    QString  str;
    QDateTime dt;

    switch (vEditorType)
    {
    case Unknown:
	break;
    case Numberic:
    case String:
	vValue = newvalue;
	pos = lineEdit->cursorPosition();
	lineEdit->setText(vValue);
	lineEdit->setCursorPosition(pos);
	break;
    case Date:
    case DateTime:
	// conventering date-time to date, and if new value is NULL set up current locale date.
	// date must be stored in server in format ISO
	 str = newvalue;
	 if(newvalue.isEmpty()) 
	 {
		 str= QDateTime::currentDateTime(Qt::LocalTime).toString(Qt::ISODate);
	 }
	 dt = QDateTime::fromString(str,Qt::ISODate);
	 vValue = dt.toString(Qt::ISODate);
	 dateEdit->setDate(dt.date());
	 break;
    case Catalogue:
    case Document:
	vValue = newvalue;
	objLabel->setText( ananas_objectstr( db, vValue.toULongLong(), md_oid ) );
	break;
    case Boolean:
	vValue = newvalue;
	if(newvalue == "1") 
	{
		checkBox->setChecked(true);
	}
	else 
	{
		checkBox->setChecked(false);
	}
	break;
	//emit valueChanged(QVariant(vValue));

    }
    emit valueChanged(vValue);
    emit valueChanged(QVariant(vValue));
}



/*!
 * \en	Gets value. \_en
 * \ru	Возвращает значение виджета. \_ru
 * 	\return \en value \_en \ru значение виджета \_ru
 */
QString
wField::value() const
{
   QString str = vValue;
   return  str; //str.setUnicode(vValue.unicode(),vValue.length());
}



/*!
 * \en	Gets text value. \_en
 * \ru	Возвращает текстовое значение виджета. \_ru
 * 	\return \en value \_en \ru значение виджета \_ru
 */
QString
wField::text() const
{
   QString str;
	switch (vEditorType)
	{
	case Date:
	case DateTime:
		str = dateEdit->date().toString(Qt::ISODate);
		break;
	case String:
	case Numberic:
		str = lineEdit->text();
		break;
	case Catalogue:
	case Document:
		str = objLabel->text();
		break;
	case Boolean:
		str = checkBox->isChecked()?"1":"0";
		break;
	default:
		str = "";
		break;
	}
	return  str; //str.setUnicode(vValue.unicode(),vValue.length());
}

/*!
 * \en	Calls handler onClick event for Catalogue or Document object. \_en
 * \ru	Вызывает обработчик события onClick для объектов Каталог или Документ. \_ru
 */
void
wField::fieldSelect()
{
	aForm * f = 0;
//    if (!fieldEditor) return;
	switch (vEditorType)
	{
		case Catalogue:
		if ( engine ) 
		{
			int fid = md->getDefaultFormId( md->find( md_oid ), md_action_view);
			if ( !fid )
			{
				engine->openEmbedCatalogueEditor(md_oid,this,true);
				return;
			}
			f = engine->openForm( md_oid, 0, md_action_view, 0, false );
			if ( f ) 
			{
				connect(f, SIGNAL(selected( Q_ULLONG )), this, SLOT(on_selected( Q_ULLONG )));
				f->closeAfterSelect = true;
			}
		}
		else 
		{
			aLog::print(aLog::MT_ERROR, tr("wField::fieldSelect no engine"));
		}
		break;
		case Document:
		if( engine )
		{
			aCfgItem journ  = md->findJournal(1, md->find( md_oid ));
			if( journ.isNull() )
			{
				aLog::print(aLog::MT_DEBUG, tr("wField::fieldSelect special journal not found, used system journal"));
				journ = md->findJournal(0, md->find( md_oid ));
			}
			else
			{
				aLog::print(aLog::MT_DEBUG, tr("wField::fieldSelect found special journal %1 with class %2").arg(md->attr(journ,mda_name)).arg(md->objClass(journ)));
			}
			f =  engine->openForm( md->id(journ), 0, md_action_view, 0, false );
			if( f )
			{
				connect(f, SIGNAL(selected( Q_ULLONG )), this, SLOT(on_selected( Q_ULLONG )));
				f->closeAfterSelect = true;
			}
			
		}
		else
		{
			aLog::print(aLog::MT_ERROR, tr("wField::fieldSelect no engine"));
		}
		break;
		default:
		break;
	}
}




/*!
 * \en	Handler signal lostFocus. \_en
 * \ru	Обработчик сигнала lostFocus. \ru
 */
void
wField::focusInEvent()
{
	switch (vEditorType) {
	case Catalogue:
		objLabel->setLineWidth( 2 );
		break;
	case Document:
		break;
	default:
		break;
    }
//emit(lostFocus());
}


/*!
 * \en	Handler signal lostFocus. \_en
 * \ru	Обработчик сигнала lostFocus. \ru
 */
void
wField::focusOutEvent()
{
	switch (vEditorType) {
	case Catalogue:
		objLabel->setLineWidth( 1 );
		break;
	case Document:
		break;
	default:
		break;
    }
//emit(lostFocus());
}


void
wField::on_selected( Q_ULLONG uid )
{
	setValue( QString::number( uid ) );
	setFocus();
}

void
wField::selectAll()
{
	switch (vEditorType) {
	case Numberic:
	case String:
//		((QLineEdit *) fieldEditor)->home( false );
		lineEdit->selectAll();
		break;
	default:
		break;
    }
}

void
wField::SetReadOnly(bool fl)
{
	switch (vEditorType) {
	case Numberic:
	case String:
		lineEdit->setReadOnly(fl);
		break;
	case Date:
	case DateTime:
		dateEdit->setDisabled(fl);
		break;
	case Catalogue:
		objButton->setDisabled( fl );
		break;
	case Document:
		objButton->setDisabled( fl );
		break;
	case Boolean: 
		checkBox->setDisabled( fl );
		break;
	default:
		break;
    }

}

/*!
 *\~english
 *	Proces value changed.
 *	Proces value changed in fields diferent types.
 *\~russian
 *	Обрабатывает изменение значения.
 *	Обрабатывает изменение значения в поле, вне зависимости от типа поля.
 *\~
 */

wCatButton::wCatButton(const char * caption, QWidget *parent):QPushButton(caption,parent)
{
}

wCatButton::~wCatButton()
{
}

void
wCatButton::keyPressEvent ( QKeyEvent * e )
{
	switch(e->key())
	{
		case Qt::Key_Left:
		case Qt::Key_Up:
		case Qt::Key_Right:
		case Qt::Key_Down:
			e->accept();
			break;
		case Qt::Key_Space:
			e->accept();
			emit( clicked() );
			break;
		case Qt::Key_Tab:
//			printf("press tab\n");
			e->accept();
//<<<<<<< wfield.cpp
			//new QKeyEvent( QEvent::KeyPress, Qt::Key_Return, 10, 0);
			//new QKeyEvent( QEvent::KeyRelease, Qt::Key_Return, 10, 0);
//=======
//>>>>>>> 1.49.2.4
			break;
		default:
			e->ignore();
			break;

	}
}

wCheckBox::wCheckBox(QWidget * parent, const char * name):QCheckBox(parent,name)
{
}

wCheckBox::~wCheckBox()
{
}

void
wCheckBox::on_toggled()
{
//	printf("wCheckBox state is %d\n",this->state());
	if(this->isChecked()) emit(valueChanged("1"));
	else emit(valueChanged("0"));
}


/**
 * \ru 
 * 	\brief Задает значение полю dateEdit запросив его у пользователя.
 * \_ru
 */
void
wField::popupCalendar()
{
	QDate date = PopupCalendar::getDate(
		this, dateEdit->date(),
		dateEdit->mapToGlobal(QPoint(0, dateEdit->height())));
	dateEdit->setDate(date);
	dateEdit->setFocus();
}

/**
 * \ru 
 * 	\brief Запрашивает дату у пользователя, показав ему календарик.
 * 	\return дату, указанную пользователем.
 * \_ru
 */
QDate
PopupCalendar::getDate(QWidget *parent, const QDate &day, QPoint pos)
{
	PopupCalendar *calendar = new PopupCalendar(day, pos, parent);
	calendar->exec();
	QDate date = calendar->day();
	delete calendar;
	return date;
}


/**
 * \ru
 * 	\brief Осуществляет отрисовку календарика, обрабатывая событие PaintEvent виджета PopupCalendar.
 * \_ru
 */
void
PopupCalendar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setClipRegion(event->region());
	painter.setFont(smallFont);
	int w = width();// Ширина окна
	int h = height(); // Высота окна
	int dayw = w / COLS; // Ширина ячейки
	int dayh = h / (ROWS + 2); // Высота ячейки

	QRect rect;
	QColor color = colorGroup().light();
	QColor f_color = "red";
	QColor g_color = "green";
	QColor b_color = "blue";
	// Формируем строку с годом и месяцем
	painter.fillRect(1, 1, dayw - 2, dayh - 1, color);
	painter.drawText(1, 1, dayw - 1, dayh - 1, AlignHCenter, today.toString("<< "), -1, &rect);
	painter.fillRect(dayw, 1, dayw - 2, dayh - 1, color);
	painter.drawText(dayw, 1, dayw - 1, dayh - 1, AlignHCenter, today.toString(" < "), -1, &rect);
	painter.drawText(dayw*2+1, 1, dayw*3- 1, dayh - 1, AlignHCenter, today.toString("MMM, yyyy"), -1, &rect);
	painter.fillRect(w-(dayw*2), 1, dayw - 2, dayh - 1, color);
	painter.drawText(w-(dayw*2), 1, dayw - 1, dayh - 1, AlignHCenter, today.toString(" > "), -1, &rect);
	painter.fillRect(w-dayw, 1, dayw - 2, dayh - 1, color);
	painter.drawText(w-dayw, 1, dayw - 1, dayh - 1, AlignHCenter, today.toString(" >>"), -1, &rect);

// Формируем строку с днями недели
	int i;
	int y = dayh;
	for (i = 0; i < 7; i++) {

		painter.drawText(dayw * i + 1, y, dayw, dayh - 1,
				 AlignHCenter, QDate::shortDayName(i+1), -1, &rect);
	}

	// Заплняем таблицу календаря
	QDate day(today.year(), today.month(), 1);
	int day_pos = day.dayOfWeek()-1;
	day = day.addDays(-day_pos);
	y += dayh;
	for (int j = 0; j < ROWS-1; ++j)
		for (i = 0; i < COLS; ++i) {
		color = (day == today) ? colorGroup().light() : ( ( i < 5 ) ? colorGroup().light() : colorGroup().midlight());
		if (day == today){
			painter.fillRect(dayw * i + 1, dayh * j + y + 1, dayw - 1, dayh - 1, b_color);
			painter.fillRect(dayw * i + 3, dayh * j + y + 3, dayw - 5, dayh - 5, color);
		}else{
			painter.fillRect(dayw * i + 1, dayh * j + y + 1, dayw - 1, dayh - 1, color);
		}
		(today.month() != day.month() )?  painter.setPen(colorGroup().mid()): ( ( i < 5 ) ? painter.setPen(colorGroup().foreground()):painter.setPen(f_color));
		painter.drawText(dayw * i + 2, dayh * j + y + 2, dayw, dayh, AlignTop|AlignHCenter, day.toString("d"));
		day = day.addDays(1);
		}
	// Формируем последнюю строку
		painter.fillRect(1, h - dayh - 1, dayw*2, dayh - 1, b_color);
		painter.fillRect(3, h - dayh + 1, dayw*2-4, dayh - 5, color);
		painter.setPen(colorGroup().foreground());
		painter.drawText(2, h - dayh, dayw*2-2, dayh - 3, AlignTop|AlignHCenter, "Now");
		painter.drawText(w - dayw*3, h - dayh, dayw*3-2, dayh - 1, AlignTop|AlignHCenter, QString(tr("Week: %1").arg(today.weekNumber())));
}

/**
 * \ru
 * 	\brief	Обрабатывает пользовательские действия по выбору даты в календарике.
 * 	
 * 	Записывает значение выбранной пользователем даты в свойство виджета.
 * 
 * \_ru
 */
void
PopupCalendar::keyPressEvent(QKeyEvent *event)
{
	int days = 0;
	switch (event->key()) {
		case Key_Left: days = -1; break;
		case Key_Right: days = 1; break;
		case Key_Up: days = -COLS; break;
		case Key_Down: days = COLS; break;
		case Key_PageUp: days = today.daysTo(today.addMonths(-1)); break;
		case Key_PageDown: days = today.daysTo(today.addMonths(1)); break;
		case Key_Home: days = today.daysTo(today.addYears(-1)); break;
		case Key_End: days = today.daysTo(today.addYears(1)); break;
		case Key_Escape: today = original; accept(); break;
		case Key_Space: // fallthrough
			case Key_Enter: // fallthrough
				case Key_Return: accept(); return;
				default: QDialog::keyPressEvent(event); return;
	}

	QDate day = today.addDays(days);
	if (day != today)
		setDay(day);
}

/**
 * \ru
 * 	\brief	Обрабатывает пользовательские действия мышкой по выбору даты в календарике.
 * 	
 * 	Записывает значение выбранной пользователем даты в свойство виджета.
 * 
 * \_ru
 */
void
PopupCalendar::mousePressEvent(QMouseEvent *event)
{
	QDate day = today;
	int w = width();
	int h = height();
	int dayh2 = (h / (ROWS + 2)) * 2;
	int dayh = h / (ROWS + 2); // Высота строки
	int dayw = w / COLS; // Ширина колонки
	if (event->y() < dayh) {
		if (event->x() > 1 && event->x() < dayw) 		day = day.addYears(-1);
		if (event->x() > dayw && event->x() < dayw*2 ) 	day = day.addMonths(-1);
		if (event->x() > (w - dayw*2) && event->x() < (w - dayw) ) day = day.addMonths(1);
		if (event->x() > (w - dayw) ) day = day.addYears(1);
	} else {
		if (event->y() > dayh2 && event->y() < h - dayh) {
			int xday = event->x() / (width() / (COLS) );
			int yday = (event->y() - dayh2) / ((h - dayh2) / ROWS);
			day = QDate(today.year(), today.month(), 1);
			int day_pos = day.dayOfWeek()-1;
			day = day.addDays(xday + (COLS * yday) - (day_pos));
		}else{
			if (event->x() > 1 && event->x() < dayw*2) {
				day = today.currentDate();
			}
		}
	}
	if (day != today) setDay(day);
}

QSize
PopupCalendar::sizeHint() const
{
	QFontMetrics fm(smallFont);
	return QSize(COLS * (fm.width(tr("Wed"))+2), (ROWS + 2) * fm.height() * 1.2);
}

/**
 * \ru
 * 	\brief	Сеттер задающий дату виджету.
 * 	
 * 	Вызывает перерисовку виджета.
 * 
 * \_ru
 */
void
PopupCalendar::setDay(const QDate &day)
{
	today = day;
	update();
}


/**
 * \ru
 * 	\brief	Конструктор. Инициализирует свойства виджета, задает надпись в шапке виджета.
 * 	
 * \_ru
 */
PopupCalendar::PopupCalendar(const QDate &day, QPoint pos,
			     QWidget *parent, const char *name)
	: QDialog(parent, name), today(day), original(day)
{
	setCaption(tr("A-Calendar"));
	if (!pos.isNull()) move(pos);
	smallFont = font();
	if (smallFont.pointSize() >= 10) {
		smallFont.setPointSize(smallFont.pointSize() - 2);
		smallFont.setBold(true);
	}

	setFixedSize(sizeHint());
	setFocusPolicy(StrongFocus);
}
