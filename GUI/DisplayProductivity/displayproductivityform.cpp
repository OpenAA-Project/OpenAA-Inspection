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

#include "displayproductivityform.h"
#include "ui_displayproductivityform.h"
#include "XCriticalFunc.h"
#include "swap.h"

DisplayProductivityForm::DisplayProductivityForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::DisplayProductivityForm)
{
    ui->setupUi(this);
    CountInspected=0;
    WPoint=0;
    CountType=/**/"PerMinute";
}

DisplayProductivityForm::~DisplayProductivityForm()
{
    delete ui;
}

void	DisplayProductivityForm::Prepare(void)
{
    if(CountType==/**/"PerMinute"){
        ui->label->setText(ui->label->text()+QString(/**/"/m"));
    }
    else
    if(CountType==/**/"PerHour"){
        ui->label->setText(ui->label->text()+QString(/**/"/h"));
    }
}
void	DisplayProductivityForm::ShowInPlayer(int64 shownInspectionID)
{
    DWORD   CurrentTime=::GetComputerMiliSec();
    int N=sizeof(InspectedTimeMilisec)/sizeof(InspectedTimeMilisec[0]);
    InspectedTimeMilisec[WPoint]=CurrentTime;
    CountInspected++;
    if(CountInspected>=4){
        DWORD   LastTime    =CurrentTime;
        int64   AddedTime=0;
        int     AddedCount=0;
        for(int i=1;i<N;i++){
            int t=WPoint-i;
            if(t<0)
                t=N-1;
            DWORD   Span=LastTime-InspectedTimeMilisec[t];
            AddedTime+=Span;
            AddedCount++;
            LastTime=InspectedTimeMilisec[t];
        }
        double  InspectionMilisec=(double)AddedTime/(double)AddedCount;
        if(CountType==/**/"PerMinute"){
            ui->labelInspectedCount->setText(QString::number(60.0/InspectionMilisec*1000.0,'f',1));
        }
        else
        if(CountType==/**/"PerHour"){
            ui->labelInspectedCount->setText(QString::number(3600.0/InspectionMilisec*1000.0,'f',1));
        }
    }
    WPoint++;
    if(WPoint>=N)
        WPoint=0;
    CountInspected++;
}