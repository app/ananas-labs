/****************************************************************************
** $Id: adateservice.cpp,v 1.3 2008/05/22 08:55:05 app Exp $
**
** Header file of Ananas project
* 
** Copyright (C) 2008 Andrey Paskal.
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

#include	"adateservice.h"


/**
 *\en
 *	\brief Constructor that create object aDateService for use in ananas script.
 * 
 * 	Constructs current date object. 
 *\_en
 *\ru
 *	\brief Конструктор, который создает aDateService для работы в ананас скрипте.
 * 
 * 	Создается объект с текущей датой.
 *\_ru
 */
aDateService::aDateService(): AExtension("DateService")
{
	QDate date = QDate::currentDate();
	dateInstance = new QDate( date.year(), date.month(), date.day());
}

/**
 *\en
 *	\brief Constructor that create object aDateService for use in ananas script.
 *\_en
 *\ru
 *	\brief Конструктор, который создает aDateService для работы в ананас скрипте.
 *\_ru
 */
aDateService::aDateService( int y, int m, int d ): AExtension("DateService")
{
	dateInstance = new QDate(y,m,d);	
}


/**
 *\en
 *	\brief Constructor that create object aDateService for use in ananas script.
 *\_en
 *\ru
 *	\brief Конструктор, который создает aDateService для работы в ананас скрипте.
 *\_ru
 */
aDateService::aDateService(const aDateService& d): AExtension("DateService")
{
	dateInstance = new QDate( d.Year(), d.Month(), d.Day() );	
}


/**
 *\en
 *	\brief Constructor that create object aDateService for use in ananas script.
 *\_en
 *\ru
 *	\brief Конструктор, который создает aDateService для работы в ананас скрипте.
 *\_ru
 */
aDateService::aDateService(const QDate& d): AExtension("DateService")
{
	dateInstance = new QDate( d.year(), d.month(), d.day() );	
}



/**
 *\en
 *	\brief Destructor
 *\_en
 *\ru
 *	\brief Деструктор
 *\_ru
 */
aDateService::~aDateService()
{
	if (dateInstance) {
		delete dateInstance;
		dateInstance = 0;
	}
}

/**
 *\en
 *	\brief Returns TRUE if the date is null; otherwise returns FALSE. A null date is invalid.  
 *\_en
 *\ru
 *	\brief Returns TRUE if the date is null; otherwise returns FALSE. A null date is invalid.  
 *\_ru
 */
bool aDateService::IsNull () const
{
	return dateInstance->isNull();	
};


/**
 *\en
 * 	\brief Returns TRUE if this date is valid; otherwise returns FALSE. 
 *\_en
 *\ru
 * 	\brief Returns TRUE if this date is valid; otherwise returns FALSE. 
 *\_ru
 */
bool aDateService::IsValid () const
{
	return dateInstance->isValid() ;	
};


/**
 *\en
 * 	\brief Returns TRUE if the specified date (year y, month m and day d) is valid; otherwise returns FALSE.
 *\_en
 *\ru
 * 	\brief Returns TRUE if the specified date (year y, month m and day d) is valid; otherwise returns FALSE.
 *\_ru
 */
bool aDateService::IsValid (int y, int m, int d)
{
	return QDate::isValid(y, m, d) ;	
};


/**
 *\en
 * 	\brief Returns the year (1752..8000) of this date. 
 *\_en
 *\ru
 * 	\brief Returns the year (1752..8000) of this date. 
 *\_ru
 */
int
aDateService::Year () const
{
	return dateInstance->year() ;	
};



/**
 *\en
 * 	\brief Returns the month (January=1..December=12) of this date.
 *\_en
 *\ru
 * 	\brief Returns the month (January=1..December=12) of this date.
 *\_ru
 */
int
aDateService::Month () const
{
	return dateInstance->month() ;	
};

/**
 *\en
 * 	\brief Returns the day of the month (1..31) of this date.
 *\_en
 *\ru
 * 	\brief Returns the day of the month (1..31) of this date.
 *\_ru
 */
int
aDateService::Day () const
{
	return dateInstance->day() ;	
};

/**
 *\en
 * 	\brief Returns the weekday (Monday=1..Sunday=7) for this date. 
 *\_en
 *\ru
 * 	\brief Returns the weekday (Monday=1..Sunday=7) for this date.
 *\_ru
 */
