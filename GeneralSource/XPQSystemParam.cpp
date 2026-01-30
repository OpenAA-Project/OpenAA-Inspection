/*
 * Copyright (C) 2012
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

#include "XParamBase.h"
#include "XPQSystemParam.h"
#include"XGeneralFunc.h"



PQSystemParam::PQSystemParam(void)
{
	LocalDatabase_HostName	="localhost";
	LocalDatabase_Port		=3051;
	LocalDatabase_FileName	="D:/Data/Regulus64.fdb";

	ImageFilePath			="Z:";

	ResultDLLFileName		="PQSystemXMLAccessor.dll";

	SetParamPath	(&LocalDatabase_HostName	, /**/"SQLServer" ,/**/"LocalDatabase_HostName"		,"SQL Database Host Name / IP address"	,0);
	SetParam		(&LocalDatabase_Port		, /**/"SQLServer" ,/**/"LocalDatabase_Port"			,"SQL Database Port number"				,0,65536);
	SetParamFileName(&LocalDatabase_FileName	, /**/"SQLServer" ,/**/"LocalDatabase_FileName"		,"SQL Database file name with local path"	,0);

	SetParamPath	(&ImageFilePath				, /**/"ImagePath" ,/**/"ImageFilePath"				,"Image file pathes"	,0);

	SetParamFileName(&ResultDLLFileName			, /**/"XMLServer" ,/**/"ResultDLLFileName"			,"ResultDLL FileName"	,0);

}