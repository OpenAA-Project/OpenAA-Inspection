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


#ifndef SELECTEulerRingL1LIBRARYFORM_H
#define SELECTEulerRingL1LIBRARYFORM_H

#include <QDialog>
#include "ui_SelectEulerRingL1LibraryForm.h"
#include "XEulerRingL1.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class SelectEulerRingL1LibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectEulerRingL1LibraryForm(LayersBase *,QWidget *parent);
	~SelectEulerRingL1LibraryForm();

	int	SelectedLibID;

private:
	Ui::SelectEulerRingL1LibraryFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // SELECTEulerRingL1LIBRARYFORM_H