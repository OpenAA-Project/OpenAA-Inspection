/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Algorithm\SwitchPhase\XSwitchPhase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XSwitchPhase_h)
#define	XSwitchPhase_h

#include <QByteArray>
#include <QString>
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "NListComp.h"
#include "XFlexAreaImage.h"
#include "XDataComponent.h"

#define	SwitchPhaseVersion	5
#define	DefLibTypeNickInspection	45

class	SwitchPhaseItem;


//=====================================================================
class	SwitchPhaseDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorSwitchPhase;
	QColor	NegColorSelected;

	SwitchPhaseDrawAttr(void){}
	SwitchPhaseDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	SwitchPhaseDrawAttr( QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorSwitchPhase	=nncol;	
		NegColorSelected=nscol;	
		NegColorSwitchPhase.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	SwitchPhaseDrawAttr::Save(QIODevice *f)
{	
	if(::Save(f,NegColorSwitchPhase)==false)	return false;
	if(::Save(f,NegColorSelected)==false)		return false;
	return true;
}
inline	bool	SwitchPhaseDrawAttr::Load(QIODevice *f)
{	
	if(::Load(f,NegColorSwitchPhase)==false)	return false;
	if(::Load(f,NegColorSelected)==false)		return false;
	return true;
}

//==========================================================================
class	SwitchPhaseThreshold : public AlgorithmThreshold
{
public:
	int	SearchDot;

	SwitchPhaseThreshold(SwitchPhaseItem *parent);
	~SwitchPhaseThreshold(void);

	virtual	void	RegistHist(void)	override;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	//void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

#define	Hist_SwitchPhaseShiftX	1
#define	Hist_SwitchPhaseShiftY	2

class	SwitchPhaseItem : public AlgorithmItemPI
{
public:
	struct	ShiftDim
	{
		int	ShiftX, ShiftY;
		double	D;
	};
private:
	struct	ShiftDim	*Dim;
	struct	ShiftDim	*DimSortable;
	int		DimNumb;
public:
	int						AdaptedLayer;
	FlexAreaImageListCoeff		MatchingArea;
	FlexAreaImageListSkipCoeff	MatchingAreaSkip;
	int						Skip;
	double					MatchingResult;
	int						ResultDx,ResultDy;

	AlignmentPacket2D	*AVector;

	SwitchPhaseItem(void);
	~SwitchPhaseItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new SwitchPhaseItem();	}
	const	SwitchPhaseThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const SwitchPhaseThreshold *)GetThresholdBaseReadable(base);	}
	SwitchPhaseThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (SwitchPhaseThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new SwitchPhaseThreshold(this);	}

	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResult(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)											override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	CopyThresholdOnly(SwitchPhaseItem &src);
	virtual	QString	GetComment(Type_ItemComment t)	override;
};


class   SwitchPhaseInPage : public AlgorithmInPagePI
{
public:
	int	MasterShiftX,MasterShiftY;

	SwitchPhaseInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			SwitchPhaseItem	*a=new SwitchPhaseItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	double	GetMatchingRate(void);
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item)							override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);

	void	GenerateItemAutomaticly(void);

};


class	SwitchPhaseBase : public AlgorithmBase
{
	bool	RegistrationMode;
public:
	QColor	ColorSwitchPhase;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorSwitchPhase;
	QColor	NegColorSelected;
	int32	SkipForRoughSearch;
	int32	SourcePhaseInInitial;
	RootNameListContainer	CopiedAlgorithmDim;
	QByteArray	CopiedAlgorithmData;
	bool	SamePositionAfter2ndPhase;
	bool	Only1MarkInPage;
	bool	ModeCopyAlignment;
	bool	ModeCopyAlgorithmInLoadMaster;
	double	ItemAdoptedRate ;
	double	ItemRateFromPeak;

	int32	AutoItemSize;
	int32	AutoSearchDot;
	int32	*InspectionCountInPhase;

	SwitchPhaseBase(LayersBase *Base);
	~SwitchPhaseBase(void);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new SwitchPhaseInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)		override	{	return QString("SwitchPhase");		}
	virtual	QString	GetDefaultFileName(void)override	{	return QString("SwitchPhase.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultBaseForAlgorithmRoot *Res)	override;
	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;

	virtual	bool	SaveParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int EnableCondition=-1)	override;
	virtual	bool	LoadParam(QIODevice *f ,int StartPoint ,int EndPoint ,int EnableCondition=-1)		override;
	virtual	void	ExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data)	override;
};
//==================================================================================

#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	SwitchPhaseReqNameReqCommand			10
#define	SwitchPhaseReqNameSendCommand			11

