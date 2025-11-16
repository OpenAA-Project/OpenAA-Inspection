/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TunnelCrackImagePanel\TunnelCrackImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef TUNNELCRACKIMAGEPANEL_H
#define TUNNELCRACKIMAGEPANEL_H

#include "tunnelcrackimagepanel_global.h"
#include "XDisplayImage.h"
#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	GUICmdReqTunnelCrackImageItemsBmp;
class	GUICmdSendTunnelCrackImageItemsBmp;

class	TunnelCrackImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

	int								ItemsBmpCounts;
	GUICmdSendTunnelCrackImageItemsBmp	**ItemsBmpReceiver;
	GUICmdReqTunnelCrackImageItemsBmp	**ItemsBmpRequester;

public:
	TunnelCrackImagePanel(LayersBase *Base ,QWidget *parent);
	~TunnelCrackImagePanel(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)		override;

	//AlgorithmDrawAttr	*CreateDrawAttrPointer(void);
	virtual	void	StartPage(void)	override;

	virtual	void	GetActiveLayerList(IntList &LayerList)			override;
	virtual	void	CanvasSlotOnPaint(QPainter &pnt)				override;
	virtual	void	DrawAfterImage(QPainter &pnt ,QImage &PntImage)	override;
};

//============================================================================================
class	GUICmdReqTunnelCrackImageItemsBmp : public GUICmdPacketBase
{
	TunnelCrackImagePanel	*Form;
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
	QString		InstName;
	bool		ShowNGItemButton;
	bool		ShowAllItemsButton;
	AlgorithmBase	*SelectedAlgorithm;
	QString	AlgoRoot;
	QString	AlgoName;
	bool ResultMode;

	GUICmdReqTunnelCrackImageItemsBmp( LayersBase *Base ,TunnelCrackImagePanel *Form
								,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdReqTunnelCrackImageItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendTunnelCrackImageItemsBmp : public GUICmdPacketBase
{
public:
	QImage		*IData;
	QPainter	*PntFromIData;

	GUICmdSendTunnelCrackImageItemsBmp(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdSendTunnelCrackImageItemsBmp(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

	void	MakeImage(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,TunnelCrackImagePanel	*A
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase
					 ,bool ResultMode);
	void	MakeImageAll(IntList &LayerList					 
					 ,int Gx1,int Gy1 ,int Gx2,int Gy2
					 ,int Dx1,int Dy1 ,int Dx2,int Dy2
					 ,int MovX,int MovY, double ZoomRate
					 ,int localPage
					 ,int MoveGlobalDx ,int MoveGlobalDy
					 ,TunnelCrackImagePanel	*A
					 ,AlgorithmBase	*L
					 ,LayersBase &LocalLBase
					 ,bool ResultMode);
};



#endif // TUNNELCRACKIMAGEPANEL_H
