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