#ifndef TESTSEQUENCEDLLDIALOG_H
#define TESTSEQUENCEDLLDIALOG_H

#include <QDialog>
#include "XSequence.h"

namespace Ui {
    class TestSequenceDLLDialog;
}


class TestSequenceDLLDialog : public QDialog
{
    Q_OBJECT

	DLLVarOperand	*Var;

public:
    explicit TestSequenceDLLDialog(DLLVarOperand *D,QWidget *parent = 0);
    ~TestSequenceDLLDialog();

private slots:
    void on_pushButtonTest_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::TestSequenceDLLDialog *ui;
};

#endif // TESTSEQUENCEDLLDIALOG_H
