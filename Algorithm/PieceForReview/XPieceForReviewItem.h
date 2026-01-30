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
	int32		AreaNumber;		//���肷���G���A�ԍ�	�����ԍ��͓����G���A�Ƃ��ĔF��������
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