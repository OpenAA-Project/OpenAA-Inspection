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

#include "IntegrateCalibrateShowForm.h"
#include "ui_IntegrateCalibrateShowForm.h"
#include "XCriticalFunc.h"
#include "IntegrationCalibrateCamera.h"

IntegrateCalibrateShowForm::IntegrateCalibrateShowForm(LayersBase *Base 
                                                        ,IntegrationCalibrateCamera *p
                                                        ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::IntegrateCalibrateShowForm)
{
    ui->setupUi(this);

    ui->progressBar->setValue(0);
    StartTime   =::GetComputerMiliSec();

    TM.setSingleShot(false);
    TM.setInterval(300);
    connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
}

IntegrateCalibrateShowForm::~IntegrateCalibrateShowForm()
{
    delete ui;
}

void    IntegrateCalibrateShowForm::Start(void)
{
    ui->progressBar->setValue(0);
    StartTime   =::GetComputerMiliSec();
    TM.start();
}
void    IntegrateCalibrateShowForm::SlotTimeOut(void)
{
    DWORD   D=::GetComputerMiliSec();
    DWORD   s=(D-StartTime)/1000;
    if(ui->progressBar->maximum()<s){
        ui->progressBar->setValue(ui->progressBar->maximum());
    }
    else{
        ui->progressBar->setValue(s);
    }
    if(ui->progressBar->maximum()<=ui->progressBar->value()){
        ExecuteCalibrate();
        TM.stop();
        close();
    }
}

void IntegrateCalibrateShowForm::on_pushButtonStop_clicked()
{
    TM.stop();
    close();
}

void IntegrateCalibrateShowForm::ExecuteCalibrate(void)
{
    Parent->SlotClicked();
}