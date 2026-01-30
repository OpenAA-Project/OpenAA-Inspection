/*
 * Copyright (C) 2020
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

#ifndef ALERTMESSAGEDIALOG_H
#define ALERTMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class AlertMessageDialog;
}

class AlertMessageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AlertMessageDialog(QWidget *parent = 0);
    ~AlertMessageDialog();
    
private slots:
    void on_toolButtonYes_clicked();
    void on_toolButtonNo_clicked();

private:
    Ui::AlertMessageDialog *ui;
};

#endif // ALERTMESSAGEDIALOG_H