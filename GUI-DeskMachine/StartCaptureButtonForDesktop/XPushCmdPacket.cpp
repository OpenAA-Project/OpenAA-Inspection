/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureButton\XPushCmdPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPushCmdPacket.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"

GUICmdPushedStartCapture::GUICmdPushedStartCapture(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdPushedStartCapture::Load(QIODevice *f)
{
	if(::Load(f,ImageType)==false)
		return false;
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	GUICmdPushedStartCapture::Save(QIODevice *f)
{
	if(::Save(f,ImageType)==false)
		return false;
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}

void	GUICmdPushedStartCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1 || StrategicNumber==0){
		GetLayersBase()->SetCurrentStrategicNumber		(StrategicNumber);
		GetLayersBase()->SetCurrentStrategicNumberForSeq(StrategicNumber);
	}
	
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(ImageType==/**/"Master")
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoMasterCaptureOnly();
		else if(ImageType==/**/"Target")	
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoTargetCaptureOnly();
	}
	
	GUICmdRepliedPushStartCapture	*SendBack=GetSendBack(GUICmdRepliedPushStartCapture,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdRepliedPushStartCapture::GUICmdRepliedPushStartCapture(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdRepliedPushStartCapture::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdRepliedPushStartCapture::Save(QIODevice *f)
{
	return true;
}
void	GUICmdRepliedPushStartCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
