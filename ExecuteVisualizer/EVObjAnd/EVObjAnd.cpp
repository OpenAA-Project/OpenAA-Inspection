/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjAnd\EVObjAnd.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjAnd.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "SetCountOfInputDialog.h"

static	const	char	*sRoot="Calc";
static	const	char	*sName="EVObjAnd";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("AND logic");
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
	return(new EVObjAnd(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_ShowSettingDialog(RunnerObject *handle)
{
	EVObjAnd	*h=dynamic_cast<EVObjAnd *>(handle);
	if(h!=NULL){
		SetCountOfInputDialog	W(h->InputNumb,NULL);
		if(W.exec()==(int)true){
			h->InputNumb=W.InputNumb;
			h->SetInputConnectors();
		}
	}
	return true;
}

//======================================================================================

bool		AndOutput::GetOutputBool(void)
{
	EVObjAnd	*a=dynamic_cast<EVObjAnd *>(GetParent());
	if(a!=NULL){
		return a->GetValue();
	}
	return false;
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

EVObjAnd::EVObjAnd(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	Value	=0;
	InputNumb	=2;

	SetInputConnectors();

	AndOutput	*d=new AndOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
EVObjAnd::~EVObjAnd(void)
{
}

void EVObjAnd::SetInputConnectors(void)
{
	if(GetInputCount()<InputNumb){
		for(int i=GetInputCount();i<InputNumb;i++){
			AndInput	*a=new AndInput(this ,i);
			AppendInputConnector(a);
		}
	}
	else if(GetInputCount()<InputNumb){
		while(GetInputCount()!=InputNumb){
			RunnerConnector	*L=InputConnectors.GetLast();
			InputConnectors.RemoveList(L);
			delete	L;
		}
	}
}
	
bool	EVObjAnd::Save(QIODevice *f)
{
	if(RunnerObject::Save(f)==false)
		return false;
	if(::Save(f,InputNumb)==false)
		return false;
	return true;
}

bool	EVObjAnd::Load(QIODevice *f)
{
	if(RunnerObject::Load(f)==false)
		return false;
	if(::Load(f,InputNumb)==false)
		return false;
	SetInputConnectors();
	return true;
}


void EVObjAnd::paintEvent ( QPaintEvent * event )
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
	QString	Str("<AND>");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	QString	Str2=(Value==true)?"TRUE":"false";
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::yellow);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);

}

void	EVObjAnd::IntervalExecute(void)
{
	Value=true;
	int	N=GetInputCount();
	for(int i=0;i<N;i++){
		if(GetInputBool(i)==false){
			Value=false;
			break;
		}
	}
}
