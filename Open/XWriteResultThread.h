/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XWriteResultThread.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XWRITERESULTTHREAD_H)
#define	XWRITERESULTTHREAD_H

#include <QThread>
#include <QReadWriteLock>
#include "XDateTime.h"
#include "XResult.h"
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class	LayersBase;
class	ShadowTree;

class	ResultInspectionForStock : public NPList<ResultInspectionForStock> ,public ResultInspection
{
	int		ID;				//FixedID
	bool	Enabled;
	bool	OnWrite;
	bool	ShouldWriteResult;
	XDateTime	PushedTime;	//リングバッファに転送された日時

	IntList	ConnectedPCs;

public:
	ResultInspectionForStock(int n ,LayersBase *base):ResultInspection(base){	ID=n;	Enabled=false;	OnWrite=false;	ShouldWriteResult=true;	}

	int		GetID(void)					{	return ID;			}

	void	Set(LayersBase *base);
	bool	GetEnabled(void)			{	return Enabled;		}
	bool	GetOnWrite(void)			{	return OnWrite;		}
	void	SetEnabled(bool d)			{	Enabled=d;		}
	void	SetOnWrite(bool d)			{	OnWrite=d;		}
	bool	GetShouldWriteResult(void)	{	return ShouldWriteResult;	}
	void	SetShouldWriteResult(bool b)	{	ShouldWriteResult=b;	}
	XDateTime	&GetPushedTime(void)		{	return PushedTime;			}

	IntList	&GetConnectedPCs(void)		{	return ConnectedPCs;		}
};


class	ResultStock : public ServiceForLayers
{
	int			AllocatedNumb;
	NPListPack<ResultInspectionForStock>	ResultBaseDim;
	int			CurrentRPoint;
	int			CurrentWPoint;
	QMutex		FlagMutex;

public:
	ResultStock(LayersBase *base);
	~ResultStock(void);

	void	Initial(LayersBase *Base);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	RemovePhase(int RemovedPhaseCode);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);
	bool	SetWriteMode(LayersBase *Base ,ResultInspection &CurrentRes);
	bool	SetWriteModeForce(LayersBase *Base ,ResultInspection &CurrentRes);

	ResultInspectionForStock	*GetOldestAndClear(void);
	ResultInspectionForStock	*GetOldest(void);
	ResultInspectionForStock	*GetNewest(void);
	ResultInspectionForStock	*SearchOnMask(bool IDMaskMode10Base,int IDMaskBit,int IDtoWriteOut);
	ResultInspectionForStock	*PickupForWriteInSlave(const XDateTime &InspectedTime);
	ResultInspectionForStock	*Pickup(const XDateTime &InspectedTime);
	ResultInspectionForStock	*GetResult(int n);
	ResultInspectionForStock	*Ineffective(int CountFromOlder);

	int		GetStockedCount(void);
	int		GetStockedCountToWrite(void);
	ResultInspection *NeedDeleteResultOnCurrent(void);
	ResultInspection *NeedDeleteResult(void);

	ResultInspection	*GetBufferedResult(int64 inspectionID);
	ResultInspection	*GetBufferedResultAbsolutely(int64 inspectionID);
	ResultInspection	*GetBufferedOlderResult(int64 inspectionID, int GenerationLevel=0);
	void	ExecuteInitialAfterEdit	(int ExeID);
	void	InitialInspectionResult(void);

	void	CastAll(void);
	void	SetIDtoWriteOut(bool IDMaskMode10Base,int IDMaskBit,int id);
	ResultInspectionForStock	*SearchOnWrite(void);
	ResultInspection	*GetLatest(void);
	int64	GetUnsavedMinimumID(void);

	void	GetFlag(ResultInspectionForStock *Src ,bool &Enabled ,bool &OnWrite);
	void	SetFlag(ResultInspectionForStock *Src ,bool Enabled ,bool OnWrite);

	void	ClearAllErrorGroup(void);
};

