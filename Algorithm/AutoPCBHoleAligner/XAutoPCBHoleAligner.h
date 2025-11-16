/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoPCBHoleAligner\XAutoPCBHoleAligner.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAutoPCBHoleAligner_H)
#define	XAutoPCBHoleAligner_H

#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XServiceForLayers.h"
#include "XDataModelPageItem.h"
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"

#define	AutoPCBHoleAlignerVersion	1
#define	DefLibTypeAutoPCBHoleAligner			13

class	AutoPCBHoleAlignerHole;
class	AutoPCBHoleAlignerBase;
class	AutoPCBHoleAlignerInPage;
class	AASheetInfos;

class	AutoPCBHoleAlignerDrawAttr : public AlgorithmDrawAttr
{
public:
	bool	DrawHole;
	bool	DrawFringe;
	IntList	SelectedLDList;

	AutoPCBHoleAlignerDrawAttr(void)
		: AlgorithmDrawAttr(Qt::green,100,Qt::yellow,100,Qt::red,100){}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};


inline	bool	AutoPCBHoleAlignerDrawAttr::Save(QIODevice *f)
{	
	if(::Save(f,DrawHole)==false)
		return false;
	if(::Save(f,DrawFringe)==false)
		return false;
	if(SelectedLDList.Save(f)==false){
		return false;
	}
	return true;
}
inline	bool	AutoPCBHoleAlignerDrawAttr::Load(QIODevice *f)
{	
	if(::Load(f,DrawHole)==false)
		return false;
	if(::Load(f,DrawFringe)==false)
		return false;
	if(SelectedLDList.Load(f)==false){
		return false;
	}
	return true;
}

//----------------------------------------------------------------------

class	AutoPCBHoleAlignerLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	ColorLogic	PickupHoleColor;
	bool		StartupExecute;
	int			ExpandForPickup;
	int			MinDiameter;
	int			MaxDiameter;
	int			FringeDot;
	bool		CheckOutside;
	int			MaxSearch;
	int			ThresholdDiff;

	int			FromOtherAlgorithmCount;
public:

	AutoPCBHoleAlignerLibrary(int LibType,LayersBase *Base);
	virtual	~AutoPCBHoleAlignerLibrary(void){}

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	AutoPCBHoleAlignerLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	AutoPCBHoleAlignerLibraryContainer : public AlgorithmLibraryContainer
{
public:
	AutoPCBHoleAlignerLibraryContainer(LayersBase *base);
	virtual	~AutoPCBHoleAlignerLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeAutoPCBHoleAligner;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "AutoPCBHoleAligner Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new AutoPCBHoleAlignerLibrary(GetLibType(),GetLayersBase());	}
};

class	AutoPCBHoleAlignerThreshold : public AlgorithmThreshold
{
public:
	ColorLogic	PickupHoleColor;
	int			ExpandForPickup;
	int			MinDiameter;
	int			MaxDiameter;
	int			FringeDot;
	bool		CheckOutside;
	bool		FromOtherAlgorithm;
	int			FromOtherAlgorithmIndex;

	AutoPCBHoleAlignerThreshold(AutoPCBHoleAlignerHole *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

//-----------------------------------------------------------------------------------------

class	MatchingHoleClass : public ServiceForLayers
{
	int	HoleRadius;

public:
	struct	PointClass
	{
		int	X,Y;
	};
	struct	HoleIndexStruct
	{
		int		OffsetX;
		int		OffsetY;
		BYTE	Value;
	};
private:
	struct	HoleIndexStruct	HoleTestData[16];	//５点は穴、１１点は周辺

	int		XCount;
	int		YCount;
	int		Cx,Cy;
	int32	AddA;
	int32	AddA2;
public:
	MatchingHoleClass(LayersBase *Base):ServiceForLayers(Base){}

	void	Initial(int holeRadius);

	int		ExecuteMatch(ImageBuffer *Image[],BYTE **Mask 
						,struct PointClass PointDim[],int MaxPointDim
						,double MatchingRate1, double MatchingRate2);
private:
	double	MatchOne(int X ,int Y ,ImageBuffer *IBuff ,double	&Var);
	void	BreakMask(BYTE **Mask,int Px,int Py);

	void	SearchFittablePosition(ImageBuffer *Image[]
								,int PosX,int PosY
								,int &mx,int &my);
};

class	AutoPCBHoleAlignerHole : public AlgorithmItemPI
{
public:
	FlexArea	FringeArea;

	AutoPCBHoleAlignerHole(void);
	~AutoPCBHoleAlignerHole(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AutoPCBHoleAlignerHole();	}
	const	AutoPCBHoleAlignerThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AutoPCBHoleAlignerThreshold *)GetThresholdBaseReadable(base);	}
	AutoPCBHoleAlignerThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AutoPCBHoleAlignerThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold		*CreateThresholdInstance(void)	override	{	return new AutoPCBHoleAlignerThreshold(this);	}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)override;

