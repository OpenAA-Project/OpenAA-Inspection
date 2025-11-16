/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LineEnhancerImagePanel\LineEnhancerImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef LINEENHANCERIMAGEPANEL_H
#define LINEENHANCERIMAGEPANEL_H

#include "lineenhancerimagepanel_global.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XLineEnhancer.h"
#include "XDisplayImage.h"


class	LineEnhancerImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	LineEnhancerImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage	(void)	override;

	void	ExecuteDrawEnd(FlexArea &Area);
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;

private slots:
};
#endif // LINEENHANCERIMAGEPANEL_H
