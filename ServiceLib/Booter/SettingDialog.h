/*
 * Copyright (C) 2014
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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XBooter.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingDialog(BooterParameter &param ,QWidget *parent = 0);
    ~SettingDialog();

    BooterParameter		BooterData;

private slots:
    void on_pushButtonAddIPAddress_clicked();
    void on_pushButtonDelIPAddress_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidgetBeforeBooter_doubleClicked(const QModelIndex &index);
    void on_tableWidgetAfterBooter_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddProgBefore_clicked();
    void on_pushButtonDelProgBefore_clicked();
    void on_pushButtonAddProgAfter_clicked();
    void on_pushButtonDelProgAfter_clicked();

private:
    Ui::SettingDialog *ui;

	void	ShowBeforeList(void);
	void	ShowAfterList(void);
};

#endif // SETTINGDIALOG_H