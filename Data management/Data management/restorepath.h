/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\restorepath.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef RESTOREPATH_H
#define RESTOREPATH_H

#include <QDialog>
#include "ui_restorepath.h"

namespace Ui {
    class RestorePath;
}

class RestorePath : public QDialog
{
    Q_OBJECT

public:
    explicit RestorePath(QStringList &PathList,QWidget *parent = 0);
    ~RestorePath();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::RestorePath *ui;
};

#endif // RESTOREPATH_H
