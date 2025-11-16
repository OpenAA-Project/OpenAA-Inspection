#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "LEDControl32.h"

SettingDialog::SettingDialog(LEDControl32 *src ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	Panel=src;
	LEDData	=Panel->LEDData;
	LastPatternNo	=-1;
	LastBoardNo		=-1;

	pEditBrightnrss[0]	=ui->spinBoxBrightness0;
	pEditBrightnrss[1]	=ui->spinBoxBrightness1;
	pEditBrightnrss[2]	=ui->spinBoxBrightness2;
	pEditBrightnrss[3]	=ui->spinBoxBrightness3;
	pEditBrightnrss[4]	=ui->spinBoxBrightness4;
	pEditBrightnrss[5]	=ui->spinBoxBrightness5;
	pEditBrightnrss[6]	=ui->spinBoxBrightness6;
	pEditBrightnrss[7]	=ui->spinBoxBrightness7;
	pEditBrightnrss[8]	=ui->spinBoxBrightness8;
	pEditBrightnrss[9]	=ui->spinBoxBrightness9;
	pEditBrightnrss[10]	=ui->spinBoxBrightness10;
	pEditBrightnrss[11]	=ui->spinBoxBrightness11;
	pEditBrightnrss[12]	=ui->spinBoxBrightness12;
	pEditBrightnrss[13]	=ui->spinBoxBrightness13;
	pEditBrightnrss[14]	=ui->spinBoxBrightness14;
	pEditBrightnrss[15]	=ui->spinBoxBrightness15;
	pEditBrightnrss[16]	=ui->spinBoxBrightness16;
	pEditBrightnrss[17]	=ui->spinBoxBrightness17;
	pEditBrightnrss[18]	=ui->spinBoxBrightness18;
	pEditBrightnrss[19]	=ui->spinBoxBrightness19;
	pEditBrightnrss[20]	=ui->spinBoxBrightness20;
	pEditBrightnrss[21]	=ui->spinBoxBrightness21;
	pEditBrightnrss[22]	=ui->spinBoxBrightness22;
	pEditBrightnrss[23]	=ui->spinBoxBrightness23;
	pEditBrightnrss[24]	=ui->spinBoxBrightness24;
	pEditBrightnrss[25]	=ui->spinBoxBrightness25;
	pEditBrightnrss[26]	=ui->spinBoxBrightness26;
	pEditBrightnrss[27]	=ui->spinBoxBrightness27;
	pEditBrightnrss[28]	=ui->spinBoxBrightness28;
	pEditBrightnrss[29]	=ui->spinBoxBrightness29;
	pEditBrightnrss[30]	=ui->spinBoxBrightness30;
	pEditBrightnrss[31]	=ui->spinBoxBrightness31;

	pEditText[0]	=ui->lineEditText0;
	pEditText[1]	=ui->lineEditText1;
	pEditText[2]	=ui->lineEditText2;
	pEditText[3]	=ui->lineEditText3;
	pEditText[4]	=ui->lineEditText4;
	pEditText[5]	=ui->lineEditText5;
	pEditText[6]	=ui->lineEditText6;
	pEditText[7]	=ui->lineEditText7;
	pEditText[8]	=ui->lineEditText8;
	pEditText[9]	=ui->lineEditText9;
	pEditText[10]	=ui->lineEditText10;
	pEditText[11]	=ui->lineEditText11;
	pEditText[12]	=ui->lineEditText12;
	pEditText[13]	=ui->lineEditText13;
	pEditText[14]	=ui->lineEditText14;
	pEditText[15]	=ui->lineEditText15;
	pEditText[16]	=ui->lineEditText16;
	pEditText[17]	=ui->lineEditText17;
	pEditText[18]	=ui->lineEditText18;
	pEditText[19]	=ui->lineEditText19;
	pEditText[20]	=ui->lineEditText20;
	pEditText[21]	=ui->lineEditText21;
	pEditText[22]	=ui->lineEditText22;
	pEditText[23]	=ui->lineEditText23;
	pEditText[24]	=ui->lineEditText24;
	pEditText[25]	=ui->lineEditText25;
	pEditText[26]	=ui->lineEditText26;
	pEditText[27]	=ui->lineEditText27;
	pEditText[28]	=ui->lineEditText28;
	pEditText[29]	=ui->lineEditText29;
	pEditText[30]	=ui->lineEditText30;
	pEditText[31]	=ui->lineEditText31;

	for(int i=0;i<LEDPatternCount;i++){
		ui->comboBoxPattern		->addItem(QString::number(i));
		ui->comboBoxPatternBuffA->addItem(QString::number(i));
		ui->comboBoxPatternBuffB->addItem(QString::number(i));
	}
	for(int i=0;i<Panel->BoardCount;i++){
		ui->comboBoxBoard	->addItem(QString::number(i));
	}
	ui->lineEditVersionStr	->setText(Panel->VersionStr);

	ui->comboBoxBoard	->setCurrentIndex(0);
	ui->comboBoxPattern	->setCurrentIndex(0);

	ui->comboBoxPatternBuffA	->setCurrentIndex(Panel->IndexBuffer1);
	on_comboBoxPatternBuffA_currentIndexChanged(0);

	ui->comboBoxPatternBuffB	->setCurrentIndex(Panel->IndexBuffer2);
	on_comboBoxPatternBuffB_currentIndexChanged(0);

	if(Panel->OutputNumber==0){
		ui->radioButtonOutputA	->setChecked(true);
		on_radioButtonOutputA_clicked();
	}
	else{
		ui->radioButtonOutputB	->setChecked(true);
		on_radioButtonOutputB_clicked();
	}
	src->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::ShowCurrent(void)
{
	int	BoardNo	 =ui->comboBoxBoard	->currentIndex();
	int	PatternNo=ui->comboBoxPattern->currentIndex();
	if(BoardNo<0 || PatternNo<0)
		return;
	for(int i=0;i<LEDCountInSheet;i++){
		pEditBrightnrss[i]->setMaximum(Panel->MaxValue);
		pEditBrightnrss[i]->setValue(LEDData.Board[BoardNo].Pattern[PatternNo].Brightness[i]);
		pEditText[i]->setText(LEDData.Board[BoardNo].Text[i]);
	}
	ui->verticalSliderBrightnrss	->setMaximum(Panel->MaxValue);
}
void SettingDialog::StoreCurrent(int BoardNo ,int PatternNo)
{
	if(BoardNo<0 || PatternNo<0)
		return;
	for(int i=0;i<LEDCountInSheet;i++){
		LEDData.Board[BoardNo].Pattern[PatternNo].Brightness[i]	=pEditBrightnrss[i]->value();
		LEDData.Board[BoardNo].Text[i]	=pEditText[i]->text();
	}
}


void SettingDialog::on_comboBoxPattern_currentIndexChanged(int index)
{
	if(LastPatternNo>=0 && LastBoardNo>=0)
		StoreCurrent(LastBoardNo,LastPatternNo);
	ShowCurrent();
}

void SettingDialog::on_comboBoxBoard_currentIndexChanged(int index)
{
	if(LastPatternNo>=0 && LastBoardNo>=0)
		StoreCurrent(LastBoardNo,LastPatternNo);
	ShowCurrent();
}

void SettingDialog::on_verticalSliderBrightnrss_valueChanged(int value)
{
	int	PatternNo=ui->comboBoxPattern->currentIndex();
	if(PatternNo<0)
		return;
	if(ui->toolButtonSelectAllBoard->isChecked()==true){
		for(int b=0;b<LEDBoardCount;b++){
			for(int i=0;i<LEDCountInSheet;i++){
				LEDData.Board[b].Pattern[PatternNo].Brightness[i]	=value;
			}
		}
	}
	else if(ui->toolButtonSelectAll->isChecked()==true){
		int	b=ui->comboBoxBoard	->currentIndex();
		if(b>=0){
			for(int i=0;i<LEDCountInSheet;i++){
				LEDData.Board[b].Pattern[PatternNo].Brightness[i]	=value;
			}
		}
	}
	ShowCurrent();
}

void SettingDialog::on_spinBoxBrightness_valueChanged(int arg1)
{
	on_verticalSliderBrightnrss_valueChanged(ui->spinBoxBrightness->value());
}

void SettingDialog::on_pushButtonTransfer_clicked()
{
	int	BoardNo	 =ui->comboBoxBoard	->currentIndex();
	int	PatternNo=ui->comboBoxPattern->currentIndex();
	if(BoardNo<0 || PatternNo<0)
		return;
	StoreCurrent(BoardNo ,PatternNo);

	LEDControl32::LEDDataStruct	TmpLEDData;
	TmpLEDData=Panel->LEDData;
	Panel->LEDData	=LEDData;
	Panel->ReflectDataInDialog();
	Panel->LEDData	=TmpLEDData;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	int	BoardNo	 =ui->comboBoxBoard	->currentIndex();
	int	PatternNo=ui->comboBoxPattern->currentIndex();
	if(BoardNo<0 || PatternNo<0)
		return;
	StoreCurrent(BoardNo ,PatternNo);

	Panel->LEDData=LEDData;
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_toolButtonLightON_clicked()
{
	Panel->ReflectOnOffInDialog(ui->toolButtonLightON->isChecked());
}

void SettingDialog::on_radioButtonOutputA_clicked()
{
	Panel->CommSetOutputNumber(0);
}

void SettingDialog::on_radioButtonOutputB_clicked()
{
	Panel->CommSetOutputNumber(1);
}

void SettingDialog::on_comboBoxPatternBuffA_currentIndexChanged(int index)
{
	int	BoardNo	 =ui->comboBoxBoard	->currentIndex();
	if(BoardNo<0)
		return;
	Panel->IndexBuffer1	=ui->comboBoxPatternBuffA->currentIndex();
	Panel->CommTransferAll(BoardNo,Panel->IndexBuffer1,0);
}

void SettingDialog::on_comboBoxPatternBuffB_currentIndexChanged(int index)
{
	int	BoardNo	 =ui->comboBoxBoard	->currentIndex();
	if(BoardNo<0)
		return;
	Panel->IndexBuffer2	=ui->comboBoxPatternBuffB->currentIndex();
	Panel->CommTransferAll(BoardNo,Panel->IndexBuffer2,1);
}
