#include "PropertyResultImportanceResource.h"
#include "editimportanceform.h"
#include "ui_editimportanceform.h"

EditImportanceForm::EditImportanceForm(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditImportanceForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	ImportanceLevel=100;
	InstallOperationLog(this);
}

EditImportanceForm::~EditImportanceForm()
{
    delete ui;
}
void	EditImportanceForm::SetImportanceLevel(int L)
{
	if(L==10){
		ui->radioButtonVeryHigh->setChecked(true);
	}
	if(L==50){
		ui->radioButtonHigh->setChecked(true);
	}
	if(L==100){
		ui->radioButtonNormal->setChecked(true);
	}
	if(L==200){
		ui->radioButtonNotSoHigh->setChecked(true);
	}
	ui->spinBoxLevel->setValue(L);
	ImportanceLevel=L;
}
void EditImportanceForm::on_pushButtonOK_clicked()
{
	if(ui->radioButtonVeryHigh->isChecked()==true){
		ImportanceLevel=10;
	}
	if(ui->radioButtonHigh->isChecked()==true){
		ImportanceLevel=50;
	}
	if(ui->radioButtonNormal->isChecked()==true){
		ImportanceLevel=100;
	}
	if(ui->radioButtonNotSoHigh->isChecked()==true){
		ImportanceLevel=200;
	}
	done(true);
}

void EditImportanceForm::on_pushButtonOKLevel_clicked()
{
	ImportanceLevel=ui->spinBoxLevel->value();
	done(true);
}

void EditImportanceForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void EditImportanceForm::on_radioButtonVeryHigh_clicked(bool checked)
{
	ui->pushButtonOKLevel->setDefault(false);
	ui->pushButtonOK	 ->setDefault(true);
}

void EditImportanceForm::on_radioButtonHigh_clicked(bool checked)
{
	ui->pushButtonOKLevel->setDefault(false);
	ui->pushButtonOK	 ->setDefault(true);

}

void EditImportanceForm::on_radioButtonNormal_clicked(bool checked)
{
	ui->pushButtonOKLevel->setDefault(false);
	ui->pushButtonOK	 ->setDefault(true);

}

void EditImportanceForm::on_radioButtonNotSoHigh_clicked(bool checked)
{
	ui->pushButtonOKLevel->setDefault(false);
	ui->pushButtonOK	 ->setDefault(true);

}

void EditImportanceForm::on_spinBoxLevel_valueChanged(int arg1)
{
	ui->pushButtonOKLevel->setDefault(true);
	ui->pushButtonOK	 ->setDefault(false);

}
