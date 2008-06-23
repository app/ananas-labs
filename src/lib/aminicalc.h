/****************************************************************************
** Form interface generated from reading ui file 'aminicalc.ui'
**
** Created: 2008-06-18T13:52:59
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

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
