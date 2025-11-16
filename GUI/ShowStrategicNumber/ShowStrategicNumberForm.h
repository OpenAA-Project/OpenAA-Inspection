/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowStrategicNumber\ShowStrategicNumberForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SHOWSTRATEGICNUMBERFORM_H
#define SHOWSTRATEGICNUMBERFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowStrategicNumberForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowStrategicNumberForm : public GUIFormBase
{
	Q_OBJECT

public:
	ShowStrategicNumberForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowStrategicNumberForm();

	virtual	void	Prepare(void)	override;
	virtual	void	BuildForShow(void)	override;
	virtual	void	ShowInPlayer(int64 shownInspectionID)	override;

private:
	Ui::ShowStrategicNumberFormClass ui;

private slots:
	void on_spinBoxNumber_valueChanged(int);
	void	SlotChangeCurrentStrategicNumber();
	void	SlotChangeCurrentStrategicNumberSeq();
};

#endif // SHOWSTRATEGICNUMBERFORM_H
