/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PiecePanel\PiecePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIECEPANEL_H
#define PIECEPANEL_H

#include "piecepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPieceArrange.h"

class	PiecePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	QColor	AlgorithmImageColor;
	int32	AlgorithmImageTransparency;

	PiecePanel(LayersBase *Base ,QWidget *parent);
	~PiecePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	PickupColorAndMove(QImage &dst ,QImage &src ,QColor pickcol ,QColor putcol ,int dx,int dy);

	void	DrawInsideExpandedPaste( QPainter &pnt ,double movx,double movy,double ZoomRate
										    ,int SrcX ,int SrcY
											,int Dx,int Dy
											,int Page, int Layer, int ItemID
											,int ItemWidth ,int ItemHeight);
											
	virtual	void	ExpandedPasteExecute(ExpandedItemPosContainer &ExpandedItems)	override;
	virtual void	StartPage(void)	override;
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)	override;
	virtual	void	SlotCancelDraw()	override;
protected:
	virtual	void	DrawBtnDown()	override;
};

#endif // PIECEPANEL_H
