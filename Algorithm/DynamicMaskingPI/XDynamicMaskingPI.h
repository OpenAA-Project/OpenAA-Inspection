/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DynamicMaskingPI\XDynamicMaskingPI.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XDynamicMaskingPI_H
#define XDynamicMaskingPI_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XIntClass.h"

class	DynamicMaskingPIItem;
#define	DefLibTypeDynamicMaskingPI			16

class	DynamicMaskingPILibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	ColorLogic	MaskingColor;
	int32		EnsmallDot;
	int32		EnlargeDot;

public:
	DynamicMaskingPILibrary(int LibType,LayersBase *Base);
	virtual	~DynamicMaskingPILibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	DynamicMaskingPILibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	DynamicMaskingPILibraryContainer : public AlgorithmLibraryContainer
{
public:
	DynamicMaskingPILibraryContainer(LayersBase *base);
	virtual	~DynamicMaskingPILibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeDynamicMaskingPI;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "Dynamic MaskingPI Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new DynamicMaskingPILibrary(GetLibType(),GetLayersBase());	}
};


class	DynamicMaskingPIThreshold : public AlgorithmThreshold
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	enum	OperationType{
		_PickupMask			=1
		,_DrawMask			=2
		,_DynamicDrawMask	=3
		,_MakeDynamicMask	=4
	}OpeType;
	BYTE		DrawColR;
	BYTE		DrawColG;
	BYTE		DrawColB;

	int32		AbsLR2, AbsHR2;
	int32		AbsLG2, AbsHG2;
	int32		AbsLB2, AbsHB2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	BYTE		DrawColG2;
	BYTE		DrawColB2;
	int32		Mergin;
	ColorLogic	MaskingColor;
	int32		Layer;
	IntList		AdaptedPickupLayers;

	DynamicMaskingPIThreshold(DynamicMaskingPIItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};

class	DynamicMaskingPIItem : public AlgorithmItemPI
{
public:
	AlignmentPacket2D			*AVector;		//For PreProcessing
	PureFlexAreaListContainer	MaskingArea;
	double	Cx,Cy;
	BYTE	**MaskingMap;
	BYTE	**TmpBuff;
	int		XByte;
	int		YLen;

	DynamicMaskingPIItem(void);
	virtual	~DynamicMaskingPIItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DynamicMaskingPIItem();	}
	const	DynamicMaskingPIThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const DynamicMaskingPIThreshold *)GetThresholdBaseReadable(base);	}
	DynamicMaskingPIThreshold			*GetThresholdW(LayersBase *base=NULL){	return (DynamicMaskingPIThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new DynamicMaskingPIThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

private:
	void	MakePickupMask(int mx,int my,BYTE	**MaskingMap,int XByte ,int YLen ,bool Master);
};


class   DynamicMaskingPIInPage : public AlgorithmInPagePI
{
public:

	DynamicMaskingPIInPage(AlgorithmBase *parent);
	~DynamicMaskingPIInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			DynamicMaskingPIItem	*a=new DynamicMaskingPIItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)	override;
	void	GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen);
	void	SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen); 

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res ,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	bool	DrawResultItem(ResultInPageRoot *Res,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
};

class	DynamicMaskingPIBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	OnlyMakeMask;
	bool	ModePreAlignment;

	DynamicMaskingPIBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new DynamicMaskingPIInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("DynamicMaskingPI");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigDynamicMaskingPI.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
//===================================================================================
class	AddDynamicMaskingPIAreaPacket : public GUIDirectMessage
{
public:
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	FlexArea	MaskArea;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	BYTE		DrawColG;
	BYTE		DrawColB;

	int32		AbsLR2, AbsHR2;
	int32		AbsLG2, AbsHG2;
	int32		AbsLB2, AbsHB2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	BYTE		DrawColG2;
	BYTE		DrawColB2;
	int32		Mergin;
	ColorLogic	MaskingColor;
	int32		Layer;
	int32		ParentItemID;
	IntList		AdaptedPickupLayers;

	AddDynamicMaskingPIAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddDynamicMaskingPIAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	ModDynamicMaskingPIAreaPacket : public GUIDirectMessage
{
public:
	int32		ID;
	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	BYTE		DrawColG;
	BYTE		DrawColB;

	int32		AbsLR2, AbsHR2;
	int32		AbsLG2, AbsHG2;
	int32		AbsLB2, AbsHB2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	BYTE		DrawColG2;
	BYTE		DrawColB2;
	int32		Mergin;
	ColorLogic	MaskingColor;
	int32		Layer;
	IntList		AdaptedPickupLayers;

	ModDynamicMaskingPIAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	ModDynamicMaskingPIAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DynamicMaskingPIDrawAttr : public AlgorithmDrawAttr
{
public:
	enum	_MaskMode{
			_PickupMode
			,_MakingMode
	}MaskMode;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	ListPageID		SelectedMask;

	DynamicMaskingPIDrawAttr(void){}
	DynamicMaskingPIDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	DynamicMaskingPIDrawAttr( 
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

class	CmdDynamicMaskingPIDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdDynamicMaskingPIDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdDynamicMaskingPIDeleteItemPacket : public GUIDirectMessage
{
public:

	CmdDynamicMaskingPIDeleteItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDynamicMaskingPIDeleteItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DynamicMaskingPIInfoList : public NPList<DynamicMaskingPIInfoList>
{
public:
	int			ID;
	int			GlobalPage;

	int32		AbsLR, AbsHR;
	int32		AbsLG, AbsHG;
	int32		AbsLB, AbsHB;
	int32		EnsmallDot;
	int32		EnlargeDot;
	int32		BlockWidth;
	int32		BlockHeight;
	int32		MinSize;
	int32		Cx,Cy;
	int32		x1,y1,x2,y2;
	int32		Page;
	DynamicMaskingPIThreshold::OperationType	OpeType;
	BYTE		DrawColR;
	BYTE		DrawColG;
	BYTE		DrawColB;

	int32		AbsLR2, AbsHR2;
	int32		AbsLG2, AbsHG2;
	int32		AbsLB2, AbsHB2;
	int32		EnsmallDot2;
	int32		EnlargeDot2;
	BYTE		DrawColR2;
	BYTE		DrawColG2;
	BYTE		DrawColB2;
	int32		Mergin;
	ColorLogic	MaskingColor;
	int32		Layer;
	IntList		AdaptedPickupLayers;

	DynamicMaskingPIInfoList(void){}

	bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

class	DynamicMaskingPIInfoListContainer : public NPListPack<DynamicMaskingPIInfoList>
{
public:
	bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

	DynamicMaskingPIInfoListContainer	&operator+=(DynamicMaskingPIInfoListContainer &src);
};

class	CmdReqDMaskingPIAreaInfoList : public GUIDirectMessage
{
public:
	DynamicMaskingPIInfoListContainer	*List;

	CmdReqDMaskingPIAreaInfoList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDMaskingPIAreaInfoList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqDMaskingPIMode : public GUIDirectMessage
{
public:
	DynamicMaskingPIDrawAttr::_MaskMode	Mode;
	ListPageID							SelectedItem;

	CmdReqDMaskingPIMode(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDMaskingPIMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif