/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\DockMasterPiece.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef DOCKMASTERPIECE_H
#define DOCKMASTERPIECE_H

#include "ui_DockMasterPiece.h"
#include "WindowBase.h"
#include <QLineEdit>

class DockMasterPiece : public WindowBase
{
//	Q_OBJECT

public:
	DockMasterPiece(const QString &title=/**/"", QWidget *parent = 0);
	~DockMasterPiece();

	void	SetTitle(bool Enabled);

	Ui::DockMasterPieceClass ui;
	QLineEdit	*leNGMasterPixTitle;

private:
//	Ui::DockMasterPieceClass ui;
};

#endif // DOCKMASTERPIECE_H
