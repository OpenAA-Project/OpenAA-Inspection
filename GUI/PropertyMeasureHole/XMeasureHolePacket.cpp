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

#include "CreateManualMeasureHoleFormResource.h"
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