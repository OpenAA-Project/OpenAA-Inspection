#if	!defined(XDentInspection_h)
#define	XDentInspection_h


#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XYCross.h"
#include "XFlexAreaImage.h"
#include "XStandardCommand.h"

#define	DentVersion	2


class   AlignmentInLayer;
class	XAlignmentArea;
class	DentLibrary;
class	DentBase;
class	DentItem;
class	DentInPage;
class	DentInLayer;
class	SetThresholdDentInfo;


class	DentThreshold : public AlgorithmThreshold
{
public:
	double	Difference	;
	int		BandWidth	;
	int		MinNGSize;
	int		MaxNGSize;
	double	MaxDiffCoef		;
	int		LinesForAverage	;

	DentThreshold(DentItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src) override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src) const override;
	virtual	bool	Save(QIODevice *f)				 override;
    virtual	bool	Load(QIODevice *f)				 override;
	virtual	void	FromLibrary(AlgorithmLibrary *src) override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest) override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer) 	const	override;
};

class	MountZoneClass
{
public:
	int	x1,x2;
};

struct	CalcCoefTableList
{
	double	AvrS;
	double	Da;
	double	SkipAvrS;
	double	SkipDa;
	int		Count;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class   DentItem : public AlgorithmItemPLITemplate<DentInLayer,DentInPage,DentBase>
{

public:
	AlignmentPacket2D	*AVector;

	class	DentBand : public NPList<DentBand>
	{
		DentItem		*Parent;
	public:
		FlexArea		Area;
		AlignmentPacket2D	*AVector;
		int				mx,my;
		double			AvrBrightnessL;
		double			AvrBrightnessH;
		int				ResultDx,ResultDy;

		//int				NGCount;
		//ResultPosList	NGPoins[10];	//NG point in Master-matrix

		DentBand(DentItem *p);
		~DentBand(void);

		void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
		void	ExecuteStartByInspection(void);
		void	ExecuteProcessing(ImageBuffer &IBuff);

		void	DrawInHistogram(QImage &Pnt, QRgb Col, double ZoomRate ,int movx ,int movy);

	private:
		double	MakeCoef(int w ,int shift ,DentBase	*ABase 
							,int XList[],int MapXMin ,int Numb
							,double AvrD ,double BB);
		double	MakeCoefSkip(int w ,int shift ,DentBase	*ABase 
							,int XList[],int MapXMin ,int Numb
							,double SkipAvrD ,double SkipBB);
	};

	int		XByte;
	int		YLen;
	NPListPack<DentBand>	DentBandPack;
	int		ResultDx,ResultDy;
	int		ResultMaxNGSize;

	//double	**CoefMap;
	//int		CoefXLen;
	//int		CoefYLen;


#define	WaveCount		50
#define	WaveTableLen	2000	//(Item YLength)
	int			WaveLenList[WaveTableLen];
	int			WavePhaseList[WaveTableLen];

	double	*ResultMaxD;
	int		ResultMapXLen;
	int		ResultMapYLen;

public:

	DentItem(void);
	DentItem(FlexArea &area);
	virtual	~DentItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DentItem();	}
	const	DentThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const DentThreshold *)GetThresholdBaseReadable(base);	}
	DentThreshold			*GetThresholdW(LayersBase *base=NULL){	return (DentThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void) override {	return new DentThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	DentItem &operator=(const AlgorithmItemRoot &src) override;
	void	CopyThreshold(DentItem &src);
	void	CopyThresholdOnly(DentItem &src);
	void	CopyArea(DentItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	void	MoveForAlignment(void)	override;

	void	MakeImageMap(QImage &IData ,int MovX ,int MovY ,double ZoomRate
								,int dx, int dy);
private:

};
class   DentInLayer : public AlgorithmInLayerPLITemplate<DentItem,DentInPage,DentBase>
{
public:
	DentInLayer(AlgorithmInPageRoot *parent);
	~DentInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return new DentItem();	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	UndoGenerateItems(QIODevice *f);

	void	GenerateItems(BYTE **PickedMap ,int XByte,int XLen ,int YLen
									,DentLibrary *BLib);
private:
};

class   DentInPage : public AlgorithmInPagePLITemplate<DentItem,DentInLayer,DentBase>
{

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
public:

	DentInPage(AlgorithmBase *parent);
	~DentInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new DentInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	CreatePickupBmpBuff(void);
	void	PickupTest(DentLibrary &LibData);
	void	GenerateDents(DentLibrary *LibDim[],int LibDimNumb);

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;

	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
private:
	void	GenerateItems(IntList&ItemLibIDs);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,int32 ItemID
										,AlgorithmItemRoot *Data,IntList &EdittedMemberID
										,QByteArray &Something,QByteArray &AckData)	override;
};

class	DentBase	: public AlgorithmBase
{
public:
	QColor		ColorDentNormal		;
	QColor		ColorDentSelected	;
	QColor		ColorDentActive		;
	QColor		ColorPickup			;
	QColor		DentColor0;
	QColor		DentColor1;
	QColor		DentColor2;
	QColor		DentColor3;
	QColor		DentColor4;
	QColor		DentColor5;
	QColor		DentColor6;
	QColor		DentColor7;
	int			OmitZoneDot;
	int			BaseWaveLength	;

	double		WaveTable[WaveCount][WaveTableLen];
	struct	CalcCoefTableList	*WaveTableResult[WaveCount][WaveCount*2];

	DentBase(LayersBase *Base);
	~DentBase(void);
	virtual	DentInPage	*NewChild(AlgorithmBase *parent)		override	{	return(new DentInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)	override{	return QString("Dent");				}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigDent.dat");	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData);
	virtual	QString	GetNameByCurrentLanguage(void)	override;
private:
	bool	SaveWavetableResultHeader(QIODevice *f);
	bool	LoadWavetableResultHeader(QIODevice *f);
	bool	SaveWavetableResult(QIODevice *f);
	bool	LoadWavetableResult(QIODevice *f);
};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	DentHistogramListReqCommand						3
#define	DentHistogramListSendCommand					4
#define	DentReqThresholdReqCommand						5
#define	DentReqThresholdSendCommand						6
#define	DentReqTryThresholdCommand						7
#define	DentSendTryThresholdCommand						8
#define	DentReqChangeShiftCommand						9
#define	SetIndependentItemNameDataCommand_All			10
//==================================================================================

class	DentDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	bool		Master;
	IntList		LayerList;
	int			ShowingItemID;

	DentDrawAttr(void):ServiceForLayers(NULL){	ShowingItemID=-1;	}
	DentDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol);
	DentDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, const QColor &pcol ,int ptranparentLevel
				, const QColor &blockColor0
				, const QColor &blockColor1
				, const QColor &blockColor2
				, const QColor &blockColor3
				, const QColor &blockColor4
				, const QColor &blockColor5
				, const QColor &blockColor6
				, const QColor &blockColor7);

	void	Initial(void);

	DentDrawAttr	&operator=(DentDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	DentDrawAttr::DentDrawAttr(LayersBase *Base,const QColor &ncol,const QColor &scol ,const QColor &acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base),ShowingItemID(-1)
{
}

inline	DentDrawAttr::DentDrawAttr(LayersBase *Base
				, const QColor &ncol ,int ntranparentLevel
				, const QColor &scol ,int stranparentLevel
				, const QColor &acol ,int atranparentLevel
				, const QColor &pcol ,int ptranparentLevel
				, const QColor &blockColor0
				, const QColor &blockColor1
				, const QColor &blockColor2
				, const QColor &blockColor3
				, const QColor &blockColor4
				, const QColor &blockColor5
				, const QColor &blockColor6
				, const QColor &blockColor7)
:AlgorithmDrawAttr(ncol,ntranparentLevel,scol,stranparentLevel,acol,atranparentLevel)
,ServiceForLayers(Base)
,BlockColor0(blockColor0)
,BlockColor1(blockColor1)
,BlockColor2(blockColor2)
,BlockColor3(blockColor3)
,BlockColor4(blockColor4)
,BlockColor5(blockColor5)
,BlockColor6(blockColor6)
,BlockColor7(blockColor7)
,Master(true)
,ShowingItemID(-1)
{
	BlockColor0.setAlpha(ptranparentLevel);
	BlockColor1.setAlpha(ptranparentLevel);
	BlockColor2.setAlpha(ptranparentLevel);
	BlockColor3.setAlpha(ptranparentLevel);
	BlockColor4.setAlpha(ptranparentLevel);
	BlockColor5.setAlpha(ptranparentLevel);
	BlockColor6.setAlpha(ptranparentLevel);
	BlockColor7.setAlpha(ptranparentLevel);
}
inline	DentDrawAttr	&DentDrawAttr::operator=(DentDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);

	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	ShowingItemID	=src.ShowingItemID;
	return *this;
}
inline	bool	DentDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,BlockColor0)==false)	return false;
	if(::Save(f,BlockColor1)==false)	return false;
	if(::Save(f,BlockColor2)==false)	return false;
	if(::Save(f,BlockColor3)==false)	return false;
	if(::Save(f,BlockColor4)==false)	return false;
	if(::Save(f,BlockColor5)==false)	return false;
	if(::Save(f,BlockColor6)==false)	return false;
	if(::Save(f,BlockColor7)==false)	return false;
	if(::Save(f,Master)==false)			return false;
	if(LayerList.Save(f)==false)		return false;
	if(::Save(f,ShowingItemID)==false)	return false;
	return true;
}
inline	bool	DentDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,BlockColor0)==false)	return false;
	if(::Load(f,BlockColor1)==false)	return false;
	if(::Load(f,BlockColor2)==false)	return false;
	if(::Load(f,BlockColor3)==false)	return false;
	if(::Load(f,BlockColor4)==false)	return false;
	if(::Load(f,BlockColor5)==false)	return false;
	if(::Load(f,BlockColor6)==false)	return false;
	if(::Load(f,BlockColor7)==false)	return false;
	if(::Load(f,Master)==false)			return false;
	if(LayerList.Load(f)==false)		return false;
	if(::Load(f,ShowingItemID)==false)	return false;
	return true;
}


//==========================================================================
class	DentInfoList : public NPList<DentInfoList>
{
public:
	int		LibID;
	int		GlobalPage;
	int		Layer;
	int		ItemID;
	int		x1,y1,x2,y2;
	QString	ItemName;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	DentInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	return true;
}
inline	bool	DentInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	return true;
}


//==================================================================================

class	DentThresholdReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	DentThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DentThresholdSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	double	Difference	;
	int		BandWidth	;

	DentThresholdSend(void);

	void	ConstructList(DentThresholdReq *reqPacket,DentBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DentReqTryThreshold
{
public:
	int32	GlobalPage;
	int		Layer;
	int		BlockItemID;	
	DentItem	Threshold;

	DentReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	DentSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	double	ResultNGSize		;

	DentSendTryThreshold(void);
	~DentSendTryThreshold(void);

	void	ConstructList(DentReqTryThreshold *reqPacket,DentBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CmdGetDentLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetDentLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDentLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetDentLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetDentLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDentLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempDentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempDentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempDentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearDentLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearDentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearDentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertDentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertDentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertDentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateDentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateDentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateDentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadDentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadDentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteDentLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteDentLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteDentLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempDentItemPacket : public GUIDirectMessage
{
public:
	DentItem	*Point;
	CmdCreateTempDentItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempDentItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromDentItemPacket : public GUIDirectMessage
{
public:
	DentItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromDentItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromDentItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddDentItemPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			Layer;
	QString		ItemName;
	int			LibID;

	CmdAddDentItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddDentItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadDentItemPacketFromByteArray : public GUIDirectMessage
{
public:
	DentItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadDentItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDentItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDentInfoListPacket: public GUIDirectMessage
{
public:
	NPListPack<DentInfoList>	*DentInfos;
	CmdDentInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDentInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================


class	CmdPickupTestDentPacket : public GUIDirectMessage
{
public:
	int		LibID;

	CmdPickupTestDentPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestDentPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateDentPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateDentPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateDentPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearTestDentPacket: public GUIDirectMessage
{
public:
	CmdClearTestDentPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestDentPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDentGenerate: public GUIDirectMessage
{
public:
	IntList	ItemLibIDs;

	CmdDentGenerate(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdDentReqItemResult: public GUIDirectMessage
{
public:
	int	ItemID;
	int	Layer;
	int GlobalX;
	int GlobalY;
	double	ResultMaxD;
	double	ResultWaveLen;

	CmdDentReqItemResult(LayersBase *base):GUIDirectMessage(base){}
};



#endif