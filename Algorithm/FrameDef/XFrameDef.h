#if	!defined(XFrameDEF_H)
#define	XFrameDEF_H

#include <QImage>
#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"
#include "XFlexAreaImageBuffer.h"
#include "NListComp.h"

#define	FrameDefVersion	1

//==========================================================================================

class	FrameList : public NPListSaveLoad<FrameList>
{
public:
	int32	GroupNumber;
	int32	FrameNumber;
	bool	Original;
	ListPageIDPack	Items;
	int32	GlobalX1;
	int32	GlobalY1;
	int32	GlobalX2;
	int32	GlobalY2;

	FrameList(void){
		GroupNumber	=-1;
		FrameNumber	=-1;
		GlobalX1	=-1;
		GlobalY1	=-1;
		GlobalX2	=-1;
		GlobalY2	=-1;
		Original	=false;
	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	FrameList	&operator=(FrameList &src);
};

inline	bool	FrameList::Save(QIODevice *f)
{
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,FrameNumber)==false)
		return false;
	if(::Save(f,GlobalX1)==false)
		return false;
	if(::Save(f,GlobalY1)==false)
		return false;
	if(::Save(f,GlobalX2)==false)
		return false;
	if(::Save(f,GlobalY2)==false)
		return false;
	if(::Save(f,Original)==false)
		return false;
	if(Items.Save(f)==false)
		return false;
	return true;
}
inline	bool	FrameList::Load(QIODevice *f)
{
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,FrameNumber)==false)
		return false;
	if(::Load(f,GlobalX1)==false)
		return false;
	if(::Load(f,GlobalY1)==false)
		return false;
	if(::Load(f,GlobalX2)==false)
		return false;
	if(::Load(f,GlobalY2)==false)
		return false;
	if(::Load(f,Original)==false)
		return false;
	if(Items.Load(f)==false)
		return false;
	return true;
}

inline	FrameList	&FrameList::operator=(FrameList &src)
{
	NPListSaveLoad<FrameList>::operator=(src);
	return *this;
}

class	FrameContainer : public NPListPackSaveLoad<FrameList>
{
public:
	virtual	FrameList	*Create(void){	return new FrameList();	}
};

//========================================================================================

class	FrameDefItem;
class	FrameDefInPage;

class	FrameDefDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	Overlapped;

	FrameDefDrawAttr(LayersBase *Base):ServiceForLayers(Base){	Overlapped=true;	}
	FrameDefDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	FrameDefDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	FrameDefDrawAttr	&operator=(FrameDefDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	FrameDefDrawAttr::FrameDefDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	Overlapped	=true;
}

inline	FrameDefDrawAttr	&FrameDefDrawAttr::operator=(FrameDefDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	Overlapped	=src.Overlapped;
	return *this;
}

inline	bool	FrameDefDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;
	if(::Save(f,Overlapped)==false)
		return false;
	return true;
}
inline	bool	FrameDefDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;
	if(::Load(f,Overlapped)==false)
		return false;
	return true;
}

//==========================================================================================
class	FrameDefThreshold : public AlgorithmThreshold
{
public:

	FrameDefThreshold(FrameDefItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	FrameDefItem : public AlgorithmItemPI
{
	double	LastZoomRate;
	QImage	OriginImage;
public:
	bool		Original;
	int32		GroupNumber;
	int32		FrameNumber;
	FlexArea	GlobalArea;

	int				NGAreaXLen;
	int				NGAreaYLen;
	int				NGAreaXNumb;
	int				NGAreaYNumb;
	ErrorGroupPack	Result;
	QStringList		ResList;

	FrameDefItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new FrameDefItem();	}
	virtual	void	SetArea(const FlexArea &area)	override;
	virtual	void    MoveTo(int dx ,int dy)	override;

	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;

	const	FrameDefThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const FrameDefThreshold *)GetThresholdBaseReadable(base);	}
	FrameDefThreshold			*GetThresholdW(LayersBase *base=NULL){	return (FrameDefThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new FrameDefThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	//virtual	void	DrawResult    (ResultInItemRoot &Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate);
	//virtual	void	DrawResultItem(ResultInItemRoot &Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG);
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	MakeMasterImage(QImage &MasterImage,double ZoomRate
							, int Gx1,int Gy1,int Gx2,int Gy2,int DestGCx,int DestGCy);
	void	MakeMasterImageFromOther(QImage &MasterImage,double ZoomRate,int Lx1,int Ly1,int Lx2,int Ly2);
	void	BindResult(ResultInItemRoot *Item,ResultPosList *RPos);
	void	ResizeResult(void);
};

class   FrameDefInPage : public AlgorithmInPagePI
{
public:

	FrameDefInPage(AlgorithmBase *parent);
	~FrameDefInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			FrameDefItem	*a=new FrameDefItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	FrameDefItem	*FindOriginalInGroup(int GroupNumber);

	virtual	bool	ExecuteManageResult	(int ExeID ,ResultInspection *Res)	override;
};

class	FrameDefBase : public AlgorithmBase
{
public:
	QColor	ColorFrame;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;

	FrameDefBase(LayersBase *Base);
	~FrameDefBase(void);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new FrameDefInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("FrameDef");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigFrameDef.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	ExeResult	ExecuteManageResult		(int ExeID ,ResultInspection *Res)	override;
	bool		ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage);
};

