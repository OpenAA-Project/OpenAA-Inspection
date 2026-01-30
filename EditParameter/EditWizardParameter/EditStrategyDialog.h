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

#ifndef EDITSTRATEGYDIALOG_H
#define EDITSTRATEGYDIALOG_H

#include <QDialog>

namespace Ui {
class EditStrategyDialog;
}

class EditStrategyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStrategyDialog(QWidget *parent = 0);
    ~EditStrategyDialog();

private:
    Ui::EditStrategyDialog *ui;
};

#endif // EDITSTRATEGYDIALOG_H