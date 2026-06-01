/*
 * Copyright (C) 2017
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

#include "CreateSpotReducerFormResource.h"
#include "XPropertySpotReducerPacket.h"
#include "XGeneralFunc.h"
#include "XSpotReducer.h"


GUICmdAddSpotReducerArea::GUICmdAddSpotReducerArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdAddSpotReducerArea::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(::Load(f,SpotBrightness)==false)
		return false;
	if(::Load(f,ReductionLevel)==false)
		return false;
	if(::Load(f,SpotArea)==false)
		return false;
	if(::Load(f,SpotCount)==false)
		return false;
	
	return true;
}
bool	GUICmdAddSpotReducerArea::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(::Save(f,SpotBrightness)==false)
		return false;
	if(::Save(f,ReductionLevel)==false)
		return false;
	if(::Save(f,SpotArea)==false)
		return false;
	if(::Save(f,SpotCount)==false)
		return false;
	return true;
}

void	GUICmdAddSpotReducerArea::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"SpotReducer");
	if(L==NULL)
		return;
	AlgorithmInPageRoot		*PData=L->GetPageData(localPage);
	if(PData==NULL)
		return;
	AddSpotReducerAreaPacket	Cmd(this);
	Cmd.Area			=Area;
	Cmd.LayerList		=LayerList;
	Cmd.SpotBrightness	=SpotBrightness;
	Cmd.ReductionLevel	=ReductionLevel;
	Cmd.SpotArea		=SpotArea;
	Cmd.SpotCount		=SpotCount;
	PData->TransmitDirectly(&Cmd);
	
	SendAck(localPage);
}