/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputFloatDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "InputFloatDialog.h"
#include "ui_InputFloatDialog.h"

InputFloatDialog::InputFloatDialog(double d ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputFloatDialog)
{
    ui->setupUi(this);
    ui->doubleSpinBox->setValue(d);
}

InputFloatDialog::~InputFloatDialog()
{
    delete ui;
}

void InputFloatDialog::on_pushButtonOK_clicked()
{
    Value=ui->doubleSpinBox->value();
    done(true);
}

void InputFloatDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
