#include "PIOBitSettingDialog.h"
#include "ui_PIOBitSettingDialog.h"
#include "EVObjPioOut.h"
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XPIOButton.h"

PIOBitSettingDialog::PIOBitSettingDialog(RunnerPIOOut *obj,QWidget *parent) :
    QDialog(parent),
	Obj(obj),
    ui(new Ui::PIOBitSettingDialog)
{
    ui->setupUi(this);
	ui->spinBoxBoardNumber	->setValue(Obj->BoardNumber);
	ui->spinBoxPortNumber	->setValue(Obj->Port);
	ui->comboBoxBitNumber	->setCurrentIndex(Obj->BitNumber);
}

PIOBitSettingDialog::~PIOBitSettingDialog()
{
    delete ui;
}

void PIOBitSettingDialog::on_pushButtonOK_clicked()
{
	Obj->BoardNumber	=ui->spinBoxBoardNumber	->value();
	Obj->Port			=ui->spinBoxPortNumber	->value();
	Obj->BitNumber		=ui->comboBoxBitNumber	->currentIndex();

	done(true);
}

void PIOBitSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void PIOBitSettingDialog::on_spinBoxBoardNumber_valueChanged(int arg1)
{
	int	V=ui->spinBoxBoardNumber	->value();
	ThreadSequence	*w=Obj->GetLayersBase()->GetSequenceInstance();
	if(w!=NULL){
		PIOClass *s=w->GetFirstPIO();
		//SeqControl	*s=w->GetMainSeqControl();
		if(s!=NULL){
			ui->lineEdit->setText(s->GetBoardName(V));
		}
	}
}
