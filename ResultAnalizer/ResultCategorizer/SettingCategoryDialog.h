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

#ifndef SETTINGCATEGORYDIALOG_H
#define SETTINGCATEGORYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "ResultCategorizer.h"

namespace Ui {
class SettingCategoryDialog;
}
class  ResultCategorizer;

class SettingCategoryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ResultCategorizer	*Parent;
	ResultCatShapeContainer	ResultCat;
public:
    explicit SettingCategoryDialog(LayersBase *base ,ResultCategorizer *p,QWidget *parent = 0);
    ~SettingCategoryDialog();
    
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonAddList_clicked();
    void on_pushButtonDelList_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonUpdate_clicked();

private:
    Ui::SettingCategoryDialog *ui;

	void	ShowList(void);
	void	LoadFromWindow(void);
};

#endif // SETTINGCATEGORYDIALOG_H