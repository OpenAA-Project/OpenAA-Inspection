/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\BuslineImagePanel\BuslineImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUSLINEIMAGEPANEL_H
#define BUSLINEIMAGEPANEL_H

#include "buslineimagepanel_global.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XDisplayImage.h"

class	BuslineImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	BuslineImagePanel(LayersBase *Base ,QWidget *parent);
	~BuslineImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	//AlgorithmDrawAttr	*CreateDrawAttrPointer(void);
	virtual	void	StartPage(void)	override;


private slots:
};


#endif // BUSLINEIMAGEPANEL_H
