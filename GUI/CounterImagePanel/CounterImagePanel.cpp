/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CounterImagePanel\CounterImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#define _USE_MATH_DEFINES
#include <math.h>
#include "CounterImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include <QIcon>
#include <QPixmap>
#include "XCounter.h"
#include "XGUI.h"
#include "ImagePanelTools.h"
#include "PropertyCounterForm.h"
#include "XPropertyCounterPacket.h"

static	const char	*sRoot=/**/"Inspection";
static	const char	*sName=/**/"CounterImagePanel";

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
	CounterImagePanel	*B=new CounterImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	CounterImagePanel *InstancePtr=dynamic_cast<CounterImagePanel *>((CounterImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((CounterImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CounterImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Counter"));
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

CounterImagePanel::CounterImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Counter",QString(sRoot),QString(sName),__Target,parent)
{
}

void	CounterImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	CounterImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

void	CounterImagePanel::resizeEvent(QResizeEvent *event)
{
	DisplayImageWithAlgorithm::resizeEvent(event);
	WholeButtonDown();
}

AlgorithmDrawAttr	*CounterImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetAlgorithmBase();
	if(Ab!=NULL){
		CounterBase	*M=(CounterBase *)Ab;
		CounterDrawAttr	*mattr=new CounterDrawAttr(GetLayersBase()
								  ,M->ColorArea			,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel);

		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyCounter" ,/**/"");
		CmdCounterDrawModePacket	Da(GetLayersBase());
		if(GProp!=NULL){
			GProp->TransmitDirectly(&Da);
			mattr->ShowExecuteMap	=Da.ShowExecuteMap;
			mattr->ShowItems		=Da.ShowItems;
		}
		
		return mattr;
	}
	return new CounterDrawAttr(GetLayersBase());
}

void	CounterImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=GetAlgorithmBase();
	if(Ab==NULL)
		return;
	CounterBase	*MBase=dynamic_cast<CounterBase *>(Ab);
	if(MBase==NULL)
		return;
	GUIFormBase	*GProp=LBase->FindByName(/**/"Button" ,/**/"PropertyCounter" ,/**/"");
	CmdCounterDrawEnd	Da(LBase);
	if(GProp!=NULL){
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}

bool	CounterImagePanel::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	WholeButtonDown();
	return true;
}