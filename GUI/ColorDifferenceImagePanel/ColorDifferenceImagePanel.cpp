/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ColorDifferenceImagePanel\ColorDifferenceImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "ColorDifferenceImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XColorDifference.h"
#include "XGUI.h"
#include "ImagePanelTools.h"
#include "PropertyColorDifferenceForm.h"
#include "XPropertyColorDifferencePacket.h"



static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"ColorDifferenceImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ColorDifference ImagePanel");
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
	ColorDifferenceImagePanel	*B=new ColorDifferenceImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	ColorDifferenceImagePanel *InstancePtr=dynamic_cast<ColorDifferenceImagePanel *>((ColorDifferenceImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((ColorDifferenceImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ColorDifferenceImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ColorDifference"));
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

ColorDifferenceImagePanel::ColorDifferenceImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ColorDifference",QString(sRoot),QString(sName),__Master,parent)
{
}

void	ColorDifferenceImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	ColorDifferenceImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	ColorDifferenceImagePanel::DrawBtnDown()
{
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

AlgorithmDrawAttr	*ColorDifferenceImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(Ab!=NULL){
		ColorDifferenceBase	*M=(ColorDifferenceBase *)Ab;
		ColorDifferenceDrawAttr	*mattr=new ColorDifferenceDrawAttr(GetLayersBase()
								  ,M->ColorArea			,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);
		
		return mattr;
	}
	return new ColorDifferenceDrawAttr(GetLayersBase());
}

void	ColorDifferenceImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=LBase->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(Ab==NULL)
		return;
	ColorDifferenceBase	*MBase=dynamic_cast<ColorDifferenceBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyColorDifference" ,/**/"");
	CmdColorDifferenceDrawEnd	Da(GetLayersBase());
	if(GProp!=NULL){
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

void	ColorDifferenceImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

