/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorBlockInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XCOLORBOCKINSPECTION_H)
#define	XCOLORBOCKINSPECTION_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XBlockSearchWay.h"
#include "XColorSpace.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XPropertyColorBlockPacket.h"
#include "XColorBlockLibrary.h"
#include "XStandardCommand.h"

#define	ColorBlockInspectionVersion	10004


class   AlignmentInLayer;
class	XAlignmentArea;
class	ColorBlockLibrary;
class	ColorBlockBase;
class	ColorBlockItem;

#pragma	pack(push,1)

class	ColorBlockThreshold : public AlgorithmThreshold
{
public:
	class	ThresholdByLayer
	{
	public:
		WORD	NBrightWidthL;	//ã∑àÊÇÃà√ë§ãPìxïù
		WORD	NBrightWidthH;	//ã∑àÊÇÃñæë§ãPìxïù
		DWORD	NOKDotL;		//ã∑àÊÇÃà√ë§ÇnÇjÉhÉbÉgêî
		DWORD	NOKDotH;		//ã∑àÊÇÃñæë§ÇnÇjÉhÉbÉgêî
		WORD	BBrightWidthL;	//çLàÊÇÃà√ë§ãPìxïù
		WORD	BBrightWidthH;	//çLàÊÇÃñæë§ãPìxïù
		DWORD	BOKDotL;		//çLàÊÇÃà√ë§ÇnÇjÉhÉbÉgêî
		DWORD	BOKDotH;		//çLàÊÇÃñæë§ÇnÇjÉhÉbÉgêî

	    WORD	AdjustBlack;    //ãPìxï‚ê≥ÇÃâ∫å¿ïù
		WORD	AdjustWhite;    //ãPìxï‚ê≥ÇÃè„å¿ïù

		WORD	NMinNGCountL;	//ã∑àÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
		WORD	NMinNGCountH;	//ã∑àÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
		WORD	BMinNGCountL;	//çLàÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
		WORD	BMinNGCountH;	//çLàÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ

		WORD	BOKLengthL;		//çLàÊÇÃñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
		WORD	BOKLengthH;		//çLàÊÇÃñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
		WORD	NOKLengthL;		//ã∑àÊÇÃà√ë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
		WORD	NOKLengthH;		//ã∑àÊÇÃñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj

		ThresholdByLayer(void);
		ThresholdByLayer	&operator=(const ThresholdByLayer &src);
		bool				operator==(const ThresholdByLayer &src)	const ;
		bool				operator!=(const ThresholdByLayer &src)	const {	return !operator==(src);	}
		virtual	bool	Save(QIODevice *f)				;
		virtual	bool	Load(QIODevice *f,int Ver)				;
		virtual	void	FromLibrary(ColorBlockLibrary::InspectionData *src);
		virtual	void	ToLibrary(ColorBlockLibrary::InspectionData *Dest);
	};

	struct{
		bool	ModeEnabled				:1;
		bool	ModeAdjustable			:1;
		bool	ModeAbsoluteBright		:1;
		bool	ModeCommonMovable		:1;
		bool	ModeNGCluster			:1;
		bool	ModeDiffer				:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeOnlyMatching		:1;
		bool    ModeWhiteMask			:1;
		bool    ModeBlackMask			:1;
		bool	ModeCalcBothBN			:1;
	}PointMove;

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
    WORD	SelfSearch;     //é©å»íTçıÉhÉbÉgêî

	WORD				OmitVectorIndex;//íTçıã÷é~ï˚å¸	0xFFFFÇÃÇ∆Ç´ÅAã÷é~Ç»Çµ
	ThresholdByLayer	InsR,InsG,InsB;

	ColorBlockThreshold(ColorBlockItem *parent);

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

class   ColorBlockItem : public AlgorithmItemPI
{
public:
	enum ThresholdMode{
		_ThresholdNarrow
		,_ThresholdBroad
	};

    FlexArea    FLineEdge;
    FlexArea    FLineInside;

	WORD	CenterBrightR;
	WORD	CenterBrightG;
	WORD	CenterBrightB;	//Center brightness in MasterImage

