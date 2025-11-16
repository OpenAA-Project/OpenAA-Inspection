/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjCurrentPhase\EVObjCurrentPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjCurrentPhase.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Process";
static	const	char	*sName=/**/"CurrentPhase";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Current Phase");
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

DEFFUNCEX	RunnerObject	*DLL_CreateInstance(LayersBase *Base,RunnerMap *rmap)
{
	return(new RunnerCurrentPhase(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//======================================================================================
int		CurrentPhaseOutput::GetOutputInt(void)
{
	RunnerCurrentPhase	*a=dynamic_cast<RunnerCurrentPhase *>(GetParent());
	if(a!=NULL){
		return a->GetLayersBase()->GetCurrentPhase();
	}
	return 0;
}
void	CurrentPhaseInput::SetInputInt(int d)
{
	RunnerCurrentPhase	*a=dynamic_cast<RunnerCurrentPhase *>(GetParent());
	if(a!=NULL){
		a->GetLayersBase()->SetCurrentPhase(d);
	}
}
const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerCurrentPhase::RunnerCurrentPhase(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	CurrentPhaseInput	*a=new CurrentPhaseInput(this);
	AppendInputConnector(a);

	CurrentPhaseOutput	*d=new CurrentPhaseOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
RunnerCurrentPhase::~RunnerCurrentPhase(void)
{
}
void RunnerCurrentPhase::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	Pnt.fillRect(0,0,ObjWidth,ObjHeight,Qt::black);

	QFont	Fnt=Pnt.font();
	Fnt.setPointSize(15);
	Pnt.setFont(Fnt);
	int	e=4;
	int	h=(ObjHeight-e-e)/3;

	Pnt.setPen(Qt::white);

	QRectF	Rect1(e,e,ObjWidth-e-e,h);
	QString	Str(/**/"Phase");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	int	Value=GetLayersBase()->GetCurrentPhase();
	QString	Str2=QString::number(Value);
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::green);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);
}

void	RunnerCurrentPhase::IntervalExecute(void)
{
}
