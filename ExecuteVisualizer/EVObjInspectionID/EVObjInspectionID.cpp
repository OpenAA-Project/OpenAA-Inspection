/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjInspectionID\EVObjInspectionID.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjInspectionID.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Process";
static	const	char	*sName=/**/"InspectionID";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"InspectionID");
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
	return(new RunnerInspectionID(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//======================================================================================
int		InspectionIDOutput::GetOutputInt(void)
{
	RunnerInspectionID	*a=dynamic_cast<RunnerInspectionID *>(GetParent());
	if(a!=NULL){
		int	Value=a->GetLayersBase()->GetCurrentInspectIDForExecute();
		return Value;
	}
	return 0;
}

void	InspectionIDInput::SetInputInt(int d)
{
	RunnerInspectionID	*a=dynamic_cast<RunnerInspectionID *>(GetParent());
	if(a!=NULL){
		a->GetLayersBase()->SetCurrentInspectID(d);
	}
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerInspectionID::RunnerInspectionID(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	InspectionIDInput	*a=new InspectionIDInput(this);
	AppendInputConnector(a);

	InspectionIDOutput	*d=new InspectionIDOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
RunnerInspectionID::~RunnerInspectionID(void)
{
}
void RunnerInspectionID::paintEvent ( QPaintEvent * event )
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
	QString	Str(/**/"Ins ID");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	int	Value=GetLayersBase()->GetCurrentInspectIDForExecute();
	QString	Str2=QString::number(Value);
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::cyan);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);
}
void	RunnerInspectionID::IntervalExecute(void)
{
}
