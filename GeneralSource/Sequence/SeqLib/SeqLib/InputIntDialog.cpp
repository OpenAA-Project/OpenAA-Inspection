/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputIntDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "InputIntDialog.h"
#include "ui_InputIntDialog.h"

InputIntDialog::InputIntDialog(int d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputIntDialog)
{
    ui->setupUi(this);
    ui->spinBox->setValue(d);
}

InputIntDialog::~InputIntDialog()
{
    delete ui;
}

void InputIntDialog::on_pushButtonOK_clicked()
{
    Value=ui->spinBox->value();
    done(true);
}

void InputIntDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
