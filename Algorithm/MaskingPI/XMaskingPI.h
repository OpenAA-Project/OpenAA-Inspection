/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMaskingPI.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XMaskingPI_H
#define XMaskingPI_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"

class	MaskingPIItem;

class	MaskingPIThreshold : public AlgorithmThreshold
{
public:
    bool							Effective;		// true=有効エリア
    AlgorithmLibraryListContainer	SelAreaID;		// 限定マスク

	MaskingPIThreshold(MaskingPIItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MaskingPIItem : public AlgorithmItemPI
{
public:

	MaskingPIItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MaskingPIItem();	}
	const	MaskingPIThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MaskingPIThreshold *)GetThresholdBaseReadable(base);	}
	MaskingPIThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MaskingPIThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new MaskingPIThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool		IsEffective(void)	const override;
	virtual	void		SetEffective(bool effective)	override;
	virtual	void		Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
};


class   MaskingPIInPage : public AlgorithmInPagePI
{
public:
	MaskingPIInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override{	return new MaskingPIItem();	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	GenerateMaskInSameColor(int PickupL ,int PickupH ,bool Effective);
	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)	override;
	void	GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen);
	void	SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen); 

	void	GenerateMaskForDesktop(  ColorLogic &PickupSideBarColor 
									,ColorLogic &BaseColor	
									,int PickupSideBarColorMergin=10
									,int BaseColorMergin=2
									,int NoiseSize=10);
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,void *Anything=NULL)	override;

};

class	MaskingPIBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	MaskingPIBase(LayersBase *Base);

	virtual	bool	HasReflection(ReflectionMode mode)	override	{	return (mode==_Reflection_Mask)?true:false;	}
	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MaskingPIInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MaskingPI");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMaskingPI.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
//===================================================================================
class	AddMaskingPIAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	bool		Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	AddMaskingPIAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMaskingPIAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MaskingPIDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	bool	EffectiveMode;
	bool	IneffectiveMode;

	MaskingPIDrawAttr(void){}
	MaskingPIDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	MaskingPIDrawAttr( QColor ncol ,int ntranparentLevel
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

class	CmdMaskingPIDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdMaskingPIDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdMaskingPIDeleteItemPacket : public GUIDirectMessage
{
public:

	CmdMaskingPIDeleteItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdMaskingPIDeleteItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateMaskPIInSameColor : public GUIDirectMessage
{
public:
	int32	RPickupL;
	int32	RPickupH;
	int32	GPickupL;
	int32	GPickupH;
	int32	BPickupL;
	int32	BPickupH;
	bool	Effective;

	CmdGenerateMaskPIInSameColor(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateMaskPIInSameColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMaskingPIDrawOnOffPacket : public GUIDirectMessage
{
public:
	bool	Effective;
	bool	Ineffective;

	CmdMaskingPIDrawOnOffPacket(LayersBase *base):GUIDirectMessage(base)
			{	Effective=false;	Ineffective=false;	}
	CmdMaskingPIDrawOnOffPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)
			{	Effective=false;	Ineffective=false;	}
};

class	CmdRemoveMaskPIItem : public GUIDirectMessage
{
public:
	int	ItemID;

	CmdRemoveMaskPIItem(LayersBase *base):GUIDirectMessage(base){}
	CmdRemoveMaskPIItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};



#endif