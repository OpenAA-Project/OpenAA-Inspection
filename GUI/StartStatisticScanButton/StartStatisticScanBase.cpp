/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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
