/****************************************************************************
** $Id: adateservice.h,v 1.4 2008/05/24 13:12:33 app Exp $
**
** Header file of Ananas project
**
** Copyright (C) 2008. Andrey Paskal
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
**********************************************************************/

#ifndef ADATESERVICE_H
#define ADATESERVICE_H

#include	<qdatetime.h> 
#include 	"aextension.h"

/**
 *\en
 *\_en
 *\ru
 *	\brief Сервисный класс для операций с датами.
 * 
 * 	По сути, предоставляет доступ из Ананас-Скрипта к методам объекта QDate.
 * 	Предоставляет удобные методы для определения количества дней между двумя любыми датами,
 * 	вычисления даты прибавлением количества дней к исходной дате.
 *\_ru
 */
class ANANAS_EXPORT aDateService : public AExtension
{
	Q_OBJECT
public: 		
	aDateService();
	aDateService( int y, int m, int d );
	aDateService(const aDateService&);
	aDateService(const QDate&);
	~aDateService();
protected:
	QDate *dateInstance;
public slots:
	

	bool IsNull () const;
	bool IsValid () const;
	bool IsValid ( int y, int m, int d ) ;
	int Year ()  const ;
	int Month () const ;
	int Day () const ;
	int DayOfWeek () const ;
	int DayOfYear () const ;
	int DaysInMonth () const ;
	int DaysInYear () const ;
	int WeekNumber () const ;
	QString 	ToString ( const QString & format = QString::null)  const;
	QDate	 	ToDate ()  const;
	bool 		SetYMD ( int y, int m, int d ) ;
	aDateService*	AddDays ( int ndays ) const ;
	aDateService* 	AddMonths ( int nmonths ) const; 
	aDateService* 	AddYears ( int nyears ) const; 
	int 		DaysTo ( const aDateService& target) const ; 
	int 		DaysTo ( const QDate& target ) const ; 
	
};

#endif// ADATESERVICE_H
