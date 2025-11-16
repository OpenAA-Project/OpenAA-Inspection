#include "VCutImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\VCutImagePanel\VCutImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "VCutImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XVCutInspection.h"
#include "ImageControlTools.h"
#include "VCutImagePacket.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"VCutImagePanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"VCutImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddAlignment(QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}


DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	VCutImagePanel	*B=new VCutImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((VCutImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((VCutImagePanel *)Instance)->ImageControlToolsName;
	Data[N+1].Type					=/**/"int32";
	Data[N+1].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+1].Pointer				= &((VCutImagePanel *)Instance)->ShowFixedPhase;
	N+=2;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/VCutImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"PCB",/**/"VCutInspection"));
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
VCutImagePanel::VCutImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"PCB" ,/**/"VCutInspection",QString(sRoot),QString(sName),__Master,parent)
{
}

void	VCutImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


void	VCutImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"VCutProperty" ,/**/"");
	VectorLineBase	*V=GetVectorLineBase();
	if(V!=NULL && GProp!=NULL){
		AddVCutInspectionAreaPacket	Da(GetLayersBase());
		Da.Vector		=V;
		Da.CurrentPhase = ShowFixedPhase;
		if(Da.CurrentPhase==-1)
			Da.CurrentPhase = 0;
		GProp->TransmitDirectly(&Da);
	}
}


AlgorithmDrawAttr	*VCutImagePanel::CreateDrawAttrPointer(void)
{
	if(ShowFixedPhase!=-1)
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(ShowFixedPhase); // phase function
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"PCB",/**/"VCutInspection");
	if(Ab!=NULL){
		VCutInspectionBase	*M=(VCutInspectionBase *)Ab;
		VCutInspectionDrawAttr	*mattr=new VCutInspectionDrawAttr(
									   M->ColorVCut			,M->TransparentLevel
									  ,M->ColorSelected		,M->TransparentLevel
									  ,M->ColorActive		,M->TransparentLevel);
		return mattr;
	}
	return new VCutInspectionDrawAttr();
}


void	VCutImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================

