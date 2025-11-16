/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlock.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XTRUECOLORBLOCK_H)
#define	XTRUECOLORBLOCK_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XBlockSearchWay.h"
#include "XColorSpace.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XPropertyTrueColorBlockPacket.h"
#include "XStandardCommand.h"

#define	TrueColorBlockVersion	20004


class   AlignmentInLayer;
class	XAlignmentArea;
class	TrueColorBlockLibrary;
class	TrueColorBlockBase;
class	TrueColorBlockItem;

class	ShowAndSetItemsTrueColor : public ShowAndSetItemsBaseClass
{
public:
	GUIFormBase	*Form;
};

#pragma	pack(push,1)

class	TrueColorBlockThreshold : public AlgorithmThreshold
{
public:
	DWORD		NOKDot;			//ã∑àÊÇÃÇnÇjÉhÉbÉgêî
	DWORD		BOKDot;			//çLàÊÇÃÇnÇjÉhÉbÉgêî

	WORD		BOKLength;		//çLàÊÇ≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
	WORD		NOKLength;		//ã∑àÊÇ≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj

	ColorLogicWithTable	NInsColor;		//ã∑àÊÇÃîªíËåvéZ
	int32				NMergin;		//ã∑àÊîªíËÇÃãñóeãPìxó 
	ColorLogicWithTable	BInsColor;		//çLàÊÇÃîªíËåvéZ
	int32				BMergin;		//ã∑àÊîªíËÇÃãñóeãPìxó 

	struct{
		bool	ModeEnabled					:1;
		bool	ModeAdjustable				:1;
		bool	ModeCommonMovable			:1;
		bool	ModeNGCluster				:1;
		bool	ModeCenterBrightFromParts	:1;
		bool	ModeOnlyMatching			:1;
		bool	ModeCalcBothBN				:1;
		bool	ModeInvertLogic				:1;
	}PointMove;

	WORD	NMinNGCount;	//ã∑àÊÇ≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
	WORD	BMinNGCount;	//çLàÊÇ≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ

	enum{
		_FromUnknown	=0
		,_FromLibrary	=1
		,_FromManual	=2
		,_FromParts		=3
		,_FromMPA		=4
		,_FromCAD		=5
	}GeneratedOriginOld;

    int32   CommonMoveID;
    WORD	CommonMoveDot;

    WORD	AdjustBlack;    //ãPìxï‚ê≥ÇÃâ∫å¿ïù
    WORD	AdjustWhite;    //ãPìxï‚ê≥ÇÃè„å¿ïù
    WORD	SelfSearch;     //é©å»íTçıÉhÉbÉgêî
	WORD	OmitVectorIndex;//íTçıã÷é~ï˚å¸	0xFFFFÇÃÇ∆Ç´ÅAã÷é~Ç»Çµ

