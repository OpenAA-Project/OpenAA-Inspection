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

#ifndef CREATEMANUALMEASUREHOLEFORM_H
#define CREATEMANUALMEASUREHOLEFORM_H

#include <QDialog>
#include "ui_CreateManualMeasureHoleForm.h"
#include "XMeasureHole.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XDLLOnly.h"
#include "SelectColorSample.h"

class	GeneralLibFolderForm;

class CreateManualMeasureHoleForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

public:
	CreateManualMeasureHoleForm(LayersBase *Base, QWidget *parent);
	~CreateManualMeasureHoleForm();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	MeasureHoleItem			*BItem;

	void	Reflect(void);

private:
	Ui::CreateManualMeasureHoleFormClass ui;

	//MeasureHoleLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					LibID;

	ShowRGBSpace		ColorGenerator;
	SelectColorSample	ColorSamples;

	void	GetDataFromWindow(MeasureHoleItem &data);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_pushButtonEliminateColor_clicked();
	void on_pushButtonAddColor_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CREATEMANUALMEASUREHOLEFORM_H