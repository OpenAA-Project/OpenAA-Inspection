/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputBoolDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTBOOLDIALOG_H
#define INPUTBOOLDIALOG_H

#include <QDialog>

namespace Ui {
class InputBoolDialog;
}

class InputBoolDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputBoolDialog(bool d,QWidget *parent = 0);
    ~InputBoolDialog();

    bool	Value;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputBoolDialog *ui;
};

#endif // INPUTBOOLDIALOG_H
