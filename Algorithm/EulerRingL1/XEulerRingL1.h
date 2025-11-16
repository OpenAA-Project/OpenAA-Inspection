/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1\XEulerRingL1.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XEulerRingL1_H)
#define	XEulerRingL1_H

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
//#include "XPropertyEulerRingL1Packet.h"
#include "XStandardCommand.h"

#define	EulerRingL1Version	3


class   AlignmentInLayer;
class	XAlignmentArea;
class	EulerRingL1Library;
class	EulerRingL1Base;
class	EulerRingL1Item;
class	EulerRingL1InLayer;
class	EulerRingL1InPage;
class	SetThresholdEulerRingL1Info;


#define	Hist_EulerRingL1_HoleDiameter			1
#define	Hist_EulerRingL1_HoleShift				2
#define	Hist_EulerRingL1_HoleCenterBrightness	3
#define	Hist_EulerRingL1_RingCenterBrightness	4
#define	Hist_EulerRingL1_RingLowBrightness		5
#define	Hist_EulerRingL1_RingHighBrightness		6


class	EulerRingL1Threshold : public AlgorithmThreshold
{
public:
	struct{
		bool	ModeEnabled					:1;
		bool	ModeAbsoluteBright			:1;
		bool	ModeMakeDynamicMask			:1;
		bool	ModeEnableHoleCheck			:1;
		bool	ModeCenterBrightFromParts	:1;
		bool	ModeEnableOpenRingCheck		:1;
		bool	ModeEnableInRound			:1;			//When hole is round in generation , it's TRUE
		int		Dummy						:25;
	}PointMove;

	short		DarkWidth;		//For ring brightness
	short		LightWidth;
	int32		MinHoleDiameter;
	int32		MaxHoleDiameter;
	double		MaxShiftHole;
	int8		ConnectLen;		//ÇmÇfê⁄ë±ãóó£
	int32		ExpandForDynamicMask;

    WORD		AdjustBlack;	//For ring brightness
    WORD		AdjustWhite; 
	WORD		SearchDot;
	short		HoleBrightnessAsReference;

	EulerRingL1Threshold(EulerRingL1Item *parent);

