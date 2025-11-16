#include "CartonMenuResource.h"
#include "AdjustTriggerForm.h"
#include "ui_AdjustTriggerForm.h"
#include "CartonMenuForm.h"
#include<QMessageBox>

AdjustTriggerForm::AdjustTriggerForm(CartonMenuForm *p ,QWidget *parent) :
    QWidget(parent)
	,Parent(p)
	,Trigger(p)
    ,ui(new Ui::AdjustTriggerForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Widget | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	TriggerInfoData.TriggerTiming1	=Parent->Param.TriggerTiming1;
	TriggerInfoData.TriggerTiming2	=Parent->Param.TriggerTiming2;
	TriggerInfoData.TriggerTiming3	=Parent->Param.TriggerTiming3;
	TriggerInfoData.TriggerTiming4	=Parent->Param.TriggerTiming4;
	TriggerInfoData.DropTiming		=Parent->Param.DropTiming;

	//if(Trigger.Connect()==true){
	//	setWindowTitle(/**/"Connected");
	//	Trigger.Request(TriggerInfoData);
		BackupTriggerInfoData=TriggerInfoData;

		ui->spinBox1->setValue(TriggerInfoData.TriggerTiming1);
		ui->spinBox2->setValue(TriggerInfoData.TriggerTiming2);
		ui->spinBox3->setValue(TriggerInfoData.TriggerTiming3);
		ui->spinBox4->setValue(TriggerInfoData.TriggerTiming4);
		ui->spinBoxDrop->setValue(TriggerInfoData.DropTiming);
	//}
	//else{
	//	setWindowTitle(/**/"Not connected");
	//}
	int	MachineCount = p->GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
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

AdjustTriggerForm::~AdjustTriggerForm()
{
    delete ui;
	deleteLater();
}

void AdjustTriggerForm::on_horizontalSlider1_valueChanged(int value)
{
	ui->spinBox1->setValue(value);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming1=value;
		Trigger.Send(TriggerInfoData);
	}
	ui->label_TriggerPos1MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming1)*Parent->Param.TriggerMMPerPulse,'f',1));
}

void AdjustTriggerForm::on_horizontalSlider2_valueChanged(int value)
{
	ui->spinBox2->setValue(value);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming2=value;
		Trigger.Send(TriggerInfoData);
	}
	ui->label_TriggerPos2MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming2)*Parent->Param.TriggerMMPerPulse,'f',1));
}

void AdjustTriggerForm::on_pushButtonOK_clicked()
{
	TriggerInfoData.TriggerTiming1	=ui->spinBox1->value();
	TriggerInfoData.TriggerTiming2	=ui->spinBox2->value();
	TriggerInfoData.TriggerTiming3	=ui->spinBox3->value();
	TriggerInfoData.TriggerTiming4	=ui->spinBox4->value();
	TriggerInfoData.DropTiming		=ui->spinBoxDrop->value();

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

	if(Parent->SendTriggerInfo()==false){
		QMessageBox::warning(NULL,LangSolver.GetString(AdjustTriggerForm_LS,LID_13)/*"Warning"*/
							,LangSolver.GetString(AdjustTriggerForm_LS,LID_27)/*"郢ｧ�ｳ郢晢ｽｳ郢晏現ﾎ溽ｹ晢ｽｼ郢晢ｽｩ郢晢ｽｼ邵ｺ�ｨ鬨ｾ螢ｻ�ｿ�｡邵ｺ�ｧ邵ｺ髦ｪ竊醍ｸｺ�ｽ�ｽ邵ｺ�ｧ髫ｪ�ｭ陞ｳ螢ｹ縲堤ｸｺ髦ｪ竏ｪ邵ｺ蟶呻ｽ鍋ｸｺ�ｧ邵ｺ蜉ｱ笳�ｸｲ�ｽ*/);
	}

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Parent->ParamInMaster.Save(&Buff);
	Parent->GetLayersBase()->GetIntegrationBasePointer()->GetCommonData()->Something=Buff.buffer();

	close();
}

void AdjustTriggerForm::on_pushButtonCancel_clicked()
{
	if(Trigger.IsConnected()==true){
		Trigger.Send(BackupTriggerInfoData);
	}

	close();
}

void AdjustTriggerForm::on_spinBox1_valueChanged(int arg1)
{
	ui->horizontalSlider1->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming1=arg1;
		//Trigger.Send(TriggerInfoData);
	}
}

void AdjustTriggerForm::on_spinBox2_valueChanged(int arg1)
{
	ui->horizontalSlider2->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming2=arg1;
		//Trigger.Send(TriggerInfoData);
	}
}

void AdjustTriggerForm::on_horizontalSliderDrop_valueChanged(int value)
{
	ui->spinBoxDrop->setValue(value);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.DropTiming=value;
		//Trigger.Send(TriggerInfoData);
	}
}

void AdjustTriggerForm::on_spinBoxDrop_valueChanged(int arg1)
{
	ui->horizontalSliderDrop->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.DropTiming=arg1;
		//Trigger.Send(TriggerInfoData);
	}
}

void AdjustTriggerForm::on_horizontalSlider3_valueChanged(int value)
{
	ui->spinBox3->setValue(value);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming3=value;
		//Trigger.Send(TriggerInfoData);
	}
	ui->label_TriggerPos3MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming3)*Parent->Param.TriggerMMPerPulse,'f',1));

}


void AdjustTriggerForm::on_horizontalSlider4_valueChanged(int value)
{
	ui->spinBox4->setValue(value);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming4=value;
		//Trigger.Send(TriggerInfoData);
	}
	ui->label_TriggerPos4MM->setText(QString::number((value-BackupTriggerInfoData.TriggerTiming4)*Parent->Param.TriggerMMPerPulse,'f',1));

}


void AdjustTriggerForm::on_spinBox3_valueChanged(int arg1)
{
	ui->horizontalSlider3->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming3=arg1;
		//Trigger.Send(TriggerInfoData);
	}
}


void AdjustTriggerForm::on_spinBox4_valueChanged(int arg1)
{
	ui->horizontalSlider4->setValue(arg1);
	if(Trigger.IsConnected()==true){
		TriggerInfoData.TriggerTiming4=arg1;
		//Trigger.Send(TriggerInfoData);
	}
}

