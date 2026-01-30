/*
 * Copyright (C) 2016
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

#ifndef COPYBETWEENPHASEDIALOG_H
#define COPYBETWEENPHASEDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XServiceForLayers.h"

namespace Ui {
class CopyBetweenPhaseDialog;
}

class CopyBetweenPhaseDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	int32	SourcePhase;
	int32	DestinationPhase;
	bool	ModeCopyMasterImage;
	bool	ModeCopyTargetImage;
	bool	ModeCopyAlgorithm;

    explicit CopyBetweenPhaseDialog(const QString &AlgoRoot , const QString &AlgoName 
									,int32	SourcePhase
									,int32	DestinationPhase
									,bool	ModeCopyMasterImage
									,bool	ModeCopyTargetImage
									,bool	ModeCopyAlgorithm
									, LayersBase *base ,QWidget *parent = 0);
    ~CopyBetweenPhaseDialog();

private slots:
    void on_pushButtonCopy_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CopyBetweenPhaseDialog *ui;
};

#endif // COPYBETWEENPHASEDIALOG_H