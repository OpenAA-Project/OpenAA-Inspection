/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicClassify\XDynamicClassify.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XDynamicClassify_H
#define XDynamicClassify_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XGeneralFunc.h"
#include "XStandardCommand.h"

#define	DynamicClassifyVersion		1
#define	DefLibTypeDynamicClassify	37


class	DynamicClassifyItem;

class	ShowAndSetItemsDynamicClassify : public ShowAndSetItemsBaseClass
{
public:
	GUIFormBase	*Form;
};

class	SelectAreaMode
{
public:
	bool	CopyModeItem;
	bool	CopyModeCore;
	bool	CopyModeMaxZone;
	bool	CopyModeMinZone;
	bool	CopyModeBare;
	bool	CopyModeInside;
	bool	CopyModeOutlineI;
	bool	CopyModeOutlineT;
	bool	CopyModeOutlineO;

	SelectAreaMode(void);

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	DynamicClassifyLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
    int32		MinAreaSize;
    int32		MaxAreaSize;
    int32		MinAreaDots;
    int32		MaxAreaDots;

	int32		NoiseDot;
	int32		ShrinkDot;
	int32		Priority;
	int32		VariableWidth;

	int32		OutlineOWidth;
	int32		OutlineTWidth;
	int32		OutlineIWidth;
	int32		OverlapInEachArea;
	int32		AdjustBrightH;
	int32		AdjustBrightL;

	bool		StartupExecute;

	ColorLogic	PickupColor;

	bool		MakeEachArea;

public:
	DynamicClassifyLibrary(int LibType,LayersBase *Base);
	virtual	~DynamicClassifyLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DynamicClassifyLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImagePointerContainer &ImageBuff
									 ,const BYTE **MaskBitmap
									 ,BYTE **BmpPoint 
									 ,BYTE **OcupyMap
									 ,int Page
									 ,int XByte ,int XLen ,int YLen
									 ,int OmitZoneDot);
	void	MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int Page
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &TmpData);
};

class	DynamicClassifyLibraryContainer : public AlgorithmLibraryContainer
{
public:
	DynamicClassifyLibraryContainer(LayersBase *base);
	virtual	~DynamicClassifyLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeDynamicClassify;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "DynamicClassify Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DynamicClassifyLibrary(GetLibType(),GetLayersBase());	}
};


class	DynamicClassifyThreshold : public AlgorithmThreshold
{
public:
	int32		NoiseDot;
	int32		ShrinkDot;
	int32		Priority;
	int32		VariableWidth;

	int32		OutlineOWidth;
	int32		OutlineTWidth;
	int32		OutlineIWidth;
	int32		OverlapInEachArea;

	int32		AdjustBrightH;
	int32		AdjustBrightL;

	bool		StartupExecute;

	ColorLogic	PickupColor;

	bool		MakeEachArea;

