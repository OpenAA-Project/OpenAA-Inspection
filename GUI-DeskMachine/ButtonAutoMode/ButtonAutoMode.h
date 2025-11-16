/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAutoMode\ButtonAutoMode.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONAUTOMODE_H
#define BUTTONAUTOMODE_H

#include "buttonautomode_global.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButtonColored.h"
//#include "mtImageButtonColored.h"

class	ButtonAutoMode : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButtonColored	Button;
//	mtImageButtonColored	Button;

public:
	QColor	PushedColor;
	bool	IsNecessaryLot;

	ButtonAutoMode(LayersBase *Base ,QWidget *parent);
	~ButtonAutoMode(void);
	
	virtual void	Prepare(void)	override;
	QTranslator Translator;

public slots:
	void	SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

#endif // BUTTONAUTOMODE_H
