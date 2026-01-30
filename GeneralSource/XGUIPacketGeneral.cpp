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
#include <QSqlDatabase>
#include "XDataInLayerCommander.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XTransfer.h"
#include "XResultDLLManager.h"
#include <QThread>
#include "XForWindows.h"
#include "XShareMasterData.h"
#include "XLotInformation.h"
#include "XGeneralStocker.h"
#include "XAlgorithmDLL.h"
#include "XResultAnalizer.h"
#include "XGUIPacketGeneral.h"



GUICmdReleaseSelectImagePanel::GUICmdReleaseSelectImagePanel(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReleaseSelectImagePanel::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	return true;
}
bool	GUICmdReleaseSelectImagePanel::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	return true;
}

void	GUICmdReleaseSelectImagePanel::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		IntList PhaseList;
		ActivePhaseList(PhaseList);
		for(IntClass *v=PhaseList.GetFirst();v!=NULL;v=v->GetNext()){
			int phase=v->GetValue();
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(phase);
			AlgorithmInPageRoot	*P=Ah->GetPageData(localPage);
			if(P!=NULL){
				P->ReleaseAllSelectedItem();
			}
		}
	}
	SendAck(localPage);
}


//=======================================================================
GUICmdSelectByLibs::GUICmdSelectByLibs(AlgorithmBase *base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase((base!=NULL)?base->GetLayersBase():NULL,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	if(base!=NULL){
		base->GetDLLName(AlgoRoot ,AlgoName);
	}
}

bool	GUICmdSelectByLibs::Load(QIODevice *f)
{
	if(::Load(f,AlgoRoot)==false){
		return false;
	}
	if(::Load(f,AlgoName)==false){
		return false;
	}
	if(SelectedList.Load(f)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectByLibs::Save(QIODevice *f)
{
	if(::Save(f,AlgoRoot)==false){
		return false;
	}
	if(::Save(f,AlgoName)==false){
		return false;
	}
	if(SelectedList.Save(f)==false){
		return false;
	}
	return true;
}

void	GUICmdSelectByLibs::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	AlgorithmInPageRoot	*Ap=Ab->GetPageData(localPage);
	if(Ap!=NULL){
		Ap->SelectLibs(SelectedList);
	}
	SendAck(localPage);
}