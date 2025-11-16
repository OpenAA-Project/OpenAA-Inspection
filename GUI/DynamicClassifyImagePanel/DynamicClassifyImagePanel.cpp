#include "DynamicClassifyImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DynamicClassifyImagePanel\DynamicClassifyImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DynamicClassifyImagePanel.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XDynamicClassifyPacket.h"
#include "DynamicClassifyImagePanel.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"DynamicClassifyImagePanel";
//LayersBase *_Base;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Dynamic Classify ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	(*Base)=new GUICmdSetCopyAttr	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendDynamicClassifyInfoOnPoint(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	//_Base=Base;
	DynamicClassifyImagePanel	*B=new DynamicClassifyImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DynamicClassifyImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((DynamicClassifyImagePanel *)Instance)->ImageControlToolsName;
	N++;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/DynamicClassifyImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DynamicClassify"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
DynamicClassifyImagePanel::DynamicClassifyImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"DynamicClassify",QString(sRoot),QString(sName),__Master,parent)
{
}

void	DynamicClassifyImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*DynamicClassifyImagePanel::CreateDrawAttrPointer(void)
{
	GUICmdReqDynamicClassifyDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	DynamicClassifyDrawAttr	*A=new DynamicClassifyDrawAttr();
	A->ShowCore			=DrawMode.ShowCore;
	A->ShowMaxZone		=DrawMode.ShowMaxZone;
	A->ShowMinZone		=DrawMode.ShowMinZone;
	A->ShowBare			=DrawMode.ShowBare;
	A->ShowInside		=DrawMode.ShowInside;
	A->ShowOutlineI		=DrawMode.ShowOutlineI;
	A->ShowOutlineT		=DrawMode.ShowOutlineT;
	A->ShowOutlineO		=DrawMode.ShowOutlineO;

	return A;
}
void	DynamicClassifyImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

static	bool DynamicClassifyFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		DynamicClassifyImagePanel	*Form=dynamic_cast<DynamicClassifyImagePanel *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->DrawItems(DImage,pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}

void	DynamicClassifyImagePanel::RequireHooks(GUIFormBase *mother)
{
	DisplayImage	*DImg=dynamic_cast<DisplayImage *>(mother);
	if(DImg!=NULL){
		DImg->SetHookInPaintLast(this,DynamicClassifyFunctionLater);
	}
}

void	DynamicClassifyImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
	if(GProp!=NULL){
		CmdDynamicClassifyDrawEnd	RCmd(GetLayersBase());
		RCmd.GlobalArea		=area;
		RCmd.ImagePanelPoint=this;
		GProp->TransmitDirectly(&RCmd);
	}
}

void	DynamicClassifyImagePanel::ButtonExecuteCopySelected(bool EnableDup)
{
	SelectAreaDialog	D;
	GetLayersBase()->TmpHideProcessingForm();
	if(D.exec()==(int)true){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			GUICmdSetCopyAttr	Cmd(GetLayersBase(),QString(sRoot),QString(sName),page);
			Cmd.Mode	=D.Mode;
			Cmd.SendOnly(page,0);
		}
		DisplayImageWithAlgorithm::ButtonExecuteCopySelected(EnableDup);
	}
	GetLayersBase()->TmpRercoverProcessingForm();
}

//=======================================================================

GUICmdSetCopyAttr::GUICmdSetCopyAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}

bool	GUICmdSetCopyAttr::Load(QIODevice *f)
{
	if(Mode.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetCopyAttr::Save(QIODevice *f)
{
	if(Mode.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetCopyAttr::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(Ab!=NULL){
		CmdSetCopyAttr	Cmd(this);
		Cmd.Mode=Mode;
		Ab->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
