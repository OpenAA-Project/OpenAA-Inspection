/*
 * Copyright (C) 2022
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
#include "XServiceForLayers.h"
#include "NListComp.h"


class	ParamPQSystem : public ParamBase ,public ServiceForLayers
{
public:
	QString	TitleMasterNumber	;
	QString	TitleMasterName		;
	QString	TitleRemark			;
	QString	TitleLotID			;
	QString	TitleLotNumber		;
	QString	TitleSubCode		;

	ParamPQSystem(LayersBase *base);
	~ParamPQSystem(void);
	virtual	QString	GetDataText(void)		override{	return("PQSystem Data");	};
	virtual	QString	GetDefaultFileName(void)override{	return("PQSystem.dat");		}

};