//=================================================================================

class	GroupFrameNumberList : public NPListSaveLoad<GroupFrameNumberList>
{
public:
	int	GroupNumber;
	int	FrameNumber;

	GroupFrameNumberList(void){
		GroupNumber=-1;
		FrameNumber=-1;
	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	GroupFrameNumberContainer : public NPListPackSaveLoad<GroupFrameNumberList>
{
public:
	virtual	GroupFrameNumberList	*Create(void)	{	return new GroupFrameNumberList();	}
};
	
inline	bool	GroupFrameNumberList::Save(QIODevice *f)
{
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,FrameNumber)==false)
		return false;
	return true;
}

inline	bool	GroupFrameNumberList::Load(QIODevice *f)
{
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,FrameNumber)==false)
		return false;
	return true;
}
//=================================================================================

class	GroupFrameNumberResultList : public NPListSaveLoad<GroupFrameNumberResultList>
{
public:
	int	GroupNumber;
	int	FrameNumber;
	int	NGCount;

	GroupFrameNumberResultList(void){
		GroupNumber=-1;
		FrameNumber=-1;
		NGCount		=0;
	}

	GroupFrameNumberResultList	&operator=(const GroupFrameNumberResultList &src)
	{	
		GroupNumber	=src.GroupNumber;
		FrameNumber	=src.FrameNumber;
		NGCount		=src.NGCount;
		return *this;
	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	GroupFrameNumberResultContainer : public NPListPackSaveLoad<GroupFrameNumberResultList>
{
public:
	virtual	GroupFrameNumberResultList	*Create(void)	{	return new GroupFrameNumberResultList();	}
};
	
inline	bool	GroupFrameNumberResultList::Save(QIODevice *f)
{
	if(::Save(f,GroupNumber)==false)
		return false;
	if(::Save(f,FrameNumber)==false)
		return false;
	if(::Save(f,NGCount)==false)
		return false;
	return true;
}

inline	bool	GroupFrameNumberResultList::Load(QIODevice *f)
{
	if(::Load(f,GroupNumber)==false)
		return false;
	if(::Load(f,FrameNumber)==false)
		return false;
	if(::Load(f,NGCount)==false)
		return false;
	return true;
}


class	CmdAlgoCreateFrameDefManual : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		GroupNumber;
	int		FrameNumber;
	bool	Original;

	CmdAlgoCreateFrameDefManual(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoCreateFrameDefManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAckFrameContainer : public GUIDirectMessage
{
public:
	FrameContainer	*ItemContainer;

	CmdAckFrameContainer(LayersBase *base):GUIDirectMessage(base){}
	CmdAckFrameContainer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdAckMaxFrameNumber : public GUIDirectMessage
{
public:
	int		GroupNumber;
	int		FrameNumber;
	bool	OriginExists;

	CmdAckMaxFrameNumber(LayersBase *base):GUIDirectMessage(base){}
	CmdAckMaxFrameNumber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSetItemNumber : public GUIDirectMessage
{
public:
	int		ItemID;
	int		GroupNumber;
	int		FrameNumber;
	bool	Original;

	CmdSetItemNumber(LayersBase *base):GUIDirectMessage(base){}
	CmdSetItemNumber(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGroupList : public GUIDirectMessage
{
public:
	IntList	GroupList;

	CmdReqGroupList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGroupList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGroupFrameList : public GUIDirectMessage
{
public:
	GroupFrameNumberResultContainer	GroupFrameList;

	CmdReqGroupFrameList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGroupFrameList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGroupFrameResultList : public GUIDirectMessage
{
public:
	GroupFrameNumberResultContainer	GroupFrameList;

	CmdReqGroupFrameResultList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGroupFrameResultList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdOutputResult  : public GUIDirectMessage
{
public:
	int		GroupNumber;
	int		FrameNumber;
	int		phase;
	ResultInspection *Res;
	QStringList	*ResList;

	CmdOutputResult(LayersBase *base):GUIDirectMessage(base){}
	CmdOutputResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
 

#endif