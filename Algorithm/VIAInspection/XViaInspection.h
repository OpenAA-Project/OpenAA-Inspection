/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XViaInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XVIAINSPECTION_H)
#define	XVIAINSPECTION_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XStandardCommand.h"
#include "XGeneralFunc.h"

#define	VIAInspectionVersion	1
#define	Hist_VIAInspection_CenterBright	1
#define	Hist_VIAInspection_LightNGSize	4
#define	Hist_VIAInspection_DarkNGSize	5


class	VIALibrary;
class	VIABase;
class	VIAItem;
class	VIAInLayer;


class	VIADrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	enum	DrawType{
		 _LibTest		=1
		,_CreatedVIA	=2
	}Mode;

	QColor		ColorPickup;
	QColor		VIAColor0;
	QColor		VIAColor1;
	QColor		VIAColor2;
	QColor		VIAColor3;
	QColor		VIAColor4;
	QColor		VIAColor5;
	QColor		VIAColor6;
	QColor		VIAColor7;

	VIADrawAttr(void):ServiceForLayers(NULL){}
	VIADrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	VIADrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel
				, QColor &VIAColor0
				, QColor &VIAColor1
				, QColor &VIAColor2
				, QColor &VIAColor3
				, QColor &VIAColor4
				, QColor &VIAColor5
				, QColor &VIAColor6
				, QColor &VIAColor7);

	void	Initial(void);

	VIADrawAttr	&operator=(VIADrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	VIADrawAttr	&VIADrawAttr::operator=(VIADrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	Mode		=src.Mode;
	ColorPickup	=src.ColorPickup;
	VIAColor0	=src.VIAColor0;
	VIAColor1	=src.VIAColor1;
	VIAColor2	=src.VIAColor2;
	VIAColor3	=src.VIAColor3;
	VIAColor4	=src.VIAColor4;
	VIAColor5	=src.VIAColor5;
	VIAColor6	=src.VIAColor6;
	VIAColor7	=src.VIAColor7;
	return *this;
}
inline	bool	VIADrawAttr::Save(QIODevice *f)
{
	if(f->write((const char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Save(f,ColorPickup)==false)
		return false;
	return true;
}
inline	bool	VIADrawAttr::Load(QIODevice *f)
{
	if(f->read((char *)&Mode,sizeof(Mode))!=sizeof(Mode))
		return false;
	if(::Load(f,ColorPickup)==false)
		return false;
	return true;
}


class	VIAThreshold : public AlgorithmThreshold
{
public:
#pragma	pack(push,1)
	WORD	BrightWidthL;	//à√ë§ãPìxïù
	WORD	BrightWidthH;	//ñæë§ãPìxïù
	DWORD	OKDotL;			//à√ë§ÇnÇjÉhÉbÉgêî
	DWORD	OKDotH;			//ñæë§ÇnÇjÉhÉbÉgêî
	DWORD	MaxNGDotL;		//à√ë§ç≈ëÂÇmÇfÉhÉbÉgêî
	DWORD	MaxNGDotH;		//ñæë§ç≈ëÂÇmÇfÉhÉbÉgêî
	WORD	OKLengthL;		//ñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
	WORD	OKLengthH;		//ñæë§Ç≈ÅAÇ±ÇÃí∑Ç≥à»â∫ÇÃéûÇnÇj
	BYTE	ShrinkDot;
	BYTE	EnlargeDot;
	short	SpaceToOutline;
#pragma	pack(pop)

	VIAThreshold(VIAItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	void	RegistHist(void)	override;

};

class	VIAResultPosList : public ResultPosList
{
public:
	VIAResultPosList(void);
	VIAResultPosList(ResultPosList &src) : ResultPosList(src){}
	VIAResultPosList(int px ,int py) : ResultPosList(px,py){}
	VIAResultPosList(int px ,int py ,int rx ,int ry):ResultPosList(px ,py ,rx ,ry){}

	virtual	void	DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData 
								,int MovX ,int MovY ,double ZoomRate 
								,int MinimumRadius,QRgb Col
								,int CircleWidth,bool DrawBlueNGMark)	override;
};


class   VIAItem : public AlgorithmItemPLI
{
public:

	WORD	CenterBright;
	WORD	CenterTargetBright;

	AlignmentPacket2D	*AVector;

  public:

	VIAItem(void);
	VIAItem(FlexArea &area);
    virtual	~VIAItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new VIAItem();	}
	const	VIAThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const VIAThreshold *)GetThresholdBaseReadable(base);	}
	VIAThreshold			*GetThresholdW(LayersBase *base=NULL){	return (VIAThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new VIAThreshold(this);	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
    VIAItem &operator=(VIAItem &src);
	void	CopyThreshold(VIAItem &src);
	void	CopyThresholdOnly(VIAItem &src);
	void	CopyArea(VIAItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;	
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

  private:
	void	InitialConstructor(void);
	bool    ExecuteProcessingInner(int ThreadNo,ResultInItemRoot *Res
						  ,int mx ,int my
						  ,int BrightWidthL ,int BrightWidthH
						  ,int OKDotL ,int OKDotH
						  ,int MaxNGDotL ,int MaxNGDotH
						  ,WORD	OKLengthL ,WORD	OKLengthH
						  ,WORD	MinNGCountL,WORD MinNGCountH,BYTE ConnectLen
						  ,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);


public:
	WORD	CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my);
	void	EnAverage(int mx,int my
						,int &TmpBrightWidthL,int &TmpBrightWidthH);

	bool	CheckOnNG(int mx,int my
				, int BrightWidthL ,int BrightWidthH
				, int OKDotL ,int OKDotH
				,int MaxNGDotL ,int MaxNGDotH
				,int &SumL,int &SumH
				,ResultPosListContainer &PosList
				,WORD	OKLengthL
				,WORD	OKLengthH
				,WORD	ShrinkDot,WORD EnlargeDot
				,short &Error);
	void	CheckOnNGInner1(int dx ,int dy
                                    ,int LLevel ,int HLevel
                                    ,BYTE *pMapL ,BYTE *pMapH
                                    ,int Lx ,int Ly ,int LByte,int starty
									,int &LSum,int &HSum);

};


class   VIAInLayer : public AlgorithmInLayerPLI
{
	friend class	VIAItem;

	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;


  public:
	VIAInLayer(AlgorithmInPageRoot *parent);
	~VIAInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			VIAItem	*a=new VIAItem();
			a->SetParent(this);
			return a;
		}

	bool	UseLibraryForMaskingInOtherPage(int LibID);

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateItems(QIODevice *f);
	void	UndoSetIndependentItemDataCommand(QIODevice *f);

	void	PickupTest(VIALibrary &LibData);
	void	GenerateVIAs(VIALibrary *LibDim[],int LibDimNumb);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	void	CreatePickupBmpBuff(void);
};

class   VIAInPage : public AlgorithmInPagePLI
{
public:
	VIAInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}
	
	virtual	VIAInLayer	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new VIAInLayer(parent));	}
	void	PickupTest(IntList &LayerList ,VIALibrary &LibData);
	void	GenerateVIAs(IntList &LayerList, VIALibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	VIABase	: public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		ColorVIANormal	;
	QColor		ColorVIASelected	;
	QColor		ColorVIAActive	;

	QColor		VIAColor0;
	QColor		VIAColor1;
	QColor		VIAColor2;
	QColor		VIAColor3;
	QColor		VIAColor4;
	QColor		VIAColor5;
	QColor		VIAColor6;
	QColor		VIAColor7;
	int			OmitZoneDot;
	double		VarLow;

	VIABase(LayersBase *Base);
	virtual	VIAInPage	*NewChild(AlgorithmBase *parent)	override{	return(new VIAInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QString	GetDataText(void)	override{	return QString("VIAInspection");			}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigVIAInspection.dat");	}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};

//==================================================================================
class	VIAHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		VIAItemID;
	bool	Mastered;
	int32	Dx,Dy;

	VIAHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	VIAHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		VIAItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMaster[256];
	int		ListTarget[256];
	WORD	CenterBright;
	WORD	CenterTargetBright;

	VIAHistogramListSend(void);

	void	ConstructList(VIAHistogramListReq *reqPacket,VIABase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	VIAThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		VIAItemID;
	bool	Mastered;
	int32	Dx,Dy;

	VIAThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	VIAThresholdSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		VIAItemID;
	bool	Mastered;
	int32	Dx,Dy;
	WORD	CenterBright;
	WORD	CenterTargetBright;

	short	AbsBrightWidthL;	//à√ë§ãPìxïù
	short	AbsBrightWidthH;	//ñæë§ãPìxïù

	BYTE	ShrinkDot;
	BYTE	EnlargeDot;

	VIAThresholdSend(void);

	void	ConstructList(VIAThresholdReq *reqPacket,VIABase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	VIAReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		VIAItemID;	
	VIAItem	Threshold;

	VIAReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	VIASendTryThreshold : public AddedDataClass
{
public:
	int		NGDotInDark;
	int		NGDotInBright;
	int		Error;
	ResultInItemRoot	*Result;

	VIASendTryThreshold(void);
	~VIASendTryThreshold(void);

	void	ConstructList(VIAReqTryThreshold *reqPacket,VIABase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	VIAChangeShift
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		VIAItemID;
	int32	Dx,Dy;

	VIAChangeShift(void){}

	void	Reflect(VIABase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	VIAHistogramListReqCommand				3
#define	VIAHistogramListSendCommand				4
#define	VIAReqThresholdReqCommand				5
#define	VIAReqThresholdSendCommand				6
#define	VIAReqTryThresholdCommand				7
#define	VIASendTryThresholdCommand				8
#define	VIAReqChangeShiftCommand				9

//===================================================================================
class	VIAInfoList : public NPList<VIAInfoList>
{
public:
	int		LibID;
	IntList	VIACount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	VIAInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(VIACount.Save(f)==false)
		return false;
	return true;
}
inline	bool	VIAInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(VIACount.Load(f)==false)
		return false;
	return true;
}

//===================================================================================
class	CmdGetVIALibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetVIALibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetVIALibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetVIALibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetVIALibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetVIALibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempVIALibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempVIALibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempVIALibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearVIALibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearVIALibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearVIALibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertVIALibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertVIALibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertVIALibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateVIALibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateVIALibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateVIALibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadVIALibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadVIALibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadVIALibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteVIALibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteVIALibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteVIALibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestVIAPacket : public GUIDirectMessage
{
public:
	//VIALibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	IntList			LayerList;
	int				Page;

	CmdPickupTestVIAPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestVIAPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateVIAPacket : public GUIDirectMessage
{
public:
	IntList		LibList;
	IntList		LayerList;
	int			Page;
	CmdGenerateVIAPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateVIAPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempVIAItemPacket : public GUIDirectMessage
{
public:
	VIAItem	*Point;
	CmdCreateTempVIAItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempVIAItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromVIAItemPacket : public GUIDirectMessage
{
public:
	VIAItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromVIAItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromVIAItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteVIAItemPacket : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteVIAItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteVIAItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadVIAItemPacketFromByteArray : public GUIDirectMessage
{
public:
	VIAItem	*BItemPoint;
	QByteArray	Buff;
	CmdLoadVIAItemPacketFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadVIAItemPacketFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdModifySelectedVIAFromByteArray : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	IntList		LayerList;
	int			LocalPage;
	CmdModifySelectedVIAFromByteArray(LayersBase *base):GUIDirectMessage(base){}
	CmdModifySelectedVIAFromByteArray(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetOneSelectedItem : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	bool		ExistSelected;
	CmdGetOneSelectedItem(LayersBase *base):GUIDirectMessage(base){}
	CmdGetOneSelectedItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestVIAPacket: public GUIDirectMessage
{
public:
	CmdClearTestVIAPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestVIAPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



class	CmdVIAInfoListPacket: public GUIDirectMessage
{
public:
	int		LocalPage;
	NPListPack<VIAInfoList>	*VIAInfos;
	CmdVIAInfoListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdVIAInfoListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetVIAFromList: public GUIDirectMessage
{
public:
	ListLayerAndID	CurrentItem;
	int				LocalPage;
	VIAItem	*VIAInfoOnMouse;

	CmdGetVIAFromList(LayersBase *base):GUIDirectMessage(base){}
	CmdGetVIAFromList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateVIAItem: public GUIDirectMessage
{
public:
	VIAItem	*VIA;
	CmdCreateVIAItem(LayersBase *base):GUIDirectMessage(base){	VIA=NULL;	}
	CmdCreateVIAItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	VIA=NULL;	}
};


#endif