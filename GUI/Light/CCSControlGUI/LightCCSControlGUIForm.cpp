#include "CCSControlGUIResource.h"
#include "LightCCSControlGUIForm.h"
#include "ui_LightCCSControlGUIForm.h"
#include "XCCSControl.h"
#include "XLightClass.h"

LightCCSControlGUIForm::LightCCSControlGUIForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::LightCCSControlGUIForm)
{
    ui->setupUi(this);

	LightPointer=NULL;
}

LightCCSControlGUIForm::~LightCCSControlGUIForm()
{
    delete ui;
}

void	LightCCSControlGUIForm::Prepare(void)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightPointer=GetLayersBase()->GetLightBase()->GetLight(0,/**/"LightCCSControl");
		if(LightPointer!=NULL){
			connect(LightPointer,SIGNAL(SignalReflectDataInDialog()),this,SLOT(SlotReflectDataInDialog()));
			connect(LightPointer,SIGNAL(SignalReflectOnOffInDialog(bool)),this,SLOT(SlotReflectOnOffInDialog(bool)));
		}
	}
	bool	OnOff;
	int		value;
	if(LoadFile(OnOff, value)==true){
		ui->toolButtonON->setChecked(OnOff);
		ui->spinBoxBrightness->setValue(value);
		on_dialBrightness_valueChanged(value);
		on_toolButtonON_clicked();
	}
}
void	LightCCSControlGUIForm::BuildForShow(void)
{
	CmdLightReqData	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		LightPointer->TransmitDirectly(&Cmd);
		ui->spinBoxBrightness->setValue(Cmd.Value);
		ui->dialBrightness->setValue(Cmd.Value);
		ui->toolButtonON->setChecked(Cmd.OnMode);

		on_dialBrightness_valueChanged(Cmd.Value);
		on_toolButtonON_clicked();
	}
}
void LightCCSControlGUIForm::on_dialBrightness_valueChanged(int value)
{
	CmdLightSetValue	Cmd(GetLayersBase());
	ui->spinBoxBrightness->setValue(value);
	if(LightPointer!=NULL){
		Cmd.Value=value;
		LightPointer->TransmitDirectly(&Cmd);
	}
	SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxBrightness->value());
}

void LightCCSControlGUIForm::on_spinBoxBrightness_editingFinished()
{
	int	value=ui->spinBoxBrightness->value();
	ui->dialBrightness->setValue(value);
	SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxBrightness->value());
}

void LightCCSControlGUIForm::on_toolButtonON_clicked()
{
	CmdLightSetOnOff	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		Cmd.OnMode=ui->toolButtonON->isChecked();
		LightPointer->TransmitDirectly(&Cmd);
	}
	SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxBrightness->value());
}

void	LightCCSControlGUIForm::SlotReflectDataInDialog()
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysical();
	}
}
void	LightCCSControlGUIForm::SlotReflectOnOffInDialog(bool LightOn)
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysicalTurnOn(LightOn);
	}
}


QString	LightCCSControlGUIForm::GetParamFileName(void)
{
	QString	ParamFileName=/**/"LightCCSValue";
	QString	FileName=GetLayersBase()->GetUserPath()
					+::GetSeparator()
					+QString(ParamFileName)
					+QString(/**/".dat");
	return FileName;
}

bool LightCCSControlGUIForm::SaveFile(bool OnOff, int value)
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

bool LightCCSControlGUIForm::LoadFile(bool &OnOff, int &value)
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
