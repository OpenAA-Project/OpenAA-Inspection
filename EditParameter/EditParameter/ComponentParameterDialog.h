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

#ifndef COMPONENTPARAMETERDIALOG_H
#define COMPONENTPARAMETERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class ComponentParameterDialog;
}
class ParamBase;
class WEditParameterTab;

class ComponentParameterDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    ParamBase   *Param;
    WEditParameterTab	*WTabAlgorithm;
public:
    explicit ComponentParameterDialog(ParamBase	*P,LayersBase *Base,QWidget *parent = nullptr);
    ~ComponentParameterDialog();

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::ComponentParameterDialog *ui;
};

#endif // COMPONENTPARAMETERDIALOG_H