#include "AutoAlignmentImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoAlignmentImagePanel\AutoAlignmentImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoAlignmentImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "XAutoAlignmentPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"AutoAlignmentImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"AutoAlignment ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	(*Base)=new GUICmdReqAutoAlignmentInfoOnPoint	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAutoAlignmentInfoOnPoint(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AutoAlignmentImagePanel	*B=new AutoAlignmentImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((AutoAlignmentImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 	=/**/"QString";
	Data[N].VariableNameWithRoute	=/**/"ImageControlToolsName";
	Data[N].Pointer					=&((AutoAlignmentImagePanel *)Instance)->ImageControlToolsName;
	Data[N+1].Type					=/**/"int32";
	Data[N+1].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+1].Pointer				=&((AutoAlignmentImagePanel *)Instance)->ShowFixedPhase;
	N+=2;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/AutoAlignmentImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
AutoAlignmentImagePanel::AutoAlignmentImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AutoAlignment",QString(sRoot),QString(sName),__Master,parent)
{
	ClickAreaSize=5;
}

void	AutoAlignmentImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


void	AutoAlignmentImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
	if(GProp!=NULL){
		CmdAutoAlignmentAddManualSheetDrawEnd	RCmd(GetLayersBase());
		RCmd.GlobalArea=area;
		GProp->TransmitDirectly(&RCmd);
	}
}

AlgorithmDrawAttr	*AutoAlignmentImagePanel::CreateDrawAttrPointer(void)
{
	if(ShowFixedPhase!=-1)
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(ShowFixedPhase); // phase function
	GUICmdReqAutoAlignmentDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	AutoAlignmentDrawAttr	*A=new AutoAlignmentDrawAttr();
	A->DrawSheetMode=DrawMode.DrawSheetMode;
	A->DrawMono		=DrawMode.DrawMono;
	A->MonoLevel	=DrawMode.MonoLevel;
	if(GetDisplayType()==DisplayImage::__Master)
		A->Mastered		=true;
	else
		A->Mastered		=false;
	A->DrawPico		=DrawMode.DrawPico;
	A->SelectedLDList=DrawMode.SelectedLDList;

	return A;
}
void	AutoAlignmentImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	AutoAlignmentImagePanel::ExecuteActiveOnItemXY(int globalX ,int globalY)
{
	DisplayImageWithAlgorithm::ExecuteActiveOnItemXY(globalX ,globalY);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int localX ,localY;
		GetLayersBase()->GetPageData(page)->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,localX ,localY);
		if(GetLayersBase()->GetPageData(page)->IsInclude(localX,localY)==true){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqAutoAlignmentInfoOnPoint	Cmd		(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
			GUICmdSendAutoAlignmentInfoOnPoint	AckCmd	(GetLayersBase(),EmitterRoot ,EmitterName,globalPage);
			Cmd.localX=localX;
			Cmd.localY=localY;
			if(Cmd.Send(globalPage ,0,AckCmd)==false){
				SetError(Error_Comm , /**/"Send error :ExecuteActiveOnItemXY",ErrorCodeList::_Alart);
				break;
			}
			CmdGetAutoAlignmentResult	RCmd(GetLayersBase());
			RCmd.ShiftXFromMaster=AckCmd.ShiftXFromMaster;
			RCmd.ShiftYFromMaster=AckCmd.ShiftYFromMaster;
			RCmd.ShiftXFromTarget=AckCmd.ShiftXFromTarget;
			RCmd.ShiftYFromTarget=AckCmd.ShiftYFromTarget;
			RCmd.ShiftRelativeXFromMaster=AckCmd.ShiftRelativeXFromMaster;
			RCmd.ShiftRelativeYFromMaster=AckCmd.ShiftRelativeYFromMaster;
			RCmd.ShiftRelativeXFromTarget=AckCmd.ShiftRelativeXFromTarget;
			RCmd.ShiftRelativeYFromTarget=AckCmd.ShiftRelativeYFromTarget;
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
			if(GProp!=NULL){
				GProp->TransmitDirectly(&RCmd);
			}
		}
	}
}

static	bool AutoAlignmentlFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		AutoAlignmentImagePanel	*Form=dynamic_cast<AutoAlignmentImagePanel *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->DrawItems(DImage,pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}

static	bool AutoAlignmenlFunctionLClicked(FunctionServerClass *Obj,GUIFormBase *TartgetForm,int GlobalPosX,int GlobalPosY)
{
	DisplayImageWithAlgorithm	*a=dynamic_cast<DisplayImageWithAlgorithm	*>(TartgetForm);
	if(a!=NULL){
		if(a->GetImageDrawingMode()!=DisplayImage::_Normal){
			return true;
		}
	}
	AutoAlignmentImagePanel	*Form=dynamic_cast<AutoAlignmentImagePanel *>(Obj);
	if(Form!=NULL){
		FlexArea	RectArea;
		RectArea.SetRectangle(GlobalPosX-Form->ClickAreaSize/2,GlobalPosY-Form->ClickAreaSize/2
							, GlobalPosX+Form->ClickAreaSize/2,GlobalPosY+Form->ClickAreaSize/2);
		Form->ExecuteDrawEnd(RectArea);
		return false;
	}
	return true;
}

