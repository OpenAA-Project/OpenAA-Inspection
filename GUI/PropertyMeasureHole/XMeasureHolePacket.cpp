#include "CreateManualMeasureHoleFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\XMeasureHolePacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XMeasureHolePacket.h"
#include "XMeasureHole.h"


GUICmdSendAddManualMeasureHole::GUICmdSendAddManualMeasureHole(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendAddManualMeasureHole::Load(QIODevice *f)
{
	int64	Len;
	if(::Load(f,Len)==false)
		return false;
	BItem=f->read(Len);
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdSendAddManualMeasureHole::Save(QIODevice *f)
{
	int64	Len=BItem.size();
	if(::Save(f,Len)==false)
		return false;
	if(f->write(BItem,Len)==false)
		return false;
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	GUICmdSendAddManualMeasureHole::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MeasureHoleBase *BBase=(MeasureHoleBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHole");
	if(BBase!=NULL){
		CmdAddByteMeasureHoleItemPacket	Cmd(this);
		Cmd.Buff		=BItem;
		Cmd.Area		=Area;
		Cmd.LocalPage	=localPage;
		BBase->TransmitDirectly(&Cmd);
	}
}

CmdReqMeasureHoleColorMap::CmdReqMeasureHoleColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdReqMeasureHoleColorMap::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	return true;
}
bool	CmdReqMeasureHoleColorMap::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	return true;
}

void	CmdReqMeasureHoleColorMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdAckMeasureHoleColorMap	*SendBack=GetSendBack(CmdAckMeasureHoleColorMap,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	ImagePointerContainer Images;
	GetLayersBase()->GetPageData(localPage)->GetTargetImages(Images);
	RGBStock	PickupSamples;
	Area.CreateRGBStock(Images, PickupSamples);
		
	ColorSphere	*b=new ColorSphere();
	b->Create(PickupSamples);
	SendBack->Color.AddBase(b);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

CmdAckMeasureHoleColorMap::CmdAckMeasureHoleColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	CmdAckMeasureHoleColorMap::Load(QIODevice *f)
{
	if(Color.Load(f)==false)
		return false;
	return true;
}
bool	CmdAckMeasureHoleColorMap::Save(QIODevice *f)
{
	if(Color.Save(f)==false)
		return false;
	return true;
}

void	CmdAckMeasureHoleColorMap::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
