#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "LEDControl16P16.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "ShowIODialog.h"
#include "WriteEPROMDialog.h"


SettingDialog::LineWindow::LineWindow(QWidget *parent)
	:Label(parent)
	,EditValue(parent)
	,EditComment(parent)
{
}
void	SettingDialog::LineWindow::SetY(int n)
{
	Label.setText(QString("Line ")+QString::number(n));
	Label.move(0,12+24*n);
	Label.resize(51,21);

	EditValue.setMaximum(1023);
	EditValue.move(70,12+24*n);
	EditValue.resize(71,21);

	EditComment.move(150,12+24*n);
	EditComment.resize(200,21);
}
void	SettingDialog::LineWindow::Show(void)
{
	Label.show();
	EditValue.show();
	EditComment.show();
}

//=====================================================================

SettingDialog::SettingDialog(LEDControl16P16Panel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	ui->lineEditVersion->setText(Panel->VersionStr);

	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]=NULL;
	}

	int	n=GetCurrentRegPattern();
	if(n>=0){
		InitialWindow	(GetCurrentLightNo(),GetCurrentRegPattern());
		ShowData(GetCurrentLightNo(),GetCurrentRegPattern());
	}

	Panel->SetTestLED(true);

	LastLightNo			=GetCurrentLightNo();
	LastRegPatternNo	=GetCurrentRegPattern();
	LastShowPaatternNo	=GetCurrentShowPattern();
		
	Panel->CurrentPattern=GetCurrentShowPattern();
	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
	Panel->SetTestLED(false);

	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		if(LineData[i]!=NULL)
			delete	LineData[i];
		LineData[i]=NULL;
	}
    delete ui;
}
int		SettingDialog::GetCurrentLightNo(void)
{
	return ui->comboBoxLightNo->currentIndex();
}

int		SettingDialog::GetCurrentRegPattern(void)
{
	return ui->comboBoxPatternNo->currentIndex();
}

int		SettingDialog::GetCurrentShowPattern(void)
{
	return ui->comboBoxPatternNoOperation->currentIndex();
}

QProgressBar	*SettingDialog::GetBar(void)
{
	return ui->progressBar;
}

void	SettingDialog::InitialWindow	(int LightNo ,int PatternNo)
{
	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		if(LineData[i]!=NULL)
			delete	LineData[i];
		LineData[i]=NULL;
	}

	for(int i=0;i<Panel->LightData[LightNo].UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]=new LineWindow(ui->frameSetting);
		LineData[i]->SetY(i);
		LineData[i]->Show();
	}
}

void	SettingDialog::ShowData			(int LightNo ,int PatternNo)
{
	for(int i=0;i<Panel->LightData[LightNo].UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]->EditValue	.setValue(Panel->LightData[LightNo].PatternData[PatternNo].LineValues[i].Value);
		LineData[i]->EditComment.setText (Panel->LightData[LightNo].PatternData[PatternNo].LineValues[i].Comment);
	}
	ui->lineEditLightComment	->setText(Panel->LightData[LightNo].Comment);
	ui->lineEditPatternComment	->setText(Panel->LightData[LightNo].PatternData[PatternNo].Comment);
}
void	SettingDialog::GetDataFromWindow(int LightNo ,int PatternNo)
{
	for(int i=0;i<Panel->LightData[LightNo].UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
		Panel->LightData[LightNo].PatternData[PatternNo].LineValues[i].Value	=LineData[i]->EditValue	 .value();
		Panel->LightData[LightNo].PatternData[PatternNo].LineValues[i].Comment	=LineData[i]->EditComment.text ();
	}
	Panel->LightData[LightNo].Comment						=ui->lineEditLightComment	->text();
	Panel->LightData[LightNo].PatternData[PatternNo].Comment=ui->lineEditPatternComment	->text();
}

void SettingDialog::on_pushButtonTransfer_clicked()
{
	GetDataFromWindow(GetCurrentLightNo(),GetCurrentRegPattern());
	Panel->ReflectDataInDialog();
}

void SettingDialog::on_toolButtonON_clicked()
{
	GetDataFromWindow(GetCurrentLightNo(),GetCurrentRegPattern());

	Panel->ReflectOnOffInDialog(ui->toolButtonON->isChecked());
}

void SettingDialog::on_pushButtonOK_clicked()
{
	GetDataFromWindow(GetCurrentLightNo(),GetCurrentRegPattern());
	done(true);
}

void SettingDialog::on_pushButtonSetAll_clicked()
{
	GetDataFromWindow(GetCurrentLightNo(),GetCurrentRegPattern());

	int	V=ui->spinBoxBrightness->value();
	
	for(int i=0;i<Panel->LightData[GetCurrentLightNo()].UsageLines 
				&& i<sizeof(LineData)/sizeof(LineData[0])
				;i++){
		Panel->LightData[GetCurrentLightNo()].PatternData[GetCurrentRegPattern()].LineValues[i].Value	=V;
	}
	ShowData(GetCurrentLightNo(),GetCurrentRegPattern());
}


void SettingDialog::on_pushButtonShowIO_clicked()
{
	ShowIODialog	D(Panel);
	D.exec();
}

void SettingDialog::on_comboBoxPatternNo_currentIndexChanged(int index)
{
	GetDataFromWindow(LastLightNo,LastRegPatternNo);
	ShowData(GetCurrentLightNo(),GetCurrentRegPattern());

	LastLightNo			=GetCurrentLightNo();
	LastRegPatternNo	=GetCurrentRegPattern();
}

void SettingDialog::on_comboBoxPatternNoOperation_currentIndexChanged(int index)
{
	Panel->CurrentPattern=GetCurrentShowPattern();
	Panel->ShowPattern(Panel->CurrentPattern);
}

void SettingDialog::on_comboBoxLightNo_currentIndexChanged(int index)
{
	GetDataFromWindow(LastLightNo,LastRegPatternNo);
	ShowData(GetCurrentLightNo(),GetCurrentRegPattern());

	LastLightNo			=GetCurrentLightNo();
	LastRegPatternNo	=GetCurrentRegPattern();
}
