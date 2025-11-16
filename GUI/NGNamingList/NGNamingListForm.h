/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NGNamingList\NGNamingListForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef NGNAMINGLISTFORM_H
#define NGNAMINGLISTFORM_H

#include "XGUIFormBase.h"
#include "ui_NGNamingListForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XCmdPacket.h"

class NGNamingListForm : public GUIFormBase
{
	Q_OBJECT

public:
	int32	WidthAreaName;
	int32	WidthNGCountInPiece;

	NGAreaListContainer	NGData;
	QString			TargetImagePanelName;

	NGNamingListForm(LayersBase *Base ,QWidget *parent = 0);
	~NGNamingListForm();

	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;

private:
	Ui::NGNamingListFormClass ui;

private slots:
	void	ResizeAction();
};

#endif // NGNAMINGLISTFORM_H
