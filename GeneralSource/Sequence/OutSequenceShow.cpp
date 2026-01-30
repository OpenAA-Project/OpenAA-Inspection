/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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