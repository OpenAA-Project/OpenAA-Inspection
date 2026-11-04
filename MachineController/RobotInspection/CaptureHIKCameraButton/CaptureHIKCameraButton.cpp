/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CaptureHIKCameraButton\CaptureHIKCameraButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "CaptureHIKCameraButton.h"
#include "ListSelectFixedPage.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataInLayer.h"
#include "XCameraClass.h"
#include "XEntryPoint.h"
#include "XCameraRobotCommon.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"CaptureHIKCamera";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Capture HIK Camera");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CaptureHIKCameraButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((CaptureHIKCameraButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((CaptureHIKCameraButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((CaptureHIKCameraButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((CaptureHIKCameraButton *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"MasterImage";
	Data[4].Pointer				 =&((CaptureHIKCameraButton *)Instance)->MasterImage;
	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCopyImage.png")));
}

//==================================================================================================
CaptureHIKCameraButton::CaptureHIKCameraButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"CaptureHIKCameraButton");
	Msg=/**/"Capture HIK";
	resize(80,25);
	MasterImage	=true;
	Cam=NULL;

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

CaptureHIKCameraButton::~CaptureHIKCameraButton(void)
{
	if(Cam!=NULL){
		delete	[]Cam;
		Cam=NULL;
	}
}

void	CaptureHIKCameraButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
void	CaptureHIKCameraButton::ReadyParam(void)
{
	ListSelectPage=GetLayersBase()->FindByName(/**/"List",/**/"SelectFixedPage",/**/"");
	CountCamera=GetParamComm()->GetLocalCameraNumb(0);
	if(Cam==NULL){
		Cam=new CameraClass*[CountCamera];
		for(int i=0;i<CountCamera;i++){
			Cam[i]=NULL;
		}
	}
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		for(int i=0;i<CountCamera;i++){
			Cam[i]=E->GetCamera(i);
		}
	}
}
void	CaptureHIKCameraButton::ResizeAction()
{
	Button.resize(width(),height());
}

void	CaptureHIKCameraButton::SlotClicked (bool checked)
{
	if(ListSelectPage!=NULL){
		CmdGetCurrentPage	Cmd(GetLayersBase());
		ListSelectPage->TransmitDirectly(&Cmd);
		if(Cmd.CurrentPage>=0){
			if(MasterImage==true){
				DataInPage	*Dp=GetLayersBase()->GetPageData(Cmd.CurrentPage);
				ImageBuffer	*BuffDim[3];
				for(int i=0;i<CountCamera;i++){
					for(int layer=0;layer<GetLayerNumb(Cmd.CurrentPage);layer++){
						BuffDim[layer]=Dp->GetLayerData(layer)->GetMasterBuffPointer();
					}
					while(Cam[i]->StartCaptureContinuously(BuffDim,GetLayerNumb(Cmd.CurrentPage),NULL)==false){
						GSleep(10);
					}
				}
			}
			else{
				GetLayersBase()->SetCurrentStrategicNumber(Cmd.CurrentPage);
				for(int i=0;i<CountCamera;i++){
					CmdSetCaptureOne	RCmd(GetLayersBase());
					if(Cam[i]!=NULL){
						Cam[i]->TransmitDirectly(&RCmd);
					}
				}
			}
		}
	}
}

void	CaptureHIKCameraButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPushButton	*CmdPushButtonVar=dynamic_cast<CmdPushButton *>(packet);
	if(CmdPushButtonVar!=NULL){
		CmdSetCurrentPage	Cmd(GetLayersBase());
		Cmd.CurrentPage=CmdPushButtonVar->Page;
		ListSelectPage->TransmitDirectly(&Cmd);
		SlotClicked(true);
		return;
	}
}

void	CaptureHIKCameraButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,"Execute","Capture",this);
	p->SetMenuNumber(1059);
	Info.AppendList(p);
}
void	CaptureHIKCameraButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}


