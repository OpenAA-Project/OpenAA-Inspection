/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjOr\EVObjOr.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjOr.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "SetCountOfInputDialog.h"

static	const	char	*sRoot=/**/"Calc";
static	const	char	*sName=/**/"EVObjOr";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"OR logic");
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
	return(new EVObjOr(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_ShowSettingDialog(RunnerObject *handle)
{
	EVObjOr	*h=dynamic_cast<EVObjOr *>(handle);
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

bool		OrOutput::GetOutputBool(void)
{
	EVObjOr	*a=dynamic_cast<EVObjOr *>(GetParent());
	if(a!=NULL){
		return a->GetValue();
	}
	return false;
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

EVObjOr::EVObjOr(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	Value	=0;
	InputNumb	=2;

	SetInputConnectors();

	OrOutput	*d=new OrOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
EVObjOr::~EVObjOr(void)
{
}

void EVObjOr::SetInputConnectors(void)
{
	if(GetInputCount()<InputNumb){
		for(int i=GetInputCount();i<InputNumb;i++){
			OrInput	*a=new OrInput(this ,i);
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
	
bool	EVObjOr::Save(QIODevice *f)
{
	if(RunnerObject::Save(f)==false)
		return false;
	if(::Save(f,InputNumb)==false)
		return false;
	return true;
}

bool	EVObjOr::Load(QIODevice *f)
{
	if(RunnerObject::Load(f)==false)
		return false;
	if(::Load(f,InputNumb)==false)
		return false;
	SetInputConnectors();
	return true;
}


void EVObjOr::paintEvent ( QPaintEvent * event )
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
	QString	Str(/**/"<OR>");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	QString	Str2=(Value==true)?/**/"TRUE":/**/"false";
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::yellow);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);

}

void	EVObjOr::IntervalExecute(void)
{
	Value=false;
	int	N=GetInputCount();
	for(int i=0;i<N;i++){
		if(GetInputBool(i)==true){
			Value=true;
			break;
		}
	}
}
