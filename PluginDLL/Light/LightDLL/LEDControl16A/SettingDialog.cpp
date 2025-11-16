#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "LEDControl16A.h"
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

SettingDialog::SettingDialog(LEDControl16APanel *p,QWidget *parent) :
    QDialog(parent)
	,Panel(p)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	ui->lineEditVersion->setText(Panel->VersionStr);

	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]=NULL;
	}
	for(int L=0;L<Panel->LightDataNumb;L++){
		if(Panel->LightData[L].PatternData[0].LineValues[0].Pointer!=NULL){
			QString	Str=GetColorStr(Panel->LightData[L].PatternData[0].LineValues[0].Pointer->ColorType);
			if(L==0)
				ui->toolButtonRed->setText(Str);
			else if(L==1)
				ui->toolButtonGreen->setText(Str);
			else if(L==2)
				ui->toolButtonBlue->setText(Str);
		}
	}

	int	n=GetCurrentPortNumber();
	if(n>=0){
		InitialWindow	(Panel->LightData[n]);
		ShowData(n,Panel->LightData[n] ,Panel->CurrentPattern);
	}

	Panel->SetTestLED(true);

	LastLight=n;
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

int	SettingDialog::GetCurrentPortNumber(void)
{
	if(ui->toolButtonRed->isChecked()==true)
		return 0;
	if(ui->toolButtonGreen->isChecked()==true)
		return 1;
	if(ui->toolButtonBlue->isChecked()==true)
		return 2;
	return -1;
}

QString	SettingDialog::GetColorStr(int ColorType)
{
	switch(ColorType){
	case 0:
		return "Red";
	case 1:
		return "Green";
	case 2:
		return "Blue";
	case 3:
		return "IR";
	case 4:
		return "UV";
	case 5:
		return "White";
	case 6:
		return "Other";
	default:
		return "----";
	}
}

QProgressBar	*SettingDialog::GetBar(void)
{
	return ui->progressBar;
}

void	SettingDialog::InitialWindow	(LEDControl16APanel::PortData &Data)
{
	for(int i=0;i<sizeof(LineData)/sizeof(LineData[0]);i++){
		if(LineData[i]!=NULL)
			delete	LineData[i];
		LineData[i]=NULL;
	}

	for(int i=0;i<Data.UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]=new LineWindow(ui->frameSetting);
		LineData[i]->SetY(i);
		LineData[i]->Show();
	}
}

void	SettingDialog::ShowData			(int TypeNumber ,LEDControl16APanel::PortData &Data ,int PatternNumber)
{
	for(int i=0;i<Data.UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
		LineData[i]->EditValue	.setValue(Data.PatternData[PatternNumber].LineValues[i].Value);
		LineData[i]->EditComment.setText (Data.PatternData[PatternNumber].LineValues[i].Comment);
	}
}
void	SettingDialog::GetDataFromWindow(int TypeNumber ,LEDControl16APanel::PortData &Data ,int PatternNumber)
{
	for(int i=0;i<Data.UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
		Data.PatternData[PatternNumber].LineValues[i].Value		=LineData[i]->EditValue	 .value();
		Data.PatternData[PatternNumber].LineValues[i].Comment	=LineData[i]->EditComment.text ();
	}
}


void SettingDialog::on_toolButtonRed_clicked()
{
	if(LastLight>=0){
		GetDataFromWindow(LastLight ,Panel->LightData[LastLight] ,Panel->CurrentPattern);
	}
	int	n=GetCurrentPortNumber();
	if(n>=0){
		InitialWindow	(Panel->LightData[n]);
		ShowData(n,Panel->LightData[n] ,Panel->CurrentPattern);
	}
	LastLight=n;
}

void SettingDialog::on_toolButtonGreen_clicked()
{
	on_toolButtonRed_clicked();
}

void SettingDialog::on_toolButtonBlue_clicked()
{
	on_toolButtonRed_clicked();
}

void SettingDialog::on_pushButtonTransfer_clicked()
{
	if(LastLight>=0){
		GetDataFromWindow(LastLight ,Panel->LightData[LastLight] ,Panel->CurrentPattern);
	}
	Panel->ReflectDataInDialog();
}

void SettingDialog::on_toolButtonON_clicked()
{
	if(LastLight>=0){
		GetDataFromWindow(LastLight,Panel->LightData[LastLight] ,Panel->CurrentPattern);
	}
	Panel->ReflectOnOffInDialog(ui->toolButtonON->isChecked());
}

void SettingDialog::on_pushButtonOK_clicked()
{
	if(LastLight>=0){
		GetDataFromWindow(LastLight,Panel->LightData[LastLight] ,Panel->CurrentPattern);
	}
	done(true);
}

void SettingDialog::on_pushButtonSetAll_clicked()
{
	GetDataFromWindow(LastLight,Panel->LightData[LastLight] ,Panel->CurrentPattern);

	int	V=ui->spinBoxBrightness->value();
	int	n=GetCurrentPortNumber();
	if(n>=0){	
		for(int i=0;i<Panel->LightData[LastLight].UsageLines && i<sizeof(LineData)/sizeof(LineData[0]);i++){
			Panel->LightData[n].PatternData[Panel->CurrentPattern].LineValues[i].Value	=V;
		}
		ShowData(n,Panel->LightData[n] ,Panel->CurrentPattern);
	}
}

void SettingDialog::on_pushButtonWriteEPROM_clicked()
{
	WriteEPROMDialog	D(Panel);
	D.exec();
}

void SettingDialog::on_pushButtonShowIO_clicked()
{
	ShowIODialog	D(Panel);
	D.exec();
}

void SettingDialog::on_pushButtonTemporaryON_clicked()
{
	Panel->SetTemporaryON(1000000);
}
