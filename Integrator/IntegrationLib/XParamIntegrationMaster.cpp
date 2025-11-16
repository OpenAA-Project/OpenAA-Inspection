#include "XParamIntegrationMaster.h"
#include<QIODevice>
#include"XGeneralFunc.h"
#include"swap.h"
#include "XDataInLayer.h"

IntegrationSlave::IntegrationSlave(void)
{	
	MachineCode=0;
	SlaveIsInMaster	=false;
	Dependent		=false;
	MinAdditionalSec=MaxAdditionalSec=0;
	CountOfConnectedPC=0;
	OffsetXForSync=0;
	OffsetYForSync=0;
}

bool	IntegrationSlave::Save(QIODevice *f)
{
	int32	Ver=4;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,MachineCode)==false)
		return false;
	if(::Save(f,SlaveIsInMaster)==false)
		return false;
	if(::Save(f,Dependent)==false)
		return false;
	if(::Save(f,SlaveAddress)==false)
		return false;
	if(::Save(f,ImageFolders)==false)
		return false;
	if(::Save(f,SharedFolder)==false)
		return false;
	if(::Save(f,MinAdditionalSec)==false)
		return false;
	if(::Save(f,MaxAdditionalSec)==false)
		return false;
	if(::Save(f,CountOfConnectedPC)==false)
		return false;
	if(::Save(f,OffsetXForSync)==false)
		return false;
	if(::Save(f,OffsetYForSync)==false)
		return false;
	return true;
}
bool	IntegrationSlave::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,MachineCode)==false)
		return false;
	if(Ver>=4){
		if(::Load(f,SlaveIsInMaster)==false)
			return false;
	}

	if(Ver>=3){
		if(::Load(f,Dependent)==false)
			return false;
	}
	else{
		Dependent=false;
	}
	if(::Load(f,SlaveAddress)==false)
		return false;
	if(::Load(f,ImageFolders)==false)
		return false;
	if(::Load(f,SharedFolder)==false)
		return false;
	if(::Load(f,MinAdditionalSec)==false)
		return false;
	if(::Load(f,MaxAdditionalSec)==false)
		return false;
	if(::Load(f,CountOfConnectedPC)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,OffsetXForSync)==false)
			return false;
		if(::Load(f,OffsetYForSync)==false)
			return false;
	}
	return true;
}

ParamIntegrationMaster::ParamIntegrationMaster(LayersBase *base)
:ServiceForLayers(base)
{
	IntegrationPortNo				=23210;
	IntegrationPageDirectlyPortNo	=24210;
	AllocateMasterBuff				=true;
	AllocateTargetBuff				=true;
	EnabeToLoadMasterImage			=false;
	Mastered						=true;
	OwnSlaveNo						=-1;
	SlaveSubNo						=0;
	MasterIPAddress					=/**/"localhost";
	SharedFolderForSlaveIntegration	=/**/"C:\\SharedForIntegration";
	WaitMilisecToConnectByLAN		=100;
	RunningTimeFileName				=/**/"RunningTime.tbl";
	IntegrationSlaveMode			=false;
	UseSystemResultStocker			=false;

	SetParam(&IntegrationPortNo				, /**/"Master"		,/**/"IntegrationPortNo"			,"Port number for Integration"	,0,65535);
	SetParam(&IntegrationPageDirectlyPortNo	, /**/"Master"		,/**/"IntegrationPageDirectlyPortNo","Port number for IntegrationPageDirectly"	,0,65535);
	SetParam(&AllocateMasterBuff			, /**/"Master"		,/**/"AllocateMasterBuff"			,"Allocate Master buffer");
	SetParam(&AllocateTargetBuff			, /**/"Master"		,/**/"AllocateTargetBuff"			,"Allocate Target buffer");
	SetParam(&EnabeToLoadMasterImage		, /**/"Master"		,/**/"EnabeToLoadMasterImage"		,"When master-image is loaded, this is checked");
	SetParam(&RunningTimeFileName			, /**/"Master"		,/**/"RunningTimeFileName"			,"Running time table file name");
	SetParam(&IntegrationSlaveMode			, /**/"Master"		,/**/"IntegrationSlaveMode"			,"Integration with slave system");
	SetParam(&UseSystemResultStocker		, /**/"Master"		,/**/"UseSystemResultStocker"		,"Use SystemResultStocker in integration master");

	SetParam(&Mastered						, /**/"Connection"	,/**/"Mastered"						,"Integration master");
	SetParam(&OwnSlaveNo					, /**/"Connection"	,/**/"OwnSlaveNo"					,"Own slave number (-1 : not use Integration)",-1,65535);
	SetParam(&SlaveSubNo					, /**/"Connection"	,/**/"SlaveSubNo"					,"0:Primary slave number. 1-:Secondary",-1,65535);
	SetParam(&MasterIPAddress				, /**/"Connection"	,/**/"MasterIPAddress"				,"IP address for integration-master for slave");
	SetParam(&WaitMilisecToConnectByLAN		, /**/"Connection"	,/**/"WaitMilisecToConnectByLAN"	,"Waiting time (ms) to connect by LAN");

	SetParam(&SharedFolderForSlaveIntegration,/**/"Sharing"		,/**/"SharedFolderForSlaveIntegration"	,"Shared folder for slave Integration",0);
}

ParamIntegrationMaster::~ParamIntegrationMaster(void)
{
}

QString	ParamIntegrationMaster::GetSlaveSharedPath(int SlaveNo)
{
	IntegrationSlave	*Slave=Slaves[SlaveNo];
	if(Slave!=NULL){
		return Slave->SharedFolder;
	}
	return /**/"";
}

bool	ParamIntegrationMaster::SaveParam(QIODevice *f ,int EnableCondition)
{
	if(ParamBase::SaveParam(f,EnableCondition)==false)
		return false;
	if(Slaves.Save(f)==false)
		return false;
	return true;
}

bool	ParamIntegrationMaster::LoadParam(QIODevice *f ,int EnableCondition)
{
	if(ParamBase::LoadParam(f,EnableCondition)==false)
		return false;
	if(Slaves.Load(f)==false)
		return false;
	return true;
}

QString	ParamIntegrationMaster::GetDefaultFileName(void)
{
	if(GetParamGlobal()!=NULL){
		return GetParamGlobal()->IntegrationParamFileName;
	}
	return(/**/"ParamIntegrationMaster.dat");
}