#pragma once


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include <QIODevice>
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"

#define	PalletizeVersion	4

class	PalletizeItem;
class	PalletizeRegulation;
class	PalletizeInPage;
class	PalletizeBase;
class	PalletizeLibrary;

class	PalletizeItem;
class	PalletizeInPage;
class	MatchingResultList;
class	PalletizingBackItem;
class	RotatedMatchingPattern;

//==========================================================================================

class	PalletizeDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ShowItems;
	bool	ShowResult;

	PalletizeDrawAttr(LayersBase *Base):ServiceForLayers(Base){	ShowItems=true;	ShowResult=true;	}
	PalletizeDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	PalletizeDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	PalletizeDrawAttr	&operator=(PalletizeDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	PalletizeDrawAttr::PalletizeDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	ShowItems=true;
	ShowResult=true;
}

inline	PalletizeDrawAttr	&PalletizeDrawAttr::operator=(PalletizeDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	ShowItems		=src.ShowItems;
	return *this;
}

inline	bool	PalletizeDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	if(::Save(f,ShowItems)==false)
		return false;
	return true;
}
inline	bool	PalletizeDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	if(::Load(f,ShowItems)==false)
		return false;
	return true;
}

//========================================================================================
class	PalletizeThreshold : public AlgorithmThreshold
{
public:
	double	AngleRange;		//Degree
	double	MinZoomSize;
	double	MaxZoomSize;
	int		PieceSize;
	int		SearchDotPiece;
	double	ThresholdV;
	int		MaxCountOfPiece;
	double	ThreshCoeff;
	int		SearchNearBy;
	int		MaxShift;

	PalletizeThreshold(PalletizeItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

};

class MatchingLineBase : public NPList<MatchingLineBase>
{
protected:
	WORD	PosX,PosY;
	WORD	LineLen;
	BYTE	*Data;

	int32	A;
	int32	AA;
	double	AvrS;
	double	AASS;
	double	RLineLen;
public:
	MatchingLineBase(void);
	virtual	~MatchingLineBase(void);

	virtual	int	GetLineClass(void)	=0;

	virtual	double	Match(ImageBuffer *TBuff,int dx,int dy)=0;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)=0;
	virtual	double	GetVar(ImageBuffer &Buff)	=0;
protected:
	void	Initial(void);

};

class MatchingLineV : public MatchingLineBase
{
public:
	MatchingLineV(void){}
	~MatchingLineV(void){}

	virtual	int	GetLineClass(void)	override	{	return 1;	}
	bool	Set(double cx, double cy ,double Len 
				,ImageBuffer &SourcePattern);
	bool	SetOnly(double cx, double cy ,double Len);

	virtual	double	Match(ImageBuffer *TBuff,int dx,int dy)	override;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)override;
	virtual	double	GetVar(ImageBuffer &Buff)	override;
};

class MatchingLineH : public MatchingLineBase
{
public:
	MatchingLineH(void){}
	~MatchingLineH(void){}

	virtual	int	GetLineClass(void)	override	{	return 2;	}
	bool	Set(double cx, double cy ,double Len 
				,ImageBuffer &SourcePattern);
	bool	SetOnly(double cx, double cy ,double Len);

	virtual	double	Match(ImageBuffer *TBuff,int dx,int dy)	override;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)override;
	virtual	double	GetVar(ImageBuffer &Buff)	override;
};

#pragma	pack(push)
#pragma	pack(1)
struct ShiftXY
{
	short	X,Y;
	short	Dx,Dy;
	float	D;
};
#pragma	pack(pop)
const int	MaxShiftXYDimCount=1000000;

enum MatchingMethod
{
	_AveragePower	=0
	,_MinRate		=1
};

class CoeffLine : public FlexAreaImageListCoeff
{
	friend	class RotatedMatchingPattern;

	RotatedMatchingPattern	*Parent;
public:
	NPListPack<MatchingLineBase>	MLines;

	CoeffLine(void):Parent(NULL){}
	void	Initial(RotatedMatchingPattern *p ,ImageBuffer &IBuff);
	double	MatchByLine(int dx,int dy,ImageBuffer &TargetImage ,int SearchDot);

	bool	GoodForRough(void);
};

class RotatedMatchingPattern : public NPList<RotatedMatchingPattern>
{
	friend	class CoeffLine;

public:
	PalletizeItem	*Parent;
	CoeffLine		**XYPiece;
	int				XCount,YCount;
	CoeffLine		*RoughPiece[4];
	FlexArea		PickedAreaInPattern;
	int				PickedAreaInPatternXLen;
	int				PickedAreaInPatternYLen;
	double			Radian;
	double			ZoomSize;

	RotatedMatchingPattern(PalletizeItem *p ,double radian ,double zoomsize);
	~RotatedMatchingPattern(void);

	bool	BuildInitial(FlexAreaImage &ItemArea);

	void	Draw(QImage &IData
				,int MovX ,int MovY ,double ZoomRate);
	double	MatchByLine		(int dx,int dy,ImageBuffer &TargetImage);
	double	MatchRoughByLine(int dx,int dy,ImageBuffer &TargetImage);
	double	MatchByOneLine	(int dx,int dy,ImageBuffer &TargetImage);
	double	Match			(int dx,int dy,ImageBuffer &TargetImage);
	double	MatchRough		(int dx,int dy,ImageBuffer &TargetImage);
};

