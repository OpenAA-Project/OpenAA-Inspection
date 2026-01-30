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

#include "MaskingImagePanelResource.h"
#include "SelectByLimitedDialog.h"
#include "ui_SelectByLimitedDialog.h"
#include "XDLLOnly.h"
#include "XParamDatabase.h"
#include "SelectLibrariesForAnyType.h"

SelectByLimitedDialog::SelectByLimitedDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::SelectByLimitedDialog)
{
    ui->setupUi(this);

	Libs=new SelectLibrariesForAnyType(Base,this);
	Libs->setParent(ui->frameLibrary);
	Libs->setGeometry(0,0,ui->frameLibrary->width(),ui->frameLibrary->height());

	QIODevice	*Buff=GetLayersBase()->GetLocalParamStocker()->CreateIODevice(objectName());
	Libs->Load(Buff);
	GetLayersBase()->GetLocalParamStocker()->DeleteIODevice(Buff);
	InstallOperationLog(this);
}

SelectByLimitedDialog::~SelectByLimitedDialog()
{
    delete ui;
	delete	Libs;
	Libs=NULL;
}

void	SelectByLimitedDialog::SetSelected(AlgorithmLibraryListContainer &selectedList)
{
	Libs->SelectedList=selectedList;
	Libs->ShowSelectedList();
}


void SelectByLimitedDialog::on_ButtonSelectAll_clicked()
{
	done(1);
}

void SelectByLimitedDialog::on_ButtonSelectOneAtLeast_clicked()
{
	done(2);
}

void SelectByLimitedDialog::on_ButtonCancel_clicked()
{
	done(-1);
}
AlgorithmLibraryListContainer	SelectByLimitedDialog::GetSelectedList(void)
{
	return Libs->SelectedList;
}