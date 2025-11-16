/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XResultDLLManager.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <cmath>
#include "XResultDLLManager.h"
#include "XResultInterfaceDLL.h"
#include "XDLLType.h"
#include "XGeneralFunc.h"
#include "XErrorCode.h"
#include "XDataInLayer.h"
#include "XLotInformation.h"

ResultInterfaceDLL::ResultInterfaceDLL(LayersBase *Base)
:ServiceForLayers(Base)
{
	Ver	=1;

	DLL_GetOrganization		=NULL;
	DLL_GetDLLType			=NULL;
	DLL_GetName				=NULL;
	DLL_GetVersion			=NULL;
	DLL_GetExplain			=NULL;
	DLL_CheckCopyright		=NULL;
	DLL_AssociateComponent	=NULL;
	DLL_GetParamName		=NULL;
	DLL_SetLanguage			=NULL;

	DLL_Initial				=NULL;
	DLL_Release				=NULL;

	DLL_OutputResultCommon	=NULL;
	DLL_OutputResultSlave	=NULL;
	DLL_OutputResultDirectly=NULL;
	DLL_InputResult			=NULL;
	DLLPoint				=NULL;
	DLL_RemoveResult		=NULL;
	DLL_GetLastInspectionID	=NULL;

	DLL_OutputInLotChangedCommon	=NULL;
	DLL_OutputInLotChangedSlave		=NULL;
	DLL_SearchLotID					=NULL;
	DLL_CheckConnection				=NULL;

	DLLPoint=NULL;
	DLL_RegistMacroFunction			=NULL;

	DLL_ExecuteInitialAfterEdit		=NULL;
	DLL_ExecuteStartByInspection	=NULL;
	DLL_ExecuteCaptured				=NULL;
	DLL_ExecutePreAlignment			=NULL;
	DLL_ExecuteAlignment			=NULL;
	DLL_ExecutePreProcessing		=NULL;
	DLL_ExecuteProcessing			=NULL;
	DLL_ExecuteProcessingRevived	=NULL;
	DLL_ExecutePostProcessing		=NULL;
	DLL_ExecutePreScanning			=NULL;
	DLL_ExecuteScanning				=NULL;
	DLL_ExecutePostScanning			=NULL;
	DLL_ExecuteManageResult			=NULL;
}
ResultInterfaceDLL::ResultInterfaceDLL(const ResultInterfaceDLL &src)
	:ServiceForLayers((LayersBase *)src.GetLayersBase())
{
	if(src.DllLib.isLoaded()==true){
		LoadDLL(src.DllLib.fileName());
		Initial();
	}
}
ResultInterfaceDLL::~ResultInterfaceDLL(void)
{
	if(ReEntrantDLL==true)
		return;
	ReEntrantDLL=true;

	Release();
	if(DllLib.isLoaded()==true){
		DllLib.unload();
	}
	ReEntrantDLL=false;
}
bool		ResultInterfaceDLL::Release(void)
{
	if(DLL_Release!=NULL && DLLPoint!=NULL){
		DLL_Release(DLLPoint);
		DLLPoint=NULL;
	}
	return true;
}

ResultInterfaceDLL	&ResultInterfaceDLL::operator=(ResultInterfaceDLL &src)
{
	GetLayersBase()->TestLoadDLL(src.DllLib.fileName());
	if(LoadDLL(src.DllLib.fileName())==true){
		Initial();
	}
	return *this;
}

