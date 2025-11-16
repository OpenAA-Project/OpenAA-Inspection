/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\SelectCodecForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SELECTCODECFORM_H
#define SELECTCODECFORM_H

#include <QDialog>
#include "ui_SelectCodecForm.h"

class SelectCodecForm : public QDialog
{
	Q_OBJECT

public:
	SelectCodecForm(QWidget *parent);
	~SelectCodecForm();

private:
	Ui::SelectCodecFormClass ui;

private slots:
	void on_listWidgetCodec_doubleClicked(QModelIndex);
	void on_pushButtonSelect_clicked();
};

#endif // SELECTCODECFORM_H
