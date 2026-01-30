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

#if	!defined(XParamIntegrationMaster_H)
#define	XParamIntegrationMaster_H

#include"XParamBase.h"
#include"XIntClass.h"
#include"XServiceForLayers.h"
#include "XTypeDef.h"
#include "NListComp.h"


class	IntegrationSlave : public NPListSaveLoad<IntegrationSlave>
{
public:
	int32		MachineCode;
	bool		SlaveIsInMaster;
	bool		Dependent;
	QString		SlaveAddress;
	QStringList	ImageFolders;
	QString		SharedFolder;
	int32		MinAdditionalSec;
	int32		MaxAdditionalSec;
	int32		CountOfConnectedPC;	//For Slave count
	int32		OffsetXForSync;
	int32		OffsetYForSync;

	IntegrationSlave(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	IntegrationSlaveContainer : public NPListPackSaveLoad<IntegrationSlave>
{
public:
	IntegrationSlaveContainer(void){}


	virtual	IntegrationSlave	*Create(void)	{	return new IntegrationSlave();	}
};


class	ParamIntegrationMaster : public ParamBase ,public ServiceForLayers
{
public:
	int32	IntegrationPortNo;
	int32	IntegrationPageDirectlyPortNo;
	IntegrationSlaveContainer	Slaves;
	bool	AllocateMasterBuff;
	bool	AllocateTargetBuff;
	bool	EnabeToLoadMasterImage;
	bool	Mastered;
	int32	OwnSlaveNo;				//-1:Not use Integration
	int32	SlaveSubNo;				//0: Primary Slave
	QString	MasterIPAddress;
	QString	SharedFolderForSlaveIntegration;
	int32	WaitMilisecToConnectByLAN;
	QString	RunningTimeFileName;
	bool	IntegrationSlaveMode;		//スレーブソフトを伴わない自己完結型
	bool	UseSystemResultStocker;

	ParamIntegrationMaster(LayersBase *base);
	~ParamIntegrationMaster(void);
	virtual	QString	GetDataText(void)	override{	return("ParamIntegrationMaster Data");	};
	virtual	QString	GetDefaultFileName(void)	override;	//{	return("ParamIntegrationMaster.dat");	}

	QString	GetSlaveSharedPath(int SlaveNo);
	int		GetIntegrationSlaveCount(void){	return Slaves.GetCount();	}

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;

	bool	IsIntegrationMaster(void)	const	{	return Mastered;		}
	int		GetOwnSlaveNo(void)			const	{	return OwnSlaveNo;		}
};


#endif