#include "ShowADDialog.h"
#include "ui_ShowADDialog.h"
#include "LEDControl16B.h"

ShowADDialog::ShowADDialog(LEDControl16BPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::ShowADDialog)
{
    ui->setupUi(this);
}

ShowADDialog::~ShowADDialog()
{
    delete ui;
}

void ShowADDialog::on_pushButtonClose_clicked()
{
	close();
}

void ShowADDialog::on_pushButtonReqAD_clicked()
{
	int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
	Panel->LoadADData(BoardNumber);
	ui->listWidgetADValue	->clear();
	for(int i=0;i<16;i++){
		ui->listWidgetADValue->addItem(QString::number(Panel->BoardData[BoardNumber].ADData[i]));
	}
}
