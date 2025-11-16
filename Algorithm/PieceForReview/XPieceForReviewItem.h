/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPieceForReviewItem.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPIECEFORREVIEWITEM_H)
#define	XPIECEFORREVIEWITEM_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"

class	PieceForReviewItem;

class   ErrorGroupPieceForReview : public ErrorGroup
{
public:
	PieceForReviewItem	*Item;

	ErrorGroupPieceForReview(LayersBase *Base):ErrorGroup(Base){}
};

//==========================================================================
class	PieceForReviewThreshold : public AlgorithmThreshold
{
public:

	PieceForReviewThreshold(PieceForReviewItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override{}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override{	return true;	}
    virtual	bool	Load(QIODevice *f)					override{	return true;	}
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	PieceForReviewItem : public AlgorithmItemPI
{
public:
	int32		AreaNumber;		//特定するエリア番号	同じ番号は同じエリアとして認識される
	QString		AreaName;
	int32		SysRegNumber;

	static	BYTE	OverlappedColorTable[3][256];
	static	BYTE	OverlappedColorTableActive[3][256];
	static	BYTE	OverlappedColorTableSelected[3][256];
	static	bool	InitializedTable;


	PieceForReviewItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new PieceForReviewItem();	}
	const	PieceForReviewThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const PieceForReviewThreshold *)GetThresholdBaseReadable(base);	}
	PieceForReviewThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (PieceForReviewThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new PieceForReviewThreshold(this);	}

	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool	SaveUnique(QIODevice *f)	override;
	virtual	bool	LoadUnique(QIODevice *f)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	DrawOverlappedImage(QImage &pnt, int movx ,int movy ,double ZoomRate
								,int dx, int dy
								,BYTE ColorTable[3][256]);
	virtual	void			DrawMove(int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;


	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	void	BindResult(ResultInItemRoot *Item,ResultPosList *RPos);

private:
	void	SetColorTable(void);

};

#endif