bool	ResultInterfaceDLL::LoadDLL(const QString &filename)
{
	DllLib.setFileName(filename);
	if(DllLib.load()==false){
		return(false);
	}
	DLL_GetDLLType				=(WORD (*)(void))DllLib.resolve("DLL_GetDLLType");
	DLL_GetOrganization			=(bool (*)(QString &))DllLib.resolve("DLL_GetOrganization");
	DLL_GetName					=(bool (*)(QString &Root ,QString &Name))DllLib.resolve("DLL_GetName");
	DLL_GetVersion				=(WORD (*)(void))DllLib.resolve("DLL_GetVersion");
	DLL_AssociateComponent		=(void (*)(LayersBase *Base,ComponentListContainer &List))DllLib.resolve(/**/"DLL_AssociateComponent");

	if(DLLManager::LoadDLL(DllLib)==false){
		return false;
	}
	DLL_SetLanguage				=(void (*)(LanguagePackage &Pkg ,int LanguageCode))DllLib.resolve(/**/"DLL_SetLanguage");

	DLL_GetExplain				=(const char *(*)(void))DllLib.resolve("DLL_GetExplain");
	DLL_CheckCopyright			=(bool (*)(QString &CopyrightString))DllLib.resolve("DLL_CheckCopyright");
	DLL_GetParamName			=(const char *(*)(void))DllLib.resolve("DLL_GetParamName");
	
	DLL_Initial					=(ResultDLLBaseRoot *(*)(LayersBase *Base))DllLib.resolve("DLL_Initial");
	DLL_Release					=(void (*)(ResultDLLBaseRoot *))DllLib.resolve("DLL_Release");

	DLL_OutputResultCommon		=(bool (*)(ResultDLLBaseRoot *handle
										,ResultInspection *RBase 
										,ResultInspectionForStockPointerContainer &ShadowResStocks
										,EntryPointBase &entryPoint))DllLib.resolve("DLL_OutputResultCommon");
	DLL_OutputResultSlave		=(bool (*)(ResultDLLBaseRoot *handle
											,ResultInspectionForStockPointerContainer &ShadowResStocks
											,int32 MachineID 
											,const XDateTime &InspectedTime 
											,ResultInspection *RBase 
											,const QString &LotID
											,int phase
											,int localPage 
											,EntryPointBase &entryPoint))DllLib.resolve("DLL_OutputResultSlave");
	DLL_OutputResultDirectly	=(bool (*)(ResultDLLBaseRoot *handle
											,int mode ,ResultInspection *RBase 
											,GUIDirectMessage *packet
											,EntryPointBase &entryPoint))DllLib.resolve("DLL_OutputResultDirectly");
	DLL_InputResult				=(bool (*)(ResultDLLBaseRoot *handle
											,ResultBaseForAlgorithm * ,EntryPointBase &))DllLib.resolve("DLL_InputResult");
	DLL_RemoveResult			=(bool (*)(ResultDLLBaseRoot *handle
											,int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID))DllLib.resolve("DLL_RemoveResult");
	DLL_GetLastInspectionID		=(bool (*)(ResultDLLBaseRoot *handle
											,int MasterID ,QString LotID ,int64 &InspectionID))DllLib.resolve("DLL_GetLastInspectionID");

	DLL_OutputInLotChangedCommon=(bool (*)(ResultDLLBaseRoot *handle
											,EntryPointBase &entryPoint))DllLib.resolve("DLL_OutputInLotChangedCommon");
	DLL_OutputInLotChangedSlave =(bool (*)(ResultDLLBaseRoot *handle
											,EntryPointBase &entryPoint,int LocalPage))DllLib.resolve("DLL_OutputInLotChangedSlave");

	DLL_SearchLotID				=(bool (*)(ResultDLLBaseRoot *handle
											,const QString &iLotID))DllLib.resolve("DLL_SearchLotID");
	DLL_CheckConnection			=(bool (*)(ResultDLLBaseRoot *handle))DllLib.resolve("DLL_CheckConnection");
	DLL_RegistMacroFunction		=(int32	(*)(ResultDLLBaseRoot *handle
											,ExportFuncForMacro Functions[],int MaxBuffer))DllLib.resolve("DLL_RegistMacroFunction");

	DLL_ExecuteInitialAfterEdit		=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteInitialAfterEdit");
	DLL_ExecuteStartByInspection	=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteStartByInspection");
	DLL_ExecuteCaptured				=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res ,ListPhasePageLayerPack &CapturedList))DllLib.resolve("ExecuteCaptured");
	DLL_ExecutePreAlignment			=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecutePreAlignment");
	DLL_ExecuteAlignment			=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteAlignment");
	DLL_ExecutePreProcessing		=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecutePreProcessing");
	DLL_ExecuteProcessing			=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteProcessing");
	DLL_ExecuteProcessingRevived	=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteProcessingRevived");
	DLL_ExecutePostProcessing		=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecutePostProcessing");
	DLL_ExecutePreScanning			=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecutePreScanning");
	DLL_ExecuteScanning				=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteScanning");
	DLL_ExecutePostScanning			=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecutePostScanning");
	DLL_ExecuteManageResult			=(ExeResult	(*)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res))DllLib.resolve("DLL_ExecuteManageResult");

	return(true);
}

