#include "MatchingAlignmentImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MaskingImagePanel\MaskingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MatchingAlignmentImagePanel.h"
#include "XCrossObj.h"
//#include "XGUI.h"
#include "XMatchingAlignment.h"
#include "ImageControlTools.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"
#include "PropertyMatchingAlignmentForm.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"MatchingAlignmentImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MatchingAlignment ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	MatchingAlignmentImagePanel	*B=new MatchingAlignmentImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	MatchingAlignmentImagePanel *InstancePtr=dynamic_cast<MatchingAlignmentImagePanel*>((MatchingAlignmentImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				 =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				 =&((MatchingAlignmentImagePanel *)Instance)->ImageControlToolsName;
		N++;
		return(N);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MatchingAlignmentImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MatchingAlignment"));
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
MatchingAlignmentImagePanel::MatchingAlignmentImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"MatchingAlignment",QString(sRoot),QString(sName),__Master,parent)
{
}

void	MatchingAlignmentImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	MatchingAlignmentImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	MatchingAlignmentImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchingAlignment" ,/**/"");
	AddMatchingAlignmentAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	Da.LayerList	=LayerList;
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*MatchingAlignmentImagePanel::CreateDrawAttrPointer(void)
{	
	bool	ModeSpecified=false;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchingAlignment" ,/**/"");
	if(GProp!=NULL){
		DisplayModeOfMatchingAlignment	Cmd(GetLayersBase());
		GProp->TransmitDirectly(&Cmd);
		ModeSpecified=Cmd.ModeSpecified;
	}

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchingAlignment");
	if(Ab!=NULL){
		MatchingAlignmentBase	*M=(MatchingAlignmentBase *)Ab;
		MatchingAlignmentDrawAttr	*mattr=new MatchingAlignmentDrawAttr(
								   M->ColorNormal		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,ModeSpecified);
		return mattr;
	}
	return new MatchingAlignmentDrawAttr();
}



void	MatchingAlignmentImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================
