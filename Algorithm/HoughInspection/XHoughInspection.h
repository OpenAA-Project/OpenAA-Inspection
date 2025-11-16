#if	!defined(XHoughINSPECTION_H)
#define	XHoughINSPECTION_H

#include "XDataInLayer.h"
#include "XMainSchemeMemory.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
//#include "XDirectComm.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XCrossObj.h"

#define	HoughVersion	1
#define	DefLibTypeHoughInspect	66
class	HoughItem;
class	HoughBase;

class	HoughLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32		ZoneWidth;	
	int32		MaxIsolation;
	int32		MinPixels;
	int32		NGLength;
	int32		BinarizedLength;	//局所２値化領域サイズ
	int32		PickupL,PickupH;	//Relative;
	bool		RemoveDynamicMask;
	int32		ReducedSize;
	int32		MaxLineCount;
	double		MinNGWidth;
	double		MaxNGWidth;
	int32		MinAverageContinuous;
	bool		DynamicBinarize;

	HoughLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	HoughLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeBlocks(ImageBuffer &IBuff ,PureFlexAreaListContainer &Blocks
						,BYTE **MaskMap);
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

private:
	int		MakeThreshold(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap);
	void	MakeMap(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap
									,BYTE **BMap);
	double	GetAverageRough(ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap);
	void	MakeBrightList(int BrList[] ,ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap);
};

class	HoughLibraryContainer : public AlgorithmLibraryContainer
{
public:
	HoughLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeHoughInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Hough Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new HoughLibrary(GetLibType(),GetLayersBase());	}
};

class	HoughThreshold : public AlgorithmThreshold
{
public:
	int32		ZoneWidth;
	int32		MaxIsolation;
	int32		MinPixels;
	int32		NGLength;
	int32		BinarizedLength;
	int32		PickupL,PickupH;
	bool		RemoveDynamicMask;
	int32		ReducedSize;
	int32		MaxLineCount;
	double		MinNGWidth;
	double		MaxNGWidth;
	int32		MinAverageContinuous;
	bool		DynamicBinarize;

	HoughThreshold(HoughItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	BinarizeFlexAreaList : public PureFlexAreaList
{
public:
	int		ResultCenterBrightness;

	BinarizeFlexAreaList(void){}
};

class	PeakPointList : public NPList<PeakPointList>
{
public:
	int	x1,y1;
	int x2,y2;
	uint32	Count;
	uint32	FoldedCount;
	double	Width;
	double	Length;
	double	MinWidthPartially;
	double	MaxWidthPartially;
	int		PartialCount;
	double	AveCont;		//Average of continuous pixel count

	PeakPointList(void)	{	Count=0;	FoldedCount=0;	}
};

class	LineWithWidth
{
public:
	int		x1,y1;
	int		x2,y2;
	double	Width;
	int		PixelCount;
	bool	Effective;
};

struct BMapPointIndex
{
	int32	XPos;
	int32	YPos;
	int32	Count;
};

class	HoughItem : public AlgorithmItemPLI
{
	uint32	**BMap;		//Hough graph
	int		BMapXLen;	//Hough XLen(s)
	int		BMapYLen;	//Hough YLen(p)

	struct BMapPointIndex	*BMapPointDim;
	int		BMapPointCount;
	int		BMapPointMaxCount;

	double	CompressXRate;
	double	DivS;
	double	*CosTable;
	double	*SinTable;
	BYTE	**BitMap;
	int		XLen;
	int		YLen;
	int		XByte;
	BYTE	**TmpMap;
	QMutex	ProcessMutex;

	AlignmentPacket2D	*AVector;

	FlexArea	**SmallAreaDim;
	int		SmallAreaXNumb;
	int		SmallAreaYNumb;
	NPListPack<PeakPointList> PeakPoints;

	int	Mx,My;

public:

	HoughItem(void);
	~HoughItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new HoughItem();	}
	void	ReleaseBuffer(void);

	const	HoughThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const HoughThreshold *)GetThresholdBaseReadable(base);	}
	HoughThreshold			*GetThresholdW(LayersBase *base=NULL){	return (HoughThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new HoughThreshold(this);	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

private:
	void	ClearBMap(void);
	void	MakeBitMap		(ImageBuffer &Buff ,int mx ,int my,FlexArea &RectArea ,int PickupL ,int PickupH);
	void	MakeBitMapDirect(ImageBuffer &Buff ,int mx ,int my,FlexArea &RectArea ,int PickupL ,int PickupH);

	void	MakeBitCountFromBitMap(void);
	void	PickupPeaks(void);
	bool	PickupLine(int s ,int p);
	void	SaveBMapImage(int ID);
	void	CopyThresholdOnly(HoughItem &src);
	uint	GatherCount(int x ,int y);
	void	SearchAddPoints(XYClassContainer &ClosedPoints ,int x,int y,int &ReEntrantCount,int ThresholdCount);

	virtual	void	SetIndependentItemData(int32 Command
								,int32 LocalPage,int32 Layer
								,AlgorithmItemRoot *Data
								,IntList &EdittedMemberID
								,QByteArray &Something,QByteArray &AckData)	override;
	int		CheckLine(int x1, int y1, int x2 ,int y2 ,LineWithWidth ResultLines[100],double &AveCont);
	int		GetClusterCount(int tx1,int ty1,int tx2,int ty2 ,XYData *XYDim ,int XYDimCount
										,bool &LastExist ,int &NCount
										,int LineClusterCount[] );
	bool	Exist(XYData *XYDim ,int XYDimCount,int X,int Y);
};

class   HoughInLayer : public AlgorithmInLayerPLI
{
public:
	BYTE	**DynamicMaskMap;
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;

  public:
	HoughInLayer(AlgorithmInPageRoot *parent);
	~HoughInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			HoughItem	*a=new HoughItem();
			a->SetParent(this);
			return a;
		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	
	virtual	ExeResult	ExecuteProcessing(int ExeID ,ResultInLayerRoot *R)	override;

private:
	void	CreatePickupBmpBuff(void);
	void	GenerateBlocks(IntList &LibList);
};

class   HoughInPage : public AlgorithmInPagePLI
{
public:

	HoughInPage(AlgorithmBase *parent);

	virtual	HoughInLayer	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new HoughInLayer(parent));	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
};

