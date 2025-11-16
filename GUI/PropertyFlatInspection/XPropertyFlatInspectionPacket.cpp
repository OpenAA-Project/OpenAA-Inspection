//#include "CreateManualFlatInspectionFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyFlatInspection\XPropertyFlatInspectionPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
	FlatInspectionBase *BBase=(FlatInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"FlatInspection");
	if(BBase!=NULL){
		FlatInspectionInPage	*Ap=(FlatInspectionInPage *)BBase->GetPageData(localPage);
		CmdSendAddManualFlatInspection	Cmd(GetLayersBase());
		Cmd.FIType=FIType;
		Cmd.Area=Area;
		Cmd.LibID=LibID;
		Ap->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

