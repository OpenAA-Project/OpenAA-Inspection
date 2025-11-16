/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureHole\XMeasureHole.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XMeasureHole_H
#define XMeasureHole_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"


#define	MeasureHoleVersion	1
#define	DefLibTypeMeasureHole		17

class	MeasureHoleItem;

class	MeasureHoleLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	ColorLogic	CupperColor;
	int			MinDiameter;	//micron size
	int			MaxDiameter;	//micron size
	int			NoiseSize;
	int			SearchDot;

public:
	MeasureHoleLibrary(int LibType,LayersBase *Base);
	virtual	~MeasureHoleLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MeasureHoleLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	MeasureHoleLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MeasureHoleLibraryContainer(LayersBase *base);
	virtual	~MeasureHoleLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeMeasureHole;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MeasureHole Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MeasureHoleLibrary(GetLibType(),GetLayersBase());	}
};

class	EllipseXYList : public NPList<EllipseXYList>
{
public:
	double	Cx,Cy;
	double	RadiusX,RadiusY;

	EllipseXYList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#define	ResultMeasureHoleOnItemType	101

class	ResultMeasureHoleOnItem : public AddedDataClass
{
public:
	NPListPack<EllipseXYList>		List;
	PureFlexAreaListContainer	FPack;

	ResultMeasureHoleOnItem(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Clear(void){	List.RemoveAll();	FPack.RemoveAll();	}
};

class	MeasureHoleThreshold : public AlgorithmThreshold
{
public:
	ColorLogic	CupperColor;
	int			MinDiameter;	//micron size
	int			MaxDiameter;	//micron size
	int			NoiseSize;
	int			SearchDot;

	MeasureHoleThreshold(MeasureHoleItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MeasureHoleItem : public AlgorithmItemPI
{
public:
	EllipseXYList	Result;

	MeasureHoleItem(){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureHoleItem();	}
	const	MeasureHoleThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const MeasureHoleThreshold *)GetThresholdBaseReadable(base);	}
	MeasureHoleThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (MeasureHoleThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new MeasureHoleThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;


	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res)	override;
private:
	double	GetDivSum(double Cx,double Cy,double Rx,double Ry
					,ImageBuffer *ImageList[]);

};


class   MeasureHoleInPage : public AlgorithmInPagePI
{
public:
	BYTE	**MaskingMap;
	int		XByte;

	MeasureHoleInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			MeasureHoleItem	*a=new MeasureHoleItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)	override;
	void	GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen);
	void	SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen); 
};

class	MeasureHoleBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	double	Offset;
	double	Gain;

	MeasureHoleBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MeasureHoleInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MeasureHole");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMeasureHole.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	AvailableShrinkItem(void)		const	override	{	return false;	}
	virtual	bool	AvailableChangeLibrary(void)	const	override	{	return false;	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
//===================================================================================

class	AddMeasureHoleAreaPacket : public GUIDirectMessage
{
public:
	ColorLogic	CupperColor;
	FlexArea	MaskArea;

	AddMeasureHoleAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMeasureHoleAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MeasureHoleDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;

	MeasureHoleDrawAttr(void){}
	MeasureHoleDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	MeasureHoleDrawAttr( 
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

class	CmdMeasureHoleDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdMeasureHoleDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdCreateTempMeasureHoleItemPacket :public GUIDirectMessage
{
public:
	MeasureHoleItem	*Point;

	CmdCreateTempMeasureHoleItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMeasureHoleItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempMeasureHoleLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempMeasureHoleLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMeasureHoleLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMeasureHoleLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetMeasureHoleLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMeasureHoleLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadMeasureHoleLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadMeasureHoleLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadMeasureHoleLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateByteArrayFromMeasureHoleItemPacket : public GUIDirectMessage
{
public:
	MeasureHoleItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromMeasureHoleItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromMeasureHoleItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddByteMeasureHoleItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	CmdAddByteMeasureHoleItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteMeasureHoleItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertMeasureHoleLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertMeasureHoleLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertMeasureHoleLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateMeasureHoleLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateMeasureHoleLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateMeasureHoleLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif