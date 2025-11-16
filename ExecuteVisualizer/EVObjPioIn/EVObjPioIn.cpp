/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ExecuteVisualizer\EVObjPioIn\EVObjPioIn.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EVObjPioIn.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include <QPaintEvent>
#include <QPainter>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"
#include "PIOBitSettingDialog.h"
#include "ThreadSequence.h"
//#include "XSequence.h"
#include "XPIOButton.h"

static	const	char	*sRoot=/**/"Environment";
static	const	char	*sName=/**/"PioIn";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"PIO In bit");
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
	return(new RunnerPIOIn(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_ShowSettingDialog(RunnerObject *handle)
{
	PIOBitSettingDialog	W((RunnerPIOIn *)handle,NULL);
	W.exec();
	return true;
}


//======================================================================================
bool	PIOInOutput::GetOutputBool(void)
{
	RunnerPIOIn	*a=dynamic_cast<RunnerPIOIn *>(GetParent());
	if(a!=NULL){
		return a->GetPIOData();
	}
	return false;
}

const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerPIOIn::RunnerPIOIn(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	BoardNumber		=0;
	Port			=0;
	BitNumber		=0;
	ShowingNumber	=0;

	PIOInOutput	*d=new PIOInOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);

	ImageOn[0]	= new QImage(/**/":Resources/IN_On.png");
	ImageOn[1]	= new QImage(/**/":Resources/IN_On2.png");
	ImageOff[0]	= new QImage(/**/":Resources/IN_OFF.png");
	ImageOff[1]	= new QImage(/**/":Resources/IN_OFF2.png");

	SetImage(ImageOff[0]);
}
RunnerPIOIn::~RunnerPIOIn(void)
{
	delete	ImageOn[0];
	delete	ImageOn[1];

	delete	ImageOff[0];
	delete	ImageOff[1];
}

bool	RunnerPIOIn::Save(QIODevice *f)
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
bool	RunnerPIOIn::Load(QIODevice *f)
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

void RunnerPIOIn::paintEvent ( QPaintEvent * event )
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

bool	RunnerPIOIn::GetPIOData(void)
{
	ThreadSequence	*w=GetLayersBase()->GetSequenceInstance();
	if(w!=NULL){
		PIOClass *s=w->GetFirstPIO();
		//SeqControl	*s=w->GetMainSeqControl();
		if(s!=NULL){
			if(s->GetBit(BoardNumber,Port ,BitNumber)==0){
				return false;
			}
			else{
				return true;
			}
		}
	}
	return false;
}

void	RunnerPIOIn::IntervalExecute(void)
{
}