class ResultInspectionForStockPointer : public NPList<ResultInspectionForStockPointer>
{
public:
	ResultInspectionForStock	*Pointer;
	ShadowTree					*STree;

	ResultInspectionForStockPointer(ShadowTree *t,ResultInspectionForStock *s)
		:Pointer(s),STree(t){}

	ResultInspectionForStock	*GetResult(void){	return Pointer;	}
};

class ResultInspectionForStockPointerContainer : public NPListPack<ResultInspectionForStockPointer>
{
public:
	ResultInspectionForStockPointerContainer(void){}

};

//---------------------------------------------------------------------------------------
class	FifoWriteBase : public NPList<FifoWriteBase>
{
public:
	XDateTime	EventTime;

	FifoWriteBase(void){}
};

class	FifoWriteOldest : public FifoWriteBase
{
public:
	QString		LotID;
	QString		LotName;
	QString		DeliveredInfo;
	FifoWriteOldest(void){}
};

class	FifoChangeLot : public FifoWriteBase
{
public:
	int			DeliveryNo;
	QString		LotID;
	QString		LotName;
	int32		LotAutoCount;
	QString		Remark;
	FifoChangeLot(void){	DeliveryNo=0;	LotAutoCount=0;		}
};


class	SlaveOutputResultQueueLeaf : public NPList<SlaveOutputResultQueueLeaf>
{
public:
	LayersBase	*Base;
	int32		MachineID;
	XDateTime	InspectedTime;
	ResultInspection *RBase;
	int			Phase;
	int			localPage;
	QByteArray	LotData;
	int32		MasterID;
	QString		DeliveryInfo;

public:
	SlaveOutputResultQueueLeaf(LayersBase	*_Base
								,int32 _MachineID
								,const XDateTime &_InspectedTime
								,ResultInspection *_RBase
								,int			phase
								,int			_localPage
								,const QByteArray	&LotData
								,int32		MasterID
								,const QString &DeliveryInfo);
	bool	OutputResultSlave (void);

	XDateTime	&GetInspectedTime(void)		{	return InspectedTime;	}
	bool			IsDoneCompressed(void)	{	return RBase->IsDoneCompressed();	}
};
//---------------------------------------------------------------------------------------

class	SlaveWriteThread : public QThread,public ServiceForLayers
{
public:
	NPListPack<SlaveOutputResultQueueLeaf>	SlaveWriteQueue;
	QMutex									SlaveWriteQueueMutex;
	volatile    bool    CmdFinish;

	SlaveWriteThread(LayersBase *base);

	void	Push(SlaveOutputResultQueueLeaf  *W);
	void	WriteLoop(void);
protected:
	void run();

};


class WriteResultThread : public QThread,public ServiceForLayers
{
	Q_OBJECT

	ResultStock			*ResultCache;
	volatile	bool	CastFlag;
	volatile	bool	ForceWriteFlag;
	NPListPack<SlaveOutputResultQueueLeaf>	SlaveOutputResultQueue;
	QMutex									SlaveOutputResultQueueMutex;
	NPListPack<FifoWriteBase>		DataWriteOldest;

	volatile    bool    EnabledStockedWrite;
	volatile    int     IDMaskBit;
	volatile    bool    IDMaskMode10Base;
	volatile    int     IDtoWriteOut;
	volatile    bool    CmdFinish;
	bool	Mastered;
	QMutex	MutexWriteOldest;
	QString		DeliveredInfo;
	QString		BarcodeInfo;

	SlaveWriteThread	*SlaveWriteThreadInst;

public:
	WriteResultThread(LayersBase *base ,bool StartThreadWriteMode);
	virtual	~WriteResultThread(void);
	void	Initial(LayersBase *Base);
	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	bool	Reallocate(int newPhaseNumb);
	bool	RemovePhase(int RemovedPhaseCode);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);

	void	ExecuteInitialAfterEdit	(int ExeID ,ResultInspection *Res);
protected:
	void run();

