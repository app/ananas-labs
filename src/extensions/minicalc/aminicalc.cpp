/****************************************************************************
** $Id$
**
** Source file of Ananas project
**  
**  Copyright (C) 2005-2005 Trolltech AS. All rights reserved.
**  Copyright (C) 2008 Dmitry Kruglikov.
**
** This file is part of the extention of the Ananas
** automation accounting system.
** Based on code samples of the documentation of the Qt Toolkit
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

#include "aminicalc.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qevent.h>
#include <qpalette.h>
#include <math.h>



/*
 *  Constructs a MiniCalc as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
MiniCalc::MiniCalc( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name ) setName( "MiniCalc" );
    setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 1, 1, sizePolicy().hasHeightForWidth() ) );
    MiniCalcLayout = new QGridLayout( this, 1, 1, 1, 1, "MiniCalcLayout");
    MiniCalcLayout->setResizeMode( QLayout::Fixed );

    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;


    calcFrame = new QFrame( this, "calcFrame" );
    calcFrame->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, calcFrame->sizePolicy().hasHeightForWidth() ) );
    calcFrame->setFrameShape( QFrame::StyledPanel );
    calcFrame->setFrameShadow( QFrame::Raised );
    calcFrameLayout = new QGridLayout( calcFrame, 1, 1, 1, 1, "calcFrameLayout");

    extMem = new QPushButton( calcFrame, "extMem" );
    extMem->setMaximumSize( QSize( 25, 25 ) );
    extMem->setPaletteBackgroundColor( QColor( 205, 205, 205 ) );
    QFont extMem_font(  extMem->font() );
    extMem_font.setPointSize( 8 );
    extMem->setFont( extMem_font );
    extMem->setToggleButton( TRUE );

    calcFrameLayout->addWidget( extMem, 0, 0 );

    display = new QLineEdit( calcFrame, "display" );
    QFont display_font(  display->font() );
    display_font.setFamily( "xos4 Terminus" );
    display_font.setPointSize( 11 );
    display->setFont( display_font );
    display->setText("0");
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);
    display->installEventFilter(this);


    calcFrameLayout->addMultiCellWidget( display, 0, 0, 1, 5 );

    toDocButton = new QPushButton( calcFrame, "toDocButton" );
    toDocButton->setMaximumSize( QSize( 25, 25 ) );
    toDocButton->setPaletteBackgroundColor( QColor( 200, 200, 250 ) );
    QFont toDocButton_font(  toDocButton->font() );
    toDocButton_font.setPointSize( 8 );
    toDocButton->setFont( toDocButton_font );

    calcFrameLayout->addWidget( toDocButton, 0, 6 );

    clearMemoryButton = new QPushButton( calcFrame, "clearMemoryButton" );
    clearMemoryButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, clearMemoryButton->sizePolicy().hasHeightForWidth() ) );
    clearMemoryButton->setMaximumSize( QSize( 25, 25 ) );
    clearMemoryButton->setPaletteBackgroundColor( QColor( 205, 205, 205 ) );
    QFont clearMemoryButton_font(  clearMemoryButton->font() );
    clearMemoryButton_font.setPointSize( 8 );
    clearMemoryButton->setFont( clearMemoryButton_font );

    calcFrameLayout->addWidget( clearMemoryButton, 1, 0 );

    btn_7 = new QPushButton( calcFrame, "btn_7" );
    btn_7->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_7->sizePolicy().hasHeightForWidth() ) );
    btn_7->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_7_font(  btn_7->font() );
    btn_7_font.setPointSize( 8 );
    btn_7->setFont( btn_7_font );

    calcFrameLayout->addWidget( btn_7, 1, 1 );

    btn_8 = new QPushButton( calcFrame, "btn_8" );
    btn_8->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_8->sizePolicy().hasHeightForWidth() ) );
    btn_8->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_8_font(  btn_8->font() );
    btn_8_font.setPointSize( 8 );
    btn_8->setFont( btn_8_font );

    calcFrameLayout->addWidget( btn_8, 1, 2 );

    btn_9 = new QPushButton( calcFrame, "btn_9" );
    btn_9->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_9->sizePolicy().hasHeightForWidth() ) );
    btn_9->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_9_font(  btn_9->font() );
    btn_9_font.setPointSize( 8 );
    btn_9->setFont( btn_9_font );

    calcFrameLayout->addWidget( btn_9, 1, 3 );

    plusButton = new QPushButton( calcFrame, "plusButton" );
    plusButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, plusButton->sizePolicy().hasHeightForWidth() ) );
    plusButton->setMaximumSize( QSize( 25, 25 ) );
    plusButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont plusButton_font(  plusButton->font() );
    plusButton_font.setPointSize( 8 );
    plusButton->setFont( plusButton_font );

    calcFrameLayout->addWidget( plusButton, 1, 4 );

    changeSignButton = new QPushButton( calcFrame, "changeSignButton" );
    changeSignButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, changeSignButton->sizePolicy().hasHeightForWidth() ) );
    changeSignButton->setMaximumSize( QSize( 25, 25 ) );
    changeSignButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont changeSignButton_font(  changeSignButton->font() );
    changeSignButton_font.setPointSize( 8 );
    changeSignButton->setFont( changeSignButton_font );

    calcFrameLayout->addWidget( changeSignButton, 1, 5 );

    clearButton = new QPushButton( calcFrame, "clearButton" );
    clearButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, clearButton->sizePolicy().hasHeightForWidth() ) );
    clearButton->setMaximumSize( QSize( 25, 25 ) );
    clearButton->setPaletteBackgroundColor( QColor( 250, 200, 200 ) );
    QFont clearButton_font(  clearButton->font() );
    clearButton_font.setPointSize( 8 );
    clearButton->setFont( clearButton_font );

    calcFrameLayout->addWidget( clearButton, 1, 6 );

    readMemoryButton = new QPushButton( calcFrame, "readMemoryButton" );
    readMemoryButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, readMemoryButton->sizePolicy().hasHeightForWidth() ) );
    readMemoryButton->setMaximumSize( QSize( 25, 25 ) );
    readMemoryButton->setPaletteBackgroundColor( QColor( 205, 205, 205 ) );
    QFont readMemoryButton_font(  readMemoryButton->font() );
    readMemoryButton_font.setPointSize( 8 );
    readMemoryButton->setFont( readMemoryButton_font );

    calcFrameLayout->addWidget( readMemoryButton, 2, 0 );

    btn_4 = new QPushButton( calcFrame, "btn_4" );
    btn_4->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_4->sizePolicy().hasHeightForWidth() ) );
    btn_4->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_4_font(  btn_4->font() );
    btn_4_font.setPointSize( 8 );
    btn_4->setFont( btn_4_font );

    calcFrameLayout->addWidget( btn_4, 2, 1 );

    btn_5 = new QPushButton( calcFrame, "btn_5" );
    btn_5->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_5->sizePolicy().hasHeightForWidth() ) );
    btn_5->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_5_font(  btn_5->font() );
    btn_5_font.setPointSize( 8 );
    btn_5->setFont( btn_5_font );

    calcFrameLayout->addWidget( btn_5, 2, 2 );

    btn_6 = new QPushButton( calcFrame, "btn_6" );
    btn_6->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_6->sizePolicy().hasHeightForWidth() ) );
    btn_6->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_6_font(  btn_6->font() );
    btn_6_font.setPointSize( 8 );
    btn_6->setFont( btn_6_font );

    calcFrameLayout->addWidget( btn_6, 2, 3 );

    minusButton = new QPushButton( calcFrame, "minusButton" );
    minusButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, minusButton->sizePolicy().hasHeightForWidth() ) );
    minusButton->setMaximumSize( QSize( 25, 25 ) );
    minusButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont minusButton_font(  minusButton->font() );
    minusButton_font.setPointSize( 8 );
    minusButton->setFont( minusButton_font );

    calcFrameLayout->addWidget( minusButton, 2, 4 );

    persentButton = new QPushButton( calcFrame, "persentButton" );
    persentButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, persentButton->sizePolicy().hasHeightForWidth() ) );
    persentButton->setMaximumSize( QSize( 25, 25 ) );
    persentButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont persentButton_font(  persentButton->font() );
    persentButton_font.setPointSize( 8 );
    persentButton->setFont( persentButton_font );

    calcFrameLayout->addWidget( persentButton, 2, 5 );

    clearAllButton = new QPushButton( calcFrame, "clearAllButton" );
    clearAllButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, clearAllButton->sizePolicy().hasHeightForWidth() ) );
    clearAllButton->setMaximumSize( QSize( 25, 25 ) );
    clearAllButton->setPaletteBackgroundColor( QColor( 250, 200, 200 ) );
    QFont clearAllButton_font(  clearAllButton->font() );
    clearAllButton_font.setPointSize( 8 );
    clearAllButton->setFont( clearAllButton_font );

    calcFrameLayout->addWidget( clearAllButton, 2, 6 );

    minusMemoryButton = new QPushButton( calcFrame, "minusMemoryButton" );
    minusMemoryButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, minusMemoryButton->sizePolicy().hasHeightForWidth() ) );
    minusMemoryButton->setMaximumSize( QSize( 25, 25 ) );
    minusMemoryButton->setPaletteBackgroundColor( QColor( 205, 205, 205 ) );
    QFont minusMemoryButton_font(  minusMemoryButton->font() );
    minusMemoryButton_font.setPointSize( 8 );
    minusMemoryButton->setFont( minusMemoryButton_font );

    calcFrameLayout->addWidget( minusMemoryButton, 3, 0 );

    btn_1 = new QPushButton( calcFrame, "btn_1" );
    btn_1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_1->sizePolicy().hasHeightForWidth() ) );
    btn_1->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_1_font(  btn_1->font() );
    btn_1_font.setPointSize( 8 );
    btn_1->setFont( btn_1_font );

    calcFrameLayout->addWidget( btn_1, 3, 1 );

    btn_2 = new QPushButton( calcFrame, "btn_2" );
    btn_2->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_2->sizePolicy().hasHeightForWidth() ) );
    btn_2->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_2_font(  btn_2->font() );
    btn_2_font.setPointSize( 8 );
    btn_2->setFont( btn_2_font );

    calcFrameLayout->addWidget( btn_2, 3, 2 );

    btn_3 = new QPushButton( calcFrame, "btn_3" );
    btn_3->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_3->sizePolicy().hasHeightForWidth() ) );
    btn_3->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_3_font(  btn_3->font() );
    btn_3_font.setPointSize( 8 );
    btn_3->setFont( btn_3_font );

    calcFrameLayout->addWidget( btn_3, 3, 3 );

    timesButton = new QPushButton( calcFrame, "timesButton" );
    timesButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, timesButton->sizePolicy().hasHeightForWidth() ) );
    timesButton->setMaximumSize( QSize( 25, 25 ) );
    timesButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont timesButton_font(  timesButton->font() );
    timesButton_font.setPointSize( 8 );
    timesButton->setFont( timesButton_font );

    calcFrameLayout->addWidget( timesButton, 3, 4 );

    reciprocalButton = new QPushButton( calcFrame, "reciprocalButton" );
    reciprocalButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, reciprocalButton->sizePolicy().hasHeightForWidth() ) );
    reciprocalButton->setMaximumSize( QSize( 25, 25 ) );
    reciprocalButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont reciprocalButton_font(  reciprocalButton->font() );
    reciprocalButton_font.setPointSize( 8 );
    reciprocalButton->setFont( reciprocalButton_font );

    calcFrameLayout->addWidget( reciprocalButton, 3, 5 );

    backspaceButton = new QPushButton( calcFrame, "backspaceButton" );
    backspaceButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, backspaceButton->sizePolicy().hasHeightForWidth() ) );
    backspaceButton->setMaximumSize( QSize( 25, 25 ) );
    backspaceButton->setPaletteBackgroundColor( QColor( 250, 200, 200 ) );
    QFont backspaceButton_font(  backspaceButton->font() );
    backspaceButton_font.setPointSize( 8 );
    backspaceButton->setFont( backspaceButton_font );

    calcFrameLayout->addWidget( backspaceButton, 3, 6 );

    addToMemoryButton = new QPushButton( calcFrame, "addToMemoryButton" );
    addToMemoryButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, addToMemoryButton->sizePolicy().hasHeightForWidth() ) );
    addToMemoryButton->setMaximumSize( QSize( 25, 25 ) );
    addToMemoryButton->setPaletteBackgroundColor( QColor( 205, 205, 205 ) );
    QFont addToMemoryButton_font(  addToMemoryButton->font() );
    addToMemoryButton_font.setPointSize( 8 );
    addToMemoryButton->setFont( addToMemoryButton_font );

    calcFrameLayout->addWidget( addToMemoryButton, 4, 0 );

    btn_0 = new QPushButton( calcFrame, "btn_0" );
    btn_0->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, btn_0->sizePolicy().hasHeightForWidth() ) );
    btn_0->setMaximumSize( QSize( 25, 25 ) );
    QFont btn_0_font(  btn_0->font() );
    btn_0_font.setPointSize( 8 );
    btn_0->setFont( btn_0_font );

    calcFrameLayout->addWidget( btn_0, 4, 1 );

    doubleZero = new QPushButton( calcFrame, "doubleZero" );
    doubleZero->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, doubleZero->sizePolicy().hasHeightForWidth() ) );
    doubleZero->setMaximumSize( QSize( 25, 25 ) );
    QFont doubleZero_font(  doubleZero->font() );
    doubleZero_font.setPointSize( 8 );
    doubleZero->setFont( doubleZero_font );

    calcFrameLayout->addWidget( doubleZero, 4, 2 );

    pointButton = new QPushButton( calcFrame, "pointButton" );
    pointButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pointButton->sizePolicy().hasHeightForWidth() ) );
    pointButton->setMaximumSize( QSize( 25, 25 ) );
    QFont pointButton_font(  pointButton->font() );
    pointButton_font.setPointSize( 8 );
    pointButton->setFont( pointButton_font );

    calcFrameLayout->addWidget( pointButton, 4, 3 );

    divisionButton = new QPushButton( calcFrame, "divisionButton" );
    divisionButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, divisionButton->sizePolicy().hasHeightForWidth() ) );
    divisionButton->setMaximumSize( QSize( 25, 25 ) );
    divisionButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont divisionButton_font(  divisionButton->font() );
    divisionButton_font.setPointSize( 8 );
    divisionButton->setFont( divisionButton_font );

    calcFrameLayout->addWidget( divisionButton, 4, 4 );

    powButton = new QPushButton( calcFrame, "powButton" );
    powButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, powButton->sizePolicy().hasHeightForWidth() ) );
    powButton->setMaximumSize( QSize( 25, 25 ) );
    powButton->setPaletteBackgroundColor( QColor( 200, 250, 200 ) );
    QFont powButton_font(  powButton->font() );
    powButton_font.setPointSize( 8 );
    powButton->setFont( powButton_font );

    calcFrameLayout->addWidget( powButton, 4, 5 );

    equalButton = new QPushButton( calcFrame, "equalButton" );
    equalButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, equalButton->sizePolicy().hasHeightForWidth() ) );
    equalButton->setMaximumSize( QSize( 25, 25 ) );
    equalButton->setPaletteBackgroundColor( QColor( 200, 200, 250 ) );
    QFont equalButton_font(  equalButton->font() );
    equalButton_font.setPointSize( 8 );
    equalButton->setFont( equalButton_font );

    calcFrameLayout->addWidget( equalButton, 4, 6 );

    MiniCalcLayout->addWidget( calcFrame, 0, 0 );

    extension = new QFrame( this, "extension" );
    extension->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, extension->sizePolicy().hasHeightForWidth() ) );
    extension->setFrameShape( QFrame::StyledPanel );
    extension->setFrameShadow( QFrame::Raised );
    extensionLayout = new QGridLayout( extension, 1, 1, 1, 1, "extensionLayout");

    label = new QLabel( extension, "label" );
    label->setMinimumSize( QSize( 0, 20 ) );
    QFont label_font(  label->font() );
    label_font.setPointSize( 8 );
    label->setFont( label_font );
    //label->setAlignment( int( QLabel::AlignCenter ) );

    extensionLayout->addMultiCellWidget( label, 0, 0, 0, 2 );

    mem_1 = new QLineEdit( extension, "mem_1" );
    QFont mem_1_font(  mem_1->font() );
    mem_1_font.setPointSize( 10 );
    mem_1->setFont( mem_1_font );

    extensionLayout->addWidget( mem_1, 1, 2 );

    mem_to_disp_4 = new QPushButton( extension, "mtd_4" );
    mem_to_disp_4->setMaximumSize( QSize( 25, 25 ) );
    QFont mem_to_disp_4_font(  mem_to_disp_4->font() );
    mem_to_disp_4_font.setPointSize( 8 );
    mem_to_disp_4->setFont( mem_to_disp_4_font );

    extensionLayout->addWidget( mem_to_disp_4, 4, 1 );

    disp_to_mem_4 = new QPushButton( extension, "dtm_4" );
    disp_to_mem_4->setMaximumSize( QSize( 25, 25 ) );
    QFont disp_to_mem_4_font(  disp_to_mem_4->font() );
    disp_to_mem_4_font.setPointSize( 8 );
    disp_to_mem_4->setFont( disp_to_mem_4_font );

    extensionLayout->addWidget( disp_to_mem_4, 4, 0 );

    mem_to_disp_3 = new QPushButton( extension, "mtd_3" );
    mem_to_disp_3->setMaximumSize( QSize( 25, 25 ) );
    QFont mem_to_disp_3_font(  mem_to_disp_3->font() );
    mem_to_disp_3_font.setPointSize( 8 );
    mem_to_disp_3->setFont( mem_to_disp_3_font );

    extensionLayout->addWidget( mem_to_disp_3, 3, 1 );

    disp_to_mem_3 = new QPushButton( extension, "dtm_3" );
    disp_to_mem_3->setMaximumSize( QSize( 25, 25 ) );
    QFont disp_to_mem_3_font(  disp_to_mem_3->font() );
    disp_to_mem_3_font.setPointSize( 8 );
    disp_to_mem_3->setFont( disp_to_mem_3_font );

    extensionLayout->addWidget( disp_to_mem_3, 3, 0 );

    disp_to_mem_1 = new QPushButton( extension, "dtm_1" );
    disp_to_mem_1->setMaximumSize( QSize( 25, 25 ) );
    QFont disp_to_mem_1_font(  disp_to_mem_1->font() );
    disp_to_mem_1_font.setPointSize( 8 );
    disp_to_mem_1->setFont( disp_to_mem_1_font );

    extensionLayout->addWidget( disp_to_mem_1, 1, 0 );

    mem_4 = new QLineEdit( extension, "mem_4" );
    QFont mem_4_font(  mem_4->font() );
    mem_4_font.setPointSize( 10 );
    mem_4->setFont( mem_4_font );

    extensionLayout->addWidget( mem_4, 4, 2 );

    mem_3 = new QLineEdit( extension, "mem_3" );
    QFont mem_3_font(  mem_3->font() );
    mem_3_font.setPointSize( 10 );
    mem_3->setFont( mem_3_font );

    extensionLayout->addWidget( mem_3, 3, 2 );

    disp_to_mem_2 = new QPushButton( extension, "dtm_2" );
    disp_to_mem_2->setMaximumSize( QSize( 25, 25 ) );
    QFont disp_to_mem_2_font(  disp_to_mem_2->font() );
    disp_to_mem_2_font.setPointSize( 8 );
    disp_to_mem_2->setFont( disp_to_mem_2_font );

    extensionLayout->addWidget( disp_to_mem_2, 2, 0 );

    mem_2 = new QLineEdit( extension, "mem_2" );
    QFont mem_2_font(  mem_2->font() );
    mem_2_font.setPointSize( 10 );
    mem_2->setFont( mem_2_font );

    extensionLayout->addWidget( mem_2, 2, 2 );

    mem_to_disp_2 = new QPushButton( extension, "mtd_2" );
    mem_to_disp_2->setMaximumSize( QSize( 25, 25 ) );
    QFont mem_to_disp_2_font(  mem_to_disp_2->font() );
    mem_to_disp_2_font.setPointSize( 8 );
    mem_to_disp_2->setFont( mem_to_disp_2_font );

    extensionLayout->addWidget( mem_to_disp_2, 2, 1 );

    mem_to_disp_1 = new QPushButton( extension, "mtd_1" );
    mem_to_disp_1->setMaximumSize( QSize( 25, 25 ) );
    QFont mem_to_disp_1_font(  mem_to_disp_1->font() );
    mem_to_disp_1_font.setPointSize( 8 );
    mem_to_disp_1->setFont( mem_to_disp_1_font );

    extensionLayout->addWidget( mem_to_disp_1, 1, 1 );

    MiniCalcLayout->addWidget( extension, 1, 0 );
    languageChange();
    resize( QSize(210, 233).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    extension->hide();
    clearMemoryButton->setDisabled(true);
    readMemoryButton->setDisabled(true);

    // signals and slots connections
    connect( extMem, SIGNAL( clicked() ), this, SLOT( extMemClicked() ) );
    connect( btn_0, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_1, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_2, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_3, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_4, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_5, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_6, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_7, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_8, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( btn_9, SIGNAL( clicked() ), this, SLOT( digitClicked() ) );
    connect( mem_to_disp_1, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( mem_to_disp_2, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( mem_to_disp_3, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( mem_to_disp_4, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( disp_to_mem_1, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( disp_to_mem_2, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( disp_to_mem_3, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( disp_to_mem_4, SIGNAL( clicked() ), this, SLOT(extMemOperations()));
    connect( backspaceButton, SIGNAL( clicked() ), this, SLOT(backspaceClicked()));
    connect( changeSignButton, SIGNAL( clicked() ), this, SLOT(changeSignClicked()));
    connect( reciprocalButton, SIGNAL( clicked() ), this, SLOT( unaryOperatorClicked() ) );
    connect( powButton, SIGNAL( clicked() ), this, SLOT( unaryOperatorClicked() ) );
    connect( divisionButton, SIGNAL( clicked() ), this, SLOT( multiplicativeOperatorClicked() ) );
    connect( timesButton, SIGNAL( clicked() ), this, SLOT( multiplicativeOperatorClicked() ) );
    connect( minusButton, SIGNAL( clicked() ), this, SLOT( additiveOperatorClicked() ) );
    connect( plusButton, SIGNAL( clicked() ), this, SLOT( additiveOperatorClicked() ) );
    connect( persentButton, SIGNAL( clicked() ), this, SLOT( percentClicked() ) );
    connect( equalButton, SIGNAL( clicked() ), this, SLOT( equalClicked() ) );
    connect( doubleZero, SIGNAL( clicked() ), this, SLOT( dzClicked() ) );
    connect( pointButton, SIGNAL( clicked() ), this, SLOT( pointClicked() ) );
    connect( clearButton, SIGNAL( clicked() ), this, SLOT( clear() ) );
    connect( clearAllButton, SIGNAL( clicked() ), this, SLOT( clearAll() ) );
    connect( clearMemoryButton, SIGNAL( clicked() ), this, SLOT( clearMemory() ) );
    connect( toDocButton, SIGNAL( clicked() ), this, SLOT( toDoc() ) );
    connect( clearMemoryButton, SIGNAL( clicked() ), this, SLOT( clearMemory() ) );
    connect( readMemoryButton, SIGNAL( clicked() ), this, SLOT( readMemory() ) );
    connect( minusMemoryButton, SIGNAL( clicked() ), this, SLOT( minusMemory() ) );
    connect( addToMemoryButton, SIGNAL( clicked() ), this, SLOT( addToMemory() ) );

}

/*
 *  Destroys the object and frees any allocated resources
 */
