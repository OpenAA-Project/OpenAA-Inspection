/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XResultDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XRESULTDLL_H)
#define	XRESULTDLL_H

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XMacroFunction.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif


class	AddedDataClass;
class	ResultBaseForAlgorithm;
class	ResultDLLBase;
class	ResultDLLBaseRoot;
class	LayersBase;
class	LanguagePackage;
class	ResultInspectionForStockPointerContainer;
class	GUIDirectMessage;

extern	"C"{

struct	DllToAppFuncs
{
	void		(*APP_MouseMove)(int gx ,int gy);
};

#ifdef _MSC_VER
DEFFUNCEX	bool			DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD			DLL_GetDLLType(void);
DEFFUNCEX	bool			DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	WORD			DLL_GetVersion(void);
DEFFUNCEX	const char		*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void			DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	void			DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	const char		*DLL_GetExplain(void);
DEFFUNCEX	bool			DLL_CheckCopyright(QString &CopyrightString);
DEFFUNCEX	const	char	*DLL_GetParamName(void);
DEFFUNCEX	ResultDLLBaseRoot	*DLL_Initial(LayersBase *Base);
DEFFUNCEX	bool			DLL_Release(ResultDLLBaseRoot *handle);

DEFFUNCEX	bool		DLL_OutputResultCommon(ResultDLLBaseRoot *ResultPointer
												,ResultInspection *RBase 
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,EntryPointBase &entryPoint);
DEFFUNCEX	bool		DLL_OutputResultSlave (ResultDLLBaseRoot *ResultPointer
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,int32 MachineID ,const XDateTime &InspectedTime
												,ResultInspection *RBase 
												,const QString &LotID
												,int phase
												,int localPage 
												,EntryPointBase &entryPoint);
DEFFUNCEX	bool		DLL_OutputResultDirectly(ResultDLLBaseRoot *ResultPointer
												,int mode ,ResultInspection *RBase 
												,GUIDirectMessage *packet
												,EntryPointBase &entryPoint);

DEFFUNCEX	bool		DLL_OutputInLotChangedCommon(ResultDLLBaseRoot *ResultPointer
													,EntryPointBase &entryPoint);
DEFFUNCEX	bool		DLL_OutputInLotChangedSlave (ResultDLLBaseRoot *ResultPointer
													,EntryPointBase &entryPoint ,int LocalPage);

DEFFUNCEX	bool			DLL_InputResult(ResultDLLBaseRoot *ResultPointer
												,ResultBaseForAlgorithm *RBase ,EntryPointBase &entryPoint);
DEFFUNCEX	bool			DLL_RemoveResult(ResultDLLBaseRoot *ResultPointer
												,int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID);
DEFFUNCEX	bool			DLL_GetLastInspectionID(ResultDLLBaseRoot *ResultPointer
												,int MasterID ,QString LotID ,int64 &InspectionID);
DEFFUNCEX	bool			DLL_SearchLotID(ResultDLLBaseRoot *ResultPointer
												,const QString &iLotID);
DEFFUNCEX	bool			DLL_CheckConnection(ResultDLLBaseRoot *ResultPointer);
DEFFUNCEX	int32			DLL_RegistMacroFunction(ResultDLLBaseRoot *ResultPointer
												,ExportFuncForMacro Functions[],int MaxBuffer);

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEdit		(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspection	(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignment			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignment			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessing		(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessing			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevived	(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessing		(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreScanning			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteScanning				(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostScanning			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteManageResult			(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);

#endif

};

#endif
