/*
 * Copyright (C) 2025
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

#include "XPropertyWorld3DPacket.h"
#include "XGeneralFunc.h"
#include "XWorld3D.h"

GUICmdLoadStepFile::GUICmdLoadStepFile(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdLoadStepFile::Load(QIODevice *f)
{
	if(::Load(f,FArray)==false)	return false;
	return true;
}
bool	GUICmdLoadStepFile::Save(QIODevice *f)
{
	if(::Save(f,FArray)==false)	return false;
	return true;
}

void	GUICmdLoadStepFile::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	World3DBase *BBase=(World3DBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"World3D");
	if(BBase!=NULL){
		World3DInPage	*PData=dynamic_cast<World3DInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdLoadStepFile	Cmd(this);
			Cmd.FArray		=FArray;
			PData->TransmitDirectly(&Cmd);
		}
	}
}