MiniCalc::~MiniCalc()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MiniCalc::languageChange()
{
    setCaption( tr( "Calculator" ) );
    extMem->setText( tr( "ME" ) );
    toDocButton->setText( tr( "->" ) );
    clearMemoryButton->setText( tr( "MC" ) );
    btn_7->setText( tr( "7" ) );
    btn_8->setText( tr( "8" ) );
    btn_9->setText( tr( "9" ) );
    plusButton->setText( tr( "+" ) );
    changeSignButton->setText( tr( "\261" ) );
    clearButton->setText( tr( "C" ) );
    readMemoryButton->setText( tr( "MR" ) );
    btn_4->setText( tr( "4" ) );
    btn_5->setText( tr( "5" ) );
    btn_6->setText( tr( "6" ) );
    minusButton->setText( tr( "-" ) );
    persentButton->setText( tr( "%" ) );
    clearAllButton->setText( tr( "CE" ) );
    minusMemoryButton->setText( tr( "M-" ) );
    btn_1->setText( tr( "1" ) );
    btn_2->setText( tr( "2" ) );
    btn_3->setText( tr( "3" ) );
    timesButton->setText( tr( "\327" ) );
    reciprocalButton->setText( tr( "1/X" ) );
    backspaceButton->setText( tr( "<-" ) );
    addToMemoryButton->setText( tr( "M+" ) );
    btn_0->setText( tr( "0" ) );
    doubleZero->setText( tr( "00" ) );
    pointButton->setText( tr( "." ) );
    divisionButton->setText( tr( "/" ) );
    powButton->setText( tr( "x\262" ) );
    equalButton->setText( tr( "=" ) );
    label->setText( tr( "In memory: 0" ) );
    mem_to_disp_4->setText( tr( "<" ) );
    disp_to_mem_4->setText( tr( ">" ) );
    mem_to_disp_3->setText( tr( "<" ) );
    disp_to_mem_3->setText( tr( ">" ) );
    disp_to_mem_1->setText( tr( ">" ) );
    disp_to_mem_2->setText( tr( ">" ) );
    mem_to_disp_2->setText( tr( "<" ) );
    mem_to_disp_1->setText( tr( "<" ) );
}


