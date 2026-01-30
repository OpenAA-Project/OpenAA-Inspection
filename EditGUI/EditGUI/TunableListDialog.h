/*
 * Copyright (C) 2021
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

#ifndef TUNABLELISTDIALOG_H
#define TUNABLELISTDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class TunableListDialog;
}

class TunableListDialog : public QDialog
{
    Q_OBJECT
    
public:
    QStringList &MList;

    explicit TunableListDialog(QStringList &mList,QWidget *parent = 0);
    ~TunableListDialog();
    
private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::TunableListDialog *ui;

    void ShowList(void);
};

#endif // TUNABLELISTDIALOG_H