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

#ifndef REGISTLEARNINGDIALOG_H
#define REGISTLEARNINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class RegistLearningDialog;
}

class RegistLearningDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int		GlobalX1 ,GlobalY1;
	int		GlobalX2 ,GlobalY2;
	int		PointX,PointY;
    int     LibType,LibID;
public:

    explicit RegistLearningDialog(LayersBase *base ,int PointX,int PointY 
									,int GlobalX1 ,int GlobalY1 ,int GlobalX2 ,int GlobalY2
                                    ,int LibType,int LibID
                                    ,QWidget *parent = 0);
    ~RegistLearningDialog();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonNG_clicked();
    void on_pushButtonCancel_clicked();
    void on_horizontalSliderPriority_valueChanged(int value);
    void on_spinBoxPriority_valueChanged(int arg1);

private:
    Ui::RegistLearningDialog *ui;
};

#endif // REGISTLEARNINGDIALOG_H