bool	ResultInterfaceDLL::IsResultDLL(void)	const
{
	if(DLL_GetDLLType!=NULL){
		int	d=DLL_GetDLLType();
		if((d&DLLModeMask)==DLLResultMode){
			return(true);
		}
	}
	return(false);
}
bool	ResultInterfaceDLL::Initial(void)
{
	if(DLL_CheckCopyright!=NULL){
		if(DLL_CheckCopyright(Copyright)==false){
			return false;
		}
	}
	if(DLL_GetVersion!=NULL){
		Ver=DLL_GetVersion();
	}
	if(DLL_GetName!=NULL){
		DLL_GetName(DLLRoot,DLLName);
	}
	if(DLL_GetOrganization!=NULL){
		DLL_GetOrganization(Organization);
	}

	if(DLL_SetLanguage!=NULL){
		DLL_SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
	}

	if(DLL_Initial!=NULL){
		if(DLLPoint!=NULL){
			delete	DLLPoint;
		}
		DLLPoint=DLL_Initial(GetLayersBase());
		if(DLLPoint==NULL){
			return false;
		}
	}
	if(DLL_GetParamName!=NULL){
		ParamFileName=QString(DLL_GetParamName());
	}
	if(DLLPoint!=NULL && ParamFileName.isEmpty()==false){
		QFile	PFile(ParamFileName);
		if(PFile.open(QIODevice::ReadOnly)==true){
			DLLPoint->LoadParam(&PFile);
		}
	}
	return(true);
}
WORD	ResultInterfaceDLL::GetDLLType(void)	const
{
	if(DLL_GetDLLType!=NULL){
		return DLL_GetDLLType();
	}
	return 0;
}
void	ResultInterfaceDLL::AssociateComponent	(ComponentListContainer &List)
{
	if(DLL_AssociateComponent!=NULL){
		DLL_AssociateComponent(GetLayersBase(),List);
	}
}

const QString	ResultInterfaceDLL::GetExplain(void)	const
{
	if(DLL_GetExplain!=NULL){
		const char	*c=DLL_GetExplain();
		if(c!=NULL){
			return QString::fromLocal8Bit(c);
		}
	}
	return /**/"";
}

bool	ResultInterfaceDLL::SearchLotID(const QString &iLotID)
{
	if(DLL_SearchLotID!=NULL){
		return DLL_SearchLotID(DLLPoint,iLotID);
	}
	return false;
}

bool	ResultInterfaceDLL::CheckSystemVersion(QStringList &Str)
{
	return CheckSystemVersionFunc(Str ,"ResultDLL",DLLRoot,DLLName);
}

void	ResultInterfaceDLL::Prepare(void)
{
	GetDLLPoint()->Prepare();
}

int64	ResultInterfaceDLL::OutputResultCommon(ResultInspection *RBase 
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,EntryPointBase &entryPoint)
{
	if(DLL_OutputResultCommon!=NULL){
		return DLL_OutputResultCommon(DLLPoint,RBase ,ShadowResStocks,entryPoint);
	}
	return -1;
}
bool	ResultInterfaceDLL::OutputResultSlave (ResultInspectionForStockPointerContainer &ShadowResStocks
									,int32 MachineID 
									,const XDateTime &InspectedTime 
									,ResultInspection *RBase 
									,const QString &LotID
									,int phase
									,int localPage 
									,EntryPointBase &entryPoint)
{
	if(DLL_OutputResultSlave!=NULL){
		return DLL_OutputResultSlave(DLLPoint
									,ShadowResStocks
									,MachineID ,InspectedTime ,RBase 
									,LotID
									,phase,localPage ,entryPoint);
	}
	return false;
}

int64	ResultInterfaceDLL::OutputResultDirectly(int mode,ResultInspection *RBase 
												,GUIDirectMessage *packet
												,EntryPointBase &entryPoint)
{
	if(DLL_OutputResultDirectly!=NULL){
		return DLL_OutputResultDirectly(DLLPoint,mode ,RBase ,packet,entryPoint);
	}
	return -1;
}
bool	ResultInterfaceDLL::RemoveResult(int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID)
{
	if(DLL_RemoveResult!=NULL){
		return DLL_RemoveResult(DLLPoint,MachineID ,ResultTime ,InspectionID);
	}
	return false;
}

bool	ResultInterfaceDLL::GetLastInspectionID(int MasterID ,const QString &LotID ,int64 &InspectionID)
{
	if(DLL_GetLastInspectionID!=NULL){
		return DLL_GetLastInspectionID(DLLPoint,MasterID ,LotID ,InspectionID);
	}
	InspectionID=GetLayersBase()->GetParamGlobal()->TopOfID;
	return false;
}

bool	ResultInterfaceDLL::OutputInLotChangedCommon(EntryPointBase &entryPoint)
{
	if(DLL_OutputInLotChangedCommon!=NULL){
		return DLL_OutputInLotChangedCommon(DLLPoint,entryPoint);
	}
	return false;
}

bool	ResultInterfaceDLL::OutputInLotChangedSlave (EntryPointBase &entryPoint ,int LocalPage)
{
	if(DLL_OutputInLotChangedSlave!=NULL){
		return DLL_OutputInLotChangedSlave(DLLPoint,entryPoint ,LocalPage);
	}
	return false;
}

bool		ResultInterfaceDLL::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	if(DLLPoint!=NULL){
		return DLLPoint->MakeExecuteInitialAfterEditInfo	(ExeID ,Res,EInfo);
	}
	return false;
}

