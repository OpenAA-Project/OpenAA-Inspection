/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPieceReviewSide.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XPIECEREVIEWSIDE_H)
#define	XPIECEREVIEWSIDE_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XPieceForReview.h"
#include "NListComp.h"
#include "XFlexAreaImage.h"

#define	PieceReviewSideVersion	1
#define	PieceReviewSideReqItems		10201
#define	PieceReviewSideSendItems	10202
#define	PieceReviewSideReqImage		10203
#define	PieceReviewSideSendImage	10204

class   PieceReviewSideInPage : public AlgorithmInPagePI
{
public:
	PieceReviewSideInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			PieceForReviewItem	*a=new PieceForReviewItem();	
			a->SetParent(this);
			return a;
		}
};

class	PieceReviewSideBase : public AlgorithmBase
{
	bool	Restructured;
public:
	QColor	ColorPieceReviewSide;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorPieceReviewSide;
	QColor	NegColorSelected;

	PieceReviewSideBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new PieceReviewSideInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("PieceReviewSide");			}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("PieceReviewSide.dat");		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

private:
	bool	ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage);
};
//==================================================================================

class	ReviewSideItems : public NPListSaveLoad<ReviewSideItems>
{
public:
	int		GlobalPage;
	int		AreaNumber;
	QString	AreaName;

	ReviewSideItems(void){}
	ReviewSideItems(const ReviewSideItems &src);

	virtual	bool	Save(QIODevice *f)	;
	virtual	bool	Load(QIODevice *f)	;
};

class	ReviewSideItemsContainer : public NPListPackSaveLoad<ReviewSideItems>
{
public:
	ReviewSideItemsContainer(void){}

	virtual	ReviewSideItems	*Create(void)	{	return new ReviewSideItems();	}
};

class	ClassPieceReviewSideReqItem
{
public:
	int	GlobalPage;

	ClassPieceReviewSideReqItem(void){	GlobalPage=-1;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ClassPieceReviewSideSendItem
{
public:
	ReviewSideItemsContainer	Items;

	ClassPieceReviewSideSendItem(void){}
	void	ConstructList(ClassPieceReviewSideReqItem *Req ,PieceReviewSideBase *ABase);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	ClassPieceReviewSideReqImage
{
public:
	int		GlobalPage;
	int		AreaNumber;

	ClassPieceReviewSideReqImage(void){	AreaNumber=-1;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ClassPieceReviewSideSendImage
{
public:
	FlexAreaImage	ImageR;
	FlexAreaImage	ImageG;
	FlexAreaImage	ImageB;

	ClassPieceReviewSideSendImage(void){}

	void	ConstructList(ClassPieceReviewSideReqImage *Req ,PieceReviewSideBase *ABase);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif