//#include "NickInspectionImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NickInspectionImagePanel\NickInspectionImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "NickInspectionImagePanel.h"
#include "XAlgorithmDLL.h"

#include "XCrossObj.h"
#include "XNickInspection.h"
#include "XGeneralDialog.h"
#include "XNickInspectionPacket.h"



static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"NickInspectionImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Image panel for NickInspection inspection");
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
	NickInspectionImagePanel	*B=new NickInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((NickInspectionImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((NickInspectionImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/NickInspectionImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"NickInspection"));
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

//==================================================================================================
NickInspectionImagePanel::NickInspectionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"NickInspection",QString(sRoot),QString(sName),__Master,parent)
{
}

void	NickInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	NickInspectionImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*NickInspectionImagePanel::CreateDrawAttrPointer(void)
{
	NickInspectionBase	*a=dynamic_cast<NickInspectionBase *>(GetAlgorithmBase());
	if(a!=NULL){
		NickInspectionDrawAttr	*c=new NickInspectionDrawAttr(a->ColorMask		,a->TransparentLevel
											,  a->ColorSelected	,a->TransparentLevel
											,  a->ColorActive	,a->TransparentLevel
											,a->NegColorMask
											,a->NegColorSelected);

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNickInspection" ,/**/"");
		if(GProp!=NULL){
			CmdNickInspectionDrawPacket	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
		}
		return c;
	}
	else{
		NickInspectionDrawAttr	*c=new NickInspectionDrawAttr();
		return c;
	}
}

void	NickInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNickInspection" ,/**/"");
	if(GProp!=NULL){
		CmdNickInspectionDrawEnd	Da(GetLayersBase());
		Da.Area			=area;
		GetActiveLayerList(Da.LayerList);
		GProp->TransmitDirectly(&Da);
	}
}

void	NickInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


