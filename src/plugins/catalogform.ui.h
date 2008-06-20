/****************************************************************************
** $Id: catalogform.ui.h,v 1.39 2007/05/26 19:01:10 leader Exp $
**
** Catalogue metadata object implementation file of
** Ananas application library
**
** Created : 20031201
**
** Copyright (C) 2003-2005 Grigory Panov <gr1313 at mail.ru>, Yoshkar-Ola.
**
** This file is part of the Designer application of the Ananas 
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
** See http://www.leaderit.ru/page=ananas or email sales@leaderit.ru
** See http://www.leaderit.ru/gpl/ for GPL licensing information.
**
** Contact org@leaderit.ru if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/
/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

/*!
 * \return id selected element
 */
Q_ULLONG
CatalogForm::getId()
{
    return id;
}

/*!
 * Function set initial data. Adds one element in each group.
 * \param catalog (in) - object catalog for edit or select.
 * \param mg (in) - map of catalog groups. Key - group id. 
 * \param Fname (in) - list of field names of elements. 
 * \param FnameGroup (in) - list of field names of groups.
 */
void 
CatalogForm::setData( aCatalogue* catalog,
   QMap<Q_ULLONG, QListViewItem*> mg, 
   //QMap<Q_ULLONG, bool> map_d,
   const QStringList & Fname, 
   const QStringList & FnameGroup,
   Q_ULLONG idElForm,
   Q_ULLONG idGrForm,
   const bool toSelect)
{
	ListView->setDestination(toSelect);
	aLog::print(aLog::MT_DEBUG, tr("CatalogForm:setData begin"));
	QListViewItem* item;
	uint i;
	QPixmap pixmap(getElementPixmap());
	QPixmap pixmap_mark_deleted(getMarkDeletedPixmap());
	idElementForm = idElForm;
	idGroupForm = idGrForm;
	cat = catalog;
	fieldName= Fname[0];
	fieldList= Fname;
	fieldListGroup = FnameGroup;
	map_gr = mg;
	ListView->setAllColumnsShowFocus ( true );
	QMap<Q_ULLONG, QListViewItem *>::Iterator it = map_gr.begin();
	cat->Select();
  	// added one element in each group 
	while(it!=map_gr.end())
	{
		cat->selectByGroup(it.key());// select elements in each group
		if(cat->First()) // if group have elements 
		{
			item = new QListViewItem(map_gr[it.key()]);
			aLog::print(aLog::MT_DEBUG, tr("CatalogForm add first element in group"));
			//printf("add first element in group\n");
			if(cat->isElementMarkDeleted())
				item->setPixmap(0,pixmap_mark_deleted);
			else
				item->setPixmap(0,pixmap);
			for(i=0; i<fieldList.count(); i++)
			{
				item->setText(i,cat->sysValue(fieldList[i]).toString());
			}
			 map_el.insert(cat->sysValue("id").toULongLong(),item);
		} 
	 ++it;
	}

	cat->selectByGroup(0);// select elements without group
	if(cat->First())
	{
		
		aLog::print(aLog::MT_DEBUG, tr("CatalogForm add elements into root"));
		do
		{
			item = new QListViewItem(ListView);
			if(cat->isElementMarkDeleted())
				item->setPixmap(0,pixmap_mark_deleted);
			else
				item->setPixmap(0,pixmap);
			for(i=0; i<fieldList.count(); i++)
			{
				item->setText(i,cat->sysValue(fieldList[i]).toString());
			}
			map_el.insert(cat->sysValue("id").toULongLong(),item);
			
		}while(cat->Next());
	}
	cat->Select();
	setGeometry(aService::loadSizeFromConfig(QString("%1_embedded editor").arg(cat->md->attr(cat->obj, mda_name))));
	ListView->setSelected(ListView->firstChild(),true);
	aLog::print(aLog::MT_DEBUG, tr("CatalogForm init"));
}

/*!
 * Function set id, returned getId().
 * \param idx (in) - id. 
 */
void 
CatalogForm::setId(Q_ULLONG idx )
{
	id = idx;
}

