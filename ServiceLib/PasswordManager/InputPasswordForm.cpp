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

#include "XTypeDef.h"
#include "InputPasswordFormDialog.h"
#include "ui_InputPasswordForm.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

InputPasswordFormDialog::InputPasswordFormDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent),
    ui(new Ui::InputPasswordFormDialog)
{
    ui->setupUi(this);

    QRegularExpression rx("^[a-z|A-Z|\\d]*$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->liedPassword->setValidator(validator);
}

InputPasswordFormDialog::~InputPasswordFormDialog()
{
    delete ui;
}

QString	InputPasswordFormDialog::GetLiedPassword(void)
{
	return ui->liedPassword->text();
}