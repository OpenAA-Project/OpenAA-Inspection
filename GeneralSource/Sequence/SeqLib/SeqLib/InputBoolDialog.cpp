/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\InputBoolDialog.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "InputBoolDialog.h"
#include "ui_InputBoolDialog.h"

InputBoolDialog::InputBoolDialog(bool d,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputBoolDialog)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(d);
}

InputBoolDialog::~InputBoolDialog()
{
    delete ui;
}

void InputBoolDialog::on_pushButtonOK_clicked()
{
    Value=ui->checkBox->isChecked();
    done(true);
}

void InputBoolDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
