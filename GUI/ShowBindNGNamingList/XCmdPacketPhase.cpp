/*
 * Copyright (C) 2021
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

#include "XGeneralFunc.h"
#include "ShowBindNGNamingListForm.h"


//=============================================================================

GUICmdReqNGNamingPhaseList::GUICmdReqNGNamingPhaseList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}
bool	GUICmdReqNGNamingPhaseList::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	return true;
}
bool	GUICmdReqNGNamingPhaseList::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	return true;
}

void	GUICmdReqNGNamingPhaseList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGNamingPhaseList	*SendBack=GetSendBack(GUICmdSendNGNamingPhaseList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		R->BindNGAreaListContainer(Phase,localPage,SendBack->NGData);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}


GUICmdSendNGNamingPhaseList::GUICmdSendNGNamingPhaseList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendNGNamingPhaseList::Load(QIODevice *f)
{
	if(NGData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNGNamingPhaseList::Save(QIODevice *f)
{
	if(NGData.Save(f)==false)
		return false;
	return true;
}