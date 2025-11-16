/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XNaming.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XNAMING
#define XNAMING

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "NListComp.h"

#define	NamingVersion	4

class	NamingItem;

class	ShowAndSetItemsNaming : public ShowAndSetItemsBaseClass
{
public:
	GUIFormBase	*Form;
};

class	NamingPointer : public NPList<NamingPointer>
{
public:
	int	GlobalX1;
	int	GlobalY1;
	int	GlobalX2;
	int	GlobalY2;
	int	GlobalPage;
	int	ItemID;
	int		IndexX,IndexY;
	QString	AreaName;

	int	LocalX1;
	int	LocalY1;
	int	LocalX2;
	int	LocalY2;

	NamingPointer(void)	{	IndexX=IndexY=-1;	}
	int	GetCenterX(void){	return (GlobalX1+GlobalX2)/2;	}
	int	GetCenterY(void){	return (GlobalY1+GlobalY2)/2;	}
	int	GetHeight(void)	{	return GlobalY2-GlobalY1;		}
	int	GetWidth(void)	{	return GlobalX2-GlobalX1;		}
	bool	SetName(char *FormatStr ,int MaxX ,int MaxY);
	static	QString	SetNameOnly(char *FormatStr ,int X ,int Y ,int MaxX ,int MaxY,int &Column ,int &Row);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	NamingPointer	&operator=(NamingPointer &src);
private:
	static	int		GetAlphaNumber(char *fp);
	static	char	*SetAlphaA(char *dp,int N);
	static	char	*SetAlphaa(char *dp,int N);
	static	char	*SetNumber(char *dp,int N);
};

class	NamingPointerStock : public NPListPack<NamingPointer>
{
public:
	NamingPointerStock(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	NamingPointerStock	&operator+=(NamingPointerStock &src);
};

inline	NamingPointer	&NamingPointer::operator=(NamingPointer &src)
{
	GlobalX1	=src.GlobalX1;
	GlobalY1	=src.GlobalY1;
	GlobalX2	=src.GlobalX2;
	GlobalY2	=src.GlobalY2;
	GlobalPage	=src.GlobalPage;
	ItemID		=src.ItemID;
	IndexX		=src.IndexX;
	IndexY		=src.IndexY;
	AreaName	=src.AreaName;
	LocalX1		=src.LocalX1;
	LocalY1		=src.LocalY1;
	LocalX2		=src.LocalX2;
	LocalY2		=src.LocalY2;
	return *this;
}

inline	bool	NamingPointer::Save(QIODevice *f)
{
	if(::Save(f,GlobalX1)==false)
		return false;
	if(::Save(f,GlobalY1)==false)
		return false;
	if(::Save(f,GlobalX2)==false)
		return false;
	if(::Save(f,GlobalY2)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,IndexX)==false)
		return false;
	if(::Save(f,IndexY)==false)
		return false;
	if(::Save(f,AreaName)==false)
		return false;
	if(::Save(f,LocalX1)==false)
		return false;
	if(::Save(f,LocalY1)==false)
		return false;
	if(::Save(f,LocalX2)==false)
		return false;
	if(::Save(f,LocalY2)==false)
		return false;
	return true;
}
	
inline	bool	NamingPointer::Load(QIODevice *f)
{
	if(::Load(f,GlobalX1)==false)
		return false;
	if(::Load(f,GlobalY1)==false)
		return false;
	if(::Load(f,GlobalX2)==false)
		return false;
	if(::Load(f,GlobalY2)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,IndexX)==false)
		return false;
	if(::Load(f,IndexY)==false)
		return false;
	if(::Load(f,AreaName)==false)
		return false;
	if(::Load(f,LocalX1)==false)
		return false;
	if(::Load(f,LocalY1)==false)
		return false;
	if(::Load(f,LocalX2)==false)
		return false;
	if(::Load(f,LocalY2)==false)
		return false;
	return true;
}

inline	bool	NamingPointerStock::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(NamingPointer *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
	
inline	bool	NamingPointerStock::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		NamingPointer	*c=new NamingPointer();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}

inline	NamingPointerStock	&NamingPointerStock::operator+=(NamingPointerStock &src)
{
	for(NamingPointer *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		NamingPointer *d=new NamingPointer();
		*d=*c;
		AppendList(d);
	}
	return *this;
}

class   ErrorGroupNaming : public ErrorGroup
{
public:
	NamingItem	*Item;

	ErrorGroupNaming(LayersBase *Base):ErrorGroup(Base){}
};

//=====================================================================

class	NamingNG : public NPListSaveLoad<NamingNG>
{
public:
	int		GlobalPage;
	int		ItemID;
	int		NGCount;

