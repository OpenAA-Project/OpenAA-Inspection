/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingParameters\ButtonSettingParameters.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSETTINGPARAMETERS_H
#define BUTTONSETTINGPARAMETERS_H

#include "buttonsettingparameters_global.h"

#include <QPushButton>
#include <QDialog>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WEditParameterTab.h"

class	ButtonSettingParameters : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSettingParameters(LayersBase *Base ,QWidget *parent);
	~ButtonSettingParameters(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};



#endif // BUTTONSETTINGPARAMETERS_H
