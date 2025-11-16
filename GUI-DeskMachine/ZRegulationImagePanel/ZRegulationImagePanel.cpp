/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NamingImagePanel\NamingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ZRegulationImagePanel.h"
#include "XCrossObj.h"
#include "XZAxisRegulation.h"
//#include "ImageControlTools.h"
#include "XPropertyZRegulationPacket.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"
#include "XDisplayImagePacket.h"



static	char	*sRoot="Inspection";
static	char	*sName="ZRegulationImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Z Axsis Regulation ImagePanel");
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
	ZRegulationImagePanel	*B=new ZRegulationImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((ZRegulationImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 ="QString";
	Data[N].VariableNameWithRoute="ImageControlToolsName";
	Data[N].Pointer				 =&((ZRegulationImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ZRegulationImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Regulation","ZAxis"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
ZRegulationImagePanel::ZRegulationImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Regulation" ,/**/"ZAxis",QString(sRoot),QString(sName),__Master,parent)
{
}

void	ZRegulationImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	ZRegulationImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
	CmdReqLayersListPacket	*CmdReqLayersListVar=dynamic_cast<CmdReqLayersListPacket *>(packet);
	if(CmdReqLayersListVar!=NULL){
		GetActiveLayerList(CmdReqLayersListVar->Layers);
		return;
	}
}

void	ZRegulationImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyZRegulation" ,/**/"");
	AddZRegulationAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	GetActiveLayerList(Da.Layers);
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*ZRegulationImagePanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyZRegulation" ,/**/"");
	//CmdMaskingDrawOnOffPacket	Da;
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Regulation",/**/"ZAxis");
	if(Ab!=NULL){
		ZAxisRegulationBase	*M=(ZAxisRegulationBase *)Ab;
		ZAxisRegulationDrawAttr	*mattr=new ZAxisRegulationDrawAttr(
								   M->ColorRegulation	,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  );
		//mattr->EffectiveMode	=Da.Effective;
		//mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new ZAxisRegulationDrawAttr();
}


//=======================================================================
