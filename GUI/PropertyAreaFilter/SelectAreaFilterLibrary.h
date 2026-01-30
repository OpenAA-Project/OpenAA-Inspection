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


#ifndef SELECTAREAFILTERLIBRARY_H
#define SELECTAREAFILTERLIBRARY_H

#include <QDialog>
#include "ui_SelectAreaFilterLibrary.h"
#include "XServiceForLayers.h"
#include "XAreaFilter.h"

class	GeneralLibFolderForm;

class SelectAreaFilterLibrary : public QDialog , public ServiceForLayers
{
	Q_OBJECT

public:
	SelectAreaFilterLibrary(LayersBase *base ,QWidget *parent);
	~SelectAreaFilterLibrary();

	int	SelectedLibID;

private:
	Ui::SelectAreaFilterLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_tableWidgetLibList_itemDoubleClicked(QTableWidgetItem*);
	void on_ButtonCancel_clicked();
	void on_ButtonSelect_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // SELECTAREAFILTERLIBRARY_H