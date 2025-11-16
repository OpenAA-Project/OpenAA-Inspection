/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MatchingAlignmentImagePanel\MatchingAlignmentImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef MATCHINGALIGNMENTIMAGEPANEL_H
#define MATCHINGALIGNMENTIMAGEPANEL_H

#include "matchingalignmentimagepanel_global.h"

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	MatchingAlignmentImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	MatchingAlignmentImagePanel(LayersBase *Base ,QWidget *parent);
	~MatchingAlignmentImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage	(void)	override;

private slots:
};

#endif // MATCHINGALIGNMENTIMAGEPANEL_H
