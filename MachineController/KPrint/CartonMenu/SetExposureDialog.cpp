#include "CartonMenuResource.h"
#include "SetExposureDialog.h"
#include "ui_SetExposureDialog.h"
#include "IntegrationChangeCameraSetting.h"
#include "CartonMenuForm.h"

SetExposureDialog::SetExposureDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SetExposureDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	int	SlaveCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	for(int i=0;i<SlaveCount;i++){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
		if(m!=NULL){
			QString	s=m->GetMachineName()+QString(LangSolver.GetString(SetExposureDialog_LS,LID_29)/*"驛｢�ｧ�ｽ�ｫ驛｢譎｢�ｽ�｡驛｢譎｢�ｽ�ｩ"*/);
			if(i==0){
				ui->labelTop	->setText(s);
			}
			else if(i==1){
				ui->labelBottom	->setText(s);
			}
			else if(i==2){
				ui->labelMono	->setText(s);
			}
		}
	}
	if(SlaveCount==2){
		ui->frameMono->setVisible(false);
	}
	else
	if(SlaveCount==1){
		ui->frameBottom	->setVisible(false);
		ui->frameMono	->setVisible(false);
	}
}

SetExposureDialog::~SetExposureDialog()
{
    delete ui;
}

void SetExposureDialog::on_PushButtonSettingTop1_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
	if(f!=NULL){
		IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
		RCmd.CameraSettingFileName=/**/"Cam1.dat";
		RCmd.MachineID=1;
		f->TransmitDirectly(&RCmd);
	}
}

void SetExposureDialog::on_PushButtonSettingTop2_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
	if(f!=NULL){
		IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
		RCmd.CameraSettingFileName=/**/"Cam2.dat";
		RCmd.MachineID=1;
		f->TransmitDirectly(&RCmd);
	}
}

void SetExposureDialog::on_PushButtonSettingTop3_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
	if(f!=NULL){
		IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
		RCmd.CameraSettingFileName=/**/"Cam3.dat";
		RCmd.MachineID=1;
		f->TransmitDirectly(&RCmd);
	}
}
void SetExposureDialog::on_PushButtonSettingTopHolo_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
    if(f!=NULL){
        IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
        RCmd.CameraSettingFileName=/**/"Cam4.dat";
        RCmd.MachineID=1;
        f->TransmitDirectly(&RCmd);
    }
}
void SetExposureDialog::on_PushButtonSettingBottom1_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
	if(f!=NULL){
		IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
		RCmd.CameraSettingFileName=/**/"Cam1.dat";
		RCmd.MachineID=2;
		f->TransmitDirectly(&RCmd);
	}
}

void SetExposureDialog::on_PushButtonSettingBottom2_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
	if(f!=NULL){
		IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
		RCmd.CameraSettingFileName=/**/"Cam2.dat";
		RCmd.MachineID=2;
		f->TransmitDirectly(&RCmd);
	}
}

void SetExposureDialog::on_PushButtonSettingBottom3_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
	if(f!=NULL){
		IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
		RCmd.CameraSettingFileName=/**/"Cam3.dat";
		RCmd.MachineID=2;
		f->TransmitDirectly(&RCmd);
	}
}
void SetExposureDialog::on_PushButtonSettingBottomHolo_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
    if(f!=NULL){
        IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
        RCmd.CameraSettingFileName=/**/"Cam4.dat";
        RCmd.MachineID=2;
        f->TransmitDirectly(&RCmd);
    }
}
void SetExposureDialog::on_PushButtonClose_clicked()
{
	close();
}

void SetExposureDialog::on_PushButtonSettingMono1_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
    if(f!=NULL){
        IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
        RCmd.CameraSettingFileName=/**/"Cam1.dat";
        RCmd.MachineID=3;
        f->TransmitDirectly(&RCmd);
    }
}

void SetExposureDialog::on_PushButtonSettingMono2_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
    if(f!=NULL){
        IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
        RCmd.CameraSettingFileName=/**/"Cam2.dat";
        RCmd.MachineID=3;
        f->TransmitDirectly(&RCmd);
    }
}

void SetExposureDialog::on_PushButtonSettingMono3_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
    if(f!=NULL){
        IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
        RCmd.CameraSettingFileName=/**/"Cam3.dat";
        RCmd.MachineID=3;
        f->TransmitDirectly(&RCmd);
    }
}

void SetExposureDialog::on_PushButtonSettingMonoHolo_clicked()
{
    GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ChangeCameraSetting",/**/"");
    if(f!=NULL){
        IntegrationChangeCameraSettingFile	RCmd(GetLayersBase());
        RCmd.CameraSettingFileName=/**/"Cam4.dat";
        RCmd.MachineID=3;
        f->TransmitDirectly(&RCmd);
    }
}
