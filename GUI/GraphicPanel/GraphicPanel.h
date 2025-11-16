/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GraphicPanel\GraphicPanel.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GRAPHICPANEL_H
#define GRAPHICPANEL_H

#include "graphicpanel_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GraphicPanel : public GUIFormBase
{
	Q_OBJECT

	QLabel	Label;

public:
	QString		FileName;
	bool		Scaling;

	GraphicPanel(LayersBase *Base ,QWidget *parent);
	~GraphicPanel(void);
	
	virtual void	Prepare(void)	override;
private:
	void	DrawOnly(void);

private slots:
	void	ResizeAction();
};

#endif // GRAPHICPANEL_H
