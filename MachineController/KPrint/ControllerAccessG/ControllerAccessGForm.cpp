#include "ControllerAccessGForm.h"
#include "ui_ControllerAccessGForm.h"
#include "XIntegrationBase.h"
#include "CartonMenuForm.h"

ControllerAccessGForm::ControllerAccessGForm(LayersBase *Base
											,CartonMenuForm *p
											,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(Base)
	,Parent(p)
	,Trigger(p)
    ,ui(new Ui::ControllerAccessGForm)
{
    ui->setupUi(this);

	if(Trigger.Connect()==true){
		setWindowTitle(/**/"Connected");
		Trigger.Request(TriggerInfoData);
		BackupTriggerInfoData=TriggerInfoData;

		ui->spinBox1->setValue(TriggerInfoData.TriggerTiming1);
		ui->spinBox2->setValue(TriggerInfoData.TriggerTiming2);
		ui->spinBox3->setValue(TriggerInfoData.TriggerTiming3);
		ui->spinBox4->setValue(TriggerInfoData.TriggerTiming4);
		ui->spinBoxDrop->setValue(TriggerInfoData.DropTiming);
	}
	else{
		setWindowTitle(/**/"Not connected");
	}
	int	MachineCount = GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if(MachineCount==1){
		ui->frameDownStream->setVisible(false);
		ui->frame3->setVisible(false);
		ui->frame4->setVisible(false);
	}
	else
	if(MachineCount==2){
		ui->frame3->setVisible(false);
		ui->frame4->setVisible(false);
	}
	else
	if(MachineCount==3){
		ui->frame4->setVisible(false);
	}
}

ControllerAccessGForm::~ControllerAccessGForm()
{
    delete ui;
}

void ControllerAccessGForm::on_horizontalSlider1_valueChanged(int value)
{
	ui->spinBox1->setValue(value);
	ui->label_TriggerPos1MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming1)*Parent->GetParam()->TriggerMMPerPulse,'f',1));
}


void ControllerAccessGForm::on_horizontalSlider2_valueChanged(int value)
{
	ui->spinBox2->setValue(value);
	ui->label_TriggerPos2MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming2)*Parent->GetParam()->TriggerMMPerPulse,'f',1));
}


void ControllerAccessGForm::on_horizontalSlider3_valueChanged(int value)
{
	ui->spinBox3->setValue(value);
	ui->label_TriggerPos3MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming3)*Parent->GetParam()->TriggerMMPerPulse,'f',1));
}


void ControllerAccessGForm::on_horizontalSlider4_valueChanged(int value)
{
	ui->spinBox4->setValue(value);
	ui->label_TriggerPos4MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming4)*Parent->GetParam()->TriggerMMPerPulse,'f',1));
}


void ControllerAccessGForm::on_horizontalSliderDrop_valueChanged(int value)
{
	ui->spinBoxDrop->setValue(value);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.DropTiming=value;
	}
}


void ControllerAccessGForm::on_spinBox1_valueChanged(int arg1)
{
	ui->horizontalSlider1->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming1=arg1;
	}
}


void ControllerAccessGForm::on_spinBox2_valueChanged(int arg1)
{
	ui->horizontalSlider2->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming2=arg1;
	}
}


void ControllerAccessGForm::on_spinBox3_valueChanged(int arg1)
{
	ui->horizontalSlider3->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming3=arg1;
	}
}


void ControllerAccessGForm::on_spinBox4_valueChanged(int arg1)
{
	ui->horizontalSlider4->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming4=arg1;
	}
}


void ControllerAccessGForm::on_spinBoxDrop_valueChanged(int arg1)
{
	ui->horizontalSliderDrop->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.DropTiming=arg1;
	}
}


void ControllerAccessGForm::on_pushButtonOK_clicked()
{
	TriggerInfoData.TriggerTiming1	=ui->spinBox1->value();
	TriggerInfoData.TriggerTiming2	=ui->spinBox2->value();
	TriggerInfoData.TriggerTiming3	=ui->spinBox3->value();
	TriggerInfoData.TriggerTiming4	=ui->spinBox4->value();
	TriggerInfoData.DropTiming		=ui->spinBoxDrop->value();
	if(Trigger.IsConnected()==true){
		Trigger.Send(TriggerInfoData);
	}

	Parent->ParamInMaster.TriggerTiming1=TriggerInfoData.TriggerTiming1	;
	Parent->ParamInMaster.TriggerTiming2=TriggerInfoData.TriggerTiming2	;
	Parent->ParamInMaster.TriggerTiming3=TriggerInfoData.TriggerTiming3	;
	Parent->ParamInMaster.TriggerTiming4=TriggerInfoData.TriggerTiming4	;
	Parent->ParamInMaster.DropTiming	=TriggerInfoData.DropTiming		;
	
	Parent->Param.TriggerTiming1=TriggerInfoData.TriggerTiming1	;
	Parent->Param.TriggerTiming2=TriggerInfoData.TriggerTiming2	;
	Parent->Param.TriggerTiming3=TriggerInfoData.TriggerTiming3	;
	Parent->Param.TriggerTiming4=TriggerInfoData.TriggerTiming4	;
	Parent->Param.DropTiming	=TriggerInfoData.DropTiming		;

	CmdSaveParamInMaster	Cmd(GetLayersBase());
	Parent->TransmitDirectly(&Cmd);

	close();
}


void ControllerAccessGForm::on_pushButtonCancel_clicked()
{
	if(Trigger.IsConnected()==true){
		Trigger.Send(BackupTriggerInfoData);
	}

	close();
}

