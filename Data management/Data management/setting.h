/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\setting.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include "ui_setting.h"

namespace Ui {
    class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
	void GetData();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
