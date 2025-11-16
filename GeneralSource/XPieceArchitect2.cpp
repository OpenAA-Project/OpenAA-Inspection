/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XPieceArchitect2.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <cmath>
#include "XPieceArchitect.h"

PieceClass	*PieceStocker::SearchOnly(int masterCode)
{
	MutexLoader.lockForRead();
	PieceClass	*p;
	for(p=GetFirst();p!=NULL;p=p->GetNext()){
		if(p->GetMasterCode()==masterCode){
			MutexLoader.unlock();
			return p;
		}
	}
	MutexLoader.unlock();
	return NULL;
}
GUICmdReqUpdateAlgorithmOnPiece::GUICmdReqUpdateAlgorithmOnPiece(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage),IData(base)
{
}

bool	GUICmdReqUpdateAlgorithmOnPiece::Load(QIODevice *f)
{
	if(::Load(f,DLLRoot)==false){
		return false;
	}
	if(::Load(f,DLLName)==false){
		return false;
	}
	if(::Load(f,PieceCode)==false){
		return false;
	}
	if(::Load(f,Command)==false){
		return false;
	}
	if(IData.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdReqUpdateAlgorithmOnPiece::Save(QIODevice *f)
{
	if(::Save(f,DLLRoot)==false){
		return false;
	}
	if(::Save(f,DLLName)==false){
		return false;
	}
	if(::Save(f,PieceCode)==false){
		return false;
	}
	if(::Save(f,Command)==false){
		return false;
	}
	if(IData.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdReqUpdateAlgorithmOnPiece::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckUpdateAlgorithmOnPiece	*SendBack=GetSendBack(GUICmdAckUpdateAlgorithmOnPiece,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	QString ErrorMessageOfFalse;
	PieceClass	*Pc=GetLayersBase()->GetEntryPoint()->SearchAndLoadPiece(PieceCode,ErrorMessageOfFalse);
	if(Pc!=NULL){
		if(Pc->SetAlgorithmItemData(Command,DLLRoot,DLLName ,IData)==true){
			if(Pc->SaveAlgorithmForMaster(DLLRoot,DLLName)==true){
				SendBack->Ret=true;
			}
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
GUICmdAckUpdateAlgorithmOnPiece::GUICmdAckUpdateAlgorithmOnPiece(LayersBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Ret=false;
}

bool	GUICmdAckUpdateAlgorithmOnPiece::Load(QIODevice *f)
{
	if(::Load(f,Ret)==false){
		return false;
	}
	return true;
}
bool	GUICmdAckUpdateAlgorithmOnPiece::Save(QIODevice *f)
{
	if(::Save(f,Ret)==false){
		return false;
	}
	return true;
}

void	GUICmdAckUpdateAlgorithmOnPiece::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