/*! Function search string s in table of elements and show list founding lines.
 * Searching for length s >= constant LENGTH_NO_FIND.
 * Displaing <= VISIBLE_ROWS lines.
 * \param s (in) - string for search.
 */
void 
CatalogForm::find(const QString& s )
{
	int count=0;//,rows=0;
	bool ok;
	int tmp = aService::readConfigVariable("LengthAboveFind",&ok).toInt();
	if(!ok) tmp = 3;
	const int LENGTH_NO_FIND = tmp;

	tmp = aService::readConfigVariable("VisibleRows",&ok).toInt();
	if(!ok) tmp = 50;
   
	const int VISIBLE_ROWS = tmp;
  
	setId(0);
	ListHint->clear();
	if(s.length()>=LENGTH_NO_FIND) // show list hint
	{
		if(!ListHint->isVisible())
		{
			ListHint->show(LineEdit, StatusFrame);
			StatusFrame->show();
		}
	
		cat->select(fieldName + " like '%"+s+"%'");// AND df<>'1'");
		if(cat->First())
		{
			do
			{
				if(count++<VISIBLE_ROWS)
				{
		   		 	ListHint->insertItem(cat->sysValue(fieldName).toString(), cat->sysValue("id").toInt());
				}
			} while(cat->Next());
		}
		if(!ListHint->count()) // don't show empty list
		{
			ListHint->hide();
			StatusFrame->hide();
		
		}
		else
		{
			StatusFrame->repaint();
			StatusFrame->drawText(	5, StatusFrame->size().height()-3, QString(tr("displaying %1 from %2")).arg(ListHint->count()).arg(count) );
		}
			
	}
	else // length < LENGTH_NO_FIND, don't show list hint
	{
		if(ListHint->isVisible())
		{
			ListHint->hide();
			StatusFrame->hide();
		}
	}
	    
}

/*! 
 * Handler signal press arrow for line edit
 */
void 
CatalogForm::pressArrow()
{
	
	if(ListHint->isVisible())
	{
		ListHint->setFocus();
		ListHint->setSelected(ListHint->currentItem(),true);

	}
	else
	{
		find(LineEdit->text());
		if(ListHint->isVisible())
		{
			ListHint->setFocus();
			ListHint->setSelected(ListHint->currentItem(),true);
		}
		 
	}
}


void 
CatalogForm::isPressArrow()
{

}

/*!
 * Function create visual objects and connect slots.
 */
void 
CatalogForm::init()
{

	ListView = new aListView(centralWidget(), "listView");
	ListView->setGeometry(30,30,400,300);
	ListView->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	LineEdit = new aLineEdit(centralWidget(), "lineEdit");
	ListHint = new aListBox(centralWidget(), "listBox");
	StatusFrame = new QFrame(centralWidget(), "statusFrame");
	
	ListView->setRootIsDecorated( true );
	
	StatusFrame->setGeometry( QRect( 0, 0, 50,5 ) );
	StatusFrame->setFrameShape( QFrame::StyledPanel );
	StatusFrame->setFrameShadow( QFrame::Raised );
	StatusFrame->hide();
    	
	GridLayout = new QGridLayout(centralWidget(), 1, 1, 11, 6, "GridLayout");
	GridLayout->addMultiCellWidget( ListView, 2,3, 0 , 0 );
	GridLayout->addWidget( LineEdit, 1, 0 );
	GridLayout->addWidget( bCancel, 3, 1 );
	QLabel *lb = new QLabel(tr("Search"),centralWidget());
	lb->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, lb->sizePolicy().hasHeightForWidth() ) );
	GridLayout->addWidget( lb ,0,0);
	QSpacerItem* spacer = new QSpacerItem( 20, 390, QSizePolicy::Minimum, QSizePolicy::Expanding );
	GridLayout->addMultiCell( spacer, 0,2,1, 1);
	
 	QPixmap  pix= QPixmap::fromMimeSource("cat.png");
	if(pix.isNull())
	{
		aLog::print(aLog::MT_INFO, tr("Catalog Form image cat.png not loaded"));
	}
	else
	{
		setIcon( pix );
	}
 	//setFocusPolicy();
  //  connect(this, 	SIGNAL	(destoyed()),
