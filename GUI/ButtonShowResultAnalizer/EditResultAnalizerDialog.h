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

#ifndef EDITRESULTANALIZERDIALOG_H
#define EDITRESULTANALIZERDIALOG_H

#include <QDialog>
#include <QTableView>
#include "XServiceForLayers.h"

namespace Ui {
class EditResultAnalizerDialog;
}

class EditResultAnalizerDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditResultAnalizerDialog(LayersBase *Base ,QWidget *parent = 0);
    ~EditResultAnalizerDialog();
    
private slots:
    void on_listWidgetResultAnalizerDLL_doubleClicked(const QModelIndex &index);
    void on_pushButtonFromDLL_clicked();
    void on_pushButtonToDLL_clicked();
    void on_tableWidgetResultAnalizerItemBase_doubleClicked(const QModelIndex &index);
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonUpdateDefault_clicked();

private:
    Ui::EditResultAnalizerDialog *ui;

	void	ShowList(void);
};

#endif // EDITRESULTANALIZERDIALOG_H