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

#include "ExecuteBatchResource.h"
#include "MessageForm.h"
#include "ui_MessageForm.h"
#include "XGeneralFunc.h"

MessageForm::MessageForm(LayersBase *base, QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::MessageForm)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
	InstallOperationLog(this);
}

MessageForm::~MessageForm()
{
    delete ui;
}

void	MessageForm::SetMessage(const QString &Message)
{
	ui->label->setText(Message);
}
void MessageForm::on_pushButtonClose_clicked()
{
    close();
}