#include "NGNamingListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NGNamingList\XCmdPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XGeneralFunc.h"
#include "XCmdPacket.h"


//=============================================================================

GUICmdReqNGNamingList::GUICmdReqNGNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}
bool	GUICmdReqNGNamingList::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	return true;
}
bool	GUICmdReqNGNamingList::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	return true;
}

void	GUICmdReqNGNamingList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGNamingList	*SendBack=GetSendBack(GUICmdSendNGNamingList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		R->BindNGAreaListContainer(localPage,SendBack->NGData);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}


GUICmdSendNGNamingList::GUICmdSendNGNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendNGNamingList::Load(QIODevice *f)
{
	if(NGData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNGNamingList::Save(QIODevice *f)
{
	if(NGData.Save(f)==false)
		return false;
	return true;
}
