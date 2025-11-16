#include "CCSControl2GUIResource.h"
#include "LightCCSControl2GUIForm.h"
#include "ui_LightCCSControl2GUIForm.h"
#include "XCCSControl2.h"
#include "XLightClass.h"

LightCCSControl2GUIForm::LightCCSControl2GUIForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::LightCCSControl2GUIForm)
{
    ui->setupUi(this);

	LightPointer=NULL;
}

LightCCSControl2GUIForm::~LightCCSControl2GUIForm()
{
    delete ui;
}

void	LightCCSControl2GUIForm::Prepare(void)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightPointer=GetLayersBase()->GetLightBase()->GetLight(0,/**/"LightCCSControl2");
		if(LightPointer!=NULL){
			connect(LightPointer,SIGNAL(SignalReflectDataInDialog()),this,SLOT(SlotReflectDataInDialog()));
			connect(LightPointer,SIGNAL(SignalReflectOnOffInDialog(bool)),this,SLOT(SlotReflectOnOffInDialog(bool)));
		}
	}
	bool	OnOff1;
	int		value1;
	bool	OnOff2;
	int		value2;
	if(LoadFile(OnOff1, value1 ,OnOff2, value2)==true){
		ui->toolButtonON1->setChecked(OnOff1);
		ui->spinBoxBrightness1->setValue(value1);
		ui->toolButtonON2->setChecked(OnOff2);
		ui->spinBoxBrightness2->setValue(value2);

		on_dialBrightness1_valueChanged(value1);
		on_dialBrightness2_valueChanged(value2);
		on_toolButtonON1_clicked();
		on_toolButtonON2_clicked();
	}
}
void	LightCCSControl2GUIForm::BuildForShow(void)
{
	CmdLightReqData	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		LightPointer->TransmitDirectly(&Cmd);
		ui->spinBoxBrightness1->setValue(Cmd.Value1);
		ui->spinBoxBrightness2->setValue(Cmd.Value2);
		ui->dialBrightness1->setValue(Cmd.Value1);
		ui->dialBrightness2->setValue(Cmd.Value2);
		ui->toolButtonON1->setChecked(Cmd.OnMode1);
		ui->toolButtonON2->setChecked(Cmd.OnMode2);

		on_dialBrightness1_valueChanged(Cmd.Value1);
		on_toolButtonON1_clicked();
		on_dialBrightness2_valueChanged(Cmd.Value2);
		on_toolButtonON2_clicked();
	}
}
void LightCCSControl2GUIForm::on_dialBrightness1_valueChanged(int value)
{
	CmdLightSetValue1	Cmd(GetLayersBase());
	ui->spinBoxBrightness1->setValue(value);
	if(LightPointer!=NULL){
		Cmd.Value1=ui->spinBoxBrightness1->value();
		LightPointer->TransmitDirectly(&Cmd);
	}
	SaveFile(ui->toolButtonON1->isChecked(),ui->spinBoxBrightness1->value()
			,ui->toolButtonON2->isChecked(),ui->spinBoxBrightness2->value());
}

void LightCCSControl2GUIForm::on_spinBoxBrightness1_editingFinished()
{
	int	value=ui->spinBoxBrightness1->value();
	ui->dialBrightness1->setValue(value);
	SaveFile(ui->toolButtonON1->isChecked(),ui->spinBoxBrightness1->value()
			,ui->toolButtonON2->isChecked(),ui->spinBoxBrightness2->value());
}

void LightCCSControl2GUIForm::on_toolButtonON1_clicked()
{
	CmdLightSetOnOff	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		Cmd.OnMode1=ui->toolButtonON1->isChecked();
		Cmd.OnMode2=ui->toolButtonON2->isChecked();
		LightPointer->TransmitDirectly(&Cmd);
	}
	SaveFile(ui->toolButtonON1->isChecked(),ui->spinBoxBrightness1->value()
			,ui->toolButtonON2->isChecked(),ui->spinBoxBrightness2->value());
}

void LightCCSControl2GUIForm::on_dialBrightness2_valueChanged(int value)
{
	CmdLightSetValue2	Cmd(GetLayersBase());
	ui->spinBoxBrightness2->setValue(value);
	if(LightPointer!=NULL){
		Cmd.Value2=ui->spinBoxBrightness2->value();
		LightPointer->TransmitDirectly(&Cmd);
	}
	SaveFile(ui->toolButtonON1->isChecked(),ui->spinBoxBrightness1->value()
			,ui->toolButtonON2->isChecked(),ui->spinBoxBrightness2->value());
}

void LightCCSControl2GUIForm::on_spinBoxBrightness2_editingFinished()
{
	int	value=ui->spinBoxBrightness2->value();
	ui->dialBrightness2->setValue(value);
	SaveFile(ui->toolButtonON1->isChecked(),ui->spinBoxBrightness1->value()
			,ui->toolButtonON2->isChecked(),ui->spinBoxBrightness2->value());
}

void LightCCSControl2GUIForm::on_toolButtonON2_clicked()
{
	CmdLightSetOnOff	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		Cmd.OnMode1=ui->toolButtonON1->isChecked();
		Cmd.OnMode2=ui->toolButtonON2->isChecked();
		LightPointer->TransmitDirectly(&Cmd);
	}
	SaveFile(ui->toolButtonON1->isChecked(),ui->spinBoxBrightness1->value()
			,ui->toolButtonON2->isChecked(),ui->spinBoxBrightness2->value());
}
void	LightCCSControl2GUIForm::SlotReflectDataInDialog()
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysical();
	}
}
void	LightCCSControl2GUIForm::SlotReflectOnOffInDialog(bool LightOn)
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysicalTurnOn(LightOn);
	}
}


QString	LightCCSControl2GUIForm::GetParamFileName(void)
{
	QString	ParamFileName=/**/"LightCCS2Value";
	QString	FileName=GetLayersBase()->GetUserPath()
					+::GetSeparator()
					+QString(ParamFileName)
					+QString(/**/".dat");
	return FileName;
}

bool LightCCSControl2GUIForm::SaveFile(bool OnOff1, int value1
									 , bool OnOff2, int value2)
{
	QString	FileName=GetParamFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		int32	Ver=1;
		if(::Save(&File,Ver)==false)
			return false;
		if(::Save(&File,OnOff1)==false)
			return false;
		if(::Save(&File,value1)==false)
			return false;
		if(::Save(&File,OnOff2)==false)
			return false;
		if(::Save(&File,value2)==false)
			return false;
		return true;
	}
	return false;
}

bool LightCCSControl2GUIForm::LoadFile(bool &OnOff1, int &value1
									 , bool &OnOff2, int &value2)
{
	QString	FileName=GetParamFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	Ver;
		if(::Load(&File,Ver)==false)
			return false;
		if(::Load(&File,OnOff1)==false)
			return false;
		if(::Load(&File,value1)==false)
			return false;
		if(::Load(&File,OnOff2)==false)
			return false;
		if(::Load(&File,value2)==false)
			return false;
		return true;
	}
	return false;
}