class	SwitchPhaseNameReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	SwitchPhaseNameReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	SwitchPhaseNameSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;
	QString	AreaName;

	SwitchPhaseNameSend(void);

	void	ConstructList(SwitchPhaseNameReq *reqPacket,SwitchPhaseBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AddSwitchPhaseAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		AreaName;
	int			SearchDot;

	AddSwitchPhaseAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddSwitchPhaseAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	ModifySwitchPhasePacket : public GUIDirectMessage
{
public:
	int			ItemID;
	int			SearchDot;

	ModifySwitchPhasePacket(LayersBase *base):GUIDirectMessage(base){}
	ModifySwitchPhasePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	PhaseItemList : public NPListSaveLoad<PhaseItemList>
{
public:
	int	Phase;
	int	Page;
	int	ItemCount;
	double	MatchingResult;

	PhaseItemList(void){	Phase=-1;	Page=-1;	ItemCount=0;	MatchingResult=0;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
inline	bool	PhaseItemList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Page)==false)	return false;
	if(::Save(f,ItemCount)==false)	return false;
	return true;
}
inline	bool	PhaseItemList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Page)==false)	return false;
	if(::Load(f,ItemCount)==false)	return false;
	return true;
}

class	PhaseItemListContainer : public NPListPackSaveLoad<PhaseItemList>
{
public:
	PhaseItemListContainer(void){}

	virtual	PhaseItemList	*Create(void){	return new PhaseItemList();	}
};

class	CmdPhaseItemList : public GUIDirectMessage
{
public:
	PhaseItemListContainer	ItemsInfos;

	CmdPhaseItemList(LayersBase *base):GUIDirectMessage(base){}
	CmdPhaseItemList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	ItemInfoList : public NPListSaveLoad<ItemInfoList>
{
public:
	int	Phase;
	int	Page;
	int	ItemID;
	int	Cx,Cy;
	int	SearchDot;
	double	MatchingResult;

	ItemInfoList(void){	MatchingResult=0;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
inline	bool	ItemInfoList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,Page)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	if(::Save(f,Cx)==false)		return false;
	if(::Save(f,Cy)==false)		return false;
	if(::Save(f,SearchDot)==false)	return false;
	return true;
}
inline	bool	ItemInfoList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,Page)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	if(::Load(f,Cx)==false)		return false;
	if(::Load(f,Cy)==false)		return false;
	if(::Load(f,SearchDot)==false)	return false;
	return true;
}

class	PhaseItemInfoListContainer : public NPListPackSaveLoad<ItemInfoList>
{
public:
	PhaseItemInfoListContainer(void){}

	virtual	ItemInfoList	*Create(void){	return new ItemInfoList();	}
};

class	CmdItemInfoList : public GUIDirectMessage
{
public:
	int	Phase;
	PhaseItemInfoListContainer	ItemsInfos;

	CmdItemInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdItemInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	PhaseItemResultList : public NPListSaveLoad<PhaseItemResultList>
{
public:
	int	Phase;
	int	ItemID;
	double	MatchingResult;

	PhaseItemResultList(void):Phase(0),ItemID(-1),MatchingResult(0){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	PhaseItemResultContainer : public NPListPackSaveLoad<PhaseItemResultList>
{
public:
	PhaseItemResultContainer(void){}

	virtual	PhaseItemResultList	*Create(void){	return new PhaseItemResultList();	}
};

inline	bool	PhaseItemResultList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)	return false;
	if(::Save(f,ItemID)==false)	return false;
	if(::Save(f,MatchingResult)==false)	return false;
	return true;
}
inline	bool	PhaseItemResultList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)	return false;
	if(::Load(f,ItemID)==false)	return false;
	if(::Load(f,MatchingResult)==false)	return false;
	return true;
}


class	CmdGatherItemResult : public GUIDirectMessage
{
public:
	PhaseItemResultContainer	Result;

	CmdGatherItemResult(LayersBase *base):GUIDirectMessage(base){}
	CmdGatherItemResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAdjustItemPosition: public GUIDirectMessage
{
public:
	int		TargetPhase;
	int		SourcePhase;
	CmdAdjustItemPosition(LayersBase *base):GUIDirectMessage(base){}
	CmdAdjustItemPosition(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoGeneration: public GUIDirectMessage
{
public:
	int	LocalPage;

	CmdAutoGeneration(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoGeneration(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAllItemInAllPhases: public GUIDirectMessage
{
public:
	int	LocalPage;

	CmdDeleteAllItemInAllPhases(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAllItemInAllPhases(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif