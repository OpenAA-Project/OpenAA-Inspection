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