/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonTransferMasterData\ButtonTransferMasterData.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONTRANSFERMASTERDATA_H
#define BUTTONTRANSFERMASTERDATA_H

#include "buttontransfermasterdata_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonTransferMasterData : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	int32	SenderPort;
	QString	IPAddress;

	ButtonTransferMasterData(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONTRANSFERMASTERDATA_H
