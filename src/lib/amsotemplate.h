#ifndef AMSOTEMPLATE_H
#define AMSOTEMPLATE_H

#include <qstring.h>
#include <qptrlist.h>
#include <qvaluestack.h>
#include <qdom.h>

#define open_token "<:"
#define close_token ":>"
#define open_token_section "\\[:"
#define close_token_section ":\\]"
#define PARAM "param"

#include "ananasglobal.h"
#include "itemplate.h"


/**
 * \en
 * Class for work with pattern in Microsoft Office Word 2003 format
 * \_en
 * \ru
 * \brief Класс определяет интерфейс для работы с шаблонами в формате Microsoft Office Word 2003. Наследует iTemplate.
 *
 * Описание шаблона: \n
 * Шаблон представляет собой xml документ для Microsoft Office Word 2003.
 * Он предназначен для того, чтобы быстро создавать отчеты. 
 * Внешне шаблон отличается от того документа, который необходимо сгенерировать 
 * только наличием специальных тегов. 
 * Эти теги при генерации заменяются на конкретные значения. \n
 * Предусмотрено два типа тегов: \n
 * 1) Тег секции \n
 * С помощью него можно размножать строки таблицы. 
 * Для этого надо просто записать его в любую ячейку строки. \n
 * Формат тега [:имя тега:] \n
 * В имени допустимы любые символы. \n
 * При вызове exec() с параметром = имени этого тега к таблице будет добавлена еще
 * одна строка. Если в этой строке есть простые теги, 
 * то произойдет замена тега на значение, заданное с помощью функции setValue() \n
 * 2) Простой тег. \n
 * С помощью него можно вставлять в документ обычный текст, дату, и т.п. \n
 * формат тега <:имя тега:> \n
 * При вызове exec() с параметром = имени этого тега, рядом допишется значение, 
 * предварительно заданное с помощью функции setValue() \n
 * Функция setValue() задает значения для подстановки. 
 * Для прстых тегов надо задавать setValue("param",значение для подстановки);
 * после чего надо выполнить exec(имя простого тега) \n
 * Для тегов секции setValue(имя простого тега, значение для подстановки);
 * после чего выполнить exec(имя секции);
 * \_ru
 */
class  ANANAS_EXPORT aMSOTemplate : public iTemplate
{
	Q_OBJECT
public:

	aMSOTemplate();
	virtual ~aMSOTemplate();

	virtual bool open( const QString &fname );
	virtual void close();
	virtual void clear();
	virtual QString	getValue( const QString &name );
	virtual void setValue( const QString &name, const QString &value );
	virtual QString exec( const QString &sname );
	virtual QString	result();
	virtual bool save( const QString & fname );
	virtual void cleanUpTags();
	virtual void setDir(const QString &dir);
	virtual QString	getDir();

protected:
	QMap<QString,QString> values;
	void searchTags(QDomNode node, const QString &sname );
	virtual bool getNodeTags(QDomNode node, const QString &tagname, bool params );
	void insertRowValues(QDomNode node);
	virtual void insertTagsValues(QDomNode node, const QString &tagName);
	void clearTags(QDomNode node, bool section );
	void clearRow(QDomNode node);
	void clearAttributes(QDomNode n, const QString node, const QString attr);
	int getRowIndex(QDomNode node);

/**
 * \en
 * directory template name
 * \_en
 * \ru
 * �?мя директории шаблонов
 * \_ru
 */	
	QString templateDir;
	
/**
 * \en
 * 	Variable for store unpacking teplate content
 * \_en
 * \ru
 *	Переменная для хранения содержимого распакованного шаблона.
 * \_ru
 */	
	QDomDocument docTpl;
	
	
};

#endif //AMSOTEMPLATE_H