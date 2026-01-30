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

#include "PropertyGerberFastFormResource.h"
#include "CreateDCodeDialog.h"
#include "ui_CreateDCodeDialog.h"

CreateDCodeDialog::CreateDCodeDialog(LayersBase *base,GerberApertureInfoContainer *_ApertureList,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CreateDCodeDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	Page=0;
	ApertureList	=_ApertureList;
	int	MaxDCode=0;
	for(GerberApertureInfo	*a=ApertureList->GetFirst();a!=NULL;a=a->GetNext()){
		if(MaxDCode<a->DCode){
			MaxDCode=a->DCode;
		}
	}
	ui->spinBoxDCode->setValue(MaxDCode+1);
	CreatedAperture	=NULL;

	InstallOperationLog(this);
}

CreateDCodeDialog::~CreateDCodeDialog()
{
    delete ui;
}

void	CreateDCodeDialog::InitialForEdit(GerberApertureInfo *p)
{
	CreatedAperture	=NULL;

	ui->spinBoxDCode->setValue(p->DCode);
	QPalette	P=ui->spinBoxDCode->palette();
	P.setColor(QPalette::Window,Qt::cyan);
	ui->spinBoxDCode->setPalette(P);
	ui->spinBoxDCode->setReadOnly(true);

	switch(p->ShapeClass){
	case 1:	//Circle
			ui->stackedWidget	->setCurrentIndex(0);
			ui->doubleSpinBoxCircleDiameterPixel->setValue(p->Width);
			break;
	case 2:	//Rectangle
			ui->stackedWidget	->setCurrentIndex(1);
			ui->doubleSpinBoxRectangleWidthPixel->setValue(p->Width);
			ui->doubleSpinBoxRectangleHeightPixel->setValue(p->Height);
			break;
	case 3:	//Obround
			ui->stackedWidget	->setCurrentIndex(3);
			ui->doubleSpinBoxObroundWidthPixel->setValue(p->Width);
			ui->doubleSpinBoxObroundHeightPixel->setValue(p->Height);
			break;
	case 4:	//Polygon
			ui->stackedWidget	->setCurrentIndex(4);
			ui->doubleSpinBoxPolygonDiameterPixel->setValue(p->Width);
			ui->spinBoxPolygonSides->setValue((int)p->Height);
			break;
	}	
}

void CreateDCodeDialog::on_comboBoxType_currentIndexChanged(int index)
{
	ui->stackedWidget	->setCurrentIndex(ui->comboBoxType->currentIndex());
}

void CreateDCodeDialog::on_pushButtonCreate_clicked()
{
	/*
	if(ui->comboBoxType->currentIndex()==0){
		CreatedAperture	= new GerberDCodeCircle(NULL);
		((GerberDCodeCircle *)CreatedAperture)->HSize		=ui->doubleSpinBoxCircleDiameterPixel->value();
		((GerberDCodeCircle *)CreatedAperture)->WSize		=ui->doubleSpinBoxCircleDiameterPixel->value();
	}
	else if(ui->comboBoxType->currentIndex()==1){
		CreatedAperture	= new GerberDCodeRectangle(NULL);
		((GerberDCodeRectangle *)CreatedAperture)->WSize	=ui->doubleSpinBoxRectangleWidthPixel ->value();
		((GerberDCodeRectangle *)CreatedAperture)->HSize	=ui->doubleSpinBoxRectangleHeightPixel->value();
	}
	else if(ui->comboBoxType->currentIndex()==2){
		CreatedAperture	= new GerberDCodeObround(NULL);
		((GerberDCodeObround *)CreatedAperture)->WSize		=ui->doubleSpinBoxObroundWidthPixel ->value();
		((GerberDCodeObround *)CreatedAperture)->HSize		=ui->doubleSpinBoxObroundHeightPixel->value();
	}
	else if(ui->comboBoxType->currentIndex()==3){
		CreatedAperture	= new GerberDCodePolygon(NULL);
		((GerberDCodePolygon *)CreatedAperture)->Diameter	=ui->doubleSpinBoxPolygonDiameterPixel	->value();
		((GerberDCodePolygon *)CreatedAperture)->Sides		=ui->spinBoxPolygonSides				->value();
	}
	*/
	done(true);
}

void CreateDCodeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void CreateDCodeDialog::on_doubleSpinBoxCircleDiameterPixel_valueChanged(double arg1)
{
	ui->doubleSpinBoxCircleDiameterMM	->setValue(GetParamGlobal()->TransformPixelToUnit(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxCircleDiameterMM_valueChanged(double arg1)
{
	ui->doubleSpinBoxCircleDiameterPixel	->setValue(GetParamGlobal()->TransformUnitToPixel(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxRectangleWidthPixel_valueChanged(double arg1)
{
	ui->doubleSpinBoxRectangleWidthMM	->setValue(GetParamGlobal()->TransformPixelToUnit(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxRectangleWidthMM_valueChanged(double arg1)
{
	ui->doubleSpinBoxRectangleWidthPixel	->setValue(GetParamGlobal()->TransformUnitToPixel(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxRectangleHeightPixel_valueChanged(double arg1)
{
	ui->doubleSpinBoxRectangleHeightMM	->setValue(GetParamGlobal()->TransformPixelToUnit(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxRectangleHeightMM_valueChanged(double arg1)
{
	ui->doubleSpinBoxRectangleHeightPixel	->setValue(GetParamGlobal()->TransformUnitToPixel(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxObroundWidthPixel_valueChanged(double arg1)
{
	ui->doubleSpinBoxObroundWidthMM	->setValue(GetParamGlobal()->TransformPixelToUnit(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxObroundWidthMM_valueChanged(double arg1)
{
	ui->doubleSpinBoxObroundWidthPixel	->setValue(GetParamGlobal()->TransformUnitToPixel(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxObroundHeightPixel_valueChanged(double arg1)
{
	ui->doubleSpinBoxObroundHeightMM	->setValue(GetParamGlobal()->TransformPixelToUnit(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxObroundHeightMM_valueChanged(double arg1)
{
	ui->doubleSpinBoxObroundHeightPixel	->setValue(GetParamGlobal()->TransformUnitToPixel(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxPolygonDiameterPixel_valueChanged(double arg1)
{
	ui->doubleSpinBoxPolygonDiameterMM	->setValue(GetParamGlobal()->TransformPixelToUnit(Page,arg1));
}

void CreateDCodeDialog::on_doubleSpinBoxPolygonDiameterMM_valueChanged(double arg1)
{
	ui->doubleSpinBoxPolygonDiameterPixel	->setValue(GetParamGlobal()->TransformUnitToPixel(Page,arg1));
}