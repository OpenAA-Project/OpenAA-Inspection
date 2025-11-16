/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjCountUp\EVObjCountUp.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjCountUp.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"

static	const	char	*sRoot=/**/"Calc";
static	const	char	*sName=/**/"EVObjCountUp";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Count up any value");
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
	return(new RunnerCountUp(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//======================================================================================

int		CountUpOutput::GetOutputInt(void)
{
	RunnerCountUp	*a=dynamic_cast<RunnerCountUp *>(GetParent());
	if(a!=NULL){
		return a->GetValue()+1;
	}
	return 0;
}

void	CountUpInput::SetInputInt(int d)
{
	RunnerCountUp	*a=dynamic_cast<RunnerCountUp *>(GetParent());
	if(a!=NULL){
		a->Value=d;
	}
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerCountUp::RunnerCountUp(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	Value	=0;

	CountUpInput	*a=new CountUpInput(this);
	AppendInputConnector(a);

	CountUpOutput	*d=new CountUpOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
RunnerCountUp::~RunnerCountUp(void)
{
}
void RunnerCountUp::paintEvent ( QPaintEvent * event )
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
	QString	Str(/**/"<+1>");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	QString	Str2=QString::number(Value);
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::yellow);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);

}

void	RunnerCountUp::IntervalExecute(void)
{
	Value=GetInputInt(/**/"Input");
}
