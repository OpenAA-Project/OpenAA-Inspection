/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StatisticImagerImagePanel\StatisticImagerImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STATISTICIMAGERIMAGEPANEL_H
#define STATISTICIMAGERIMAGEPANEL_H

#include "statisticimagerimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XStatisticImager.h"

class	StatisticImagerImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:

	StatisticImagerImagePanel(LayersBase *Base ,QWidget *parent);
	~StatisticImagerImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	DrawImage(QPainter &pnt ,QImage &PntImage,IntList &LayerList) override;
	virtual void	StartPage	(void)	override;
///////////
	bool	StatisticBuffisNULL();
};

//================================================================

class	GUICmdReqStatisticDraw : public GUICmdPacketBase
{
public:
	StatisticImagerDrawAttr::_DrawMode	DrawMode;
	int		Movx ,Movy;
	double	ZoomRate;
	int		XLen,YLen;

	GUICmdReqStatisticDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendStatisticDraw : public GUICmdPacketBase
{
public:
	QImage	*Image;

	GUICmdSendStatisticDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendStatisticDraw(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // STATISTICIMAGERIMAGEPANEL_H
