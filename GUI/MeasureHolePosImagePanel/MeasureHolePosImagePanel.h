/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MeasureHolePosImagePanel\MeasureHolePosImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MEASUREHOLEPOSIMAGEPANEL_H
#define MEASUREHOLEPOSIMAGEPANEL_H

#include "measureholeposimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XDisplayImage.h"

class	MeasureHolePosImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	MeasureHolePosImagePanel(LayersBase *Base ,QWidget *parent);
	~MeasureHolePosImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	void	StartPage(void)	override;

private slots:
};

#endif // MEASUREHOLEPOSIMAGEPANEL_H
