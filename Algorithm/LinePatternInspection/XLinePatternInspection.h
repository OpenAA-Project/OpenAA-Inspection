#if	!defined(XLinePatternInspection_h)
#define	XLinePatternInspection_h


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XYCross.h"
#include "XFlexArea.h"
#include "XStandardCommand.h"

#define	LinePatternVersion	1
#define	DefLibTypeLinePattern	48
class	LinePatternItem;
class   LinePatternInLayer;
class	LinePatternBase;
class	SetThresholdLinePatternInfo;

class	BlockInfoList;

class	LinePatternLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	IntList	SubtractBlock; //Removal library

	short	LineWidthInPattern;
	short	LineWidthOutside;
	int32	LimitLength;
	int32	GlobalSize;
	int32	MinLineLength;

	short	BrightWidthIL;
	short	BrightWidthIH;
	short	BrightWidthOL;
	short	BrightWidthOH;
	int32	NGSizeIL;
	int32	NGSizeIH;
	int32	NGSizeOL;
	int32	NGSizeOH;
	short	TransitDot;
	short	SearchDot;
	WORD	AdjustBrightIL;
	WORD	AdjustBrightIH;
	WORD	AdjustBrightOL;
	WORD	AdjustBrightOH;
	short	GlobalSearchDot;
	struct {
		bool	ModeEnabled:1;
		bool	ModeAbsoluteBright:1;
		bool	ModeCenterBrightFromParts:1;
		bool	ModeDynamicMask:1;
		bool	ModeUseRegularBrightness:1;
	}PointMove;
	BYTE	RegulatedColI;
	BYTE	RegulatedColO;
	short	AngleNumb;

	LinePatternLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	LinePatternLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakeLinePatternOnly(int localpage
								,BYTE **CurrentMap,const BYTE **MaskMap ,BYTE **DriftMap 
								,int XByte ,int XLen,int YLen
								,NPListPack<AlgorithmItemPLI> &TmpBlockData
								,int OmitZoneDot);
private:
	int		MakeThreshold(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap);
	void	MakeMap(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap
									,BYTE **BMap);
	double	GetAverageRough(ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap);
	void	MakeBrightList(int BrList[] ,ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap);
};

class	LinePatternLibraryContainer : public AlgorithmLibraryContainer
{
public:
	LinePatternLibraryContainer(LayersBase *base);

	virtual	int	GetLibType(void)				override{	return DefLibTypeLinePattern;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "LinePattern Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new LinePatternLibrary(GetLibType(),GetLayersBase());	}
};

class	LinePatternThreshold : public AlgorithmThreshold
{
public:
	#pragma	pack(push,1)
	struct LinePatternThreshBag{
		short	BrightWidthIL;
		short	BrightWidthIH;
		short	BrightWidthOL;
		short	BrightWidthOH;
		int32	NGSizeIL;
		int32	NGSizeIH;
		int32	NGSizeOL;
		int32	NGSizeOH;
		short	TransitDot;
		short	SearchDot;
		WORD	AdjustBrightIL;
		WORD	AdjustBrightIH;
		WORD	AdjustBrightOL;
		WORD	AdjustBrightOH;
		short	GlobalSearchDot;
		struct {
			bool	ModeEnabled					:1;
			bool	ModeAbsoluteBright			:1;
			bool	ModeCenterBrightFromParts	:1;
			bool	ModeDynamicMask				:1;
			bool	ModeUseRegularBrightness	:1;
		}PointMove;
		BYTE	RegulatedColI;
		BYTE	RegulatedColO;

		bool	operator==(const LinePatternThreshBag &src)	const;
		bool	operator!=(const LinePatternThreshBag &src)	const	{	return !operator==(src);	}
	}ThreshBag;
	short	AngleNumb;
	#pragma	pack(pop)

