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

#ifndef EDITLIBRARYDIALOG_H
#define EDITLIBRARYDIALOG_H

#include <QDialog>
#include <QTableWidgetItem>
#include "XRasterInspection.h"
#include "XRasterInspectionLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditLibraryDialog;
}
class	GeneralLibFolderForm;
class	RasterInspectionBase;
class	AlgorithmLibraryLevelContainer;


class EditLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	bool	OnChanging;

	AlgorithmLibraryLevelContainer	*LLib;
	int		LibType;

public:
    explicit EditLibraryDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~EditLibraryDialog();

private slots:
    void on_tableWidgetLibList_itemSelectionChanged();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::EditLibraryDialog *ui;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	RasterInspectionBase	*GetRasterInspectionBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // EDITLIBRARYDIALOG_H