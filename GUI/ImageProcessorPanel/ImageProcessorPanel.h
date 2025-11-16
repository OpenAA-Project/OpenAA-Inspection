/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageProcessorPanel\ImageProcessorPanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
