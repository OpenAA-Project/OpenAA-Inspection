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

#ifndef CREATEMANUALITEMFORM_H
#define CREATEMANUALITEMFORM_H

#include <QDialog>
#include "ui_CreateManualItemForm.h"
#include "XServiceForLayers.h"
#include "XMeasureHolePos.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "XDLLOnly.h"
#include "SelectColorSample.h"

class	GeneralLibFolderForm;

class CreateManualItemForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

	int	SelectedLibID;

public:
	CreateManualItemForm(LayersBase *Base ,QWidget *parent = 0);
	~CreateManualItemForm();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	MeasureHolePosItem			*BItem;

	void	Reflect(void);

private:
	Ui::CreateManualItemFormClass ui;

	//MeasureHolePosLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					LibID;

	ShowRGBSpace		ColorGenerator;
	SelectColorSample	ColorSamples;
	void	GetDataFromWindow(MeasureHolePosItem &data);

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void on_pushButtonNColor_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CREATEMANUALITEMFORM_H