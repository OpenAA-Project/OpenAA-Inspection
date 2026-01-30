/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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
