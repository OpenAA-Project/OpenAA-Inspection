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

#ifndef SELECTSTARTDIALOG_H
#define SELECTSTARTDIALOG_H

#include <QDialog>
#include"XServiceForLayers.h"
#include <QModelIndex>

namespace Ui {
class SelectStartDialog;
}

class AutoGeneratorButtonForm;
class ListAutoGenerator;

class SelectStartDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    AutoGeneratorButtonForm *Parent;
public:
    ListAutoGenerator   *Selected;

    explicit SelectStartDialog(LayersBase *base,AutoGeneratorButtonForm *p ,QWidget *parent = nullptr);
    ~SelectStartDialog();

private slots:
    void on_tableWidgetStoredList_itemSelectionChanged();
    void on_tableWidgetStoredList_clicked(const QModelIndex &index);
    void on_lineEditCode_textChanged(const QString &arg1);
    void on_pushButtonGenerate_clicked();

    void on_tableWidgetStoredList_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectStartDialog *ui;

    void    ShowStoredGrid(void);
};

#endif // SELECTSTARTDIALOG_H