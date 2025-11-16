/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjPioOut\EVObjPioOut.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjPioOut.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"
#include "PIOBitSettingDialog.h"
#include "ThreadSequence.h"
#include "XPIOButton.h"

static	const	char	*sRoot=/**/"Environment";
static	const	char	*sName=/**/"PioOut";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"PIO Out bit");
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
	return(new RunnerPIOOut(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_ShowSettingDialog(RunnerObject *handle)
{
	PIOBitSettingDialog	W((RunnerPIOOut *)handle,NULL);
	W.exec();
	return true;
}

//======================================================================================
void	PIOOutInput::SetInputBool(bool b)
{
	RunnerPIOOut	*a=dynamic_cast<RunnerPIOOut *>(GetParent());
	if(a!=NULL){
		a->SetPIOData(b);
	}
}
const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerPIOOut::RunnerPIOOut(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	BoardNumber		=0;
	Port			=0;
	BitNumber		=0;
	ShowingNumber	=0;

	PIOOutInput	*d=new PIOOutInput(this);
	AppendInputConnector(d);

	resize(ObjWidth,ObjHeight);

	ImageOn[0]	= new QImage(/**/":Resources/OUT_On.png");
	ImageOn[1]	= new QImage(/**/":Resources/OUT_On2.png");
	ImageOff[0]	= new QImage(/**/":Resources/OUT_OFF.png");
	ImageOff[1]	= new QImage(/**/":Resources/OUT_OFF2.png");

	SetImage(ImageOff[0]);
}

RunnerPIOOut::~RunnerPIOOut(void)
{
	delete	ImageOn[0];
	delete	ImageOn[1];

	delete	ImageOff[0];
	delete	ImageOff[1];
}

bool	RunnerPIOOut::Save(QIODevice *f)
{
	if(RunnerObject::Save(f)==false)
		return false;
	if(::Save(f,BoardNumber)==false)
		return false;
	if(::Save(f,Port)==false)
		return false;
	if(::Save(f,BitNumber)==false)
		return false;
	return true;
}
bool	RunnerPIOOut::Load(QIODevice *f)
{
	if(RunnerObject::Load(f)==false)
		return false;
	if(::Load(f,BoardNumber)==false)
		return false;
	if(::Load(f,Port)==false)
		return false;
	if(::Load(f,BitNumber)==false)
		return false;
	return true;
}


void RunnerPIOOut::paintEvent ( QPaintEvent * event )
{
	static	bool	ReEntrance=false;

	if(ReEntrance==true)
		return;

	ReEntrance=true;

	if(GetPIOData()==true){
		if(ShowingNumber==0 || ShowingNumber==1 || ShowingNumber==2){
			SetImage(ImageOn[0]);
		}
		else{
			SetImage(ImageOn[1]);
		}
	}
	else{
		if(ShowingNumber==0 || ShowingNumber==1 || ShowingNumber==2){
			SetImage(ImageOff[0]);
		}
		else{
			SetImage(ImageOff[1]);
		}
	}
	ShowingNumber++;
	if(ShowingNumber>=6){
		ShowingNumber=0;
	}

	QPainter	Pnt(this);

	if(CurrentImage!=NULL){
		Pnt.drawImage(0,0,*CurrentImage);
	}

	Pnt.setPen(Qt::black);

	int	R=4;
	int	H=(ObjHeight-2*R)/4;
	QRect	Rect1(ObjWidth/2,R,ObjWidth/2-R,H);
	Pnt.drawText(Rect1, Qt::AlignRight | Qt::AlignVCenter ,QString(/**/"Brd: ")+QString::number(BoardNumber));

	QRect	Rect2(ObjWidth/2,R+H,ObjWidth/2-R,H);
	Pnt.drawText(Rect2, Qt::AlignRight | Qt::AlignVCenter ,QString(/**/"Prt: ")+QString::number(Port));

	QRect	Rect3(ObjWidth/2,R+H*2,ObjWidth/2-R,H);
	Pnt.drawText(Rect3, Qt::AlignRight | Qt::AlignVCenter ,QString(/**/"Bit: ")+QString::number(BitNumber));

	QRect	Rect4(R,R+H*3,ObjWidth-R*2,H);
	Pnt.drawText(Rect4, Qt::AlignHCenter | Qt::AlignVCenter ,GetUniqueName());

	ReEntrance=false;
}

void	RunnerPIOOut::SetPIOData(bool d)
{
	ThreadSequence	*w=GetLayersBase()->GetSequenceInstance();
	if(w!=NULL){
		PIOClass *s=w->GetFirstPIO();
		//SeqControl	*s=w->GetMainSeqControl();
		if(s!=NULL){
			BYTE	D;
			if(d==true)
				D=1;
			else
				D=0;
			s->SetBit(BoardNumber,Port,BitNumber,D);
		}
	}
}
bool	RunnerPIOOut::GetPIOData(void)
{
	ThreadSequence	*w=GetLayersBase()->GetSequenceInstance();
	if(w!=NULL){
		PIOClass *s=w->GetFirstPIO();
		//SeqControl	*s=w->GetMainSeqControl();
		if(s!=NULL){
			if(s->GetOutBit(BoardNumber,8*Port+BitNumber)==0){
				return false;
			}
			else{
				return true;
			}
		}
	}
	return false;
}
void	RunnerPIOOut::IntervalExecute(void)
{
}