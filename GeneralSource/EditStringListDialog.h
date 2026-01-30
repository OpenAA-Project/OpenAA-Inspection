/*
 * Copyright (C) 2017
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

#ifndef EDITSTRINGLISTDIALOG_H
#define EDITSTRINGLISTDIALOG_H

#include <QDialog>
#include <QStringList>
#include "XServiceForLayers.h"

namespace Ui {
class EditStringListDialog;
}

class EditStringListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStringListDialog(const QStringList &str,QWidget *parent = 0);
    ~EditStringListDialog();
	
	QStringList	Str;

private slots:
    void on_buttonBox_accepted();
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();

private:
    Ui::EditStringListDialog *ui;
};

#endif // EDITSTRINGLISTDIALOG_H