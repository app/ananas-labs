#include "amsotemplate.h"
#include "alog.h"
#include <stdlib.h>
#include <qfile.h>
#include <qdom.h>
#include <qdir.h>
#include <qprocess.h>
#include <qregexp.h>

aMSOTemplate::aMSOTemplate() : iTemplate()
{

}

aMSOTemplate::~aMSOTemplate() 
{
}

/**
 * \en
 * Open pattern.
 * \_en
 * \ru
 * Открывает шаблон.
 * \_ru
 * \param fname \en name of pattern.\_en \ru имя шаблона\_ru
 */
bool
aMSOTemplate::open( const QString &fname )
{
	QString fullFileName= QDir::convertSeparators(templateDir+"/"+fname);
	QFile content( fullFileName );
	if ( content.open( IO_ReadOnly ) )
	{
		docTpl.setContent( &content, false ); 
		content.close();
		aLog::print(aLog::MT_DEBUG, tr("aMSOTemplate: report template '%1' has been read").arg(fullFileName));
		return true;
	}
	else
	{
		aLog::print(aLog::MT_ERROR, tr("aMSOTemplate: can't read report template '%1'").arg(fullFileName));
		return false;
	}		 
}

/**
 * \en
 * Closes pattern. 
 * \_en
 * 
 * \ru
 * Закрывает шаблон.
 * \_ru
 */
void
aMSOTemplate::close()
{
	values.clear();
	docTpl.clear();
}


/**
 * \en
 * clears internal variable.
 * \_en
 * \ru
 * Обнуляет внутренние переменные.
 * \_ru
 */
void
aMSOTemplate::clear()
{
	values.clear();
}


/**
 * \en
 * Returns value parameter `name`
 * \_en
 * \ru
 * Возвращает значение параметра по его имени.
 * \_ru
 *  \param name - \en name of parametr.\_en \ru
 *		  имя параметра\_ru 
 */
QString
aMSOTemplate::getValue( const QString &name )
{
	if(values.find( name )!=values.end())
	{
		return values.find( name ).data();
	}
	else
	{
		aLog::print(aLog::MT_INFO, tr("aMSOTemplate value for field %1 not setted").arg(name));
		return "";
	}
}

/**
 * \en
 * Sets value parameter `name'
 * \_en
 * \ru
 * Устанавливает значение параметра по его имени.
 * \_ru
 *  \param name - \en name of parametr.\_en \ru
 *		  имя параметра\_ru 
 *  \param value - \en value of parametr.\_en \ru
 *		  значение параметра\_ru 
 */
void
aMSOTemplate::setValue( const QString &name, const QString &value )
{
	values[name]=value;
}


/**
 * \en
 * Returns patten
 * \_en
 * \ru
 * Возвращает результат, т.е. шаблон в текстовом виде. Включена в интерфейс временно.
 * \_ru
 */
QString
aMSOTemplate::result()
{
	return docTpl.toString();
}


/**
 * \en
 * Execute replace tags to values. 
 * \_en
 * \ru
 * Выполняет подстановку значения параметра в шаблоне.
 * Есть 2 типа тегов 
 *  \arg обычные теги 
 *  \arg секции - могут находиться ТОЛЬКО в строках таблицы. 

 * Для подстановки значений обычных тегов необходимо выполнить setValue() где name = PARAM (сейчас #define PARAM "param") а value - значение для подстановки. Потом выполнить exec() с параметром = имени тега.
 * Для подстановки секций необходимо з
 адать нужные параметры, используя setValue()
 * а потом выполнить exec() с именем секции. 
 * exec может вызываться нужное число раз как для обычных тегов, так и для секций
 * \_ru
 *  \param sname - \en name of parametr.\_en \ru
 *		  имя параметра\_ru  
 */
QString
aMSOTemplate::exec( const QString &sname )
{
	setValue(sname, getValue(PARAM));
	//search tags in content
	QDomNode n = docTpl.lastChild();
	while( !n.isNull() ) 
	{
		searchTags(n, sname);
		n = n.previousSibling();
	}
	return docTpl.toString();
	
}


/** 
 * \en
 * Added value to end tag with name `sname'. Don't deletes tag. 
 * \_en
 * \ru
 * Рекурсивная функция поиска и замены тегов на их значения в node.
 * Не заменяет теги, а дописывает значения в конец. 
 * Для удаления тэгов используйте функцию cleanUpTags()
 * \_ru
 * \param node - \en context for searching \_en \ru узел, с которого осуществляется поиск. \_ru
 * \param sname - \en tag name \_en \ru имя тега для поиска \_ru
 * \see cleanUpTags() getNodeTags() insertRowValues()
 */
void
aMSOTemplate::searchTags(QDomNode node, const QString &sname )
{
	QDomNode n = node.lastChild();
	while( !n.isNull() )
	{	
		bool res = getNodeTags(n, sname, false);
		if( res ) 
		{
			insertRowValues(n);
		}
		else
		{
			res = getNodeTags(n, sname, true);
			if(res)
			{
				insertTagsValues(n, sname);
			}
			else
			{
				searchTags(n, sname);
			}
		}
		n = n.previousSibling();
	}
}


