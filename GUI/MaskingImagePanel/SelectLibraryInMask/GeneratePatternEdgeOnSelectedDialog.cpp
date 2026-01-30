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

#include "GeneratePatternEdgeOnSelectedDialog.h"
#include "ui_GeneratePatternEdgeOnSelectedDialog.h"
#include "SelectLibrariesForAnyType.h"
#include "XParamDatabase.h"
#include "XDLLOnly.h"
#include "XRememberer.h"

GeneratePatternEdgeOnSelectedDialog::GeneratePatternEdgeOnSelectedDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::GeneratePatternEdgeOnSelectedDialog)
{
    ui->setupUi(this);

	OnChanging=false;

	Libs=new SelectLibrariesForAnyType(Base,this);
	Libs->setParent(ui->frameLibrary);
	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());

	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Load(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	ui->labelMM1->setText(GetParamGlobal()->UnitName);

	ui->spinBoxBoundaryDiff	->setValue(ControlRememberer::GetInt(ui->spinBoxBoundaryDiff));
	ui->spinBoxWidthDot		->setValue(ControlRememberer::GetInt(ui->spinBoxWidthDot));

	InstallOperationLog(this);
}

GeneratePatternEdgeOnSelectedDialog::~GeneratePatternEdgeOnSelectedDialog()
{
    delete ui;
}
void GeneratePatternEdgeOnSelectedDialog::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,height()-ui->frame->height()
							,width(),ui->frame->height());
	ui->frameLibrary->resize(width(),height()-ui->frame->height());

	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());
}
void GeneratePatternEdgeOnSelectedDialog::on_ButtonEffective_clicked()
{
	Effective=true;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	BoundaryDiff=ControlRememberer::SetValue(ui->spinBoxBoundaryDiff);
	WidthDot	=ControlRememberer::SetValue(ui->spinBoxWidthDot);

	done(true);
}


void GeneratePatternEdgeOnSelectedDialog::on_ButtonNotEffective_clicked()
{
	Effective=false;
	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Save(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);

	BoundaryDiff=ControlRememberer::SetValue(ui->spinBoxBoundaryDiff);
	WidthDot	=ControlRememberer::SetValue(ui->spinBoxWidthDot);

	done(true);
}


void GeneratePatternEdgeOnSelectedDialog::on_ButtonCancel_clicked()
{
	done(false);
}

AlgorithmLibraryListContainer	GeneratePatternEdgeOnSelectedDialog::GetSelectedList(void)
{
	return Libs->SelectedList;
}

void GeneratePatternEdgeOnSelectedDialog::on_spinBoxWidthDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformPixelToUnit(-1,ui->spinBoxWidthDot->value());
	ui->doubleSpinBoxWidthMM->setValue(m);
	OnChanging=false;
}


void GeneratePatternEdgeOnSelectedDialog::on_doubleSpinBoxWidthMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	double	m=GetParamGlobal()->TransformUnitToPixel(-1,ui->doubleSpinBoxWidthMM->value());
	ui->spinBoxWidthDot->setValue((int)m);
	OnChanging=false;
}
