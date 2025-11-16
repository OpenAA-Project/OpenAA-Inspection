#include "CartonMenuResource.h"
#include "EachSettingDialog.h"
#include "ui_EachSettingDialog.h"
#include "CartonMenuForm.h"
#include "ButtonSettingThresholdForm.h"
#include "SetExposureDialog.h"

EachSettingDialog::EachSettingDialog(LayersBase *Base ,CartonMenuForm *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),Parent(p),
    ui(new Ui::EachSettingDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	SetRunningGray();

	ui->PushButtonBlade->setVisible(Parent->ShowBlade);

	TM.setInterval(1000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int ,int64,bool)),this,SLOT(SlotInspectionDone(int,int64 ,bool)));

	int	MachineCount = GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if (MachineCount == 1) {
		ui->PushButtonBladeSettingThresholdBottom	->setVisible(false);
		ui->PushButtonSettingThresholdMono			->setVisible(false);
	}
	else
	if (MachineCount == 2) {
		ui->PushButtonSettingThresholdMono			->setVisible(false);
	}
	if(GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference")==NULL){
		ui->PushButtonColorDifference->setVisible(false);
	}
	//if(GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureLineMove")==NULL){
	//	ui->PushButtonBlade->setVisible(false);
	//}

	for(int i=0;i<MachineCount;i++){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(m!=NULL){
			QString	s=m->GetMachineName();
			if(i==0){
				ui->PushButtonSettingThresholdTop	->setText(s+QString(LangSolver.GetString(EachSettingDialog_LS,LID_4)/*"驍ｵ�ｺ陷会ｽｱ遯ｶ�ｳ驍ｵ�ｺ�ｽ�ｽ�ｽ�ｽ�ｽ�､"*/));
			}
			else if(i==1){
				ui->PushButtonBladeSettingThresholdBottom	->setText(s+QString(LangSolver.GetString(EachSettingDialog_LS,LID_5)/*"驍ｵ�ｺ陷会ｽｱ遯ｶ�ｳ驍ｵ�ｺ�ｽ�ｽ�ｽ�ｽ�ｽ�､"*/));
			}
			else if(i==2){
				ui->PushButtonSettingThresholdMono	->setText(s+QString(LangSolver.GetString(EachSettingDialog_LS,LID_6)/*"驍ｵ�ｺ陷会ｽｱ遯ｶ�ｳ驍ｵ�ｺ�ｽ�ｽ�ｽ�ｽ�ｽ�､"*/));
			}
		}
	}

}

EachSettingDialog::~EachSettingDialog()
{
 	disconnect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int ,int64,bool)),this,SLOT(SlotInspectionDone(int,int64 ,bool)));
	disconnect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));

	delete ui;
}

void	EachSettingDialog::SetRunningGray(void)
{
	//if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		ui->PushButtonSwitchPhase	->setEnabled(true);
		ui->PushButtonMask			->setEnabled(true);
		ui->PushButtonAlignment		->setEnabled(true);
		ui->PushButtonInspection	->setEnabled(true);
		ui->PushButtonBlade			->setEnabled(true);
		ui->PushButtonAutoGenerate	->setEnabled(true);
	//}
	//else{
	//	ui->PushButtonSwitchPhase	->setEnabled(false);
	//	ui->PushButtonMask			->setEnabled(false);
	//	ui->PushButtonAlignment		->setEnabled(false);
	//	ui->PushButtonInspection	->setEnabled(false);
	//	ui->PushButtonBlade			->setEnabled(false);
	//	ui->PushButtonAutoGenerate	->setEnabled(false);
	//}
}

void EachSettingDialog::on_PushButtonSwitchPhase_clicked()
{
	Parent->on_PushButtonSwitchPhase_clicked();
	close();
}

void EachSettingDialog::on_PushButtonMask_clicked()
{
	Parent->on_PushButtonMask_clicked();
	close();
}

void EachSettingDialog::on_PushButtonAlignment_clicked()
{
	Parent->on_PushButtonAlignment_clicked();
	close();
}

void EachSettingDialog::on_PushButtonInspection_clicked()
{
	Parent->on_PushButtonInspection_clicked();
	close();
}

void EachSettingDialog::on_PushButtonBlade_clicked()
{
	Parent->on_PushButtonBlade_clicked();
	close();
}

void EachSettingDialog::on_PushButtonAutoGenerate_clicked()
{
	Parent->on_PushButtonAutoGenerate_clicked();
	close();
}

void EachSettingDialog::on_PushButtonColorDifference_clicked()
{
	Parent->on_PushButtonColorDifference_clicked();
	close();
}

void EachSettingDialog::on_PushButtonSettingThresholdTop_clicked()
{
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"SettingThreshold",GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=dynamic_cast<ButtonSettingThresholdForm *>(GUIRet[i]);
		if(f->SlaveNo==0){
			IntegrationClickSettingThresholdForm	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
			close();
			break;
		}
	}
}

void EachSettingDialog::on_PushButtonBladeSettingThresholdBottom_clicked()
{
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"SettingThreshold",GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=dynamic_cast<ButtonSettingThresholdForm *>(GUIRet[i]);
		if(f->SlaveNo==1){
			IntegrationClickSettingThresholdForm	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
			close();
			break;
		}
	}
}

void EachSettingDialog::on_PushButtonClose_clicked()
{
	close();
}


void	EachSettingDialog::SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK)
{
	SetRunningGray();
}

void	EachSettingDialog::SlotTimeOut()
{
	SetRunningGray();
}

void EachSettingDialog::on_PushButtonMakeAverageImage_clicked()
{
	Parent->OpenMakeAverage();
	close();

}

void EachSettingDialog::on_PushButtonSettingExpose_clicked()
{
	SetExposureDialog	D(GetLayersBase());
	D.exec();
	close();
}

void EachSettingDialog::on_PushButtonBCode_clicked()
{
	Parent->on_PushButtonBCode_clicked();
	close();
}

void EachSettingDialog::on_PushButtonMeasure_clicked()
{
	Parent->on_PushButtonBlade_clicked();
	close();
}

void EachSettingDialog::on_PushButtonSettingThresholdMono_clicked()
{
	GUIFormBase *GUIRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"SettingThreshold",GUIRet ,100);
	for(int i=0;i<n;i++){
		ButtonSettingThresholdForm	*f=dynamic_cast<ButtonSettingThresholdForm *>(GUIRet[i]);
		if(f->SlaveNo==2){
			IntegrationClickSettingThresholdForm	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
			close();
			break;
		}
	}
}

void EachSettingDialog::on_PushButtonCalcFinalize_clicked()
{
	Parent->CalcFinalize();
}

void EachSettingDialog::on_PushButtonResetSlaves_clicked()
{
	Parent->ResetSlaves();
}