struct MatchingShiftList
{
	int	Dx,Dy;
	int	RIndex;
	int	ZIndex;
	double		MatchingValue;
	RotatedMatchingPattern	*Pointer;
};


class MatchingResult
{
public:
	int			ResultPosX,ResultPosY;
	int			RotatedIndex;
	int			ZoomSizeIndex;
	double		MatchingValue;
	int			DiffX,DiffY;
	int			IndexMasterPos;

	MatchingResult(void);
	virtual	~MatchingResult(void){}

	MatchingResult	&operator=(const MatchingResult &src);
};

class MatchingResultContainer
{
public:
	MatchingResult	*ResultList;
	int				ResultCount;
	int				AllocatedResultCount;

	MatchingResultContainer(void);
	virtual	~MatchingResultContainer(void);

	void	Allocate(int AllocatedResultCount);

	MatchingResultContainer	&operator=(const MatchingResultContainer &src);
};


class MasterPositionList : public NPListSaveLoad<MasterPositionList>
{
public:
	int		XPos,YPos,ZPos;

	MasterPositionList(void){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class MasterPositionListContainer : public NPListPackSaveLoad<MasterPositionList>
{
public:
	MasterPositionListContainer(){}

	virtual	MasterPositionList	*Create(void)	override;
};

#define		StockCountResult	20
#define		IgnoreStockCount	2

class	PalletizeItem : public AlgorithmItemPITemplate<PalletizeInPage,PalletizeBase>
{
	struct MatchingShiftList	*MList;
	struct MatchingShiftList	*SList;
	int							MListCount;
	int							SkipSearchXY;	//=3

	struct MatchingShiftList	*NearMList;
	struct MatchingShiftList	*NearSList;
	int							NearMListCount;
	int							NearSkipSearchXY;	//=2
public:
	FlexAreaImage	ItemArea;
	NPListPack<RotatedMatchingPattern>	*RotatedContainer;
	int									CountZoomSize;

	MatchingResultContainer		LastResults[StockCountResult];
	int							LastResultCount;
	MatchingResultContainer		Results;
	MasterPositionListContainer	MasterPositions;
public:
	PalletizeItem(void);
	virtual	~PalletizeItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new PalletizeItem();	}
	virtual	bool		Save(QIODevice *f)					override;
	virtual	bool		Load(QIODevice *f,LayersBase *LBase)override;
	const	PalletizeThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const PalletizeThreshold *)GetThresholdBaseReadable(base);	}
	PalletizeThreshold			*GetThresholdW(LayersBase *base=NULL){	return (PalletizeThreshold *)GetThresholdBaseWritable(base);			}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new PalletizeThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	PalletizeItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(PalletizeItem &src);
	void	CopyThresholdOnly(PalletizeItem &src);
	void	CopyArea(PalletizeItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	RotatedMatchingPattern	*GetRotPattern(int RotIndex ,int ZoomIndex);
	int		GetCountZoomSize(void)	{	return CountZoomSize;	}
	int		GetCountRotation(void);
};

//========================================================================================

class   PalletizeInPage : public AlgorithmInPagePITemplate<PalletizeItem,PalletizeBase>
{

public:
	PureFlexAreaListContainer ExecutedPickedFPack;
public:
	bool	RegistInFlowMode;

	PalletizeInPage(AlgorithmBase *parent);
	~PalletizeInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

};

class	PalletizeBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	double	PickupLineVar;
	double	AffinParam[6];
	double	MinAvrage;		//Background;

	PalletizeBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new PalletizeInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("Palletize");					}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigPalletize.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//=================================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	PalletizeHistogramListReqCommand		3
#define	PalletizeHistogramListSendCommand		4
#define	PalletizeReqThresholdReqCommand			5
#define	PalletizeReqThresholdSendCommand		6
#define	PalletizeReqTryThresholdCommand			7
#define	PalletizeSendTryThresholdCommand		8
#define	PalletizeReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All	10
//==================================================================================
class	CmdGetPalletizeLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetPalletizeLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPalletizeLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetPalletizeLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetPalletizeLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetPalletizeLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempPalletizeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempPalletizeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempPalletizeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearPalletizeLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearPalletizeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearPalletizeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertPalletizeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertPalletizeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertPalletizeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdatePalletizeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdatePalletizeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdatePalletizeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadPalletizeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadPalletizeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadPalletizeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeletePalletizeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeletePalletizeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeletePalletizeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempPalletizeItemPacket : public GUIDirectMessage
{
public:
	PalletizeItem	*Point;
	CmdCreateTempPalletizeItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempPalletizeItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromPalletizeItemPacket : public GUIDirectMessage
{
public:
	PalletizeItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromPalletizeItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromPalletizeItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddPalletizeItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			LibID;

	CmdAddPalletizeItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddPalletizeItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadPalletizeItemPacketFromByteArray : public GUIDirectMessage
{
public:
	PalletizeItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadPalletizeItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadPalletizeItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPalletizeResultInItem : public GUIDirectMessage
{
public:
	double	Radian;
	int		XoomSize;
	int		ResultIndex;
	CmdPalletizeResultInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdPalletizeResultInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
