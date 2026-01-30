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



#ifndef XDATAINLAYERCOMMANDER_H
#define XDATAINLAYERCOMMANDER_H

#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"


//============================================================================
class	GUICmdSendAlgorithmItemIndependentPack : public GUICmdPacketBase
{
public:
	bool								NeedInitializerOfUndo;
	AlgorithmItemIndependentPack		IData;
	int32								Command;

	GUICmdSendAlgorithmItemIndependentPack(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1,bool needUndo=false);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlgorithmItemIndependentPack : public GUICmdPacketBase
{
public:
	bool								NeedInitializerOfUndo;
	AlgorithmItemIndependentPack		IData;
	int32								Command;

	GUICmdReqAlgorithmItemIndependentPack(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1,bool needUndo=false);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlgorithmItemIndependentPack : public GUICmdPacketBase
{
public:
	ItemDataWithPhasePageLayerContainer	Container;

	GUICmdAckAlgorithmItemIndependentPack(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1,bool needUndo=false);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdReqAlgorithmGeneralData : public GUICmdPacketBase
{
public:
	void	*Data;
	int32	ReqCommand;
	int32	SendCommand;
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	GUICmdReqAlgorithmGeneralData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	BuildData(QString algorithmRoot,QString	algorithmName ,int32 reqCommand ,int32 sendCommand);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	*GetData(void){	return Data;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlgorithmGeneralData : public GUICmdPacketBase
{
public:
	void	*Data;
	int32	SendCommand;
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	GUICmdSendAlgorithmGeneralData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	BuildData(QString algorithmRoot,QString	algorithmName ,int32 sendCommand,void *reqData);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	*GetData(void){	return Data;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqMoveForAlignment : public GUICmdPacketBase
{
public:
	GUICmdReqMoveForAlignment(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	CmdGetCurrentInfo :public GUIDirectMessage
{
public:
	int		ShadowLevel ;
	int		ShadowNumber;
	int		Phase;
	int		Page;
	int		Layer;
	int		ItemID;
	int		LibType;
	int		LibID;
	AlgorithmItemRoot	*RepresentativeItem;

	CmdGetCurrentInfo(LayersBase *base);
	CmdGetCurrentInfo(GUICmdPacketBase *gbase);
};


#endif