	WORD	CenterBrightTargetR;
	WORD	CenterBrightTargetG;
	WORD	CenterBrightTargetB;	//Center brightness in TargetImage

	AlignmentPacket2D	*AVector;
  public:

	ColorBlockItem(void);
	ColorBlockItem(FlexArea &area);
    virtual	~ColorBlockItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ColorBlockItem();	}
    virtual	void    MoveTo(int dx ,int dy)	override;
	const	ColorBlockThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ColorBlockThreshold *)GetThresholdBaseReadable(base);	}
	ColorBlockThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ColorBlockThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ColorBlockThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
    ColorBlockItem &operator=(ColorBlockItem &src);
	void	CopyThreshold(ColorBlockItem &src);
	void	CopyThresholdOnly(ColorBlockItem &src);
	void	CopyArea(ColorBlockItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

  private:
	void	InitialConstructor(void);
	bool	ExecuteProcessingInside(int ThreadNo,ResultInItemRoot *Res
											 ,int mx ,int my
											 ,int CenterBright ,ColorBlockThreshold::ThresholdByLayer &LThre
											 ,int MError
											 ,ImageBuffer &MasterBuff ,ImageBuffer &TargetBuff
											 );

	bool    ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthRL ,int BrightWidthRH ,int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
						  ,int BrightWidthGL ,int BrightWidthGH ,int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
						  ,int BrightWidthBL ,int BrightWidthBH ,int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
						  ,WORD  &CenterBrightR,WORD  &CenterBrightG,WORD  &CenterBrightB
						  ,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
							,WORD	RMinNGCountL,WORD RMinNGCountH
							,WORD	GMinNGCountL,WORD GMinNGCountH
							,WORD	BMinNGCountL,WORD BMinNGCountH
							,ThresholdMode NBMode);

	bool    ExecuteProcessingInnerWithoutSubtract(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthRL ,int BrightWidthRH ,int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
						  ,int BrightWidthGL ,int BrightWidthGH ,int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
						  ,int BrightWidthBL ,int BrightWidthBH ,int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
						  ,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
							,WORD	RMinNGCountL,WORD RMinNGCountH
							,WORD	GMinNGCountL,WORD GMinNGCountH
							,WORD	BMinNGCountL,WORD BMinNGCountH
							,ThresholdMode NBMode);

	bool    L3Remove(int mx ,int my
                           ,FlexArea &SubFLines
                           ,FlexArea &SubFLineEdge
                           ,FlexArea &SubFLineInside);

	void	Level3Inside(int mx ,int my
					,int TmpBrightWidthRL ,int TmpBrightWidthRH
					,int TmpBrightWidthGL ,int TmpBrightWidthGH
					,int TmpBrightWidthBL ,int TmpBrightWidthBH
					,int &InsideSumRL,int &InsideSumRH
					,int &InsideSumGL,int &InsideSumGH
					,int &InsideSumBL,int &InsideSumBH
					,ImageBuffer *TargetBuff[]);

	void	Level3Speedy(int mx,int my
					,int TmpBrightWidthRL ,int TmpBrightWidthRH
					,int TmpBrightWidthGL ,int TmpBrightWidthGH
					,int TmpBrightWidthBL ,int TmpBrightWidthBH
					,int &SumRL,int &SumRH
					,int &SumGL,int &SumGH
					,int &SumBL,int &SumBH
					,ImageBuffer *TargetBuff[]);

	void	Level3OnlyEdge(int mx,int my
					,int TmpBrightWidthRL ,int TmpBrightWidthRH
					,int TmpBrightWidthGL ,int TmpBrightWidthGH
					,int TmpBrightWidthBL ,int TmpBrightWidthBH
					,int &SumRL,int &SumRH
					,int &SumGL,int &SumGH
					,int &SumBL,int &SumBH
					,ImageBuffer *TargetBuff[]);

	bool	CheckOnNG(int mx,int my ,int hx ,int hy
				,int TmpBrightWidthRL,int TmpBrightWidthRH , int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
				,int TmpBrightWidthGL,int TmpBrightWidthGH , int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
				,int TmpBrightWidthBL,int TmpBrightWidthBH , int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,short &Error
				,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
				,WORD	RMinNGCountL,WORD RMinNGCountH
				,WORD	GMinNGCountL,WORD GMinNGCountH
				,WORD	BMinNGCountL,WORD BMinNGCountH
				,ThresholdMode NBMode);

	bool	CheckOnNGAll(int mx,int my ,int hx ,int hy
				,int TmpBrightWidthRL,int TmpBrightWidthRH , int OKDotRL ,int OKDotRH ,WORD OKLengthRL ,WORD OKLengthRH
				,int TmpBrightWidthGL,int TmpBrightWidthGH , int OKDotGL ,int OKDotGH ,WORD OKLengthGL ,WORD OKLengthGH
				,int TmpBrightWidthBL,int TmpBrightWidthBH , int OKDotBL ,int OKDotBH ,WORD OKLengthBL ,WORD OKLengthBH
				,int &SumL,int &SumH
				,NPListPack<ResultPosList> &PosList
				,short &Error
				,ImageBuffer *MasterBuff[] ,ImageBuffer *TargetBuff[]
				,WORD RMinNGCountL,WORD RMinNGCountH
				,WORD GMinNGCountL,WORD GMinNGCountH
				,WORD BMinNGCountL,WORD BMinNGCountH
				,ThresholdMode NBMode);

	void	CheckOnNGInner1(int dx ,int dy
							,int LLevel ,int HLevel
							,BYTE *pMapL ,BYTE *pMapH
							,int Lx ,int Ly ,int LByte,int starty
							,ImageBuffer &TargetBuff);
	void	CheckOnNGInner1All(int dx ,int dy
                            ,int LLevelR ,int HLevelR
                            ,int LLevelG ,int HLevelG
                            ,int LLevelB ,int HLevelB
                            ,BYTE *pMapL ,BYTE *pMapH
                            ,int Lx ,int Ly ,int LByte,int starty
							,ImageBuffer *TargetBuff[]);
	void	CheckOnNGInner2(int dx ,int dy
							,int LLevel ,int HLevel
							,BYTE *pMapL ,BYTE *pMapH
							,int Lx ,int Ly ,int LByte,int starty
							,ImageBuffer &MasterBuff ,ImageBuffer &TargetBuff);
	void	CheckOnNGInner2All(int dx ,int dy
							,int LLevelR ,int HLevelR
                            ,int LLevelG ,int HLevelG
                            ,int LLevelB ,int HLevelB
                            ,BYTE *pMapL ,BYTE *pMapH
                            ,int Lx ,int Ly ,int LByte,int starty
							,ImageBuffer *MasterBuff[],ImageBuffer *TargetBuff[]);

	static	void  SearchAnalyzeNGHoleL(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHoleH(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2L(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2H(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	int		AnalyzeNGHole(int dx ,int dy,int x ,int y
							, int LLevel ,int HLevel
							, BYTE *NGBmpL ,BYTE *NGBmpH ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDotL ,int OKDotH
							,int &SumL  ,int &SumH );

	int		AnalyzeNGHole(int dx ,int dy,int x ,int y
							, int LLevel ,int HLevel
							, BYTE *NGBmp ,int NGBmpX ,int NGBmpY
							,int &Cx ,int &Cy
							,int OKDot,int &Sum
							,ImageBuffer &MasterBuff,ImageBuffer &TargetBuff);

	static	void  SearchAnalyzeNGHole(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);
	static	void  SearchAnalyzeNGHole2(struct AnalyzeNGHoleClass *LData,int x ,int y ,BYTE *B);

	XYClass	*GetSWayListFirst(int ThreadNo,int selfSearch);
	void	SetSWayListToTop(int ThreadNo,int selfSearch,XYClass *w);
	ColorBlockLibNGTypeItem	*MakeNGType(FlexArea &NGArea ,LibNGTypeInAlgorithm &NGContainer);

public:
	void	CalcCenterBright(ImageBuffer *IBuff[] ,int mx ,int my 
							 ,WORD &CenterBrightR,WORD &CenterBrightG,WORD &CenterBrightB);
	void	MakeInsideEdgeArea(void);

	void	EnAverage(int mx,int my
						,int &TmpBrightWidthLR,int &TmpBrightWidthHR
						,int &TmpBrightWidthLG,int &TmpBrightWidthHG
						,int &TmpBrightWidthLB,int &TmpBrightWidthHB
						,ImageBuffer *TargetBuff[]);
	void	EnAverage(int mx,int my
						,WORD &TmpBrightWidthLR,WORD &TmpBrightWidthHR
						,WORD &TmpBrightWidthLG,WORD &TmpBrightWidthHG
						,WORD &TmpBrightWidthLB,WORD &TmpBrightWidthHB
						,ImageBuffer *TargetBuff[]);
};

class	ColorBlockLimitedMask : public AlgorithmItemPI
{
public:
	ColorBlockLimitedMask(void){}

    virtual	bool    Save(QIODevice *file);
    virtual	bool    Load(QIODevice *file,LayersBase *LBase);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
};

class   ColorBlockInPage : public AlgorithmInPagePI
{
	friend class	ColorBlockItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
	IntList	CommonMoveIDList;

	SearchWayList   *SWayListPerCPU;
public:
	ColorBlockInPage(AlgorithmBase *parent);
	~ColorBlockInPage(void);

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);

	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	PickupTest(ColorBlockLibrary &LibData);
	void	GenerateBlocks(ColorBlockLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ColorBlockItem		*CreateItem(int ItemClassType=0)	override
		{	
			ColorBlockItem	*a=new ColorBlockItem();
			a->SetParent(this);
			return a;
		}
    virtual	bool			Save(QIODevice *f)	override;
    virtual	bool			Load(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	CopyItemsFormDispatcherForParts(void)	override{}	//For skip
private:
	void	CreatePickupBmpBuff(void);
};

class	ColorBlockBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		ColorBlockNormal	;
	QColor		ColorBlockSelected	;
	QColor		ColorBlockActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;

	ColorBlockBase(LayersBase *Base);
	virtual	ColorBlockInPage	*NewChild(AlgorithmBase *parent)	override{	return(new ColorBlockInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)			override{	return QString("ColorBlockInspection");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigColorBlock.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};

//==================================================================================
class	ColorBlockHistogramListReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ColorBlockHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ColorBlockHistogramListSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMasterR[256];
	int		ListTargetR[256];
	int		ListMasterG[256];
	int		ListTargetG[256];
	int		ListMasterB[256];
	int		ListTargetB[256];

	ColorBlockHistogramListSend(void);

	void	ConstructList(ColorBlockHistogramListReq *reqPacket,ColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ColorBlockThresholdReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ColorBlockThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ColorBlockThresholdSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	class	ColorBlockThresholdSendClass
	{
	public:
		WORD	CenterBright;
		WORD	CenterTargetBright;
		short	NBrightWidthL;		//ã∑àÊÇÃà√ë§ãPìxïù
		short	NBrightWidthH;		//ã∑àÊÇÃñæë§ãPìxïù
		short	BBrightWidthL;		//çLàÊÇÃà√ë§ãPìxïù
		short	BBrightWidthH;		//çLàÊÇÃñæë§ãPìxïù

		short	AbsNBrightWidthL;	//ã∑àÊÇÃà√ë§ãPìxïù
		short	AbsNBrightWidthH;	//ã∑àÊÇÃñæë§ãPìxïù
		short	AbsBBrightWidthL;	//çLàÊÇÃà√ë§ãPìxïù
		short	AbsBBrightWidthH;	//çLàÊÇÃñæë§ãPìxïù

		WORD	NMinNGCountL;	//ã∑àÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
		WORD	NMinNGCountH;	//ã∑àÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
		WORD	BMinNGCountL;	//çLàÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ
		WORD	BMinNGCountH;	//çLàÊÇÃà√ë§Ç≈Ç±ÇÃå¬êîà»è„ÇÃÇmÇfå¬êîÇ™Ç†ÇÍÇŒÇmÇfÇ…Ç∑ÇÈ

		WORD	BOKLengthL;		//çLàÊÇÃñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
		WORD	BOKLengthH;		//çLàÊÇÃñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
		WORD	NOKLengthL;		//ã∑àÊÇÃà√ë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
		WORD	NOKLengthH;		//ã∑àÊÇÃñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj

		ColorBlockThresholdSendClass(void);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
		void	Transform(ColorBlockThreshold::ThresholdByLayer &Ins
						,int CenterBright 
						,ColorBlockItem *BItem
						,ImageBuffer &TargetBuff,int dx,int dy);
	};
	ColorBlockThresholdSendClass	RRes,GRes,BRes;

	ColorBlockThresholdSend(void);

	void	ConstructList(ColorBlockThresholdReq *reqPacket,ColorBlockBase *Base,ImageBuffer *TargetImageList[]);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	ColorBlockReqTryThreshold
{
public:
	int32	GlobalPage;
	int		BlockItemID;	
	ColorBlockItem	Threshold;

	ColorBlockReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	ColorBlockSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInNDark;
	int		NGDotInNBright;
	int		NGDotInBDark;
	int		NGDotInBBright;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;
	ResultInItemRoot	*Result;

	ColorBlockSendTryThreshold(void);
	~ColorBlockSendTryThreshold(void);

	void	ConstructList(ColorBlockReqTryThreshold *reqPacket,ColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ColorBlockChangeShift
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	int32	Dx,Dy;

	ColorBlockChangeShift(void){}

	void	Reflect(ColorBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	BlockHistogramListReqCommand			3
#define	BlockHistogramListSendCommand			4
#define	BlockReqThresholdReqCommand				5
#define	BlockReqThresholdSendCommand			6
#define	BlockReqTryThresholdCommand				7
#define	BlockSendTryThresholdCommand			8
#define	ColorBlockReqChangeShiftCommand			9

//===================================================================================

class	CmdGetColorBlockLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetColorBlockLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorBlockLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetColorBlockLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetColorBlockLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorBlockLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearColorBlockLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteColorBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteColorBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteColorBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestColorBlockPacket : public GUIDirectMessage
{
public:
	//ColorBlockLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;

	CmdPickupTestColorBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestColorBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateColorBlockPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateColorBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateColorBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempColorBlockItemPacket : public GUIDirectMessage
{
public:
	ColorBlockItem	*Point;
	CmdCreateTempColorBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempColorBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromColorBlockItemPacket : public GUIDirectMessage
{
public:
	ColorBlockItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromColorBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromColorBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteColorBlockItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteColorBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteColorBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadColorBlockItemPacketFromByteArray : public GUIDirectMessage
{
public:
	ColorBlockItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadColorBlockItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadColorBlockItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedColorBlockFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedColorBlockFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedColorBlockFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestColorBlockPacket: public GUIDirectMessage
{
public:
	CmdClearTestColorBlockPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestColorBlockPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdColorBlockInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<ColorBlockInfoList>	*ColorBlockInfos;
	CmdColorBlockInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdColorBlockInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetColorBlockFromList: public GUIDirectMessage
{
public:
	IntClass	CurrentItem;
	int			LocalPage;
	ColorBlockItem	*ColorBlockInfoOnMouse;

	CmdGetColorBlockFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorBlockFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateColorBlockItem: public GUIDirectMessage
{
public:
	ColorBlockItem	*ColorBlock;
	CmdCreateColorBlockItem(LayersBase *base):GUIDirectMessage(base){	ColorBlock=NULL;	}
	CmdCreateColorBlockItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ColorBlock=NULL;	}
};
class	CmdFindColorBlockItem: public GUIDirectMessage
{
public:
	int	LocalX,LocalY;
	ColorBlockItem	*ColorBlock;
	CmdFindColorBlockItem(LayersBase *base):GUIDirectMessage(base){	ColorBlock=NULL;	}
	CmdFindColorBlockItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ColorBlock=NULL;	}
};



#endif