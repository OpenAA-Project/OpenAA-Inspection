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

#include "PropertyHalconResource.h"

#include "XPropertyHalconInspectionPacket.h"
#include "XHalconInspection.h"
#include "XGeneralFunc.h"
#include "XGUI.h"


//=====================================================================================
GUICmdGenerateHalconInspection::GUICmdGenerateHalconInspection(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateHalconInspection::~GUICmdGenerateHalconInspection(void)
{
}

bool	GUICmdGenerateHalconInspection::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdGenerateHalconInspection::Save(QIODevice *f)
{
	return true;
}

void	GUICmdGenerateHalconInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	/*
	CmdGenerateBlockPacket	PTestPacket;
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithm("Basic","BlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	*/
}

//=====================================================================================