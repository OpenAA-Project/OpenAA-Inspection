/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\TargetImageControlTools\TargetImageControlTools.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef TARGETIMAGECONTROLTOOLS_H
#define TARGETIMAGECONTROLTOOLS_H

#include "targetimagecontroltools_global.h"
#include <QToolButton>
#include <QToolBar>
#include <QComboBox>
#include <QTimer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"
#include "mtToolButtonColored.h"
#include "XDisplayImage.h"
#include "XIntClass.h"


class	TargetImageControlTools : public GUIFormBase
{
	Q_OBJECT

	QToolBar	IBar;
	mtToolButtonWithBalloon	*NoItemButton;
	mtToolButtonWithBalloon	*NGItemButton;
	mtToolButtonWithBalloon	*AllItemsButton;
	QToolBar	RBar;
	mtToolButtonWithBalloon	*RedCircleButton;
	QToolBar	LayerBar;
	mtToolButtonColored		**LButtonList;
	int						LNumb;
	int						XPos,RPos,LPos;
	QComboBox				ComboItemLib;
	AlgorithmBase			*SelectedAlgorithm;
	bool					BlinkShowMode;
	QTimer					TM;

	void	ClearLButtonList();
public:
	bool	ShowNGItemButton;
	bool	ShowAllItemsButton;
	bool	ShowLayer;
	bool	ShowComboItemLib;
	bool	ExclusiveLayer;
	int		ShowLayerAtFirst;
	QStringList	RelatedPanels;
	int32	IconSize;
	bool	InitONNoItemButton		;
	bool	InitONNGItemButton		;
	bool	InitONAllItemsButton	;
	bool	InitONRedCircleButton	;
	int32	BlinkNGMilisec;

	TargetImageControlTools(LayersBase *Base ,QWidget *parent);
	~TargetImageControlTools(void);
	
	virtual void	Prepare(void)		override;
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	QStringList	GetRelatedForm(void)		override {	return RelatedPanels;	}

private slots:
	void	NoItemButtonDown (bool checked);
	void	NGItemButtonDown (bool checked);
	void	RedCircleButtonDown(bool checked);
	void	AllItemsButtonDown (bool checked);
	void	ResizeAction();
	void	SlotCurrentIndexChanged ( int index );
	void	LayerClicked(bool checked);
	void	BlinkTimeout();
};

//======================================================================

class	CmdReqTargetImageLayer : public GUIDirectMessage
{
public:
	bool			ShowNGItemButton;
	bool			ShowAllItemsButton;
	bool			RedCircleMode;
	AlgorithmBase	*SelectedAlgorithm;
	IntList			LayerList;

	CmdReqTargetImageLayer(LayersBase *base,int LayerNumb);
};

inline	CmdReqTargetImageLayer::CmdReqTargetImageLayer(LayersBase *base,int LayerNumb)
	:GUIDirectMessage(base)
{	
	ShowNGItemButton=false;
	SelectedAlgorithm=NULL;
	for(int L=0;L<LayerNumb;L++){
		LayerList.Add(L);
	}
}
#endif // TARGETIMAGECONTROLTOOLS_H
