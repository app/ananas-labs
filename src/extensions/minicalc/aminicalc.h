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

#ifndef MINICALC_H
#define MINICALC_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QPushButton;
class QLineEdit;
class QLabel;


class MiniCalc : public QDialog
{
    Q_OBJECT

public:
    MiniCalc( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MiniCalc();

    void abortOperation();
    bool calculate(double rightOperand, const QString &pendingOperator);
    bool calcpercent(double rightOperand, const QString &pendingOperator);

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;

    QFrame* calcFrame;
    QPushButton* extMem;
    QLineEdit* display;
    QPushButton* toDocButton;
    QPushButton* clearMemoryButton;
    QPushButton* btn_7;
    QPushButton* btn_8;
    QPushButton* btn_9;
    QPushButton* plusButton;
    QPushButton* changeSignButton;
    QPushButton* clearButton;
    QPushButton* readMemoryButton;
    QPushButton* btn_4;
    QPushButton* btn_5;
    QPushButton* btn_6;
    QPushButton* minusButton;
    QPushButton* persentButton;
    QPushButton* clearAllButton;
    QPushButton* minusMemoryButton;
    QPushButton* btn_1;
    QPushButton* btn_2;
    QPushButton* btn_3;
    QPushButton* timesButton;
    QPushButton* reciprocalButton;
    QPushButton* backspaceButton;
    QPushButton* addToMemoryButton;
    QPushButton* btn_0;
    QPushButton* doubleZero;
    QPushButton* pointButton;
    QPushButton* divisionButton;
    QPushButton* powButton;
    QPushButton* equalButton;
    QFrame* extension;
    QLabel* label;
    QLineEdit* mem_1;
    QPushButton* mem_to_disp_4;
    QPushButton* disp_to_mem_4;
    QPushButton* mem_to_disp_3;
    QPushButton* disp_to_mem_3;
    QPushButton* disp_to_mem_1;
    QLineEdit* mem_4;
    QLineEdit* mem_3;
    QPushButton* disp_to_mem_2;
    QLineEdit* mem_2;
    QPushButton* mem_to_disp_2;
    QPushButton* mem_to_disp_1;

public slots:
    virtual void digitClicked();
    virtual void unaryOperatorClicked();
    virtual void additiveOperatorClicked();
    virtual void multiplicativeOperatorClicked();
    virtual void equalClicked();
    virtual void dzClicked();
    virtual void pointClicked();
    virtual void percentClicked();
    virtual void changeSignClicked();
    virtual void backspaceClicked();
    virtual void clear();
    virtual void clearAll();
    virtual void clearMemory();
    virtual void readMemory();
    virtual void minusMemory();
    virtual void addToMemory();
    virtual void toDoc();
    virtual void extMemClicked();
    virtual void extMemOperations();

protected:
    QGridLayout* MiniCalcLayout;
    QGridLayout* calcFrameLayout;
    QGridLayout* extensionLayout;

protected slots:
    virtual void languageChange();

};

#endif // MINICALC_H
