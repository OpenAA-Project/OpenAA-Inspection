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

#include "CopyBetweenPhaseDialogResource.h"
#include "CopyBetweenPhaseDialog.h"
#include "ui_CopyBetweenPhaseDialog.h"

CopyBetweenPhaseDialog::CopyBetweenPhaseDialog(const QString &AlgoRoot , const QString &AlgoName 
											,int32	iSourcePhase
											,int32	iDestinationPhase
											,bool	iModeCopyMasterImage
											,bool	iModeCopyTargetImage
											,bool	iModeCopyAlgorithm
											, LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CopyBetweenPhaseDialog)
{
    ui->setupUi(this);
	SourcePhase				=iSourcePhase;
	DestinationPhase		=iDestinationPhase;
	ModeCopyMasterImage		=iModeCopyMasterImage;
	ModeCopyTargetImage		=iModeCopyTargetImage;
	ModeCopyAlgorithm		=iModeCopyAlgorithm;

	ui->checkBoxMaster		->setChecked(ModeCopyMasterImage);
	ui->checkBoxTarget		->setChecked(ModeCopyTargetImage);
	ui->checkBoxAlgorithm	->setChecked(ModeCopyAlgorithm);
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ui->listWidgetSourcePhase->addItem(GetLayersBase()->GetParamGlobal()->GetPhaseString(phase));
		ui->listWidgetDestPhase	 ->addItem(GetLayersBase()->GetParamGlobal()->GetPhaseString(phase));
	}
	InstallOperationLog(this);
}

CopyBetweenPhaseDialog::~CopyBetweenPhaseDialog()
{
    delete ui;
}

void CopyBetweenPhaseDialog::on_pushButtonCopy_clicked()
{
	SourcePhase			=ui->listWidgetSourcePhase->currentRow();
	DestinationPhase	=ui->listWidgetDestPhase->currentRow();

	ModeCopyMasterImage	=ui->checkBoxMaster		->isChecked();
	ModeCopyTargetImage	=ui->checkBoxTarget		->isChecked();
	ModeCopyAlgorithm	=ui->checkBoxAlgorithm	->isChecked();
	done(true);
}

void CopyBetweenPhaseDialog::on_pushButtonCancel_clicked()
{
	done(false);
}