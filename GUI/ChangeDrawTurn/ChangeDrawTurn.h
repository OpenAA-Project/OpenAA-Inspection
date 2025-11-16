/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ChangeDrawTurn\ChangeDrawTurn.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef CHANGEDRAWTURN_H
#define CHANGEDRAWTURN_H

#include <QListWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ChangeDrawTurn : public GUIFormBase
{
	Q_OBJECT

	QListWidget		List;	

public:
	ChangeDrawTurn(LayersBase *Base ,QWidget *parent = 0);
	~ChangeDrawTurn();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit(void)	override;
private:

private slots:
	void	ListClicked(const QModelIndex index);
	void	ResizeAction();
};
#endif // CHANGEDRAWTURN_H
