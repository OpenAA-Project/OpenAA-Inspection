/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoMaskingPIImagePanel\AutoMaskingPIImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef AUTOMASKINGPIIMAGEPANEL_H
#define AUTOMASKINGPIIMAGEPANEL_H


#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AutoMaskingPIImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	AutoMaskingPIImagePanel(LayersBase *Base ,QWidget *parent);
	~AutoMaskingPIImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;

	virtual	void	RequireHooks(GUIFormBase *mother)	override;

protected:

private slots:
};

//=========================================================
#endif // AUTOMASKINGPIIMAGEPANEL_H
