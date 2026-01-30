/*
 * Copyright (C) 2025
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

#pragma once

#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmLibrary.h"
//#include "XMeasureLineMoveLibrary.h"
//#include "XMeasureLineMove.h"
#include "NListComp.h"



//-------------------------------------------------------------------------------------

class	IntegrationReqMeasureLineMoveSelectItems: public IntegrationCmdPacketBase
{
public:
	AlgorithmLibraryList	SelectedLib;
	FlexArea	GlobalArea;
	int			Phase;
	int			GlobalX,GlobalY;
	int			Mode;	//0:Area ,1:XY	2:Whole

	IntegrationReqMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationAckMeasureLineMoveSelectItems: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItemPack	Items;

	IntegrationAckMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqMeasureLineMoveSelectItems: public GUICmdPacketBase
{
public:
	AlgorithmLibraryList	SelectedLib;
	FlexArea	LocalArea;
	int			Phase;
	int			LocalX,LocalY;
	int			Mode;	//0:Area ,1:XY	2:Whole

	GUICmdReqMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckMeasureLineMoveSelectItems: public GUICmdPacketBase
{
public:
	ListPhasePageLayerItemPack	Items;

	GUICmdAckMeasureLineMoveSelectItems(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int GlobanPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage,int cmd,QString &EmitterRoot,QString &EmitterName){}
};

//-------------------------------------------------------------------------------------

class	IntegrationReqMeasureLineMoveItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;

	IntegrationReqMeasureLineMoveItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckMeasureLineMoveItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int		Line1ItemID;
	int		Line2ItemID;

	QByteArray	ThresholdDataDistance;
	QByteArray	ThresholdDataLine1;
	QByteArray	ThresholdDataLine2;
	double		OKLengthLUnit;
	double		OKLengthHUnit;

	IntegrationAckMeasureLineMoveItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationSetMeasureLineMoveItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;
	QByteArray	ThresholdDataDistance;
	QByteArray	ThresholdDataLine1;
	QByteArray	ThresholdDataLine2;

	IntegrationSetMeasureLineMoveItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

//===============================================================================

class	IntegrationReqMeasureLineMoveTryResult: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItem	ItemIndex;
	QByteArray	ThresholdDataDistance;
	QByteArray	ThresholdDataLine1;
	QByteArray	ThresholdDataLine2;

	IntegrationReqMeasureLineMoveTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckMeasureLineMoveTryResult: public IntegrationCmdPacketBase
{
public:
	bool	OK;
	double	Distance;
	

	IntegrationAckMeasureLineMoveTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};