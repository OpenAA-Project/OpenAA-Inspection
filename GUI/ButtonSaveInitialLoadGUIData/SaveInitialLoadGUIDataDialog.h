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

#ifndef SAVEINITIALLOADGUIDATADIALOG_H
#define SAVEINITIALLOADGUIDATADIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "ButtonSaveInitialLoadGUIData.h"

namespace Ui {
class SaveInitialLoadGUIDataDialog;
}

class	ButtonSaveInitialLoadGUIData;

class SaveInitialLoadGUIDataDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    ButtonSaveInitialLoadGUIData    *Parent;
    GUIDataListContainer	AllComponentsData;
    GUIDataListContainer	TmpData;

public:
    explicit SaveInitialLoadGUIDataDialog(ButtonSaveInitialLoadGUIData *p,QWidget *parent = nullptr);
    ~SaveInitialLoadGUIDataDialog();

private slots:
    void on_tableWidgetAllComponents_doubleClicked(const QModelIndex &index);
    void on_tableWidgetManagedComponents_doubleClicked(const QModelIndex &index);
    void on_pushButtonUseOne_clicked();
    void on_pushButtonReturnOne_clicked();
    void on_pushButtonUseAll_clicked();
    void on_pushButtonReturnAll_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSaveData_clicked();

private:
    Ui::SaveInitialLoadGUIDataDialog *ui;

	void ShowManagedTable(void);
};

#endif // SAVEINITIALLOADGUIDATADIALOG_H