#if	!defined(XBUSLINEINSPECTION_H)
#define	XBUSLINEINSPECTION_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XYCross.h"
#include "XFlexArea.h"


#define	BuslineVersion	2
#define	DefLibTypeBusInspect	38
class	BuslineItem;
class	BuslineBase;

const int	BuslineAreaMergin = 6;

class	BuslineLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int64	BlockMinArea;
	int64	BlockMaxArea;
	int		LimitDot;	//å¿äEÉTÉCÉY

	int		MinWidth;	//ç≈è¨ê¸ïù
	int		MinGap;		//ç≈è¨ä‘äu
	int64	MinArea;
	int64	MaxArea;
	int		MinSize;
	bool	Darkside;
	bool	CompareToMaster;
	bool	AutoBinarize;
	bool	ReduceNoise;
	int		BinarizedLength;	//ã«èäÇQílâªóÃàÊÉTÉCÉY
	int		ReferredBrightness;	//ÇQílâªéQè∆ãPìx
	int		SearchDotToMaster;
	int		WidthToIgnoreEdge;
	int		OKNickRate;			//0-100% for MinWidth
	int		OKShortRate;		//0-100% for MinGap
	int		BrightnessWidthInsideL;
	int		BrightnessWidthInsideH;
	int		BrightnessWidthOutsideL;
	int		BrightnessWidthOutsideH;

	BuslineLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	BuslineLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeBlocks(ImageBuffer &IBuff ,PureFlexAreaListContainer &Blocks
						,int page
						,BYTE **MaskMap);
private:
	int		MakeThreshold(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap);
	void	MakeMap(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap
									,BYTE **BMap);
	double	GetAverageRough(ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap);
	void	MakeBrightList(int BrList[] ,ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap);
};

class	BuslineLibraryContainer : public AlgorithmLibraryContainer
{
public:
	BuslineLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeBusInspect;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Busline Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new BuslineLibrary(GetLibType(),GetLayersBase());	}
};

class	BuslineThreshold : public AlgorithmThreshold
{
public:
	int		MinWidth;	//ç≈è¨ê¸ïù
	int		MinGap;		//ç≈è¨ä‘äu
	int		LimitDot;	//å¿äEÉTÉCÉY
	int64	MinArea;
	int64	MaxArea;
	int		MinSize;
	bool	Darkside;
	bool	CompareToMaster;
	bool	AutoBinarize;
	bool	ReduceNoise;
	int		BinarizedLength;	//ã«èäÇQílâªóÃàÊÉTÉCÉY
	int		ReferredBrightness;
	int		SearchDotToMaster;
	int		WidthToIgnoreEdge;
	int		OKNickRate;			//0-100% for MinWidth
	int		OKShortRate;		//0-100% for MinGap
	int		BrightnessWidthInsideL ;
	int		BrightnessWidthInsideH ;
	int		BrightnessWidthOutsideL;
	int		BrightnessWidthOutsideH;

