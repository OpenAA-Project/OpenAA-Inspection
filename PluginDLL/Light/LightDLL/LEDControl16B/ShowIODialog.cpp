#include "ShowIODialog.h"
#include "ui_ShowIODialog.h"
#include "LEDControl16B.h"
#include "swap.h"

ShowIODialog::ShowIODialog(LEDControl16BPanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::ShowIODialog)
{
    ui->setupUi(this);

	TM.setInterval(300);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

ShowIODialog::~ShowIODialog()
{
    delete ui;
}

void ShowIODialog::on_pushButton_clicked()
{
    close();
}

void	ShowIODialog::SlotTimeOut()
{
	int	BoardNumber=ui->comboBoxBoardNumber->currentIndex();
	if(BoardNumber<0)
		return;
	Panel->LoadInputData(BoardNumber);
	ui->checkBoxInput1	->setChecked((Panel->BoardData[BoardNumber].InputData[0]!=0)?true:false);
	ui->checkBoxInput2	->setChecked((Panel->BoardData[BoardNumber].InputData[1]!=0)?true:false);
}