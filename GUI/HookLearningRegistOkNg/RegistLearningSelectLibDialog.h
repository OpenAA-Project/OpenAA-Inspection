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

#ifndef REGISTLEARNINGSELECTLIBDIALOG_H
#define REGISTLEARNINGSELECTLIBDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XHookRegistCommon.h"

namespace Ui {
class RegistLearningSelectLibDialog;
}

class RegistLearningSelectLibDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int		GlobalX1 ,GlobalY1;
	int		GlobalX2 ,GlobalY2;
	int		PointX,PointY;
    LibIDListWithResultContainer    LibContainer;

public:
    explicit RegistLearningSelectLibDialog(LayersBase *base ,int PointX,int PointY 
									,int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
                                    ,LibIDListWithResultContainer &Container
                                    ,QWidget *parent = nullptr);
    ~RegistLearningSelectLibDialog();

    LibIDListWithResultContainer    SelectedLibContainer;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonNG_clicked();
    void on_horizontalSliderPriority_valueChanged(int value);
    void on_spinBoxPriority_valueChanged(int arg1);
    void on_pushButtonCancel_clicked();

private:
    Ui::RegistLearningSelectLibDialog *ui;
};

#endif // REGISTLEARNINGSELECTLIBDIALOG_H