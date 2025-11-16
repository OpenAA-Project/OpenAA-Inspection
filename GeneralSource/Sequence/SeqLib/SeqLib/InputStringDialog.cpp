/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputStringDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "InputStringDialog.h"
#include "ui_InputStringDialog.h"

InputStringDialog::InputStringDialog(QString d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputStringDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(d);
}

InputStringDialog::~InputStringDialog()
{
    delete ui;
}

void InputStringDialog::on_pushButtonOK_clicked()
{
    Value=ui->lineEdit->text();
    done(true);
}

void InputStringDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