	NamingNG(void)	{	NGCount=0;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	NamingNGContainer : public NPListPackSaveLoad<NamingNG>
{
public:
	NamingNGContainer(void){}

	virtual	NamingNG	*Create(void){	return new NamingNG();	}
};

	
inline	bool	NamingNG::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,NGCount)==false)
		return false;
	return true;
}

inline	bool	NamingNG::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,NGCount)==false)
		return false;
	return true;
}

//=====================================================================
class	NamingDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorNaming;
	QColor	NegColorSelected;
	bool	EffectiveMode;
	bool	IneffectiveMode;

	NamingDrawAttr(void){}
	NamingDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	NamingDrawAttr( QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorNaming	=nncol;	
		NegColorSelected=nscol;	
		NegColorNaming.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};
//==========================================================================
class	NamingThreshold : public AlgorithmThreshold
{
public:

	NamingThreshold(NamingItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override	{	return true;	}
    virtual	bool	Load(QIODevice *f)	override	{	return true;	}
    virtual	int		GetSize(void)		const override	{	return sizeof(this);	}
};

class	NGAreaNaming
{
public:
	int	x1,y1,x2,y2;
	int	NGNumb;

	NGAreaNaming(void){}
};


class	NamingItem : public AlgorithmItemPI
{
public:
	//QString		AreaName;
	int				Row;
	int				Column;
	int				GroupID;
	AlignmentPacket2D	*AVector;
	int				ShiftX,ShiftY;
	int				Result;		//1:OK	2:NG

	int				NGAreaXLen;
	int				NGAreaYLen;
	int				NGAreaXNumb;
	int				NGAreaYNumb;
	NGAreaNaming	*NGAreaDim;

	NamingItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new NamingItem();	}
	const	NamingThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const NamingThreshold *)GetThresholdBaseReadable(base);	}
	NamingThreshold			*GetThresholdW(LayersBase *base=NULL){	return (NamingThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new NamingThreshold(this);	}

	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool	SaveUnique(QIODevice *f)				override;
	virtual	bool	LoadUnique(QIODevice *f)				override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResult(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	void	BindResult(ResultInItemRoot *Item,ResultPosList *RPos);
	void	MakeErrorGroup(NGImageContainerInPage *h);
	virtual	void	SetError(short e)	override;
	virtual	QString	GetComment(Type_ItemComment t)	override;
	virtual	void	ClearResult(void)	override;
};

inline	NamingItem::NamingItem(void)
{	
	Row			=-1;	
	Column		=-1;	
	GroupID		=-1;	
	AVector		=NULL;	
	Result		=0;
	NGAreaXLen	=0;
	NGAreaYLen	=0;
	NGAreaXNumb	=0;
	NGAreaYNumb	=0;
	NGAreaDim	=NULL;
}


class   NamingInPage : public AlgorithmInPagePI
{
public:
	NamingInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			NamingItem	*a=new NamingItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	BuildItemPointer(NamingPointerStock &NStocker);
	void	GetItemPointer(NamingPointerStock &NStocker);
	void	SetItemPointer(NamingPointerStock &NStocker);
	void	GenerateIndex(bool OnlySelected=true);

	NamingItem	*FindItem(const QString &areaname);
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	bool		ExecuteManageResult		(int ExeID ,ResultInspection *Res)	override;
};


class	NamingGroupList : public NPListSaveLoad<NamingGroupList>
{
public:
	QString		GroupName;
	int			GroupID;

	NamingGroupList(void){	GroupID=-1;	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	NamingGroupContainer : public NPListPackSaveLoad<NamingGroupList>
{
public:
	NamingGroupContainer(void){}

	virtual	NamingGroupList	*Create(void)	override{	return new NamingGroupList();	}
};

class	NamingBase : public AlgorithmBase
{
public:
	QColor	ColorNaming;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorNaming;
	QColor	NegColorSelected;
	bool	BindResultByArea;
	bool	ResetIndexAfterEdit;

	NamingGroupContainer	GroupData;

	NamingBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new NamingInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("Naming");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("Naming.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	int		GetMaxGroupID(void);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteManageResult		(int ExeID ,ResultInspection *Res)	override;

	bool	Name2GloalPos(QString Name ,int &XGlobalPos, int &YGlobalPos);
	bool	Name2LocalPos(QString Name ,int &Page ,int &XLocalPos, int &YLocalPos);
	bool	LocalPos2Name(int Page ,int XLocalPos, int YLocalPos ,QString &Name);
	bool	GlobalPos2Name(int XGlobalPos, int YGlobalPos ,QString &Name);

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
private:
	bool	ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage);
	bool	ExecuteManageResultOnPagePhase(int ExeID ,ResultInspection *Res 
											,int phase,int localPage
											,int ImageW,int	ImageH);
};
//==================================================================================

#define	SetIndependentItemDataCommand_OnlyOne	1
#define	NamingReqNameReqCommand		10
#define	NamingReqNameSendCommand	11

class	NamingNameReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	NamingNameReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	NamingNameSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;
	QString	AreaName;
	int		Row;
	int		Column;

	NamingNameSend(void);

	void	ConstructList(NamingNameReq *reqPacket,NamingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AddNamingAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	QString		AreaName;
	int			Column;
	int			Row;

	AddNamingAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddNamingAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	AddNamingGenerateName : public GUIDirectMessage
{
public:
	QString				FormatStr;
	NamingPointerStock	Stocker;

	AddNamingGenerateName(LayersBase *base):GUIDirectMessage(base){}
	AddNamingGenerateName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MakeAreaNamePacket : public GUIDirectMessage
{
public:
	QString				FormatStr;
	int					X,Y;
	int					CountX,CountY;
	QString				AreaName;
	int					Column;
	int					Row;

	MakeAreaNamePacket(LayersBase *base):GUIDirectMessage(base){}
	MakeAreaNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	ReqBuildItemPointerNaming : public GUIDirectMessage
{
public:
	NamingPointerStock	*Stocker;

	ReqBuildItemPointerNaming(LayersBase *base):GUIDirectMessage(base){}
	ReqBuildItemPointerNaming(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ReqBuildItemPointerNamingPage : public GUIDirectMessage
{
public:
	int	Page;
	NamingPointerStock	*Stocker;

	ReqBuildItemPointerNamingPage(LayersBase *base):GUIDirectMessage(base){}
	ReqBuildItemPointerNamingPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ReqSetItemPointerNaming : public GUIDirectMessage
{
public:
	NamingPointerStock	*Stocker;

	ReqSetItemPointerNaming(LayersBase *base):GUIDirectMessage(base){}
	ReqSetItemPointerNaming(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ReqNameFromPoint : public GUIDirectMessage
{
public:
	int XGlobalPos, YGlobalPos;
	QString	AreaName;

	ReqNameFromPoint(LayersBase *base):GUIDirectMessage(base){}
	ReqNameFromPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ReqItemFromAreaName : public GUIDirectMessage
{
public:
	QString		AreaName;
	NamingItem	*Item;

	ReqItemFromAreaName(LayersBase *base):GUIDirectMessage(base)		{	Item=NULL;	}
	ReqItemFromAreaName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Item=NULL;	}
};

class	ReqMaxGroupID : public GUIDirectMessage
{
public:
	int	MaxGroupID;

	ReqMaxGroupID(LayersBase *base):GUIDirectMessage(base)			{	MaxGroupID=0;	}
	ReqMaxGroupID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	MaxGroupID=0;	}
};

class	SetGroupCmd : public GUIDirectMessage
{
public:
	QString	GroupString;
	int		GroupID;

	SetGroupCmd(LayersBase *base):GUIDirectMessage(base)			{	GroupID=0;	}
	SetGroupCmd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GroupID=0;	}
};

class	ClearGroupCmd: public GUIDirectMessage
{
public:
	int		GroupID;

	ClearGroupCmd(LayersBase *base):GUIDirectMessage(base)			{	GroupID=0;	}
	ClearGroupCmd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GroupID=0;	}
};

class	ReqGroupData: public GUIDirectMessage
{
public:
	NamingGroupContainer	*GroupPointer;

	ReqGroupData(LayersBase *base):GUIDirectMessage(base)			{	GroupPointer=NULL;	}
	ReqGroupData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	GroupPointer=NULL;	}
};	

class	ReqNamingAreas: public GUIDirectMessage
{
public:
	QStringList		Areas;

	ReqNamingAreas(LayersBase *base):GUIDirectMessage(base)			{}
	ReqNamingAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};	

class	ReqGenerateIndex: public GUIDirectMessage
{
public:
	ReqGenerateIndex(LayersBase *base):GUIDirectMessage(base)			{}
	ReqGenerateIndex(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};	
class	CmdFindOverlappedItem: public GUIDirectMessage
{
public:
	FlexArea	*Area;
	NamingItem	*Item;

	CmdFindOverlappedItem(LayersBase *base):GUIDirectMessage(base)			{	Area=NULL;	Item=NULL;	}
	CmdFindOverlappedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Area=NULL;	Item=NULL;	}
};		
#endif