#include "GeneralHairLineResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralHairLine\GeneralHairLine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralHairLine.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"HairLine";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General HairLine");
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
	return(new GeneralHairLine(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"LineColor";
	Data[0].Pointer				 =&((GeneralHairLine *)Instance)->LineColor;
	Data[1].Type				 =/**/"HLine,VLine";
	Data[1].VariableNameWithRoute=/**/"FrameShape";
	Data[1].Pointer				 =&((GeneralHairLine *)Instance)->FrameShape;
	Data[2].Type				 =/**/"Plain,Raised,Sunken";
	Data[2].VariableNameWithRoute=/**/"FrameShadow";
	Data[2].Pointer				 =&((GeneralHairLine *)Instance)->FrameShadow;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"LineWidth";
	Data[3].Pointer				 =&((GeneralHairLine *)Instance)->LineWidth;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralHairLine.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GeneralHairLine::GeneralHairLine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Line.setParent(this);
	Line.move(0,0);
	FrameShape		=/**/"HLine";
	FrameShadow		=/**/"Plain";
	LineWidth		=1;
	resize(300,10);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

GeneralHairLine::~GeneralHairLine(void)
{
}

void	GeneralHairLine::Prepare(void)
{
	QPalette palette;
	palette.setColor(QPalette::WindowText,LineColor);
	Line.setPalette(palette);

	if(FrameShape==/**/"HLine")
		Line.setFrameShape(QFrame::HLine);
	else
		Line.setFrameShape(QFrame::VLine);

	if(FrameShadow==/**/"Plain")
		Line.setFrameShadow(QFrame::Plain);
	else if(FrameShadow==/**/"Raised")
		Line.setFrameShadow(QFrame::Raised);
	else
		Line.setFrameShadow(QFrame::Sunken);

	Line.setLineWidth(LineWidth);

	ResizeAction();
//	update();
}

void	GeneralHairLine::ResizeAction(void)
{
	Line.resize(width(),height());
}
