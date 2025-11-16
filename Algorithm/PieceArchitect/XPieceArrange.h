/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPieceArrange.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPIECEARRANGE_H)
#define	XPIECEARRANGE_H

#include "XTypeDef.h"
#include "XGeneralFunc.h"
#include "XDataModelPageItem.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "NListComp.h"

//========================================================================================

class	PieceArrangeItem;
class	PieceArrangeInPage;

class	PieceDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	QString	DLLRoot;
	QString	DLLName;
	IntList LayerList;
	ListPageIDPack	SelectedLines;

	PieceDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	PieceDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	PieceDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	PieceDrawAttr	&operator=(PieceDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	PieceDrawAttr::PieceDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	PieceDrawAttr	&PieceDrawAttr::operator=(PieceDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	DLLRoot			=src.DLLRoot;
	DLLName			=src.DLLName;
	LayerList		=src.LayerList;
	SelectedLines	=src.SelectedLines;
	return *this;
}

inline	bool	PieceDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;
	if(::Save(f,DLLRoot)==false)
		return false;
	if(::Save(f,DLLName)==false)
		return false;
	if(LayerList.Save(f)==false)
		return false;
	if(SelectedLines.Save(f)==false)
		return false;
	return true;
}
inline	bool	PieceDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;
	if(::Load(f,DLLRoot)==false)
		return false;
	if(::Load(f,DLLName)==false)
		return false;
	if(LayerList.Load(f)==false)
		return false;
	if(SelectedLines.Load(f)==false)
		return false;
	return true;
}
//==========================================================================================
class	ReflectionAttr : public NPList<ReflectionAttr>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	bool	EnabledReflection;

	ReflectionAttr(void){	EnabledReflection=true;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ReflectionAttr	&operator=(ReflectionAttr &src);
};

class	ReflectionAttrPack : public NPListPack<ReflectionAttr>
{
public:
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	ReflectionAttrPack	&operator=(ReflectionAttrPack &src);
	bool	Check(QString DLLRoot,QString DLLName);
};

inline	ReflectionAttr	&ReflectionAttr::operator=(ReflectionAttr &src)
{
	DLLRoot	=src.DLLRoot;
	DLLName	=src.DLLName;
	EnabledReflection	=src.EnabledReflection;
	return *this;
}
inline	ReflectionAttrPack	&ReflectionAttrPack::operator=(ReflectionAttrPack &src)
{
	RemoveAll();
	for(ReflectionAttr *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		ReflectionAttr	*b=new ReflectionAttr();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

class	PieceItemInfo : public NPList<PieceItemInfo>
{
public:
	int32	X1,Y1;
	int32	X2,Y2;
	int32	MasterCode;

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	PieceItemInfo::Save(QIODevice *f)
{
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}
inline	bool	PieceItemInfo::Load(QIODevice *f)
{
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}

class	PieceItemInfoContainer : public NPListPack<PieceItemInfo>
{
public:
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	bool	PieceItemInfoContainer::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(PieceItemInfo *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false)
			return false;
	}
	return true;
}
inline	bool	PieceItemInfoContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		PieceItemInfo *c=new PieceItemInfo();
		if(c->Load(f)==false)
			return false;
		AppendList(c);
	}
	return true;
}

class	GetselectedPieceItemInfoPacket : public GUIDirectMessage
{
public:
	PieceItemInfoContainer	*Point;

	GetselectedPieceItemInfoPacket(LayersBase *base):GUIDirectMessage(base){}
	GetselectedPieceItemInfoPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



//==========================================================================================
class	PieceThreshold : public AlgorithmThreshold
{
public:

	PieceThreshold(PieceArrangeItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override	{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override	{	return true;	}
	virtual	bool	Save(QIODevice *f)					override	{	return true;	}
	virtual	bool	Load(QIODevice *f)					override	{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	PieceArrangeItem : public AlgorithmItemPI
{
	int32	MasterCode;		//==Piece kind ID
public:
	ReflectionAttrPack	ReflectionData;
	double				AlignmentProbability;

	PieceArrangeItem(void){	AlignmentProbability=0;	}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new PieceArrangeItem();	}
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	int		GetMasterCode(void)	{	return MasterCode;	}
	void	SetMasterCode(int code){	MasterCode=code;	}
	void	ListupMasterID(IntList &List);

	const	PieceThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const PieceThreshold *)GetThresholdBaseReadable(base);	}
	PieceThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (PieceThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new PieceThreshold(this);	}
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	//virtual	void	DrawResult    (ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;
	//virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	void	CalcFittableInfo(double AffinParam[6],int SearchDot);
	void	ExecuteAlignmentByAffin(double AffinParam[6]);
};

class	PieceSearchItem : public ServiceForLayers
{
public:
	int	MasterCode;
	int	ItemWidth;
	int	ItemHeight;
	PieceArrangeInPage	*ParentPage;
	PieceClass			*Piece;
	LogicDLL			*ExecutionDLLInPiece;
	AlgorithmBase		*ExecutionAlgorithmBaseInPiece;
	AlgorithmInPageRoot	*ExecutionAlgorithmPageInPiece;
	NPListPack<AlgorithmItemPointerList>	AlgorithmItemPointers;

