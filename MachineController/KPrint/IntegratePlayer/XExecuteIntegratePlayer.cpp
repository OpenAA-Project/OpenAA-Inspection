/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\ExecuteIntegratePlayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XDateTime.h"
#include <QThread>

#include "XExecuteIntegratePlayer.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <stdio.h>
#include "XParamGlobal.h"
//#include "XSequenceLocalExecuter.h"
#include "XFileRegistry.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XCriticalFunc.h"
#include "XResultDLLManager.h"
#include "XDataInExe.h"
#include "XFilterManager.h"
#include "XIntClass.h"
#include "XForWindows.h"
#include <omp.h>
#include "IntegratePlayer.h"
#include "XSequence.h"

const	int		MAXBUFFERCOUNTS=10000;
const	int		ExeSleepTimeMilisec=20;

ExecuteIntegratePlayer::ExecuteIntegratePlayer(IntegratePlayer *p, EntryPointBase *_EntryPoint ,int _UnitNo) 
: ExecuteInspectBase(p,_EntryPoint,NULL)
{
	CurrentState	=ExecuteInspectBase::_EI_IDLE;
	Parent			=p;
	UnitNo			=_UnitNo;
	setPriority(QThread::HighestPriority);
}

ExecuteIntegratePlayer::~ExecuteIntegratePlayer(void)
{
	Release();
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
}


void	ExecuteIntegratePlayer::Initial(void)
{
}

void	ExecuteIntegratePlayer::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
}


void	ExecuteIntegratePlayer::Release(void)
{
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
}

void	ExecuteIntegratePlayer::Exit(GUIFormBase *)
{
	if(GetLayersBase()->GetResultDLLBase()!=NULL)
		GetLayersBase()->GetResultDLLBase()->Release();
}

//==================================================================

static	DWORD		C,Cn;

void ExecuteIntegratePlayer::run()
{

IdleTurn:;
	for(;;){
		if(GetPermitToRun()==true){
			msleep(2);
			C=GetComputerMiliSec();

			GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
			GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

			Cn=GetComputerMiliSec();

			if(Parent->GetPIOInBit(1+UnitNo,0)!=0){
				Parent->SetResult(true,UnitNo);
				Parent->SetPIOOutBit(1+UnitNo,0,1);
				while(Parent->GetPIOInBit(1+UnitNo,0)!=0){
					GSleep(5);
					if(GetPermitToRun()==false){
						return;
					}
				}
				Parent->SetPIOOutBit(1+UnitNo,0,0);
				emit	SignalOK();
			}
			else
			if(Parent->GetPIOInBit(1+UnitNo,1)!=0){
				Parent->SetResult(false,UnitNo);
				Parent->SetPIOOutBit(1+UnitNo,0,1);
				while(Parent->GetPIOInBit(1+UnitNo,1)!=0){
					GSleep(5);
					if(GetPermitToRun()==false){
						return;
					}
				}
				Parent->SetPIOOutBit(1+UnitNo,0,0);
				emit	SignalNG();
			}
		}
	}
}
