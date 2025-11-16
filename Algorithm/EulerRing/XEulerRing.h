/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\XEulerRing.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XEulerRing_H)
#define	XEulerRing_H

#include "XFlexArea.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XColorSpace.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
//#include "XPropertyEulerRingPacket.h"
#include "XStandardCommand.h"

#define	EulerRingVersion	1


class   AlignmentInLayer;
class	XAlignmentArea;
class	EulerRingLibrary;
class	EulerRingBase;
class	EulerRingItem;

class	ShowAndSetItemsEulerRing : public ShowAndSetItemsBaseClass
{
public:
	GUIFormBase	*Form;
};

class	EulerRingThreshold : public AlgorithmThreshold
{
public:
//検査データ
    WORD				ExpandedDot;
	ColorLogicWithTable	InspectionColor;
	int32				Mergin;
    WORD				AdjustBlack;    //輝度補正の下限幅
    WORD				AdjustWhite;    //輝度補正の上限幅

	EulerRingThreshold(EulerRingItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
    
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class	ResultClusterOnItem : public AddedDataClass
{
public:
	FlexArea	ResultArea;
	ResultClusterOnItem(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#define	ResultEulerRingOnItemType	7

class   EulerRingItem : public AlgorithmItemPI
{
public:
	AlignmentPacket2D	*AVector;
  public:

	EulerRingItem(void);
	EulerRingItem(FlexArea &area);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new EulerRingItem();	}
	const	EulerRingThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const EulerRingThreshold *)GetThresholdBaseReadable(base);	}
	EulerRingThreshold			*GetThresholdW(LayersBase *base=NULL){	return (EulerRingThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new EulerRingThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
    EulerRingItem &operator=(EulerRingItem &src);
	void	CopyThreshold(EulerRingItem &src);
	void	CopyThresholdOnly(EulerRingItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
										   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

private:
	void	InitialConstructor(void);

	bool    ExecuteProcessingInner(ResultInItemRoot *Res
						  ,int mx ,int my
						  ,ColorLogic &Brightness
						  ,int Mergin);

	void	CheckOnNGInner1(int dx ,int dy ,int turn
							,ColorLogic &Level
							,int Mergin
							,BYTE **pMap);
	QRgb	CalcCenterBright(ImageBuffer *ImageList[] ,int mx ,int my);

public:
	double	EnAverage(int mx,int my
						,ColorLogic &TmpBrightness);
};

class   EulerRingInPage : public AlgorithmInPagePI
{
	friend class	EulerRingItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

public:
	EulerRingInPage(AlgorithmBase *parent);
	~EulerRingInPage(void);
	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			EulerRingItem	*a=new EulerRingItem();	
			a->SetParent(this);
			return a;
		}

	void	PickupTest(EulerRingLibrary &LibData);
	void	GenerateBlocks(EulerRingLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

private:
	void	CreatePickupBmpBuff(void);
};

class	EulerRingBase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		EulerRingNormal	;
	QColor		EulerRingSelected	;
	QColor		EulerRingActive	;

	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;
	int			OmitZoneDot;

	EulerRingBase(LayersBase *Base);

	virtual	EulerRingInPage	*NewChild(AlgorithmBase *parent)	override{	return(new EulerRingInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)			override{	return QString("EulerRing");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigEulerRing.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
};

//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne		1
#define	SetIndependentItemDataCommand_All			2
#define	EulerRingHistogramListReqCommand			3
#define	EulerRingHistogramListSendCommand			4
#define	EulerRingReqThresholdReqCommand				5
#define	EulerRingReqThresholdSendCommand			6
#define	EulerRingReqTryThresholdCommand				7
#define	EulerRingSendTryThresholdCommand			8
#define	EulerRingReqChangeShiftCommand				9
//==================================================================================

class	EulerRingDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	enum	DrawMode{
		_None
		,_LibTest
		,_CreatedBlock
	};

	DrawMode	Mode;

	QColor		ColorPickup	;
	QColor		BlockColor0;
	QColor		BlockColor1;
	QColor		BlockColor2;
	QColor		BlockColor3;
	QColor		BlockColor4;
	QColor		BlockColor5;
	QColor		BlockColor6;
	QColor		BlockColor7;

	EulerRingDrawAttr(void):ServiceForLayers(NULL){}
	EulerRingDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	EulerRingDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &blockColor0
				, QColor &blockColor1
				, QColor &blockColor2
				, QColor &blockColor3
				, QColor &blockColor4
				, QColor &blockColor5
				, QColor &blockColor6
				, QColor &blockColor7);

	void	Initial(void);

	EulerRingDrawAttr	&operator=(EulerRingDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	EulerRingDrawAttr	&EulerRingDrawAttr::operator=(EulerRingDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	ColorPickup	=src.ColorPickup;
	BlockColor0	=src.BlockColor0;
	BlockColor1	=src.BlockColor1;
	BlockColor2	=src.BlockColor2;
	BlockColor3	=src.BlockColor3;
	BlockColor4	=src.BlockColor4;
	BlockColor5	=src.BlockColor5;
	BlockColor6	=src.BlockColor6;
	BlockColor7	=src.BlockColor7;
	return *this;
}
inline	bool	EulerRingDrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	EulerRingDrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}
//==========================================================================
class	EulerRingInfoList : public NPList<EulerRingInfoList>
{
public:
	int		LibID;
	IntList	EulerRingCount;

	int		GetLibID(void){		return LibID;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	EulerRingInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(EulerRingCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	EulerRingInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(EulerRingCount.Load(f)==false)
		return false;
	return true;
}


//==================================================================================
class	EulerRingChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		BlockItemID;
	int32	Dx,Dy;

	EulerRingChangeShift(void){}

	void	Reflect(EulerRingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingHistogramListReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	EulerRingHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingHistogramListSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	ColorLogic	MasterColor;
	ColorLogic	TargetColor;

	EulerRingHistogramListSend(void);

	void	ConstructList(EulerRingHistogramListReq *reqPacket,EulerRingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingThresholdReq
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;

	EulerRingThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingThresholdSend
{
public:
	int32	GlobalPage;
	int		BlockItemID;
	bool	Mastered;
	int32	Dx,Dy;
	QRgb	CenterBright;
	ColorLogic	InspectionColor;
	ColorLogic	AbsInspectionColor;
	double	Multiplier;

	EulerRingThresholdSend(void);

	void	ConstructList(EulerRingThresholdReq *reqPacket,EulerRingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	EulerRingReqTryThreshold
{
public:
	int32	GlobalPage;
	int		BlockItemID;	
	EulerRingItem	Threshold;

	EulerRingReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	EulerRingSendTryThreshold : public AddedDataClass
{
public:
	int		Result;
	int		ResultMoveDx;
	int		ResultMoveDy;

	EulerRingSendTryThreshold(void);

	void	ConstructList(EulerRingReqTryThreshold *reqPacket,EulerRingBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	CmdGetEulerRingLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetEulerRingLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEulerRingLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEulerRingLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetEulerRingLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEulerRingLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempEulerRingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempEulerRingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempEulerRingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearEulerRingLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearEulerRingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearEulerRingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertEulerRingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertEulerRingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertEulerRingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateEulerRingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateEulerRingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateEulerRingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadEulerRingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadEulerRingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadEulerRingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteEulerRingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteEulerRingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteEulerRingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestEulerRingPacket : public GUIDirectMessage
{
public:
	//EulerRingLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	int				Page;

	CmdPickupTestEulerRingPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestEulerRingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateEulerRingPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	int			Page;
	CmdGenerateEulerRingPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateEulerRingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempEulerRingItemPacket : public GUIDirectMessage
{
public:
	EulerRingItem	*Point;
	CmdCreateTempEulerRingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempEulerRingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromEulerRingItemPacket : public GUIDirectMessage
{
public:
	EulerRingItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromEulerRingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromEulerRingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteEulerRingItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteEulerRingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteEulerRingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadEulerRingItemPacketFromByteArray : public GUIDirectMessage
{
public:
	EulerRingItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadEulerRingItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadEulerRingItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedEulerRingFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	int			LocalPage;
	CmdModifySelectedEulerRingFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedEulerRingFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestEulerRingPacket: public GUIDirectMessage
{
public:
	CmdClearTestEulerRingPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestEulerRingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdEulerRingInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<EulerRingInfoList>	*EulerRingInfos;
	CmdEulerRingInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdEulerRingInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEulerRingFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	EulerRingItem	*EulerRingInfoOnMouse;

	CmdGetEulerRingFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEulerRingFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateEulerRingItem: public GUIDirectMessage
{
public:
	EulerRingItem	*EulerRing;
	CmdCreateEulerRingItem(LayersBase *base):GUIDirectMessage(base){	EulerRing=NULL;	}
	CmdCreateEulerRingItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif