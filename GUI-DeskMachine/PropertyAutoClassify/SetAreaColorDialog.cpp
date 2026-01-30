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

#include "SetAreaColorDialog.h"
#include "XColorSpace.h"
#include "XFlexArea.h"
#include "XDataInLayer.h"


SetAreaColorDialog::SetAreaColorDialog(RGBStock &PickupColor ,FlexArea &Area
						,LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
}

SetAreaColorDialog::~SetAreaColorDialog()
{

}


void SetAreaColorDialog::on_pushButtonReplace_clicked()
{

	done(true);
}

void SetAreaColorDialog::on_pushButtonAdd_clicked()
{

	done(true);
}

void SetAreaColorDialog::on_pushButtonCancel_clicked()
{
	done(false);
}