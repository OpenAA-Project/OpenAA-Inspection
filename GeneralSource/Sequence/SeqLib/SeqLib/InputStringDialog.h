/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputStringDialog.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef INPUTSTRINGDIALOG_H
#define INPUTSTRINGDIALOG_H

#include <QDialog>

namespace Ui {
class InputStringDialog;
}

class InputStringDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputStringDialog(QString d, QWidget *parent = 0);
    ~InputStringDialog();

    QString	Value;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputStringDialog *ui;
};

#endif // INPUTSTRINGDIALOG_H
