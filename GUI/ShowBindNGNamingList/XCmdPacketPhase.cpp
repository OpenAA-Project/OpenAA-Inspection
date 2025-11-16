/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowBindNGNamingListForm\XCmdPacketPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XGeneralFunc.h"
#include "ShowBindNGNamingListForm.h"


//=============================================================================

GUICmdReqNGNamingPhaseList::GUICmdReqNGNamingPhaseList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{}
bool	GUICmdReqNGNamingPhaseList::Load(QIODevice *f)
{
	if(::Load(f,ShownInspectionID)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	return true;
}
bool	GUICmdReqNGNamingPhaseList::Save(QIODevice *f)
{
	if(::Save(f,ShownInspectionID)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	return true;
}

void	GUICmdReqNGNamingPhaseList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGNamingPhaseList	*SendBack=GetSendBack(GUICmdSendNGNamingPhaseList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	if(R!=NULL){
		R->BindNGAreaListContainer(Phase,localPage,SendBack->NGData);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}


GUICmdSendNGNamingPhaseList::GUICmdSendNGNamingPhaseList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendNGNamingPhaseList::Load(QIODevice *f)
{
	if(NGData.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendNGNamingPhaseList::Save(QIODevice *f)
{
	if(NGData.Save(f)==false)
		return false;
	return true;
}
