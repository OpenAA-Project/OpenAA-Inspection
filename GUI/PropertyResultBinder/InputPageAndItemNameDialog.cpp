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

#include "PropertyResultBinderFormResource.h"
#include "InputPageAndItemNameDialog.h"
#include "ui_InputPageAndItemNameDialog.h"

InputPageAndItemNameDialog::InputPageAndItemNameDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::InputPageAndItemNameDialog)
{
    ui->setupUi(this);

	for(int page=0;page<GetPageNumb();page++){
		ui->comboBoxPage->addItem(LangSolver.GetString(InputPageAndItemNameDialog_LS,LID_13)/*"Layer "*/+QString::number(page));
	}
	InstallOperationLog(this);
}

InputPageAndItemNameDialog::~InputPageAndItemNameDialog()
{
    delete ui;
}

void	InputPageAndItemNameDialog::Initial(const QString &ItemName)
{
	ui->lineEditItemName->setText(ItemName);
}
void InputPageAndItemNameDialog::on_pushButtonOK_clicked()
{
	Page	=ui->comboBoxPage->currentIndex();
	ItemName=ui->lineEditItemName->text();
	done(true);
}

void InputPageAndItemNameDialog::on_pushButtonCancel_clicked()
{
	done(false);
}