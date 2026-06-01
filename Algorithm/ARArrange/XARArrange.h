/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

//===========================================================================

class	ARItemList : public NPList<ARItemList>
{
public:
	int64						ItemID;
	XDateTime					CreatedTime;
	ARArrangeItem::ARResult		Result;
	DualIntClass				Position;

	ARItemList(void){}
	ARItemList(ARArrangeItem *p);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	
	ARItemList	&operator=(ARItemList &src);
};

class	ARItemListContainer : public NPListPack<ARItemList>
{
public:
	ARItemListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	ARItemListContainer	&operator+=(ARItemListContainer &src);
};

class	CmdMakeARArrangeList : public GUIDirectMessage
{
public:
	XDateTime				CreatedTime;
	ARItemListContainer		*ItemContainer;

	CmdMakeARArrangeList(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeARArrangeList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif