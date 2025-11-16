#include "testsequencedlldialog.h"
#include "ui_testsequencedlldialog.h"
#include "XSequence.h"

TestSequenceDLLDialog::TestSequenceDLLDialog(DLLVarOperand *D,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestSequenceDLLDialog)
{
    ui->setupUi(this);
	Var=D;

	QStringList Functions;
	Var->GetExportFunctions(Functions);
	ui->comboBoxFunction->addItems(Functions);
}

TestSequenceDLLDialog::~TestSequenceDLLDialog()
{
    delete ui;
}

void TestSequenceDLLDialog::on_pushButtonTest_clicked()
{

}

void TestSequenceDLLDialog::on_pushButtonClose_clicked()
{

}
