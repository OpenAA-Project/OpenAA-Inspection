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
#include <QString>


class BCodeItemList : public NPListSaveLoad<BCodeItemList>
{
public:
	ListPhasePageLayerItem	ItemIndex;
	int						x1,y1,x2,y2;
	QString					Result;

	BCodeItemList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	BCodeItemList	&operator=(const BCodeItemList &src);
};

class BCodeItemListContainer : public NPListPackSaveLoad<BCodeItemList>
{
public:
	BCodeItemListContainer(void){}

	virtual	BCodeItemList	*Create(void)	{	return new BCodeItemList();	}
	BCodeItemListContainer	&operator+=(const BCodeItemListContainer &src);
	BCodeItemListContainer	&operator=(const BCodeItemListContainer &src);
};

//===============================================================================

class	IntegrationReqBCodeItemListInfo: public IntegrationCmdPacketBase
{
public:
	int	Phase;
	IntegrationReqBCodeItemListInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationAckBCodeItemListInfo: public IntegrationCmdPacketBase
{
public:
	BCodeItemListContainer	Container;

	IntegrationAckBCodeItemListInfo(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

//===============================================================================

class	IntegrationReqBCRInspectionTryResult: public IntegrationCmdPacketBase
{
public:
	ListPhasePageLayerItem	ItemIndex;
	QByteArray				ThresholdData;

	IntegrationReqBCRInspectionTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};

class	IntegrationAckBCRInspectionTryResult: public IntegrationCmdPacketBase
{
public:
	QString		Result;

	IntegrationAckBCRInspectionTryResult(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};