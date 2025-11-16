/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\OutlineImagePanel\OutlineImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef OUTLINEIMAGEPANEL_H
#define OUTLINEIMAGEPANEL_H

#include "outlineimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertyOutlinePacket.h"

class	OutlineImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;
public:
	OutlineImagePanel(LayersBase *Base ,QWidget *parent);
	~OutlineImagePanel(void){}

	virtual void	Prepare(void)		override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)					override;

private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};

#endif // OUTLINEIMAGEPANEL_H
