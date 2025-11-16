/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPalletize\XPropertyPalletizePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyPalletizePacket.h"
#include "XPalletize.h"
#include "XGeneralFunc.h"
//#include "XGUI.h"
#include "XPalletizeLibrary.h"

//=====================================================================================
GUICmdSendAddManualPalletize::GUICmdSendAddManualPalletize(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualPalletize::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualPalletize::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualPalletize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetUndoStocker().SetLocalTopic(GetIDForUndo());

	PalletizeBase *BBase=(PalletizeBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Palletize");
	if(BBase!=NULL){
		PalletizeInPage	*PData=dynamic_cast<PalletizeInPage	*>(BBase->GetPageData(localPage));
		if(PData!=NULL){
			CmdAddPalletizeItemPacket	Cmd(this);
			Cmd.Area		=Area;
			Cmd.LibID		=LibID;
			PData->TransmitDirectly(&Cmd);
		}
	}
	SendAck(localPage);
}
