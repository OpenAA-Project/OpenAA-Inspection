/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceForReviewImagePanel\PieceForReviewImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIECEFORREVIEWIMAGEPANEL_H
#define PIECEFORREVIEWIMAGEPANEL_H

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	PieceForReviewImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	PieceForReviewImagePanel(LayersBase *Base ,QWidget *parent);
	~PieceForReviewImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)		override;
protected:

private slots:
};

#endif // PIECEFORREVIEWIMAGEPANEL_H