	TrueColorBlockThreshold(TrueColorBlockItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
    
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

#pragma	pack(pop)

class   TrueColorBlockItem : public AlgorithmItemPI
{
public:
	enum ThresholdMode{
		_ThresholdNarrow
		,_ThresholdBroad
	};

    FlexArea    FLineEdge;
    FlexArea    FLineInside;

	QRgb		CenterBright;

	AlignmentPacket2D	*AVector;
  public:

	TrueColorBlockItem(void);
	TrueColorBlockItem(FlexArea &area);
    virtual	~TrueColorBlockItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new TrueColorBlockItem();	}
    virtual	void	MoveTo(int dx ,int dy)	override;
	const	TrueColorBlockThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const TrueColorBlockThreshold *)GetThresholdBaseReadable(base);	}
	TrueColorBlockThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (TrueColorBlockThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new TrueColorBlockThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
    TrueColorBlockItem &operator=(TrueColorBlockItem &src);
	void	CopyThreshold(TrueColorBlockItem &src);
	void	CopyThresholdOnly(TrueColorBlockItem &src);
	void	CopyArea(TrueColorBlockItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	SetInvertLogic(bool b)	override;
	virtual	bool	GetInvertLogic(void)	override;

	void	AddMasterColor(int Mergin);

  private:
	void	InitialConstructor(void);
	bool    ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,ColorLogic &Brightness
						  ,int Mergin
						  ,int OKDot ,int OKLength
						  ,WORD	MinNGCount
						  ,ThresholdMode NBMode);

	bool    ExecuteProcessingInnerWithoutSubtract(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,ColorLogic &Brightness
						  ,int Mergin
						  ,int OKDot,int OKLength
						  ,WORD	MinNGCount
						  ,ThresholdMode NBMode);
	bool    L3Remove(int mx ,int my
                           ,FlexArea &SubFLines
                           ,FlexArea &SubFLineEdge
                           ,FlexArea &SubFLineInside);

	void	Level3Inside(int mx ,int my
					,ColorLogic &Brightness
					,int Mergin
					,int &InsideSum);

	void	Level3Speedy(int mx,int my
					,ColorLogic &TmpBrightness
					,int Mergin
					,int &Sum);

	bool	CheckOnNG(int mx,int my ,int hx ,int hy
				, ColorLogic &Brightness
				,int Mergin
				, int OKDot,int OKLength
				,int &Sum
				,NPListPack<ResultPosList> &PosList
				,WORD MinNGCount
				,ThresholdMode NBMode);

	void	CheckOnNGInner1(int dx ,int dy
							,ColorLogic &Level
							,int Mergin
							,BYTE *pMap
							,int Lx ,int Ly ,int LByte,int starty);
	static	void  SearchAnalyzeNGHoleL(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHoleH(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2L(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2H(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	int		AnalyzeNGHole(int dx ,int dy,int x ,int y
							, ColorLogic &Level
							, BYTE *NGBmpL ,BYTE *NGBmpH ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot
							,int &Sum);

	int  AnalyzeNGHole(int dx ,int dy,int x ,int y
							, ColorLogic &Level
							, BYTE *NGBmp ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot,int &Sum);
	static	void  SearchAnalyzeNGHole(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);

	XYClass	*GetSWayListFirst(int ThreadNo,int selfSearch);
	void	SetSWayListToTop(int ThreadNo,int selfSearch,XYClass *w);
	TrueColorBlockLibNGTypeItem	*MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer);

public:
	QRgb	CalcCenterBright(ImageBuffer *ImageList[] ,int mx ,int my);
	void	MakeInsideEdgeArea(void);

	double	EnAverage(int mx,int my
						,ColorLogic &TmpBrightness);
};

class	TrueColorBlockLimitedMask : public AlgorithmItemPI
{
public:
	TrueColorBlockLimitedMask(void){}
    virtual	bool    Save(QIODevice *file);
    virtual	bool    Load(QIODevice *file,LayersBase *LBase);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
};


class   TrueColorBlockInPage : public AlgorithmInPagePI
{
	friend class	TrueColorBlockItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
	IntList	CommonMoveIDList;

	SearchWayList   *SWayListPerCPU;

public:
	TrueColorBlockInPage(AlgorithmBase *parent);
	~TrueColorBlockInPage(void);
	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			TrueColorBlockItem	*a=new TrueColorBlockItem();
			a->SetParent(this);
			return a;
		}

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);

	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	PickupTest(TrueColorBlockLibrary &LibData);
	void	GenerateBlocks(TrueColorBlockLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,int32 ItemID,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	CopyItemsFormDispatcherForParts(void)	override{}	//For skip
private:
	void	CreatePickupBmpBuff(void);
};

class	TrueColorBlockBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		TrueColorBlockNormal	;
	QColor		TrueColorBlockSelected	;
	QColor		TrueColorBlockActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;

	TrueColorBlockBase(LayersBase *Base);

	virtual	TrueColorBlockInPage	*NewChild(AlgorithmBase *parent)override{	return(new TrueColorBlockInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("TrueColorBlock");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigTrueColorBlock.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
};

//==================================================================================
class	TrueColorBlockHistogramListReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	TrueColorBlockHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TrueColorBlockHistogramListSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	ColorLogic	MasterColor;
	ColorLogic	TargetColor;

	TrueColorBlockHistogramListSend(void);

	void	ConstructList(TrueColorBlockHistogramListReq *reqPacket,TrueColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TrueColorBlockThresholdReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	TrueColorBlockThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TrueColorBlockThresholdSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	QRgb	CenterBright;
	ColorLogic	NInsColor;
	ColorLogic	BInsColor;

	ColorLogic	AbsNInsColor;
	ColorLogic	AbsBInsColor;
	double	Multiplier;
	WORD	NMinNGCount;	//ã∑àÊÇ≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
	WORD	BMinNGCount;	//çLàÊÇ≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
	WORD	BOKLength;		//çLàÊÇ≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
	WORD	NOKLength;		//ã∑àÊÇ≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj


	TrueColorBlockThresholdSend(void);

	void	ConstructList(TrueColorBlockThresholdReq *reqPacket,TrueColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TrueColorBlockReqTryThreshold
{
public:
	int32	GlobalPage;
	int		BlockItemID;	
	TrueColorBlockItem	Threshold;

	TrueColorBlockReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	TrueColorBlockSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInN;
	int		NGDotInB;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;

	TrueColorBlockSendTryThreshold(void);

	void	ConstructList(TrueColorBlockReqTryThreshold *reqPacket,TrueColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	TrueColorBlockChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	int32	Dx,Dy;

	TrueColorBlockChangeShift(void){}

	void	Reflect(TrueColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#define	SetIndependentItemDataCommand_OnlyOne		1
#define	SetIndependentItemDataCommand_All			2
#define	TrueColorBlockHistogramListReqCommand		3
#define	TrueColorBlockHistogramListSendCommand		4
#define	TrueColorBlockReqThresholdReqCommand		5
#define	TrueColorBlockReqThresholdSendCommand		6
#define	TrueColorBlockReqTryThresholdCommand		7
#define	TrueColorBlockSendTryThresholdCommand		8
#define	TrueColorBlockReqChangeShiftCommand			9
#define	SetIndependentItemAddInPlaceColor			10

//===================================================================================

class	CmdGetTrueColorBlockLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetTrueColorBlockLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetTrueColorBlockLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetTrueColorBlockLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetTrueColorBlockLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetTrueColorBlockLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempTrueColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempTrueColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempTrueColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearTrueColorBlockLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearTrueColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTrueColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertTrueColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertTrueColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertTrueColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateTrueColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateTrueColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateTrueColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadTrueColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadTrueColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadTrueColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteTrueColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteTrueColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteTrueColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestTrueColorBlockPacket : public GUIDirectMessage
{
public:
	//TrueColorBlockLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;

	CmdPickupTestTrueColorBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestTrueColorBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateTrueColorBlockPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateTrueColorBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateTrueColorBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempTrueColorBlockItemPacket : public GUIDirectMessage
{
public:
	TrueColorBlockItem	*Point;
	CmdCreateTempTrueColorBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempTrueColorBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromTrueColorBlockItemPacket : public GUIDirectMessage
{
public:
	TrueColorBlockItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromTrueColorBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromTrueColorBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteTrueColorBlockItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteTrueColorBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteTrueColorBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadTrueColorBlockItemPacketFromByteArray : public GUIDirectMessage
{
public:
	TrueColorBlockItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadTrueColorBlockItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadTrueColorBlockItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedTrueColorBlockFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedTrueColorBlockFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedTrueColorBlockFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestTrueColorBlockPacket: public GUIDirectMessage
{
public:
	CmdClearTestTrueColorBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestTrueColorBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdTrueColorBlockInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<TrueColorBlockInfoList>	*TrueColorBlockInfos;
	CmdTrueColorBlockInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdTrueColorBlockInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetTrueColorBlockFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	TrueColorBlockItem	*TrueColorBlockInfoOnMouse;

	CmdGetTrueColorBlockFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetTrueColorBlockFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTrueColorBlockItem: public GUIDirectMessage
{
public:
	TrueColorBlockItem	*TrueColorBlock;
	CmdCreateTrueColorBlockItem(LayersBase *base):GUIDirectMessage(base){	TrueColorBlock=NULL;	}
	CmdCreateTrueColorBlockItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	TrueColorBlock=NULL;	}
};

class	CmdFindTrueColorBlockItem: public GUIDirectMessage
{
public:
	int	LocalX,LocalY;
	TrueColorBlockItem	*TrueColorBlock;
	CmdFindTrueColorBlockItem(LayersBase *base):GUIDirectMessage(base){	TrueColorBlock=NULL;	}
	CmdFindTrueColorBlockItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	TrueColorBlock=NULL;	}
};


#endif