/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonTransferRequireMasterData\ButtonTransferRequireMasterData.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONTRANSFERREQUIREMASTERDATA_H
#define BUTTONTRANSFERREQUIREMASTERDATA_H

#include "buttontransferrequiremasterdata_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralWidget.h"

class	ButtonTransferRequireMasterData : public GUIFormBase
{
	Q_OBJECT

	QPushButtonWithRightClick	Button;

public:
	QString	Msg;

	ButtonTransferRequireMasterData(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotRightClicked();
	void	SlotResetFixedHost();
	void	SlotEditHost();
};

#endif // BUTTONTRANSFERREQUIREMASTERDATA_H
