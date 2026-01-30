/*
 * Copyright (C) 2017
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

#include "DynamicClassifyImagePanelResource.h"
#include "SelectAreaDialog.h"
#include "XGeneralFunc.h"


bool	SelectAreaMode::Load(QIODevice *f)
{
	if(::Load(f,CopyModeItem)==false)
		return false;
	if(::Load(f,CopyModeCore)==false)
		return false;
	if(::Load(f,CopyModeMaxZone)==false)
		return false;
	if(::Load(f,CopyModeMinZone)==false)
		return false;
	if(::Load(f,CopyModeBare)==false)
		return false;
	if(::Load(f,CopyModeInside)==false)
		return false;
	if(::Load(f,CopyModeOutlineI)==false)
		return false;
	if(::Load(f,CopyModeOutlineT)==false)
		return false;
	if(::Load(f,CopyModeOutlineO)==false)
		return false;
	return true;
}
bool	SelectAreaMode::Save(QIODevice *f)
{
	if(::Save(f,CopyModeItem)==false)
		return false;
	if(::Save(f,CopyModeCore)==false)
		return false;
	if(::Save(f,CopyModeMaxZone)==false)
		return false;
	if(::Save(f,CopyModeMinZone)==false)
		return false;
	if(::Save(f,CopyModeBare)==false)
		return false;
	if(::Save(f,CopyModeInside)==false)
		return false;
	if(::Save(f,CopyModeOutlineI)==false)
		return false;
	if(::Save(f,CopyModeOutlineT)==false)
		return false;
	if(::Save(f,CopyModeOutlineO)==false)
		return false;
	return true;
}


SelectAreaDialog::SelectAreaDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SelectAreaDialog::~SelectAreaDialog()
{

}


void SelectAreaDialog::on_pushButtonCopy_clicked()
{
	Mode.CopyModeItem		=ui.toolButtonItemArea		->isChecked();
	Mode.CopyModeCore		=ui.toolButtonCoreArea		->isChecked();
	Mode.CopyModeMaxZone	=ui.toolButtonMaxZone		->isChecked();
	Mode.CopyModeMinZone	=ui.toolButtonMinZone		->isChecked();
	Mode.CopyModeBare		=ui.toolButtonBareArea		->isChecked();
	Mode.CopyModeInside		=ui.toolButtonInsideArea	->isChecked();
	Mode.CopyModeOutlineI	=ui.toolButtonOutlineIArea	->isChecked();
	Mode.CopyModeOutlineT	=ui.toolButtonOutlineTArea	->isChecked();
	Mode.CopyModeOutlineO	=ui.toolButtonOutlineOArea	->isChecked();

	done(true);
}

void SelectAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}