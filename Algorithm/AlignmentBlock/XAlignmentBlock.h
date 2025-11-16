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

#define	AlignmentBlockVersion	4

class	AlignmentBlockItem;
class	AlignmentBlockInPage;
class	AlignmentBlockBase;
class	AlignmentBlockLibrary;

class	AlignmentBlockItem;
class	AlignmentBlockInPage;
class	MatchingResultList;
class	PalletizingBackItem;
class	RotatedMatchingPattern;

//==========================================================================================

class	AlignmentBlockDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ShowLines;
	bool	ShowResult;
	double	Radian;

	AlignmentBlockDrawAttr(LayersBase *Base):ServiceForLayers(Base){	ShowLines=true;	ShowResult=true;	Radian=0;	}
	AlignmentBlockDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	AlignmentBlockDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	AlignmentBlockDrawAttr	&operator=(AlignmentBlockDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	AlignmentBlockDrawAttr::AlignmentBlockDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	ShowLines=true;
	ShowResult=true;
	Radian	=0;
}

inline	AlignmentBlockDrawAttr	&AlignmentBlockDrawAttr::operator=(AlignmentBlockDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	ShowLines	=src.ShowLines;
	ShowResult	=src.ShowResult;
	Radian		=src.Radian;
	return *this;
}

inline	bool	AlignmentBlockDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	if(::Save(f,ShowLines)==false)
		return false;
	if(::Save(f,ShowResult)==false)
		return false;
	if(::Save(f,Radian)==false)
		return false;
	return true;
}
inline	bool	AlignmentBlockDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	if(::Load(f,ShowLines)==false)
		return false;
	if(::Load(f,ShowResult)==false)
		return false;
	if(::Load(f,Radian)==false)
		return false;
	return true;
}

//========================================================================================
class	AlignmentBlockThreshold : public AlgorithmThreshold
{
public:
	int		SearchDot	;
	double	MaxDegree	;
	int		LineLength	;
	double	MinVar		;
	double	ThreDiv		;

	AlignmentBlockThreshold(AlignmentBlockItem *parent);

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
	int		Layer;

	MatchingLineBase(void);
	virtual	~MatchingLineBase(void);

	virtual	int	GetLineClass(void)	=0;
	void	MoveTo(int dx ,int dy);

	virtual	double	Match(bool ModeCalcIncline,ImageBuffer *TBuff,int dx,int dy)=0;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)=0;
	virtual	double	GetVar(bool ModeCalcIncline,ImageBuffer &Buff)	=0;
	virtual	double	GetSitaBrightness(ImageBuffer &Buff)	=0;

	bool	CalcIncline(double &pa,double &pb,BYTE *D ,int DLen);		//y=pa*x+pb

protected:
	void	Initial(bool ModeCalcIncline);

};

class MatchingLineV : public MatchingLineBase
{
public:
	MatchingLineV(void){}
	~MatchingLineV(void){}

	virtual	int	GetLineClass(void)	override	{	return 1;	}
	bool	Set(bool ModeCalcIncline,double cx, double cy ,double Len 
				,ImageBuffer &SourcePattern);
	bool	SetOnly(double cx, double cy ,double Len);

	virtual	double	Match(bool ModeCalcIncline,ImageBuffer *TBuff,int dx,int dy)	override;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)override;
	virtual	double	GetVar(bool ModeCalcIncline,ImageBuffer &Buff)	override;
	virtual	double	GetSitaBrightness(ImageBuffer &Buff)			override;
};

class MatchingLineH : public MatchingLineBase
{
public:
	MatchingLineH(void){}
	~MatchingLineH(void){}

	virtual	int	GetLineClass(void)	override	{	return 2;	}
	bool	Set(bool ModeCalcIncline,double cx, double cy ,double Len 
				,ImageBuffer &SourcePattern);
	bool	SetOnly(double cx, double cy ,double Len);

	virtual	double	Match(bool ModeCalcIncline,ImageBuffer *TBuff,int dx,int dy)	override;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)override;
	virtual	double	GetVar(bool ModeCalcIncline,ImageBuffer &Buff)	override;
	virtual	double	GetSitaBrightness(ImageBuffer &Buff)			override;
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
class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
{
public:
	AlignmentBlockItem		*Item;
	AlignmentPacket2DList(void){	Item=NULL;	}
};

class RotatedMatchingPattern : public NPList<RotatedMatchingPattern>,public FlexAreaColorImage
{
	friend	class CoeffLine;

public:
	AlignmentBlockItem				*Parent;
	NPListPack<MatchingLineBase>	MLines;
	double							Radian;

	double							Result;
	int								ResultDx,ResultDy;

	RotatedMatchingPattern(AlignmentBlockItem *p ,double radian);
	~RotatedMatchingPattern(void);

	bool	BuildInitial(bool ModeCalcIncline);

	void	Draw(QImage &IData
				,int MovX ,int MovY ,double ZoomRate);
	void	DrawLine(QImage &IData ,QColor &LineColor
				,int MovX ,int MovY ,double ZoomRate);

