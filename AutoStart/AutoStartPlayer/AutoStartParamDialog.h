/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\AutoStartParamDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef AUTOSTARTPARAMDIALOG_H
#define AUTOSTARTPARAMDIALOG_H

#include <QDialog>
#include "ui_AutoStartParamDialog.h"
#include "WEditParameterTab.h"
class	ParamBase;

class AutoStartParamDialog : public QDialog
{
	Q_OBJECT

public:
	AutoStartParamDialog(ParamBase *pbase,QWidget *parent = 0);
	~AutoStartParamDialog();

private:
	Ui::AutoStartParamDialogClass ui;
	WEditParameterTab	*WTab;
private slots:
	void on_CancelButton_clicked();
	void on_OKButton_clicked();
};

#endif // AUTOSTARTPARAMDIALOG_H
