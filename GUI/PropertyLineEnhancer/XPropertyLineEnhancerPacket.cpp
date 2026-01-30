/*
 * Copyright (C) 2021
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

#include "PropertyLineEnhancerForm.h"
#include "XLineEnhancer.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
//#include "XLineEnhancerPacket.h"
#include "EditLibraryMono.h"
#include "XGeneralFunc.h"

//=============================================================================================================
GUICmdCreateLineEnhancer::GUICmdCreateLineEnhancer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdCreateLineEnhancer::Load(QIODevice *f)
{
	if(SelectedLibList.Load(f)==false)
		return false;
	return true;
}
bool	GUICmdCreateLineEnhancer::Save(QIODevice *f)
{
	if(SelectedLibList.Save(f)==false)
		return false;
	return true;
}
void	GUICmdCreateLineEnhancer::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LineEnhancerBase *PBase=(LineEnhancerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
	if(PBase!=NULL){
		CmdCreateLineEnhancerPacket	Cmd(this);
		Cmd.SelectedLibList=SelectedLibList;
		Cmd.LocalPage	=localPage;
		PBase->GetPageData(localPage)->TransmitDirectly(&Cmd);
	}
	SendAck(localPage);
}

//=============================================================================================================

GUICmdPickupTestList::GUICmdPickupTestList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	LibPoint=NULL;
	CreatedInside=false;
}

GUICmdPickupTestList::~GUICmdPickupTestList(void)
{
	if(CreatedInside==true)
		delete	LibPoint;
	LibPoint=NULL;
}


bool	GUICmdPickupTestList::Load(QIODevice *f)
{
	if(LibPoint==NULL){
		CreatedInside=true;
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
		if(Ab!=NULL){
			CmdCreateTempLineEnhancerLibraryPacket	Packet(GetLayersBase());
			Ab->TransmitDirectly(&Packet);
			LibPoint=Packet.Point;
		}
	}
	if(LibPoint==NULL)
		return false;
	int32	LibID;
	if(::Load(f,LibID)==false)
		return false;
	LibPoint->SetLibID(LibID);
	if(LibPoint->LoadBlob(f)==false)
		return false;

	return true;
}
bool	GUICmdPickupTestList::Save(QIODevice *f)
{
	if(LibPoint==NULL)
		return false;
	int32	LibID=LibPoint->GetLibID();
	if(::Save(f,LibID)==false)
		return false;
	if(LibPoint->SaveBlob(f)==false)
		return false;

	return true;
}

void	GUICmdPickupTestList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdPickupTestLineEnhancerPacket	PTestPacket(this);
	PTestPacket.LibPoint	=LibPoint;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&PTestPacket);
	}
	SendAck(localPage);
}

//=============================================================================================================

GUICmdTestClear::GUICmdTestClear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdTestClear::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdClearTestLineEnhancePacket	ClearTestPacket(this);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
	if(Ab!=NULL){
		Ab->GetPageData(localPage)->TransmitDirectly(&ClearTestPacket);
	}
	SendAck(localPage);
}

//=============================================================================================================

GUICmdSetDrawing::GUICmdSetDrawing(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetDrawing::Load(QIODevice *f)
{
	int	N;
	if(::Load(f,N)==false)
		return false;
	DrawingArea=(LineEnhancerDrawAttr::_DrawingArea)N;
	if(::Load(f,InstName)==false)
		return false;
	return true;
}
bool	GUICmdSetDrawing::Save(QIODevice *f)
{
	int	N=(int)DrawingArea;
	if(::Save(f,N)==false)
		return false;
	if(::Save(f,InstName)==false)
		return false;
	return true;
}

void	GUICmdSetDrawing::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSetLineEnhancerDrawMode	DrawMode(this);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLineEnhancer" ,InstName);
	if(GProp!=NULL){
		DrawMode.DrawingArea	=DrawingArea;
		GProp->TransmitDirectly(&DrawMode);
	}

}