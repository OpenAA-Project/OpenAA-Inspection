/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMasterNames\ShowMasterNamesForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWMASTERNAMESFORM_H
#define SHOWMASTERNAMESFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowMasterNamesForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowMasterNamesForm : public GUIFormBase
{
	Q_OBJECT

public:
	bool	ShowMasterID;
	bool	ShowMasterName;
	bool	ShowLotID;
	bool	ShowLotName;
	bool	ShowWorkerID;
	bool	ShowWorkerName;

	QString	TitleMasterID;
	QString	TitleMasterName;
	QString	TitleLotID;
	QString	TitleLotName;
	QString	TitleWorkerID;
	QString	TitleWorkerName;

	bool	ShowHeadMasterID;
	bool	ShowHeadMasterName;
	bool	ShowHeadLotID;
	bool	ShowHeadLotName;
	bool	ShowHeadWorkerID;
	bool	ShowHeadWorkerName;

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

	ShowMasterNamesForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowMasterNamesForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowMasterNamesFormClass ui;
private slots:
	void	ResizeAction();
};

#endif // SHOWMASTERNAMESFORM_H
