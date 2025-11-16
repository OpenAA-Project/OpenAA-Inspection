/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMasking.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XARArrangeH
#define XARArrangeH

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"

#define	ARArrangePIVersion	1

class	LearningImage;
class	ARArrangeItem;
class	ARArrangeInPage;
class	ARArrangeBase;

class	ARArrangeThreshold : public AlgorithmThreshold
{
public:

	ARArrangeThreshold(ARArrangeItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override	{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	ARArrangeItem : public AlgorithmItemPITemplate<ARArrangeInPage,ARArrangeBase>
{
	LearningImage	*Index;
public:
	enum	ARResult{
		__NotYet	=0
		,__OK		=1
		,__NG		=2
	}ARResultData;
public:
	ARArrangeItem(void){	Index=NULL;	ARResultData=__NotYet;	}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new ARArrangeItem();	}
	const	ARArrangeThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const ARArrangeThreshold *)GetThresholdBaseReadable(base);	}
	ARArrangeThreshold			*GetThresholdW(LayersBase *base=NULL){	return (ARArrangeThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new ARArrangeThreshold(this);	}

	virtual	int32		GetItemClassType(void)				override{		return 0;		}
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	LearningImage	*GetIndex(void)		{	return Index;			}
	void			SetIndex(LearningImage *p){	Index=p;			}
	ARResult		GetARResult(void)	{	return ARResultData;	}
};

//--------------------------------------------------------

class   ARArrangeInPage : public AlgorithmInPagePITemplate<ARArrangeItem,ARArrangeBase>
{
public:
	ARArrangeInPage(AlgorithmBase *parent);
	~ARArrangeInPage(void);

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

};

class	ARArrangeBase : public AlgorithmBase
{
public:

	ARArrangeBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override	{	return new ARArrangeInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	QString	GetDataText(void)			override{	return QString("ARArrange");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigARArrange.dat");	}

};


//==================================================================================

class	CmdReqAddARArrange : public GUIDirectMessage
{
public:
	FlexArea	Area;
	XDateTime	CreatedTime;

	CmdReqAddARArrange(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAddARArrange(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif