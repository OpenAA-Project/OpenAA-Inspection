/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\OutSequenceShow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "OutSequenceShow.h"
#include "ui_OutSequenceShow.h"
#include "XSequence.h"
#include "ThreadSequence.h"
#include "XGeneralFunc.h"


OutSequenceShow::OutSequenceShow(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent,flags | Qt::WindowStaysOnTopHint),
    ui(new Ui::OutSequenceShow)
{
    ui->setupUi(this);

    QPalette P=palette();
    QColor	Color=*((QColor *)&seq->MessageCol);
    P.setColor(QPalette::Base,Color);
    setPalette(P);
    SetWidgetCenter(this);
}

OutSequenceShow::~OutSequenceShow()
{
    delete ui;
}

void	OutSequenceShow::ShowMessage(QString &msg)
{
    ui->MessageLabel->setText(msg);
}
