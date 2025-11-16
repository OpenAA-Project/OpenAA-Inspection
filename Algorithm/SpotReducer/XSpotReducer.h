/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\SpotReducer\XSpotReducer.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#if	!defined(XSPOTREDUCER_H)
#define XSPOTREDUCER_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"

#define	SpotReducerVersion	1

class	SpotReducerItem;

class	SpotReducerThreshold : public AlgorithmThreshold
{
public:
	int		SpotBrightness;
	double	ReductionLevel;
	int		SpotArea;
	int		SpotCount;

	SpotReducerThreshold(SpotReducerItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	SpotReducerItem : public AlgorithmItemPLI
{
public:
	SpotReducerItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new SpotReducerItem();	}
	const	SpotReducerThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const SpotReducerThreshold *)GetThresholdBaseReadable(base);	}
	SpotReducerThreshold			*GetThresholdW(LayersBase *base=NULL){	return (SpotReducerThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new SpotReducerThreshold(this);	}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecutePreProcessing(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
private:
	void	ReduceSpot(int x, int y
					,double Avr);
};

class   SpotReducerInLayer : public AlgorithmInLayerPLI
{
public:
	BYTE	**SpotMap;
	BYTE	**SpotMap2;
	int		AllocatedXByte;
	int		AllocatedYLen;

	SpotReducerInLayer(AlgorithmInPageRoot *parent);
	~SpotReducerInLayer(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override
		{	
			SpotReducerItem	*a=new SpotReducerItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)	override;
};

class   SpotReducerInPage : public AlgorithmInPagePLI
{
public:
	SpotReducerInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new SpotReducerInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	SpotReducerBase : public AlgorithmBase
{
public:
	int	TransparentLevel;

	SpotReducerBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new SpotReducerInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("SpotReducer");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigSpotReducer.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
//===================================================================================
class	AddSpotReducerAreaPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	int			SpotBrightness;
	double		ReductionLevel;
	int			SpotArea;
	int			SpotCount;

	AddSpotReducerAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddSpotReducerAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	SpotReducerDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;

	SpotReducerDrawAttr(void){}
	SpotReducerDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
};

class	CmdSpotReducerDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdSpotReducerDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	AddSpotReducerArea : public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList	LayerList;

	AddSpotReducerArea(LayersBase *base):GUIDirectMessage(base){}
	AddSpotReducerArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
