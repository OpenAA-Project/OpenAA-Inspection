/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjNot\EVObjNot.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjNot.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"

static	const	char	*sRoot=/**/"Calc";
static	const	char	*sName=/**/"EVObjNot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NOT logic");
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
	return(new EVObjNot(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//======================================================================================

bool		NotOutput::GetOutputBool(void)
{
	EVObjNot	*a=dynamic_cast<EVObjNot *>(GetParent());
	if(a!=NULL){
		return !a->GetValue();
	}
	return 0;
}


const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

EVObjNot::EVObjNot(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	Value	=0;

	NotInput	*a=new NotInput(this);
	AppendInputConnector(a);

	NotOutput	*d=new NotOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
EVObjNot::~EVObjNot(void)
{
}
void EVObjNot::paintEvent ( QPaintEvent * event )
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
	QString	Str(/**/"<NOT>");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	QString	Str2=(Value==true)?/**/"T->F":/**/"F->T";
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::yellow);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);

}

void	EVObjNot::IntervalExecute(void)
{
	Value=!GetInputBool(/**/"Input");
}
