/****************************************************************************
** $Id: acalendar.h,v 1.37 2008/06/09 11:44:27 dkr Exp $
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