	LinePatternThreshold(LinePatternItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;

	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class	BinarizeFlexAreaList : public PureFlexAreaList
{
public:
	int		ResultCenterBrightness;

	BinarizeFlexAreaList(void){}
};

class	LinePatternItem : public AlgorithmItemPLI
{
	//This use VectorLineBase
	//Vector right side is inside

public:
	AlignmentPacket2D	*AVector;

	FlexArea	*InsideAreaDim;
	FlexArea	*OutsideAreaDim;
	int			AreaNumb;

	BYTE	MasterColI;
	BYTE	MasterColO;
	BYTE	TargetColI;
	BYTE	TargetColO;

	BYTE	CalcTargetColI;
	BYTE	CalcTargetColO;

	int		ResultAngleNumber;
	int		ResultGlobalShiftX,ResultGlobalShiftY;
	int		ResultShiftX ,ResultShiftY;

public:

	LinePatternItem(void);
	~LinePatternItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new LinePatternItem();	}
	virtual	void    MoveTo(int dx ,int dy)	override;
	virtual	VectorLineBase	*CreateVectorBase(void)	override;

	const	LinePatternThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const LinePatternThreshold *)GetThresholdBaseReadable(base);	}
	LinePatternThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (LinePatternThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new LinePatternThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	ExeResult	ExecuteProcessingAngle	(int ExeID ,int ThreadNo,ResultInItemRoot *Res ,int ReqAngleNumber);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	void	SetThresholdFromCommon(SetThresholdLinePatternInfo *Info);
private:
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	CopyThresholdOnly(LinePatternItem &src);

	WORD	CalcCenterBright(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my);
	WORD	CalcCenterBright(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	double	CalcCenterBrightDetail(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my);
	double	CalcCenterBrightDetail(FlexArea &Area ,ImageBuffer &IBuff ,int mx ,int my
				,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);

	void	ExecuteInspectInArea(FlexArea &Area,ImageBuffer &Buff
						,int mx ,int my	,int AlignedX,int AlignedY
						,int tResultShiftX, int tResultShiftY
						,int BrightL,int BrightH
						,int NGSizeL,int NGSizeH
						,ResultInItemRoot *Res
						,ResultPosListContainer	&NowList
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
						,int &Error
						,DWORD InOut);
	void	MakeAreaIO(double X1, double Y1 ,double X2 ,double Y2 ,int n ,LinePatternLibrary &Lib);

public:
	double	TryToMatch(int mx ,int my ,int k);
	double	TryToMatchRough(int mx ,int my ,int k);
	bool	ExecuteProcessingFunc	(int AngleNumber,ResultInItemRoot *Res
									,int mx ,int my
									,ImageBuffer &Buff
									,ResultPosListContainer &NowListI ,ResultPosListContainer &NowListO
									,int &tResultShiftX ,int &tResultShiftY
									,int &Error);
};


class	LinePatternItemPointerList : public NPList<LinePatternItemPointerList>
{
	LinePatternItem		*Pointer;
	int32				ID;
public:
	LinePatternItemPointerList(void)			{	Pointer=NULL;	ID=-1;	};
	LinePatternItemPointerList(LinePatternItem *item)	{	Pointer=item;	ID=item->GetID();	}

	LinePatternItem	*GetItem(void)	{	return Pointer;	}	

	void	SetPointer(LinePatternItem *item)	{	Pointer=item;	}
	void	SetID(int id)	{	ID=id;		}
	int		GetID(void)		{	return ID;	}
};

class	LinePatternItemPointerListContainer : public NPListPack<LinePatternItemPointerList> ,  public NPList<LinePatternItemPointerListContainer> 
{
public:
	int	xn,yn;

	LinePatternItemPointerListContainer(void){}
	~LinePatternItemPointerListContainer(void){}

	LinePatternItemPointerList	*Create(void){	return new LinePatternItemPointerList();	}
	void	Add(LinePatternItem *item)	{	NPListPack<LinePatternItemPointerList>::AppendList(new LinePatternItemPointerList(item));	}
	//bool	IsExist(LinePatternItem *item);
	LinePatternItemPointerListContainer	&operator=(LinePatternItemPointerListContainer &src);
	LinePatternItemPointerListContainer	&operator+=(LinePatternItemPointerListContainer &src);

	ExeResult	ExecuteProcessing		(int ExeID ,bool ThreadMode);
	bool	IsInclude(int ItemID);
	void	ExecuteProcessingTryMatch(int &Mx ,int &My ,int GlobalSearchDot=-1);
};

class	LinePatternExecutablePointerContainer;

class	LinePatternExecutablePointerList : public NPList<LinePatternExecutablePointerList>
{
	IntList		MaskLinkedLibList;						//For SubtractBlock library ID
	AlgorithmItemPointerListContainer	MaskLinkedItems;//For SubtractBlock 
public:
	int		LibID;
	AlgorithmItemPointerListContainer	ItemPointer;
	NPListPack<LinePatternItemPointerListContainer>		GroupContainer;
	LinePatternExecutablePointerContainer	*Container;
	LinePatternInLayer				*ParentLayer;

	LinePatternExecutablePointerList(void);
	~LinePatternExecutablePointerList(void);

	void		ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	void		ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res);
	ExeResult	ExecuteProcessing		(int ExeID ,bool ThreadMode);

	bool	IsLinkedToMask(AlgorithmItemRoot *Item);
	void	MakeDynamicMask(void);
};

class	LinePatternExecutablePointerContainer : public NPListPack<LinePatternExecutablePointerList>
{
public:
	LinePatternInLayer				*ParentLayer;

