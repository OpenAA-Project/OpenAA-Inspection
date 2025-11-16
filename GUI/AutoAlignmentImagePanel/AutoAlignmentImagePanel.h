/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoAlignmentImagePanel\AutoAlignmentImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef AUTOALIGNMENTIMAGEPANEL_H
#define AUTOALIGNMENTIMAGEPANEL_H

#include "autoalignmentimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAutoAlignment.h"

class	AutoAlignmentImagePanel : public DisplayImageWithAlgorithm,public FunctionServerClass
{
	Q_OBJECT

public:
	int		ClickAreaSize;

	AutoAlignmentImagePanel(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;
	virtual void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual void	StartPage(void)	override;
	virtual void	ExecuteActiveOnItemXY(int globalX ,int globalY)	override;

	virtual	void	RequireHooks(GUIFormBase *mother)	override;
	void	ExecuteDrawEnd(FlexArea &Area);

private slots:
};

class	GUICmdReqAutoAlignmentInfoOnPoint : public GUICmdPacketBase
{
public:
	int	localX,localY;

	GUICmdReqAutoAlignmentInfoOnPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAutoAlignmentInfoOnPoint : public GUICmdPacketBase
{
public:
	int	ShiftXFromMaster,ShiftYFromMaster;
	int	ShiftXFromTarget,ShiftYFromTarget;
	int	ShiftRelativeXFromMaster,ShiftRelativeYFromMaster;
	int	ShiftRelativeXFromTarget,ShiftRelativeYFromTarget;

	GUICmdSendAutoAlignmentInfoOnPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeData(int localPage ,int localX,int localY);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // AUTOALIGNMENTIMAGEPANEL_H