int
aDateService::DayOfWeek () const
{
	return dateInstance->dayOfWeek() ;	
};

/**
 *\en
 * 	\brief Returns the day of the year (1..365) for this date. 
 *\_en
 *\ru
 * 	\brief Returns the day of the year (1..365) for this date.
 *\_ru
 */
int
aDateService::DayOfYear () const
{
	return dateInstance->dayOfYear() ;	
};

/**
 *\en
 * 	\brief Returns the number of days in the month (28..31) for this date. 
 *\_en
 *\ru
 * 	\brief Returns the number of days in the month (28..31) for this date.
 *\_ru
 */
int
aDateService::DaysInMonth () const
{
	return dateInstance->daysInMonth() ;	
};

/**
 *\en
 * 	\brief Returns the number of days in the year (365 or 366) for this date. 
 *\_en
 *\ru
 * 	\brief Returns the number of days in the year (365 or 366) for this date. 
 *\_ru
 */
int
aDateService::DaysInYear () const
{
	return dateInstance->daysInYear() ;	
};

/**
 *\en
 * 	\brief Returns the week number (1 to 53) for this date.
 * 
 * 	In accordance with ISO 8601, weeks start on Monday and the first Thursday 
 * 	of a year is always in week 1 of that year. Most years have 52 weeks, but some have 53. 
 *\_en
 *\ru
 * 	\brief Returns the week number (1 to 53) for this date.
 * 
 * 	In accordance with ISO 8601, weeks start on Monday and the first Thursday 
 * 	of a year is always in week 1 of that year. Most years have 52 weeks, but some have 53. 
 *\_ru
 */
int
aDateService::WeekNumber () const
{
	return dateInstance->weekNumber( ) ;	
};

/**
 *\en
 * 	\brief Returns the date as a string. The format parameter determines the format of the result string.
 * 
 * 	These expressions may be used: 
 * 	d - the day as number without a leading zero (1-31) 
 * 	dd - the day as number with a leading zero (01-31) 
 * 	ddd - the abbreviated localized day name (e.g. 'Mon'..'Sun'). 
 * 	dddd - the long localized day name (e.g. 'Monday'..'Sunday').
 * 	M - the month as number without a leading zero (1-12)
 * 	MM - the month as number with a leading zero (01-12)
 * 	MMM - the abbreviated localized month name (e.g. 'Jan'..'Dec').
 * 	MMMM - the long localized month name (e.g. 'January'..'December').
 * 	yy - the year as two digit number (00-99).
 * 	yyyy - the year as four digit number (1752-8000) 
 * 
 * 	Example format strings (assuming that the Date is the 20th July 1969): 
 * 	
 *	Format  dd.MM.yyyy 
 *	Result  20.07.1969 
 *	Format ddd MMMM d yy 
 *	Result Sun July 20 69 
 *
 *\_en
 *\ru
 * 	\brief Возвращает дату в виде строки. 
 * 
 * 	Формат даты задается параметром. Если параметр не задан, дата возвращается в формате dd.MM.yyyy
 * 
 * 	Для задания формата даты могут быть использованы следующие наборы символов: 
 * 	d - the day as number without a leading zero (1-31) 
 * 	dd - the day as number with a leading zero (01-31) 
 * 	ddd - the abbreviated localized day name (e.g. 'Mon'..'Sun'). 
 * 	dddd - the long localized day name (e.g. 'Monday'..'Sunday').
 * 	M - the month as number without a leading zero (1-12)
 * 	MM - the month as number with a leading zero (01-12)
 * 	MMM - the abbreviated localized month name (e.g. 'Jan'..'Dec').
 * 	MMMM - the long localized month name (e.g. 'January'..'December').
 * 	yy - the year as two digit number (00-99).
 * 	yyyy - the year as four digit number (1752-8000) 
 * 
 * 	Example format strings (assuming that the Date is the 20th July 1969): 
 * 	
 *	Format  dd.MM.yyyy 
 *	Result  20.07.1969 
 *	Format ddd MMMM d yy 
 *	Result Sun July 20 69 
 *\_ru
 */
QString
aDateService::ToString (const QString & format ) const
{
	if ( !format || format && format.isNull() )
	{
		return dateInstance->toString( "dd.MM.yyyy" ) ;
	}
	return dateInstance->toString( format ) ;
};


