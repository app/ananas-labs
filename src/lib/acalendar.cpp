/****************************************************************************
** $Id: acalendar.dkr,v 1.73 2008/06/09 11:45:27 app Exp $
**
**********************************************************************/

#include <qlineedit.h>
#include <qlayout.h>
#include <qdom.h>
#include <qvalidator.h>
#include <qlabel.h>
#include <qsizepolicy.h>
#include <qevent.h>
#include <qpainter.h>

#include "ananas.h"
#include "alog.h"
#include "acalendar.h"


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
		if (event->x() > 1 && event->x() < dayw) day = day.addYears(-1);
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

/**
 * \ru
 * 	\brief	Обрабатывает двойной клик мышкой в календарике.
 *
 * 	Записывает значение выбранной пользователем даты в свойство виджета.
 *
 * \_ru
 */
void
PopupCalendar::mouseDoubleClickEvent(QMouseEvent *event)
{
	QDate day = today;
	int w = width();
	int h = height();
	int dayh2 = (h / (ROWS + 2)) * 2;
	int dayh = h / (ROWS + 2); // Высота строки
	int dayw = w / COLS; // Ширина колонки

	if (event->y() > dayh2 && event->y() < h - dayh) {
		int xday = event->x() / (width() / (COLS) );
		int yday = (event->y() - dayh2) / ((h - dayh2) / ROWS);
		day = QDate(today.year(), today.month(), 1);
		int day_pos = day.dayOfWeek()-1;
		day = day.addDays(xday + (COLS * yday) - (day_pos));
		if (day != today) setDay(day);
		accept();
	}
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