//	    this,	SLOT	(close());
    
    connect(ListView, 	SIGNAL	(newItemRequest(QListViewItem*)),
	    this,	SLOT	(new_item(QListViewItem*)));
    
    connect(ListView, 	SIGNAL	(newGroupRequest(QListViewItem*)), 
	    this, 	SLOT	(new_group(QListViewItem*)));
    
    connect(ListView, 	SIGNAL	(delItemRequest(QListViewItem*)), 
	    this, 	SLOT	(del_item(QListViewItem*)));
    
    connect(ListView, 	SIGNAL	(markDeletedRequest(QListViewItem*)), 
	    this, 	SLOT	(mark_deleted(QListViewItem*)));
    
    connect(ListView, 	SIGNAL	(undoMarkDeletedRequest(QListViewItem*)), 
	    this, 	SLOT	(undo_mark_deleted(QListViewItem*)));
    
    connect(ListView, 	SIGNAL	(editRequest(QListViewItem*, int)), 
	    this, 	SLOT	(edit(QListViewItem*, int)));
    
    connect(ListView, 	SIGNAL	(selectRequest(QListViewItem*)), 
	    this, 	SLOT	(select(QListViewItem*)));
    
    connect(LineEdit, 	SIGNAL	(delayTextChanged(const QString&)),
	    this, 	SLOT	(find(const QString&))); 
    
    connect(LineEdit, 	SIGNAL	(keyArrowPressed()),
	    this, 	SLOT	(pressArrow()));
    
    connect(LineEdit, 	SIGNAL	(keyEnterPressed()),
	    this, 	SLOT	(go()));
    
    connect(ListView,	SIGNAL	(expanded ( QListViewItem *)),
	    this,	SLOT	(onLoadElements( QListViewItem *)));
    
    connect(ListHint, 	SIGNAL	(lostFocus()),
	    LineEdit, 	SLOT	(setFocus()));
    
    connect(ListHint, 	SIGNAL	(lostFocus()),
	   StatusFrame,	SLOT	(hide()));	
    
    connect(ListHint, 	SIGNAL	(lostFocus()),
     ListHint,  SLOT (hide())); 
    
    connect(ListHint,  SIGNAL (keyArrowLRPressed()), 
     LineEdit,  SLOT (setFocus()));
    
    connect(ListHint,  SIGNAL (keyArrowLRPressed(const QString&)),
     this,  SLOT (setText(const QString&)));
    
    connect(ListHint,  SIGNAL (keyEnterPressed()),
     this,  SLOT (go()));
    
    connect(ListHint,  SIGNAL (sendMessage(const QString &)),
     this->statusBar(),  SLOT (message( const QString &)));

    connect(ListView,  SIGNAL (sendMessage(const QString &)),
     this->statusBar(),  SLOT (message( const QString &)));

    connect(LineEdit,  SIGNAL (sendMessage(const QString &)),
     this->statusBar(),  SLOT (message( const QString &)));
    
    LineEdit->setFocus();
}

/*!
 * Function delete objects, which were created in function init()
 */
void 
CatalogForm::destroy()
{
	aService::saveSize2Config(this->rect(),QString("%1_embedded editor").arg(cat->md->attr(cat->obj, mda_name)));	
	delete cat;
	cat = 0;
}

/*!
 * Function set text for line edit. Don't emit signals.
 */
void 
CatalogForm::setText( const QString & s )
{
    LineEdit->blockSignals ( true );
    LineEdit->setText ( s );
    setId(ListHint->getId(ListHint->currentItem()));
    LineEdit->blockSignals ( false );
}

/*!
 * Handler bGo::onClick() event. 
 */
void 
CatalogForm::go()
{
	Q_ULLONG ide=getId(), idg;
    	if(!getId())
	{
		ide = findFirst(LineEdit->text());
		setId(ide);
	}
	idg = getIdg(ide);
	loadElements(idg);
	if(map_el.contains(getId()))
    	{
		goToItem(map_el[getId()]);
   	}

}
/*!
 * Ensures that item is visible, scrolling the list view vertically if necessary and opening (expanding) any parent items if this is required to show the item.
 */