	DynamicClassifyThreshold(DynamicClassifyItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class	DynamicClassifyItem : public AlgorithmItemPI
{
	BYTE		**TmpMap;
	BYTE		**TmpMap2;
	BYTE		**TmpMap3;
	BYTE		**TmpMap4;
	int			TmpXByte;
	int			TmpYLen;
	int			Hx1,Hy1,Hx2,Hy2;	//Tmp領域範囲

	QRgb		CenterBright;
	int			CoreCenterX,CoreCenterY;

public:
	AlignmentPacket2D	*AVector;

	FlexArea	CoreArea;	//不変領域
	FlexArea	MaxZone;
	FlexArea	MinZone;

	//Generated Areas in each inspection
	FlexArea	BareArea;
	FlexArea	InsideArea;
	FlexArea	OutlineOArea;
	FlexArea	OutlineTArea;
	FlexArea	OutlineIArea;


	DynamicClassifyItem(void);
	~DynamicClassifyItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DynamicClassifyItem();	}
	virtual	FlexArea	&GetArea(int UniqueAreaType_Code)	override;

	const	DynamicClassifyThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const DynamicClassifyThreshold *)GetThresholdBaseReadable(base);	}
	DynamicClassifyThreshold			*GetThresholdW(LayersBase *base=NULL){	return (DynamicClassifyThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new DynamicClassifyThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	ClipboardAlgorithmItem	*CreateClipboardItem(void)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override	{	return _ER_true;	}

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
								   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	bool	InitializeBuffer(void);
	void	MakeExecuableArea(ImagePointerContainer &Images , int dx, int dy);
	void	MakeShowMap( bool	MapBareArea
						,bool	MapInsideArea
						,bool	MapOutlineIArea
						,bool	MapOutlineTArea
						,bool	MapOutlineOArea
						,BYTE	**RetMap);

private:
	int		GetCenterBright(int BrList[256]);
};

class	CmdGetDynamicClassifyBitmap : public GUIDirectMessage
//	領域マップを取得するとき、このパケットでDynamicClassifyInPage　に　TransmitDirectlyする
{
public:
	bool	BareArea;
	bool	InsideArea;
	bool	OutlineIArea;
	bool	OutlineTArea;
	bool	OutlineOArea;
	BYTE	**RetMap;

	CmdGetDynamicClassifyBitmap(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDynamicClassifyBitmap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class   DynamicClassifyInPage : public AlgorithmInPagePI
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
public:

	DynamicClassifyInPage(AlgorithmBase *parent);
	~DynamicClassifyInPage(void);

	void	CreatePickupBmpBuff(void);
	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			DynamicClassifyItem	*a=new DynamicClassifyItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;


	void	PickupTest(DynamicClassifyLibrary &LibData);
	void	GenerateBlocks(DynamicClassifyLibrary *LibDim[],int LibDimNumb);

	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,int32 ItemID,AlgorithmItemRoot *Data,IntList &EdittedMemberID
											,QByteArray &Something,QByteArray &AckData)	override;
};

class	DynamicClassifyBase : public AlgorithmBase
{
public:
	SelectAreaMode	ModeForCopy;

	QColor		ColorPickup;
	QColor		ColorItem	;
	QColor		ColorCore	;
	QColor		ColorMaxZone	;
	QColor		ColorMinZone	;
	QColor		ColorBare;
	QColor		ColorInside;
	QColor		ColorOutlineI	;
	QColor		ColorOutlineT	;
	QColor		ColorOutlineO	;
	QColor		ColorSelected	;
	QColor		ColorActive	;
	int32		Transparent;

	int32		OmitZoneDot;

	DynamicClassifyBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new DynamicClassifyInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("DynamicClassify");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigDynamicClassify.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)				override;
	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	int		GetUniqueAreaType(UniqueAreaType UTypeDim[] ,int MaxDimCount)	override;
};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne		1
#define	SetIndependentItemDataCommand_All			2
#define	DynamicClassifyReqThresholdReqCommand		3
#define	DynamicClassifyReqThresholdSendCommand		4
#define	DynamicClassifyReqTryThresholdCommand		5
#define	DynamicClassifySendTryThresholdCommand		6
#define	SetIndependentItemAddInPlaceColor			10
//==================================================================================