/*
 *  Open a extended memory cells
 */ 
void MiniCalc::extMemClicked()
{
 if ( !extension->isVisibleTo(0) ) {
     extension->show();
     setCaption( tr( "A-Calc +" ) );
 } else {
     extension->hide();
     setCaption( tr( "A-Calc" ) );
 }
 return;
}


void MiniCalc::digitClicked()
{
    QPushButton *clickedButton = (QPushButton*)sender();
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
	waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));

}


void MiniCalc::dzClicked()
{
    double operand = display->text().toDouble();
    double result = 0.0;
    if (operand > 0.0) {
       result = operand * 100;
       display->setText(QString::number(result));
    }
    else {return;}
}

void MiniCalc::unaryOperatorClicked()
{
    QPushButton *clickedButton = (QPushButton*)sender();
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;


    if (clickedOperator == tr("x\262")) {
        result = pow(operand, 2.0);
    } else if (clickedOperator == tr("1/X")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}


void MiniCalc::additiveOperatorClicked()
{
    QPushButton *clickedButton = (QPushButton*)sender();
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.truncate(0);
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    waitingForOperand = true;
}


void MiniCalc::multiplicativeOperatorClicked()
{
    QPushButton *clickedButton = (QPushButton*)sender();
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}


void MiniCalc::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains("."))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}


