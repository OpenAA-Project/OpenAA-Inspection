//#include "MatchShiftRotationImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MatchShiftRotationImagePanel\MatchShiftRotationImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "MatchShiftRotationImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XMatchShiftRotation.h"
#include "XGUI.h"
#include "ImagePanelTools.h"
#include "PropertyMatchShiftRotationForm.h"
#include "XPropertyMatchShiftRotationPacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"MatchShiftRotationImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MatchShiftRotationImagePanel");
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
	MatchShiftRotationImagePanel	*B=new MatchShiftRotationImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	MatchShiftRotationImagePanel *InstancePtr=dynamic_cast<MatchShiftRotationImagePanel *>((MatchShiftRotationImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((MatchShiftRotationImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MatchShiftRotationImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MatchShiftRotation"));
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

MatchShiftRotationImagePanel::MatchShiftRotationImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"MatchShiftRotation",QString(sRoot),QString(sName),__Master,parent)
{
}

void	MatchShiftRotationImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	MatchShiftRotationImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	MatchShiftRotationImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*MatchShiftRotationImagePanel::CreateDrawAttrPointer(void)
{	
	CmdMatchShiftRotationDrawModePacket	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchShiftRotationForm" 
												,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
	if(Ab!=NULL){
		MatchShiftRotationBase	*M=(MatchShiftRotationBase *)Ab;
		MatchShiftRotationDrawAttr	*mattr=new MatchShiftRotationDrawAttr(GetLayersBase()
								  ,M->ColorArea				
								  ,M->ColorAreaSelected		
								  ,M->ColorAreaActive		,M->AlphaLevel);
		mattr->ModeDrawArea	=DrawMode.DrawArea;
		mattr->ModeDrawItem	=DrawMode.DrawMark;
		mattr->SelectedArea	=DrawMode.SelectedArea;
		
		return mattr;
	}
	return new MatchShiftRotationDrawAttr(GetLayersBase());
}

void	MatchShiftRotationImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
	if(Ab==NULL)
		return;
	MatchShiftRotationBase	*MBase=dynamic_cast<MatchShiftRotationBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMatchShiftRotationForm" ,/**/"");
	CmdMatchShiftRotationDrawEnd	Da(GetLayersBase());
	if(GProp!=NULL){
		Da.ImagePanelPoint=this;
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	MatchShiftRotationImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

