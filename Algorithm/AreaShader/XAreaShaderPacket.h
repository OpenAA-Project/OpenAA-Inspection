/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XAREAFILTERPACKET_H
#define XAREAFILTERPACKET_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

class	AreaShaderLibrary;
class	AreaFilterItem;
class	GUICmdSendAddManualAreaShader : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	IntList		LayerList;
	int		CellSize;
	double	AdoptRate;	//çÃópó¶
	bool	Fixed;
	double	Average;
	double	Sigma;		//ïWèÄïŒç∑

	GUICmdSendAddManualAreaShader(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdCreateAreaShaderPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;
	IntList							LayerList;

	CmdCreateAreaShaderPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAreaShaderPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestAreaShaderPacket : public GUIDirectMessage
{
public:
	IntList					LayerList;
	//AreaShaderLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;

	CmdPickupTestAreaShaderPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestAreaShaderPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestAreaShaderPacket : public GUIDirectMessage
{
public:
	CmdClearTestAreaShaderPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestAreaShaderPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif