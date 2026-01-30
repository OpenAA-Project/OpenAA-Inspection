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

#include "PropertyResultBinderFormResource.h"
#include "RuleOperationDialog.h"
#include "ui_RuleOperationDialog.h"

RuleOperationDialog::RuleOperationDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RuleOperationDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

RuleOperationDialog::~RuleOperationDialog()
{
    delete ui;
}
void	RuleOperationDialog::Initial(RuleOfBinderBase *rule)
{
	ui->lineEditName	->setText(rule->Name);
	ui->lineEditRemark	->setText(rule->Remark);
	ui->checkBoxConclusion	->setChecked(rule->Conclusion);
}
void RuleOperationDialog::on_pushButtonOK_clicked()
{
	RuleName	=ui->lineEditName	->text();
	RuleRemark	=ui->lineEditRemark	->text();
	Conclusion	=ui->checkBoxConclusion	->isChecked();
	done(true);
}

void RuleOperationDialog::on_pushButtonCancel_clicked()
{
	done(false);
}