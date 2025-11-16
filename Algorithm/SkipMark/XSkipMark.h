#if	!defined(XSkipMark_h)
#define	XSkipMark_h


#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

#define	SkipMarkVersion	1

class	SkipMarkItem;
class	SkipMarkInLayer;
class	SkipMarkInPage;
class	SkipMarkBase;


class	SkipMarkItem;
class	SkipMarkInPage;
//==========================================================================================

class	SkipMarkDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	SkipMarkDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	SkipMarkDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	SkipMarkDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	SkipMarkDrawAttr	&operator=(SkipMarkDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	SkipMarkDrawAttr::SkipMarkDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	SkipMarkDrawAttr	&SkipMarkDrawAttr::operator=(SkipMarkDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	SkipMarkDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	SkipMarkDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}
//========================================================================================
//========================================================================================
class	SkipMarkThreshold : public AlgorithmThreshold
{
public:
	SkipMarkThreshold(SkipMarkItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	SkipMarkSourceAlgoList : public NPListSaveLoad<SkipMarkSourceAlgoList>,public ServiceForLayers
{
public:
	AlgorithmBase	*AlgoBase;
	IntList			IDList;

	SkipMarkSourceAlgoList(LayersBase *b);
	
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	SkipMarkSourceAlgoContainer : public NPListPackSaveLoad<SkipMarkSourceAlgoList>,public ServiceForLayers
{
public:
	SkipMarkSourceAlgoContainer(LayersBase *b):ServiceForLayers(b){}

	virtual	SkipMarkSourceAlgoList	*Create(void)	{	return new SkipMarkSourceAlgoList(GetLayersBase());	}
};


class	SkipMarkItem : public AlgorithmItemPLITemplate<SkipMarkInLayer,SkipMarkInPage,SkipMarkBase>
{
	AlignmentPacket2D	*AVector;
	bool	ResultON;	//Execute skip

public:
	AlgorithmBase	*NamingBase;
	int32			NamingID;		//Change result in this naming area
	SkipMarkSourceAlgoContainer		SourceItems;	//If this items are NG, Naming area results are changed

	AlgorithmItemRoot					*NamingItem;
	AlgorithmItemPointerListContainer	DestPointer;
	AlgorithmItemPointerListContainer	SourcePointer;

	SkipMarkItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new SkipMarkItem();	}
	virtual	void	SetParent(AlgorithmInLayerPLI *parent)	override;

	const	SkipMarkThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const SkipMarkThreshold *)GetThresholdBaseReadable(base);	}
	SkipMarkThreshold			*GetThresholdW(LayersBase *base=NULL){	return (SkipMarkThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new SkipMarkThreshold(this);	}

	virtual	int32		GetItemClassType(void)		override	{		return 0;		}
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	void	CopyThreshold(SkipMarkItem &src);

	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
private:

};

class   SkipMarkInLayer : public AlgorithmInLayerPLITemplate<SkipMarkItem,SkipMarkInPage,SkipMarkBase>
{
public:
	SkipMarkInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);
};

class   SkipMarkInPage : public AlgorithmInPagePLITemplate<SkipMarkItem,SkipMarkInLayer,SkipMarkBase>
{

public:
	SkipMarkInPage(AlgorithmBase *parent);
	~SkipMarkInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new SkipMarkInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:

};

class	SkipMarkBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;

	SkipMarkBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new SkipMarkInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("SkipMark");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigSkipMark.dat");	}

	/*
	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
	*/
};
//==================================================================================
#define	SkipMarkReqThresholdReqCommand					1
#define	SkipMarkReqThresholdSendCommand					2
#define	SetIndependentItemDataCommand_OnlyOneSkipMark	3
#define	SetIndependentItemDataCommand_AllSkipMark		4
#define	SetIndependentItemDataCommand_SetThreBrightnessThis		5
#define	SetIndependentItemDataCommand_SetThreBrightnessAll		6

