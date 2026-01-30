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


#include "PropertyAutoPCBHoleAlignerForm.h"
#include "EditAutoPCBHoleAlignerLibrary.h"
#include "XGeneralFunc.h"
#include "XAutoPCBHoleAlignerPacket.h"
#include "XAutoPCBHoleAligner.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


//=============================================================================================================

GUICmdCreateAutoPCBHoleAligner::GUICmdCreateAutoPCBHoleAligner(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCreateAutoPCBHoleAligner::Load(QIODevice *f)
{
	if(SelectedLibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdCreateAutoPCBHoleAligner::Save(QIODevice *f)
{
	if(SelectedLibList.Save(f)==false)
		return false;
	return true;
}

void	GUICmdCreateAutoPCBHoleAligner::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AutoPCBHoleAlignerBase *PBase=(AutoPCBHoleAlignerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	CmdCreateAutoPCBHoleAlignerHolePacket	Cmd(this);
	Cmd.SelectedLibList=SelectedLibList;
	Cmd.LocalPage	=localPage;
	PBase->TransmitDirectly(&Cmd);
}


GUICmdReqAutoPCBHoleAlignerInfo::GUICmdReqAutoPCBHoleAlignerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqAutoPCBHoleAlignerInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAutoPCBHoleAlignerInfo	*SendBack=GetSendBack(GUICmdSendAutoPCBHoleAlignerInfo,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->MakeData(localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAutoPCBHoleAlignerInfo::GUICmdSendAutoPCBHoleAlignerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAutoPCBHoleAlignerInfo::Load(QIODevice *f)
{
	if(AAInfoData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAutoPCBHoleAlignerInfo::Save(QIODevice *f)
{
	if(AAInfoData.Save(f)==false)
		return false;
	return true;
}
void	GUICmdSendAutoPCBHoleAlignerInfo::MakeData(int localPage)
{
	AutoPCBHoleAlignerBase *PBase=(AutoPCBHoleAlignerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	if(PBase!=NULL){
		CmdGetHoleInfo	Cmd(this);
		PBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
		AAInfoData=Cmd.AAInfoData;
	}
}

//=============================================================================================================