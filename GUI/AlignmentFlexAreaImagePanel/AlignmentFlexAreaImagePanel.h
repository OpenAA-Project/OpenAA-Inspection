/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentFlexAreaImagePanel\AlignmentFlexAreaImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef ALIGNMENTFLEXAREAIMAGEPANEL_H
#define ALIGNMENTFLEXAREAIMAGEPANEL_H

#include "alignmentflexareaimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAlignmentFlexArea.h"


class	AlignmentFlexAreaImagePanel : public DisplayImageWithAlgorithm
{
	bool	HasBitbuffData;
public:
	struct	ShiftResultStruct
	{
		int		IndexX1,IndexY1;
		int		IndexX2,IndexY2;
		int		IndexX3,IndexY3;
		bool	EnableIndex1;
		bool	EnableIndex2;
		bool	EnableIndex3;
		int		TotalShiftX		,TotalShiftY		,AreaID;	
		int		WholeMatchShiftX,WholeMatchShiftY;
		int		GlobalShiftX	,GlobalShiftY		,GlobalAreaID;

		ShiftResultStruct(void);
		void	Transform(LayersBase *Base,int GlobalPage);
		void	Clear(void);
	};
	struct	AlignmentFlexAreaImagePanel::ShiftResultStruct	ShiftResultData;
	int		CurrentGlobalX,CurrentGlobalY;

	AlignmentFlexAreaImagePanel(LayersBase *Base ,QWidget *parent);
	~AlignmentFlexAreaImagePanel(void);

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	ButtonExecuteDeleteSelected(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;

	virtual	void	CanvasSlotOnPaint(QPainter &pnt)	override;
	virtual	void	MouseMoveEvent(int globalX ,int globalY)	override;
	virtual	void	ExecuteMouseRDownWithShift(int globalX ,int globalY)	override;
};

//=========================================================

class	GUICmdReqAlignmentFlexAreaResultInfo : public GUICmdPacketBase
{
public:
	int	localX ,localY;

	GUICmdReqAlignmentFlexAreaResultInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlignmentFlexAreaResultInfo : public GUICmdPacketBase
{
public:
	struct	AlignmentFlexAreaImagePanel::ShiftResultStruct	ShiftResultData;

	GUICmdAckAlignmentFlexAreaResultInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdReqAlignmentPointInfo : public GUICmdPacketBase
{
public:
	int	AreaID;
	int	localX ,localY;

	GUICmdReqAlignmentPointInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlignmentPointInfo : public GUICmdPacketBase
{
public:
	int	ItemID;
	int	LibID;
	int	GlobalSearchDot;
	int	SearchDot;
	bool	KeepBW;

	GUICmdAckAlignmentPointInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReqSetAlignmentPointInfo : public GUICmdPacketBase
{
public:
	int		ItemID;
	int		LibID;
	int		GlobalSearchDot;
	int		SearchDot;
	bool	KeepBW;
	bool	ModeSetAll;

	GUICmdReqSetAlignmentPointInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=========================================================

class	GUICmdReqAlignmentFlexAreaCheckBitBuff: public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentFlexAreaCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlignmentFlexAreaCheckBitBuff : public GUICmdPacketBase
{
public:
	bool	HasData;

	GUICmdAckAlignmentFlexAreaCheckBitBuff(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================
#endif // ALIGNMENTFLEXAREAIMAGEPANEL_H
