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

#include "EasyPropertyMeasureResource.h"
#include "SetSearchDotDialog.h"
#include "ui_SetSearchDotDialog.h"
#include "EasyPropertyMeasureForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SetSearchDotDialog::SetSearchDotDialog(LayersBase *Base ,EasyPropertyMeasureForm *p
                                ,int SearchDot ,int _Page
								,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,Page(_Page)
    ,ui(new Ui::SetSearchDotDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    OnChanging=false;

    ui->spinBoxSearchDot->setValue(SearchDot);
    on_spinBoxSearchDot_valueChanged(0);
}

SetSearchDotDialog::~SetSearchDotDialog()
{
    delete ui;
}

void SetSearchDotDialog::on_spinBoxSearchDot_valueChanged(int arg1)
{
    if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixLength=ui->spinBoxSearchDot->value();
	ui->doubleSpinBoxSearchDotMM->setValue(GetParamGlobal()->TransformPixelToUnit(Page,PixLength));
	OnChanging=false;
}

void SetSearchDotDialog::on_doubleSpinBoxSearchDotMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	int	PixLength=GetParamGlobal()->TransformUnitToPixel(Page,ui->doubleSpinBoxSearchDotMM->value());
	ui->spinBoxSearchDot->setValue(PixLength);
	OnChanging=false;
}

void SetSearchDotDialog::on_pushButtonOK_clicked()
{
    RetSearchDot=ui->spinBoxSearchDot->value();
    done(1);
}

void SetSearchDotDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

void SetSearchDotDialog::on_pushButtonOKAll_clicked()
{
    RetSearchDot=ui->spinBoxSearchDot->value();
    done(2);
}