static	bool AutoAlignmentFunctionDrawEnd(FunctionServerClass *Obj,GUIFormBase *TartgetForm)
{
	DisplayImageWithAlgorithm	*a=dynamic_cast<DisplayImageWithAlgorithm	*>(TartgetForm);
	if(a!=NULL){
		if(a->GetImageDrawingMode()!=DisplayImage::_Normal){
			return true;
		}
	}
	AutoAlignmentImagePanel	*Form=dynamic_cast<AutoAlignmentImagePanel *>(Obj);
	if(Form!=NULL){
		FlexArea resultarea;
		a->ToFlexArea( *a->GetRawSDataPoint(),resultarea);
		Form->ExecuteDrawEnd(resultarea);
		return false;
	}
	return true;
}

void	AutoAlignmentImagePanel::RequireHooks(GUIFormBase *mother)
{
	DisplayImage	*DImg=dynamic_cast<DisplayImage *>(mother);
	if(DImg!=NULL){
		DImg->SetHookInPaintLast(this,AutoAlignmentlFunctionLater);
		//DImg->SetHookInMouseLClick(this,AutoAlignmenlFunctionLClicked);
		//DImg->SetHookInDrawEnd(this,AutoAlignmentFunctionDrawEnd);
	}
}

void	AutoAlignmentImagePanel::ExecuteDrawEnd(FlexArea &Area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoAlignment" ,/**/"");
	if(GProp!=NULL){
		CmdAutoAlignmentExecuteDrawEnd	RCmd(GetLayersBase());
		RCmd.GlobalArea=Area;
		GProp->TransmitDirectly(&RCmd);
	}
}

//=======================================================================
GUICmdReqAutoAlignmentInfoOnPoint::GUICmdReqAutoAlignmentInfoOnPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}
bool	GUICmdReqAutoAlignmentInfoOnPoint::Load(QIODevice *f)
{
	if(::Load(f,localX)==false){
		return false;
	}
	if(::Load(f,localY)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqAutoAlignmentInfoOnPoint::Save(QIODevice *f)
{
	if(::Save(f,localX)==false){
		return false;
	}
	if(::Save(f,localY)==false){
		return false;
	}
	return true;
}

void	GUICmdReqAutoAlignmentInfoOnPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAutoAlignmentInfoOnPoint	*SendBack=GetSendBack(GUICmdSendAutoAlignmentInfoOnPoint,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeData(localPage ,localX,localY);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAutoAlignmentInfoOnPoint::GUICmdSendAutoAlignmentInfoOnPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}
bool	GUICmdSendAutoAlignmentInfoOnPoint::Load(QIODevice *f)
{
	if(::Load(f,ShiftXFromMaster)==false){
		return false;
	}
	if(::Load(f,ShiftYFromMaster)==false){
		return false;
	}
	if(::Load(f,ShiftXFromTarget)==false){
		return false;
	}
	if(::Load(f,ShiftYFromTarget)==false){
		return false;
	}
	if(::Load(f,ShiftRelativeXFromMaster)==false){
		return false;
	}
	if(::Load(f,ShiftRelativeYFromMaster)==false){
		return false;
	}
	if(::Load(f,ShiftRelativeXFromTarget)==false){
		return false;
	}
	if(::Load(f,ShiftRelativeYFromTarget)==false){
		return false;
	}
	return true;
}
bool	GUICmdSendAutoAlignmentInfoOnPoint::Save(QIODevice *f)
{
	if(::Save(f,ShiftXFromMaster)==false){
		return false;
	}
	if(::Save(f,ShiftYFromMaster)==false){
		return false;
	}
	if(::Save(f,ShiftXFromTarget)==false){
		return false;
	}
	if(::Save(f,ShiftYFromTarget)==false){
		return false;
	}
	if(::Save(f,ShiftRelativeXFromMaster)==false){
		return false;
	}
	if(::Save(f,ShiftRelativeYFromMaster)==false){
		return false;
	}
	if(::Save(f,ShiftRelativeXFromTarget)==false){
		return false;
	}
	if(::Save(f,ShiftRelativeYFromTarget)==false){
		return false;
	}
	return true;
}

void	GUICmdSendAutoAlignmentInfoOnPoint::MakeData(int localPage ,int localX,int localY)
{
	AutoAlignmentBase *PBase=(AutoAlignmentBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	CmdGetAutoAlignmentResult	Cmd(this);
	Cmd.LocalX=localX;
	Cmd.LocalY=localY;
	PBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	ShiftXFromMaster=Cmd.ShiftXFromMaster;
	ShiftYFromMaster=Cmd.ShiftYFromMaster;
	ShiftXFromTarget=Cmd.ShiftXFromTarget;
	ShiftYFromTarget=Cmd.ShiftYFromTarget;
	ShiftRelativeXFromMaster=Cmd.ShiftRelativeXFromMaster;
	ShiftRelativeYFromMaster=Cmd.ShiftRelativeYFromMaster;
	ShiftRelativeXFromTarget=Cmd.ShiftRelativeXFromTarget;
	ShiftRelativeYFromTarget=Cmd.ShiftRelativeYFromTarget;
}

void	GUICmdSendAutoAlignmentInfoOnPoint::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
