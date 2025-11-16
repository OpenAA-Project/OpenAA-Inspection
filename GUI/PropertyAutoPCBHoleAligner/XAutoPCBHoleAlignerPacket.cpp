/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoPCBHoleAligner\XAutoPCBHoleAlignerPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
