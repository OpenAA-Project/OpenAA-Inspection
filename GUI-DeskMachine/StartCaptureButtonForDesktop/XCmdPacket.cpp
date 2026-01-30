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


#include "XCmdPacket.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"

GUICmdPushed::GUICmdPushed(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdPushed::Load(QIODevice *f)
{
	if(::Load(f,ImageType)==false)
		return false;
	return true;
}
bool	GUICmdPushed::Save(QIODevice *f)
{
	if(::Save(f,ImageType)==false)
		return false;
	return true;
}

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	EntryPointBase	*E=GetLayersBase()->GetEntryPoint();
	if(E->GetExecuteInspect()!=NULL){
		if(ImageType=="Master")
			E->GetExecuteInspect()->GoMasterCaptureOnly();
		else if(ImageType=="Target")
			E->GetExecuteInspect()->GoTargetCaptureOnly();
	}
}