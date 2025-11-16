/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MeasureLineMoveImagePanel\MeasureLineMoveImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef MEASURELINEMOVEIMAGEPANEL_H
#define MEASURELINEMOVEIMAGEPANEL_H

#include "measurelinemoveimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	MeasureLineMoveImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	MeasureLineMoveImagePanel(LayersBase *Base ,QWidget *parent);
	~MeasureLineMoveImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	void	StartPage(void)		override;

	virtual	void	ExecuteMouseLDown(int globalX ,int globalY)	override;

private slots:
};
#endif // MEASURELINEMOVEIMAGEPANEL_H
