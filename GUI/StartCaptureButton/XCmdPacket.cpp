#include "startcapturebuttonResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartCaptureButton\XCmdPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XCmdPacket.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"

GUICmdPushed::GUICmdPushed(const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
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

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName ,EntryPointForLocal &LocalEntry)
{
	if(LocalEntry.GetExecuteInspect()!=NULL){
		if(ImageType==/**/"Master")	
			LocalEntry.GetExecuteInspect()->GoMasterCaptureOnly();
		else if(ImageType==/**/"Target")	
			LocalEntry.GetExecuteInspect()->GoTargetCaptureOnly();
	}
}
