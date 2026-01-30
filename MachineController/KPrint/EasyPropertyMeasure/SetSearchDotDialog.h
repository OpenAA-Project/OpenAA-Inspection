/*
 * Copyright (C) 2024
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

#ifndef SETSEARCHDOTDIALOG_H
#define SETSEARCHDOTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SetSearchDotDialog;
}
class EasyPropertyMeasureForm;

class SetSearchDotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    EasyPropertyMeasureForm *Parent;
    int                     Page;
    bool    OnChanging;
public:
    explicit SetSearchDotDialog(LayersBase *Base ,EasyPropertyMeasureForm *p
	                            ,int SearchDot ,int Page
                                ,QWidget *parent = 0);
    ~SetSearchDotDialog();
    
    int    RetSearchDot;

private slots:
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotMM_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonOKAll_clicked();

private:
    Ui::SetSearchDotDialog *ui;
};

#endif // SETSEARCHDOTDIALOG_H