private:
};


class	AutoPCBHoleAlignerInPage : public AlgorithmInPagePI
{

public:
	int	XLen;
	int	YLen;
	int	XByte;

	BYTE	**BitmapFringe;

	AutoPCBHoleAlignerInPage(AlgorithmBase *parent);
	~AutoPCBHoleAlignerInPage(void);

	void	InitialAlloc(void);
	virtual	void	Release(void)	override;

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			AutoPCBHoleAlignerHole	*a=new AutoPCBHoleAlignerHole();	
			a->SetParent(this);
			return a;
		}
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID 
												,ResultInPageRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo) override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	//bool	GetBitmapFringe(int x ,int y)	{	return (BitmapFringe[y][x>>3]&(0x80>>(x&7)))!=0?true:false;	}
	bool	GetBitmapFringe(int x ,int y);

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	//const	BYTE	**GetMaskBitmap(void);

private:
	void	MakeBitmap(const BYTE	**Mask
					 ,BYTE	**TmpMap
					 ,ImagePointerContainer &MasterImages
					 ,AutoPCBHoleAlignerLibrary &Lib
					 ,BYTE	**HoleMap);
	bool	CheckOutside(int CenterX ,int CenterY
						 ,ImagePointerContainer &MasterImages
						 ,int MaxSearch ,int ThresholdDiff);
};

inline bool	AutoPCBHoleAlignerInPage::GetBitmapFringe(int x ,int y)	{
	if(BitmapFringe==NULL) return false;
	return (BitmapFringe[y][x>>3]&(0x80>>(x&7)))!=0?true:false;
}

class	AutoPCBHoleAlignerBase : public AlgorithmBase
{
public:
	AlgorithmLibraryListContainer	AdoptedLib;
	double		AdoptedRate;
	QList<int>	DeleteLibIDListFromOtherAlgorithm;
	QList<int>	DeleteIndexListFromOtherAlgorithm;

	AutoPCBHoleAlignerBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new AutoPCBHoleAlignerInPage(((AutoPCBHoleAlignerBase *)parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("AutoPCBHoleAligner");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigAutoPCBHoleAligner.dat");		}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID 
												,ResultBaseForAlgorithmRoot *Res 
												,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	int		GetFromOtherAlgorithmCount(int LibID)			{	return FromOtherAlgorithmCount[StartupExecuteLibIDList.indexOf(LibID)];	}
	void	SetFromOtherAlgorithmCount(int LibID,int data)	{	FromOtherAlgorithmCount[StartupExecuteLibIDList.indexOf(LibID)]=data;	}

private:
	QList<int>	StartupExecuteLibIDList;
	int			*FromOtherAlgorithmCount;
};

//==================================================================================

class	AAHoleInfoList : public NPList<AAHoleInfoList>
{
public:
	int			ID;
	int			MinDiameter;
	int			MaxDiameter;
	int			FringeDot;

	AAHoleInfoList(void){}
	AAHoleInfoList(AAHoleInfoList &src)
		:ID(src.ID)
		,MinDiameter(src.MinDiameter)
		,MaxDiameter(src.MaxDiameter)
		,FringeDot(src.FringeDot)
	{}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	AAHoleInfoList	&operator=(AAHoleInfoList &src);
};

class	AAHoleInfos : public NPListPack<AAHoleInfoList>
{
public:
	AAHoleInfos(void){}
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	AAHoleInfos	&operator=(AAHoleInfos &src);
};

inline	AAHoleInfoList	&AAHoleInfoList::operator=(AAHoleInfoList &src)
{
	ID			=src.ID;
	MinDiameter	=src.MinDiameter;
	MaxDiameter	=src.MaxDiameter;
	FringeDot	=src.FringeDot;
	return *this;
}

inline	bool	AAHoleInfoList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	if(::Load(f,MinDiameter)==false)
		return false;	
	if(::Load(f,MaxDiameter)==false)
		return false;	
	if(::Load(f,FringeDot)==false)
		return false;	
	return true;
}
inline	bool	AAHoleInfoList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	if(::Save(f,MinDiameter)==false)
		return false;	
	if(::Save(f,MaxDiameter)==false)
		return false;	
	if(::Save(f,FringeDot)==false)
		return false;	
	return true;
}
inline	bool	AAHoleInfos::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		AAHoleInfoList *a=new AAHoleInfoList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
inline	bool	AAHoleInfos::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(AAHoleInfoList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

inline	AAHoleInfos	&AAHoleInfos::operator=(AAHoleInfos &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

//==================================================================================

class	CmdCreateTempAutoPCBHoleAlignerLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempAutoPCBHoleAlignerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAutoPCBHoleAlignerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAutoPCBHoleAlignerLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAutoPCBHoleAlignerLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoPCBHoleAlignerLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadAutoPCBHoleAlignerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadAutoPCBHoleAlignerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAutoPCBHoleAlignerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAutoPCBHoleAlignerLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAutoPCBHoleAlignerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAutoPCBHoleAlignerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteAutoPCBHoleAlignerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAutoPCBHoleAlignerLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAutoPCBHoleAlignerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertAutoPCBHoleAlignerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAutoPCBHoleAlignerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAutoPCBHoleAlignerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdUpdateAutoPCBHoleAlignerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAutoPCBHoleAlignerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAutoPCBHoleAlignerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateAutoPCBHoleAlignerHolePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;

	CmdCreateAutoPCBHoleAlignerHolePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAutoPCBHoleAlignerHolePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetAutoPCBHoleAlignerLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetAutoPCBHoleAlignerLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAutoPCBHoleAlignerLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetHoleInfo: public GUIDirectMessage
{
public:
	AAHoleInfos	AAInfoData;

	CmdGetHoleInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdGetHoleInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqAutoPCBHoleAlignerDrawMode: public GUIDirectMessage
{
public:
	bool	DrawHole;
	bool	DrawFringe;
	IntList	SelectedLDList;

	GUICmdReqAutoPCBHoleAlignerDrawMode(LayersBase *base):GUIDirectMessage(base){}
	GUICmdReqAutoPCBHoleAlignerDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdReqAutoPCBHoleAlignerEnumLibs: public GUIDirectMessage
//	StartupExecute=trueのライブラリのLibIDリストコンテナを外部から所得する
{
public:
	IntList	LibIDList;
	CmdReqAutoPCBHoleAlignerEnumLibs(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAutoPCBHoleAlignerEnumLibs(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdReqAutoPCBHoleAlignerExecuteInitialAfterEdit: public GUIDirectMessage
//	AutoPCBHoleAlignerのExecuteInitialAfterEditを実行する
{
public:
	CmdReqAutoPCBHoleAlignerExecuteInitialAfterEdit(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAutoPCBHoleAlignerExecuteInitialAfterEdit(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdReqAutoPCBHoleAlignerShowPasteCreateWithShape: public GUIDirectMessage
//	アルゴリズム領域貼り付け対応
{
public:
	int	LibID;
	int	FromOtherAlgorithmIndex;
	CmdReqAutoPCBHoleAlignerShowPasteCreateWithShape(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAutoPCBHoleAlignerShowPasteCreateWithShape(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=========================================================================
class	CmdReqAutoPCBHoleAlignerDeleteIndexFromOtherAlgorithm: public GUIDirectMessage
//	アルゴリズム領域削除対応
{
public:
	int	LibID;
	int	DeleteIndex;
	CmdReqAutoPCBHoleAlignerDeleteIndexFromOtherAlgorithm(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAutoPCBHoleAlignerDeleteIndexFromOtherAlgorithm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif