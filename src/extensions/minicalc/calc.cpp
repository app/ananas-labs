#include "calc.h"

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
aCalc::aCalc(): AExtension("Calc")
{
	QDate date = QDate::currentDate();
	calcInstance = new MiniCalc();
}