	PieceSearchItem(PieceArrangeInPage *parentpage,LayersBase *Base,int _MasterCode);
	void	Initial(void);

	bool	Match	(int ExeID ,bool MasterImage ,int cx, int cy ,double &Result);
};


class   PieceArrangeInPage : public AlgorithmInPagePI
{
public:
	QMutex	MutexExecuteInitialAfterEditInLayer;

	PieceArrangeInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			PieceArrangeItem	*a=new PieceArrangeItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	//virtual	bool		Save(QIODevice *f);
	//virtual	bool		Load(QIODevice *f);
	void	ListupMasterID(IntList &List);
	void	ExecuteAlignmentForPiece(int SearchDot);
	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
										,FlexArea &area,AlgorithmBase *OriginBase
										,int ItemClass)override;
	bool	ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy) override;

	void	ExecuteAutoAlignmentForPiece(IntList &AutoSelectedMasterList);
	virtual	ExeResult	ExecuteInitialAfterEdit(int ExeID ,ResultInPageRoot *R,ExecuteInitialAfterEditInfo &EInfo)	override;
};

class	PieceArrangeBase : public AlgorithmBase
{
public:
	QColor	ColorPiece;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	int32	TransparentLevelNonSelection;
	QString	TempPath;
	QString	PieceGUIFile;
	QString	EditorPathFile;

	PieceArrangeBase(LayersBase *Base);
	~PieceArrangeBase(void);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return new PieceArrangeInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override	{	return QString("PieceArrange");		}
	virtual	QString	GetDefaultFileName(void)	override	{	return QString("ConfigPiece.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	void	ClearTempFiles(void);
	bool	CreateTempFiles(QString &ParamFileName ,QString &PixFileName);
	void	ListupMasterID(IntList &List);
	virtual	bool		ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
};

//=================================================================================


class	CmdPieceCreateTempFiles : public GUIDirectMessage
{
public:
	QString ParamFileName;
	QString PixFileName;

	CmdPieceCreateTempFiles(LayersBase *base):GUIDirectMessage(base){}
	CmdPieceCreateTempFiles(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPieceAdd : public GUIDirectMessage
{
public:
	int	X1,Y1,X2,Y2,X3,Y3,X4,Y4;
	int	MasterCode;
	int	GlobalPage;

	CmdPieceAdd(LayersBase *base):GUIDirectMessage(base){}
	CmdPieceAdd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateOnePiece : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			MasterCode;
	ReflectionAttrPack	ReflectionData;

	CmdCreateOnePiece(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateOnePiece(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReflectionAttrPack : public GUIDirectMessage
{
public:
	ReflectionAttrPack	ReflectionData;
	CmdReflectionAttrPack(LayersBase *base):GUIDirectMessage(base){}
	CmdReflectionAttrPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GetPieceItemInfoPacket : public GUIDirectMessage
{
public:
	int	ItemID;
	int	MasterCode;
	GetPieceItemInfoPacket(LayersBase *base):GUIDirectMessage(base){}
	GetPieceItemInfoPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GetReqMasterNamePacket : public GUIDirectMessage
{
public:
	int	MasterCode;
	QString	MasterName;

	GetReqMasterNamePacket(LayersBase *base):GUIDirectMessage(base){}
	GetReqMasterNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//------------------------------------------
class	PieceGridList : public NPListSaveLoad<PieceGridList>
{
public:
	int32	Page;
	int32	PieceID;
	int32	MasterCode;
	
	PieceGridList(void){	Page=-1;	PieceID=-1;	MasterCode=-1;	}
	virtual	bool	Save(QIODevice *f)
	{
		if(::Save(f,Page)==false)
			return false;
		if(::Save(f,PieceID)==false)
			return false;
		if(::Save(f,MasterCode)==false)
			return false;
		return true;
	}
	virtual	bool	Load(QIODevice *f)
	{
		if(::Load(f,Page)==false)
			return false;
		if(::Load(f,PieceID)==false)
			return false;
		if(::Load(f,MasterCode)==false)
			return false;
		return true;
	}
};

class	PieceGridContainer : public NPListPackSaveLoad<PieceGridList>
{
public:
	PieceGridList	*Create(void){	return new PieceGridList();	}
};

class	CmdReqPieceGrid : public GUIDirectMessage
{
public:
	PieceGridContainer	*PieceGridInfo;

	CmdReqPieceGrid(LayersBase *base):GUIDirectMessage(base){}
	CmdReqPieceGrid(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqSelectPiece : public GUIDirectMessage
{
public:
	int	PieceID;

	CmdReqSelectPiece(LayersBase *base):GUIDirectMessage(base){}
	CmdReqSelectPiece(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
