#if	!defined(XColorDifference_h)
#define	XColorDifference_h

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>

#define	ColorDifferenceVersion	6

class	ColorDifferenceItem;
class	ColorDifferenceRegulation;
class	ColorDifferenceInPage;
class	ColorDifferenceBase;
class	ColorDifferenceLibrary;

class	ColorDifferenceItem;
class	ColorDifferenceInPage;


//==========================================================================================

class	ColorDifferenceDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	ColorDifferenceDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	ColorDifferenceDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	ColorDifferenceDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	ColorDifferenceDrawAttr	&operator=(ColorDifferenceDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	ColorDifferenceDrawAttr::ColorDifferenceDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol ,196
				 , scol ,196
				 , acol ,196),ServiceForLayers(Base)
{
}

inline	ColorDifferenceDrawAttr::ColorDifferenceDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	ColorDifferenceDrawAttr	&ColorDifferenceDrawAttr::operator=(ColorDifferenceDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	ColorDifferenceDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	ColorDifferenceDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}

//========================================================================================

#pragma	pack(push,1)
struct ResultColorDifferenceForExtraData
{
	double	ThresholdDeltaE;
	double	ResultDeltaE;
};
#pragma	pack(pop)

//========================================================================================

class	ColorDifferenceResultPosList : public ResultPosList
{
	AlgorithmItemRoot	*AItem;
public:
	ColorDifferenceResultPosList(AlgorithmItemRoot	*item)
		:ResultPosList(),AItem(item){}
	ColorDifferenceResultPosList(AlgorithmItemRoot	*item,int px ,int py) 
		: ResultPosList(px,py),AItem(item){}
	ColorDifferenceResultPosList(AlgorithmItemRoot	*item,int px ,int py ,int rx ,int ry)
		:ResultPosList(px ,py ,rx ,ry),AItem(item){}

	virtual	void	GetExtraData(QByteArray &EData)	override;
};

class	ResultColorDifferenceInPagePI : public ResultInPagePI
{
public:
	ResultColorDifferenceInPagePI(ResultBasePhase *pPhaseParent,DataInPage *pPage):ResultInPagePI(pPhaseParent,pPage){}

	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount) override;
};

class	ResultColorDifferenceBaseForAlgorithmPI : public ResultBaseForAlgorithmPI
{
public:
	ResultColorDifferenceBaseForAlgorithmPI(LogicDLL *parent):ResultBaseForAlgorithmPI(parent){}

	ResultInPageRoot	*CreatePage(int phase ,int page) override
	{	
		if(GetLayersBase()->GetPageDataPhase(phase)!=NULL){
			return new ResultColorDifferenceInPagePI(GetPageDataPhase(phase),GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page));	
		}
	return NULL;
	}
};

//========================================================================================
class	ColorDifferenceThreshold : public AlgorithmThreshold
{
public:
	double		AdoptedRate;	//Percentage
	double		THDeltaE;
	int32		JudgeMethod;	//0:OK/NG	1:DeltaE	2:FlowSample/HSV threshold
	double		dH;
	double		dSL;
	double		dSH;
	double		dVL;
	double		dVH;
	bool		AdaptAlignment;	//AlignmentÇÃâeãøÇéÛÇØÇƒåüç∏Ç≤Ç∆Ç…ÉVÉtÉg

	ColorDifferenceThreshold(ColorDifferenceItem *parent);
	ColorDifferenceThreshold(ColorDifferenceRegulation *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	ColorDifferenceItem : public AlgorithmItemPITemplate<ColorDifferenceInPage,ColorDifferenceBase>
{
public:
	AlignmentPacket2D	*AVector;

	bool		OutputConstantly;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	PreciseColorListConatiner	FlowBrightness;	//After regulation

	PreciseColor	MasterColor;
	PreciseColor	TargetColor;
	ColorDifferenceRegulation	*Reference1;
	ColorDifferenceRegulation	*Reference2;
	PreciseColor	ReferedCurrentColor;
	double			ResultDeltaE;

	int	MasterCx,MasterCy;
	PreciseColor	FlowCenterColor;

	struct{
		double	HAvr,SAvr,VAvr;
		double	Hvl,Hvh;
		double	Svl,Svh;
		double	Vvl,Vvh;
	}StatisticData;
	QByteArray	ResultExtraData;

	struct{
		float		ResultDiffR;
		float		ResultDiffG;
		float		ResultDiffB;
	};


	ColorDifferenceItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ColorDifferenceItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return 0;		}

	const	ColorDifferenceThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ColorDifferenceThreshold *)GetThresholdBaseReadable(base);	}
	ColorDifferenceThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ColorDifferenceThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ColorDifferenceThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	void	CopyThreshold(ColorDifferenceItem &src);

	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	MoveForAlignment(void)	override;

	void	AddSampleColor(bool OK);

	void	SetStatisticThreshold(double SigmaH ,double SigmaS ,double SigmaV);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	UpdateThreshold(int LearningMenuID ,LearningResource &LRes)			override;

private:
	void	CalcFlowCenterColor(void);
};


class	ColorDifferenceRegulation : public AlgorithmItemPITemplate<ColorDifferenceInPage,ColorDifferenceBase>
{
	AlignmentPacket2D	*AVector;
	int	MasterCx,MasterCy;
public:
	RGBStock	Brightness;
	PreciseColor	MasterColor;
	PreciseColor	TargetColor;

	ColorDifferenceRegulation(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ColorDifferenceRegulation();	}
	virtual	int32		GetItemClassType(void)		override{		return 1;		}

	const	ColorDifferenceThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ColorDifferenceThreshold *)GetThresholdBaseReadable(base);	}
	ColorDifferenceThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ColorDifferenceThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ColorDifferenceThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	void	CopyThreshold(ColorDifferenceRegulation &src);
	virtual	void	MoveForAlignment(void)	override;

	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										,AlgorithmItemRoot *Data,IntList &EdittedMemberID
										,QByteArray &Something,QByteArray &AckData)	override;
private:
};

class   ColorDifferenceInPage : public AlgorithmInPagePITemplate<ColorDifferenceItem,ColorDifferenceBase>
{

public:
	bool	RegistInFlowMode;

	ColorDifferenceInPage(AlgorithmBase *parent);
	~ColorDifferenceInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res) override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

	void	MakeBlocks(ColorDifferenceLibrary &Lib ,ImagePointerContainer &Images);

private:

};

#define	LearningMenu_ColorDifference_OK_ByDeltaE	1

class	ColorDifferenceBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	QColor	TextColor;
	bool	DeltaE2000;

	ColorDifferenceBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new ColorDifferenceInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;	
	virtual	QString	GetDataText(void)	override{	return QString("ColorDifference");					}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigColorDifference.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	int	GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================
#define	ColorDifferenceReqThresholdReqCommand					1
#define	ColorDifferenceReqThresholdSendCommand					2
#define	SetIndependentItemDataCommand_OnlyOneColorDifference	3
#define	SetIndependentItemDataCommand_AllColorDifference		4
#define	SetIndependentItemDataCommand_SetThreBrightnessThis		5
#define	SetIndependentItemDataCommand_SetThreBrightnessAll		6
#define	SetIndependentItemNameDataCommand_All					10

#define	ColorDifferenceReqTryThresholdCommand			7
#define	ColorDifferenceSendTryThresholdCommand			8
#define	ColorDifferenceSendTryThresholdCommand2			9

class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	int			ItemClass;
	QString		ItemName;
	FlexArea	Area;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	RGBStock	Brightness	;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	ColorDifferenceInfoContainer;

class	CmdReqColorDifferenceInfo : public GUIDirectMessage
{
public:
	ColorDifferenceInfoContainer	*Info;

	CmdReqColorDifferenceInfo(LayersBase *Base):GUIDirectMessage(Base){}
};
class	CBPanelListContainer;
class	CmdReqCBPanelInfo : public GUIDirectMessage
{
public:
	int		Layer;
	CBPanelListContainer	*Info;

	CmdReqCBPanelInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqCBPanelResult : public GUIDirectMessage
{
public:
	int		ItemID;
	bool	ResultOK;

	CmdReqCBPanelResult(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemInfo : public GUIDirectMessage
{
public:
	int			ItemID;
	QString		ItemName;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	RGBStock	Brightness	;

	CmdReqItemInfo(LayersBase *Base):GUIDirectMessage(Base){}
};
class	CmdUpdateManual : public GUIDirectMessage
{
public:
	int			ItemID;
	QString		ItemName;
	RGBStock	OKBrightness;
	RGBStock	NGBrightness;
	RGBStock	Brightness	;

	CmdUpdateManual(LayersBase *Base):GUIDirectMessage(Base){}
};


class	ColorDifferenceThresholdReq
{
public:
	int32	GlobalPage;
	int		ColorDifferenceItemID;

	ColorDifferenceThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ColorDifferenceThresholdSend
{
public:
	int32	GlobalPage;
	int		ColorDifferenceItemID;
	RGBStock		OKBrightness;
	RGBStock		NGBrightness;	
	PreciseColor	TargetColor;
	PreciseColor	ReferedCurrentColor;
	PreciseColor	MasterColor;
	double		AdoptedRate;	//Percentage
	double		THDeltaE;

	ColorDifferenceThresholdSend(void);

	void	ConstructList(ColorDifferenceThresholdReq *reqPacket,ColorDifferenceBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ColorDifferenceReqTryThreshold
{
public:
	int32	GlobalPage;
	int		ColorDifferenceItemID;	
	ColorDifferenceItem			Threshold;
	ColorDifferenceRegulation	ThresholdReg;

	ColorDifferenceReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	ColorDifferenceSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		Error;
	double	LenOK;
	double	LenNG;
	double	DeltaE;
	PreciseColor	ReferenceColor1	;
	PreciseColor	ReferenceColor2	;
	PreciseColor	MasterColor		;
	PreciseColor	TargetColor		;
	struct{
		double		MasterH,MasterS,MasterV;
		double		TargetH,TargetS,TargetV;
		double		SigmaH,SigmaS,SigmaV;
	}StatisticData;

	ColorDifferenceSendTryThreshold(void);
	~ColorDifferenceSendTryThreshold(void);

	void	ConstructList(ColorDifferenceReqTryThreshold *reqPacket,ColorDifferenceBase *Base);
	void	ConstructList2(ColorDifferenceReqTryThreshold *reqPacket,ColorDifferenceBase *Base);
	void	Calc(ColorDifferenceItem *Target,ColorDifferenceItem *Src,ColorDifferenceBase *Base);
	void	CalcRegulation(ColorDifferenceRegulation *Target,ColorDifferenceRegulation *Src,ColorDifferenceBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	CmdColorDifferenceSendTryThreshold : public GUIDirectMessage
{
public:
	ColorDifferenceSendTryThreshold	*PTry;
	ColorDifferenceItem				*Src;
	ColorDifferenceItem				*Target;
	QByteArray							ThresholdDataForTarget;

	CmdColorDifferenceSendTryThreshold(LayersBase *base):GUIDirectMessage(base){	PTry=NULL;	Target=NULL;	Src=NULL;	}
	CmdColorDifferenceSendTryThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}

	~CmdColorDifferenceSendTryThreshold(void){	delete	PTry;	delete	Target;	}
};

//===================================================================================

class	ColorDifferenceInfo : public NPListSaveLoad<ColorDifferenceInfo>
{
public:
	int		ItemID;
	QString	ItemName;
	int		Page;
	int		Cx,Cy;
	int		x1,y1,x2,y2;

	ColorDifferenceInfo(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	ColorDifferenceInfoContainer : public NPListPackSaveLoad<ColorDifferenceInfo>
{
public:
	ColorDifferenceInfoContainer(void){}
	virtual	ColorDifferenceInfo	*Create(void);
	void	SetPage(int page);
};


inline	bool	ColorDifferenceInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Cx)==false)
		return false;
	if(::Load(f,Cy)==false)
		return false;
	if(::Load(f,x1)==false)
		return false;
	if(::Load(f,x2)==false)
		return false;
	if(::Load(f,y1)==false)
		return false;
	if(::Load(f,y2)==false)
		return false;
	int16	d;
	if(::Load(f,d)==false)
		return false;

	return true;
}
inline	bool	ColorDifferenceInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Cx)==false)
		return false;
	if(::Save(f,Cy)==false)
		return false;
	if(::Save(f,x1)==false)
		return false;
	if(::Save(f,x2)==false)
		return false;
	if(::Save(f,y1)==false)
		return false;
	if(::Save(f,y2)==false)
		return false;

	return true;
}

inline	ColorDifferenceInfo	*ColorDifferenceInfoContainer::Create(void)
{
	return new ColorDifferenceInfo();
}

inline	void	ColorDifferenceInfoContainer::SetPage(int page)
{
	for(ColorDifferenceInfo *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Page=page;
	}
}

//---------------------------------------------

class	CBPanelList : public NPListSaveLoad<CBPanelList>
{
public:
	int			GlobalPage;
	int			ItemID;
	QString		ItemName;
	bool		ResultOk;
	bool		Check;

	CBPanelList(void){	}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};
	
class	CBPanelListContainer : public NPListPackSaveLoad<CBPanelList>
{
public:
	CBPanelListContainer(void){}
	virtual	CBPanelList	*Create(void)	{	return new CBPanelList();	}
};

inline	bool	CBPanelList::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,ResultOk)==false)
		return false;
	return true;
}

inline	bool	CBPanelList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,ResultOk)==false)
		return false;
	return true;
}

