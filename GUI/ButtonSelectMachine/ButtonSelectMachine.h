/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectMachine\ButtonSelectMachine.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSELECTMACHINE_H
#define BUTTONSELECTMACHINE_H

#include "buttonselectmachine_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class	ButtonSelectMachine : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	SaveMachineID;

	ButtonSelectMachine(LayersBase *Base ,QWidget *parent);
	~ButtonSelectMachine(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	void SelectMachine(int32 MachineID);

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

class	CmdSelectMachine : public GUIDirectMessage
{
public:
	CmdSelectMachine(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONSELECTMACHINE_H
