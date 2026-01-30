/*
 * Copyright (C) 2022
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

#ifndef DEFINESIGNALDIALOG_H
#define DEFINESIGNALDIALOG_H

#include <QDialog>

namespace Ui {
class DefineSignalDialog;
}
class LEDControl16HioPanel;

class DefineSignalDialog : public QDialog
{
    Q_OBJECT
    LEDControl16HioPanel	*Panel;
public:
    explicit DefineSignalDialog(LEDControl16HioPanel *p,QWidget *parent = 0);
    ~DefineSignalDialog();
    
private slots:
    void on_pushButtonUpdate_clicked();

private:
    Ui::DefineSignalDialog *ui;
};

#endif // DEFINESIGNALDIALOG_H