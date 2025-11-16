/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\World3DImagePanel\World3DImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#define _USE_MATH_DEFINES
#include <math.h>
#include "World3DImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XGeneralFunc.h"
#include <QBitmap>
#include "XWorld3D.h"
#include "SelectPages.h"
#include "XGUI.h"
//#include "ImagePanelTools.h"
#include "PropertyWorld3DForm.h"
#include "XPropertyWorld3DPacket.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"World3DImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"World3D ImagePanel");
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
	World3DImagePanel	*B=new World3DImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	World3DImagePanel *InstancePtr=dynamic_cast<World3DImagePanel *>((World3DImagePanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				  =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				=&((World3DImagePanel *)Instance)->ImageControlToolsName;

		return(N+1);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/World3DImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"World3D"));
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

World3DImagePanel::World3DImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"World3D",QString(sRoot),QString(sName),__Target,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	World3DImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
}

void	World3DImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImage::TransmitDirectly(packet);
}

AlgorithmDrawAttr	*World3DImagePanel::CreateDrawAttrPointer(void)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"World3D");
	if(Ab!=NULL){
		World3DBase	*M=(World3DBase *)Ab;
		World3DDrawAttr	*mattr=new World3DDrawAttr(GetLayersBase()
								  ,M->ColorArea			,128
								  ,M->ColorSelected		,128
								  ,M->ColorActive		,128);
		
		return mattr;
	}
	return new World3DDrawAttr(GetLayersBase());
}

void	World3DImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

