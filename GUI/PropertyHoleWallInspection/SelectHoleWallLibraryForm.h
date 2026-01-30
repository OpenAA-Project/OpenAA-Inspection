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

#ifndef SELECTHOLEWALLLIBRARYFORM_H
#define SELECTHOLEWALLLIBRARYFORM_H

#include <QDialog>
#include "XHoleWallInspection.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectHoleWallLibraryForm;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SelectHoleWallLibraryForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectHoleWallLibraryForm(LayersBase *,QWidget *parent = 0);
    ~SelectHoleWallLibraryForm();

	int	SelectedLibID;

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectHoleWallLibraryForm *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
};

#endif // SELECTHOLEWALLLIBRARYFORM_H