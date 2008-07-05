/****************************************************************************
** $Id: acalendar.h,v 1.2 2008/07/05 12:43:48 app Exp $
**
** Copyright (C) 2008 Dmitry Kruglikov (dkr)
** Copyright (C) 2008 Ananas Project 
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
**
**********************************************************************/

#ifndef CALENDAR_H
#define CALENDAR_H

#include <qwidget.h>
#include <qwidgetplugin.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include "ananas.h"

/*!
 * \en PopupCalendar for DateEdit field editor. \_en
 * \ru
 * 	\brief Всплывающий календарь для выбора даты.
 *
 * 	Используется как дополнение к виджету поля ввода/редактирования
 * 	атрибута типа Дата бизнес объекта Ананаса.
 *
 * \_ru
 */
class PopupCalendar : public QDialog
{
Q_OBJECT
public:
	PopupCalendar(const QDate &day = QDate::currentDate(),
		QPoint pos = QPoint(), QWidget *parent = 0, const char *name = 0);

	static QDate	getDate(QWidget *parent = 0, const QDate &day = QDate::currentDate(),
	QPoint		pos = QPoint());

	const QDate&	day() const { return today; }
	void		setDay(const QDate &day);
	QSize		sizeHint() const;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void paintEvent(QPaintEvent *event);

private:
	enum { ROWS = 7, COLS = 7 };
	QFont smallFont;
	QDate today;
	const QDate original;
};

#endif
