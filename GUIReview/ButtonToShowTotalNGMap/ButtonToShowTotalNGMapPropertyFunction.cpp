/*
 * Copyright (C) 2021
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

#include "ButtonToShowTotalNGMapResource.h"
#include "ui_ButtonToShowTotalNGMapPropertyForm.h"
#include "ButtonToShowTotalNGMap.h"
#include "ButtonToShowTotalNGMapProperty.h"
#include <QColorDialog>

void ButtonToShowTotalNGMap::setProperty(const ButtonToShowTotalNGMapProperty &property)
{
	// �����Ƀp�����[�^�ύX�̑Ή����L�q����
	(*m_property) = property;
}

void ButtonToShowTotalNGMap::setPropertyToUi(const ButtonToShowTotalNGMapProperty &property)
{
	// �����Ƀp�����[�^�̓��e��Ui�ɔ��f�������L�q������
	Ui::ButtonToShowTotalNGMapPropertyClass *ui = getPropertyUi();

	ui->sbSplitCountX->setValue(property.SplitCountX);
	ui->sbSplitCountY->setValue(property.SplitCountY);
	QPalette pale = ui->tbNGColor->palette();
	pale.setColor(QPalette::ColorRole::Button, property.NGDrawColor);
	ui->lbNGColorSample->setText(property.NGDrawColor.name());
	ui->lbNGColorSample->setBackgroundRole(QPalette::Button);
	ui->lbNGColorSample->setAutoFillBackground(true);
	ui->tbNGColor->setPalette(pale);
	ui->sbNGDrawSize->setValue(property.NGDrawSize);
	ui->cbDrawShape->setCurrentIndex(property.NGDrawShape);
	ui->cbIgnoreResultError->setChecked(property.IgnoreErrorBoard);
}

void ButtonToShowTotalNGMap::setPropertyToUi()
{
	setPropertyToUi(getProperty());
}

void ButtonToShowTotalNGMap::setPropertyFromUi(ButtonToShowTotalNGMapProperty &property)
{
	// ������Ui�̓��e���p�����[�^�ɔ��f�������L�q���s����
	Ui::ButtonToShowTotalNGMapPropertyClass *ui = getPropertyUi();

	property.SplitCountX = ui->sbSplitCountX->value();
	property.SplitCountY = ui->sbSplitCountY->value();
	property.NGDrawColor = ui->tbNGColor->palette().color(QPalette::ColorRole::Button);
	property.NGDrawSize = ui->sbNGDrawSize->value();
	int index = ui->cbDrawShape->currentIndex();
	if(index!=-1){
		property.NGDrawShape = (TotalNGMap::NGDrawShapeType)index;
	}else{
		property.NGDrawShape = TotalNGMap::NGDrawShapeType::Fill_Rectangle;
	}
	property.IgnoreErrorBoard = ui->cbIgnoreResultError->isChecked();
}

void ButtonToShowTotalNGMap::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ButtonToShowTotalNGMap::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	getProperty().save();
}

void ButtonToShowTotalNGMap::slot_propertyRejected()
{
	setPropertyToUi();
}

void ButtonToShowTotalNGMap::slot_tbNGColor_clicked()
{
	QColor color = QColorDialog::getColor(getProperty().NGDrawColor, this, LangSolver.GetString(ButtonToShowTotalNGMapPropertyFunction_LS,LID_0)/*"Select NG Color"*/);
	if(color.isValid()==true){
		QPalette pale = getPropertyUi()->tbNGColor->palette();
		pale.setColor(QPalette::ColorRole::Button, color);
		getPropertyUi()->tbNGColor->setBackgroundRole(QPalette::Button);
		getPropertyUi()->tbNGColor->setPalette(pale);
		getPropertyUi()->lbNGColorSample->setText(pale.color(QPalette::Button).name());
	}
}

void ButtonToShowTotalNGMap::initProperty()
{
	setProperty(new ButtonToShowTotalNGMapProperty);
	setPropertyUi(new Ui::ButtonToShowTotalNGMapPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());

	getProperty().load();
	setPropertyToUi();

	connect(getPropertyDialog(), SIGNAL(accepted()), this, SLOT(slot_propertyModified()));
	connect(getPropertyDialog(), SIGNAL(rejected()), this, SLOT(slot_propertyRejected()));
	connect(getPropertyUi()->tbNGColor, SIGNAL(clicked()), this, SLOT(slot_tbNGColor_clicked()));
}


 
void ButtonToShowTotalNGMap::clicked()
{
	m_map.setSplitX(getProperty().SplitCountX);
	m_map.setSplitY(getProperty().SplitCountY);
	m_map.setNGDrawColor(getProperty().NGDrawColor);
	m_map.setNGDrawSize(getProperty().NGDrawSize);
	m_map.setNGDrawShape((TotalNGMap::NGDrawShapeType)getProperty().NGDrawShape);
	m_map.setIgnoreErrorInspect(getProperty().IgnoreErrorBoard);

	m_map.setModal(false);
	
	m_map.exec();
}