/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInLayerCmdLocal.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XDATAINLAYERCMDLOCAL_H
#define XDATAINLAYERCMDLOCAL_H

#include "XGUIPacketForDLL.h"
#include "XDataInLayer.h"
#include "XMasterData.h"
#include "XDataAlgorithmConfirm.h"

//============================================================================
class CmdReqSaveMasterForPage : public GUICmdPacketBase
{
	int32		MasterCode;
public:
	int32		MachineID;
	QString		ImagePath;
	bool		ForceSave;

	CmdReqSaveMasterForPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int masterCode ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class CmdReqLoadMasterForPage : public GUICmdPacketBase
{
public:
	int32		MasterCode;
	int32		MachineID;
	bool		ModeLoadMasterImage;

	CmdReqLoadMasterForPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int masterCode ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class CmdAckLoadMasterForPage : public GUICmdPacketBase
{
public:
	LoadedInfoContainer	LInfo;

	CmdAckLoadMasterForPage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class CmdReqLoadMasterForPagePhase : public GUICmdPacketBase
{
public:
	int32		MasterCode;
	int32		MachineID;
	bool		ModeLoadMasterImage;
	int32		DestPhase;

	CmdReqLoadMasterForPagePhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int masterCode ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdReqPartialImage : public GUICmdPacketBase
{
public:
	int32		localX1,localY1;
	int32		localX2,localY2;
	int32		LayerNumb;

	GUICmdReqPartialImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendPartialImage : public GUICmdPacketBase
{
public:
	ImageBuffer	**ImageData;
	int32		LayerNumb;
	int			ImageWidth;
	int			ImageHeight;

	GUICmdSendPartialImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendPartialImage(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	CreateData(void);
	void	CreateImage(LayersBase *Base ,int localPageSrc ,int localX1,int localY1,int localX2,int localY2,int LayerNumb);
	ImageBuffer	*GetLayer(int layer){	return ImageData[layer];	}
};

//============================================================================
class	GUICmdSendProcessing : public GUICmdPacketBase
{
public:
	int			CurrentValue;
	int			MaxValue;
	QString		Message;

	GUICmdSendProcessing(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdSendProcessingAdd : public GUICmdPacketBase
{
public:
	int			CurrentValue;
	int			MaxValue;
	QString		Message;

	GUICmdSendProcessingAdd(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdCopyImage : public GUICmdPacketBase
{
public:
	int			srcImageType;
	int			dstImageType;

	GUICmdCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================

class	GUICmdSendClose : public GUICmdPacketBase
{
public:
	int32	ReturnCode;
	GUICmdSendClose(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdSendAck : public GUICmdPacketBase
{
public:
	int		AckFilterID;

	GUICmdSendAck(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


//============================================================================

class	GUICmdSendParameters : public GUICmdPacketBase
{
public:
	QBuffer	Buff;

	GUICmdSendParameters(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Initial(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetForceChangedInspectID : public GUICmdPacketBase
{
public:

	GUICmdSetForceChangedInspectID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Initial(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdReqEdited : public GUICmdPacketBase
{
public:

	GUICmdReqEdited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendEdited : public GUICmdPacketBase
{
public:
	bool	Edited;

	GUICmdSendEdited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdReqCalcDone : public GUICmdPacketBase
{
public:

	GUICmdReqCalcDone(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCalcDone : public GUICmdPacketBase
{
public:
	bool	CalcDone;

	GUICmdSendCalcDone(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdSetEdited : public GUICmdPacketBase
{
public:
	bool	Edited;

	GUICmdSetEdited(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdSetCalcDone : public GUICmdPacketBase
{
public:
	bool	CalcDone;

	GUICmdSetCalcDone(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdSendOffset : public GUICmdPacketBase
{
public:
	DataInPage::ConstructionData	*GlobalOffset;
	int								GlobalPageNumb;

	GUICmdSendOffset(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendOffset(void);

	void	InitialInMaster(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdReqCheckSlave : public GUICmdPacketBase
{
public:
	XDateTime	NowTime;
	QByteArray	Buff;
	bool		NoCamDevice;

	GUICmdReqCheckSlave(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckCheckSlave : public GUICmdPacketBase
{
public:
	enum	RetMode{
		_ReqReboot		=1
		,_NoProblem		=2
		,_ErrorOccurs	=3
	}Ret;
	QStringList	Messages;

	GUICmdAckCheckSlave(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class CmdReqRemoveStockedResult : public GUICmdPacketBase
{
public:
	CmdReqRemoveStockedResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	ResultCmdReqLotChangedSlave: public GUICmdPacketBase
{
public:
	ResultCmdReqLotChangedSlave(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class CmdWritternResult : public GUICmdPacketBase
{
public:
	XDateTime	InspectedTime;

	CmdWritternResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdReqPixWithAlgorithm : public GUICmdPacketBase
{
public:
	GUICmdReqPixWithAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckPixWithAlgorithm : public GUICmdPacketBase
{
public:
	QByteArray	Buff;

	GUICmdAckPixWithAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLoadPixWithAlgorithm : public GUICmdPacketBase
{
public:
	QByteArray	Buff;

	GUICmdLoadPixWithAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class CmdReportError : public GUICmdPacketBase
{
public:
	CmdReportError(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//============================================================================
class	GUICmdSendInspectionNumber : public GUICmdPacketBase
{
public:
	int64	InspectionNumber;

	GUICmdSendInspectionNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdSendMachineID : public GUICmdPacketBase
{
public:
	int32	MachineID;

	GUICmdSendMachineID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================

class	GUICmdReqResultInfo : public GUICmdPacketBase
{
public:
	GUICmdReqResultInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckResultInfo : public GUICmdPacketBase
{
public:
	QByteArray	Buff;

	GUICmdAckResultInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdLoadResultInfo : public GUICmdPacketBase
{
public:
	QByteArray	Buff;

	GUICmdLoadResultInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdSendAllComms: public GUICmdPacketBase
{
public:
	SystemConnectionInfoContainer	Data;

	GUICmdSendAllComms(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAllComms(void);

	void	Initial(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdReqSetCurrentPhase : public GUICmdPacketBase
{
public:
	int		CurrentPhase;

	GUICmdReqSetCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdMakeUncoveredMap : public GUICmdPacketBase
{
public:

	GUICmdMakeUncoveredMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdReqRewindExecuter : public GUICmdPacketBase
{
public:
	int	CPoint[6];

	GUICmdReqRewindExecuter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdSetAutoRepeat : public GUICmdPacketBase
{
public:
	bool	RepeatMode;

	GUICmdSetAutoRepeat(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdSetCurrentScanPhaseNumber : public GUICmdPacketBase
{
public:
	int	CurrentScanPhaseNumber;

	GUICmdSetCurrentScanPhaseNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdForceStrategicNumber : public GUICmdPacketBase
{
public:
	int	StrategicNumber;
	int CPoints[10];

	GUICmdForceStrategicNumber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdChangeLotInfo : public GUICmdPacketBase
{
public:
	int			LotAutoCount;
	QString		LotID;
	QString		LotName;
	QString		Remark;
	int			DeliveryNo;

	GUICmdChangeLotInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdDeliverManualExecuter : public GUICmdPacketBase
{
public:
	QString		DLLRoot;
	QString		DLLName;
	QByteArray	ManualArray;

	GUICmdDeliverManualExecuter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdSetLibFolderID : public GUICmdPacketBase
{
public:
	int	LibFolderID;
	int originalLibFolder;

	GUICmdSetLibFolderID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdReqChangedAlgo : public GUICmdPacketBase
{
public:
	GUICmdReqChangedAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckChangedAlgo : public GUICmdPacketBase
{
public:
	struct	LayersBase::HasChanged	ChangedAlgo;

	GUICmdAckChangedAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdDeliverChangedAlgo : public GUICmdPacketBase
{
public:
	struct	LayersBase::HasChanged	ChangedAlgo;

	GUICmdDeliverChangedAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//============================================================================
class	GUICmdSendResultAnalizerData : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendResultAnalizerData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdSetThresholdLevel : public GUICmdPacketBase
{
public:
	int	ThresholdLevelParentID;
	int	ThresholdLevelID;

	GUICmdSetThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdCopyThresholdLevel : public GUICmdPacketBase
{
public:
	int SourceLevelID;
	int DestLevelID;

	GUICmdCopyThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdRebuildThresholdLevel : public GUICmdPacketBase
{
public:
	GUICmdRebuildThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdSetCurrentIntoThresholdLevel : public GUICmdPacketBase
{
public:
	int LevelID;

	GUICmdSetCurrentIntoThresholdLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdReqThresholdInstance : public GUICmdPacketBase
{
public:
	int	LibType	;
	int	LibID	;
	int	Layer	;
	int	ItemID	;

	GUICmdReqThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckThresholdInstance : public GUICmdPacketBase
{
public:
	QByteArray	Array;

	GUICmdAckThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReflectThresholdInstanceOne: public GUICmdPacketBase
{
public:
	int	LibType	;
	int	LibID	;
	int	Layer	;
	IntList	ItemID;
	QByteArray	ThresholdData;
	ChangedMap	ChangedMapInThreshold;

	GUICmdReflectThresholdInstanceOne(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReflectThresholdInstanceAll: public GUICmdPacketBase
{
public:
	int	LibType	;
	int	LibID	;
	int	Layer	;
	QByteArray	ThresholdData;
	ChangedMap	ChangedMapInThreshold;

	GUICmdReflectThresholdInstanceAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdTestThresholdInstance: public GUICmdPacketBase
{
public:
	int	LibType	;
	int	LibID	;
	int	Layer	;
	IntList	ItemID;
	QByteArray	ThresholdData;
	ChangedMap	ChangedMapInThreshold;

	GUICmdTestThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdResultThresholdInstance: public GUICmdPacketBase
{
public:
	QByteArray	ResultInItemData;

	GUICmdResultThresholdInstance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//============================================================================

class	GUICmdEmitPipeCreateArea: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	FlexArea			Area;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeCreateArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeMoveItem: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	int					dx ,dy;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeMoveItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeRemoveItem: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeRemoveItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeSelectItem: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	int					px ,py;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeSelectItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeSelectItemByLibrary: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	int					LibType, LibID;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeSelectItemByLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeSelectItemByArea: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	FlexArea			Area;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeSelectItemByArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeRotateItems	: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	double				Radian;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeRotateItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeMirrorItem	: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	bool				XMirror ,YMirror;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeMirrorItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdEmitPipeCopyImage	: public GUICmdPacketBase
{
public:
	EmitPipeDirection	EDir;
	int					Source;
	int					Destination;
	QByteArray			Something;
	QString				AlgoDLLRoot;
	QString				AlgoDLLName;

	GUICmdEmitPipeCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

//============================================================================
class	GUICmdCopyShadowAlgorithm : public GUICmdPacketBase
{
public:
	QString	DLLRoot;
	QString	DLLName;
	int32	Phase;
	int32	ParentShadowLevel;
	int32	ParentShadowNumber;
	int32	ChildShadowLevel;
	int32	ChildShadowNumber;

	GUICmdCopyShadowAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdReqUndo : public GUICmdPacketBase	
{
public:
	int32	IDForUndo;

	GUICmdReqUndo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================================
class	GUICmdReqRedo : public GUICmdPacketBase	
{
public:
	int32	IDForUndo;

	GUICmdReqRedo(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================
class	GUICmdReqConfirmItemList : public GUICmdPacketBase
{
public:
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	GUICmdReqConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckConfirmItemList : public GUICmdPacketBase
{
public:
	ConfirmItemListContainer	ItemList;

	GUICmdAckConfirmItemList(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//============================================================================
class	GUICmdReqBufferInfo : public GUICmdPacketBase
{
public:
	GUICmdReqBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckBufferInfo : public GUICmdPacketBase
{
public:
	BufferInfoList	*Dim;
	int				DimCount;

	GUICmdAckBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//============================================================================
class	GUICmdReqClearBufferInfo : public GUICmdPacketBase
{
public:
	GUICmdReqClearBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//============================================================================
class	GUICmdReqRemoveBufferInfo : public GUICmdPacketBase
{
public:
	int	OriginCode;

	GUICmdReqRemoveBufferInfo(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//============================================================================

class	GUICmdChangeItemID : public GUICmdPacketBase
{
public:
	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Layer;
	int		OldItemID;
	int		NewItemID;

	GUICmdChangeItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckChangeItemID : public GUICmdPacketBase
{
public:
	bool	DoneSuccessful;
	bool	NoItem;
	bool	DupID;

	GUIAckChangeItemID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

#endif

