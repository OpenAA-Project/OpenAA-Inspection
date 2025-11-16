/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XResultDLLManager.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XRESULTDLLMANAGERH
#define XRESULTDLLMANAGERH

#include "XTypeDef.h"
#include "NList.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XResult.h"
#include "XServiceForLayers.h"
#include "XMacroFunction.h"
#include <QMutex>

class	ResultInterfaceDLL;
class	ResultInspectionForStockPointerContainer;
class	ExecuteInitialAfterEditInfo;

class	ResultDLL : public NPList<ResultDLL> ,public ServiceForLayers
{
	ResultInterfaceDLL	*Interface;
public:
	ResultDLL(LayersBase *Base);
	ResultDLL(const ResultDLL &src);
	~ResultDLL(void);

	ResultInterfaceDLL	*GetInterface(void)		{	return Interface;	}
	
	ResultDLL	&operator=(const ResultDLL &src);
	bool		LoadDLL(const QString &filename);
	bool		IsResultDLL(void);
	bool		Initial(void);
	bool		Release(void);
	bool		CheckSystemVersion(QStringList &Str);
	void		AssociateComponent	(ComponentListContainer &List);
	void		Prepare(void);

	int64	OutputResultCommon(ResultInspection *RBase
								,ResultInspectionForStockPointerContainer &ShadowResStocks
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

	const QString	&GetFileName(void)				const;
	void			SetFileName(const QString &s)	;
	QString			GetOrganization(void)			const;
	QString			GetDLLRoot(void)				const;
	QString			GetDLLName(void)				const;
	QString			GetParamFileName(void)			const;
	WORD			GetVersion(void)				const;
	ResultDLLBaseRoot	*GetDLLPoint(void)			const;
	QString			GetCopyright(void)				const;
	WORD			GetDLLType(void)				const;
	QString			GetExplain(void)				const;

	void	GetExportFunctions(QStringList &Str);
	void	GetMacroNames(QStringList &Str);

	virtual	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);
};

class	ResultDLLBaseClass : public NPListPack<ResultDLL>,public ServiceForLayers
{
	QMutex	Mutex;
public:
	explicit	ResultDLLBaseClass(LayersBase *Base);

	void	Prepare(void);
	ResultDLLBaseClass	&operator=(const ResultDLLBaseClass &src);
	int		SearchAddDLL(const QString &path);
	int		LoadDLL(const QString &FileNames,bool ShowInWindow);
	bool	Release(void);
	bool	UnSavedResult(void);
	bool	CheckSystemVersion(QStringList &Str);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	SearchLotID(const QString &iLotID);

	int64	OutputResultCommon(ResultInspection *RBase
								,ResultInspectionForStockPointerContainer	&ShadowResStocks);
	bool	OutputResultSlave (ResultInspectionForStockPointerContainer &ShadowResStocks
								,int32 MachineID ,XDateTime &InspectedTime
								,ResultInspection *RBase 
								,const QString &LotID
								,int phase ,int localPage);
	int64	OutputResultDirectly(int mode ,ResultInspection *RBase
								,GUIDirectMessage *packet);	//mode=-2:PreFinishInspection -1:FinishInspection
	bool	RemoveResult(int32 MachineID ,XDateTime &ResultTime ,int64 InspectionID);
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

	bool	OutputInLotChangedCommon(void);
	bool	OutputInLotChangedSlave (int LocalPage);

	ResultDLL	*GetResultDLL(const QString &DLLRoot ,const QString &DLLName);
	bool	CheckConnection(void);
	bool	CheckResultDLL(void);

	void	Lock(void)		{	Mutex.lock();	}
	void	Unlock(void)	{	Mutex.unlock();	}
};

class	ResultCmdSaveSlave : public GUICmdPacketBase
{
public:
	XDateTime	InspectedTime;
	int32		MachineID;
	QByteArray	LotData;
	int32		MasterID;
	int32		Phase;
	QString		DeliveryInfo;

	ResultCmdSaveSlave(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