public:
	void	PutCurrentToStock(LayersBase *Base ,ResultInspection &currentResultData);
	void	PutForceToStock(LayersBase *Base ,ResultInspection &currentResultData);;

	ResultInspectionForStock	*PickupForWriteInSlave(const XDateTime &InspectedTime);
	ResultInspectionForStock	*Pickup(const XDateTime &InspectedTime);
	int		GetStockedCount(void);
	int		GetStockedCountToWrite(void);
	void	SetCastAll(void);
	bool	WaitForFinishingCast(int MaxMilisec=10000);
	void	ForceWrite(void);
	void	FlushWaitForWrite(void);
	bool	GetForceWriteMode(void){	return ForceWriteFlag;	}

	ResultStock			*GetResultCache(void)	{	return ResultCache;		}
	ResultInspection	*GetBufferedResult(int64 inspectionID)			{		return ResultCache->GetBufferedResult(inspectionID);			}
	ResultInspection	*GetBufferedResultAbsolutely(int64 inspectionID){		return ResultCache->GetBufferedResultAbsolutely(inspectionID);	}
	ResultInspection	*GetBufferedOlderResult(int64 inspectionID, int GenerationLevel=0)
																{		return ResultCache->GetBufferedOlderResult(inspectionID, GenerationLevel);	}

	void	PushSlaveCommand(SlaveOutputResultQueueLeaf *W);
	SlaveOutputResultQueueLeaf	*PopSlaveOutputResultQueueLeaf(void);
	ResultInspection	*GetLatest(void)		{	return ResultCache->GetLatest();		}
	ResultInspection	*NeedDeleteResultOnCurrent(void);
	ResultInspection	*NeedDeleteResult(void);
	ResultInspection	*GetResult(int n){	return ResultCache->GetResult(n);	}
	ResultInspectionForStock	*RemoveResultFromOldest(int n);
	void	ClearAllErrorGroup(void);

	bool	GetEnabledStockedWrite(void)	{	return EnabledStockedWrite;		}
	void	SetEnabledStockedWrite(bool b)	{	EnabledStockedWrite=b;			}
	int		GetIDMaskBit(void)				{	return IDMaskBit;				}
	void	SetIDMaskBit(int id)			{	IDMaskBit=id;					}
	bool	GetIDMaskMode10Base(void)		{	return IDMaskMode10Base;		}
	void	SetIDMaskMode10Base(bool b)		{	IDMaskMode10Base=b;				}
	int		GetIDtoWriteOut(void)			{	return IDtoWriteOut;			}
	void	SetIDtoWriteOut(int id);
	bool	GetCmdFinish(void)				{	return CmdFinish;				}
	void	SetCmdFinish(bool b)			{	CmdFinish=b;					}
	bool	GetMastered(void)				{	return Mastered;				}
	void	SetMastered(bool b)				{	Mastered=b;						}
	int64	GetUnsavedMinimumID(void);

	void	SetWriteOldestOne(void);
	FifoWriteBase	*IsWrittenOldestOne(void);

	void	ReserveChangeLot(int32 _DeliveryNo
							,int32 _NextLotAutoCount
							,QString _NextLotID
							,QString _NextLotName
							,QString _NextRemark);
	void	PushSlaveWriteThread(SlaveOutputResultQueueLeaf	*WSlave);
	SlaveWriteThread	*GetSlaveWriteThreadInst(void)	{	return SlaveWriteThreadInst;	}

	bool	Ineffective(int CountFromOlder);
	void	SetDeliveredInfo(const QString &Info)	{		DeliveredInfo=Info;		}
	QString	GetDeliveredInfo(void)					{		return DeliveredInfo;	}
	void	SetBarcodeInfo(const QString &Info)		{		BarcodeInfo=Info;		}
	QString	GetBarcodeInfo(void)					{		return BarcodeInfo;		}
private:
	void	ReleaseForWrite(void);
	bool	IsLocalCamera(void);
signals:
	void	SignalWroteCommon(XDateTime tm);
	void	SignalWroteSlave(XDateTime tm);
	void	SignalChangeLotInfo(int DeliveryNo);

private slots:

};


#endif