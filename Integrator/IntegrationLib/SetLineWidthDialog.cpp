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

#include "ServiceLibResource.h"
#include "SetLineWidthDialog.h"
#include "ui_SetLineWidthDialog.h"
#include "XRememberer.h"

SetLineWidthDialog::SetLineWidthDialog(LayersBase *base ,int _SlaveNo
                                        ,int _LineWidth,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,SlaveNo(_SlaveNo)
    ,ui(new Ui::SetLineWidthDialog)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
    ReEntrant   =false;
    LineWidth=_LineWidth;
    ui->spinBoxLineWidth    ->setValue(LineWidth);
}

SetLineWidthDialog::~SetLineWidthDialog()
{
    delete ui;
}

void SetLineWidthDialog::on_spinBoxLineWidth_valueChanged(int arg1)
{
    if(ReEntrant==true)
        return;
    ReEntrant=true;
	EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
        int PixelCount=ui->spinBoxLineWidth->value();
        ui->doubleSpinBoxLineWidthMM->setValue(m->TransformPixelToUnit(PixelCount));
    }
    ReEntrant=false;
}


void SetLineWidthDialog::on_doubleSpinBoxLineWidthMM_valueChanged(double arg1)
{
    if(ReEntrant==true)
        return;
    ReEntrant=true;
    EachMaster* m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
        double UnitCount=ui->doubleSpinBoxLineWidthMM->value();
        ui->spinBoxLineWidth->setValue(m->TransformUnitToPixel(UnitCount));
    }
    ReEntrant=false;
}


void SetLineWidthDialog::on_pushButtonOK_clicked()
{
    LineWidth=ui->spinBoxLineWidth->value();
    done(true);
}


void SetLineWidthDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
