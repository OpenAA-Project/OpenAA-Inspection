/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\DockNGPiece.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef DOCKNGPIECE_H
#define DOCKNGPIECE_H

#include "ui_DockNGPiece.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockNGPiece : public WindowBase
{
//	Q_OBJECT

public:
	DockNGPiece(const QString &title=/**/"", QWidget *parent = 0);
	~DockNGPiece();

	void	SetTitle(bool Enabled);

	Ui::DockNGPieceClass ui;
	QLineEdit	*leNGInspectionPixTitle;

private:
//	Ui::DockNGPieceClass ui;
};

#endif // DOCKNGPIECE_H
