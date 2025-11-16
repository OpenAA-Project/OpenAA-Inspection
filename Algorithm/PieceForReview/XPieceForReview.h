/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPieceForReview.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPIECEFORREVIEW_H)
#define	XPIECEFORREVIEW_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XPieceForReviewItem.h"

#define	PieceForReviewVersion	1

class	PieceForReviewItem;

#define	PieceForReviewReqItemCount	10101
#define	PieceForReviewSendItemCount	10102

//=====================================================================
class	PieceForReviewDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorPieceForReview;
	QColor	NegColorSelected;
	bool	OverlapImage;

	PieceForReviewDrawAttr(void){}
	PieceForReviewDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	PieceForReviewDrawAttr(  QColor ncol ,int ntranparentLevel
							,QColor scol ,int stranparentLevel
							,QColor acol ,int atranparentLevel
							,QColor nncol
							,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorPieceForReview	=nncol;	
		NegColorSelected		=nscol;	
		NegColorPieceForReview.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

//==========================================================================

class	PieceForReviewItem;


class   PieceForReviewInPage : public AlgorithmInPagePI
{
public:
	PieceForReviewInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override
		{	
			PieceForReviewItem	*a=new PieceForReviewItem();	
			a->SetParent(this);
			return a;
		}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	PieceForReviewItem	*FindItem(QString areaname);
	int				GetItemTypeCount(void);
	virtual	bool	ExecuteManageResult		(int ExeID ,ResultInspection *Res)	override;
};

class	PieceForReviewBase : public AlgorithmBase
{
public:
	QColor	ColorPieceForReview;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorPieceForReview;
	QColor	NegColorSelected;

	int		OverlappedRStrength;
	int		OverlappedGStrength;
	int		OverlappedBStrength;

	int		OverlappedRStrengthActive;
	int		OverlappedGStrengthActive;
	int		OverlappedBStrengthActive;

	int		OverlappedRStrengthSelected;
	int		OverlappedGStrengthSelected;
	int		OverlappedBStrengthSelected;

	IntList	AreaNumberList;

	PieceForReviewBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override{	return new PieceForReviewInPage(parent);	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("PieceForReview");		}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("PieceForReview.dat");	}
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)	override;
	virtual	bool	LoadOnlyBase(QIODevice *f)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteManageResult		(int ExeID ,ResultInspection *Res			)	override;

	bool	Name2GloalPos(QString Name ,int &XGlobalPos, int &YGlobalPos);
	bool	Name2LocalPos(QString Name ,int &Page ,int &XLocalPos, int &YLocalPos);
	bool	LocalPos2Name(int Page ,int XLocalPos, int YLocalPos ,QString &Name);
	bool	GlobalPos2Name(int XGlobalPos, int YGlobalPos ,QString &Name);

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

private:
	bool	ExecuteManageResultOnPage(int ExeID ,ResultInspection *Res ,int localPage);
};
//==================================================================================


class	ClassPieceForReviewReqItemCount
{
public:
	int32	GlobalPage;

	ClassPieceForReviewReqItemCount(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ClassPieceForReviewSendItemCount
{
public:
	int32	GlobalPage;
	IntList	ItemAreaNumber;

	ClassPieceForReviewSendItemCount(void);
	void	ConstructList(ClassPieceForReviewReqItemCount *Req ,PieceForReviewBase *ABase);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif