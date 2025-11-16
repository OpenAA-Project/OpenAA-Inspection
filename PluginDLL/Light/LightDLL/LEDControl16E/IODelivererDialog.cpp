#include "IODelivererDialog.h"
#include "ui_IODelivererDialog.h"
#include "LEDControl16E.h"

IODelivererDialog::IODelivererDialog(LEDControl16EPanel *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IODelivererDialog)
	,Panel(p)
{
    ui->setupUi(this);
}

IODelivererDialog::~IODelivererDialog()
{
    delete ui;
}

void IODelivererDialog::on_pushButtonStart_clicked()
{
	//if(ui->pushButtonStart->isChecked()==true)
	//	Panel->SetTestSignal(0);
	//else
	//	Panel->SetTestSignal(1);
}
