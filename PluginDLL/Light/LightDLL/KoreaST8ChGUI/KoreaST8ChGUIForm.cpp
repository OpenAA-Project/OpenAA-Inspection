#include "KoreaST8ChGUIForm.h"
#include "ui_KoreaST8ChGUIForm.h"
#include "XLightClass.h"
#include "KoreaST8CH.h"

KoreaST8ChGUIForm::KoreaST8ChGUIForm(LayersBase *base,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::KoreaST8ChGUIForm)
{
    ui->setupUi(this);
	LightPointer=NULL;
	Number=0;
	StepValue	=15;
	installEventFilter(parent);
	SetKeyGrab(true);
}

KoreaST8ChGUIForm::~KoreaST8ChGUIForm()
{
    delete ui;
}

void	KoreaST8ChGUIForm::Prepare(void)
{
	if(GetLayersBase()->GetLightBase()!=NULL){
		LightPointer=GetLayersBase()->GetLightBase()->GetLight(0,"KoreaST8Ch");
		if(LightPointer!=NULL){
			connect(LightPointer,SIGNAL(SignalReflectDataInDialog())		,this,SLOT(SlotReflectDataInDialog()));
			connect(LightPointer,SIGNAL(SignalReflectOnOffInDialog(bool))	,this,SLOT(SlotReflectOnOffInDialog(bool)));
		}
	}
	bool	OnOff;
	int		value;
	if(LoadFile(OnOff, value)==true){
		ui->toolButtonON->setChecked(OnOff);
		ui->spinBoxLightValue->setValue(value);
		on_pushButtonSet_clicked();
	}
}
void	KoreaST8ChGUIForm::BuildForShow(void)
{
	CmdLightReqData	Cmd(GetLayersBase());
	if(LightPointer!=NULL){
		Cmd.Number	=Number;
		LightPointer->TransmitDirectly(&Cmd);
		ui->spinBoxLightValue->setValue(Cmd.Value);
		ui->dialLightValue	 ->setValue(Cmd.Value);
		ui->toolButtonON	 ->setChecked(Cmd.OnMode);

		on_pushButtonSet_clicked();
		SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxLightValue->value());
	}
}

void	KoreaST8ChGUIForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdReqReflectFromLightSpecifiedBroadcaster	*CmdReqReflectFromLightSpecifiedBroadcasterVar=dynamic_cast<CmdReqReflectFromLightSpecifiedBroadcaster *>(v);
	if(CmdReqReflectFromLightSpecifiedBroadcasterVar!=NULL){
		CmdLightReqData	Cmd(GetLayersBase());
		if(LightPointer!=NULL){
			Cmd.Number	=Number;
			LightPointer->TransmitDirectly(&Cmd);
			ui->spinBoxLightValue->setValue(Cmd.Value);
			ui->dialLightValue	 ->setValue(Cmd.Value);
			ui->toolButtonON	 ->setChecked(Cmd.OnMode);
		}
	}
}

void KoreaST8ChGUIForm::on_dialLightValue_valueChanged(int value)
{
	int	v=ui->dialLightValue->value();
	ui->spinBoxLightValue->setValue(v);
	
	if(LightPointer!=NULL){
		CmdLightSetValue	Cmd(GetLayersBase());
		Cmd.Value	=v;
		Cmd.Number	=Number;
		Cmd.OnMode	=ui->toolButtonON		->isChecked();
		LightPointer->TransmitDirectly(&Cmd);
		SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxLightValue->value());
	}
}

void KoreaST8ChGUIForm::on_spinBoxLightValue_valueChanged(int arg1)
{
	int	v=ui->spinBoxLightValue->value();
	ui->dialLightValue->setValue(v);
}

void KoreaST8ChGUIForm::on_pushButtonSet_clicked()
{
	if(LightPointer!=NULL){
		CmdLightSetValue	Cmd(GetLayersBase());
		Cmd.Value	=ui->spinBoxLightValue->value();
		Cmd.OnMode	=ui->toolButtonON		->isChecked();
		Cmd.Number	=Number;
		LightPointer->TransmitDirectly(&Cmd);
		SaveFile(ui->toolButtonON->isChecked(),ui->spinBoxLightValue->value());
	}
}

void	KoreaST8ChGUIForm::SlotReflectDataInDialog()
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysical();
	}
}
void	KoreaST8ChGUIForm::SlotReflectOnOffInDialog(bool LightOn)
{
	if(LightPointer!=NULL){
		LightPointer->ReflectPhysicalTurnOn(LightOn);
	}
}

QString	KoreaST8ChGUIForm::GetParamFileName(void)
{
	QString	ParamFileName="LightST8ChValue";
	QString	FileName=GetLayersBase()->GetUserPath()
					+::GetSeparator()
					+QString(ParamFileName)
					+QString::number(Number)
					+QString(".dat");
	return FileName;
}

bool KoreaST8ChGUIForm::SaveFile(bool OnOff, int value)
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

bool KoreaST8ChGUIForm::LoadFile(bool &OnOff, int &value)
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

bool KoreaST8ChGUIForm::eventFilter(QObject *target, QEvent *event)
{
	if(event->type() == QEvent::KeyPress){
		QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
		if(keyEvent!=NULL){
			keyPressEvent(keyEvent);
			return true;
		}
	}
	return false;
}


void KoreaST8ChGUIForm::keyPressEvent(QKeyEvent *event)
{
	if(GetEditMode()==true){
		return;
	}
	int	d=event->key();
	if(d==Qt::Key_1){
		int	v=ui->dialLightValue->value();
		v-=StepValue;
		if(v<0)
			v=0;
		ui->spinBoxLightValue->setValue(v);
		event->setAccepted(true);
	}
	if(d==Qt::Key_7){
		int	v=ui->dialLightValue->value();
		v+=StepValue;
		if(v>255)
			v=255;
		ui->spinBoxLightValue->setValue(v);	
		event->setAccepted(true);
	}
}

void KoreaST8ChGUIForm::on_toolButtonON_clicked()
{
	on_pushButtonSet_clicked();
}
