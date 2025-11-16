/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartStatisticScanButton\StartStatisticScanBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StartStatisticScanBase.h"
#include "StartStatisticScanButtonResource.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


StartStatisticScanBase::StartStatisticScanBase(LayersBase *Base)
	: ServiceForLayers(Base)
{
	Started=false;
}

void	StartStatisticScanBase::SlotToggledInside(bool checked)
{
	if(checked==true){
		if(Started==true){
			return;
		}
		GetLayersBase()->ShowProcessingForm (LangSolver.GetString(StartStatisticScanBase_LS,LID_0)/*"Start statistic scan"*/);
		GetLayersBase()->AddMaxProcessing(-1,0);
		OnToggled();

		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			Param->CaptureMode=3;
			//Param->StartScanOnly=true;
		}

		GUICmdStartStatisticScan	*Cmd[1000];
		GUICmdReplyStatisticScan	*Reply[1000];
		Started=true;
		StrategicListContainer SList;
		GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber()
									,SList);
		int	N=0;
		for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
			int page=s->Page;
			Cmd[N]	=new GUICmdStartStatisticScan(GetLayersBase(),sRoot,sName,page);
			Cmd[N]->Layer=s->Layer;
			Reply[N]	=new GUICmdReplyStatisticScan(GetLayersBase(),sRoot,sName,page);
		}
		for(int i=0;i<N;i++){
			Cmd[i]->Send(Cmd[i]->GetGlobalPage() ,0,*Reply[i]);
		}
		bool	ReadyAll;
		do{
			ReadyAll=true;
			for(int i=0;i<N;i++){
				if(Reply[i]->IsReceived()==false){
					ReadyAll=false;
				}
			}
		}while(ReadyAll==false);

		if(Param!=NULL){
			Param->ReadyForScan=true;
		}

		for(int i=0;i<N;i++){
			delete	Cmd[i]	;
			delete	Reply[i]	;
		}
	}
}

void StartStatisticScanBase::OnIdleFunc(void)
{
	if(Started==true){
		if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL)
			return;
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param->StartScanOnly==false){
			OnIdleEnd();
			Started=false;
		}
	}
}


//==================================================================================================

GUICmdStartStatisticScan::GUICmdStartStatisticScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdStartStatisticScan::~GUICmdStartStatisticScan(void)
{
}

bool	GUICmdStartStatisticScan::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	GUICmdStartStatisticScan::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdStartStatisticScan::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoTargetCaptureOnly();
	}
	
	GUICmdReplyStatisticScan	*SendBack=GetSendBack(GUICmdReplyStatisticScan,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdReplyStatisticScan::GUICmdReplyStatisticScan(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReplyStatisticScan::~GUICmdReplyStatisticScan(void)
{
}

bool	GUICmdReplyStatisticScan::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReplyStatisticScan::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReplyStatisticScan::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

