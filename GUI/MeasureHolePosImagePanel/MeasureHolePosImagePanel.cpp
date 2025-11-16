#include "MeasureHolePosImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MeasureHolePosImagePanel\MeasureHolePosImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MeasureHolePosImagePanel.h"
#include "XMeasureHolePosPacket.h"

#include "XCrossObj.h"
#include "XMeasureHolePos.h"
#include "XGeneralDialog.h"
#include "SelectCreateNew.h"


static	const	char	*sRoot=/**/"Measure";
static	const	char	*sName=/**/"MeasureHolePosImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MeasureHolePosImagePanel");
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
	MeasureHolePosImagePanel	*B=new MeasureHolePosImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((MeasureHolePosImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((MeasureHolePosImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MeasureHolePosImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Measure",/**/"MeasureHolePos"));
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
MeasureHolePosImagePanel::MeasureHolePosImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Measure" ,/**/"MeasureHolePos",QString(sRoot),QString(sName),__Master,parent)
{
}

void	MeasureHolePosImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	MeasureHolePosImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*MeasureHolePosImagePanel::CreateDrawAttrPointer(void)
{
	CmdMeasureHolePosDrawModePacket	DrawMode(GetLayersBase());
	DrawMode.DrawAttr=new MeasureHolePosDrawAttr();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"PropertyMeasureHolePos" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	return DrawMode.DrawAttr;
}

void	MeasureHolePosImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"PropertyMeasureHolePos" ,/**/"");
	SelectCreateNew	D(this);
	int	n=D.exec();
	VectorLineBase	*V=GetVectorLineBase();
	if(n==1){
		CmdMeasureHolePosDrawEnd	Da(GetLayersBase());
		Da.Area			=area;
		Da.Vector		=V;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
	else if(n==2){
		GUICmdMeasureHolePosGetColorMap	Da(GetLayersBase());
		Da.Area			=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	MeasureHolePosImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