void 
CatalogForm::goToItem( QListViewItem *item)
{
	ListView->setSelected(item, true);
	ListView->ensureItemVisible(item); 
	ListView->setFocus();
}

/*!
 * Searching string s in table of elements.
 * \param s (in) - stirng for search.
 * \return id first founding line.
 */
long 
CatalogForm::findFirst( const QString &s )
{
	Q_ULLONG res=0;		
	cat->select(fieldName + " like '%"+s+"%'");// AND df<>'1'");
	//Cat->Select();
	if(cat->First())
	{
		res = cat->sysValue("id").toULongLong();

 	}
	return res;
}

/*!
 * Loads elements in group, if then don't loaded. 
 * \param idGroup (in) - id group for load.
 */
void 
CatalogForm::loadElements( Q_ULLONG idGroup )
{
  QListViewItem * item;
  QListViewItem * p_item;
  uint i;
//  printf("load elements\n");
//  printf("sel by group id = %lu\n",idGroup);
  QPixmap pixmap(getElementPixmap());
  QPixmap pixmap_mark_deleted(getMarkDeletedPixmap());
  cat->selectByGroup(idGroup);
//  printf("_sel by group\n");
  if(cat->First())
  {
  	do
  	{
  //count++;
  		if(map_gr.contains(idGroup)
		   && !map_el.contains(cat->sysValue("id").toULongLong()))
		{
			p_item = map_gr[idGroup];
			item = new QListViewItem(p_item);
			if(cat->isElementMarkDeleted())
				item->setPixmap(0,pixmap_mark_deleted);
			else
				item->setPixmap(0,pixmap);
			for(i=0; i<fieldList.count(); i++)
			{
			//	printf("i = %d\n",i);
				item->setText(i,cat->sysValue(fieldList[i]).toString());
			}
			map_el.insert(cat->sysValue("id").toULongLong(),item);
		}
  	}while(cat->Next());
  }
//  printf("end load\n");
}

/*!
 * Loads elemens in group, if then don't loaded.
 * \param item (in) - group for load.
 */
void 
CatalogForm::onLoadElements( QListViewItem *item )
{
	QValueList<QListViewItem*> lst = map_gr.values();
	int ind = lst.findIndex(item);
	Q_ULLONG key;
	if(ind!=-1)
	{
		QValueList<Q_ULLONG> listKey = map_gr.keys();
		key = listKey[ind];
		loadElements(key);
	}
}

/*!
 * Gets id parent group for element.
 * \param ide (in) - id of element.
 * \return id of group or 0 if no group.
 */
Q_ULLONG 
CatalogForm::getIdg( Q_ULLONG ide )
{
    return cat->idGroupByElement(ide);
}


/*!
 * Adds new element.
 * \param parentItem (in) - parent group. If parent group == 0, element not added.
 */
void 
CatalogForm::new_item( QListViewItem * parentItem )
{
	if(!parentItem)
	{
		//cat->groupSelect(0);	
		cat->newElement(0);
		//printf("id = %llu\n",id);
		QListViewItem* item = new QListViewItem(ListView);
		QPixmap pixmap(getElementPixmap());
		item->setPixmap(0,pixmap);
		map_el.insert(cat->sysValue("id").toULongLong(),item);
		edit(item,true);
		ListView->ensureItemVisible(item);
	//	cfg_message(0,tr("Can't added element"));
		return;
	}
	Q_ULLONG id = getGroupId(parentItem);
	QPixmap pixmap(getElementPixmap());
	if(id) // parent item is group
	{
		cat->groupSelect(id);
		if(!cat->isGroupMarkDeleted())
		{
			cat->newElement(id);
			QListViewItem* item = new QListViewItem(map_gr[id]);
			item->setPixmap(0,pixmap);
			map_el.insert(cat->sysValue("id").toULongLong(),item);
			edit(item,true); 
			ListView->ensureItemVisible(item);
			//ListView->setFocus();
		}
		else cfg_message(0,tr("Can't added new element to mark deleted group"));
	}
	else 
	{
		new_item(parentItem->parent());
	}//cfg_message(0,tr("Can't added element to element"));
}

