/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoPCBHoleAlignerImagePanel\AutoPCBHoleAlignerImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef AutoPCBHoleAlignerIMAGEPANEL_H
#define AutoPCBHoleAlignerIMAGEPANEL_H

#include "AutoPCBHoleAlignerimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAutoPCBHoleAligner.h"

class	AutoPCBHoleAlignerImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	AutoPCBHoleAlignerImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;

	virtual	void	RequireHooks(GUIFormBase *mother)	override;
	
	void	ExecuteDrawEnd(FlexArea &Area);
};

#endif // AUTOPCBHOLEALIGNERIMAGEPANEL_H