/**
 * \en
 * Return true, if node contain tag
 * \_en
 * \ru
 * Возвращает истину, когда текст ноды содержит тег с заданным именем.
 * \_en
 * \param node - \en context for searching \_en \ru узел, с которого осуществляется поиск. \_ru
 * \param sname - \en tag name \_en \ru имя тега для поиска \_ru
 * \param params - \en true, if find simple tag and false, if section \_en
 * 		\ru true, если ищется обычный тег и false, если ищется тег секции \_ru
 */
bool
aMSOTemplate::getNodeTags(QDomNode node, const QString &tagname, bool params )
{
  	if(node.isText())
	{
		QString str = node.nodeValue();
		QRegExp re;
		if(params)
		{
			re.setPattern(QString("%1.*%2").arg(open_token).arg(close_token));
		}
		else
		{
			re.setPattern(QString("%1.*%2").arg(open_token_section).arg(close_token_section));	
		}
		re.setMinimal(true);
		int pos = re.search(str,0);
		
		while(pos != -1)
		{
			if(tagname == str.mid(pos+2, re.matchedLength()-4))
			{
				return true;
			}
			pos+= re.matchedLength();
			pos = re.search(str,pos);
		}
		
	}
 return false;	
}


/** 
 * \en
 * insert new row in table and replace tag to value
 * \_en
 * \ru
 * Вставляет новую строку в таблицу, заменяет теги на значения, удаляет тег секции из строки таблицы.
 * Выполняет рекурсивный поиск узла, содержащего строку таблицы. У этого узла есть
 * специальное имя(w:r), которое распознается функцией. После того, как узел найден, строка строка дублируется, 
 * а из текущей строки удаляются все теги секции, чтобы избежать мнократного размножения строк таблицы.
 * \_ru
 * \param node - \en context for inserting \_en \ru узел, в который происходит вставка \_ru 
 * \see searchTags()
 */
void 
aMSOTemplate::insertRowValues(QDomNode node)
{
	QDomNode n = node;
	while(!n.parentNode().isNull())
	{
		n = n.parentNode();
		QDomElement e = n.toElement();
		if( n.nodeName()=="Row" ) 
		{	
			QDomAttr a = n.toElement().attributeNode( "ss:Index" );
			n.parentNode().insertAfter(n.cloneNode(true),n);
			clearTags(n,true);
			
			QMap<QString,QString>::Iterator it;
			for ( it = values.begin(); it != values.end(); ++it )
			{
				searchTags(n,it.key());
			}
			int rowIndex = a.value().toInt();
			if (rowIndex == 0) 
			{
				rowIndex = getRowIndex(n);
				n.toElement().setAttribute("ss:Index",rowIndex);	
			}
			n.nextSibling().toElement().setAttribute("ss:Index",rowIndex+1);	
		}
	}
}


/**
 * \en
 * Addes to tag value of parametr \a tagName
* \_en
 * \ru
 * Добавляет к тегу значение параметра \a tagName. После вызова этой функции тег не исчезает,
 * и к нему можно добавить еще значения, которые добавятся к концу текста, содержащего тег.
 * \_ru
 * \param node - \en context \_en \ru узел к которому добавляется значение \_ru
 * \param sname - \en tag name \_en \ru имя тега \_ru
 */
void 
aMSOTemplate::insertTagsValues(QDomNode node, const QString &tagName)
{
	QDomNode n = node;
	//old vers.
	//n.setNodeValue(n.nodeValue()+getValue(tagName));
	QString s = n.nodeValue(), tag = QString("%1%2%3").arg(open_token).arg(tagName).arg(close_token);
	s.replace(tag, QString("%1%2").arg(tag).arg(getValue(tagName)));
	n.setNodeValue(s);	
}

/**
 * \en
 * Deletes tags from \a node
 * \_en
 * \ru
 * Удаляет рекурсивно теги из \a node.
 * \_ru
 * \param node - \en context \_en \ru узел из которого нужно удалить теги \_ru
 * \param section - \ru true, если надо удалить тег секции \_ru
 */
void
aMSOTemplate::clearTags(QDomNode node, bool section )
{
	if(node.isNull()) return;
	
	QDomNode n = node.lastChild();
	while( !n.isNull() )
	{	
		if(n.isText())
		{
			QString str = n.nodeValue();
			QRegExp re;
			if(section)
			{
				re.setPattern(QString("%1.*%2").arg(open_token_section).arg(close_token_section));
			}
			else
			{
				re.setPattern(QString("%1.*%2").arg(open_token).arg(close_token));
			}
			re.setMinimal(true);
			int pos = re.search(str,0);
		
			while(pos != -1)
			{
				str = str.remove(re);
				pos = re.search(str,0);
			}
			n.setNodeValue(str);			
		}
		else
		{
			clearTags(n,section);
		}
		n = n.previousSibling();
	}	
}

