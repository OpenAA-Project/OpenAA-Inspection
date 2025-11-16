#include "ShowIODialog.h"
#include "ui_ShowIODialog.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XHidCommand.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "LEDControl16.h"

ShowIODialog::ShowIODialog(LEDControl16Panel *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowIODialog)
{
    ui->setupUi(this);

	Panel=p;

	CurrentBoard	=0;
	CurrentADNumber	=0;


	TM.setInterval(30);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

ShowIODialog::~ShowIODialog()
{
    delete ui;
}

void	ShowIODialog::ShowData(void)
{
	if(CurrentBoard>=0){
		ui->checkBoxInput0	->setChecked((Panel->BoardData[CurrentBoard].InputData[0]!=0)?true:false);
		ui->checkBoxInput1	->setChecked((Panel->BoardData[CurrentBoard].InputData[1]!=0)?true:false);
		ui->lineEditAD0	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[0]));
		ui->lineEditAD1	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[1]));
		ui->lineEditAD2	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[2]));
		ui->lineEditAD3	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[3]));
		ui->lineEditAD4	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[4]));
		ui->lineEditAD5	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[5]));
		ui->lineEditAD6	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[6]));
		ui->lineEditAD7	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[7]));
		ui->lineEditAD8	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[8]));
		ui->lineEditAD9	->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[9]));
		ui->lineEditAD10->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[10]));
		ui->lineEditAD11->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[11]));
		ui->lineEditAD12->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[12]));
		ui->lineEditAD13->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[13]));
		ui->lineEditAD14->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[14]));
		ui->lineEditAD15->setText(QString::number(Panel->BoardData[CurrentBoard].ADData[15]));

		on_comboBoxLineNumber_currentIndexChanged(0);
	}
}

void	ShowIODialog::SlotTimeOut()
{
	if(ui->toolButtonAutoUpdate->isChecked()==true){
		if(CurrentBoard<Panel->BoardCount){
			Panel->LoadADData(CurrentBoard,CurrentADNumber);
	
			CurrentADNumber++;
			if(CurrentADNumber>=16){
				CurrentADNumber=0;
			}
			Panel->LoadInputData(CurrentBoard);
			ShowData();
		}
	}
}
void ShowIODialog::on_comboBoxLineNumber_currentIndexChanged(int index)
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	if(BoardNumber>=0){
		int	LineNumber = ui->comboBoxLineNumber	->currentIndex();
		for(int i=0;i<Panel->LightDataNumb;i++){
			for(int j=0;j<Panel->LightData[i].UsageLines;j++){
				if(Panel->LightData[i].PatternData[0].LineValues[j].BoardNumber==BoardNumber
				&& Panel->LightData[i].PatternData[0].LineValues[j].LineNumber==LineNumber){
					int	d=Panel->LightData[i].PatternData[0].LineValues[j].Value;
					ui->lineEditCurrentValue	->setText(QString::number(d));
					return;
				}
			}
		}
	}
}
void ShowIODialog::on_pushButtonReadAD_clicked()
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	int	LineNumber = ui->comboBoxLineNumber	->currentIndex();
	if(BoardNumber>=0 && LineNumber>=0){
		Panel->LoadADData(BoardNumber,LineNumber);
		ShowData();
	}
}

void ShowIODialog::on_pushButtonReadInput_clicked()
{
	int	BoardNumber	= ui->comboBoxSelectBoard->currentIndex();
	if(BoardNumber>=0){
		Panel->LoadInputData(BoardNumber);
		ShowData();
	}
}

void ShowIODialog::on_toolButtonTestLED_clicked()
{
	Panel->SetTestLED(ui->toolButtonTestLED->isChecked());
}
