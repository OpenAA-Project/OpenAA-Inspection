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
