/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowTopBottomSideInfo\ShowTopBottomSideInfoForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWMASTERNAMESFORM_H
#define ShowTopBottomSideInfoForm_H

#include "XGUIFormBase.h"
#include "ui_ShowTopBottomSideInfoForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowTopBottomSideInfoForm: public GUIFormBase
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

	ShowTopBottomSideInfoForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowTopBottomSideInfoForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowTopBottomSideInfoFormClass ui;
private slots:
	void	ResizeAction();
};

#endif // ShowTopBottomSideInfoForm_H
