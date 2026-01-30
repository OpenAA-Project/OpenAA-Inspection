/*
 * Copyright (C) 2025
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

#include "CartonMenuResource.h"
#include "InputBeltSpeedDialog.h"
#include "ui_InputBeltSpeedDialog.h"
#include "XParamGlobal.h"
#include "XIntegrationBase.h"
#include "CartonMenuForm.h"
#include "InputPanelDialog.h"
#include "XRememberer.h"

InputBeltSpeedDialog::InputBeltSpeedDialog(LayersBase *Base ,CartonMenuForm	*p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),Parent(p),
    ui(new Ui::InputBeltSpeedDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
    TimeOutValue    =GetParamGlobal()->MaxInspectMilisec;
    ui->spinBoxBeltVelocity	->setValue(ControlRememberer::GetInt(ui->spinBoxBeltVelocity));
}

InputBeltSpeedDialog::~InputBeltSpeedDialog()
{
    delete ui;
}

void InputBeltSpeedDialog::on_PushButtonOK_clicked()
{
    TimeOutValue=GetTimeOutValue();
    done(true);
}

void InputBeltSpeedDialog::on_spinBoxBeltVelocity_valueChanged(int arg1)
{
    int Ret=GetTimeOutValue();
    ui->labelTimeout->setText(QString::number(Ret)+QString(LangSolver.GetString(InputBeltSpeedDialog_LS,LID_3)/*" ms"*/));
}

void InputBeltSpeedDialog::on_pushButtonInputPanelVelocity_clicked()
{
    InputPanelDialog	D(IPD_Number ,QString::number(ui->spinBoxBeltVelocity->value()));
    if(D.exec()==(bool)true){
        QString	str=D.GetResult();
        bool    ok;
        int V=str.toInt(&ok);
        if(ok==true){
            ui->spinBoxBeltVelocity->setValue(V);
        }
    }
}
int InputBeltSpeedDialog::GetTimeOutValue(void)
{
    int V=ui->spinBoxBeltVelocity->value();
    if(V!=0){
        IntegrationCommonData   *D=GetLayersBase()->GetIntegrationBasePointer()->GetCommonData();
        if(D!=NULL){
            int Ret=(Parent->Param.SystemBeltLength-(D->CommonSizeY+D->AddedY))*60.0/V + Parent->Param.AddedTimeoutMilisec;
            return Ret;
        }
    }
    return 0;
}