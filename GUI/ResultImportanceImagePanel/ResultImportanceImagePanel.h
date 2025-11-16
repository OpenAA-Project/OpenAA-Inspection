/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ResultImportanceImagePanel\ResultImportanceImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef ResultImportanceImagePanel_H
#define ResultImportanceImagePanel_H

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	ResultImportanceImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	ResultImportanceImagePanel(LayersBase *Base ,QWidget *parent);
	~ResultImportanceImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;

	virtual void	StartPage(void)	override;
protected:

private slots:
};

#endif // ResultImportanceImagePanel_H
