#include "PropertyHalconResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\XPropertyHalconInspectionPacket.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XPropertyHalconInspectionPacket.h"
#include "XHalconInspection.h"
#include "XGeneralFunc.h"
#include "XGUI.h"


//=====================================================================================
GUICmdGenerateHalconInspection::GUICmdGenerateHalconInspection(LayersBase *Base ,QString &EmitterRoot,QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdGenerateHalconInspection::~GUICmdGenerateHalconInspection(void)
{
}

bool	GUICmdGenerateHalconInspection::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdGenerateHalconInspection::Save(QIODevice *f)
{
	return true;
}

void	GUICmdGenerateHalconInspection::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
