#include "DynamicMaskingPIImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DynamicMaskingPIImagePanel\DynamicMaskingPIImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DynamicMaskingPIImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XDynamicMaskingPI.h"
#include "ImageControlTools.h"
#include "XPropertyDynamicMaskingPIPacket.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"DynamicMaskingPIImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"DynamicMaskingPIImagePanel");
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

	(*Base)=new GUICmdReqSelectedItemCount	(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount	(Base ,QString(sRoot) ,QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	DynamicMaskingPIImagePanel	*B=new DynamicMaskingPIImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DynamicMaskingPIImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((DynamicMaskingPIImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DynamicMaskingPIImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DynamicMaskingPI"));
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
DynamicMaskingPIImagePanel::DynamicMaskingPIImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"DynamicMaskingPI",QString(sRoot),QString(sName),__Master,parent)
{
}

void	DynamicMaskingPIImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	DynamicMaskingPIImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	DynamicMaskingPIImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicMaskingPI" ,/**/"");
	
	if(GProp!=NULL){
		AddDynamicMaskingPIAreaPacket	Da(GetLayersBase());
		Da.MaskArea			=area;
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*DynamicMaskingPIImagePanel::CreateDrawAttrPointer(void)
{	
	/*
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyMaskingFormPI" ,"");
	CmdMaskingPIDrawOnOffPacket	Da;
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}*/

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"DynamicMaskingPI");
	if(Ab!=NULL){
		DynamicMaskingPIBase	*DM=(DynamicMaskingPIBase *)Ab;
		DynamicMaskingPIDrawAttr	*dmattr=new DynamicMaskingPIDrawAttr(
								   DM->ColorMask			,DM->TransparentLevel
								  ,DM->ColorSelected		,DM->TransparentLevel
								  ,DM->ColorActive			,DM->TransparentLevel
								  ,DM->NegColorMask			,DM->NegColorSelected);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicMaskingPI" ,/**/"");
		if(GProp!=NULL){
			CmdReqDMaskingPIMode	RCmd(GetLayersBase());
			GProp->TransmitDirectly(&RCmd);
			dmattr->MaskMode	=RCmd.Mode;
			dmattr->SelectedMask=RCmd.SelectedItem;
		}
		return dmattr;
	}

	return new DynamicMaskingPIDrawAttr();
}

void DynamicMaskingPIImagePanel::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicMaskingPI" ,/**/"");
	if(GProp!=NULL)
		GProp->BuildForShow();
}

void	DynamicMaskingPIImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================