	virtual	void	RegistHist(void)					override;
	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
    
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class   EulerRingL1Item : public AlgorithmItemPLITemplate<EulerRingL1InLayer,EulerRingL1InPage,EulerRingL1Base>
{
	BYTE	**BmpMap;
	BYTE	**TmpMap;
	BYTE	**MaskMap;
	int		XLen;
	int		XByte;
	int		YLen;
	int		MapXPos,MapYPos;
	int		MasterCx,MasterCy;
	int		HoleShiftX;
	int		HoleShiftY;
public:
	AlignmentPacket2D	*AVector;
	WORD				CenterBright;
	WORD				CenterTargetBright;
	double	MasterHoleDiameter;

	double	ResultHoleShift;
	double	ResultHoleDiameter;
	bool	TestMode;

public:

	EulerRingL1Item(void);
	EulerRingL1Item(FlexArea &area);
	virtual	~EulerRingL1Item(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new EulerRingL1Item();	}
	const	EulerRingL1Threshold	*GetThresholdR(LayersBase *base=NULL){	return (const EulerRingL1Threshold *)GetThresholdBaseReadable(base);	}
	EulerRingL1Threshold			*GetThresholdW(LayersBase *base=NULL){	return (EulerRingL1Threshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new EulerRingL1Threshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	EulerRingL1Item &operator=(const AlgorithmItemRoot &src)	override;
	void	CopyThreshold(EulerRingL1Item &src);
	void	CopyThresholdOnly(EulerRingL1Item &src);
	void	CopyArea(EulerRingL1Item &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)		override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)		override;

	int		CalcCenterBright(ImageBuffer &IBuff,int dx,int dy);
	void	SetThresholdFromCommon(SetThresholdEulerRingL1Info *Info);

private:
	void		MakeHoleMask(FlexArea *HoleF,int mx,int my);
	ExeResult	ExecutePreProcessingInside(int ThreadNo,ResultInItemRoot *Res ,int mx ,int my,int AlignedMx ,int AlignedMy);
	PureFlexAreaList *ExecutePreProcessingInsise	(ResultInItemRoot *Res ,int mx ,int my,int AlignedMx ,int AlignedMy
											,bool ModeMakeHoleMask
											,PureFlexAreaListContainer &FPack
											,ExeResult &Ret);
	void	Search(int mx ,int my ,int &Dx ,int &Dy);
	double	CalcSearchUpper(ImageBuffer &TBuff ,int cx,int cy);
	double	CalcSearchLeft (ImageBuffer &TBuff ,int cx,int cy);
	double	CalcSearchRight(ImageBuffer &TBuff ,int cx,int cy);
	double	CalcSearchLower(ImageBuffer &TBuff ,int cx,int cy);
	bool	MatchDetail(ImageBuffer &TBuff,int cx,int cy,int Rx ,int Ry ,double &Rate);
	void	CalcRingThreshold(ImageBuffer &IBuffer ,int mx,int my ,int HoleBrightnessAsReference ,int &BrightWidthL,int &BrightWidthH);
};

class	EulerRingL1Searcher
{
public:
	int		R;
	int		Vy1,Vy2;
	int		Hx1,Hx2;
	int		Skip;
	double	A,AA;
	int		VNumb;
	int		HNumb;
	BYTE	*VData;
	BYTE	*HData;

	struct	MatchingDot
	{
		int	x,y;
	};
	struct	MatchingDot	*MDimHole;
	struct	MatchingDot	*MDimRing;
	int		MDotSecondNumb;
	double	SA,SAA;

	EulerRingL1Searcher(void);
	virtual	~EulerRingL1Searcher(void);

	void	ExecuteInitialAfterEdit(int radius,ExecuteInitialAfterEditInfo &EInfo);
	double	MatchFirst	(EulerRingL1InLayer *Parent ,ImageBuffer &IBuff ,int dx ,int dy);
	double	MatchSecond	(EulerRingL1InLayer *Parent ,ImageBuffer &IBuff ,int dx ,int dy);
};



class   EulerRingL1InLayer : public AlgorithmInLayerPLITemplate<EulerRingL1Item,EulerRingL1InPage,EulerRingL1Base>
{
	friend class	EulerRingL1Item;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

public:
	EulerRingL1Searcher	*DimSearcher;
	int					DimSearcherNumb;

public:
	EulerRingL1InLayer(AlgorithmInPageRoot *parent);
	~EulerRingL1InLayer(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			EulerRingL1Item	*a=new EulerRingL1Item();	
			a->SetParent(this);
			return a;
		}
	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item)			override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override;

	void	PickupTest(EulerRingL1Library &LibData);
	void	GenerateBlocks(EulerRingL1Library *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	Draw(QImage &pnt,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	MoveFromPipe(GeneralPipeInfo &Info);
private:
	void	CreatePickupBmpBuff(void);
};

class   EulerRingL1InPage : public AlgorithmInPagePLITemplate<EulerRingL1Item,EulerRingL1InLayer,EulerRingL1Base>
{

public:
	EulerRingL1InPage(AlgorithmBase *parent);
	~EulerRingL1InPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new EulerRingL1InLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)			override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;
private:

};
class	EulerRingL1Base	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		EulerRingL1Normal	;
	QColor		EulerRingL1Selected	;
	QColor		EulerRingL1Active	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;
	double		RoundRateInHole;
	int			MaxRadius;

	EulerRingL1Base(LayersBase *Base);
	virtual	EulerRingL1InPage	*NewChild(AlgorithmBase *parent)	override{	return(new EulerRingL1InPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("EulerRingL1");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigEulerRingL1.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID 
												,ResultBaseForAlgorithmRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)	override;
};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	EulerRingL1HistogramListReqCommand				3
#define	EulerRingL1HistogramListSendCommand				4
#define	EulerRingL1ReqThresholdReqCommand				5
#define	EulerRingL1ReqThresholdSendCommand				6
#define	EulerRingL1ReqTryThresholdCommand				7
#define	EulerRingL1SendTryThresholdCommand				8
#define	EulerRingL1ReqChangeShiftCommand				9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================

class	EulerRingL1DrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
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

	EulerRingL1DrawAttr(void):ServiceForLayers(NULL){}
	EulerRingL1DrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	EulerRingL1DrawAttr(LayersBase *Base
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

	EulerRingL1DrawAttr	&operator=(EulerRingL1DrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	EulerRingL1DrawAttr	&EulerRingL1DrawAttr::operator=(EulerRingL1DrawAttr &src)
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
inline	bool	EulerRingL1DrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	EulerRingL1DrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}


//==========================================================================
class	EulerRingL1InfoList : public NPList<EulerRingL1InfoList>
{
public:
	int		LibID;
	IntList	EulerRingL1Count;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	EulerRingL1InfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(EulerRingL1Count.Save(f)==false)
		return false;
	return true;
}
inline	bool	EulerRingL1InfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(EulerRingL1Count.Load(f)==false)
		return false;
	return true;
}


//==================================================================================
class	EulerRingL1ChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	int32	Dx,Dy;

	EulerRingL1ChangeShift(void){}

	void	Reflect(EulerRingL1Base *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingL1HistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	EulerRingL1HistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingL1HistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMaster[256];
	int		ListTarget[256];
	WORD	CenterBright;
	WORD	CenterTargetBright;

	EulerRingL1HistogramListSend(void);

	void	ConstructList(EulerRingL1HistogramListReq *reqPacket,EulerRingL1Base *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingL1ThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	EulerRingL1ThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingL1ThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	WORD	CenterBright;
	WORD	CenterTargetBright;

	short	DarkWidth;		//For ring brightness
	short	LightWidth;
	int		MinHoleDiameter;
	int		MaxHoleDiameter;
	double	MaxShiftHole;
	int8	ConnectLen;		//ÇmÇfê⁄ë±ãóó£
	int		ExpandForDynamicMask;

    WORD	AdjustBlack;	//For ring brightness
    WORD	AdjustWhite;
	WORD	SearchDot;
	short	HoleBrightnessAsReference;

	int		AbsBrightWidthL;
	int		AbsBrightWidthH;
	int		BrightWidthL;
	int		BrightWidthH;

	EulerRingL1ThresholdSend(void);

	void	ConstructList(EulerRingL1ThresholdReq *reqPacket,EulerRingL1Base *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingL1ReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;	
	EulerRingL1Item	Threshold;

	EulerRingL1ReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	EulerRingL1SendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	double	MasterHoleDiameter;
	double	HoleDiameter;
	double	HoleShift;
	int		Ring;

	EulerRingL1SendTryThreshold(void);
	~EulerRingL1SendTryThreshold(void);

	void	ConstructList(EulerRingL1ReqTryThreshold *reqPacket,EulerRingL1Base *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CmdGetEulerRingL1LibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetEulerRingL1LibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEulerRingL1LibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEulerRingL1LibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetEulerRingL1LibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEulerRingL1LibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempEulerRingL1LibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempEulerRingL1LibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempEulerRingL1LibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearEulerRingL1LibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearEulerRingL1LibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearEulerRingL1LibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertEulerRingL1LibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertEulerRingL1LibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertEulerRingL1LibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateEulerRingL1LibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateEulerRingL1LibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateEulerRingL1LibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadEulerRingL1LibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadEulerRingL1LibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadEulerRingL1LibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteEulerRingL1LibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteEulerRingL1LibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteEulerRingL1LibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestEulerRingL1Packet : public GUIDirectMessage
{
public:
	//EulerRingL1Library	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;
	IntList			LayerList;

	CmdPickupTestEulerRingL1Packet(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestEulerRingL1Packet(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateEulerRingL1Packet : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	IntList		LayerList;

	CmdGenerateEulerRingL1Packet(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateEulerRingL1Packet(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempEulerRingL1ItemPacket : public GUIDirectMessage
{
public:
	EulerRingL1Item	*Point;
	CmdCreateTempEulerRingL1ItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempEulerRingL1ItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromEulerRingL1ItemPacket : public GUIDirectMessage
{
public:
	EulerRingL1Item	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromEulerRingL1ItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromEulerRingL1ItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteEulerRingL1ItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;

	CmdAddByteEulerRingL1ItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteEulerRingL1ItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadEulerRingL1ItemPacketFromByteArray : public GUIDirectMessage
{
public:
	EulerRingL1Item	*BItemPoint;
	QByteArray	Buff;
	CmdLoadEulerRingL1ItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadEulerRingL1ItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedEulerRingL1FromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedEulerRingL1FromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedEulerRingL1FromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestEulerRingL1Packet: public GUIDirectMessage
{
public:
	CmdClearTestEulerRingL1Packet(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestEulerRingL1Packet(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdEulerRingL1InfoListPacket: public GUIDirectMessage
{
public:
	NPListPack<EulerRingL1InfoList>	*EulerRingL1Infos;
	CmdEulerRingL1InfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdEulerRingL1InfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEulerRingL1FromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	EulerRingL1Item	*EulerRingL1InfoOnMouse;

	CmdGetEulerRingL1FromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEulerRingL1FromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateEulerRingL1Item: public GUIDirectMessage
{
public:
	EulerRingL1Item	*EulerRingL1;
	CmdCreateEulerRingL1Item(LayersBase *base):GUIDirectMessage(base){	EulerRingL1=NULL;	}
	CmdCreateEulerRingL1Item(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//==========================================================================



#endif