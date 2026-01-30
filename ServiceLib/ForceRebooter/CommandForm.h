/*
 * Copyright (C) 2024
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

#ifndef COMMANDFORM_H
#define COMMANDFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class CommandForm;
}

class CommandForm : public QWidget
{
    Q_OBJECT

    int     Cmd;
    int     OwnCmd;
    QTimer  TM;

public:
    explicit CommandForm(int cmd ,int OwnCmd,QWidget *parent = 0);
    ~CommandForm();
    
private:
    Ui::CommandForm *ui;

private slots:
    void    SlotTimeOut();
};

#endif // COMMANDFORM_H