/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\DisplayThumbnailImage\DisplayThumbnailImagePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGeneralFunc.h"
#include "DisplayThumbnailImagePacket.h"
/*
bool	CmdSetNGInformation::Load(QIODevice *f)
{
	if(::Load(f,ErrorGroupTableCount)==false)
		return false;
	return true;
}
bool	CmdSetNGInformation::Save(QIODevice *f)
{
	if(::Save(f,ErrorGroupTableCount)==false)
		return false;
	for(int Cnt=0;Cnt<ErrorGroupTableCount;Cnt++){
		ErrorGroup	*p=ErrorGroupTable[Cnt];
		if(f->write((char *)p,sizeof(p[0]))!=sizeof(p[0]))
			return false;
	}
	if(::Save(f,CenterX)==false)
		return false;
	if(::Save(f,CenterY)==false)
		return false;
	if(::Save(f,NGWidth)==false)
		return false;
	if(::Save(f,NGHeight)==false)
		return false;
	return true;
}

GUICmdSetNGInformation::GUICmdSetNGInformation(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
,State(Base)
{
}

bool	GUICmdSetNGInformation::Load(QIODevice *f)
{
	if(State.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSetNGInformation::Save(QIODevice *f)
{
	if(State.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSetNGInformation::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyAutoAlignment" ,"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&State);
	}
}
*/
