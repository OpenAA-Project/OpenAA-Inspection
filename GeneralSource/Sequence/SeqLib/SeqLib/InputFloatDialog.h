/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputFloatDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTFLOATDIALOG_H
#define INPUTFLOATDIALOG_H

#include <QDialog>

namespace Ui {
class InputFloatDialog;
}

class InputFloatDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputFloatDialog(double d ,QWidget *parent = 0);
    ~InputFloatDialog();

    double	Value;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputFloatDialog *ui;
};

#endif // INPUTFLOATDIALOG_H
