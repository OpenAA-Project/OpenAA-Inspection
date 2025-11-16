/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionPlayer\XSequenceLocal.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#define	_USE_MATH_DEFINES
#include <math.h>
#include "XSequenceLocalExecuter.h"
#include "XParamGlobal.h"
#include "XDataInExe.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XLightClass.h"
#include "XFormOperator.h"
#include "XLotInformation.h"
#include "IntegrationPlayer.h"

//---------------------------------------------------------------------------


SeqControlParam::SeqControlParam(IntegrationPlayer *p,LayersBase *Base) 
:SeqLocalParam(Base),Parent(p)
{
	ReadyForScan	=false;
	PermitCapture	=false;
	DoneCapture		=false;

	/*
	SetSpecialOperand(NULL					,0		,350	,"PCB type 0/1"							,_ReadWrite);
	SetSpecialOperand(NULL					,0		,400	,"TypeA - PC ready"						,_ReadWrite);
	SetSpecialOperand(NULL					,0		,401	,"TypeA - PCB Length"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,402	,"TypeA - PCB Width"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,403	,"TypeA - PCB Thickness"				,_ReadWrite);
	SetSpecialOperand(NULL					,0		,404	,"TypeA - Max stock OK"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,405	,"TypeA - Max stock BG"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,406	,"TypeA - ShiftX"						,_ReadWrite);
	SetSpecialOperand(NULL					,0		,410	,"TypeB - PC ready"						,_ReadWrite);
	SetSpecialOperand(NULL					,0		,411	,"TypeB - PCB Length"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,412	,"TypeB - PCB Width"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,413	,"TypeB - PCB Thickness"				,_ReadWrite);
	SetSpecialOperand(NULL					,0		,414	,"TypeB - Max stock OK"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,415	,"TypeB - Max stock BG"					,_ReadWrite);
	SetSpecialOperand(NULL					,0		,416	,"TypeB - ShiftX"						,_ReadWrite);

	SetSpecialOperand(&ReadyForScan			,false	,4		,"This indicates Ready-state for scanning and inspection. Sequence must wait till true(1).");
	SetSpecialOperand(NULL					,false	,5		,"In true(1), sequence can stop inspection/scanning process anytime.");
	SetSpecialOperand(&PermitCapture		,false	,20		,"If true(1) , capture(including inspect) proceeds");
	SetSpecialOperand(NULL					,true	,21		,"Light turns on in true"					,_ReadWrite	);
	SetSpecialOperand(&DoneCapture			,false	,30		,"Capture one time image"					,_ReadWrite);
	SetSpecialOperand(&ErrorNoSoftware		,false	,31		,"Error no software"						,_ReadWrite);

	SetSpecialOperand(NULL					,true	,100	,"Move window in A"							,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,101	,"Result OK in A"							,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,102	,"Result NG in A"							,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,103	,"Error in A"								,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,104	,"Knock on A"								,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,105	,"Unloaded stocker A"						,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,106	,"Finish A"									,_ReadWrite	);

	SetSpecialOperand(NULL					,true	,110	,"Move window in B"							,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,111	,"Result OK in B"							,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,112	,"Result NG in B"							,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,113	,"Error in B"								,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,114	,"Knock on B"								,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,115	,"Unloaded stocker B"						,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,116	,"Finish B"									,_ReadWrite	);

	SetSpecialOperand(NULL					,true	,203	,"Acknowledged unloading A"					,_ReadWrite	);
	SetSpecialOperand(NULL					,true	,213	,"Acknowledged unloading B"					,_ReadWrite	);

	*/
	QWidget	*W=GetLayersBase()->GetMainWidget();

	W->connect(this,SIGNAL(SignalLightOn())				,this,SLOT(SlotLightOn()),Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalLightOff())			,this,SLOT(SlotLightOff()),Qt::QueuedConnection);
	W->connect(this,SIGNAL(SignalMoveChildWindow(int))	,this,SLOT(SlotMoveChildWindow(int)),Qt::QueuedConnection);
}
SeqControlParam::~SeqControlParam(void)
{
}
int		SeqControlParam::GetDataSpecialOperand(int ID)	const
{
	return SeqLocalParam::GetDataSpecialOperand(ID);
}
void	SeqControlParam::SetDataSpecialOperand(int ID, int d)
{
}
void	SeqControlParam::SetDataSpecialBitOperand(int ID, bool d)
{
	switch(ID){
		default:
				SeqLocalParam::SetDataSpecialBitOperand(ID, d);
	}
}

void	SeqControlParam::SlotMoveChildWindow(int n)
{
	//Parent->MoveChildWindow(n);
}
	
void	SeqControlParam::SlotLightOn()
{
	GetLayersBase()->GetLightBase()->LightOn();
}

void	SeqControlParam::SlotLightOff()
{
	GetLayersBase()->GetLightBase()->LightOff();
}

bool	SeqControlParam::GetDataSpecialBitOperand(int ID)	const
{
	switch(ID){
		//case 2:	return GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartInspection;
		//case 3:	return GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartScanOnly;

		case 5:
				if(GetLayersBase()==NULL
				|| GetLayersBase()->GetEntryPoint()==NULL
				|| GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
					return false;
				}
				return GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetHaltMode();

		case 21:	if(GetLayersBase()->GetLightBase()!=NULL){
						return GetLayersBase()->GetLightBase()->IsTurnOn();
					}
					return false;

		default:
					return SeqLocalParam::GetDataSpecialBitOperand(ID);
	}
}
void	SeqControlParam::SetDataSpecialStringOperand(int ID, QString d)
{
	SeqLocalParam::SetDataSpecialStringOperand(ID, d);
}
QString SeqControlParam::GetDataSpecialStringOperand(int ID)	const
{
	return SeqLocalParam::GetDataSpecialStringOperand(ID);
}


//FifoIntPacket     SeqControlParam::SeqWriteID;

void    _XSeqLocalInit(SeqLocalParam *param ,SeqControl *seqControl)
{
	param->XSeqLocalInit(seqControl);
}

void    _SetDataSpecialOperand(SeqLocalParam *param ,int ID, int d)
{
	param->SetDataSpecialOperand(ID, d);
}

int     _GetDataSpecialOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialOperand(ID));
}

void    _SetDataSpecialBitOperand(SeqLocalParam *param ,int ID,bool d)
{
	param->SetDataSpecialBitOperand(ID, d);
}
bool     _GetDataSpecialBitOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialBitOperand(ID));
}


void _SetDataSpecialStringOperand(SeqLocalParam *param ,int ID, QString d)
{
	param->SetDataSpecialStringOperand(ID, d);
}

QString  _GetDataSpecialStringOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialStringOperand(ID));
}

void _SetDataSpecialFloatOperand(SeqLocalParam *param ,int ID, double d)
{
	param->SetDataSpecialFloatOperand(ID, d);
}

double  _GetDataSpecialFloatOperand(SeqLocalParam *param ,int ID)
{
	return(param->GetDataSpecialFloatOperand(ID));
}
