/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputIntDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTINTDIALOG_H
#define INPUTINTDIALOG_H

#include <QDialog>

namespace Ui {
class InputIntDialog;
}

class InputIntDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputIntDialog(int d,QWidget *parent = 0);
    ~InputIntDialog();

    int	Value;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputIntDialog *ui;
};

#endif // INPUTINTDIALOG_H
