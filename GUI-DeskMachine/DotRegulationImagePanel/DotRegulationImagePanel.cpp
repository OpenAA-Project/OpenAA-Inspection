/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DotRegulationImagePanel\DotRegulationImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DotRegulationImagePanel.h"
#include "XCrossObj.h"
#include "XDotRegulation.h"
//#include "ImageControlTools.h"
#include "XPropertyDotRegulationPacket.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"
#include "XDisplayImagePacket.h"



static	char	*sRoot="Inspection";
static	char	*sName="DotRegulationImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Dot Pattern Regulation ImagePanel");
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
	DotRegulationImagePanel	*B=new DotRegulationImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DotRegulationImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 ="QString";
	Data[N].VariableNameWithRoute="ImageControlToolsName";
	Data[N].Pointer				 =&((DotRegulationImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/DotRegulationImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Basic","DotRegulation"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
DotRegulationImagePanel::DotRegulationImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"DotRegulation",QString(sRoot),QString(sName),__Master,parent)
{
}

void	DotRegulationImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	DotRegulationImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
	CmdReqLayersListPacket	*CmdReqLayersListVar=dynamic_cast<CmdReqLayersListPacket *>(packet);
	if(CmdReqLayersListVar!=NULL){
		GetActiveLayerList(CmdReqLayersListVar->Layers);
		return;
	}
}

void	DotRegulationImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDotRegulation" ,/**/"");
	AddDotRegulationAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	GetActiveLayerList(Da.Layers);
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*DotRegulationImagePanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDotRegulation" ,/**/"");
	//CmdMaskingDrawOnOffPacket	Da;
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Regulation",/**/"DotPattern");
	if(Ab!=NULL){
		DotRegulationBase	*M=(DotRegulationBase *)Ab;
		DotRegulationDrawAttr	*mattr=new DotRegulationDrawAttr(
								   M->ColorRegulation	,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  );
		//mattr->EffectiveMode	=Da.Effective;
		//mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new DotRegulationDrawAttr();
}


//=======================================================================
