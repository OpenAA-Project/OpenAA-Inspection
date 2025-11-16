#include "LEDControl16KDSBeltDialog.h"
#include "ui_LEDControl16KDSBeltDialog.h"
#include "LEDControl16KDSBelt.h"

LEDControl16KDSBeltDialog::LEDControl16KDSBeltDialog(LEDControl16KDSBeltPanel *p,QWidget *parent) :
    QDialog(parent)
    ,Panel(p)
    ,ui(new Ui::LEDControl16KDSBeltDialog)
{
    ui->setupUi(this);

    ui->toolButtonStartSequence->setChecked(Panel->GIOStructData.RegStartSequence);
}

LEDControl16KDSBeltDialog::~LEDControl16KDSBeltDialog()
{
    delete ui;
}

void LEDControl16KDSBeltDialog::on_toolButtonStartSequence_clicked()
{
    Panel->GIOStructData.RegStartSequence=ui->toolButtonStartSequence->isChecked();
	Panel->SendGio();
}


void LEDControl16KDSBeltDialog::on_toolButtonBlueLight_clicked()
{

}


void LEDControl16KDSBeltDialog::on_pushButtonClose_clicked()
{
    done(true);
}

