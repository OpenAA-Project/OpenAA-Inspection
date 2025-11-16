//#include "SwitchPhaseImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SwitchPhaseImagePanel\SwitchPhaseImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SwitchPhaseImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XSwitchPhase.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertySwitchPhasePacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"SwitchPhaseImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"SwitchPhaseImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);


	//new GUICmdReqBlockBmp(QString(sRoot),QString(sName));
	//new GUICmdSendBlockBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddBlock(QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	SwitchPhaseImagePanel	*B=new SwitchPhaseImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((SwitchPhaseImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((SwitchPhaseImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SwitchPhaseImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"SwitchPhase"));
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

SwitchPhaseImagePanel::SwitchPhaseImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"SwitchPhase",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	SwitchPhaseImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	SwitchPhaseImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}


AlgorithmDrawAttr	*SwitchPhaseImagePanel::CreateDrawAttrPointer(void)
{
	SwitchPhaseBase	*Base=(SwitchPhaseBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new SwitchPhaseDrawAttr(
								 Base->ColorSwitchPhase		,100
								,Base->ColorSelected		,100
								,Base->ColorActive		,100
								,Base->NegColorSwitchPhase
								,Base->NegColorSelected);
	}
	return NULL;
}

void	SwitchPhaseImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertySwitchPhase" ,/**/"");
	if(GProp!=NULL){
		CmdSwitchPhaseDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	SwitchPhaseImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================
