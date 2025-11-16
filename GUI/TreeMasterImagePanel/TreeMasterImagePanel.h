/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TreeMasterImagePanel\TreeMasterImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef TREEMASTERIMAGEPANEL_H
#define TREEMASTERIMAGEPANEL_H

#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	TreeMasterImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	TreeMasterImagePanel(LayersBase *Base ,QWidget *parent);
	~TreeMasterImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	
	virtual	AlgorithmDrawAttr *CreateDrawAttrPointer(void)	override;
	virtual void SelectArea(IntList &LayerList,FlexArea &area)	override; // test

	virtual void	StartPage(void)		override;
protected:

private slots:
};

#endif // TREEMASTERIMAGEPANEL_H