	BuslineThreshold(BuslineItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;	
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class	AreaWithBrightness : public NPListSaveLoad<AreaWithBrightness>,public FlexArea
{
public:
	int32		PeakH,PeakL;
	int32		ThresholdBrightness;

	AreaWithBrightness(void){	ThresholdBrightness=-1;	PeakH=PeakL=-1;	}
	virtual	~AreaWithBrightness(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
class	FlexAreaWithBrightnessListContainer : public NPListPackSaveLoad<AreaWithBrightness>
{
public:
	FlexAreaWithBrightnessListContainer(void){}

	FlexAreaWithBrightnessListContainer	&operator=(FlexAreaWithBrightnessListContainer &src);
	FlexAreaWithBrightnessListContainer	&operator+=(FlexAreaWithBrightnessListContainer &src);

	virtual	AreaWithBrightness	*Create(void)	{	return new AreaWithBrightness();	}
	bool	IsInclude(int x ,int y);
	AreaWithBrightness	*SearchArea(int x ,int y);
	void	MoveNoClip(int dx ,int dy);
	void	MoveClip(int dx ,int dy ,int Left ,int Top ,int Right ,int Bottom);
};

class	BuslineItem : public AlgorithmItemPLI
{
public:
	BYTE	**BMap;
	BYTE	**BMapOpen;
	BYTE	**BMapShort;
	BYTE	**TmpMap1;
	BYTE	**TmpMap2;
	int		BMapXByte;
	int		BMapXLen;
	int		BMapYLen;
	int		MerginX;
	int		MerginY;
	FlexAreaWithBrightnessListContainer	BinarizedAreas;
	PureFlexAreaListContainer			MasterAreas;

	AlignmentPacket2D	*AVector;
	int		NGDotOpen;
	int		NGDotShort;
public:

	BuslineItem(void);
	~BuslineItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new BuslineItem();	}
	const	BuslineThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const BuslineThreshold *)GetThresholdBaseReadable(base);	}
	BuslineThreshold			*GetThresholdW(LayersBase *base=NULL){	return (BuslineThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new BuslineThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	void	MakeBMap(void);
	void	ClearBMap(void);
	bool	CheckOpenInPoint(int Px, int Py);
private:
	void	CreateBinarizedArea(BuslineLibrary &Lib);
	void	MakeBMap(ImageBuffer &Buff,int mx ,int my ,bool DarkSide);
	int		GetBinarizedBrightness(ImageBuffer &Buff);
	void	RegulatePureFlexAreaList(PureFlexAreaListContainer &FPack);

	void	ExecuteProcessingCompareToMaster(ImageBuffer &Buff,ResultInItemRoot *Res,int mx,int my,short &Error);
	void	ExecuteProcessingCheckShort		(ImageBuffer &Buff,ResultInItemRoot *Res,int mx,int my,short &Error);
	void	ExecuteProcessingCheckOpen		(ImageBuffer &Buff,ResultInItemRoot *Res,int mx,int my,short &Error);

	int		GetBinarizedBrightness(ImageBuffer &Buff,int mx ,int my
									,AreaWithBrightness &BArea);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	CopyThresholdOnly(BuslineItem &src);
	bool	OverlapEffective(int cx,int cy);
	bool	IsOnTheEdge(FlexArea *f,int dx ,int dy);
	void	MaskEdge(BYTE** Map, int XLen, int YLen
					, int LMerginLeft, int LMerginTop, int LMerginRight, int LMerginBottom);
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
};

class   BuslineInLayer : public AlgorithmInLayerPLI
{
  public:
	BuslineInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			BuslineItem	*a=new BuslineItem();
			a->SetParent(this);
			return a;
		}
	virtual	bool		AppendItem(AlgorithmItemRoot *item)							override;
			bool		AppendItem(AlgorithmItemRoot* item, AlgorithmLibrary* LibP)	;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)				override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID)			override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
private:
	void	CreatePickupBmpBuff(void);
	void	GenerateBlocks(IntList &LibList);
};
class   BuslineInPage : public AlgorithmInPagePLI
{
public:

	BuslineInPage(AlgorithmBase *parent);

	virtual	BuslineInLayer	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new BuslineInLayer(parent));	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
};

class	BuslineBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	BuslineBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new BuslineInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)	override{		return QString("Busline");	}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigBusline.dat");		}

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};
//==================================================================================
//===================================================================================

class	AddBuslineAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int32		Angle;

	AddBuslineAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddBuslineAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	BuslineDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	enum	__DMode{
		__Mode_PickupArea			=1
		,__Mode_ItemArea			=2
		,__Mode_TestOpen			=3
		,__Mode_TestShort			=4
	}DMode;

	BuslineDrawAttr(void){}
	BuslineDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	BuslineDrawAttr( 
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

class	CmdBuslineDrawPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;
	BuslineDrawAttr::__DMode	DMode;

	CmdBuslineDrawPacket(LayersBase *base)
		:GUIDirectMessage(base)
		{}
};

class	CmdCreateTempBuslineItemPacket :public GUIDirectMessage
{
public:
	BuslineItem	*Point;

	CmdCreateTempBuslineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempBuslineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempBuslineLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempBuslineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempBuslineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetBuslineLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetBuslineLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetBuslineLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadBuslineLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadBuslineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadBuslineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearBuslineLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearBuslineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearBuslineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteBuslineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteBuslineLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteBuslineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateByteArrayFromBuslineItemPacket : public GUIDirectMessage
{
public:
	BuslineItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromBuslineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromBuslineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddByteBuslineItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteBuslineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteBuslineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAddBuslineItemPacket :public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	CmdAddBuslineItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddBuslineItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertBuslineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertBuslineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertBuslineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateBuslineLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateBuslineLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateBuslineLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetBuslineLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetBuslineLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetBuslineLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqChangeItemAttr : public GUIDirectMessage
{
public:
	int			ItemID;
	int32		Angle;
	CmdReqChangeItemAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReqChangeItemAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateBuslinePacket: public GUIDirectMessage
{
public:
	IntList	LibList;
	IntList	LayerList;
	CmdGenerateBuslinePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateBuslinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdTestBuslinePacket: public GUIDirectMessage
{
public:
	IntList	LayerList;
	CmdTestBuslinePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdTestBuslinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearBuslinePacket: public GUIDirectMessage
{
public:
	CmdClearBuslinePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearBuslinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================

class	BuslineListForPacket : public NPListSaveLoad<BuslineListForPacket>
{
public:
	int		ItemID;
	int		Page;
	int		Layer;
	int		x1,y1,x2,y2;
	int		Angle;
	
	BuslineListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	BuslineListForPacket	&operator=(BuslineListForPacket &src)
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

class	BuslineListForPacketPack : public NPListPackSaveLoad<BuslineListForPacket>
{
public:
	BuslineListForPacketPack(void){}

	virtual	BuslineListForPacket	*Create(void){	return new BuslineListForPacket();	}
};

inline	BuslineListForPacket::BuslineListForPacket(void)
{
	ItemID	=-1;
	Page	=-1;
	Layer	=-1;
	x1=y1=x2=y2=0;
	Angle	=0;
}

inline	bool	BuslineListForPacket::Save(QIODevice *f)
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
inline	bool	BuslineListForPacket::Load(QIODevice *f)
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


class	MakeListPacket : public GUIDirectMessage
{
public:
	BuslineListForPacketPack	*ListInfo;

	MakeListPacket(LayersBase *base):GUIDirectMessage(base){}
};
//===================================================================================
#define	BuslineReqThresholdReqCommand			1
#define	BuslineReqThresholdSendCommand			2
#define	SetIndependentItemDataCommand_OnlyOne	3
#define	SetIndependentItemDataCommand_All		4
#define	BuslineReqTryThresholdCommand			7
#define	BuslineSendTryThresholdCommand			8

class	BuslineThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	BuslineThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BuslineThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	int32	Dx,Dy;
	int		MinWidth;	//ç≈è¨ê¸ïù
	int		MinGap;		//ç≈è¨ä‘äu
	int64	MinArea;
	int64	MaxArea;
	int		MinSize;
	bool	Darkside;
	bool	CompareToMaster;
	bool	AutoBinarize;
	bool	ReduceNoise;
	int		BinarizedLength;
	int		ReferredBrightness;
	int		SearchDotToMaster;
	int		WidthToIgnoreEdge;
	int		OKNickRate;			//0-100% for MinWidth
	int		OKShortRate;		//0-100% for MinGap
	int		BrightnessWidthInsideL ;
	int		BrightnessWidthInsideH ;
	int		BrightnessWidthOutsideL;
	int		BrightnessWidthOutsideH;

	BuslineThresholdSend(void);

	void	ConstructList(BuslineThresholdReq *reqPacket,BuslineBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	BuslineReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ItemID;
	BuslineItem	Threshold;

	BuslineReqTryThreshold(void);

	bool	Save(QIODevice* f);
	bool	Load(QIODevice* f, LayersBase* LBase);
};

class	BuslineSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotOpen;
	int		NGDotShort;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;
	ResultInItemRoot* Result;
	BYTE	** BMapOpen;
	BYTE	** BMapShort;
	BYTE	** BMapBinary;
	int		BMapXByte;
	int		BMapXLen;
	int		BMapYLen;

	BuslineSendTryThreshold(void);
	~BuslineSendTryThreshold(void);

	void	ConstructList(BuslineReqTryThreshold* reqPacket, BuslineBase* Base);

	bool	Save(QIODevice* f);
	bool	Load(QIODevice* f);
};


#endif