/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VCutInspection\XVCutInspection.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XVCutInspection_h
#define XVCutInspection_h

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XDirectComm.h"
#include "XGeneralFunc.h"

#define	VCutInspectionVersion		1
#define	DefLibTypeVCutInspection	15
class	VCutInspectionItem;
class	VCutInspectionInLayer;


class	VCutInspectionDrawAttr : public AlgorithmDrawAttr
{
public:
	VCutInspectionDrawAttr(void){}
	VCutInspectionDrawAttr(QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel)
		: AlgorithmDrawAttr(  ncol , ntranparentLevel
							, scol , stranparentLevel
							, acol , atranparentLevel){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


inline	bool	VCutInspectionDrawAttr::Save(QIODevice *f)
{	
	return true;
}
inline	bool	VCutInspectionDrawAttr::Load(QIODevice *f)
{	
	return true;
}

//======================================================================

class	VCutInspectionLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;
	bool	GenDynamicMask;
	int		ExpandGenMask;
public:

	VCutInspectionLibrary(int LibType,LayersBase *Base);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	VCutInspectionLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	VCutInspectionLibraryContainer : public AlgorithmLibraryContainer
{
public:
	VCutInspectionLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeVCutInspection;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "VCutInspection Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new VCutInspectionLibrary(GetLibType(),GetLayersBase());	}
};
//======================================================================

class	VCutInspectionThreshold : public AlgorithmThreshold
{
public:
	int		ThresholdShift	;
	double	ThresholdLevel	;
	int		ThresholdLength	;
	bool	GenDynamicMask	;
	int		ExpandGenMask	;

	VCutInspectionThreshold(AlgorithmItemPI *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	virtual	bool	Save(QIODevice *f)					override;
	virtual	bool	Load(QIODevice *f)					override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	VCutBand
{
	VCutInspectionItem	*Parent;

	int		Px,Py;
	double	Ux,Uy;	//Vカットを垂直に横切る方向の単位ベクトル
	double	Vx,Vy;	//Vカット方向の単位ベクトル
	int		WLen;		//Vカットを垂直に横切る方向のバンドの長さ
	int		StackedLen;	//Vカット方向の長さ

	double	*BList;

	MapBuffer	ResultBitImage;		//結果エリア
	int			ResImageX1,ResImageY1,ResImageX2,ResImageY2;
	int			MidAvr;
public:
	int		ResultU1,ResultU2;
	double	ResultDifference;		//判定結果の値
	AlignmentPacket2D	*AVector;	//アラインメント
	int		ResMx,ResMy;			//検査した結果、移動量
	FlexArea	Area;
	FlexArea	MaskArea;

	VCutBand(void);
	~VCutBand(void);

	void	SetP(double px,double py)			{	Px=px;	Py=py;	}
	void	SetV(double vx,double vy ,int hlen)	{	Vx=vx;	Vy=vy;	StackedLen=hlen;	}
	void	SetU(double ux,double uy ,int wlen)	{	Ux=ux;	Uy=uy;	WLen=wlen;	}

	void	SetParent(VCutInspectionItem *parent);
	void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	ResultPosList	*ExecuteProcessing(int mx,int my);
	bool	CalcFromBList(void);

	void	GetCenter(int &cx,int &cy);
	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	void	Draw(QPainter &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	void	MakeResultVCutMap(MapBuffer &BitMap);
	void	MakeDynamicMask(int mx ,int my);
	void	MakeFlexArea(void);
	int		GetDotPerLine(void);
	int		GetMaxLines(void);
private:
	void	MakeBList(ImageBuffer *ImageList[] ,int mx ,int my);
};


class	VCutInspectionItem : public AlgorithmItemPI
{
	VCutBand	*InspectedBands;
	int			BandNumb;
	int			MasterX,MasterY;
	AlignmentPacket2D	*AVector;	//アラインメント
public:
	FlexArea	BandZone;	//ExecuteIntialAfterEditで自動生成

	VCutInspectionItem(void);
	~VCutInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new VCutInspectionItem();	}
	virtual	FlexArea	&GetArea(void)	override					{	return AlgorithmItemRoot::GetArea();	}
	virtual	FlexArea	&GetArea(int UniqueAreaType_Code)	override{	return BandZone;	}

	const	VCutInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const VCutInspectionThreshold *)GetThresholdBaseReadable(base);	}
	VCutInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (VCutInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new VCutInspectionThreshold(this);	}

	virtual	int32		GetItemClassType(void)	override	{		return 0;		}
	virtual	VectorLineBase	*CreateVectorBase(void)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	CopyArea(VCutInspectionItem &src);
	void	MakeResultVCutMap(MapBuffer &BitMap);
	void	MakebandZone(void);
	void	CopyThresholdOnly(VCutInspectionItem *src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
private:
};

class   VCutInspectionInPage : public AlgorithmInPagePI
{
	MapBuffer	VCutMapBuffer;

public:
	BYTE	**IndexDynamicMaskMap;		//Global dynamic masking buffer. Needless to delete in this class
	int		IndexDynamicMaskMapXByte;
	int		IndexDynamicMaskMapYLen;

	VCutInspectionInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override
		{	
			VCutInspectionItem	*a=new VCutInspectionItem();	
			a->SetParent(this);
			return a;
		}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	MakeResultVCutMap(MapBuffer &BitMap);
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	UndoSetIndependentItemDataCommand(QIODevice *f);
};

class	VCutInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorVCut;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorVCut;
	QColor	NegColorSelected;
	int		ExpandPixelForResult;

	VCutInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new VCutInspectionInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("VCutInspection");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigVCutInspection.dat");		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//===================================================================================
#define	Hist_AlighmentLargeShiftX	1
#define	Hist_AlighmentLargeShiftY	2
#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12

#define	VCutReqThresholdReqCommand				5
#define	VCutReqThresholdSendCommand				6
#define	VCutReqTryThresholdCommand				7
#define	VCutSendTryThresholdCommand				8
//===================================================================================


class	CmdCreateTempVCutInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempVCutInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempVCutInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetVCutInspectionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetVCutInspectionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetVCutInspectionLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AddVCutInspectionAreaPacket: public GUIDirectMessage
{
public:
	VectorLineBase	*Vector;
	int		CurrentPhase;
	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;
	int		LibID;

	AddVCutInspectionAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddVCutInspectionAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadVCutInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadVCutInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadVCutInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearVCutInspectionLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearVCutInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearVCutInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteVCutInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteVCutInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteVCutInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertVCutInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertVCutInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertVCutInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateVCutInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateVCutInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateVCutInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	VCutThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	VCutThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	VCutThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;
	WORD	CenterBright;
	WORD	CenterTargetBright;


	VCutThresholdSend(void);

	void	ConstructList(VCutThresholdReq *reqPacket,VCutInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};



class	VCutReqTryThreshold
{
public:
	int32	GlobalPage;
	int		ItemID;	
	VCutInspectionItem	Threshold;

	VCutReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	VCutSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	int		NGDot;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		ResultMinDifference;
	int		Error;

	VCutSendTryThreshold(void);
	~VCutSendTryThreshold(void);

	void	ConstructList(VCutReqTryThreshold *reqPacket,VCutInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
#endif
