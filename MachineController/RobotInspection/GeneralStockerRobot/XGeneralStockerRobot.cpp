#define	_WS2DEF_
#define	_WINSOCK2API_

#include "X6AxisCommon.h"
#include "XCameraRobotCommon.h"

#include "GeneralStockerRobot.h"
#include "XTypeDef.h"
#include "XDataInLayer.h"
#include "XDateTime.h"
#include "XLotInformation.h"
#include "XDatabaseLoader.h"
#include "XForWindows.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XResult.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XGeneralStockerClass.h"
#include "ButtonAutoMode.h"
#include "CaptureHIKCameraButton.h"
#include "ButtonAddSubPage.h"
#include "ListSelectFixedPage.h"
#include "XLightClass.h"
//#include "CameraHIKRobotGigE.h"
#include "XCameraRobotCommon.h"
#include "ControlRobotCommon.h"

//=============================================================================
GeneralStockerRobot::GeneralStockerRobot(LayersBase *Base)
	:ServiceForLayers(Base)
{
	MMap    =new QSharedMemory(SharedMemoryKey);
	Camera				=NULL;
	ErrorCount			=0;
	FormAutoMode		=NULL;
	FormSelectPage		=NULL;
	FormCaptureHIKMaster=NULL;
	FormButtonAddSub	=NULL;
	LastTargetCaptureOn	=-1;
	LastCamIndex		=0;
	CommToControllerLocal.setParent(this);

	connect(this,SIGNAL(SignalSetTotalPage(int)),this,SLOT(SlotSetTotalPage(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalCaptureImage(int)),this,SLOT(SlotCaptureImage(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalInsertPage(int)),this,SLOT(SlotInsertPage(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalRemovePage(int)),this,SLOT(SlotRemovePage(int)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalInspectImage(int)),this,SLOT(SlotInspectImage(int)),Qt::QueuedConnection);
}

GeneralStockerRobot::~GeneralStockerRobot(void)
{
	wait(1000);
	if(MMap!=NULL){
		delete	MMap;
	}
	MMap=NULL;
}

void	GeneralStockerRobot::InitialAfterParamLoaded(void)
{
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		Camera=E->GetCamera(0);
	}
	FormAutoMode		=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
	FormSelectPage		=GetLayersBase()->FindByName(/**/"List",/**/"SelectFixedPage",/**/"");

	GUIFormBase *GUIInst[100];
	int	N=GetLayersBase()->EnumGUIInst(/**/"Button",/**/"CaptureHIKCamera",GUIInst,sizeof(GUIInst)/sizeof(GUIInst[0]));
	for(int i=0;i<N;i++){
		CaptureHIKCameraButton	*f=dynamic_cast<CaptureHIKCameraButton *>(GUIInst[i]);
		if(f!=NULL){
			if(f->MasterImage==true){
				FormCaptureHIKMaster=f;
			}
		}
	}
	if(MMap->isAttached()==false){
		if(MMap->attach()==false){
		}
	}
	MMap->lock();
    struct RobotInfo  *p=(struct RobotInfo *)MMap->data();
	if(p!=NULL){
		CurrentInfo=*p;
		p->Cmd=RobotInfo::CMD_None;

	}
	MMap->unlock();

	//if(Camera!=NULL){
	//	CameraHIKRobotGigE	*ECam=dynamic_cast<CameraHIKRobotGigE	*>(Camera->GetCameraHandle());
	//	if(ECam!=NULL){
	//		connect(ECam,SIGNAL(SignalCapturedImage(int)),this,SLOT(SlotCapturedFromCamera(int)));
	//	}
	//}
	FormButtonAddSub	=GetLayersBase()->FindByName(/**/"Button",/**/"AddSubPage",/**/"");
	start();
}
void	GeneralStockerRobot::run()
{
	IntList		PageList;

	while(GetLayersBase()->GetOnTerminating()==false){
		if(MMap->isAttached()==false){
			if(MMap->attach()==false){
				if(FormAutoMode!=NULL && Camera!=NULL){
					CmdGetStateOnAutoMode	GCmd(GetLayersBase());
					FormAutoMode->TransmitDirectly(&GCmd);
					CmdSetContinuousMode	CCmd(GetLayersBase());
					CCmd.ContinuousON=GCmd.AutoModeOn;
					Camera->TransmitDirectly(&CCmd);
				}
				msleep(1000);
				continue;
			}
		}
		MMap->lock();
        struct RobotInfo  *p=(struct RobotInfo *)MMap->data();
		if(p!=NULL){
			CurrentInfo=*p;
			p->Cmd=RobotInfo::CMD_None;
		}
		MMap->unlock();

		if(p!=NULL){
			if(CurrentInfo.Cmd==RobotInfo::CMD_SetTotalPage){
				emit SignalSetTotalPage(CurrentInfo.Page);
			}
			if(CurrentInfo.Cmd==RobotInfo::CMD_CaptureImage){
				emit SignalCaptureImage(CurrentInfo.Page);
			}
			if(CurrentInfo.Cmd==RobotInfo::CMD_InsertPage){
				emit SignalInsertPage(CurrentInfo.Page);
			}
			if(CurrentInfo.Cmd==RobotInfo::CMD_RemovePage){
				emit SignalRemovePage(CurrentInfo.Page);
			}
			if(CurrentInfo.Cmd==RobotInfo::CMD_InspectImage){
				emit SignalInspectImage(CurrentInfo.Page);
			}			
		}
	}
}

void	GeneralStockerRobot::SlotSetTotalPage(int TotalPage)
{
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	E->StopCycle();
	GSleep(1000);
	LayersBase	*L=GetLayersBase();
	if(L->GetPageNumb()<TotalPage){
		for(int i=L->GetPageNumb();i<TotalPage;i++){
			CmdAddPage	AddCmd(L);
			FormButtonAddSub->TransmitDirectly(&AddCmd);
		}
	}
	else if(L->GetPageNumb()>TotalPage){
		for(int i=L->GetPageNumb()-1;i>=TotalPage;i--){
			CmdRemovePage	RemoveCmd(L);
			RemoveCmd.IndexPage=i;
			FormButtonAddSub->TransmitDirectly(&RemoveCmd);
		}
	}
	int	iMaxScanStrategy=max(GetPageNumb(),GetParamGlobal()->GetMaxStrategyCount());
	GetParamGlobal()->SetMaxStrategyCount(iMaxScanStrategy);
	for(int page=0;page<GetPageNumb();page++){
		for(int layer=0;layer<GetLayerNumb(0);layer++){
			GetParamGlobal()->SetStrategyCode(page,layer,page);
		}
		GetParamGlobal()->SetCameraNo(page,0);

		DataInPage	*Dp=GetLayersBase()->GetPageData(page);
		XYData	*xy=Dp->GetOutlineOffset();
		xy->x = 0;
		xy->y = 0;
	}

	E->StartCycle();
}

void	GeneralStockerRobot::SlotCaptureImage(int Page)
{
	MMap->lock();
	//CameraHIKRobotGigE	*ECam=dynamic_cast<CameraHIKRobotGigE *>(Camera->GetCameraHandle());
	//if(ECam!=NULL){
		//CamBufferStack		*E=ECam->GetCamBuffDim(CamBuffPoint);
		//E->CurrentPos[0]=CurrentInfo.CurrentJoint.jPos[0];
		//E->CurrentPos[1]=CurrentInfo.CurrentJoint.jPos[1];
		//E->CurrentPos[2]=CurrentInfo.CurrentJoint.jPos[2];
		//E->CurrentPos[3]=CurrentInfo.CurrentJoint.jPos[3];
		//E->CurrentPos[4]=CurrentInfo.CurrentJoint.jPos[4];
		//E->CurrentPos[5]=CurrentInfo.CurrentJoint.jPos[5];
	//}
	MMap->unlock();
}
void	GeneralStockerRobot::SlotInsertPage(int Page)
{
	LayersBase	*L=GetLayersBase();
	CmdInsertPage	AddCmd(L);
	AddCmd.IndexPage=Page;
	FormButtonAddSub->TransmitDirectly(&AddCmd);
}
void	GeneralStockerRobot::SlotRemovePage(int Page)
{
	LayersBase	*L=GetLayersBase();
	if(0<=Page && Page<L->GetPageNumb()){
		CmdRemovePage	RemoveCmd(L);
		RemoveCmd.IndexPage=Page;
		FormButtonAddSub->TransmitDirectly(&RemoveCmd);
	}
}
void	GeneralStockerRobot::SlotInspectImage(int Page)
{
	LayersBase	*L=GetLayersBase();
	MMap->lock();

	CmdSetCaptureOne	Cmd(L);
	Cmd.Index = Page;
	Camera->TransmitDirectly(&Cmd);
	//CameraHIKRobotGigE	*ECam=dynamic_cast<CameraHIKRobotGigE *>(Camera->GetCameraHandle());
	//if(ECam!=NULL){
		//CamBufferStack		*E=ECam->GetCamBuffDim(CamBuffPoint);
		//E->CurrentPos[0]=CurrentInfo.CurrentJoint.jPos[0];
		//E->CurrentPos[1]=CurrentInfo.CurrentJoint.jPos[1];
		//E->CurrentPos[2]=CurrentInfo.CurrentJoint.jPos[2];
		//E->CurrentPos[3]=CurrentInfo.CurrentJoint.jPos[3];
		//E->CurrentPos[4]=CurrentInfo.CurrentJoint.jPos[4];
		//E->CurrentPos[5]=CurrentInfo.CurrentJoint.jPos[5];
	//}
	MMap->unlock();

	//float	Pos[6];
	//float	CompareParamJ[6];
	//MMap->lock();
	//struct RobotInfo  *p=(struct RobotInfo *)MMap->data();
	//if(p!=NULL){
	//	p->ReqCaptureNo=Page;
	//}
	//MMap->unlock();
	//
	//bool	Flag=true;
	//while(Flag){
	//	MMap->lock();
	//	struct RobotInfo  *p=(struct RobotInfo *)MMap->data();
	//	if(p!=NULL){
	//		if(p->ReqCaptureNo<0){
	//			Flag=false;
	//			Pos[0]=p->CurrentJoint.jPos[0];
	//			Pos[1]=p->CurrentJoint.jPos[1];
	//			Pos[2]=p->CurrentJoint.jPos[2];
	//			Pos[3]=p->CurrentJoint.jPos[3];
	//			Pos[4]=p->CurrentJoint.jPos[4];
	//			Pos[5]=p->CurrentJoint.jPos[5];
	//			CompareParamJ[0]=p->CurrentJoint.jPos[0];
	//			CompareParamJ[1]=p->CurrentJoint.jPos[1];
	//			CompareParamJ[2]=p->CurrentJoint.jPos[2];
	//			CompareParamJ[3]=p->CurrentJoint.jPos[3];
	//			CompareParamJ[4]=p->CurrentJoint.jPos[4];
	//			CompareParamJ[5]=p->CurrentJoint.jPos[5];
	//		}
	//	}
	//	MMap->unlock();
	//}
	//
	//CmdReqCaptureClosed	RCmd(L);
	//RCmd.Pos[0]=Pos[0];
	//RCmd.Pos[1]=Pos[1];
	//RCmd.Pos[2]=Pos[2];
	//RCmd.Pos[3]=Pos[3];
	//RCmd.Pos[4]=Pos[4];
	//RCmd.Pos[5]=Pos[5];
	//RCmd.CompareParamJ[0]=CompareParamJ[0];
	//RCmd.CompareParamJ[1]=CompareParamJ[1];
	//RCmd.CompareParamJ[2]=CompareParamJ[2];
	//RCmd.CompareParamJ[3]=CompareParamJ[3];
	//RCmd.CompareParamJ[4]=CompareParamJ[4];
	//RCmd.CompareParamJ[5]=CompareParamJ[5];
	//RCmd.Index	=LastCamIndex;
	//if(Camera!=NULL){
	//	Camera->TransmitDirectly(&RCmd);
	//	LastCamIndex=RCmd.Index;
	//}
	//
	//CmdSetCaptureOne	CCmd(L);
	//if(Camera!=NULL){
	//	CCmd.Index=RCmd.Index;
	//	Camera->TransmitDirectly(&CCmd);
	//}

	GSleep(100);
}


bool	GeneralStockerRobot::WriteToController(void)
{
	if(CommToControllerLocal.state()!=QLocalSocket::ConnectedState){
		CommToControllerLocal.connectToServer(CommRobotSocket);
		if(CommToControllerLocal.waitForConnected()==false){
			return false;
		}
	}
	if(CommToControllerLocal.state()==QLocalSocket::ConnectedState){
		BYTE	Cmd=1;
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		::Save(&Buff,Cmd);
		::Save(&Buff,ControllerData);

		QByteArray	PacketData=Buff.buffer();
		CommToControllerLocal.write(PacketData);
		CommToControllerLocal.flush();
		return true;
	}
	return false;
}
	
void	GeneralStockerRobot::TransmitDirectly(GUIDirectMessage *packet)
{
	//CmdReqControllerData	*CmdReqControllerDataVar=dynamic_cast<CmdReqControllerData *>(packet);
	//if(CmdReqControllerDataVar!=NULL){
	//	ReadFromController();
	//	return;
	//}
	CmdTransmitControllerData	*CmdTransmitControllerDataVar=dynamic_cast<CmdTransmitControllerData *>(packet);
	if(CmdTransmitControllerDataVar!=NULL){
		WriteToController();
		return;
	}
	//CmdGetControllerData	*CmdGetControllerDataVar=dynamic_cast<CmdGetControllerData *>(packet);
	//if(CmdGetControllerDataVar!=NULL){
	//	CmdGetControllerDataVar->ControllerData=ControllerData;
	//	return;
	//}
	//CmdSendControllerData	*CmdSendControllerDataVar=dynamic_cast<CmdSendControllerData *>(packet);
	//if(CmdSendControllerDataVar!=NULL){
	//	ControllerData=CmdGetControllerDataVar->ControllerData;
	//	return;
	//}
}

void	GeneralStockerRobot::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		QVariant	data;
		if(GetLayersBase()->LoadMasterFieldData(/**/"ROBOTSPLINE", data)==true){
			ControllerData	=data.toByteArray();
			WriteToController();
		}
		GetParamGlobal()->SetMaxStrategyCount(GetPageNumb());
		return;
	}
	//CreateNewMasterSpecifiedBroadcaster		*CreateNewMasterSpecifiedBroadcasterVar=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	//CreateUpdateMasterSpecifiedBroadcaster	*CreateUpdateMasterSpecifiedBroadcasterVar=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	//if(CreateNewMasterSpecifiedBroadcasterVar!=NULL
	//|| CreateUpdateMasterSpecifiedBroadcasterVar!=NULL){
	//	if(ReadFromController()==true){
	//		QVariant	data=ControllerData;
	//		GetLayersBase()->AddMasterFieldData(/**/"ROBOTSPLINE",data);
	//	}
	//	return;
	//}
}
ExeResult	GeneralStockerRobot::ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res)
{
	int	iMaxScanStrategy=max(GetPageNumb(),GetParamGlobal()->GetMaxStrategyCount());
	GetParamGlobal()->SetMaxStrategyCount(iMaxScanStrategy);
	for(int page=0;page<GetPageNumb();page++){
		for(int layer=0;layer<GetLayerNumb(0);layer++){
			GetParamGlobal()->SetStrategyCode(page,layer,page);
		}
		GetParamGlobal()->SetCameraNo(page,0);
		DataInPage	*Dp=GetLayersBase()->GetPageData(page);
		XYData	*xy=Dp->GetOutlineOffset();
		xy->x = 0;
		xy->y = 0;
	}
	return _ER_true;
}