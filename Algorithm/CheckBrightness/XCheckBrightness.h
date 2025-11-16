#if	!defined(XCheckBrightness_h)
#define	XCheckBrightness_h


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

#define	CheckBrightnessVersion	1

class	CheckBrightnessItem;
class	CheckBrightnessInLayer;
class	CheckBrightnessInPage;
class	CheckBrightnessBase;


class	CheckBrightnessItem;
class	CheckBrightnessInPage;
//==========================================================================================

class	CheckBrightnessDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	CheckBrightnessDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	CheckBrightnessDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	CheckBrightnessDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	CheckBrightnessDrawAttr	&operator=(CheckBrightnessDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	CheckBrightnessDrawAttr::CheckBrightnessDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	CheckBrightnessDrawAttr	&CheckBrightnessDrawAttr::operator=(CheckBrightnessDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	CheckBrightnessDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	CheckBrightnessDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}
//========================================================================================
//========================================================================================
class	CheckBrightnessThreshold : public AlgorithmThreshold
{
public:
	CheckBrightnessThreshold(CheckBrightnessItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	CheckBrightnessItem : public AlgorithmItemPLITemplate<CheckBrightnessInLayer,CheckBrightnessInPage,CheckBrightnessBase>
{
	AlignmentPacket2D	*AVector;
public:
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
	int16		WidthL,WidthH;

	CheckBrightnessItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CheckBrightnessItem();	}
	const	CheckBrightnessThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CheckBrightnessThreshold *)GetThresholdBaseReadable(base);	}
	CheckBrightnessThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CheckBrightnessThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new CheckBrightnessThreshold(this);	}

	virtual	int32		GetItemClassType(void)			override{		return 0;		}
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	void	CopyThreshold(CheckBrightnessItem &src);

	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
								   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
private:
	void	NGFunc(ResultInItemRoot *Res);
};

class   CheckBrightnessInLayer : public AlgorithmInLayerPLITemplate<CheckBrightnessItem,CheckBrightnessInPage,CheckBrightnessBase>
{
public:
	CheckBrightnessInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
};

class   CheckBrightnessInPage : public AlgorithmInPagePLITemplate<CheckBrightnessItem,CheckBrightnessInLayer,CheckBrightnessBase>
{

public:
	CheckBrightnessInPage(AlgorithmBase *parent);
	~CheckBrightnessInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new CheckBrightnessInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)			override;

private:

};

class	CheckBrightnessBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;

	CheckBrightnessBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new CheckBrightnessInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)	override{	return QString("CheckBrightness");				}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigCheckBrightness.dat");	}

	/*
	virtual	bool	GeneralDataRelease(int32 Command,void *data);
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData);
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data);
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data);
	virtual	bool	GeneralDataReply(int32 Command,void *data);
	*/
};
//==================================================================================
#define	CheckBrightnessReqThresholdReqCommand					1
#define	CheckBrightnessReqThresholdSendCommand					2
#define	SetIndependentItemDataCommand_OnlyOneCheckBrightness	3
#define	SetIndependentItemDataCommand_AllCheckBrightness		4
#define	SetIndependentItemDataCommand_SetThreBrightnessThis		5
#define	SetIndependentItemDataCommand_SetThreBrightnessAll		6

class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	QString		ItemName;
	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		RegNumber;
	CheckBrightnessItem::_Condition	Condition;
	IntList		LayerList;
	FlexArea	Area;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CheckBrightnessInfoContainer;

class	CmdReqCheckBrightnessInfo : public GUIDirectMessage
{
public:
	CheckBrightnessInfoContainer	*Info;

	CmdReqCheckBrightnessInfo(LayersBase *Base):GUIDirectMessage(Base){}
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
	int		Layer;
	int		ItemID;
	bool	ResultOK;

	CmdReqCBPanelResult(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemInfo : public GUIDirectMessage
{
public:
	int			ItemID;
	int			Layer;
	QString		ItemName;
	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		RegNumber;
	CheckBrightnessItem::_Condition	Condition;

	CmdReqItemInfo(LayersBase *Base):GUIDirectMessage(Base){}
};
class	CmdUpdateManual : public GUIDirectMessage
{
public:
	int			ItemID;
	int			Layer;
	QString		ItemName;
	int16		ThreshL,ThreshH;
	int16		RepeatableCount;
	int16		RegNumber;
	CheckBrightnessItem::_Condition	Condition;

	CmdUpdateManual(LayersBase *Base):GUIDirectMessage(Base){}
};
//===================================================================================

class	CheckBrightnessInfo : public NPListSaveLoad<CheckBrightnessInfo>
{
public:
	int		ItemID;
	QString	ItemName;
	int		Page;
	int		Layer;
	int		Cx,Cy;
	int		x1,y1,x2,y2;
	CheckBrightnessItem::_Condition	Condition;
	int16		ThreshL,ThreshH;

	CheckBrightnessInfo(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	CheckBrightnessInfoContainer : public NPListPackSaveLoad<CheckBrightnessInfo>
{
public:
	CheckBrightnessInfoContainer(void){}
	virtual	CheckBrightnessInfo	*Create(void);
	void	SetPage(int page);
};


inline	bool	CheckBrightnessInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,Layer)==false)
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
	Condition=(CheckBrightnessItem::_Condition)d;
	if(::Load(f,ThreshL)==false)
		return false;
	if(::Load(f,ThreshH)==false)
		return false;
	return true;
}
inline	bool	CheckBrightnessInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,Layer)==false)
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
	int16	d=(int16)Condition;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,ThreshL)==false)
		return false;
	if(::Save(f,ThreshH)==false)
		return false;
	return true;
}

inline	CheckBrightnessInfo	*CheckBrightnessInfoContainer::Create(void)
{
	return new CheckBrightnessInfo();
}

inline	void	CheckBrightnessInfoContainer::SetPage(int page)
{
	for(CheckBrightnessInfo *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Page=page;
	}
}

//---------------------------------------------

class	CBPanelList : public NPListSaveLoad<CBPanelList>
{
public:
	int			GlobalPage;
	int			Layer;
	int			ItemID;
	QString		ItemName;
	int			RegNumber;
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
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,RegNumber)==false)
		return false;
	if(::Load(f,ResultOk)==false)
		return false;
	return true;
}

inline	bool	CBPanelList::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,RegNumber)==false)
		return false;
	if(::Save(f,ResultOk)==false)
		return false;
	return true;
}
#endif