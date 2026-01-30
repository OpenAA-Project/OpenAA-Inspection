/*
 * Copyright (C) 2024
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

#include "EditTemplateRuleItemDialog.h"
#include "ui_EditTemplateRuleItemDialog.h"

EditTemplateRuleItemDialog::EditTemplateRuleItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTemplateRuleItemDialog)
{
    ui->setupUi(this);
}

EditTemplateRuleItemDialog::~EditTemplateRuleItemDialog()
{
    delete ui;
}

void EditTemplateRuleItemDialog::on_pushButtonCreate_clicked()
{

}


void EditTemplateRuleItemDialog::on_pushButtonUpdate_clicked()
{

}


void EditTemplateRuleItemDialog::on_pushButtonDelete_clicked()
{

}


void EditTemplateRuleItemDialog::on_pushButtonClose_clicked()
{

}


void EditTemplateRuleItemDialog::on_tableWidgetMemberList_doubleClicked(const QModelIndex &index)
{

}
