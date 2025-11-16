/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLightDB\ButtonSelectLightDB.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSELECTLIGHTDB_H
#define BUTTONSELECTLIGHTDB_H

#include "buttonselectlightdb_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSelectLightDB : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	int		SelectedLightID;

	ButtonSelectLightDB(LayersBase *Base ,QWidget *parent);
	~ButtonSelectLightDB(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdReqCurrentSelectedLightID : public GUIDirectMessage
{
public:
	int		SelectedLightID;

	CmdReqCurrentSelectedLightID(LayersBase *base):GUIDirectMessage(base)		{	SelectedLightID=-1;	}
	CmdReqCurrentSelectedLightID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	SelectedLightID=-1;	}
};


#endif // BUTTONSELECTLIGHTDB_H
