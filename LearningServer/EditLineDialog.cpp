#include "EditLineDialog.h"
#include "ui_EditLineDialog.h"

EditLineDialog::EditLineDialog(int SampleType,int Priority,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLineDialog)
{
    ui->setupUi(this);

    ui->spinBoxPriority->setValue(Priority);
    ui->horizontalSliderPriority->setValue(Priority);
    if(SampleType==1){
        ui->radioButtonOK   ->setChecked(true);
        ui->radioButtonNG   ->setChecked(false);
    }
    else{
        ui->radioButtonOK   ->setChecked(false);
        ui->radioButtonNG   ->setChecked(true);
    }
}

EditLineDialog::~EditLineDialog()
{
    delete ui;
}

void EditLineDialog::on_horizontalSliderPriority_valueChanged(int value)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->spinBoxPriority->setValue(ui->horizontalSliderPriority->value());
	ReEntrant=false;
}


void EditLineDialog::on_spinBoxPriority_valueChanged(int arg1)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	ui->horizontalSliderPriority->setValue(ui->spinBoxPriority->value());
	ReEntrant=false;
}


void EditLineDialog::on_pushButtonSave_clicked()
{
	if(ui->radioButtonOK->isChecked()==true){
		SampleType	=1;
	}
	else{
		SampleType	=2;
	}
	Priority=ui->spinBoxPriority->value();
	done(true);
}


void EditLineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

