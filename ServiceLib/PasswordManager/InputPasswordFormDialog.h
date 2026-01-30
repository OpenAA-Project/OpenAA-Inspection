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

#ifndef INPUTPASSWORDFORMDIALOG
#define INPUTPASSWORDFORMDIALOG

#include <QDialog>

namespace Ui {
class InputPasswordFormDialog;
}

class InputPasswordFormDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputPasswordFormDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::Widget);
    ~InputPasswordFormDialog();
    
	QString	GetLiedPassword(void);

public:
    Ui::InputPasswordFormDialog *ui;
};

#endif // INPUTPASSWORDFORMDIALOG