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

#ifndef SHOWNGMESSAGEFORM_H
#define SHOWNGMESSAGEFORM_H

#include <QWidget>

namespace Ui {
class ShowNGMessageForm;
}

class ShowNGMessageForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShowNGMessageForm(QWidget *parent = nullptr);
    ~ShowNGMessageForm();

    void    SetMessage(const QString &msg);
private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::ShowNGMessageForm *ui;
};

#endif // SHOWNGMESSAGEFORM_H