/*
 * Copyright (C) 2026
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

//#include "AddManualItemFormResource.h"
#include "AddMonoManualItemForm.h"
#include "XRememberer.h"
#include "XDataInLayer.h"

AddMonoManualItemForm::AddMonoManualItemForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent) ,ServiceForLayers(base)
{
	ui.setupUi(this);

	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	if(LayerNumb==1)
		ui.stackedWidget->setCurrentIndex(2);
	else
		ui.stackedWidget->setCurrentIndex(0);

	InstallOperationLog(this);
}

AddMonoManualItemForm::~AddMonoManualItemForm()
{

}

void	AddMonoManualItemForm::SetInitial(void)
{
}

void AddMonoManualItemForm::on_pushButtonOK_clicked()
{
	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}



void AddMonoManualItemForm::on_pushButtonOK_2_clicked()
{
	done(true);
}

void AddMonoManualItemForm::on_pushButtonCancel_2_clicked()
{
	done(false);
}