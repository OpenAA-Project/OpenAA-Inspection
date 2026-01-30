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

#ifndef SELECTCAMERADIALOG_H
#define SELECTCAMERADIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
namespace Ui {
class SelectCameraDialog;
}

class SelectCameraDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	int VendoredProductIDList[100];
	int CountOfCam;
public:
    explicit SelectCameraDialog(int VendoredProductIDList[] ,int CountOfCam ,LayersBase *base,QWidget *parent = 0);
    ~SelectCameraDialog();
    
	int	SelectedNo;

private slots:
    void on_listWidgetCameraList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();

private:
    Ui::SelectCameraDialog *ui;
};

#endif // SELECTCAMERADIALOG_H