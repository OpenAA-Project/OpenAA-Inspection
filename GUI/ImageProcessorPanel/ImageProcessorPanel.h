/*
 * Copyright (C) 2025
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


#ifndef IMAGEPROCESSORPANEL_H
#define IMAGEPROCESSORPANEL_H

#include "imageprocessorpanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XImageProcessor.h"

class	ImageProcessorPanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ImageProcessorPanel(LayersBase *Base ,QWidget *parent);
	~ImageProcessorPanel(void){}

	virtual void	Prepare(void) override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;

	GrouperImageItem	*CurrentItem;

	virtual	bool	DynamicPickupColor(int globalX,int globalY ,QColor &Ret)	override;
	virtual	bool	DrawImage(QPainter &pnt ,QImage &PntImage ,IntList &LayerList)	override;
	virtual	QImage	GetSaveImage(int gx1, int gy1, int gx2 ,int gy2)	override;
private slots:
	//virtual	void	CanvasSlotOnPaint(QPainter &pnt);
};


#endif // IMAGEPROCESSORPANEL_H