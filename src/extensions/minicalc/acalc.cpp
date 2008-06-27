#include "acalc.h"

/**
 *\en
 *	\brief 
 * 
 *\_en
 *\ru
 *	\brief 
 * 
 *\_ru
 */
aCalc::aCalc(): AExtension("Calc")
{
	calcInstance = new MiniCalc();
}

/**
 *\en
 *	\brief Destructor
 *\_en
 *\ru
 *	\brief Деструктор
 *\_ru
 */
aCalc::~aCalc()
{
	if (calcInstance) {
		delete calcInstance;
		calcInstance = 0;
	}
}


/**
 *\en
 *	\brief Destructor
 *\_en
 *\ru
 *	\brief Деструктор
 *\_ru
 */
void
aCalc::Show()
{
	if ( calcInstance ) 
	{
		calcInstance->show();
	}
}


#include <aextensionplugin.h>
typedef AExtensionPlugin<aCalc> aCalcPlugin;
A_EXPORT_PLUGIN( aCalcPlugin )
