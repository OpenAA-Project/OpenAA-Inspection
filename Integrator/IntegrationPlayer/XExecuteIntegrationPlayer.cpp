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

#include "XExecuteIntegrationPlayer.h"
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
#include "IntegrationPlayer.h"
#include "XSequence.h"
#include "XPIOButton.h"

const	int		MAXBUFFERCOUNTS=10000;
const	int		ExeSleepTimeMilisec=20;
ExecuteIntegrationPlayer	*ExecuteIntegrationPlayer::StaticInstance;

ExecuteIntegrationPlayer::ExecuteIntegrationPlayer(IntegrationPlayer *p, EntryPointBase *_EntryPoint) 
: ExecuteInspectBase(p,_EntryPoint,NULL)
{
	CurrentState	=ExecuteInspectBase::_EI_IDLE;
	Parent			=p;
	setPriority(QThread::HighestPriority);

	StaticInstance=this;
}

ExecuteIntegrationPlayer::~ExecuteIntegrationPlayer(void)
{
	Release();
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
}


void	ExecuteIntegrationPlayer::Initial(void)
{
}

void	ExecuteIntegrationPlayer::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
}


void	ExecuteIntegrationPlayer::Release(void)
{
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
}

void	ExecuteIntegrationPlayer::Exit(GUIFormBase *)
{
	if(GetLayersBase()->GetResultDLLBase()!=NULL)
		GetLayersBase()->GetResultDLLBase()->Release();
}

//==================================================================

static	DWORD		C,Cn;

void ExecuteIntegrationPlayer::run()
{

IdleTurn:;
	for(;;){
		if(GetPermitToRun()==true){
			C=GetComputerMiliSec();

			GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
			GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

			Cn=GetComputerMiliSec();
			msleep(10);
		}
	}
}
