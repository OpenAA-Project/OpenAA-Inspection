#if	!defined(XThinMetal_H)
#define	XThinMetal_H


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"
#include "XStandardCommand.h"

#define	ThinMetalVersion	2

class	ThinMetalItem;
class	ThinMetalInLayer;
class	ThinMetalInPage;
class	ThinMetalBase;


class	ThinMetalItem;
class	ThinMetalInPage;
class	ThinMetalLibrary;


//==========================================================================================

class	ThinMetalDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	enum	DrawType{
		 _LibTest		=1
		,_CreatedArea	=2
	}Mode;

	ThinMetalDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	ThinMetalDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	ThinMetalDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	ThinMetalDrawAttr	&operator=(ThinMetalDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


inline	ThinMetalDrawAttr	&ThinMetalDrawAttr::operator=(ThinMetalDrawAttr &src)
{
	Mode	=src.Mode;
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	ThinMetalDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	ThinMetalDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}
//========================================================================================
//========================================================================================
class	ThinMetalThreshold : public AlgorithmThreshold
{
	friend	class	ThinMetalItem ;
public:
	short		SpaceToOutline;

#pragma	pack(push,1)
	WORD	BrightWidthL;	//à√ë§ãPìxïù
	WORD	BrightWidthH;	//ñæë§ãPìxïù
	DWORD	OKDotL;			//à√ë§ÇnÇjÉhÉbÉgêî
	DWORD	OKDotH;			//ñæë§ÇnÇjÉhÉbÉgêî
	WORD	OKLengthL;		//à√ë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
	WORD	OKLengthH;		//ñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
	DWORD	MaxNGDotL;		//à√ë§ç≈ëÂÇmÇfÉhÉbÉgêî
	DWORD	MaxNGDotH;		//ñæë§ç≈ëÂÇmÇfÉhÉbÉgêî
	BYTE	ShrinkDot;
	BYTE	EnlargeDot;
#pragma	pack(pop)


	ThinMetalThreshold(ThinMetalItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class	CoeffImageList : public NPListSaveLoad<CoeffImageList>
{
public:
	int		X,Y;
	int32	XLen;
	int32	YLen;
	BYTE	**Image;

	double	A,AA;
	int32	Judgement;
	double	tA,tAA;		//for Rough match

	QString	TargetFolder;
	QString	TargetFileName;

	CoeffImageList(void);
	~CoeffImageList(void);

	CoeffImageList	&operator=(CoeffImageList &src);

	void	SetImage(ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,int SepNumb);
	double	GetRoughMatch  (ImageBuffer &IBuff ,int mx, int my ,double B ,double BB,int Sep);
	double	GetPreciseMatch(ImageBuffer &IBuff ,int mx, int my ,double B ,double BB);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	CalcAA(int Sep);
};

class	CoeffImageContainer : public NPListPackSaveLoad<CoeffImageList>
{
public:

	CoeffImageContainer(void){}

	virtual	CoeffImageList	*Create(void){	return new CoeffImageList;	}

};

struct	MatchingList
{
	int	dx,dy;
	double	B,BB;
	CoeffImageList *Point;
	double	Result;
};

class	ThinMetalItem : public AlgorithmItemPLITemplate<ThinMetalInLayer,ThinMetalInPage,ThinMetalBase>
{
	friend	class	ThinMetalThreshold;
public:
	AlignmentPacket2D	*AVector;

	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		CurrentNGCount;
	int16		RegNumber;
	enum	_Condition
	{
		 _AverageMustBeInside		=1
		,_AllMustBeInside			=2
		,_OneMustBeInsideAtLeast	=3
		,_AverageMustBeOutside		=4
		,_AllMustBeOutside			=5
		,_OneMustBeOutsideAtLeast	=6
	}Condition;

	int16		CurrentBrightness;
	bool		ResultOK;
	BYTE		CenterBright;
	BYTE		CenterTargetBright;

	int	LastAreaX1,LastAreaY1;
	int	LastAreaX2,LastAreaY2;
	CoeffImageContainer		SampleImages;
	struct MatchingList *MList;
	int					MListNumb;
	int					AllocatedMListNumb;

	ThinMetalItem(void);
	~ThinMetalItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ThinMetalItem();	}
	void InitialConstructor(void);

	const	ThinMetalThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ThinMetalThreshold *)GetThresholdBaseReadable(base);	}
	ThinMetalThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ThinMetalThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ThinMetalThreshold(this);	}

	void	CopyThreshold(ThinMetalItem &src);
	void	CopyThresholdOnly(ThinMetalItem &src);

	virtual	int32		GetItemClassType(void)	override	{		return 0;		}
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	ThinMetalItem		&operator=(ThinMetalItem &src);
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	void	CopyArea(ThinMetalItem &src);
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override{}

	void	StoreTargetImageToSamples(int Judgement,const QString &TargetFolder ,const QString &TargetFileName);
	void	ClearSampleImages(void);
	int		MatchSamples(int mx ,int my ,int swing ,int &Dx ,int &Dy ,double &Result,int &SampleNo);
	void	FinalizeSampleImages(void){}
	void	DeleteSamples(IntList &Numbers);
	QString	GetNGString(int judgeNo);
