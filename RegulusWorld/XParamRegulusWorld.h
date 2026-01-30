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

#pragma once

#include "XParamBase.h"
#include "XIntClass.h"
#include "NListComp.h"
#include "XTypeDef.h"

class RegulusWorld;

class RWDeviceParamList : public NPListSaveLoad<RWDeviceParamList>
{
public:
	int			DeviceID;
	QString		DLLFileName;
	QString		Parameter;

	RWDeviceParamList(void);
	RWDeviceParamList(const RWDeviceParamList &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	RWDeviceParamList	&operator=(const RWDeviceParamList &src);
};

class RWDeviceParamListContainer: public NPListPackSaveLoad<RWDeviceParamList>
{
public:
	RWDeviceParamListContainer(void){}
	RWDeviceParamListContainer(const RWDeviceParamListContainer &src);

	virtual	RWDeviceParamList	*Create(void)	override;
	RWDeviceParamListContainer	&operator=(const RWDeviceParamListContainer &src);
};

//============================================================

class	ParamRegulusWorld : public ParamBase
{
	RegulusWorld	*Parent;
public:
	int32	PageNumb;
	QString	DataFilePath;
	QString	ErrorLogFile;
	RWDeviceParamListContainer	RWDeviceParams;

	ParamRegulusWorld(RegulusWorld *base);

	virtual	QString	GetDataText(void)			override{	return("GlobalRegulusWorld Data");	};
	virtual	QString	GetDefaultFileName(void)	override{	return("GlobalRegulusWorld.dat");	}

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition=-1)	override;

};