#include "PickupColorFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\XPropertyPixelInspectionPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyPixelInspectionPacket.h"
#include "XPixelInspection.h"
#include "XGeneralFunc.h"
#include "XGUI.h"


//=====================================================================================
GUICmdGeneratePixelInspection::GUICmdGeneratePixelInspection(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGeneratePixelInspection::~GUICmdGeneratePixelInspection(void)
{
}

bool	GUICmdGeneratePixelInspection::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdGeneratePixelInspection::Save(QIODevice *f)
{
	return true;
}

void	GUICmdGeneratePixelInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	/*
	CmdGenerateBlockPacket	PTestPacket;
	PTestPacket.LibList		=LibList;
	PTestPacket.LayerList	=LayerList;
	PTestPacket.Page		=localPage;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithm("Basic","BlockInspection");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&PTestPacket);
	}
	*/
}

//=====================================================================================
