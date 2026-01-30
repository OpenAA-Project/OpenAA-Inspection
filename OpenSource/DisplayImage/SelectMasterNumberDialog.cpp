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

#include "DisplayImageResource.h"
#include "SelectMasterNumberDialog.h"
#include "XTypeDef.h"
#include "ui_SelectMasterNumberDialog.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"

SelectMasterNumberDialog::SelectMasterNumberDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectMasterNumberDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

	SelectedMasterNo=-1;

	for(int i=0;i<GetCountOnlyMasterBuff();i++){
		if(i<GetParamGlobal()->MasterBuffNames.count()
		&& GetParamGlobal()->MasterBuffNames[i].isEmpty()==false){
			ui->comboBox->addItem(QString::number(i) 
								+ QString(/**/" : ")
								+ GetParamGlobal()->MasterBuffNames[i]);
		}
		else{
			ui->comboBox->addItem(QString::number(i));
		}
	}
}

SelectMasterNumberDialog::~SelectMasterNumberDialog()
{
    delete ui;
}

void SelectMasterNumberDialog::on_pushButtonOK_clicked()
{
	SelectedMasterNo=ui->comboBox->currentIndex();
	done(true);
}

void SelectMasterNumberDialog::on_pushButtonCancel_clicked()
{
	done(false);
}