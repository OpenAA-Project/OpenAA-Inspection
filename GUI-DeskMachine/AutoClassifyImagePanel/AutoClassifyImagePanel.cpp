/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-Desktop\AutoClassifyImagePanel\AutoClassifyImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AutoClassifyImagePanel.h"
#include "XCrossObj.h"
#include "XAutoClassify.h"
#include "XPropertyAutoClassifyPacket.h"
#include "XGeneralDialog.h"
#include "XDisplayImagePacket.h"



static	char	*sRoot="Inspection";
static	char	*sName="AutoClassifyImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("AutoClassify ImagePanel");
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
	AutoClassifyImagePanel	*B=new AutoClassifyImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((AutoClassifyImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 ="QString";
	Data[N].VariableNameWithRoute="ImageControlToolsName";
	Data[N].Pointer				 =&((AutoClassifyImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/AutoClassifyImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList("Basic","AutoClassify"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
AutoClassifyImagePanel::AutoClassifyImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AutoClassify",QString(sRoot),QString(sName),__Master,parent)
{
}

void	AutoClassifyImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	AutoClassifyImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	AutoClassifyImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoClassify" ,/**/"");
	CmdAutoClassifyDrawEnd	Da(GetLayersBase());
	Da.Area			=area;
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*AutoClassifyImagePanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAutoClassify" ,/**/"");
	//CmdMaskingDrawOnOffPacket	Da;
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	if(Ab!=NULL){
		AutoClassifyBase	*M=(AutoClassifyBase *)Ab;
		AutoClassifyDrawAttr	*mattr=new AutoClassifyDrawAttr(
									GetLayersBase()
								  ,M->ColorMask		,M->TransparentLevel
								  ,M->ColorSelected	,M->TransparentLevel
								  ,M->ColorActive	,M->TransparentLevel
								  ,M->PickupColor	,M->TransparentLevel
								  ,M->AreaColor0
								  ,M->AreaColor1
								  ,M->AreaColor2
								  ,M->AreaColor3
								  ,M->AreaColor4
								  ,M->AreaColor5
								  ,M->AreaColor6
								  ,M->AreaColor7
								  );
		//mattr->EffectiveMode	=Da.Effective;
		//mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new AutoClassifyDrawAttr();
}


//=======================================================================
