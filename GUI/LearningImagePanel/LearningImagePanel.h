/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LearningImagePanel\LearningImagePanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LEARNINGIMAGEPANEL_H
#define LEARNINGIMAGEPANEL_H



#include "XDisplayImage.h"

#include <QToolButton>
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonWithBalloon.h"

class	LearningImagePanel : public DisplayImageWithAlgorithm
{
	Q_OBJECT

public:
	LearningImagePanel(LayersBase *Base ,QWidget *parent);
	~LearningImagePanel(void){}

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	DrawEndAfterOperation(FlexArea &area)	override;

	virtual	AlgorithmDrawAttr	*CreateDrawAttrPointer(void)	override;
	virtual	void ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)	override;
	virtual void	StartPage	(void)	override;

protected:
private slots:
};

//=========================================================

#endif // LEARNINGIMAGEPANEL_H
