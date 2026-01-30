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
#include "NListComp.h"
#include "XIntClass.h"
#include "XFlexArea.h"
#include <QByteArray>



class	IntegrationReqColorDifferenceItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;

	IntegrationReqColorDifferenceItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckColorDifferenceItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int			ItemClass;
	QByteArray	ThresholdData;
	bool        OutputConstantlyInItem;
	int			LibID;

	IntegrationAckColorDifferenceItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};
class	IntegrationSetColorDifferenceItemThresholdData: public IntegrationCmdPacketBase
{
public:
	int						LibType;
	ListPhasePageLayerItem	ItemIndex;
	QByteArray	ThresholdData;
	bool        OutputConstantlyInItem;

	IntegrationSetColorDifferenceItemThresholdData(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};

//===============================================================================

class	IntegrationReqColorDifferenceTryResult: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItem	ItemIndex;
	QByteArray				ThresholdData;

	IntegrationReqColorDifferenceTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckColorDifferenceTryResult: public IntegrationCmdPacketBase
{
public:
	int				ResultMoveDx;
	int				ResultMoveDy;
	int				Error;
	double			LenOK;
	double			LenNG;
	double			DeltaE;
	PreciseColor	ReferenceColor1	;
	PreciseColor	ReferenceColor2	;
	PreciseColor	MasterColor		;
	PreciseColor	TargetColor		;
	struct{
		double		MasterH,MasterS,MasterV;
		double		TargetH,TargetS,TargetV;
		double		SigmaH,SigmaS,SigmaV;
	}StatisticData;

	IntegrationAckColorDifferenceTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};