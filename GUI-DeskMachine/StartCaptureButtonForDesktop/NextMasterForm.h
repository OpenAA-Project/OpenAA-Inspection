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

class NextMasterForm : public QDialog
{
	Q_OBJECT

	int LanguageCode;

public:
	NextMasterForm(QWidget *parent=0);
	~NextMasterForm();

	void SetLanguageCode	(int LCode);
	void SetNextMasterFlag	(bool Flag);
	void SetMasterCounter	(int Count,bool Enable);

//private:
	Ui::NextMasterFormClass ui;

private slots:
	void on_pushButtonStartNext_clicked();
	void on_pushButtonFinish_clicked();
};

#endif // NEXTMASTERFORM_H