	LinePatternExecutablePointerContainer(LinePatternInLayer *BL):ParentLayer(BL){}

	void		ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	void		ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res);
	ExeResult	ExecuteProcessing		(int ExeID ,bool ThreadMode);

	bool	IsLinkedToMask(AlgorithmItemRoot *Item);
	LinePatternExecutablePointerList	*FindItem(AlgorithmItemRoot *Item);
	LinePatternExecutablePointerList	*FindByLibID(int LibID);
};

class   LinePatternInLayer : public AlgorithmInLayerPLI
{
  public:
	BYTE	**IndexDynamicMaskMap;		//Global dynamic masking buffer. Needless to delete in this class
	int		IndexDynamicMaskMapXByte;
	int		IndexDynamicMaskMapYLen;

	BYTE	**DynamicMaskMap;		// This is index, needless to delete. For execution
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;
	QMutex	ParallelMutex;

	LinePatternExecutablePointerContainer		ExecutableContainer;

	LinePatternInLayer(AlgorithmInPageRoot *parent);
	~LinePatternInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			LinePatternItem	*a=new LinePatternItem();
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInLayerRoot *Res)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	MoveFromPipe(GeneralPipeInfo &Info);

	LinePatternItemPointerListContainer	*FindGroup(int ItemID);

private:

};
class   LinePatternInPage : public AlgorithmInPagePLI
{
public:

	LinePatternInPage(AlgorithmBase *parent);

	virtual	LinePatternInLayer	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new LinePatternInLayer(parent));	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)		override;
};

class	LinePatternBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	int32	OmitZoneDot;
	double	MultiplyInAngle;

	LinePatternBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new LinePatternInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("LinePattern");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigLinePattern.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
struct	LinePatternShiftInfo
{
	int32	Dx;
	int32	Dy;
	double	MatchResult;
};
int	SortLinePatternShiftInfo(const void *a,const void *b);
//===================================================================================

class	AddLinePatternAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int32		Angle;

	AddLinePatternAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddLinePatternAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	LinePatternDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	ModeDrawArea;
	bool	ModeDrawInside;
	bool	ModeDrawOutside;
	int		ResultAngleNumber;		

	LinePatternDrawAttr(void){	ResultAngleNumber=0;	}
	LinePatternDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){	ResultAngleNumber=0;	}
	LinePatternDrawAttr( 
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
		ResultAngleNumber=0;
	}
};

class	CmdLinePatternDrawPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
	bool	ModeDrawArea;
	bool	ModeDrawInside;
	bool	ModeDrawOutside;
	int		ResultAngleNumber;	

	CmdLinePatternDrawPacket(LayersBase *base)
		:GUIDirectMessage(base)
		{}
};

class	CmdCreateTempLinePatternItemPacket :public GUIDirectMessage
{
public:
	LinePatternItem	*Point;

	CmdCreateTempLinePatternItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempLinePatternItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempLinePatternLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempLinePatternLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempLinePatternLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetLinePatternLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetLinePatternLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLinePatternLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadLinePatternLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadLinePatternLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadLinePatternLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearLinePatternLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearLinePatternLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearLinePatternLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteLinePatternLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteLinePatternLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteLinePatternLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateByteArrayFromLinePatternItemPacket : public GUIDirectMessage
{
public:
	LinePatternItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromLinePatternItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromLinePatternItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddByteLinePatternItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	VectorLineBase	*Vector;
	int			ItemClass;
	int			SelectedLibID;
	QString		ItemName;
	FlexArea	Area;

	CmdAddByteLinePatternItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteLinePatternItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAddLinePatternItemPacket :public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	CmdAddLinePatternItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddLinePatternItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertLinePatternLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertLinePatternLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertLinePatternLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateLinePatternLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateLinePatternLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateLinePatternLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetLinePatternLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	AlgorithmLibraryListContainer	AList;
	bool				Success;
	CmdGetLinePatternLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLinePatternLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqChangeItemAttr : public GUIDirectMessage
{
public:
	int			ItemID;
	int32		Angle;
	CmdReqChangeItemAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdReqChangeItemAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateLinePatternPacket: public GUIDirectMessage
{
public:
	IntList	LibList;
	IntList	LayerList;
	CmdGenerateLinePatternPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateLinePatternPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=================================================================================

class	LinePatternListForPacket : public NPListSaveLoad<LinePatternListForPacket>
{
public:
	int		ItemID;
	int		Page;
	int		Layer;
	int		x1,y1,x2,y2;
	int		Angle;
	
	LinePatternListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	LinePatternListForPacket	&operator=(LinePatternListForPacket &src)
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

class	LinePatternListForPacketPack : public NPListPackSaveLoad<LinePatternListForPacket>
{
public:
	LinePatternListForPacketPack(void){}

	virtual	LinePatternListForPacket	*Create(void){	return new LinePatternListForPacket();	}
};

inline	LinePatternListForPacket::LinePatternListForPacket(void)
{
	ItemID	=-1;
	Page	=-1;
	Layer	=-1;
	x1=y1=x2=y2=0;
	Angle	=0;
}

inline	bool	LinePatternListForPacket::Save(QIODevice *f)
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
inline	bool	LinePatternListForPacket::Load(QIODevice *f)
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
	LinePatternListForPacketPack	*ListInfo;

	MakeListPacket(LayersBase *base):GUIDirectMessage(base){}
};
//===================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	LinePatternHistogramListReqCommand		3
#define	LinePatternHistogramListSendCommand		4
#define	LinePatternReqThresholdReqCommand		5
#define	LinePatternReqThresholdSendCommand		6
#define	LinePatternReqTryThresholdCommand		7
#define	LinePatternSendTryThresholdCommand		8
#define	SetIndependentItemNameDataCommand_All	10


class	LinePatternHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	LinePatternHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LinePatternHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMasterI[256];
	int		ListTargetI[256];
	int		ListMasterO[256];
	int		ListTargetO[256];
	BYTE	MasterColI;
	BYTE	MasterColO;
	BYTE	TargetColI;
	BYTE	TargetColO;

	LinePatternHistogramListSend(void);

	void	ConstructList(LinePatternHistogramListReq *reqPacket,LinePatternBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	LinePatternThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	LinePatternThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LinePatternThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	int32	Dx,Dy;

	short	BrightWidthIL;
	short	BrightWidthIH;
	short	BrightWidthOL;
	short	BrightWidthOH;
	int32	NGSizeIL;
	int32	NGSizeIH;
	int32	NGSizeOL;
	int32	NGSizeOH;
	short	TransitDot;
	short	SearchDot;
	WORD	AdjustBrightIL;
	WORD	AdjustBrightIH;
	WORD	AdjustBrightOL;
	WORD	AdjustBrightOH;
	short	GlobalSearchDot;
	bool	ModeEnabled;
	bool	ModeAbsoluteBright;
	bool	ModeCenterBrightFromParts;
	bool	ModeDynamicMask;
	bool	ModeUseRegularBrightness;
	BYTE	RegulatedColI;
	BYTE	RegulatedColO;
	short	AngleNumb;

	LinePatternThresholdSend(void);

	void	ConstructList(LinePatternThresholdReq *reqPacket,LinePatternBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


//===================================================================================


class	LinePatternReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		LinePatternItemID;	
	LinePatternItem	Threshold;
	int32	ReqAngleNumber;	//-1:Free

	LinePatternReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	LinePatternSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotIL;
	int		NGDotIH;
	int		NGDotOL;
	int		NGDotOH;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;
	ResultInItemRoot	*Result;
	int32	AlignedX;
	int32	AlignedY;
	int32	ShiftByCommonX;
	int32	ShiftByCommonY;
	int32	ShiftBySelfX;
	int32	ShiftBySelfY;
	int32	ResultAngle;

	LinePatternSendTryThreshold(void);
	~LinePatternSendTryThreshold(void);

	void	ConstructList(LinePatternReqTryThreshold *reqPacket,LinePatternBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===================================================================================

class	CmdBlockInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<BlockInfoList>	*BlockInfos;
	CmdBlockInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdBlockInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif