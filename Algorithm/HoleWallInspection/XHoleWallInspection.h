/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\XHoleWallInspection\XHoleWallInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XHoleWallInspection_H)
#define	XHoleWallInspection_H

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
//#include "XPropertyHoleWallPacket.h"
#include "XStandardCommand.h"

#define	HoleWallVersion	1


class   AlignmentInLayer;
class	XAlignmentArea;
class	HoleWallLibrary;
class	HoleWallBase;
class	HoleWallItem;
class	HoleWallInLayer;
class	HoleWallInPage;
class	SetThresholdHoleWallInfo;


#define	Hist_HoleWall_NGSize			1
#define	Hist_HoleWall_ShiftX			2
#define	Hist_HoleWall_ShiftY			3


class	HoleWallThreshold : public AlgorithmThreshold
{
public:
	int32	NGSize;
	WORD	SearchDot;

	HoleWallThreshold(HoleWallItem *parent);

	virtual	void	RegistHist(void)	override;
	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
    
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class   HoleWallItem : public AlgorithmItemPLITemplate<HoleWallInLayer,HoleWallInPage,HoleWallBase>
{
	FlexArea	OutsideArea;

	BYTE	**BmpMap;
	BYTE	**TmpMap;
	BYTE	**MaskMap;
	int		XLen;
	int		XByte;
	int		YLen;
	int		MapXPos,MapYPos;

public:
	AlignmentPacket2D	*AVector;

	int		ResultShiftX;
	int		ResultShiftY;

public:

	HoleWallItem(void);
	HoleWallItem(FlexArea &area);
	virtual	~HoleWallItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new HoleWallItem();	}
	void	RebuildWallShape(void);
	void	MakeOutsideArea(void);

	const	HoleWallThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const HoleWallThreshold *)GetThresholdBaseReadable(base);	}
	HoleWallThreshold			*GetThresholdW(LayersBase *base=NULL){	return (HoleWallThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new HoleWallThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPLI &operator=(const AlgorithmItemRoot &src)	override;
	void	CopyThreshold(HoleWallItem &src);
	void	CopyThresholdOnly(HoleWallItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	CopyArea(HoleWallItem &BI);
	void	SetThresholdFromCommon(SetThresholdHoleWallInfo *Info);
private:
	double	GetMaxDiff(ImageBuffer &Target , int dx ,int dy);
	double	CalcClusterize(ImageBuffer &Target , int dx ,int dy,PureFlexAreaListContainer &NGArea);
};


class   HoleWallInLayer : public AlgorithmInLayerPLITemplate<HoleWallItem,HoleWallInPage,HoleWallBase>
{
	friend class	HoleWallItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

public:
	HoleWallInLayer(AlgorithmInPageRoot *parent);
	~HoleWallInLayer(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			HoleWallItem	*a=new HoleWallItem();	
			a->SetParent(this);
			return a;
		}
	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item)			override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override;

	void	PickupTest(HoleWallLibrary &LibData);
	void	GenerateBlocks(HoleWallLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	Draw(QImage &pnt,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	MoveFromPipe(GeneralPipeInfo &Info);
private:
	void	CreatePickupBmpBuff(void);
};

class   HoleWallInPage : public AlgorithmInPagePLITemplate<HoleWallItem,HoleWallInLayer,HoleWallBase>
{
public:
	double		ShiftXParamLeft[4];
	double		ShiftXParamRight[4];
	double		ShiftYRate;		//ShiftY=ShiftYRate*Thickness

	HoleWallInPage(AlgorithmBase *parent);
	~HoleWallInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override	{	return new HoleWallInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)			override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;
private:

};
class	HoleWallBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		HoleWallNormal	;
	QColor		HoleWallSelected	;
	QColor		HoleWallActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;
	double		Thickness ;
	QByteArray	ArrayShiftMulInPage;
	QStringList	ShiftYRateInPage;

	HoleWallBase(LayersBase *Base);
	virtual	HoleWallInPage	*NewChild(AlgorithmBase *parent)	override{	return(new HoleWallInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)			override{	return QString("HoleWall");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigHoleWall.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	void	ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)			override;
};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	HoleWallHistogramListReqCommand				3
#define	HoleWallHistogramListSendCommand				4
#define	HoleWallReqThresholdReqCommand				5
#define	HoleWallReqThresholdSendCommand				6
#define	HoleWallReqTryThresholdCommand				7
#define	HoleWallSendTryThresholdCommand				8
#define	HoleWallReqChangeShiftCommand				9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================

class	HoleWallDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedBlock
	};

	DrawMode	Mode;

	QColor		ColorPickup	;
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;

	HoleWallDrawAttr(void):ServiceForLayers(NULL){}
	HoleWallDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	HoleWallDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &blockColor0
				, QColor &blockColor1
				, QColor &blockColor2
				, QColor &blockColor3
				, QColor &blockColor4
				, QColor &blockColor5
				, QColor &blockColor6
				, QColor &blockColor7);

	void	Initial(void);

	HoleWallDrawAttr	&operator=(HoleWallDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	HoleWallDrawAttr	&HoleWallDrawAttr::operator=(HoleWallDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	ColorPickup	=src.ColorPickup;
	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	return *this;
}
inline	bool	HoleWallDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	HoleWallDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}


//==========================================================================
class	HoleWallInfoList : public NPList<HoleWallInfoList>
{
public:
	int		LibID;
	IntList	HoleWallCount;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	HoleWallInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(HoleWallCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	HoleWallInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(HoleWallCount.Load(f)==false)
		return false;
	return true;
}


//==================================================================================
class	HoleWallChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	int32	Dx,Dy;

	HoleWallChangeShift(void){}

	void	Reflect(HoleWallBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	HoleWallThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	HoleWallThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HoleWallThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	int32	NGSize;
	WORD	SearchDot;

	HoleWallThresholdSend(void);

	void	ConstructList(HoleWallThresholdReq *reqPacket,HoleWallBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HoleWallReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;	
	HoleWallItem	Threshold;

	HoleWallReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	HoleWallSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	double	NGSize;

	HoleWallSendTryThreshold(void);
	HoleWallSendTryThreshold(const HoleWallSendTryThreshold &src);
	~HoleWallSendTryThreshold(void);

	void	ConstructList(HoleWallReqTryThreshold *reqPacket,HoleWallBase *Base);

	HoleWallSendTryThreshold	&operator=(const HoleWallSendTryThreshold &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CmdGetHoleWallLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetHoleWallLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetHoleWallLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetHoleWallLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetHoleWallLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetHoleWallLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempHoleWallLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempHoleWallLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempHoleWallLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearHoleWallLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearHoleWallLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearHoleWallLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertHoleWallLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertHoleWallLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertHoleWallLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateHoleWallLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateHoleWallLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateHoleWallLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadHoleWallLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadHoleWallLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadHoleWallLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteHoleWallLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteHoleWallLibraryPacket(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;	}
	CmdDeleteHoleWallLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;	}
};

class	CmdPickupTestHoleWallPacket : public GUIDirectMessage
{
public:
	//HoleWallLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;
	IntList			LayerList;

	CmdPickupTestHoleWallPacket(LayersBase *base):GUIDirectMessage(base)		{	LibPoint=NULL;	}
	CmdPickupTestHoleWallPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	LibPoint=NULL;	}
};

class	CmdGenerateHoleWallPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	IntList		LayerList;

	CmdGenerateHoleWallPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateHoleWallPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempHoleWallItemPacket : public GUIDirectMessage
{
public:
	HoleWallItem	*Point;
	CmdCreateTempHoleWallItemPacket(LayersBase *base):GUIDirectMessage(base)		{	Point=NULL;	}
	CmdCreateTempHoleWallItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Point=NULL;	}
};

class	CmdCreateByteArrayFromHoleWallItemPacket : public GUIDirectMessage
{
public:
	HoleWallItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromHoleWallItemPacket(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;	}
	CmdCreateByteArrayFromHoleWallItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;	}
};

class	CmdAddByteHoleWallItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;

	CmdAddByteHoleWallItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteHoleWallItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadHoleWallItemPacketFromByteArray : public GUIDirectMessage
{
public:
	HoleWallItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadHoleWallItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base)			{	BItemPoint=NULL;	}
	CmdLoadHoleWallItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	BItemPoint=NULL;	}
};
class	CmdModifySelectedHoleWallFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedHoleWallFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedHoleWallFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestHoleWallPacket: public GUIDirectMessage
{
public:
	CmdClearTestHoleWallPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestHoleWallPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdHoleWallInfoListPacket: public GUIDirectMessage
{
public:
	NPListPack<HoleWallInfoList>	*HoleWallInfos;
	CmdHoleWallInfoListPacket(LayersBase *base):GUIDirectMessage(base)			{	HoleWallInfos=NULL;	}
	CmdHoleWallInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	HoleWallInfos=NULL;	}
};

class	CmdGetHoleWallFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	HoleWallItem	*HoleWallInfoOnMouse;

	CmdGetHoleWallFromList(LayersBase *base):GUIDirectMessage(base)			{	HoleWallInfoOnMouse=NULL;	}
	CmdGetHoleWallFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	HoleWallInfoOnMouse=NULL;	}
};
class	CmdCreateHoleWallItem: public GUIDirectMessage
{
public:
	HoleWallItem	*HoleWall;
	CmdCreateHoleWallItem(LayersBase *base):GUIDirectMessage(base)			{	HoleWall=NULL;	}
	CmdCreateHoleWallItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	HoleWall=NULL;	}
};

class	CmdMakeBitBuff: public GUIDirectMessage
{
public:
	CmdMakeBitBuff(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeBitBuff(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================



#endif