private:
	void	NGFunc(ResultInItemRoot *Res);
	void	CalcTargetImage(int dx,int dy,double &B,double &BB,int Sep);
};

class   ThinMetalInLayer : public AlgorithmInLayerPLITemplate<ThinMetalItem,ThinMetalInPage,ThinMetalBase>
{
public:
	ThinMetalInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);
};

class   ThinMetalInPage : public AlgorithmInPagePLITemplate<ThinMetalItem,ThinMetalInLayer,ThinMetalBase>
{

public:
	ThinMetalInPage(AlgorithmBase *parent);
	~ThinMetalInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new ThinMetalInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

};

class	ThinMetalBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	int		OmitZoneDot;

	ThinMetalBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new ThinMetalInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("ThinMetal");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigThinMetal.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)				override;
	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};

//==================================================================================
class	ThinMetalHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ThinMetalItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ThinMetalHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ThinMetalHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ThinMetalItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMaster[256];
	int		ListTarget[256];
	WORD	CenterBright;
	WORD	CenterTargetBright;

	ThinMetalHistogramListSend(void);

	void	ConstructList(ThinMetalHistogramListReq *reqPacket,ThinMetalBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ThinMetalThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ThinMetalItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ThinMetalThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ThinMetalThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ThinMetalItemID;
	bool	Mastered;
	int32	Dx,Dy;
	WORD	CenterBright;
	WORD	CenterTargetBright;

	short	AbsBrightWidthL;	//à√ë§ãPìxïù
	short	AbsBrightWidthH;	//ñæë§ãPìxïù

	BYTE	ShrinkDot;
	BYTE	EnlargeDot;

	ThinMetalThresholdSend(void);

	void	ConstructList(ThinMetalThresholdReq *reqPacket,ThinMetalBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	ThinMetalReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ThinMetalItemID;	
	ThinMetalItem	Threshold;

	ThinMetalReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	ThinMetalSendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInDark;
	int		NGDotInBright;
	int		Error;
	ResultInItemRoot	*Result;

	ThinMetalSendTryThreshold(void);
	~ThinMetalSendTryThreshold(void);

	void	ConstructList(ThinMetalReqTryThreshold *reqPacket,ThinMetalBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ThinMetalChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ThinMetalItemID;
	int32	Dx,Dy;

	ThinMetalChangeShift(void){}

	void	Reflect(ThinMetalBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	SetIndependentItemNameDataCommand_All	3
#define	ThinMetalHistogramListReqCommand				3
#define	ThinMetalHistogramListSendCommand				4
#define	ThinMetalReqThresholdReqCommand				5
#define	ThinMetalReqThresholdSendCommand				6
#define	ThinMetalReqTryThresholdCommand				7
#define	ThinMetalSendTryThresholdCommand				8
#define	ThinMetalReqChangeShiftCommand				9

//===================================================================================
class	ThinMetalInfoList : public  NPListSaveLoad<ThinMetalInfoList>
{
public:
	int	GlobalPage;
	int	Layer;
	int	ItemID;
	int	LibID;
	int	x1,y1,x2,y2;

	ThinMetalInfoList(void){}

	ThinMetalInfoList	&operator=(ThinMetalInfoList &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ThinMetalInfoContainer : public NPListPackSaveLoad<ThinMetalInfoList>
{
public:
	ThinMetalInfoContainer(void){}
	virtual	ThinMetalInfoList	*Create(void){	return new ThinMetalInfoList();	}
};

inline	ThinMetalInfoList	&ThinMetalInfoList::operator=(ThinMetalInfoList &src)
{
	GlobalPage	=src.GlobalPage;
	Layer		=src.Layer;
	ItemID		=src.ItemID;
	LibID		=src.LibID;
	x1			=src.x1;
	y1			=src.y1;
	x2			=src.x2;
	y2			=src.y2;
	return *this;
}

inline	bool	ThinMetalInfoList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;
	return true;
}
inline	bool	ThinMetalInfoList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	return true;
}

//===================================================================================
class	CmdGetThinMetalLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetThinMetalLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetThinMetalLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetThinMetalLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetThinMetalLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetThinMetalLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempThinMetalLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempThinMetalLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempThinMetalLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearThinMetalLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearThinMetalLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearThinMetalLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertThinMetalLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertThinMetalLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertThinMetalLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateThinMetalLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateThinMetalLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateThinMetalLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadThinMetalLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadThinMetalLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadThinMetalLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteThinMetalLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteThinMetalLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteThinMetalLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestThinMetalPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;
	int				Page;

	CmdPickupTestThinMetalPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestThinMetalPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateThinMetalPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	IntList		LayerList;
	int			Page;
	CmdGenerateThinMetalPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateThinMetalPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempThinMetalItemPacket : public GUIDirectMessage
{
public:
	ThinMetalItem	*Point;
	CmdCreateTempThinMetalItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempThinMetalItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromThinMetalItemPacket : public GUIDirectMessage
{
public:
	ThinMetalItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromThinMetalItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromThinMetalItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteThinMetalItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteThinMetalItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteThinMetalItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadThinMetalItemPacketFromByteArray : public GUIDirectMessage
{
public:
	ThinMetalItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadThinMetalItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadThinMetalItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedThinMetalFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedThinMetalFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedThinMetalFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestThinMetalPacket: public GUIDirectMessage
{
public:
	CmdClearTestThinMetalPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestThinMetalPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	CmdThinMetalInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	ThinMetalInfoContainer	*ThinMetalInfos;
	CmdThinMetalInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdThinMetalInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetThinMetalFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	ThinMetalItem	*ThinMetalInfoOnMouse;

	CmdGetThinMetalFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetThinMetalFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateThinMetalItem: public GUIDirectMessage
{
public:
	ThinMetalItem	*ThinMetal;
	CmdCreateThinMetalItem(LayersBase *base):GUIDirectMessage(base){	ThinMetal=NULL;	}
	CmdCreateThinMetalItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ThinMetal=NULL;	}
};

class	CmdReqStoreThinMetal :public GUIDirectMessage
{
public:
	int		Judgement;
	QString	JudgeStr;
	QString	TargetFolder;
	QString	TargetFileName;
	CmdReqStoreThinMetal(LayersBase *base):GUIDirectMessage(base){}
	CmdReqStoreThinMetal(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqStoreThinMetalStart :public GUIDirectMessage
{
public:

	CmdReqStoreThinMetalStart(LayersBase *base):GUIDirectMessage(base){}
	CmdReqStoreThinMetalStart(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqStoreThinMetalEnd :public GUIDirectMessage
{
public:

	CmdReqStoreThinMetalEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdReqStoreThinMetalEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqSampleList:public GUIDirectMessage
{
public:
	int		ItemID;
	IntList	*Judgement;
	CmdReqSampleList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSampleList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqSampleDetail:public GUIDirectMessage
{
public:
	int		ItemID;
	int		Number;
	CoeffImageList	*Point;

	CmdReqSampleDetail(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSampleDetail(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqDeleteSample:public GUIDirectMessage
{
public:
	int		ItemID;
	IntList	Numbers;

	CmdReqDeleteSample(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDeleteSample(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif