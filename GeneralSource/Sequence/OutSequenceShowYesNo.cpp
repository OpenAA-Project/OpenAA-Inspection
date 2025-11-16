/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceShowYesNo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "OutSequenceShowYesNo.h"
#include "ui_OutSequenceShowYesNo.h"
#include "XSequence.h"
#include "ThreadSequence.h"
#include "XGeneralFunc.h"


OutSequenceShowYesNo::OutSequenceShowYesNo(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent,flags | Qt::WindowStaysOnTopHint),
    ui(new Ui::OutSequenceShowYesNo)
{
    ui->setupUi(this);
    QPalette P=palette();
    QColor	Color=*((QColor *)&seq->MessageCol);
    P.setColor(QPalette::Base,Color);
    setPalette(P);
    SetWidgetCenter(this);
}

OutSequenceShowYesNo::~OutSequenceShowYesNo()
{
    delete ui;
}


void OutSequenceShowYesNo::showEvent ( QShowEvent * event )
{
    ui->YesButton->setFocus();
}

void OutSequenceShowYesNo::on_YesButton_clicked()
{
    if(WRegID>=0){
        SeqParent->ReqWRegChange.Push(WRegID,2,ShowOnSeq,RegKindCode);
        }
}

void OutSequenceShowYesNo::on_NoButton_clicked()
{
    if(WRegID>=0){
        SeqParent->ReqWRegChange.Push(WRegID,3,ShowOnSeq,RegKindCode);
        }
}
void	OutSequenceShowYesNo::ShowMessage(QString &msg)
{
    ui->MessageLabel->setText(msg);
}

