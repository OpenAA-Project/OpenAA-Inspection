#include "AutoMaskingPIImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoMaskingPIImagePanel\AutoMaskingPIImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AutoMaskingPIImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XAutoMaskingPI.h"
#include "ImageControlTools.h"
#include "XPropertyAutoMaskingPIPacket.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"AutoMaskingPIImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"AutoMaskingPIImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}


DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AutoMaskingPIImagePanel	*B=new AutoMaskingPIImagePanel(Base,parent);
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
	int	N=((AutoMaskingPIImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 	=/**/"QString";
	Data[N].VariableNameWithRoute	=/**/"ImageControlToolsName";
	Data[N].Pointer					 =&((AutoMaskingPIImagePanel *)Instance)->ImageControlToolsName;
	Data[N+1].Type					=/**/"int32";
	Data[N+1].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+1].Pointer				 =&((AutoMaskingPIImagePanel *)Instance)->ShowFixedPhase;
	N+=2;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutoMaskingPIImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoMaskingPI"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
AutoMaskingPIImagePanel::AutoMaskingPIImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AutoMaskingPI",QString(sRoot),QString(sName),__Master,parent)
{
}

void	AutoMaskingPIImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


void	AutoMaskingPIImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoMaskingPIForm" ,/**/"");
	AddAutoMaskingPIAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*AutoMaskingPIImagePanel::CreateDrawAttrPointer(void)
{
	if(ShowFixedPhase!=-1)
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(ShowFixedPhase); // phase function
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoMaskingPIForm" ,/**/"");
	CmdAutoMaskingPIDrawOnOffPacket	Da(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoMaskingPI");
	if(Ab!=NULL){
		AutoMaskingPIBase	*M=(AutoMaskingPIBase *)Ab;
		AutoMaskingPIDrawAttr	*mattr=new AutoMaskingPIDrawAttr(
									   M->ColorMask			,M->TransparentLevel
									  ,M->ColorSelected		,M->TransparentLevel
									  ,M->ColorActive		,M->TransparentLevel
									  ,M->NegColorMask		
									  ,M->NegColorSelected);
		mattr->EffectiveMode	=Da.Effective;
		mattr->IneffectiveMode	=Da.Ineffective;
		mattr->AutoGenMode		=Da.AutoGenMode;
		mattr->CompositeMask	=Da.CompositeMask;
		return mattr;
	}
	return new AutoMaskingPIDrawAttr();
}


void	AutoMaskingPIImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================

static	bool AutoMaskingPIFunctionLater(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		AutoMaskingPIImagePanel	*Form=dynamic_cast<AutoMaskingPIImagePanel *>(Obj);
		if(Form!=NULL){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->DrawItems(DImage,pnt,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy());
				Form->GetLayersBase()->UnlockWeakDraw();
			}
		}
	}
	return true;
}

void	AutoMaskingPIImagePanel::RequireHooks(GUIFormBase *mother)
{
	DisplayImage	*DImg=dynamic_cast<DisplayImage *>(mother);
	if(DImg!=NULL){
		DImg->SetHookInPaintLast(this,AutoMaskingPIFunctionLater);
		//DImg->SetHookInMouseLClick(this,AutoMaskingPIFunctionLClicked);
		//DImg->SetHookInDrawEnd(this,AutoMaskingPIFunctionDrawEnd);
	}
}