	void	MatchByLine	(bool ModeCalcIncline,int dx,int dy,ImagePointerContainer &TargetImages,int SearchDot);
};

class	AlignmentBlockItem : public AlgorithmItemPITemplate<AlignmentBlockInPage,AlignmentBlockBase>
{
public:
	NPListPack<RotatedMatchingPattern>	RotatedContainer;

	int		CurrentRotationPatternNo;
	double	ResultRadian;
	int		ResultDx,ResultDy;

public:
	AlignmentBlockItem(void);
	virtual	~AlignmentBlockItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AlignmentBlockItem();			}
	AlignmentBlockItem	*tGetNext(void)						{	return (AlignmentBlockItem *)GetNext();		}

	virtual	bool		Save(QIODevice *f)					override;
	virtual	bool		Load(QIODevice *f,LayersBase *LBase)override;
	const	AlignmentBlockThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AlignmentBlockThreshold *)GetThresholdBaseReadable(base);	}
	AlignmentBlockThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AlignmentBlockThreshold *)GetThresholdBaseWritable(base);			}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AlignmentBlockThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	AlignmentBlockItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(AlignmentBlockItem &src);
	void	CopyThresholdOnly(AlignmentBlockItem &src);
	void	CopyArea(AlignmentBlockItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	RotatedMatchingPattern	*GetRotatedPattern(int n);
	void	CalcByNeighbor(void);
};

//========================================================================================

class   AlignmentBlockInPage : public AlgorithmInPagePITemplate<AlignmentBlockItem,AlignmentBlockBase>
{

public:
	PureFlexAreaListContainer ExecutedPickedFPack;
public:

	QMutex	AlignmentPacket2DCreaterMutex;
	NPListPack<AlignmentPacket2DList>	AlignmentPacket2DContainer;

	AlignmentBlockInPage(AlgorithmBase *parent);
	~AlignmentBlockInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	AlignmentPacket2D	*AppendAlignmentBlockPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY ,bool FromGlobal);
	bool	GetAlignmentBlock(AlignmentPacket2D &Point);

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

private:
	void	GenerateItem(AlignmentBlockLibrary *ALib);
};

class	AlignmentBlockBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	bool	ModeCalcIncline;
	double	ZLevel;

	AlignmentBlockBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new AlignmentBlockInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("AlignmentBlock");					}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigAlignmentBlock.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//=================================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	AlignmentBlockHistogramListReqCommand		3
#define	AlignmentBlockHistogramListSendCommand		4
#define	AlignmentBlockReqThresholdReqCommand			5
#define	AlignmentBlockReqThresholdSendCommand		6
#define	AlignmentBlockReqTryThresholdCommand			7
#define	AlignmentBlockSendTryThresholdCommand		8
#define	AlignmentBlockReqChangeShiftCommand			9
#define	SetIndependentItemNameDataCommand_All	10

//==================================================================================

class	AlignmentBlockReqTryThreshold
{
public:
	int32	GlobalPage;
	int		AlignmentBlockItemID;	
	AlignmentBlockItem	Threshold;

	AlignmentBlockReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	AlignmentBlockSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;

	int		ResultMoveDx;
	int		ResultMoveDy;


	AlignmentBlockSendTryThreshold(void);
	AlignmentBlockSendTryThreshold(const AlignmentBlockSendTryThreshold &src);
	~AlignmentBlockSendTryThreshold(void);

	AlignmentBlockSendTryThreshold &operator=(const AlignmentBlockSendTryThreshold &src);
	void	ConstructList(AlignmentBlockReqTryThreshold *reqPacket,AlignmentBlockBase *Base);
	void	Calc(AlignmentBlockItem *Target,AlignmentBlockItem *Src,AlignmentBlockBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//==================================================================================
class	CmdGetAlignmentBlockLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAlignmentBlockLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentBlockLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentBlockLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetAlignmentBlockLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentBlockLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempAlignmentBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAlignmentBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAlignmentBlockLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAlignmentBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAlignmentBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAlignmentBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAlignmentBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAlignmentBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAlignmentBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAlignmentBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAlignmentBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadAlignmentBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadAlignmentBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAlignmentBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAlignmentBlockLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAlignmentBlockLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAlignmentBlockLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempAlignmentBlockItemPacket : public GUIDirectMessage
{
public:
	AlignmentBlockItem	*Point;
	CmdCreateTempAlignmentBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromAlignmentBlockItemPacket : public GUIDirectMessage
{
public:
	AlignmentBlockItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromAlignmentBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromAlignmentBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddAlignmentBlockItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			LibID;

	CmdAddAlignmentBlockItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddAlignmentBlockItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadAlignmentBlockItemPacketFromByteArray : public GUIDirectMessage
{
public:
	AlignmentBlockItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadAlignmentBlockItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAlignmentBlockItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoGenerateAlignmentBlock: public GUIDirectMessage
{
public:
	int		LibID;

	CmdAutoGenerateAlignmentBlock(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoGenerateAlignmentBlock(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};