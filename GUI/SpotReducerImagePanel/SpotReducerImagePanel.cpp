#include "SpotReducerImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SpotReducerImagePanel\SpotReducerImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "SpotReducerImagePanel.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "XSpotReducer.h"
#include "XGeneralDialog.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"SpotReducerImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"SpotReducerImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

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
	SpotReducerImagePanel	*B=new SpotReducerImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	SpotReducerImagePanel *InstancePtr=dynamic_cast<SpotReducerImagePanel*>((SpotReducerImagePanel*)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		//Data[N].Type				 ="QString";
		//Data[N].VariableNameWithRoute="ImageControlToolsName";
		//Data[N].Pointer				 =&((SpotReducerImagePanel *)Instance)->ImageControlToolsName;
		//N++;
		return(N);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SpotReducerImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"SpotReducer"));
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
SpotReducerImagePanel::SpotReducerImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"SpotReducer",QString(sRoot),QString(sName),__Master,parent)
{
}

void	SpotReducerImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	SpotReducerImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	SpotReducerImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertySpotReducerForm" ,/**/"");
	AddSpotReducerArea	Da(GetLayersBase());
	Da.Area			=area;
	Da.LayerList	=LayerList;
	GProp->TransmitDirectly(&Da);
}

AlgorithmDrawAttr	*SpotReducerImagePanel::CreateDrawAttrPointer(void)
{	
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertySpotReducerForm" ,"");
	CmdDrawOnOffPacket	Da;
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase("Basic","Masking");
	if(Ab!=NULL){
		MaskingBase	*M=(MaskingBase *)Ab;
		MaskingDrawAttr	*mattr=new MaskingDrawAttr(
														M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorMask		
								  ,M->NegColorSelected);
		mattr->EffectiveMode			=Da.Effective;
		mattr->IneffectiveMode			=Da.Ineffective;
		mattr->EffectiveLimitedMode		=Da.EffectiveLimited;
		mattr->IneffectiveLimitedMode	=Da.IneffectiveLimited;
		return mattr;
	}
	return new MaskingDrawAttr();
	*/
	return new SpotReducerDrawAttr();
}

void	SpotReducerImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================

