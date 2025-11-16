/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceMessage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "OutSequenceMessage.h"
#include "ui_OutSequenceMessage.h"
#include "XSequence.h"
#include "ThreadSequence.h"
#include "XGeneralFunc.h"


OutSequenceMessage::OutSequenceMessage(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent,flags | Qt::WindowStaysOnTopHint),
    ui(new Ui::OutSequenceMessage)
{
    ui->setupUi(this);
    QPalette P=palette();
    QColor	Color=*((QColor *)&seq->MessageCol);
    P.setColor(QPalette::Base,Color);
    setPalette(P);
    OnAwake=false;
    SetWidgetCenter(this);
}

OutSequenceMessage::~OutSequenceMessage()
{
    delete ui;
}

void OutSequenceMessage::on_OKButton_clicked()
{
    close();
}

void	OutSequenceMessage::ShowMessage(QString &msg)
{
    ui->MessageLabel->setText(msg);
}

void OutSequenceMessage::showEvent ( QShowEvent * event )
{
    ui->OKButton->setFocus();
    OnAwake=true;
}
void OutSequenceMessage::closeEvent ( QCloseEvent * e )
{
    OnAwake=false;
}
