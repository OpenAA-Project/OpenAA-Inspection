/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\InspectionPlayer\InspectionPlayer\IDatabaseMessageDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef IDATABASEMESSAGEDIALOG_H
#define IDATABASEMESSAGEDIALOG_H

#include <QDialog>
#include "ui_IDatabaseMessageDialog.h"

class IDatabaseMessageDialog : public QDialog
{
    Q_OBJECT

public:
    IDatabaseMessageDialog(QWidget *parent);
    ~IDatabaseMessageDialog();

	bool	SetMessages(QStringList &msg);

private:
    Ui::IDatabaseMessageDialogClass ui;
};

#endif // IDATABASEMESSAGEDIALOG_H