/**
 * \en
 * Deletes row, having section tag
 * \_en
 * \ru
 * Рекурсивная функция. Удаляет строки, содержащие тег секции
 * \_ru
* \param node - \en context \_en \ru узел из которого нужно удалить строки \_ru
 */
void
aMSOTemplate::clearRow(QDomNode node)
{
QDomNode n = node.lastChild();
	while( !n.isNull() )
	{	
		if(n.isText())
		{
			QString str = n.nodeValue();
			QRegExp re;
			re.setPattern(QString("%1.*%2").arg(open_token_section).arg(close_token_section));
			re.setMinimal(true);
			int pos = re.search(str,0);
			if(pos!=-1)
			{
				QDomNode tmp = n;
				while(!tmp.parentNode().isNull())
				{
					tmp = tmp.parentNode();
					if( tmp.nodeName()=="Row" ) 
					{
						tmp.parentNode().removeChild(tmp);
						break;
					}
				}
			}
		}
		else
		{
			clearRow(n);
		}
		n = n.previousSibling();
	}	
}


/**
 * \en
 * clears all tags from pattern
 * \_en
 * \ru
 * Удаляет все теги из документа, а также строки, в которых содержится тег секции
 * \_ru
 */
void
aMSOTemplate::cleanUpTags()
{
	QDomNode n = docTpl.lastChild();
	while( !n.isNull() ) 
	{
		clearTags(n,false);
		//clearRow(n);
		n = n.previousSibling();
	}
	n = docTpl.lastChild();
	while( !n.isNull() ) 
	{
		//clearTags(n,false);
		clearRow(n);
		n = n.previousSibling();
	}
	n = docTpl.lastChild();
	while (!n.isNull())
	{
		clearAttributes(n, "Table", "ss:ExpandedRowCount");
		n = n.previousSibling();
	}
	
}


/**
 * \en
 * Deletes from node attribute
 * \_en
 * \ru
 * Рекурсивная функция. Удаляет из узла атрибут
 * \_ru
* \param node - \en context \_en \ru узел из которого нужно удалить атрибут \_ru
* \param nodename - \en node name \_en \ru имя узла \_ru
* \param attr - \en attribut name \_en \ru имя атрибута,который нужно удалить \_ru
 */
void
aMSOTemplate::clearAttributes(QDomNode node, const QString nodename, const QString attr)
{
	QDomNode n = node.lastChild();
	while( !n.isNull() )
	{
		if( n.parentNode().nodeName()==nodename ) 
		{	
			n.parentNode().toElement().removeAttribute(attr);		
			break;
		}	
		else
		{
			clearAttributes(n, nodename, attr);
		}
		n = n.previousSibling();
	}
}

/**
 * \en
 * Save pattern
 * \_en
 * \ru
 * Сохраняет шаблон в файл с заданным именем. Перед сохранением необходимо выполнить функцию cleanUpTags() чтобы удалить тэги из сохраняемого документа.
 * \_ru
 */
bool
aMSOTemplate::save( const QString & fname)
{
	QFile fContent( QDir::convertSeparators(fname) );
	if( !fContent.open( IO_WriteOnly ) ) 
	{
		aLog::print(aLog::MT_ERROR, tr("aMSOTemplate save %1 open for write").arg(fContent.name()));
		return false;
	}
	QTextStream stream4content(&fContent);
	docTpl.save(stream4content,2);
	fContent.close();	
	return true;	
}


/**
 * \en
 * clears all tags from pattern
 * \_en
 * \ru
 * Сохраняет в переменную template расположение шаблона
 * \_ru
 * \param dir - \en The catalogue in which is a pattern \_en \ru Каталог в котором находится шаблон \_ru
 */
void
aMSOTemplate::setDir(const QString &dir)
{
	templateDir = dir;
}

/**
 * \en
 * The catalogue for storage of time files of the report
 * \_en
 * \ru
 * Каталог для хранения временных файлов отчета
 * \_ru
 */
QString
aMSOTemplate::getDir()
{
	QString homeDir = QString("%1").arg(QDir::convertSeparators(QDir::homeDirPath ()));
#ifdef Q_OS_WIN32
	if(homeDir.right(1)!="\\") homeDir.append("\\");
#else
	
	if(homeDir.right(1)!="/") homeDir.append("/");
#endif
	return QDir::convertSeparators(homeDir);
}


/**
 * \en
 * Defines number of a line in a pattern
 * \_en
 * \ru
 * Определяет номер строки в шаблоне
 * \_ru
 * \param node - \en context \_en \ru узел Row для которого определяется индекс \_ru
 */
int
aMSOTemplate::getRowIndex(QDomNode node) 
{
	QDomNode n = node;
	int i = 0;
	while( n.nodeName()=="Row")
	{
		++i;
		n = n.previousSibling();
	}
	return i;
}
