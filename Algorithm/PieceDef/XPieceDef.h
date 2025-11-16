#if	!defined(XPIECEDEF_H)
#define	XPIECEDEF_H


#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"
#include"XFlexAreaImageBuffer.h"

#define	PieceDefVersion	1

//========================================================================================

class	PieceDefInfo : public NPListSaveLoad<PieceDefInfo>
{
public:
	int		Page;
	int		Cx,Cy;
	int		x1,y1,x2,y2;
	double	MatchingRate;

	PieceDefInfo(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
};

class	PieceDefInfoContainer : public NPListPackSaveLoad<PieceDefInfo>
{
public:
	PieceDefInfoContainer(void){}
	virtual	PieceDefInfo	*Create(void);
	void	SetPage(int page);
};


inline	bool	PieceDefInfo::Load(QIODevice *f)
{
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
	if(::Load(f,MatchingRate)==false)
		return false;
	return true;
}
inline	bool	PieceDefInfo::Save(QIODevice *f)
{
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
	if(::Save(f,MatchingRate)==false)
		return false;
	return true;
}

inline	PieceDefInfo	*PieceDefInfoContainer::Create(void)
{
	return new PieceDefInfo();
}

inline	void	PieceDefInfoContainer::SetPage(int page)
{
	for(PieceDefInfo *a=GetFirst();a!=NULL;a=a->GetNext()){
		a->Page=page;
	}
}

//========================================================================================

class	PieceDefItem;
class	PieceDefInPage;

class	PieceDefDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:

	PieceDefDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	PieceDefDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	PieceDefDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	PieceDefDrawAttr	&operator=(PieceDefDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	PieceDefDrawAttr::PieceDefDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	PieceDefDrawAttr	&PieceDefDrawAttr::operator=(PieceDefDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	return *this;
}

inline	bool	PieceDefDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;

	return true;
}
inline	bool	PieceDefDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;

	return true;
}

//==========================================================================================
class	PieceDefThreshold : public AlgorithmThreshold
{
public:

	PieceDefThreshold(PieceDefItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	PieceDefItem : public AlgorithmItemPI
{
public:
	bool	Original;
	double	MatchingRate;
	int		SweepNumber;

	PieceDefItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new PieceDefItem();	}
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	const	PieceDefThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const PieceDefThreshold *)GetThresholdBaseReadable(base);	}
	PieceDefThreshold			*GetThresholdW(LayersBase *base=NULL){	return (PieceDefThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new PieceDefThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	Match(void);
};

class   PieceDefInPage : public AlgorithmInPagePI
{
public:
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

	PieceDefInPage(AlgorithmBase *parent);
	~PieceDefInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			PieceDefItem	*a=new PieceDefItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
private:
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)	override;
};

class	PieceDefBase : public AlgorithmBase
{
public:
	QColor	ColorPiece;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	double	CoEfficient;

	PieceDefBase(LayersBase *Base);
	virtual	~PieceDefBase(void);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new PieceDefInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("PieceDef");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigPieceDef.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

};

//=================================================================================
class	CmdAlgoCreatePieceDefManual : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAlgoCreatePieceDefManual(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoCreatePieceDefManual(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlgoReqSeed : public GUIDirectMessage
{
public:
	FlexAreaImageBuffer	*Seed;
	FlexArea			*OriginalArea;
	int					SweepNumber;

	CmdAlgoReqSeed(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoReqSeed(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlgoSweepSeed : public GUIDirectMessage
{
public:
	FlexAreaImageBuffer	*Seed;
	FlexArea			*OriginalArea;
	int					SweepNumber;

	CmdAlgoSweepSeed(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoSweepSeed(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlgoReqDList : public GUIDirectMessage
{
public:
	PieceDefInfoContainer		DefList;

	CmdAlgoReqDList(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoReqDList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlgoCopyItemFromOrg : public GUIDirectMessage
{
public:
	int				OrgGlobalPage;
	QByteArray		SeedData;
	int				SweepNumber;
	FlexArea		OriginalArea;
	int				SeedCount;

	CmdAlgoCopyItemFromOrg(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoCopyItemFromOrg(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlgoReqSeedData	 : public GUIDirectMessage
{
public:
	QByteArray		*SeedData;
	int				SeedCount;
	FlexArea		*OriginalArea;
	int					SweepNumber;

	CmdAlgoReqSeedData(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoReqSeedData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlgoMatchItems : public GUIDirectMessage
{
public:
	CmdAlgoMatchItems(LayersBase *base):GUIDirectMessage(base){}
	CmdAlgoMatchItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif