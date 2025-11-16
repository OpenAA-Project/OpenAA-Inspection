#include "GraphicPanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GraphicPanel\GraphicPanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QDir>
#include "GraphicPanel.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"GraphicPanel";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Graphic panel from BMP/JPG/PNG file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GraphicPanel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"FileName";
	Data[0].VariableNameWithRoute=/**/"FileName";
	Data[0].Pointer				 =&((GraphicPanel *)Instance)->FileName;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"Scaling";
	Data[1].Pointer				 =&((GraphicPanel *)Instance)->Scaling;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GraphicPanel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GraphicPanel::GraphicPanel(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Scaling	=true;
	Label.setParent(this);
	Label.move(0,0);
	resize(100,100);
}

GraphicPanel::~GraphicPanel(void)
{
}

void	GraphicPanel::Prepare(void)
{
	DrawOnly();
	ResizeAction();
}

void	GraphicPanel::DrawOnly(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	if(FileName.isEmpty()==false && QFile::exists (FileName)==true){
		QPixmap	GMap;
		if(GMap.load(FileName)==false){
			ReEntrant=false;
			return;
		}
		if(Scaling==true){
			QPixmap	RMap=GMap.scaled(Label.width(),Label.height());
			Label.setPixmap(RMap);
		}
		else{
			int	W=GMap.width();
			int	H=GMap.height();
			resize(W+1,H+1);
			Label.setPixmap(GMap);
		}
	}
	ReEntrant=false;
}

void	GraphicPanel::ResizeAction(void)
{
	Label.resize(width(),height());
	DrawOnly();
}
