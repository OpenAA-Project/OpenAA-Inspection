#include "IODelivererDialog.h"
#include "ui_IODelivererDialog.h"
#include "LEDControl16C.h"

IODelivererDialog::IODelivererDialog(LEDControl16CPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::IODelivererDialog)
{
    ui->setupUi(this);
}

IODelivererDialog::~IODelivererDialog()
{
    delete ui;
}

void IODelivererDialog::on_pushButtonStart_clicked()
{
	if(ui->pushButtonStart->isChecked()==true)
		Panel->SetTestSignal(0);
	else
		Panel->SetTestSignal(1);
}
