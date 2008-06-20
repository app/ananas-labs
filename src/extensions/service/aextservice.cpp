#include "aservice.h"
#include "aextservice.h"
#include <quuid.h>

aExtSERVICE::aExtSERVICE()
	: AExtension("Service")
{
}

aExtSERVICE::~aExtSERVICE()
{
}


/**
 * \en
 * Defines what office (Microsoft Office или Open office) it is used by default for creation of reports
 * \_en
 * \ru
 * определяет какой офис(Microsoft Office или Open office) используется по-умолчанию для создания отчетов
  * \code
 *  var defOffice = (new Service).GetOffice();
 *  sysMessage (0, defOffice);
 *  возвращает строку:
 *  	"MSO" - Microsoft Office
 *  	"OOO" - Open Office
 * \endcode
 * \_ru
 */
QString aExtSERVICE::GetOffice() const
{
#ifdef Q_OS_WIN32
	bool ok;
	QString office = aService::readConfigVariable("defaultOffice", &ok);
	if (ok)
		return office;
	else
		return "";
#else
	return "";
#endif	
}


/**
 * \en
 * 	Class for generate GUID strings from Ananas Script. Linux only !!!
 * \_en
 * \ru
 * Генерирует строку GUID (глобально-уникального идентификатора, Globally Unique IDentifier).
 * Только в Linux версиях. В Windows возвращает 00000000-0000-... (Для Qt3.2)
 *
 * GUID представляет собой 128-битное значение, уникальное для всех практических целей.
 * 	\brief Генерирует строку GUID в верхнем регистре.
 *
 * 	Пример использования функции Generate()
 * \code
 *  var newGUID = (new Service).Generate();
 *  sysMessage (0, newGUID);
 *  возвращает строку вида {FC98E407-B3F7-4914-A2B1-36B4C2A93228}
 *
 *  Для преобразования в нижний регистр необходимо использовать
 *  newGUID.toLowerCase();
 * \endcode
 *
 * \_ru
 */
QString aExtSERVICE::Generate() const
{
	
#ifdef Q_OS_WIN32
	return QUuid().toString();
#else
	return QUuid::createUuid().toString().upper();
#endif
}


#include <aextensionplugin.h>
typedef AExtensionPlugin<aExtSERVICE> aExtSERVICEPlugin;
A_EXPORT_PLUGIN( aExtSERVICEPlugin )
