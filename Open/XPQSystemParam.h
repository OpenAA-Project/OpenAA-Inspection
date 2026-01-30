/*
 * Copyright (C) 2016
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

#if	!defined(XPQSystemParam_h)
#define	XPQSystemParam_h

#include <QString>
#include "XTypeDef.h"
#include "XParamBase.h"

class	ParamBase;

class	PQSystemParam : public ParamBase
{
public:
	QString	LocalDatabase_HostName;
	int32	LocalDatabase_Port;
	QString	LocalDatabase_FileName;

	QString	ImageFilePath;

	QString	ResultDLLFileName;


	PQSystemParam(void);

	virtual	QString	GetDataText(void){	return("PQSystem Data");	};
	virtual	QString	GetDefaultFileName(void){	return DefaultFileName.isEmpty() ? "PQSystem.dat" : DefaultFileName;	}
};

#endif