class	DynamicClassifyDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	ShowCore;
	bool	ShowMaxZone;
	bool	ShowMinZone;
	bool	ShowBare;
	bool	ShowInside;
	bool	ShowOutlineI;
	bool	ShowOutlineT;
	bool	ShowOutlineO;

	DynamicClassifyDrawAttr(void){}
	DynamicClassifyDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	DynamicClassifyDrawAttr( 
					 QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdDynamicClassifyDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdDynamicClassifyDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

//==================================================================================

class	DynamicClassifyThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	DynamicClassifyThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DynamicClassifyThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	ColorLogic	PickupColor;

	DynamicClassifyThresholdSend(void);

	void	ConstructList(DynamicClassifyThresholdReq *reqPacket,DynamicClassifyBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	DynamicClassifyReqTryThreshold
{
public:
	int32	GlobalPage;
	int		ItemID;	
	DynamicClassifyItem	Threshold;

	DynamicClassifyReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	DynamicClassifySendTryThreshold : public AddedDataClass
{
public:
	int		Error;

	DynamicClassifySendTryThreshold(void);

	void	ConstructList(DynamicClassifyReqTryThreshold *reqPacket,DynamicClassifyBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


//==================================================================================

class	DClassifyInfoList : public NPList<DClassifyInfoList>
{
public:
	int			ID;

	DClassifyInfoList(void){}
	DClassifyInfoList(DClassifyInfoList &src)
		:ID(src.ID){}
	DClassifyInfoList(int id)
		:ID(id){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	DClassifyInfoList	&operator=(DClassifyInfoList &src);
};

class	DClassifyInfos : public NPListPack<DClassifyInfoList>
{
public:
	DClassifyInfos(void){}
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
	DClassifyInfos	&operator=(DClassifyInfos &src);
};

inline	DClassifyInfoList	&DClassifyInfoList::operator=(DClassifyInfoList &src)
{
	ID			=src.ID;
	return *this;
}

inline	bool	DClassifyInfoList::Load(QIODevice *f)
{
	if(::Load(f,ID)==false)
		return false;
	return true;
}
inline	bool	DClassifyInfoList::Save(QIODevice *f)
{
	if(::Save(f,ID)==false)
		return false;
	return true;
}
inline	bool	DClassifyInfos::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false)
		return false;
	RemoveAll();
	for(int i=0;i<N;i++){
		DClassifyInfoList *a=new DClassifyInfoList();
		if(a->Load(f)==false)
			return false;
		AppendList(a);
	}
	return true;
}
inline	bool	DClassifyInfos::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false)
		return false;
	for(DClassifyInfoList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false)
			return false;
	}
	return true;
}

inline	DClassifyInfos	&DClassifyInfos::operator=(DClassifyInfos &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}
//==================================================================================

class	CmdDynamicClassifyDeleteItemPacket : public GUIDirectMessage
{
public:

	CmdDynamicClassifyDeleteItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDynamicClassifyDeleteItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdGetDynamicClassifyLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetDynamicClassifyLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDynamicClassifyLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetDynamicClassifyLibraryNamePacket : public GUIDirectMessage
{
public:
//	AlgorithmLibraryListContainer	AList;
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetDynamicClassifyLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDynamicClassifyLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempDynamicClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempDynamicClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempDynamicClassifyLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearDynamicClassifyLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearDynamicClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearDynamicClassifyLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertDynamicClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertDynamicClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertDynamicClassifyLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateDynamicClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateDynamicClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateDynamicClassifyLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadDynamicClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadDynamicClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDynamicClassifyLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteDynamicClassifyLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteDynamicClassifyLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteDynamicClassifyLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestDynamicClassifyPacket : public GUIDirectMessage
{
public:
	//DynamicClassifyLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;

	CmdPickupTestDynamicClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestDynamicClassifyPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateDynamicClassifyPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateDynamicClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateDynamicClassifyPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempDynamicClassifyItemPacket : public GUIDirectMessage
{
public:
	DynamicClassifyItem	*Point;
	CmdCreateTempDynamicClassifyItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempDynamicClassifyItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromDynamicClassifyItemPacket : public GUIDirectMessage
{
public:
	DynamicClassifyItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromDynamicClassifyItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromDynamicClassifyItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteDynamicClassifyItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteDynamicClassifyItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteDynamicClassifyItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadDynamicClassifyItemPacketFromByteArray : public GUIDirectMessage
{
public:
	DynamicClassifyItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadDynamicClassifyItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadDynamicClassifyItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedDynamicClassifyFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedDynamicClassifyFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedDynamicClassifyFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestDynamicClassifyPacket: public GUIDirectMessage
{
public:
	CmdClearTestDynamicClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestDynamicClassifyPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetDynamicClassifyPacket : public GUIDirectMessage
{
public:
	DClassifyInfos	*Point;

	CmdGetDynamicClassifyPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDynamicClassifyPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateDynamicClassifyItem: public GUIDirectMessage
{
public:
	DynamicClassifyItem	*DynamicClassify;
	CmdCreateDynamicClassifyItem(LayersBase *base):GUIDirectMessage(base){	DynamicClassify=NULL;	}
	CmdCreateDynamicClassifyItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DynamicClassify=NULL;	}
};

class	CmdSetCopyAttr : public GUIDirectMessage
{
public:
	SelectAreaMode	Mode;

	CmdSetCopyAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdSetCopyAttr(GUICmdPacketBase *base):GUIDirectMessage(base){}
};

inline	SelectAreaMode::SelectAreaMode(void)
{
	CopyModeItem	=true;
	CopyModeCore	=false;
	CopyModeMaxZone	=false;
	CopyModeMinZone	=false;
	CopyModeBare	=false;
	CopyModeInside	=false;
	CopyModeOutlineI=false;
	CopyModeOutlineT=false;
	CopyModeOutlineO=false;
}

//=========================================================================
class	CmdReqDynamicClassifyEnumLibs: public GUIDirectMessage
//	StartupExecute=trueのライブラリのLibIDリストコンテナを外部から所得する
{
public:
	IntList	LibIDList;

	CmdReqDynamicClassifyEnumLibs(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDynamicClassifyEnumLibs(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
