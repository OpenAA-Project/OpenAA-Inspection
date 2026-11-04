#define	_WS2DEF_
#define	_WINSOCK2API_


#include "GUIShowPointsButtonForm.h"
#include "ui_GUIShowPointsButtonForm.h"
#include "XDataInLayer.h"
#include "XGeneralStocker.h"
#include "GeneralStockerRobot.h"
#include "ShowPointsDialog.h"
#include "XEntryPoint.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include "XCameraRobotCommon.h"
#include "ShowAllImageForm.h"

GUIShowPointsButtonForm::GUIShowPointsButtonForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::GUIShowPointsButtonForm)
{
    ui->setupUi(this);
    CapturedCount=0;
    LastCapturedCount=0;
    AllImageForm    =NULL;
}

GUIShowPointsButtonForm::~GUIShowPointsButtonForm()
{
    if(AllImageForm!=NULL){
        AllImageForm->deleteLater();
    }
    delete ui;
}

void	GUIShowPointsButtonForm::ReadyParam(void)
{
    int CountCamera=GetParamComm()->GetLocalCameraNumb(0);
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		for(int i=0;i<CountCamera;i++){
			Cam[i]=E->GetCamera(i);
		}
	}
    TM.setInterval(500);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotShowFPS()));
    TM.setSingleShot(false);
    TM.start();
}

void    GUIShowPointsButtonForm::SlotShowFPS()
{
    DWORD   NowTime=::GetComputerMiliSec();
    DWORD   DiffT=NowTime-LastTime;
    if(DiffT>0){
        CmdReqCapturedCount Cmd(GetLayersBase());
        if(Cam[0]!=NULL){
            Cam[0]->TransmitDirectly(&Cmd);
        }
        CapturedCount=Cmd.CapturedCount;

        double  t=((double)(CapturedCount-LastCapturedCount))*1000.0/((double)DiffT);
        ui->labelFPS->setText(QString::number(t,'f',2));
        LastTime=NowTime;
        LastCapturedCount=CapturedCount;
    }
}

void GUIShowPointsButtonForm::on_pushButtonReceive_clicked()
{
    CmdReqControllerData    RCmd(GetLayersBase());
    GetLayersBase()->GetGeneralStocker()->TransmitDirectlyByName(ControlledGeneralStocker,&RCmd);
}


void GUIShowPointsButtonForm::on_pushButtonSend_clicked()
{
    CmdTransmitControllerData    RCmd(GetLayersBase());
    GetLayersBase()->GetGeneralStocker()->TransmitDirectlyByName(ControlledGeneralStocker,&RCmd);
}


void GUIShowPointsButtonForm::on_pushButtonShowPoints_clicked()
{
    ShowPointsDialog    D(GetLayersBase());
    D.exec();
}


void GUIShowPointsButtonForm::on_pushButtonAllImage_clicked()
{
    if(AllImageForm==NULL){
        AllImageForm=new ShowAllImageForm(this,GetLayersBase());
    }
    AllImageForm->show();
    AllImageForm->raise();
}

