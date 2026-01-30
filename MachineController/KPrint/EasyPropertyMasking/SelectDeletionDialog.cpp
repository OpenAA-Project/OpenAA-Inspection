/*
 * Copyright (C) 2025
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

#include "EasyPropertyMaskingResource.h"
#include "SelectDeletionDialog.h"
#include "ui_SelectDeletionDialog.h"

SelectDeletionDialog::SelectDeletionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDeletionDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	DeleteManualItems	=false;
	DeleteCADItems		=false;
}

SelectDeletionDialog::~SelectDeletionDialog()
{
    delete ui;
}

void SelectDeletionDialog::on_toolButtonOK_clicked()
{
	DeleteManualItems	=ui->toolButtonDeleteManualItems->isChecked();
	DeleteCADItems		=ui->toolButtonDeleteCADItems	->isChecked();
	done(true);
}

void SelectDeletionDialog::on_toolButtonCancel_clicked()
{
	done(false);
}