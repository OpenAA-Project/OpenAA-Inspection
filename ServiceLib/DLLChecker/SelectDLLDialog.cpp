#include "SelectDLLDialog.h"
#include "ui_SelectDLLDialog.h"

SelectDLLDialog::SelectDLLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDLLDialog)
{
    ui->setupUi(this);

	CheckCameraDLL	=false;
	CheckPIODLL		=false;
	CheckLightDLL	=false;
	CheckSequenceDLL=false;

}

SelectDLLDialog::~SelectDLLDialog()
{
    delete ui;
}

void SelectDLLDialog::on_pushButtonOK_clicked()
{
	CheckCameraDLL	=ui->checkBoxCameraDLL	->isChecked();
	CheckPIODLL		=ui->checkBoxPIODLL		->isChecked();
	CheckLightDLL	=ui->checkBoxLightDLL	->isChecked();
	CheckSequenceDLL=ui->checkBoxSequenceDLL->isChecked();
	done(true);
}
