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