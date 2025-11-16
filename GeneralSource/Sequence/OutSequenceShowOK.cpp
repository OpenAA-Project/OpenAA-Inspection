/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceShowOK.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "OutSequenceShowOK.h"
#include "ui_OutSequenceShowOK.h"
#include "XSequence.h"
#include "ThreadSequence.h"
#include "XGeneralFunc.h"


class   ThreadSequence;
class   Sequence;
class	SeqControl;

OutSequenceShowOK::OutSequenceShowOK(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent,flags | Qt::WindowStaysOnTopHint),
    ui(new Ui::OutSequenceShowOK)
{
    ui->setupUi(this);
    QPalette P=palette();
    QColor	Color=*((QColor *)&seq->MessageCol);
    P.setColor(QPalette::Base,Color);
    setPalette(P);
    SetWidgetCenter(this);
}

OutSequenceShowOK::~OutSequenceShowOK()
{
    delete ui;
}


void OutSequenceShowOK::showEvent ( QShowEvent * event )
{
    ui->OKButton->setFocus();
}

void OutSequenceShowOK::on_OKButton_clicked()
{
    if(WRegID>=0){
        SeqParent->ReqWRegChange.Push(WRegID,1,ShowOnSeq,RegKindCode);
        }
}
void	OutSequenceShowOK::ShowMessage(QString &msg)
{
    ui->MessageLabel->setText(msg);
}
