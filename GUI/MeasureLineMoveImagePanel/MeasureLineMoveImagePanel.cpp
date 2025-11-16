#include "MeasureLineMoveImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MeasureLineMoveImagePanel\MeasureLineMoveImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MeasureLineMoveImagePanel.h"
#include "XMeasureLineMovePacket.h"

#include "XCrossObj.h"
#include "XGUI.h"
#include "XMeasureLineMove.h"
#include "XGeneralDialog.h"

static	const	char	*sRoot=/**/"Measure";
static	const	char	*sName=/**/"MeasureLineMoveImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MeasureLineMoveImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);
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
	MeasureLineMoveImagePanel	*B=new MeasureLineMoveImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((MeasureLineMoveImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((MeasureLineMoveImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MeasureLineMoveImagePanel.png")));

}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Measure",/**/"MeasureLineMove"));
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
MeasureLineMoveImagePanel::MeasureLineMoveImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Measure" ,/**/"MeasureLineMove",QString(sRoot),QString(sName),__Target,parent)
{
}

void	MeasureLineMoveImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	MeasureLineMoveImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}
AlgorithmDrawAttr	*MeasureLineMoveImagePanel::CreateDrawAttrPointer(void)
{
	CmdMeasureLineMoveDrawModePacket	DrawMode(GetLayersBase());
	DrawMode.DrawAttr=new MeasureLineMoveDrawAttr();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"PropertyMeasureLineMove" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	return DrawMode.DrawAttr;
}
void	MeasureLineMoveImagePanel::ExecuteMouseLDown(int globalX ,int globalY)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"PropertyMeasureLineMove" ,/**/"");
	if(GProp!=NULL){
		CmdMeasureLineMoveLDown	Cmd(GetLayersBase());
		Cmd.GlobalX=globalX;
		Cmd.GlobalY=globalY;
		GProp->TransmitDirectly(&Cmd);
	}
}

void	MeasureLineMoveImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"PropertyMeasureLineMove" ,/**/"");
	VectorLineBase	*V=GetVectorLineBase();
	if(V!=NULL){
		AddLinePacket	Da(GetLayersBase());
		Da.Vector		=V;
		GProp->TransmitDirectly(&Da);
	}
	else{
		CmdMeasureLineMoveDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}

void	MeasureLineMoveImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================

