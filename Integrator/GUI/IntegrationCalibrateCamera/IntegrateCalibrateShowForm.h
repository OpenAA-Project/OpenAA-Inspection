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

#ifndef INTEGRATECALIBRATESHOWFORM_H
#define INTEGRATECALIBRATESHOWFORM_H

#include <QWidget>
#include <QTimer>
#include "XServiceForLayers.h"

namespace Ui {
class IntegrateCalibrateShowForm;
}
class	IntegrationCalibrateCamera;

class IntegrateCalibrateShowForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    IntegrationCalibrateCamera  *Parent;
    QTimer  TM;
    DWORD   StartTime;
public:
    explicit IntegrateCalibrateShowForm(LayersBase *Base 
                                        ,IntegrationCalibrateCamera *p
                                        ,QWidget *parent = nullptr);
    ~IntegrateCalibrateShowForm();

    void    Start(void);
private slots:
    void on_pushButtonStop_clicked();
    void    SlotTimeOut();
private:
    Ui::IntegrateCalibrateShowForm *ui;

    void    ExecuteCalibrate(void);
};

#endif // INTEGRATECALIBRATESHOWFORM_H