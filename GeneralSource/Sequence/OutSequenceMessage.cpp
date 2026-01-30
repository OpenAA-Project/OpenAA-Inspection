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