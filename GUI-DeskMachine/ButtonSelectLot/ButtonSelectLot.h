/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLot\ButtonSelectLot.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSELECTLOT_H
#define BUTTONSELECTLOT_H

#include "buttonselectlot_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButton.h"

class	ButtonSelectLot : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButton	Button;
	bool	LoadLastID;
public:
	ButtonSelectLot(LayersBase *Base ,QWidget *parent);
	~ButtonSelectLot(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	CmdSelectLot : public GUIDirectMessage
{
public:
	CmdSelectLot(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSelectLot : public GUICmdPacketBase
{
public:
	int		LotAutoCount;
	QString	LotID;
	QString	LotName;

	GUICmdSelectLot(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONSELECTLOT_H
