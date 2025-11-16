/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XResultInterfaceDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XRESULTINTERFACEDLLH
#define XRESULTINTERFACEDLLH

#include "XTypeDef.h"
#include "NList.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XResult.h"
#include "XServiceForLayers.h"
#include "XDLLManager.h"
#include "XMacroFunction.h"
#include <QMutex>

class	ResultDLLBaseRoot;
class	ResultInspectionForStockPointerContainer;
class	ExecuteInitialAfterEditInfo;

class	ResultInterfaceDLL : public DLLManager,public ServiceForLayers ,public DLLMacroFunc
{
	QLibrary 		DllLib;
protected:
	bool			(*DLL_GetOrganization)(QString &str);
	WORD			(*DLL_GetDLLType)(void);
	bool			(*DLL_GetName)(QString &Root ,QString &Name);
	WORD			(*DLL_GetVersion)(void);
	void			(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	const char		*(*DLL_GetExplain)(void);
	bool			(*DLL_CheckCopyright)(QString &CopyrightString);
	void			(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);

	const	char	*(*DLL_GetParamName)(void);

	ResultDLLBaseRoot *(*DLL_Initial)(LayersBase *Base);
	void			(*DLL_Release)(ResultDLLBaseRoot *Handle);

	bool			(*DLL_OutputResultCommon)(ResultDLLBaseRoot	*handle
												,ResultInspection *RBase 
												,ResultInspectionForStockPointerContainer &ShadowResStocks
												,EntryPointBase &entryPoint);
	bool			(*DLL_OutputResultSlave )(ResultDLLBaseRoot	*handle
											,ResultInspectionForStockPointerContainer &ShadowResStocks
											,int32 MachineID 
											,const XDateTime &InspectedTime 
											,ResultInspection *RBase 
											,const QString &LotID
											,int phase
											,int localPage ,EntryPointBase &entryPoint);
	bool			(*DLL_OutputResultDirectly)(ResultDLLBaseRoot	*handle
												,int mode ,ResultInspection *RBase 
												,GUIDirectMessage *packet
												,EntryPointBase &entryPoint);

	bool			(*DLL_InputResult)(ResultDLLBaseRoot *handle
										,ResultBaseForAlgorithm *RBase ,EntryPointBase &entryPoint);
	bool			(*DLL_RemoveResult)(ResultDLLBaseRoot *handle
										,int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID);
	bool			(*DLL_GetLastInspectionID)(ResultDLLBaseRoot *handle
												,int MasterID ,QString LotID ,int64 &InspectionID);

	bool			(*DLL_OutputInLotChangedCommon)(ResultDLLBaseRoot *handle
													,EntryPointBase &entryPoint);
	bool			(*DLL_OutputInLotChangedSlave )(ResultDLLBaseRoot *handle
													,EntryPointBase &entryPoint ,int LocalPage);

	bool			(*DLL_SearchLotID)(ResultDLLBaseRoot *handle
										,const QString &iLotID);
	bool			(*DLL_CheckConnection)(ResultDLLBaseRoot *handle);
	int32			(*DLL_RegistMacroFunction)(ResultDLLBaseRoot *handle
												,ExportFuncForMacro Functions[],int MaxBuffer);

	ExeResult	(*DLL_ExecuteInitialAfterEdit	)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteStartByInspection	)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteCaptured			)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res ,ListPhasePageLayerPack &CapturedList);
	ExeResult	(*DLL_ExecutePreAlignment		)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteAlignment			)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePreProcessing		)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteProcessing			)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteProcessingRevived	)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePostProcessing		)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePreScanning		)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteScanning			)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePostScanning		)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteManageResult		)(int ExeID ,ResultDLLBaseRoot *inst,ResultInspection *Res);


	QString			FileName;
	QString			Organization;
	QString			DLLRoot;
	QString			DLLName;
	QString			ParamFileName;
	WORD			Ver;
	ResultDLLBaseRoot	*DLLPoint;
	QString			Copyright;

public:
	explicit	ResultInterfaceDLL(LayersBase *Base);
	ResultInterfaceDLL(const ResultInterfaceDLL &src);
	~ResultInterfaceDLL(void);

	ResultInterfaceDLL	&operator=(ResultInterfaceDLL &src);
	bool		LoadDLL(const QString &filename);
	bool		IsResultDLL(void)	const;
	bool		Initial(void);
	bool		Release(void);
	bool		CheckSystemVersion(QStringList &Str);
	void		AssociateComponent	(ComponentListContainer &List);

	void		Prepare(void);

	int64	OutputResultCommon(ResultInspection *RBase 
								,ResultInspectionForStockPointerContainer	&ShadowResStocks
								,EntryPointBase &entryPoint);
	bool	OutputResultSlave (ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID 
								,const XDateTime &InspectedTime
								,ResultInspection *RBase 
								,const QString &LotID
								,int phase
								,int localPage 
								,EntryPointBase &entryPoint);
	int64	OutputResultDirectly(int mode ,ResultInspection *RBase 
								,GUIDirectMessage *packet
								,EntryPointBase &entryPoint);
	bool	RemoveResult(int32 MachineID ,const XDateTime &ResultTime ,int64 InspectionID);
	bool	GetLastInspectionID(int MasterID ,const QString &LotID ,int64 &InspectionID);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteStartByInspection	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteCaptured				(int ExeID ,ResultInspection *Res ,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignment			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteAlignment			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreProcessing		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessing			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingRevived	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostProcessing		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreScanning			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteScanning				(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostScanning			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteManageResult			(int ExeID ,ResultInspection *Res);

	bool	OutputInLotChangedCommon(EntryPointBase &entryPoint);
	bool	OutputInLotChangedSlave (EntryPointBase &entryPoint ,int LocalPage);
	bool	SearchLotID(const QString &iLotID);
	bool	CheckConnection(void);

	const QString	&GetFileName(void)				const	{	return FileName;		}
	void			SetFileName(const QString &s)			{	FileName=s;				}
	QString			GetOrganization(void)			const	{	return Organization;	}
	QString			GetDLLRoot(void)				const	{	return DLLRoot;			}
	QString			GetDLLName(void)				const	{	return DLLName;			}
	QString			GetParamFileName(void)			const	{	return ParamFileName;	}
	WORD			GetVersion(void)				const	{	return Ver;				}
	ResultDLLBaseRoot	*GetDLLPoint(void)			const	{	return DLLPoint;		}
	QString			GetCopyright(void)				const	{	return Copyright;		}
	WORD			GetDLLType(void)				const	;
	const QString	GetExplain(void)				const	;

	virtual	void	GetExportFunctions(QStringList &Str)	override;
	virtual	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)	override;
};

#endif
