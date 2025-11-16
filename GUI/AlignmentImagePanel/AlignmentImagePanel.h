/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentImagePanel\AlignmentImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef ALIGNMENTIMAGEPANEL_H
#define ALIGNMENTIMAGEPANEL_H

#include "alignmentimagepanel_global.h"
#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "XAlignment.h"


class	GUICmdReqAlignmentItemsBmp;
class	GUICmdSendAlignmentItemsBmp;

class	AlignmentImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	mtToolButtonWithBalloon	*AreaButton;
	mtToolButtonWithBalloon	*InsideButton;
	mtToolButtonWithBalloon	*ShiftButton;
	mtToolButtonWithBalloon	*OutsideButton;
	QToolBar	ABar;

	int								ItemsBmpCounts;
	GUICmdSendAlignmentItemsBmp		**ItemsBmpReceiver;
	GUICmdReqAlignmentItemsBmp		**ItemsBmpRequester;

public:
	AlignmentImagePanel(LayersBase *Base ,QWidget *parent);
	~AlignmentImagePanel(void);

	virtual void	Prepare(void)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;
	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void	ButtonExecuteDeleteSelected(void)			override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual void	StartPage	(void)	override;
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage) override;

private slots:
	void AreaButtonDown (bool checked);
	void InsideButtonDown (bool checked);
	void ShiftButtonDown (bool checked);
	void OutsideButtonDown (bool checked);
};

//=========================================================

class	GUICmdReqAddAlignment : public GUICmdPacketBase
{
public:
	int32		GlobalPage;
	FlexArea	Area;

	GUICmdReqAddAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetAlignmentButton : public GUICmdPacketBase
{
public:
	AlignmentDrawAttr::DrawModeAttr	DAttr;

	GUICmdSetAlignmentButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentItemsBmp : public GUICmdPacketBase
{
public:
	struct	GUIReqBmpStruct
	{
		int32	Gx1;
		int32	Gy1;
		int32	Gx2;
		int32	Gy2;
		int32	Dx1;
		int32	Dy1;
		int32	Dx2;
		int32	Dy2;
		double	ZoomRate;
		int32	MovX;
		int32	MovY;
		int32	GlobalPage;
		int32	MoveGlobalDx;
		int32	MoveGlobalDy;
	}Data;
	IntList		LayerList;

	GUICmdReqAlignmentItemsBmp( LayersBase *Base
							,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReqAlignmentItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendAlignmentItemsBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;
	QPainter	*PntFromIData;

	GUICmdSendAlignmentItemsBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAlignmentItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase);
};

#endif // ALIGNMENTIMAGEPANEL_H
