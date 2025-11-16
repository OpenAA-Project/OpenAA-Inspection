/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyDXFOperationImagePanel\EasyDXFOperationImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyDXFOperationImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XDXFOperation.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XIntegrationBase.h"
#include "EasyPropertyDXFOperationForm.h"
//#include "XPropertyDotColorMatchingPacket.h"


const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyDXFOperationImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyDXFOperationImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

	(*Base)	=new IntegrationCmdMove		(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdSelect	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
	Q_CLEANUP_RESOURCE(IntegrationLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	EasyDXFOperationImagePanel	*B=new EasyDXFOperationImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyDXFOperationImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;

	return(N);

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyDXFOperationImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"DXFOperation"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyDXFOperationImagePanel::EasyDXFOperationImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"DXFOperation",parent)
{
	OnMoving=false;
	SetMode(mtFrameDraw::fdPoly);

	connect(this,SIGNAL(SignalModeChanged()),this,SLOT(SlotModeChanged()));

}
void	EasyDXFOperationImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyDXFOperationImagePanel::CreateDrawAttrPointer(void)
{
	return new DXFOperationDrawAttr(
							 Qt::green		,128
							,Qt::magenta	,128
							,Qt::red		,128);
}

void	EasyDXFOperationImagePanel::SlotCanvasMouseMove (int globalX ,int globalY)
{
	if(IsMoveMode()==true){
		if(OnMoving==true){
			int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
			IntegrationCmdMove	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.GlobalDx=globalX-LastPosX;
			RCmd.GlobalDy=globalY-LastPosY;
			RCmd.Send(NULL,SlaveNo,0);
			LastPosX=globalX;
			LastPosY=globalY;
		}
	}
	else{
		IntegrationAlgoSimpleImagePanel::SlotCanvasMouseMove (globalX ,globalY);
	}
}
void	EasyDXFOperationImagePanel::SlotJustMouseLPress(int globalX ,int globalY)
{
	if(IsMoveMode()==true){
		if(OnMoving==false){
			OnMoving=true;
			int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
			IntegrationCmdSelect	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.SelectMode=true;
			RCmd.ActivePage=0;
			EasyPropertyDXFOperationForm	*f=GetPropertyForm();
			if(f!=NULL){
				CmdReqCurrentPage	SCmd(GetLayersBase());
				f->TransmitDirectly(&SCmd);
				RCmd.ActivePage=SCmd.ActivePage;
			}
			RCmd.Send(NULL,SlaveNo,0);

			LastPosX=globalX;
			LastPosY=globalY;
		}
		else{
			LastPosX=globalX;
			LastPosY=globalY;
		}
	}
	//else{
	//	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseLDown (globalX ,globalY);
	//}
}
void	EasyDXFOperationImagePanel::SlotJustMouseLRelease(int globalX ,int globalY)
{
	if(IsMoveMode()==true){
		if(OnMoving==true){
			OnMoving=false;
			int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
			IntegrationCmdSelect	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.SelectMode=false;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
	//else{
	//	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseRDown (globalX ,globalY);
	//}

}

bool	EasyDXFOperationImagePanel::IsMoveMode(void)
{
	EasyPropertyDXFOperationForm	*AccessForm=GetPropertyForm();
	if(AccessForm!=NULL){
		IntegrationCmdReqMoveMode	RCmd(GetLayersBase());
		AccessForm->TransmitDirectly(&RCmd);
		return RCmd.MoveMode;
	}
	return false;
}
EasyPropertyDXFOperationForm	*EasyDXFOperationImagePanel::GetPropertyForm(void)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDXFOperation" ,GUIFormRet,100);
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(ThisM==NULL)
		return NULL;
	int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	EasyPropertyDXFOperationForm	*AccessForm=NULL;
	for(int i=0;i<n;i++){
		if(((EasyPropertyDXFOperationForm *)GUIFormRet[i])->SlaveNo==SlaveNo){
			AccessForm=((EasyPropertyDXFOperationForm *)GUIFormRet[i]);
			break;
		}
	}
	return AccessForm;
}

void	EasyDXFOperationImagePanel::SlotModeChanged  ()
{
	EasyPropertyDXFOperationForm	*AccessForm=GetPropertyForm();
	if(AccessForm!=NULL){
		IntegrationCmdSetMoveMode	RCmd(GetLayersBase());
		RCmd.MoveMode=false;
		AccessForm->TransmitDirectly(&RCmd);
	}
	if(OnMoving==true){
		OnMoving=false;
		int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
		IntegrationCmdSelect	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.SelectMode=false;
		RCmd.Send(NULL,SlaveNo,0);
	}
}

//=================================================================================================

IntegrationCmdMove::IntegrationCmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdMove::Load(QIODevice *f)
{
	if(::Load(f,GlobalDx)==false)
		return false;
	if(::Load(f,GlobalDy)==false)
		return false;
	return true;
}
bool	IntegrationCmdMove::Save(QIODevice *f)
{
	if(::Save(f,GlobalDx)==false)
		return false;
	if(::Save(f,GlobalDy)==false)
		return false;
	return true;
}

void	IntegrationCmdMove::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Inspection",/**/"DXFOperationImagePanel",/**/"");
	if(Form!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)Form;
		W->ExecuteMove(GlobalDx,GlobalDy);
	}
}

IntegrationCmdSelect::IntegrationCmdSelect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSelect::Load(QIODevice *f)
{
	if(::Load(f,SelectMode)==false)
		return false;
	if(::Load(f,ActivePage)==false)
		return false;
	return true;
}
bool	IntegrationCmdSelect::Save(QIODevice *f)
{
	if(::Save(f,SelectMode)==false)
		return false;
	if(::Save(f,ActivePage)==false)
		return false;

	return true;
}

void	IntegrationCmdSelect::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Inspection",/**/"DXFOperationImagePanel",/**/"");
	if(Form!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)Form;
		if(SelectMode==true){
			if(GetPageNumb()==1){
				W->SlotSelectAll();
			}
			else{
				W->ButtonExecuteSelectByPage(ActivePage);
			}
		}
		else{
			W->ExecuteReleaseAllSelection();
		}
	}
}