class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	int32		Layer;
	FlexArea	Area;
	QString		ItemName;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	SkipMarkInfoContainer;

class	CmdReqSkipMarkInfo : public GUIDirectMessage
{
public:
	SkipMarkInfoContainer	*Info;

	CmdReqSkipMarkInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemInfo : public GUIDirectMessage
{
public:
	int			ItemID;
	int			Layer;	
	QString		ItemName;
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	CmdReqItemInfo(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdUpdateManual : public GUIDirectMessage
{
public:
	int			ItemID;
	int			Layer;
	QString		ItemName;
	QString		NamingDLLRoot;
	QString		NamingDLLName;
	int32		NamingID;

	CmdUpdateManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqSource : public GUIDirectMessage
{
public:
	int			ItemID;
	int			Layer;
	SkipMarkSourceAlgoContainer		*Sources;

	CmdReqSource(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdModifySource : public GUIDirectMessage
{
public:
	int			ItemID;
	int			Layer;
	SkipMarkSourceAlgoContainer		*Sources;

	CmdModifySource(LayersBase *Base):GUIDirectMessage(Base),Sources(NULL){}
};

//===================================================================================

class	SkipMarkInfo : public NPListSaveLoad<SkipMarkInfo>
{
public:
	int		ItemID;
	QString	ItemName;
	int		GlobalPage;
	int		Layer;
	int		Cx,Cy;
	int		x1,y1,x2,y2;
	QString	NamingDLLRoot;
	QString	NamingDLLName;
	QString	NamingItemName;
	int32	NamingItemID;

	SkipMarkInfo(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	SkipMarkInfoContainer : public NPListPackSaveLoad<SkipMarkInfo>
{
public:
	SkipMarkInfoContainer(void){}
	virtual	SkipMarkInfo	*Create(void);
	void	SetPage(int page);
};


inline	bool	SkipMarkInfo::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
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

	if(::Load(f,NamingDLLRoot)==false)
		return false;
	if(::Load(f,NamingDLLName)==false)
		return false;
	if(::Load(f,NamingItemName)==false)
		return false;
	if(::Load(f,NamingItemID)==false)
		return false;

	return true;
}
inline	bool	SkipMarkInfo::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
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

	if(::Save(f,NamingDLLRoot)==false)
		return false;
	if(::Save(f,NamingDLLName)==false)
		return false;
	if(::Save(f,NamingItemName)==false)
		return false;
	if(::Save(f,NamingItemID)==false)
		return false;

	return true;
}

inline	SkipMarkInfo	*SkipMarkInfoContainer::Create(void)
{
	return new SkipMarkInfo();
}
inline	void	SkipMarkInfoContainer::SetPage(int page)
{
	for(SkipMarkInfo *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->GlobalPage=page;
	}
}
//---------------------------------------------

class	CBPanelList : public NPListSaveLoad<CBPanelList>
{
public:
	int			GlobalPage;
	int			Layer;
	int			ItemID;
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
	if(::Save(f,ResultOk)==false)
		return false;
	return true;
}


//===================================================================================

class	ItemInfoList : public NPListSaveLoad<ItemInfoList>
{
public:
	int		ItemID;
	int		LibID;
	QString	ItemName;
	int		GlobalPage;
	int		Layer;
	int		Cx,Cy;
	int		x1,y1,x2,y2;

	ItemInfoList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	ItemInfoContainer : public NPListPackSaveLoad<ItemInfoList>
{
public:
	ItemInfoContainer(void){}
	virtual	ItemInfoList	*Create(void);
};


inline	bool	ItemInfoList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	if(::Load(f,GlobalPage)==false)
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

	return true;
}
inline	bool	ItemInfoList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,ItemName)==false)
		return false;

	if(::Save(f,GlobalPage)==false)
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

	return true;
}

inline	ItemInfoList	*ItemInfoContainer::Create(void)
{
	return new ItemInfoList();
}

#endif
