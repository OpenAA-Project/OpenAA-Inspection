#pragma once

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMultiSpectral.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDataAlgorithm.h"
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"

#define	MultiSpectralVersion	1

class	MultiSpectralItem;
class	MultiSpectralLibrary;

class	MultiSpectralThreshold : public AlgorithmThreshold
{
public:
	int		SearchDot		;
	double	ThresholdLength	;
	int		OKDot;

	MultiSpectralThreshold(MultiSpectralItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MultiSpectralItem : public AlgorithmItemPI
{
	int		XByte	;
	int		XLen,YLen;
	int		X1,Y1;
	BYTE	**NGMap	;
	int		MasterCx,MasterCy;

	ImagePointerContainer MasterImageList;
	ImagePointerContainer TargetImageList;
public:
	AlignmentPacket2D	*AVector;

	MultiSpectralItem(void);
	~MultiSpectralItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MultiSpectralItem();	}
	const	MultiSpectralThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MultiSpectralThreshold *)GetThresholdBaseReadable(base);	}
	MultiSpectralThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MultiSpectralThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new MultiSpectralThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

	void	CopyThreshold(MultiSpectralItem &src)	;
	void	CopyThresholdOnly(MultiSpectralItem &src);
	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

};


class   MultiSpectralInPage : public AlgorithmInPagePI
{
public:
	MultiSpectralInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType=0)	override{	return new MultiSpectralItem();	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
};

class	MultiSpectralBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	MultiSpectralBase(LayersBase *Base);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	bool	HasReflection(ReflectionMode mode)	override	{	return (mode==_Reflection_Mask)?true:false;	}
	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MultiSpectralInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MultiSpectral");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMultiSpectral.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};
//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	MultiSpectralHistogramListReqCommand	3
#define	MultiSpectralHistogramListSendCommand	4
#define	MultiSpectralReqThresholdReqCommand		5
#define	MultiSpectralReqThresholdSendCommand	6
#define	MultiSpectralReqTryThresholdCommand		7
#define	MultiSpectralSendTryThresholdCommand	8
#define	MultiSpectralReqChangeShiftCommand		9
#define	SetIndependentItemNameDataCommand_All	10
//==================================================================================
class	AddMultiSpectralAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			LibID;

	AddMultiSpectralAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMultiSpectralAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MultiSpectralDrawAttr : public AlgorithmDrawAttr
{
public:
	MultiSpectralDrawAttr(void){}
	MultiSpectralDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	MultiSpectralDrawAttr( QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		//NegColorMask	=nncol;	
		//NegColorSelected=nscol;	
		//NegColorMask.setAlpha(ntranparentLevel);
		//NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdMultiSpectralDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;

	CmdMultiSpectralDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};


//==================================================================================

class	MultiSpectralThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;

	MultiSpectralThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	MultiSpectralThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;

	int		SearchDot		;
	double	ThresholdLength	;
	int		OKDot			;

	MultiSpectralThresholdSend(void);

	void	ConstructList(MultiSpectralThresholdReq *reqPacket,MultiSpectralBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	MultiSpectralReqTryThreshold
{
public:
	MultiSpectralItem	Threshold;
	struct MultiSpectralReqTryThresholdStruct
	{
		int32	GlobalPage		;
		int		ItemID			;	
		int		SearchDot		;
		double	ThresholdLength	;
		int		OKDot			;
	}Data;

	MultiSpectralReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	MultiSpectralSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;

	MultiSpectralSendTryThreshold(void);
	~MultiSpectralSendTryThreshold(void);

	void	ConstructList(MultiSpectralReqTryThreshold *reqPacket,MultiSpectralBase *Base);
	void	Calc(MultiSpectralItem *Target,MultiSpectralItem *Src,MultiSpectralBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//=====================================================================

class	CmdMultiSpectralDeleteItemPacket : public GUIDirectMessage
{
public:
	CmdMultiSpectralDeleteItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdMultiSpectralDeleteItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMultiSpectralLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetMultiSpectralLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMultiSpectralLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMultiSpectralLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetMultiSpectralLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMultiSpectralLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempMultiSpectralLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempMultiSpectralLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMultiSpectralLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearMultiSpectralLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearMultiSpectralLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearMultiSpectralLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertMultiSpectralLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertMultiSpectralLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertMultiSpectralLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateMultiSpectralLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateMultiSpectralLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateMultiSpectralLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadMultiSpectralLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadMultiSpectralLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadMultiSpectralLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteMultiSpectralLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteMultiSpectralLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteMultiSpectralLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempMultiSpectralItemPacket : public GUIDirectMessage
{
public:
	MultiSpectralItem	*Point;
	CmdCreateTempMultiSpectralItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMultiSpectralItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromMultiSpectralItemPacket : public GUIDirectMessage
{
public:
	MultiSpectralItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromMultiSpectralItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromMultiSpectralItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadMultiSpectralItemPacketFromByteArray : public GUIDirectMessage
{
public:
	MultiSpectralItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadMultiSpectralItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadMultiSpectralItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