/*!
 * Gets group id.
 * \param item (in) - group item. 
 */
long 
CatalogForm::getGroupId( QListViewItem * item )
{
	QValueList<QListViewItem*> lst = map_gr.values();
	int ind = lst.findIndex(item);
	Q_ULLONG key=0;
	if(ind!=-1)
	{
		QValueList<Q_ULLONG> listKey = map_gr.keys();
		key = listKey[ind];
	}
return key;
}

/*!
 * Adds new group.
 * \param parentItem (in) - parent group. If parent group == 0, group adds in root.
 */
void 
CatalogForm::new_group( QListViewItem * parentItem )
{
	Q_ULLONG id = getGroupId(parentItem);
	QListViewItem * item;
	QPixmap pixmap(getGroupPixmap());
    //cat->groupSelect( id );
	if(!id)
	{
		id = getElementId(parentItem);
		if(id) 
		{
			cfg_message(0,tr("Can't added group to element"));
			return;
		}
		else
		{
//		printf(">>>>id=0\n");
			cat->newGroup(id);
			item = new QListViewItem(ListView);
			ListView->insertItem(item);
		}
	}
	else
	{
		//cat->groupSelect(id);
		if(cat->isGroupMarkDeleted())
		{
			cfg_message(0,tr("Can't added group to mark deleted group"));
			return;
		}
		cat->newGroup(id);
		item = new QListViewItem(map_gr[id]);
	}
	//item->setText(0,cat->GroupSysValue(fieldListGroup[0]).toString());
	item->setPixmap(0,pixmap);
	map_gr.insert(cat->GroupSysValue("id").toULongLong(),item);
	edit(item,true);
	ListView->ensureItemVisible(item);
	ListView->setCurrentItem(item);
	ListView->setSelected(item,true);
	//ListView->setFocus();
	
}

/*!
 * Gets pixmap for group.
 * \return pixmap.
 */
QPixmap 
CatalogForm::getGroupPixmap()
{
 QPixmap  pixmap = QPixmap::fromMimeSource("group2.png");
// pixmap.detach();
	if(pixmap.isNull())
	{
		aLog::print(aLog::MT_INFO, tr("Catalog Form group pixmap not load"));
	}
return pixmap;
}


/*!
 * Gets pixmap for element.
 * \return pixmap.
 */
QPixmap 
CatalogForm::getElementPixmap()
{
	QPixmap  pixmap= QPixmap::fromMimeSource("field2.png");
	if(pixmap.isNull())
	{
		aLog::print(aLog::MT_INFO, tr("Catalog Form element pixmap not load"));
	}
return pixmap;
}

/*!
 * Gets pixmap for mark deleted element or group.
 * \return pixmap.
 */
QPixmap 
CatalogForm::getMarkDeletedPixmap()
{
	QPixmap  pixmap = QPixmap::fromMimeSource("editdelete2.png");
// pixmap.
	if(pixmap.isNull())
	{
		aLog::print(aLog::MT_INFO, tr("Catalog Form mark deleted group pixmap not load"));
	}
return  pixmap;
}
/*!
 * Delets current element or group (with subgroups).
 * \param item (in) - deleted element or group item.
 */
void CatalogForm::del_item( QListViewItem * item )
{
   // cat->groupSelect(getGroupId(item));
	Q_ULLONG id = getElementId(item);
	if(id)
	{
		cat->select(id);
		if(cat->First())
		{
			cat->delElement();    
			map_el.remove(id);
			delete item;
			item = 0;
		}
	}
	else
	{
		id = getGroupId(item);
		if(id)
		{
			QValueList<Q_ULLONG> listDeletedId;
			cat->delGroup(id, listDeletedId);
			QValueList<Q_ULLONG>::iterator it = listDeletedId.begin(); 
			while(it!= listDeletedId.end())
			{
				if(map_el.contains(*it)) map_el.remove(*it);
				else  if(map_gr.contains(*it)) map_gr.remove(*it);
				++it;
			}
			delete item; // destructor delete all subitems
			item = 0;
		}
	}
}

