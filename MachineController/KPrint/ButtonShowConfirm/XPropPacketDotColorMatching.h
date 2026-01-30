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
//#include "XDotColorMatchingLibrary.h"
//#include "XDotColorMatching.h"
#include "NListComp.h"
#include "XIntClass.h"
#include "XFlexArea.h"
#include <QByteArray>

//===============================================================================

class	IntegrationReqDotColorMatchingTryResult: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItem	ItemIndex;
	QByteArray				ThresholdData;

	IntegrationReqDotColorMatchingTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckDotColorMatchingTryResult: public IntegrationCmdPacketBase
{
public:
	struct ResultInfo
	{
		WORD	CenterBrightR;
		WORD	CenterBrightG;
		WORD	CenterBrightB;
		WORD	CenterTargetBrightR;
		WORD	CenterTargetBrightG;
		WORD	CenterTargetBrightB;

		int		CurrentRotationPatternNo;
		int		ResultDx;
		int		ResultDy;
		int		ResultSelfSeachDx;
		int		ResultSelfSeachDy;
		int		ResultCode;			//1:OK	2:NGSize	3:MultiCount	4:

		DWORD	NGResultSize;
		DWORD	NGResultLength;
		DWORD	NGResultGroundSize;
		DWORD	NGResultGroundLength;
		DWORD	NGResultRedSize;
		DWORD	NGResultMultiCount;
	}ResultInfoData;
	FlexArea	NGShape;

	IntegrationAckDotColorMatchingTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName){}
};