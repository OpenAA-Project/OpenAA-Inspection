/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceInput.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "OutSequenceInput.h"
#include "ui_OutSequenceInput.h"
#include "XSequence.h"
#include "ThreadSequence.h"
#include "XGeneralFunc.h"



OutSequenceInput::OutSequenceInput(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent,flags | Qt::WindowStaysOnTopHint),
    ui(new Ui::OutSequenceInput)
{
    ui->setupUi(this);

    ui->MessageLabel	->setText(MessageData);
    ui->EditInput	->setText(DefaultString);
    QPalette P=palette();
    QColor	Color=*((QColor *)&seq->MessageCol);
    P.setColor(QPalette::Base,Color);
    setPalette(P);
    OnAwake=false;
    SetWidgetCenter(this);
}

OutSequenceInput::~OutSequenceInput()
{
    delete ui;
}


void OutSequenceInput::on_YesButton_clicked()
{
    Ret=ui->EditInput->text();
    OKMode=true;
    close();
}

void OutSequenceInput::on_NoButton_clicked()
{
    DefaultString=ui->EditInput->text();
    OKMode=false;
    close();
}

void	OutSequenceInput::ShowMessage(QString &msg ,QString &defaultstring)
{
    MessageData		=msg;
    DefaultString	=defaultstring;
    ui->MessageLabel	->setText(MessageData);
    ui->EditInput	->setText(DefaultString);
}
void OutSequenceInput::showEvent ( QShowEvent * event )
{
   OnAwake=true;
}
void OutSequenceInput::closeEvent ( QCloseEvent * e )
{
    OnAwake=false;
}
