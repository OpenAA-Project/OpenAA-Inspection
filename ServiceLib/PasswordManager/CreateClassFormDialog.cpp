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
#include "CreateClassFormDialog.h"
#include "ui_CreateClassForm.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#if	QT_VERSION<0x050000
#include <QTextCodec>
#endif

CreateClassFormDialog::CreateClassFormDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent,f),
    ui(new Ui::CreateClassFormDialog)
{
#if	QT_VERSION<0x050000
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#endif
    ui->setupUi(this);

    QRegularExpression n_rx("[^;@]*");
    QRegularExpressionValidator *n_validator = new QRegularExpressionValidator(n_rx, this);
    ui->liedClassName->setValidator(n_validator);

    QRegularExpression p_rx("[a-zA-Z0-9]*");
    QRegularExpressionValidator *p_validator = new QRegularExpressionValidator(p_rx, this);
    ui->liedPassword->setValidator(p_validator);

    ui->okButton->setEnabled(false);

    bool ch;
    ch = QObject::connect(ui->liedClassName, SIGNAL(textChanged(const QString&)), this, SLOT(checkEnableOk()));
    ch = QObject::connect(ui->liedPassword, SIGNAL(textChanged(const QString&)), this, SLOT(checkEnableOk()));

    if(!ch)qDebug("false");
}

CreateClassFormDialog::~CreateClassFormDialog()
{
    delete ui;
}


void CreateClassFormDialog::checkEnableOk()
{
    if(!ui->liedClassName->text().isEmpty() && !ui->liedPassword->text().isEmpty())
        ui->okButton->setEnabled(true);
    else
        ui->okButton->setEnabled(false);
}

QString	CreateClassFormDialog::GetLiedClassName(void)
{
	return ui->liedClassName->text();
}

QString	CreateClassFormDialog::GetLiedPassword(void)
{
	return ui->liedPassword->text();
}