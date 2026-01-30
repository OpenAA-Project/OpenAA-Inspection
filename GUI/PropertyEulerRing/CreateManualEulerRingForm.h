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

#ifndef CREATEMANUALEULERRINGFORM_H
#define CREATEMANUALEULERRINGFORM_H

#include <QDialog>
#include "ui_CreateManualEulerRingForm.h"
#include "XEulerRing.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class CreateManualEulerRingForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

public:
	CreateManualEulerRingForm(LayersBase *Base,QWidget *parent);
	~CreateManualEulerRingForm();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	EulerRingItem			*BItem;

	void	Reflect(void);

private:
	Ui::CreateManualEulerRingFormClass ui;
	//EulerRingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int						BlockLibID;

	ShowRGBSpace	ColorInspection;

	void	GetDataFromWindow(EulerRingItem &data);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // CREATEMANUALEULERRINGFORM_H