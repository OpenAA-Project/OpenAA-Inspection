#include "ControlHayashiTokeiGUIResource.h"
#include "ControlHayashiTokeiGUIForm.h"
#include "ui_ControlHayashiTokeiGUIForm.h"
#include "XLightClass.h"
#include "ControlHayashiTokei.h"


ControlHayashiTokeiGUIForm::ControlHayashiTokeiGUIForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ControlHayashiTokeiGUIForm)
{
    ui->setupUi(this);

	LightPointer=NULL;
}

ControlHayashiTokeiGUIForm::~ControlHayashiTokeiGUIForm()
{
    delete ui;
}
void	ControlHayashiTokeiGUIForm::Prepare(void)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightPointer=GetLayersBase()->GetLightBase()->GetLight(0,/**/"HayashiTokei");
		if(LightPointer!=NULL){
			connect(LightPointer,SIGNAL(SignalReflectDataInDialog())		,this,SLOT(SlotReflectDataInDialog()));
			connect(LightPointer,SIGNAL(SignalReflectOnOffInDialog(bool))	,this,SLOT(SlotReflectOnOffInDialog(bool)));
		}
	}
	bool	OnOff;
	int		value;
	if(LoadFile(OnOff, value)==true){
		ui->toolButtonON->setChecked(OnOff);
		ui->spinBoxValue->setValue(value);
		on_toolButtonON_clicked();
	}
}
void	ControlHayashiTokeiGUIForm::BuildForShow(void)
{
	CmdLightReqData	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		Cmd.Number	=Number;
		LightPointer->TransmitDirectly(&Cmd);
		ui->spinBoxValue->setValue(Cmd.Value);
		ui->dialValue->setValue(Cmd.Value);
		ui->toolButtonON->setChecked(Cmd.OnMode);
		on_spinBoxValue_valueChanged(0);
		on_toolButtonON_clicked();
		//SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxValue->value());
	}
}
void ControlHayashiTokeiGUIForm::on_dialValue_valueChanged(int value)
{
	int	v=ui->dialValue->value();
	ui->spinBoxValue->setValue(v);
	if(LightPointer!=NULL){
		CmdLightSetValue	Cmd(GetLayersBase());
		Cmd.Value	=v;
		Cmd.Number	=Number;
		LightPointer->TransmitDirectly(&Cmd);
		SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxValue->value());
	}
}

void ControlHayashiTokeiGUIForm::on_spinBoxValue_valueChanged(int arg1)
{
	int	v=ui->spinBoxValue->value();
	ui->dialValue->setValue(v);
	if(LightPointer!=NULL){
		CmdLightSetValue	Cmd(GetLayersBase());
		Cmd.Value	=v;
		Cmd.Number	=Number;
		LightPointer->TransmitDirectly(&Cmd);
		SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxValue->value());
	}
}

void ControlHayashiTokeiGUIForm::on_toolButtonON_clicked()
{
	if(LightPointer!=NULL){
		CmdLightSetOnOff	Cmd(GetLayersBase());
		Cmd.OnMode	=ui->toolButtonON->isChecked();
		Cmd.Number	=Number;
		LightPointer->TransmitDirectly(&Cmd);

		SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxValue->value());
	}
}
void	ControlHayashiTokeiGUIForm::SlotReflectDataInDialog()
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysical();
	}
}
void	ControlHayashiTokeiGUIForm::SlotReflectOnOffInDialog(bool LightOn)
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysicalTurnOn(LightOn);
	}
}

QString	ControlHayashiTokeiGUIForm::GetParamFileName(void)
{
	QString	ParamFileName=/**/"LightHayashiValue";
	QString	FileName=GetLayersBase()->GetUserPath()
					+::GetSeparator()
					+QString(ParamFileName)
					+QString::number(Number)
					+QString(/**/".dat");
	return FileName;
}

bool ControlHayashiTokeiGUIForm::SaveFile(bool OnOff, int value)
{
	QString	FileName=GetParamFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		int32	Ver=1;
		if(::Save(&File,Ver)==false)
			return false;
		if(::Save(&File,OnOff)==false)
			return false;
		if(::Save(&File,value)==false)
			return false;
		return true;
	}
	return false;
}

bool ControlHayashiTokeiGUIForm::LoadFile(bool &OnOff, int &value)
{
	QString	FileName=GetParamFileName();
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int32	Ver;
		if(::Load(&File,Ver)==false)
			return false;
		if(::Load(&File,OnOff)==false)
			return false;
		if(::Load(&File,value)==false)
			return false;
		return true;
	}
	return false;
}