/**
 *\en
 *\_en
 *\ru
 * 	\brief Возвращает представление даты в объекте сласса QDate. 
 *\_ru
 */
QDate
aDateService::ToDate () const
{
	QDate result( Year(), Month(), Day() );
	return result;
};


/**
 *\en
 * 	\brief Sets the date's year y, month m and day d. 
 * 
 * 	y must be in the range 1752..8000, m must be in the range 1..12, and d must be in the range 1..31. 
 * 	Warning: If y is in the range 0..99, it is interpreted as 1900..1999. 
 * 	\return TRUE if the date is valid; otherwise returns FALSE. 
 *\_en
 *\ru
 * 	\brief Sets the date's year y, month m and day d. 
 * 
 * 	y must be in the range 1752..8000, m must be in the range 1..12, and d must be in the range 1..31. 
 * 	Warning: If y is in the range 0..99, it is interpreted as 1900..1999. 
 * 	\return TRUE if the date is valid; otherwise returns FALSE. 
 *\_ru
 */
bool 
aDateService::SetYMD ( int y, int m, int d )
{
	return dateInstance->setYMD( y, m, d ) ;	
}

/**
 *\en
 * 	\brief Returns a aDateService object containing a date ndays later than the 
 * 	date of this object (or earlier if ndays is negative). 
 *\_en
 *\ru
 * 	\brief Returns a aDateService object containing a date ndays later than the 
 * 	date of this object (or earlier if ndays is negative). 
 *\_ru
 */
aDateService*
aDateService::AddDays ( int ndays ) const
{
	QDate		currentDate( Year(), Month(), Day() );
	aDateService*	result = new aDateService( currentDate.addDays( ndays ) );

	return result;
}	


/**
 *\en
 * 	\brief Returns a aDateService object containing a date nmonths later than the 
 * 	date of this object (or earlier if nmonths is negative). 
 *\_en
 *\ru
 * 	\brief Returns a aDateService object containing a date nmonths later than the 
 * 	date of this object (or earlier if nmonths is negative). 
 *\_ru
 */
aDateService*
aDateService::AddMonths ( int nmonths ) const
{
	QDate		currentDate( Year(), Month(), Day() );
	aDateService*	result = new aDateService( currentDate.addMonths( nmonths ) );

	return result;
}	


/**
 *\en
 * 	\brief Returns a aDateService object containing a date nyears later than the date of 
 * 	this object (or earlier if nyears is negative). 
 *\_en
 *\ru
 * 	\brief Возвращает объект класса aDateService содержащий дату на nyears лет позднее хранимой
 * 	в объекте даты (или ранее, если nyears меньше нуля).
 *\_ru
 */
aDateService*
aDateService::AddYears ( int nyears ) const
{
	QDate		currentDate( Year(), Month(), Day() );
	aDateService*	result = new aDateService( currentDate.addYears( nyears ) );

	return result;
}	


/**
 *\en
 * 	\brief Returns the number of days from this date to target (which is negative 
 * 	if target is earlier than this date). 
 *\_en
 * 	\brief Возвращает количество дней до указанной даты от даты, представленной объектом.
 * 
 * 	Возвращаемое значение может быть отрицательным, если указанная дата находится в прошлом по 
 * 	отношению к дате, представленной объектом.
 *\_ru
 */
int 		
aDateService::DaysTo ( const aDateService& target ) const
{
	QDate currentDate( Year(), Month(), Day() );
	QDate targetDate( target.Year(), target.Month(), target.Day() );
	return currentDate.daysTo( targetDate ) ;
}


/**
 *\en
 * 	\brief Returns the number of days from this date to target (which is negative 
 * 	if target is earlier than this date). 
 *\_en
 * 	\brief Возвращает количество дней до указанной даты от даты, представленной объектом.
 * 
 * 	Возвращаемое значение может быть отрицательным, если указанная дата находится в прошлом по 
 * 	отношению к дате, представленной объектом.
 *\_ru
 */
int 		
aDateService::DaysTo ( const QDate& target )  const
{
	QDate currentDate( Year(), Month(), Day() );
	return currentDate.daysTo( target ) ;
}


#include <aextensionplugin.h>
typedef AExtensionPlugin<aDateService> aDateServicePlugin;
A_EXPORT_PLUGIN( aDateServicePlugin )






