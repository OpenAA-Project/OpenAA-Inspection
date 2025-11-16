/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceYesNo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "OutSequenceYesNo.h"
#include "ui_OutSequenceYesNo.h"
#include "XSequence.h"
#include "ThreadSequence.h"


OutSequenceYesNo::OutSequenceYesNo(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent,flags | Qt::WindowStaysOnTopHint),
    ui(new Ui::OutSequenceYesNo)
{
    ui->setupUi(this);
    QPalette P=palette();
    QColor	Color=*((QColor *)&seq->MessageCol);
    P.setColor(QPalette::Base,Color);
    setPalette(P);
    OnAwake=false;
}

OutSequenceYesNo::~OutSequenceYesNo()
{
    delete ui;
}

void OutSequenceYesNo::on_YesButton_clicked()
{
    OKMode=true;
    close();
}

void OutSequenceYesNo::on_NoButton_clicked()
{
    OKMode=false;
    close();
}

void	OutSequenceYesNo::ShowMessage(QString &msg)
{
    ui->MessageLabel->setText(msg);
}

void OutSequenceYesNo::showEvent ( QShowEvent * event )
{
    ui->YesButton->setFocus();
    OnAwake=true;
}
void OutSequenceYesNo::closeEvent ( QCloseEvent * e )
{
    OnAwake=false;
}
