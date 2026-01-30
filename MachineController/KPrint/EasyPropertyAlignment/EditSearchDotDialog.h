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

#ifndef EDITSEARCHDOTDIALOG_H
#define EDITSEARCHDOTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "PropertyAlignmentLargePacket.h"

namespace Ui {
class EditSearchDotDialog;
}

class EasyPropertyAlignmentForm;

class EditSearchDotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    EasyPropertyAlignmentForm   *Parent;
    bool        OnChanging;
public:
    explicit EditSearchDotDialog(EasyPropertyAlignmentForm *p,LayersBase *Base 
                                ,AlignmentLargePointList *L
                                ,QWidget *parent = nullptr);
    ~EditSearchDotDialog();

    AlignmentLargePointList   Data;  

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_spinBoxMoveDotX_valueChanged(int arg1);

    void on_spinBoxMoveDotY_valueChanged(int arg1);

    void on_spinBoxMoveDotX2_valueChanged(int arg1);

    void on_spinBoxMoveDotY2_valueChanged(int arg1);

    void on_doubleSpinBoxMoveDotXMM_valueChanged(double arg1);

    void on_doubleSpinBoxMoveDotYMM_valueChanged(double arg1);

    void on_doubleSpinBoxMoveDotX2MM_valueChanged(double arg1);

    void on_doubleSpinBoxMoveDotY2MM_valueChanged(double arg1);

private:
    Ui::EditSearchDotDialog *ui;
};

#endif // EDITSEARCHDOTDIALOG_H