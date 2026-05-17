/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMasterNames\ShowMasterNamesForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWTHRESHOLDFILENAMEFORM_H
#define SHOWTHRESHOLDFILENAMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowThresholdFileNameForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowThresholdFileNameForm : public GUIFormBase
{
	Q_OBJECT

public:
	bool	ShowThresholdFile;
	QString	TitleThresholdFile;
	bool	ShowHeadThresholdFile;

	QString	AlignAttr;
	QColor	CharColor;
	QColor	BackColor;
	bool	TransparentBackColor;
	QColor	BorderColor;
	int		BorderWidth;
	QString	BorderStyle;
	QFont	CFont;

	QString	HeadAlignAttr;
	QColor	HeadCharColor;
	QColor	HeadBackColor;
	bool	HeadTransparentBackColor;
	QColor	HeadBorderColor;
	int		HeadBorderWidth;
	QString	HeadBorderStyle;
	QFont	HeadCFont;

	int		HeadWidth;

	ShowThresholdFileNameForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowThresholdFileNameForm();

	virtual void	Prepare(void)	override;
	virtual void	BuildForShow(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::Form ui;
private slots:
	void	ResizeAction();
};

#endif // SHOWTHRESHOLDFILENAMEFORM_H