ExeResult	ResultInterfaceDLL::ExecuteInitialAfterEdit	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteInitialAfterEdit!=NULL){
		return DLL_ExecuteInitialAfterEdit(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteStartByInspection	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteStartByInspection!=NULL){
		return DLL_ExecuteStartByInspection(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteCaptured	(int ExeID ,ResultInspection *Res ,ListPhasePageLayerPack &CapturedList)
{
	if(DLL_ExecuteCaptured!=NULL){
		return DLL_ExecuteCaptured(ExeID,DLLPoint,Res,CapturedList);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecutePreAlignment		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreAlignment!=NULL){
		return DLL_ExecutePreAlignment(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteAlignment			(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteAlignment!=NULL){
		return DLL_ExecuteAlignment(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecutePreProcessing		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreProcessing!=NULL){
		return DLL_ExecutePreProcessing(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteProcessing		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteProcessing!=NULL){
		return DLL_ExecuteProcessing(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteProcessingRevived	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteProcessingRevived!=NULL){
		return DLL_ExecuteProcessingRevived(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecutePostProcessing	(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePostProcessing!=NULL){
		return DLL_ExecutePostProcessing(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecutePreScanning		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePreScanning!=NULL){
		return DLL_ExecutePreScanning(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteScanning			(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteScanning!=NULL){
		return DLL_ExecuteScanning(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecutePostScanning		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecutePostScanning!=NULL){
		return DLL_ExecutePostScanning(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}
ExeResult	ResultInterfaceDLL::ExecuteManageResult		(int ExeID ,ResultInspection *Res)
{
	if(DLL_ExecuteManageResult!=NULL){
		return DLL_ExecuteManageResult(ExeID,DLLPoint,Res);
	}
	return _ER_NoFunc;
}

bool	ResultInterfaceDLL::CheckConnection(void)
{
	if(DLL_CheckConnection!=NULL){
		return DLL_CheckConnection(DLLPoint);
	}
	return true;
}

void	ResultInterfaceDLL::GetExportFunctions(QStringList &Str)
{
	if(DLL_GetOrganization!=NULL){
		Str.append("DLL_GetOrganization");
	}
	if(DLL_GetDLLType!=NULL){
		Str.append("DLL_GetDLLType");
	}
	if(DLL_GetName!=NULL){
		Str.append("DLL_GetName");
	}
	if(DLL_GetVersion!=NULL){
		Str.append("DLL_GetVersion");
	}
	if(DLL_AssociateComponent!=NULL){
		Str.append("DLL_AssociateComponent");
	}
	if(DLL_SetLanguage!=NULL){
		Str.append("DLL_SetLanguage");
	}
	if(DLL_GetExplain!=NULL){
		Str.append("DLL_GetExplain");
	}
	if(DLL_CheckCopyright!=NULL){
		Str.append("DLL_CheckCopyright");
	}
	if(DLL_GetParamName!=NULL){
		Str.append("DLL_GetParamName");
	}
	if(DLL_Initial!=NULL){
		Str.append("DLL_Initial");
	}
	if(DLL_Release!=NULL){
		Str.append("DLL_Release");
	}
	if(DLL_OutputResultCommon!=NULL){
		Str.append("DLL_OutputResultCommon");
	}
	if(DLL_OutputResultSlave!=NULL){
		Str.append("DLL_OutputResultSlave");
	}
	if(DLL_OutputResultDirectly!=NULL){
		Str.append("DLL_OutputResultDirectly");
	}
	if(DLL_InputResult!=NULL){
		Str.append("DLL_InputResult");
	}
	if(DLL_RemoveResult!=NULL){
		Str.append("DLL_RemoveResult");
	}
	if(DLL_GetLastInspectionID!=NULL){
		Str.append("DLL_GetLastInspectionID");
	}
	if(DLL_OutputInLotChangedCommon!=NULL){
		Str.append("DLL_OutputInLotChangedCommon");
	}
	if(DLL_OutputInLotChangedSlave!=NULL){
		Str.append("DLL_OutputInLotChangedSlave");
	}
	if(DLL_SearchLotID!=NULL){
		Str.append("DLL_SearchLotID");
	}
	if(DLL_CheckConnection!=NULL){
		Str.append("DLL_CheckConnection");
	}
	if(DLL_RegistMacroFunction!=NULL){
		Str.append("DLL_RegistMacroFunction");
	}
	if(DLL_ExecuteInitialAfterEdit!=NULL){
		Str.append("DLL_ExecuteInitialAfterEdit");
	}
	if(DLL_ExecuteStartByInspection!=NULL){
		Str.append("DLL_ExecuteStartByInspection");
	}
	if(DLL_ExecutePreAlignment!=NULL){
		Str.append("DLL_ExecutePreAlignment");
	}
	if(DLL_ExecuteCaptured!=NULL){
		Str.append("DLL_ExecuteCaptured");
	}
	if(DLL_ExecuteAlignment!=NULL){
		Str.append("DLL_ExecuteAlignment");
	}
	if(DLL_ExecutePreProcessing!=NULL){
		Str.append("DLL_ExecutePreProcessing");
	}
	if(DLL_ExecuteProcessing!=NULL){
		Str.append("DLL_ExecuteProcessing");
	}
	if(DLL_ExecuteProcessingRevived!=NULL){
		Str.append("DLL_ExecuteProcessingRevived");
	}
	if(DLL_ExecutePostProcessing!=NULL){
		Str.append("DLL_ExecutePostProcessing");
	}
	if(DLL_ExecutePreScanning!=NULL){
		Str.append("DLL_ExecutePreScanning");
	}
	if(DLL_ExecuteScanning!=NULL){
		Str.append("DLL_ExecuteScanning");
	}
	if(DLL_ExecutePostScanning!=NULL){
		Str.append("DLL_ExecutePostScanning");
	}
	if(DLL_ExecuteManageResult!=NULL){
		Str.append("DLL_ExecuteManageResult");
	}

	DLLManager::GetExportFunctions(Str);
}
int		ResultInterfaceDLL::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	if(DLL_RegistMacroFunction!=NULL){
		return DLL_RegistMacroFunction(DLLPoint,Functions,MaxBuffer);
	}
	return 0;
}

//=========================================================================================================================
ResultDLL::ResultDLL(LayersBase *Base)
	:ServiceForLayers(Base) ,Interface(new ResultInterfaceDLL(Base))
{
}
ResultDLL::ResultDLL(const ResultDLL &src)
	:ServiceForLayers(src.GetLayersBase()) ,Interface(new ResultInterfaceDLL(*((ResultDLL *)&src)->GetInterface()))
{
}
ResultDLL::~ResultDLL(void)
{
	delete	Interface;
	Interface=NULL;
}
void	ResultDLL::AssociateComponent	(ComponentListContainer &List)
{
	if(Interface!=NULL){
		Interface->AssociateComponent	(List);
	}
}
ResultDLL	&ResultDLL::operator=(const ResultDLL &src)
{
	if(Interface!=NULL){
		Interface->operator=(*((ResultDLL *)&src)->GetInterface());
	}
	return *this;
}
bool		ResultDLL::LoadDLL(const QString &filename)
{
	return Interface->LoadDLL(filename);
}
bool		ResultDLL::IsResultDLL(void)
{
	return Interface->IsResultDLL();
}
bool		ResultDLL::Initial(void)
{
	return Interface->Initial();
}
bool		ResultDLL::Release(void)
{
	return Interface->Release();
}
bool		ResultDLL::CheckSystemVersion(QStringList &Str)
{
	return Interface->CheckSystemVersion(Str);
}
void		ResultDLL::Prepare(void)
{
	Interface->Prepare();
}
int64	ResultDLL::OutputResultCommon(ResultInspection *RBase 
										,ResultInspectionForStockPointerContainer	&ShadowResStocks
										,EntryPointBase &entryPoint)
{
	return Interface->OutputResultCommon(RBase ,ShadowResStocks,entryPoint);
}
bool	ResultDLL::OutputResultSlave (ResultInspectionForStockPointerContainer &ShadowResStocks
							,int32 MachineID 
							,const XDateTime &InspectedTime
							,ResultInspection *RBase 
							,const QString &LotID
							,int phase
							,int localPage 
							,EntryPointBase &entryPoint)
{
	return Interface->OutputResultSlave (ShadowResStocks
							,MachineID 
							,InspectedTime
							,RBase 
							,LotID
							,phase
							,localPage 
							,entryPoint);
}
int64		ResultDLL::OutputResultDirectly(int mode ,ResultInspection *RBase 
											,GUIDirectMessage *packet
											,EntryPointBase &entryPoint)
{
	return Interface->OutputResultDirectly(mode ,RBase ,packet,entryPoint);
}
bool		ResultDLL::RemoveResult(int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID)
{
	return Interface->RemoveResult(MachineID ,ResultTime ,InspectionID);
}
bool		ResultDLL::GetLastInspectionID(int MasterID ,const QString &LotID ,int64 &InspectionID)
{
	return Interface->GetLastInspectionID(MasterID ,LotID ,InspectionID);
}

bool		ResultDLL::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	return Interface->MakeExecuteInitialAfterEditInfo(ExeID ,Res,EInfo);
}

ExeResult	ResultDLL::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteInitialAfterEdit		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteStartByInspection	(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteStartByInspection		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteCaptured		(int ExeID ,ResultInspection *Res ,ListPhasePageLayerPack &CapturedList)
{
	return Interface->ExecuteCaptured	(ExeID ,Res,CapturedList);
}
ExeResult	ResultDLL::ExecutePreAlignment			(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecutePreAlignment		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteAlignment			(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteAlignment		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecutePreProcessing		(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecutePreProcessing		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteProcessing			(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteProcessing		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteProcessingRevived	(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteProcessingRevived		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecutePostProcessing		(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecutePostProcessing		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecutePreScanning			(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecutePreScanning		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteScanning				(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteScanning		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecutePostScanning			(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecutePostScanning		(ExeID ,Res);
}
ExeResult	ResultDLL::ExecuteManageResult			(int ExeID ,ResultInspection *Res)
{
	return Interface->ExecuteManageResult		(ExeID ,Res);
}
bool	ResultDLL::OutputInLotChangedCommon(EntryPointBase &entryPoint)
{
	return Interface->OutputInLotChangedCommon(entryPoint);
}
bool	ResultDLL::OutputInLotChangedSlave (EntryPointBase &entryPoint ,int LocalPage)
{
	return Interface->OutputInLotChangedSlave (entryPoint ,LocalPage);
}
bool	ResultDLL::SearchLotID(const QString &iLotID)
{
	return Interface->SearchLotID(iLotID);
}
bool	ResultDLL::CheckConnection(void)
{
	return Interface->CheckConnection();
}

const QString	&ResultDLL::GetFileName(void)			const	{	return Interface->GetFileName();	}
void			ResultDLL::SetFileName(const QString &s)		{	Interface->SetFileName(s);			}
QString			ResultDLL::GetOrganization(void)		const	{	return Interface->GetOrganization();	}
QString			ResultDLL::GetDLLRoot(void)				const	{	return Interface->GetDLLRoot();		}
QString			ResultDLL::GetDLLName(void)				const	{	return Interface->GetDLLName();		}
QString			ResultDLL::GetParamFileName(void)		const	{	return Interface->GetParamFileName();	}
WORD			ResultDLL::GetVersion(void)				const	{	return Interface->GetVersion();		}
ResultDLLBaseRoot	*ResultDLL::GetDLLPoint(void)		const	{	return Interface->GetDLLPoint();	}
QString			ResultDLL::GetCopyright(void)			const	{	return Interface->GetCopyright();	}
WORD			ResultDLL::GetDLLType(void)				const	{	return Interface->GetDLLType();		}
QString			ResultDLL::GetExplain(void)				const	{	return Interface->GetExplain();		}

void	ResultDLL::GetExportFunctions(QStringList &Str)
{
	Interface->GetExportFunctions(Str);
}
void	ResultDLL::GetMacroNames(QStringList &Str)
{
	Interface->GetMacroNames(Str);
}
int		ResultDLL::RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	return Interface->RegistMacroFunction(Functions,MaxBuffer);
}

//=========================================================================================================================


ResultDLLBaseClass::ResultDLLBaseClass(LayersBase *Base)
:ServiceForLayers(Base)
{
}
void	ResultDLLBaseClass::AssociateComponent	(ComponentListContainer &List)
{
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ComponentListContainer TmpList;
		L->AssociateComponent(TmpList);
		for(ComponentList *L=TmpList.GetFirst();L!=NULL;L=L->GetNext()){
			ComponentList	*Boss;
			for(Boss=List.GetFirst();Boss!=NULL;Boss=Boss->GetNext()){
				if(*Boss==*L){
					break;
				}
			}
			if(Boss==NULL){
				ComponentList	*d=new ComponentList(*L);
				List.AppendList(d);
			}
		}
	}
}

ResultDLLBaseClass	&ResultDLLBaseClass::operator=(const ResultDLLBaseClass &src)
{
	RemoveAll();
	for(ResultDLL *L=src.GetFirst();L!=NULL;L=L->GetNext()){
		ResultDLL *M=new ResultDLL(GetLayersBase());
		*M=*L;
		AppendList(M);
	}
	return *this;
}

bool	ResultDLLBaseClass::UnSavedResult(void)
{
	ResultDLL	*L=GetFirst();
	if(L==NULL || L->GetDLLPoint()==NULL){
		return true;
	}
	return L->GetDLLPoint()->NotSaved;
}

int	ResultDLLBaseClass::SearchAddDLL(const QString &path)
{
	QDir	Dir;

	char	buff[200];
	QString2Char(path,buff,sizeof(buff));
	printf("%s\n",buff);

	int	N=0;
	if(Dir.cd(path)==true){
		QString	SearchFile=QString("*.")+GetDynamicFileExt();
		QStringList nameFilters(SearchFile);
		QStringList List=Dir.entryList ( nameFilters, QDir::Files, QDir::NoSort );
		for(int i=0;i<List.size();i++){
			QString	FileName=path+QString(GetSeparator())+List.at(i);
			GetLayersBase()->TestLoadDLL(FileName);
			if(QLibrary::isLibrary(FileName)==true){
				ResultDLL	*DLL=new ResultDLL(GetLayersBase());
				DLL->SetFileName(FileName);
				printf("ResultDLL\n");
				if(DLL->LoadDLL(FileName)==true){
					printf("LoadDLL OK\n");
					if(DLL->IsResultDLL()==true){
						printf("Initialc\n");
						DLL->Initial();

						printf("AppendList\n");
						AppendList(DLL);
						if(GetLayersBase()!=NULL){
							GetLayersBase()->InformToLoadDLL(FileName);
						}
						N++;
					}
					else{
						delete	DLL;
					}
				}
				else{
					delete	DLL;
				}
			}
		}
	}
	/*
	QStringList DirFilters("*");
	List=Dir.entryList ( DirFilters, QDir::Dirs | QDir::NoDotAndDotDot, QDir::NoSort );
	for(int i=0;i<List.size();i++){
		QString	s=path+QString(GetSeparator())+List.at(i);
		SearchAddDLL(PInspectionData,s);
	}
	*/
	return(N);
}

int		ResultDLLBaseClass::LoadDLL(const QString &FileNames,bool ShowInWindow)
{
	QStringList	DLLFiles=GetParamGlobal()->ResultDLLFileName.split(QChar(';'));
	int	N=0;
	for(int i=0;i<DLLFiles.count();i++){
		QString	FileName=GetLayersBase()->GetSystemPath()+GetSeparator() +DLLFiles[i];

		if(ShowInWindow==true){
			GetLayersBase()->TestLoadDLL(FileName);
		}
		if(QLibrary::isLibrary(FileName)==true){
			ResultDLL	*DLL=new ResultDLL(GetLayersBase());
			DLL->SetFileName(FileName);
			printf("ResultDLL\n");
			if(DLL->LoadDLL(FileName)==true){
				printf("LoadDLL OK\n");
				if(DLL->IsResultDLL()==true){
					printf("Initialc\n");
					DLL->Initial();

					printf("AppendList\n");
					AppendList(DLL);
					if(GetLayersBase()!=NULL){
						if(ShowInWindow==true){
							GetLayersBase()->InformToLoadDLL(FileName);
						}
					}
					N++;
				}
				else{
					delete	DLL;
				}
			}
			else{
				delete	DLL;
			}
		}
	}
	return N;
}

bool	ResultDLLBaseClass::Release(void)
{
	bool	Ret=true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->Release()==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	ResultDLLBaseClass::CheckSystemVersion(QStringList &Str)
{
	bool	Ret=true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckSystemVersion(Str)==false){
			Ret=false;
		}
	}
	return Ret;
}

void	ResultDLLBaseClass::Prepare(void)
{
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		L->Prepare();
	}
}

bool	ResultDLLBaseClass::SearchLotID(const QString &iLotID)
{
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->SearchLotID(iLotID)==true){
			return true;
		}
	}
	return false;
}

int64	ResultDLLBaseClass::OutputResultCommon(ResultInspection *RBase
											  ,ResultInspectionForStockPointerContainer	&ShadowResStocks)
{
	if(GetParamGlobal()->OutputResult==true){
		Mutex.lock();
		GetLayersBase()->GetLotBase()->ExecuteEveryInspectInMaster(RBase->GetInspectionID());
		bool	ret=true;
		for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->OutputResultCommon(RBase ,ShadowResStocks,*GetLayersBase()->GetEntryPoint())==false){
				ret=false;
			}
		}
		if(ret==true){
			GetLayersBase()->CommandSaveResultToSlave(RBase);
			GetLayersBase()->GetResultHistryData()->SetWritten(  RBase->GetStartTimeForInspection()
																,RBase->GetInspectionID());
		}
		else{
			ErrorCodeList	*e=new ErrorCodeList(ErrorCodeList::_Critical,"Lost Result",Error_ResultServer);
			GetLayersBase()->AddError(e ,0);
		}
		Mutex.unlock();
		return ret;
	}
	else{
		GetLayersBase()->GetResultHistryData()->SetWritten(  RBase->GetStartTimeForInspection()
															,RBase->GetInspectionID());
		return true;
	}
}
bool	ResultDLLBaseClass::OutputResultSlave (ResultInspectionForStockPointerContainer &ShadowResStocks
												,int32 MachineID ,XDateTime &InspectedTime
												,ResultInspection *RBase 
												,const QString &LotID
												,int phase,int localPage)
{
	//RBase->BuildNGImages();
	Mutex.lock();
	GetLayersBase()->GetLotBase()->ExecuteEveryInspectInSlave(RBase->GetInspectionID(),phase,localPage);
	bool	ret=true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->OutputResultSlave(ShadowResStocks
								,MachineID ,InspectedTime ,RBase 
								,LotID
								,phase,localPage ,*GetLayersBase()->GetEntryPoint())==false){
			ret=false;
		}
	}
	Mutex.unlock();
	if(ret==true){
		GetLayersBase()->GetResultHistryData()->SetWritten(InspectedTime);
	}
	return ret;
}

int64	ResultDLLBaseClass::OutputResultDirectly(int mode ,ResultInspection *RBase
												,GUIDirectMessage *packet)
{
	if(GetParamGlobal()->OutputResult==true){
		Mutex.lock();
		GetLayersBase()->GetLotBase()->ExecuteEveryInspectInMaster(RBase->GetInspectionID());
		bool	ret=true;
		for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->OutputResultDirectly(mode ,RBase ,packet,*GetLayersBase()->GetEntryPoint())==false){
				ret=false;
			}
		}
		Mutex.unlock();
		return ret;
	}
	return true;
}
bool	ResultDLLBaseClass::RemoveResult(int32 MachineID ,XDateTime &ResultTime ,int64 InspectionID)
{
	//RBase->BuildNGImages();
	bool	ret=true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->RemoveResult(MachineID ,ResultTime ,InspectionID)==false){
			ret=false;
		}
	}
	if(ret==true){
		GetLayersBase()->GetResultHistryData()->RemoveResult(ResultTime);
	}
	return ret;
}

bool	ResultDLLBaseClass::MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo)
{
	bool	ret=true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->MakeExecuteInitialAfterEditInfo(ExeID ,Res ,EInfo)==false){
			ret=false;
		}
	}
	return ret;
}

ExeResult	ResultDLLBaseClass::ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteInitialAfterEdit(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteStartByInspection	(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteStartByInspection(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteCaptured		(int ExeID ,ResultInspection *Res ,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteCaptured(ExeID ,Res,CapturedList))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecutePreAlignment			(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecutePreAlignment(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteAlignment			(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteAlignment(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecutePreProcessing		(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecutePreProcessing(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteProcessing			(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteProcessing(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteProcessingRevived	(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteProcessingRevived(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecutePostProcessing		(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecutePostProcessing(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecutePreScanning			(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecutePreScanning(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteScanning				(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteScanning(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecutePostScanning			(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecutePostScanning(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}
ExeResult	ResultDLLBaseClass::ExecuteManageResult			(int ExeID ,ResultInspection *Res)
{
	ExeResult	ret=_ER_true;
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		ExeResult	r;
		if((r=L->ExecuteManageResult(ExeID ,Res))!=_ER_true){
			ret=r;
		}
	}
	return ret;
}

bool	ResultDLLBaseClass::GetLastInspectionID(int MasterID ,const QString &LotID ,int64 &InspectionID)
{
	//RBase->BuildNGImages();
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetLastInspectionID(MasterID ,LotID ,InspectionID)==true){
			return true;
		}
	}
	InspectionID=GetLayersBase()->GetParamGlobal()->TopOfID;
	return false;
}


bool	ResultDLLBaseClass::OutputInLotChangedCommon(void)
{
	bool	ret=true;
	if(GetParamGlobal()->OutputResult==true){
		for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->OutputInLotChangedCommon(*GetLayersBase()->GetEntryPoint())==false){
				ret=false;
			}
		}
		GetLayersBase()->CommandOutputInLotChangedToSlave();
	}
	return ret;
}

bool	ResultDLLBaseClass::OutputInLotChangedSlave (int LocalPage)
{
	bool	ret=true;
	if(GetParamGlobal()->OutputResult==true){
		for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
			if(L->OutputInLotChangedSlave(*GetLayersBase()->GetEntryPoint(),LocalPage)==false){
				ret=false;
			}
		}
	}
	return ret;
}
ResultDLL	*ResultDLLBaseClass::GetResultDLL(const QString &DLLRoot ,const QString &DLLName)
{
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->GetDLLRoot()==DLLRoot && L->GetDLLName()==DLLName){
			return L;
		}
	}
	return NULL;
}

bool	ResultDLLBaseClass::CheckConnection(void)
{
	for(ResultDLL *L=GetFirst();L!=NULL;L=L->GetNext()){
		if(L->CheckConnection()==false){
			return false;
		}
	}
	return true;
}
bool	ResultDLLBaseClass::CheckResultDLL(void)
{
	if(IsEmpty()==true)
		return false;
	return true;
}