/*!
 * Marks deleted current element or group (with subgroups).
 * While for mark deleted items sets ahother pixmap only.
 * \param item (in) - marked deleted element or group item.
 */
void CatalogForm::mark_deleted( QListViewItem * item )
{
   Q_ULLONG id = getElementId(item);
   if(id)
   {
   	cat->select(id);
//	cat->setSelected(true);
	if(cat->First())
	{
		cat->setMarkDeletedElement(id,true);    
		item->setPixmap(0,getMarkDeletedPixmap());
	}
   }
   else
   {
	id = getGroupId(item);
	if(id)
	{
		loadElements(id); // populate items in group
		QValueList<Q_ULLONG> listDeletedId;
		cat->getMarkDeletedList(id,listDeletedId);
		QValueList<Q_ULLONG>::iterator it = listDeletedId.begin(); 
		while(it != listDeletedId.end()) //first delete elements in this group
		{
			if(map_el.contains(*it))
		    	{
				map_el[*it]->setPixmap(0, getMarkDeletedPixmap());
				cat->setMarkDeletedElement(*it,true);
				it = listDeletedId.remove(it);
			}
			else
			{
				++it;
			}
		}
		it = listDeletedId.begin();
		while(it != listDeletedId.end()) //second delete groups
		{
			if(map_gr.contains(*it)) 
			{
				map_gr[*it]->setPixmap(0, getMarkDeletedPixmap());
				cat->setMarkDeletedGroup(*it,true);
				it = listDeletedId.remove(it);
				//map_el[*it]->invalidateHeight();// setHeight(10);
			}
			else
			{
				++it;
			}
		}
	}
   }
}

/*!
 * Undo marks deleted current element or group (with subgroups).
 * \param item (in) - marked deleted element or group item.
 */
void CatalogForm::undo_mark_deleted( QListViewItem * item )
{
	Q_ULLONG id = getElementId(item);
	if(id)
	{
	  	cat->select(id);
		if(cat->First())
		{
			cat->setMarkDeletedElement(id,false);    
			item->setPixmap(0,getElementPixmap());
		}
   	}
	else
	{
		id = getGroupId(item);
		if(id)
		{
		  // cat->select(QString("id=%1").arg(id),md_group);
		   //if(cat->FirstInGroupTable())
			QValueList<Q_ULLONG> listDeletedId;
		   //	cat->setMarkDeletedGroup(id, listDeletedId,false);
	   		cat->getMarkDeletedList(id, listDeletedId);
			QValueList<Q_ULLONG>::iterator it = listDeletedId.begin(); 
			while(it != listDeletedId.end()) //first delete elements in this group
			{
				if(map_el.contains(*it))
				{
					map_el[*it]->setPixmap(0, getElementPixmap());
					cat->setMarkDeletedElement(*it,false);
					it = listDeletedId.remove(it);
				}
				else
				{
					++it;
				}
			}
			it = listDeletedId.begin();
			while(it != listDeletedId.end()) //second delete groups
			{
				if(map_gr.contains(*it)) 
				{
					map_gr[*it]->setPixmap(0, getGroupPixmap());
					cat->setMarkDeletedGroup(*it,false);
					it = listDeletedId.remove(it);
					//map_el[*it]->invalidateHeight();// setHeight(10);
				}
				else
				{
					++it;
				}
			}
		}
	}
}

void CatalogForm::edit( QListViewItem * item, int)
{
	edit( item, false);
}

