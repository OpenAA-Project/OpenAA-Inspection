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


#ifndef SELECTBLOCKLIBRARYFORM_H
#define SELECTBLOCKLIBRARYFORM_H

#include <QDialog>
#include "ui_SelectBlockLibraryForm.h"
#include "XBlockInspection.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class SelectBlockLibraryForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SelectBlockLibraryForm(LayersBase *,QWidget *parent);
	~SelectBlockLibraryForm();

	int	SelectedLibID;

private:
	Ui::SelectBlockLibraryFormClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_doubleClicked(QModelIndex);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // SELECTBLOCKLIBRARYFORM_H