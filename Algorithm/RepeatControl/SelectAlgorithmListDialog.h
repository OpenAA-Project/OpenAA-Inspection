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

#ifndef SELECTALGORITHMLISTDIALOG_H
#define SELECTALGORITHMLISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XRepeatControl.h"
#include "XDataComponent.h"

namespace Ui {
class SelectAlgorithmListDialog;
}

class RepeatControlBase;

class SelectAlgorithmListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
    RepeatControlBase *Parent;
public:
 	RootNameListContainer	OperationAlgorithmDim;

    explicit SelectAlgorithmListDialog(LayersBase *Base,RepeatControlBase *p ,QWidget *parent = 0);
    ~SelectAlgorithmListDialog();
    
private slots:
    void on_tableWidgetAlgorithmList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetOperationList_doubleClicked(const QModelIndex &index);
    void on_pushButtonGet_clicked();
    void on_pushButtonReturn_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectAlgorithmListDialog *ui;

    void    ShowSrcList(void);
    void    ShowDestList(void);
};

#endif // SELECTALGORITHMLISTDIALOG_H