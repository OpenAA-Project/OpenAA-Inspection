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

//#include "CreateManualFlatInspectionFormResource.h"

#include "XPropertyFlatInspectionPacket.h"
#include "XFlatInspection.h"
#include "XFlatInspectionAlgoPacket.h"
#include "XGeneralFunc.h"
//#include "XGUI.h"


GUICmdSendAddManualFlatInspection::GUICmdSendAddManualFlatInspection(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAddManualFlatInspection::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)	return false;
	if(Area.Load(f)==false)		return false;
	int	d;
	if(::Load(f,d)==false)	return false;
	FIType=(FlatInspectionItem::FlatInspectionType)d;
	return true;
}
bool	GUICmdSendAddManualFlatInspection::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)	return false;
	if(Area.Save(f)==false)		return false;
	int	d=(int)FIType;
	if(::Save(f,d)==false)	return false;
	return true;
}


void	GUICmdSendAddManualFlatInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase *BBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"FlatInspection");
	if(BBase!=NULL){
		AlgorithmInPageRoot	*Ap=BBase->GetPageData(localPage);
		CmdSendAddManualFlatInspection	Cmd(GetLayersBase());
		Cmd.FIType=FIType;
		Cmd.Area=Area;
		Cmd.LibID=LibID;
		Ap->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}
