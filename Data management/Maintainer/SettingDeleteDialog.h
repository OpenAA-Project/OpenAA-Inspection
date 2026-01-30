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

#ifndef SETTINGDELETEDIALOG_H
#define SETTINGDELETEDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class SettingDeleteDialog;
}

class Maintainer;

class SettingDeleteDialog : public QDialog
{
    Q_OBJECT
    Maintainer	*Parent;
public:
    explicit SettingDeleteDialog(Maintainer *p ,QWidget *parent = 0);
    ~SettingDeleteDialog();
    
private slots:
    void on_checkBoxImageKeepDays_clicked();
    void on_checkBoxImageKeepMonths_clicked();
    void on_listWidgetImageFileNames_doubleClicked(const QModelIndex &index);
    void on_pushButtonImageAddFileName_clicked();
    void on_pushButtonImageSubLine_clicked();
    void on_pushButtonImageAddFolderName_clicked();
    void on_pushButtonImageSubFolder_clicked();

    void on_pushButtonOK_clicked();

private:
    Ui::SettingDeleteDialog *ui;
};

#endif // SETTINGDELETEDIALOG_H