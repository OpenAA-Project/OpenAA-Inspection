/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DesktopMachineMenu\NextMasterForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef NEXTMASTERFORM_H
#define NEXTMASTERFORM_H

#include <QDialog>
#include "ui_NextMasterForm.h"
#include "XServiceForLayers.h"

class NextMasterForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	NextMasterForm(LayersBase *base, QWidget *parent);
	~NextMasterForm();

private:
	Ui::NextMasterFormClass ui;

private slots:
	void on_pushButtonFinish_clicked();
	void on_pushButtonStartNext_clicked();
};

#endif // NEXTMASTERFORM_H
