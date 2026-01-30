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
#include "XTypeDef.h"
#include "CopyImageInPhasesDialog.h"
#include "ui_CopyImageInPhasesDialog.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"

CopyImageInPhasesDialog::CopyImageInPhasesDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::CopyImageInPhasesDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

	InstallOperationLog(this);

	for(int phase=0;phase<GetPhaseNumb();phase++){
		ui->listWidgetSourcePhase->addItem(GetLayersBase()->GetParamGlobal()->GetPhaseString(phase));
		ui->listWidgetDestPhase	 ->addItem(GetLayersBase()->GetParamGlobal()->GetPhaseString(phase));
	}
}

CopyImageInPhasesDialog::~CopyImageInPhasesDialog()
{
    delete ui;
}

void CopyImageInPhasesDialog::on_pushButtonCopy_clicked()
{
	SrcPhase	=ui->listWidgetSourcePhase->currentRow();
	DstPhase	=ui->listWidgetDestPhase->currentRow();
	FlagMaster	=ui->checkBoxMaster->isChecked();
	FlagTarget	=ui->checkBoxTarget->isChecked();

	done(true);
}

void CopyImageInPhasesDialog::on_pushButtonCancel_clicked()
{
	done(false);
}