void CatalogForm::edit( QListViewItem * item, bool afterNew)
{
//	QWidget *wd = topLevelWidget();
	aLog::print(aLog::MT_DEBUG, tr("Catalog Form edit element start"));	
   MainForm * mw = (MainForm*) topLevelWidget();
   if(mw)
   {
	Q_ULLONG id = getElementId(item);
	if(id)
  	{
		aLog::print(aLog::MT_DEBUG, tr("Catalog Form edit element with id=%1").arg(id));
		cat->select(id);
		if(idElementForm) 
		{
			if(!cat->isElementMarkDeleted())
			{
				aForm *editForm = new aForm(mw->ws, &mw->engine, (long int) idElementForm);
				if(editForm)
				{
					if(afterNew) editForm->setMode(0);
					else editForm->setMode(1);
					editForm->Select(id);
					connect(editForm, SIGNAL(closeForm(Q_ULLONG)), this, SLOT(Refresh(Q_ULLONG)));
					editForm->show();
				}
				else
				{
					aLog::print(aLog::MT_ERROR, tr("Catalog Form edit element form is null"));
				}
			}
			else cfg_message(0, tr("Can't edit mark deleted element"));
		}
		else cfg_message(1,tr("Catalog haven't edit element form"));
	}
	else
  	{
   		id = getGroupId(item);
		aLog::print(aLog::MT_DEBUG, tr("Catalog Form edit group with id = %1").arg(id));
		if(id)
		{
			
			cat->groupSelect(id);
			if(idGroupForm)
			{
				if(!cat->isGroupMarkDeleted())
				{
					aForm *editForm = new aForm(mw->ws, &mw->engine, (long int) idGroupForm);
					if(editForm)
					{
						if(afterNew) editForm->setMode(0);
						else editForm->setMode(1);

						editForm->SelectGroup(id);
						connect(editForm, SIGNAL(closeForm(Q_ULLONG)), this, SLOT(Refresh(Q_ULLONG)));
						editForm->show();
					}
					else
					{
						aLog::print(aLog::MT_ERROR, tr("Catalog Form edit group form is null"));
					}
     				}
				else cfg_message(0, tr("Can't edit mark deleted group"));
    			}
			else cfg_message(1,tr("Catalog haven't edit group form"));
		}
	}
  }
  else
  {
	aLog::print(aLog::MT_ERROR, tr("Catalog Form main widget is not 'MainForm'"));
  } 

}

/*!
 * Selects current group or element.
 * \param item (in) - selected element or group item
 */
void CatalogForm::select( QListViewItem * item )
{
	Q_ULLONG res = getGroupId(item);
	if(!res)
	{
		res = getElementId(item);
		cat->select(res);
		if(!cat->isElementMarkDeleted()) 
		{
			setId(res);
			doOk();
		}
	}
	else
	{
		cat->groupSelect(res);
		if(!cat->isGroupMarkDeleted()) 
		{
			setId(res);
			doOk();
		}
	}
	emit(selected(res));
//    return res;
}

/*!
 * Gets element id.
 * \param item (in) - element item. 
 */
Q_ULLONG CatalogForm::getElementId( QListViewItem * item )
{
	QValueList<QListViewItem*> lst = map_el.values();
	int ind = lst.findIndex(item);
	Q_ULLONG key=0;
	if(ind!=-1)
	{
		QValueList<Q_ULLONG> listKey = map_el.keys();
		key = listKey[ind];
	}
return key;
}


void CatalogForm::doOk()
{
	close();
}



void CatalogForm::keyPressEvent( QKeyEvent * e )
{
	if ( e->key()==Qt::Key_Return)
	{
	}
	if ( e->key()==Qt::Key_Escape)
	{
		close();
	}
	e->ignore();
}


void CatalogForm::Refresh( Q_ULLONG id )
{
	QListViewItem * item;
	if( map_el.contains( id ))
	{
		item = map_el[id];
		cat->select( id );
		for(uint i=0; i<fieldList.count(); i++)
		{
			
			item->setText(i,cat->sysValue(fieldList[i]).toString());
			ListView->setFocus();
		}
	}
	else
	{
		if( map_gr.contains( id ) )
		{
			item = map_gr[id];
			cat->groupSelect( id );
			item->setText(0,cat->GroupSysValue(fieldListGroup[0]).toString());
			ListView->setFocus();
		}
	}
}





