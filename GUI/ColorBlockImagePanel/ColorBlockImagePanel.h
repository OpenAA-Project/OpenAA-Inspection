/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ColorBlockImagePanel\ColorBlockImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef COLORBLOCKIMAGEPANEL_H
#define COLORBLOCKIMAGEPANEL_H

#include "colorblockimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XPropertyColorBlockPacket.h"

class	ColorBlockImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	ListPageLayerIDPack	CurrentItem;
public:
	ColorBlockImagePanel(LayersBase *Base ,QWidget *parent);
	~ColorBlockImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void				ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
	virtual	void				SlotMouseLDown(int globalX,int globalY)	override;
	virtual void				StartPage	(void)	override;
private slots:
	void	SlotTouchItems(ListPageLayerIDPack *);
};
//=========================================================

class	GUICmdReqColorBlockInfo : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqColorBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendColorBlockInfo : public GUICmdPacketBase
{
public:
	IntList		LayerList;
	IntList		LibIDList;
	int	LocalX,LocalY;

	GUICmdSendColorBlockInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage, int localX, int localY,LayersBase	&LocalLBase);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // COLORBLOCKIMAGEPANEL_H
