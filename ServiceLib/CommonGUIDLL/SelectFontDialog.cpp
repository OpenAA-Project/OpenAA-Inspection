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

#include "CommonGUIDLLResource.h"
#include "SelectFontDialog.h"
#include "ui_SelectFontDialog.h"

SelectFontDialog::SelectFontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFontDialog)
{
    ui->setupUi(this);
}
SelectFontDialog::SelectFontDialog(const QFont & initial, QWidget *parent)
 :
    QDialog(parent),
    ui(new Ui::SelectFontDialog)
{
    ui->setupUi(this);
	CurrentFont=initial;
}

SelectFontDialog::~SelectFontDialog()
{
    delete ui;
}

void SelectFontDialog::on_listWidgetFont_currentRowChanged(int currentRow)
{

}

void SelectFontDialog::on_listWidgetStyle_currentRowChanged(int currentRow)
{

}

void SelectFontDialog::on_listWidgetSize_currentRowChanged(int currentRow)
{

}

void SelectFontDialog::on_pushButtonOK_clicked()
{

}

void SelectFontDialog::on_pushButtonCancel_clicked()
{

}

void SelectFontDialog::showEvent ( QShowEvent * event )
{

}

QFont	SelectFontDialog::currentFont()const
{
	return CurrentFont;
}
QFont	SelectFontDialog::selectedFont()const
{
	return CurrentFont;
}
void	SelectFontDialog::setCurrentFont(const QFont & initial)
{
	CurrentFont=initial;
	showEvent(NULL);
}