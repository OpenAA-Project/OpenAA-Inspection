/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotRegulation\XDotRegulation.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XDotRegulation_h
#define XDotRegulation_h

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XDirectComm.h"
#include "XGeneralFunc.h"
#include "XCSV.h"
#include "XDoubleClass.h"

#define	DotRegulationVersion	1

class	DotRegulationItem;
class	DotRegulationInLayer;


class	DotRegulationDrawAttr : public AlgorithmDrawAttr
{
public:
	DotRegulationDrawAttr(void){}
	DotRegulationDrawAttr(QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel)
		: AlgorithmDrawAttr(  ncol , ntranparentLevel
							, scol , stranparentLevel
							, acol , atranparentLevel){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};


inline	bool	DotRegulationDrawAttr::Save(QIODevice *f)
{	
	return true;
}
inline	bool	DotRegulationDrawAttr::Load(QIODevice *f)
{	
	return true;
}

//======================================================================

class	DotRegulationThreshold : public AlgorithmThreshold
{
public:

	DotRegulationThreshold(AlgorithmItemPLI *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{		return true;	}
	virtual	bool	Load(QIODevice *f)					override{		return true;	}
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	DotRegulationBrightnessItem : public AlgorithmItemPLI
{
public:
	int		ResultLen;
	double	*ResultTable;

	DotRegulationBrightnessItem(void);
	~DotRegulationBrightnessItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DotRegulationBrightnessItem();	}
	const	DotRegulationThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const DotRegulationThreshold *)GetThresholdBaseReadable(base);	}
	DotRegulationThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (DotRegulationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new DotRegulationThreshold(this);	}

	virtual	int32		GetItemClassType(void)	override	{		return 0;		}

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	void	Calc(void);
private:
};

class	DotRegulationFocusItem : public AlgorithmItemPLI
{
public:

	DotRegulationFocusItem(void);
	~DotRegulationFocusItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DotRegulationFocusItem();	}
	const	DotRegulationThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const DotRegulationThreshold *)GetThresholdBaseReadable(base);	}
	DotRegulationThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (DotRegulationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new DotRegulationThreshold(this);	}

	virtual	int32		GetItemClassType(void)	override	{		return 1;		}

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	void	Calc(void);
private:
};

class	DotRegulationDotArea : public AlgorithmItemPLI
{
public:
	PureFlexAreaListContainer	PureFlexAreaListContainer;

	DotRegulationDotArea(void);
	~DotRegulationDotArea(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new DotRegulationDotArea();	}
	const	DotRegulationThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const DotRegulationThreshold *)GetThresholdBaseReadable(base);	}
	DotRegulationThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (DotRegulationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new DotRegulationThreshold(this);	}

	virtual	int32		GetItemClassType(void)	override	{		return 2;		}

	//virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	Pickup(int Threshold);
	void	MakeXPosListStr(DoubleList &List);
	void	MakeYPosListStr(DoubleList &List);
	void	MakeBrightnessListStr(QStringListListCSV &List);
private:
	PureFlexAreaList	*FindUpper(PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer);
	PureFlexAreaList	*FindDown (PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer);
	PureFlexAreaList	*FindLeft (PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer);
	PureFlexAreaList	*FindRight(PureFlexAreaList *a,PureFlexAreaListContainer &PureFlexAreaListContainer);

};

class   DotRegulationInLayer : public AlgorithmInLayerPLI
{
public:

	DotRegulationInLayer(AlgorithmInPageRoot *parent)
		:AlgorithmInLayerPLI(parent){}

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	//virtual	bool	Save(QIODevice *f);
	//virtual	bool	Load(QIODevice *f);

private:
};

class   DotRegulationInPage : public AlgorithmInPagePLI
{
public:
	DotRegulationInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new DotRegulationInLayer(parent);	}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	DotRegulationBase : public AlgorithmBase
{
public:
	QColor	ColorRegulation;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorRegulation;
	QColor	NegColorSelected;

	DotRegulationBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new DotRegulationInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("DotRegulation");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigDotRegulation.dat");	}
};

//===================================================================================
class	CmdAddAreaBrightness	: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		Layers;

	CmdAddAreaBrightness(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdAddDotArea	: public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddDotArea(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdAddAreaFocus	: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		Layers;

	CmdAddAreaFocus(LayersBase *base):GUIDirectMessage(base){}
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
	int32	AxisID;
	int32	ItemID;
	int32	Layer;

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