//=======================================================
class	CmdGetColorDifferenceLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetColorDifferenceLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorDifferenceLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetColorDifferenceLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetColorDifferenceLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorDifferenceLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempColorDifferenceLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempColorDifferenceLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempColorDifferenceLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearColorDifferenceLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearColorDifferenceLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearColorDifferenceLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertColorDifferenceLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertColorDifferenceLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertColorDifferenceLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateColorDifferenceLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateColorDifferenceLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateColorDifferenceLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadColorDifferenceLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadColorDifferenceLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadColorDifferenceLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteColorDifferenceLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteColorDifferenceLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteColorDifferenceLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromColorDifferenceItemPacket : public GUIDirectMessage
{
public:
	ColorDifferenceItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromColorDifferenceItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromColorDifferenceItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAddByteColorDifferenceItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LibID;
	CmdAddByteColorDifferenceItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteColorDifferenceItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedColorDifferenceFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedColorDifferenceFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedColorDifferenceFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetColorDifferenceFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	ColorDifferenceItem	*ColorDifferenceInfoOnMouse;

	CmdGetColorDifferenceFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorDifferenceFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateColorDifferenceItem: public GUIDirectMessage
{
public:
	ColorDifferenceItem	*ColorDifference;
	CmdCreateColorDifferenceItem(LayersBase *base):GUIDirectMessage(base){	ColorDifference=NULL;	}
	CmdCreateColorDifferenceItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ColorDifference=NULL;	}
};
class	CmdGetColorDifferenceLibName : public GUIDirectMessage
{
public:
	int		LibID;
	QString	LibName;
	CmdGetColorDifferenceLibName(LayersBase *base):GUIDirectMessage(base){}
	CmdGetColorDifferenceLibName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddColorDifferenceOK : public GUIDirectMessage
{
public:
	CmdAddColorDifferenceOK(LayersBase *base):GUIDirectMessage(base){}
	CmdAddColorDifferenceOK(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddColorDifferenceNG : public GUIDirectMessage
{
public:
	CmdAddColorDifferenceNG(LayersBase *base):GUIDirectMessage(base){}
	CmdAddColorDifferenceNG(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqFlowData : public GUIDirectMessage
{
public:
	QByteArray	Data;
	CmdReqFlowData(LayersBase *base):GUIDirectMessage(base){}
	CmdReqFlowData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSendFlowData : public GUIDirectMessage
{
public:
	QByteArray	Data;
	CmdSendFlowData(LayersBase *base):GUIDirectMessage(base){}
	CmdSendFlowData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateColorDifferenceThreshold : public GUIDirectMessage
{
public:
	ColorDifferenceItem			*Item;		//Should be deleted
	ColorDifferenceThreshold	*Threshold;	//Should be deleted

	CmdCreateColorDifferenceThreshold(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	Threshold=NULL;	}
	CmdCreateColorDifferenceThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdCreateColorDifferenceThreshold(void){	delete	Item;	delete	Threshold;	}
};

//=======================================================
class	ItemListForPage : public NPListSaveLoad<ItemListForPage>
{
public:
	int	LibID;
	int	ItemCount;

	ItemListForPage(void){	LibID=0;	ItemCount=0;	}

	virtual	bool	Save(QIODevice *f)
	{
		if(::Save(f,LibID)==false)	return false;
		if(::Save(f,ItemCount)==false)	return false;
		return true;
	}
	virtual	bool	Load(QIODevice *f)
	{
		if(::Load(f,LibID)==false)	return false;
		if(::Load(f,ItemCount)==false)	return false;
		return true;
	}
};

class	ItemListForPageContainer : public NPListPackSaveLoad<ItemListForPage>
{
public:
	virtual	ItemListForPage	*Create(void)	{	return new ItemListForPage();	}
};
class	CmdItemListForPageContainer: public GUIDirectMessage
{
public:
	ItemListForPageContainer	*Container;
	CmdItemListForPageContainer(LayersBase *base):GUIDirectMessage(base){	Container=NULL;	}
	CmdItemListForPageContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Container=NULL;	}
};

class	CmdSetStatisticThreshold: public GUIDirectMessage
{
public:
	double	SigmaH;
	double	SigmaS;
	double	SigmaV;

	CmdSetStatisticThreshold(LayersBase *base):GUIDirectMessage(base){}
	CmdSetStatisticThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearFlowStack : public GUIDirectMessage
{
public:
	CmdClearFlowStack(LayersBase *base):GUIDirectMessage(base){}
	CmdClearFlowStack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoGenerate : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;

	CmdAutoGenerate(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoGenerate(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif