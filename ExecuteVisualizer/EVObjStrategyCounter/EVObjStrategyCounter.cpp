/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjStrategyCounter\EVObjStrategyCounter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjStrategyCounter.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Process";
static	const	char	*sName=/**/"StrategyCounter";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Strategy Counter");
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
	return(new RunnerStrategyCounter(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//======================================================================================
int		StrategyCounterOutput::GetOutputInt(void)
{
	RunnerStrategyCounter	*a=dynamic_cast<RunnerStrategyCounter *>(GetParent());
	if(a!=NULL){
		int	Value=a->GetLayersBase()->GetCurrentStrategicNumberForCalc();
		return Value;
	}
	return 0;
}

void	StrategyCounterInput::SetInputInt(int d)
{
	RunnerStrategyCounter	*a=dynamic_cast<RunnerStrategyCounter *>(GetParent());
	if(a!=NULL){
		a->GetLayersBase()->SetCurrentStrategicNumber(d);
	}
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerStrategyCounter::RunnerStrategyCounter(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	StrategyCounterInput	*a=new StrategyCounterInput(this);
	AppendInputConnector(a);

	StrategyCounterOutput	*d=new StrategyCounterOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
RunnerStrategyCounter::~RunnerStrategyCounter(void)
{
}
void RunnerStrategyCounter::paintEvent ( QPaintEvent * event )
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
	QString	Str(/**/"Strategy");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	int	Value=GetLayersBase()->GetCurrentStrategicNumberForCalc();
	QString	Str2=QString::number(Value);
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::red);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);
}

void	RunnerStrategyCounter::IntervalExecute(void)
{
}