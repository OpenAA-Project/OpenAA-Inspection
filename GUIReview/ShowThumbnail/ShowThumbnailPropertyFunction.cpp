/*
 * Copyright (C) 2018
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

#include "ShowThumbnailResource.h"
#include "ui_ShowThumbnailPropertyForm.h"
#include "ShowThumbnail.h"
#include "ShowThumbnailProperty.h"

void ShowThumbnail::setProperty(const ShowThumbnailProperty &property)
{
	// ??????p?????[?^??X???????L?q????
	
	setRowCount(property.RowCount);
	setColumnCount(property.ColumnCount);
	setNGSignSize(property.NGSignSize);
	setMoveDelay(property.CheckMillSec);
	setViewMaster(property.MasterPieceImageView);
	setMoveMode(property.InitialMoveMode);
	setEnableExpandThumbnal(property.ExpandThumbnailEnable);
	setModeShowPageByPiece (property.ModeShowPageByPiece);
	setFKeyList(property.FKeyColorList);
	getProperty().UncheckedColor	=property.UncheckedColor;
	getProperty().CheckedColor		=property.CheckedColor;

	(*m_property) = property;
}

void ShowThumbnail::setPropertyToUi(const ShowThumbnailProperty &property)
{
	// ??????p?????[?^????e??Ui????f???????L?q??????
	Ui::ShowThumbnailPropertyClass *ui = getPropertyUi();

	ui->sbRowCount->setValue( property.RowCount );
	ui->sbColumnCount->setValue( property.ColumnCount );
	ui->cbEnableExpandDialog	->setChecked( property.ExpandThumbnailEnable );
	ui->cbModeShowPageByPiece	->setChecked( property.ModeShowPageByPiece );
	ui->cbInitialMoveMode->setCurrentIndex( static_cast<int>(property.InitialMoveMode) );
	ui->cbViewMaster->setChecked( property.MasterPieceImageView );
	ui->sbCheckMillSec->setValue( property.CheckMillSec );
	ui->sbNGSignSize->setValue( property.NGSignSize );
}

void ShowThumbnail::setPropertyToUi()
{
	setPropertyToUi(getProperty());
	setProperty(getProperty());
}

void ShowThumbnail::setPropertyFromUi(ShowThumbnailProperty &property)
{
	// ??????Ui????e???p?????[?^????f???????L?q???s????
	Ui::ShowThumbnailPropertyClass *ui = getPropertyUi();
	
	property.RowCount				= ui->sbRowCount->value();
	property.ColumnCount			= ui->sbColumnCount->value();
	property.ExpandThumbnailEnable	= ui->cbEnableExpandDialog->isChecked();
	property.ModeShowPageByPiece	= ui->cbModeShowPageByPiece->isChecked();
	property.InitialMoveMode		= static_cast<ShowThumbnail::_moveMode>(ui->cbInitialMoveMode->currentIndex());
	property.MasterPieceImageView	= ui->cbViewMaster->isChecked();
	property.CheckMillSec			= ui->sbCheckMillSec->value();
	property.NGSignSize				= ui->sbNGSignSize->value();
}

void ShowThumbnail::setPropertyFromUi()
{
	setPropertyFromUi(getProperty());
}

void ShowThumbnail::slot_propertyModified()
{
	setPropertyFromUi();
	updateProperty();
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().save();

	updateGUI();
}

void ShowThumbnail::initProperty()
{
	setProperty(new ShowThumbnailProperty);
	setPropertyUi(new Ui::ShowThumbnailPropertyClass);
	setPropertyDialog(new QDialog);

	getPropertyUi()->setupUi(getPropertyDialog());
	QDir::setCurrent(GetLayersBase()->GetUserPath());
	getProperty().load();
	setPropertyToUi();

	connect(getPropertyUi()->pbOK, SIGNAL(clicked()), getPropertyDialog(), SLOT(accept()));
	connect(getPropertyUi()->pbCancel, SIGNAL(clicked()), getPropertyDialog(), SLOT(reject()));

	connect(getPropertyUi()->pbOK, SIGNAL(clicked()), this, SLOT(slot_propertyModified()));
	connect(getPropertyUi()->pbApply, SIGNAL(clicked()), this, SLOT(slot_propertyModified()));

	connect(getPropertyUi()->pushButtonColorNoChecked	, SIGNAL(clicked()), this, SLOT(on_pushButtonColorNoChecked_clicked()));
	connect(getPropertyUi()->pushButtonColorChecked		, SIGNAL(clicked()), this, SLOT(on_pushButtonColorChecked_clicked()));
	connect(getPropertyUi()->pushButtonColorF1			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF1_clicked()));
	connect(getPropertyUi()->pushButtonColorF2			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF2_clicked()));
	connect(getPropertyUi()->pushButtonColorF3			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF3_clicked()));
	connect(getPropertyUi()->pushButtonColorF4			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF4_clicked()));
	connect(getPropertyUi()->pushButtonColorF5			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF5_clicked()));
	connect(getPropertyUi()->pushButtonColorF6			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF6_clicked()));
	connect(getPropertyUi()->pushButtonColorF7			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF7_clicked()));
	connect(getPropertyUi()->pushButtonColorF8			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF8_clicked()));
	connect(getPropertyUi()->pushButtonColorF9			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF9_clicked()));
	connect(getPropertyUi()->pushButtonColorF10			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF10_clicked()));
	connect(getPropertyUi()->pushButtonColorF11			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF11_clicked()));
	connect(getPropertyUi()->pushButtonColorF12			, SIGNAL(clicked()), this, SLOT(on_pushButtonColorF12_clicked()));

}