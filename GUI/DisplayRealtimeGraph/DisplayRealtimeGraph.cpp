/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayRealtimeGraph\DisplayRealtimeGraph.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayRealtimeGraph.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XDisplayImage.h"

#include "XDisplayRealtimeGraph.h"

static	const	char	*sRoot=/**/"RealtimeGraph";
static	const	char	*sName=/**/"DisplayRealtimeGraph";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display RealtimeGraph");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayRealtimeGraph(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	;
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayRealtimeGraph.png")));
}

//===================================================================================

DisplayRealtimeGraph::DisplayRealtimeGraph(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	resize(250,250);

	PanelBrightness	=new DisplayRealtimeGraphBrightness	(GetLayersBase(),this);
	PanelFocus		=new DisplayRealtimeGraphFocus		(GetLayersBase(),this);
	PropertyRealtimeGraphPointer=NULL;
	RealtimeImagePanelPointer	=NULL;

	connect(this,SIGNAL(SignalResize())			,this,SLOT(ResizeAction()));
}
DisplayRealtimeGraph::~DisplayRealtimeGraph()
{
	delete	PanelBrightness;
	delete	PanelFocus;
	PanelBrightness	=NULL;
	PanelFocus		=NULL;
}

void	DisplayRealtimeGraph::ResizeAction()
{
	PanelBrightness	->SetGeometry(0,0,width()-1,height()/2-4);
	PanelFocus		->SetGeometry(0,height()/2,width()-1,height()/2-4);
}

void	DisplayRealtimeGraph::AfterStartSequence(void)
{
	PropertyRealtimeGraphPointer=GetLayersBase()->FindByName(/**/"RealtimeGraph",/**/"PropertyRealtimeGraph",/**/"");
	RealtimeImagePanelPointer	=dynamic_cast<DisplayImage *>(GetLayersBase()->FindByName(/**/"RealtimeGraph",/**/"ImagePanel",/**/""));
}

void	DisplayRealtimeGraph::ShowInPlayer(int64 shownInspectionID)
{
	if(GetStackedViewPlayerCount()<2){
		PanelBrightness	->Repaint();
		PanelFocus		->Repaint();
	}
}	
void	DisplayRealtimeGraph::ShowInScanning(int64 shownInspectionID)
{
	ShowInPlayer(shownInspectionID);
}

void	DisplayRealtimeGraph::TransmitDirectly(GUIDirectMessage *packet)
{
}

