/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\BlockImagePanel\BlockImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BLOCKIMAGEPANEL_H
#define BLOCKIMAGEPANEL_H

#include "blockimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertyBlockPacket.h"
//#include "XBlock.h"

class	BlockImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;

public:
	bool						ShiftRightClicked;

	BlockImagePanel(LayersBase *Base ,QWidget *parent);
	~BlockImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)	override;
	virtual	void				SlotMouseRDown(int globalX,int globalY)	override;
	virtual void	StartPage(void)	override;
private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};

//=========================================================

class	GUICmdReqBlockInfo : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendBlockInfo : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	IntList		LibIDList;
	int	LocalX,LocalY;

	GUICmdSendBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage, int localX, int localY,LayersBase	&LocalLBase);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BLOCKIMAGEPANEL_H
