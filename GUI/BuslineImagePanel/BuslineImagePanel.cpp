#include "BuslineImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\BuslineImagePanel\BuslineImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "BuslineImagePanel.h"
#include "XAlgorithmDLL.h"

#include "XCrossObj.h"
#include "XBuslineInspection.h"
#include "XGeneralDialog.h"
#include "XBuslinePacket.h"

static	const	char	*sRoot=/**/"Basic";
static	const	char	*sName=/**/"BuslineImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Image panel for Busline inspection");
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
	BuslineImagePanel	*B=new BuslineImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((BuslineImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((BuslineImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/BuslineImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Busline"));
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
BuslineImagePanel::BuslineImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Busline",QString(sRoot),QString(sName),__Master,parent)
{
}

void	BuslineImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	BuslineImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*BuslineImagePanel::CreateDrawAttrPointer(void)
{
	BuslineBase	*a=dynamic_cast<BuslineBase *>(GetAlgorithmBase());
	if(a!=NULL){
		BuslineDrawAttr	*c=new BuslineDrawAttr(a->ColorMask		,a->TransparentLevel
											,  a->ColorSelected	,a->TransparentLevel
											,  a->ColorActive	,a->TransparentLevel
											,a->NegColorMask
											,a->NegColorSelected);

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBusline" ,/**/"");
		if(GProp!=NULL){
			CmdBuslineDrawPacket	Da(GetLayersBase());
			GProp->TransmitDirectly(&Da);
			c->DMode	=Da.DMode;
		}
		return c;
	}
	else{
		BuslineDrawAttr	*c=new BuslineDrawAttr();
		return c;
	}
}

void	BuslineImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyBusline" ,/**/"");
	if(GProp!=NULL){
		CmdBuslineDrawEnd	Da(GetLayersBase());
		Da.Area			=area;
		GetActiveLayerList(Da.LayerList);
		GProp->TransmitDirectly(&Da);
	}
}

void	BuslineImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


