/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AreaFilterImagePanel\AreaFilterImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef AREAFILTERIMAGEPANEL_H
#define AREAFILTERIMAGEPANEL_H

#include "areafilterimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	AreaFilterImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	AreaFilterImagePanel(LayersBase *Base ,QWidget *parent);
	~AreaFilterImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage	(void)	override;
private slots:
};


#endif // AREAFILTERIMAGEPANEL_H