void MiniCalc::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}


void MiniCalc::backspaceClicked()
{
    if (waitingForOperand) return;

    QString text = display->text();
        display->end(false);
        display->backspace();
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
        display->setText(text);
    }

}


void MiniCalc::clear()
{
    if (waitingForOperand) return;
    display->setText("0");
    waitingForOperand = true;
}


void MiniCalc::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.truncate(0);
    pendingMultiplicativeOperator.truncate(0);
    display->setText("0");
    waitingForOperand = true;
}


void MiniCalc::clearMemory()
{
    sumInMemory = 0.0;
    clearMemoryButton->setDisabled(true);
    readMemoryButton->setDisabled(true);
    label->setText(QString("In memory: %1").arg(sumInMemory));
}

/*
* Return calculated value to Document
*/
void MiniCalc::toDoc()
{
// Sorry, later...
}


void MiniCalc::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}


void MiniCalc::minusMemory()
{
    equalClicked();
    sumInMemory -= display->text().toDouble();
    clearMemoryButton->setEnabled(true);
    readMemoryButton->setEnabled(true);
    label->setText(QString("In memory: %1").arg(sumInMemory));
}


void MiniCalc::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
    clearMemoryButton->setEnabled(true);
    readMemoryButton->setEnabled(true);
    label->setText(QString("In memory: %1").arg(sumInMemory));
}