class	HoughBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	OutputDebugFile;
	double	SearchNeighborRate;
	double	FillRate;			//Pixels/Length
	int		DefaultDivCount;
	double	RangeToFillWidth;
	bool	ModeThread;

	HoughBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new HoughInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)	override{		return QString("Hough");	}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigHough.dat");		}

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================
//===================================================================================

class	AddHoughAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int32		Angle;

	AddHoughAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddHoughAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	HoughDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	enum	__DMode{
		__Mode_PickupArea			=1
		,__Mode_ItemArea			=2
	}DMode;

	HoughDrawAttr(void){}
	HoughDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	HoughDrawAttr( 
					 QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdHoughDrawPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;
	HoughDrawAttr::__DMode	DMode;

	CmdHoughDrawPacket(LayersBase *base)
		:GUIDirectMessage(base)
		{}
};

class	CmdCreateTempHoughItemPacket :public GUIDirectMessage
{
public:
	HoughItem	*Point;

	CmdCreateTempHoughItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempHoughItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempHoughLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempHoughLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempHoughLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetHoughLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetHoughLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetHoughLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadHoughLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadHoughLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadHoughLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearHoughLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearHoughLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearHoughLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteHoughLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteHoughLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteHoughLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateByteArrayFromHoughItemPacket : public GUIDirectMessage
{
public:
	HoughItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromHoughItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromHoughItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddByteHoughItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteHoughItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteHoughItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAddHoughItemPacket :public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	CmdAddHoughItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddHoughItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertHoughLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertHoughLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertHoughLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateHoughLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateHoughLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateHoughLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetHoughLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetHoughLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetHoughLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqChangeItemAttr : public GUIDirectMessage
{
public:
	int			ItemID;
	int32		Angle;
	CmdReqChangeItemAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReqChangeItemAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateHoughPacket: public GUIDirectMessage
{
public:
	IntList	LibList;
	IntList	LayerList;
	CmdGenerateHoughPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateHoughPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================

class	HoughListForPacket : public NPListSaveLoad<HoughListForPacket>
{
public:
	int		ItemID;
	int		Page;
	int		Layer;
	int		x1,y1,x2,y2;
	int		Angle;
	
	HoughListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	HoughListForPacket	&operator=(HoughListForPacket &src)
	{
		ItemID	=src.ItemID	;
		Page	=src.Page	;
		Layer	=src.Layer	;
		x1		=src.x1;
		y1		=src.y1;
		x2		=src.x2;
		y2		=src.y2		;
		Angle	=src.Angle	;
		return *this;
	}
};

class	HoughListForPacketPack : public NPListPackSaveLoad<HoughListForPacket>
{
public:
	HoughListForPacketPack(void){}

	virtual	HoughListForPacket	*Create(void){	return new HoughListForPacket();	}
};

inline	HoughListForPacket::HoughListForPacket(void)
{
	ItemID	=-1;
	Page	=-1;
	Layer	=-1;
	x1=y1=x2=y2=0;
	Angle	=0;
}

inline	bool	HoughListForPacket::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	return true;
}
inline	bool	HoughListForPacket::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	return true;
}


class	HoughMakeListPacket : public GUIDirectMessage
{
public:
	HoughListForPacketPack	*ListInfo;

	HoughMakeListPacket(LayersBase *base):GUIDirectMessage(base){}
};
//===================================================================================
#define	HoughReqThresholdReqCommand					1
#define	HoughReqThresholdSendCommand				2
#define	SetIndependentItemDataCommand_OnlyOneHough	3
#define	SetIndependentItemDataCommand_AllHough		4


class	HoughThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	HoughThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	HoughThresholdSend
{
public:
	int32	GlobalPage;
	int32	ItemID;
	int32	Layer;
	int32	Dx,Dy;
	int32	ZoneWidth;	
	int32	MaxIsolation;
	int32	MinPixels;
	int32	NGLength;
	int32	BinarizedLength;
	int32	PickupL,PickupH;
	bool	RemoveDynamicMask;
	int32		ReducedSize;
	int32		MaxLineCount;
	double		MinNGWidth;
	double		MaxNGWidth;

	HoughThresholdSend(void);

	void	ConstructList(HoughThresholdReq *reqPacket,HoughBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#endif