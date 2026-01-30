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

#include "EasyPropertyAlignmentResource.h"
#include "EditSearchDotDialog.h"
#include "ui_EditSearchDotDialog.h"
#include "EasyPropertyAlignmentForm.h"
#include "XIntegrationBase.h"

EditSearchDotDialog::EditSearchDotDialog(EasyPropertyAlignmentForm *p,LayersBase *Base 
                                ,AlignmentLargePointList *L
                                ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),Parent(p),
    ui(new Ui::EditSearchDotDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    OnChanging=true;
    Data=*L;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->spinBoxMoveDotX ->setValue(Data.MoveDotX);
        ui->spinBoxMoveDotY ->setValue(Data.MoveDotY);
        ui->spinBoxMoveDotX2->setValue(Data.MoveDotX2);
        ui->spinBoxMoveDotY2->setValue(Data.MoveDotY2);
        ui->checkBoxJudgeWithBrDif  ->setChecked(Data.JudgeWithBrDif);
        ui->checkBoxCharacterMode   ->setChecked(Data.CharacterMode);

        ui->doubleSpinBoxMoveDotXMM   ->setValue(m->TransformPixelToUnit(Data.MoveDotX));
        ui->doubleSpinBoxMoveDotYMM   ->setValue(m->TransformPixelToUnit(Data.MoveDotY));
        ui->doubleSpinBoxMoveDotX2MM  ->setValue(m->TransformPixelToUnit(Data.MoveDotX2));
        ui->doubleSpinBoxMoveDotY2MM  ->setValue(m->TransformPixelToUnit(Data.MoveDotY2));
        ui->labelUnit1->setText(m->GetUnitStr());
        ui->labelUnit2->setText(m->GetUnitStr());
        ui->labelUnit3->setText(m->GetUnitStr());
        ui->labelUnit4->setText(m->GetUnitStr());
    }
    OnChanging=false;
}

EditSearchDotDialog::~EditSearchDotDialog()
{
    delete ui;
}

void EditSearchDotDialog::on_pushButtonOK_clicked()
{
    Data.MoveDotX  =ui->spinBoxMoveDotX ->value();
    Data.MoveDotY  =ui->spinBoxMoveDotY ->value();
    Data.MoveDotX2 =ui->spinBoxMoveDotX2->value();
    Data.MoveDotY2 =ui->spinBoxMoveDotY2->value();
    Data.JudgeWithBrDif =ui->checkBoxJudgeWithBrDif  ->isChecked();
    Data.CharacterMode  =ui->checkBoxCharacterMode   ->isChecked();

    done(true);
}


void EditSearchDotDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void EditSearchDotDialog::on_spinBoxMoveDotX_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->doubleSpinBoxMoveDotXMM->setValue(m->TransformPixelToUnit(ui->spinBoxMoveDotX->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_spinBoxMoveDotY_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->doubleSpinBoxMoveDotYMM->setValue(m->TransformPixelToUnit(ui->spinBoxMoveDotY->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_spinBoxMoveDotX2_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->doubleSpinBoxMoveDotX2MM->setValue(m->TransformPixelToUnit(ui->spinBoxMoveDotX2->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_spinBoxMoveDotY2_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->doubleSpinBoxMoveDotY2MM->setValue(m->TransformPixelToUnit(ui->spinBoxMoveDotY2->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_doubleSpinBoxMoveDotXMM_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->spinBoxMoveDotX   ->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMoveDotXMM->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_doubleSpinBoxMoveDotYMM_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->spinBoxMoveDotY   ->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMoveDotYMM->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_doubleSpinBoxMoveDotX2MM_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->spinBoxMoveDotX2->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMoveDotX2MM->value()));
    }
    OnChanging=false;
}


void EditSearchDotDialog::on_doubleSpinBoxMoveDotY2MM_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->SlaveNo);
	if(m!=NULL){
        ui->spinBoxMoveDotY2->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMoveDotY2MM->value()));
    }
    OnChanging=false;
}
