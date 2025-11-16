/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ZAxisRegulation\XZAxisRegulation.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XZAxisRegulation_h
#define XZAxisRegulation_h

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XDirectComm.h"
#include "XGeneralFunc.h"

#define	ZAxisRegulationVersion	2

class	ZAxisRegulationItem;
class	ZAxisRegulationInLayer;


class	ZAxisRegulationDrawAttr : public AlgorithmDrawAttr
{
public:
	ZAxisRegulationDrawAttr(void){}
	ZAxisRegulationDrawAttr(QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel)
		: AlgorithmDrawAttr(  ncol , ntranparentLevel
							, scol , stranparentLevel
							, acol , atranparentLevel){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


inline	bool	ZAxisRegulationDrawAttr::Save(QIODevice *f)
{	
	return true;
}
inline	bool	ZAxisRegulationDrawAttr::Load(QIODevice *f)
{	
	return true;
}

//======================================================================

class	ZAxisRegulationThreshold : public AlgorithmThreshold
{
public:

	ZAxisRegulationThreshold(AlgorithmItemPLI *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
	virtual	bool	Load(QIODevice *f)					override{	return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};


class	ZAxisRegulationYDirItem : public AlgorithmItemPLI
{
public:
	double		*ResultTable;
	int32		ResultLen;
	int			AxisID;
	int			ResultPeakY;
	AlignmentPacket2D	*AVector;

	int			CenterInMaster;
	int			OKZone;
	int			ResultCenter;
	bool		ResultOK;
	int			ResultMx;
	int			ResultMy;

	ZAxisRegulationYDirItem(void);
	~ZAxisRegulationYDirItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ZAxisRegulationYDirItem();	}
	const	ZAxisRegulationThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ZAxisRegulationThreshold *)GetThresholdBaseReadable(base);	}
	ZAxisRegulationThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ZAxisRegulationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ZAxisRegulationThreshold(this);	}

	virtual	int32		GetItemClassType(void)	override	{		return 0;		}

	//void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	void	Calc(void);
	double	CalcLine(double Data[],int N);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResult    (ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;

private:
};

class   ZAxisRegulationInLayer : public AlgorithmInLayerPLI
{
public:

	ZAxisRegulationInLayer(AlgorithmInPageRoot *parent)
		:AlgorithmInLayerPLI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType)	override
		{	
			ZAxisRegulationYDirItem	*a=new ZAxisRegulationYDirItem();	
			a->SetParent(this);
			return a;
		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	//virtual	bool	Save(QIODevice *f);
	//virtual	bool	Load(QIODevice *f);

private:
};

class   ZAxisRegulationInPage : public AlgorithmInPagePLI
{
public:
	ZAxisRegulationInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new ZAxisRegulationInLayer(parent);	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	ZAxisRegulationBase : public AlgorithmBase
{
public:
	QColor	ColorRegulation;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorRegulation;
	QColor	NegColorSelected;
	int		BrightnessRange;
	bool	CheckMaster;
	int		Gap;

	ZAxisRegulationBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new ZAxisRegulationInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("ZAxisRegulation");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigZAxisRegulation.dat");	}

};

//===================================================================================
class	CmdAddArea	: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		Layers;
	int32		AxisID;
	int32		CenterInMaster;
	int32		OKZone;

	CmdAddArea(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdStartCalc	: public GUIDirectMessage
{
public:

	CmdStartCalc(LayersBase *base):GUIDirectMessage(base){}
};

class	ItemInfoList : public NPList<ItemInfoList>
{
public:
	int		ItemID;
	int		x1,y1,x2,y2;
	int32	AxisID;
	int32	Layer;
	int32	Page;
	int32	CenterInMaster;
	int32	OKZone;
	int32	ResultCenter;
	bool	ResultOK;

	ItemInfoList(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ItemInfoContainer : public NPListPack<ItemInfoList>
{
public:
	ItemInfoContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	ItemInfoContainer	&operator=(ItemInfoContainer &src);
};

inline	bool	ItemInfoList::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false){
		return false;
	}
	if(::Save(f,x1)==false){
		return false;
	}
	if(::Save(f,y1)==false){
		return false;
	}
	if(::Save(f,x2)==false){
		return false;
	}
	if(::Save(f,y2)==false){
		return false;
	}
	if(::Save(f,AxisID)==false){
		return false;
	}
	if(::Save(f,Layer)==false){
		return false;
	}
	if(::Save(f,Page)==false){
		return false;
	}
	if(::Save(f,CenterInMaster)==false){
		return false;
	}
	if(::Save(f,OKZone)==false){
		return false;
	}
	if(::Save(f,ResultCenter)==false){
		return false;
	}
	if(::Save(f,ResultOK)==false){
		return false;
	}
	return true;
}
inline	bool	ItemInfoList::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false){
		return false;
	}
	if(::Load(f,x1)==false){
		return false;
	}
	if(::Load(f,y1)==false){
		return false;
	}
	if(::Load(f,x2)==false){
		return false;
	}
	if(::Load(f,y2)==false){
		return false;
	}
	if(::Load(f,AxisID)==false){
		return false;
	}
	if(::Load(f,Layer)==false){
		return false;
	}
	if(::Load(f,Page)==false){
		return false;
	}
	if(::Load(f,CenterInMaster)==false){
		return false;
	}
	if(::Load(f,OKZone)==false){
		return false;
	}
	if(::Load(f,ResultCenter)==false){
		return false;
	}
	if(::Load(f,ResultOK)==false){
		return false;
	}
	return true;
}

inline	bool	ItemInfoContainer::Save(QIODevice *f)
{
	int32	N=GetCount();
	if(::Save(f,N)==false){
		return false;
	}
	for(ItemInfoList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
inline	bool	ItemInfoContainer::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	RemoveAll();
	for(int i=0;i<N;i++){
		ItemInfoList	*a=new ItemInfoList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

inline	ItemInfoContainer	&ItemInfoContainer::operator=(ItemInfoContainer &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);
	return *this;
}

class	CmdReqItemInfoList	: public GUIDirectMessage
{
public:
	ItemInfoContainer	Infos;

	CmdReqItemInfoList(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetItemInfo	: public GUIDirectMessage
{
public:
	int32		AxisID;
	int32		ItemID;
	int32		Layer;
	int32		CenterInMaster;
	int32		OKZone;

	CmdSetItemInfo(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqItemResult: public GUIDirectMessage
{
public:
	int32	AxisID;

	double	*ResultTable;
	int		ResultCount;

	CmdReqItemResult(LayersBase *base):GUIDirectMessage(base)	{		ResultTable=NULL;	}
	~CmdReqItemResult(void){	if(ResultTable!=NULL){	delete	[]ResultTable;	ResultTable=NULL;	}	}
};

#endif
