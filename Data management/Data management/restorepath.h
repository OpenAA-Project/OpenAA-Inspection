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


#ifndef RESTOREPATH_H
#define RESTOREPATH_H

#include <QDialog>
#include "ui_restorepath.h"

namespace Ui {
    class RestorePath;
}

class RestorePath : public QDialog
{
    Q_OBJECT

public:
    explicit RestorePath(QStringList &PathList,QWidget *parent = 0);
    ~RestorePath();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::RestorePath *ui;
};

#endif // RESTOREPATH_H