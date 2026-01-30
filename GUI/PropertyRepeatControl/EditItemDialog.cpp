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

#include "EditItemDialog.h"
#include "ui_EditItemDialog.h"
#include "XRepeatControl.h"

EditItemDialog::EditItemDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),
    ServiceForLayers(base),
    ui(new Ui::EditItemDialog)
{
    ui->setupUi(this);

    RepeatCount    =50;
    MeshSize       =100;
    SequenceOffset =0;
    GatherAllPhase =true;

    RepeatControlBase	*ABase=GetRepeatControlBase();

    ui->spinBoxRepeatCount      ->setValue  (ABase->DefaultRepeatCount  );
    ui->spinBoxMeshSize         ->setValue  (ABase->WholeMeshSize       );
    ui->spinBoxSequenceOffset   ->setValue  (ABase->WholeSequenceOffset );
    ui->checkBoxGatherAllPhase  ->setChecked(ABase->WholeGatherAllPhase );
}

EditItemDialog::~EditItemDialog()
{
    delete ui;
}

void	EditItemDialog::Initial(void)
{
    ui->spinBoxRepeatCount      ->setValue  (RepeatCount    );
    ui->spinBoxMeshSize         ->setValue  (MeshSize       );
    ui->spinBoxSequenceOffset   ->setValue  (SequenceOffset );
    ui->checkBoxGatherAllPhase  ->setChecked(GatherAllPhase );
}
RepeatControlBase	*EditItemDialog::GetRepeatControlBase(void)
{
	return (RepeatControlBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RepeatControl");
}


void EditItemDialog::on_pushButtonOK_clicked()
{
    RepeatCount    =ui->spinBoxRepeatCount      ->value  ();
    MeshSize       =ui->spinBoxMeshSize         ->value  ();
    SequenceOffset =ui->spinBoxSequenceOffset   ->value  ();
    GatherAllPhase =ui->checkBoxGatherAllPhase  ->isChecked();
    done(true);
}


void EditItemDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