void MiniCalc::abortOperation()
{
    clearAll();
    display->setText(tr("ERROR"));
}


bool MiniCalc::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\327")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("/")) {
	if (rightOperand == 0.0)
	    return false;
	factorSoFar /= rightOperand;
    }
    return true;
}


void MiniCalc::extMemOperations()
{
    QPushButton *clickedButton = (QPushButton*)sender();
    QString clickedOperator = clickedButton->name();

    if (clickedOperator == "dtm_1") {
       QString text = display->text();
       mem_1->setText(text);
    } else if (clickedOperator == "dtm_2"){
       QString text = display->text();
       mem_2->setText(text);
    } else if (clickedOperator == "dtm_3"){
        QString text = display->text();
        mem_3->setText(text);
    } else if (clickedOperator == "dtm_4"){
        QString text = display->text();
        mem_4->setText(text);
    } else if (clickedOperator == "mtd_1"){
        QString text = mem_1->text();
        display->setText(text);
    } else if (clickedOperator == "mtd_2"){
        QString text = mem_2->text();
        display->setText(text);
    } else if (clickedOperator == "mtd_3"){
        QString text = mem_3->text();
        display->setText(text);
    } else if (clickedOperator == "mtd_4"){
        QString text = mem_4->text();
        display->setText(text);
    }

}


void MiniCalc::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
	    return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.truncate( 0 );
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
	    return;
        }
        pendingAdditiveOperator.truncate(0);
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}


bool MiniCalc::calcpercent(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar = sumSoFar + ((sumSoFar / 100) * rightOperand);

    } else if (pendingOperator == tr("-")) {
        sumSoFar = sumSoFar - ((sumSoFar / 100) * rightOperand);

    } else if (pendingOperator == tr("\327")) {
        factorSoFar = (factorSoFar /rightOperand ) * 100;

    } else if (pendingOperator == tr("/")) {
	if (rightOperand == 0.0)
	    return false;
        factorSoFar = (factorSoFar / 100) * rightOperand;

    }
    return true;
}


void MiniCalc::percentClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calcpercent(operand, pendingMultiplicativeOperator)) {
            abortOperation();
	    return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.truncate( 0 );
    }

    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calcpercent(operand, pendingAdditiveOperator)) {
            abortOperation();
	    return;
        }
        pendingAdditiveOperator.truncate(0);
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;

}

