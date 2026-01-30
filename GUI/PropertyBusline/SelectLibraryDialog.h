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

#ifndef SELECTLIBRARYDIALOG_H
#define SELECTLIBRARYDIALOG_H

#include <QDialog>
#include "XBuslineInspection.h"
#include "XServiceForLayers.h"
#include "XDLLOnly.h"
#include "XDataAlgorithm.h"

namespace Ui {
class SelectLibraryDialog;
}

class	GeneralLibFolderForm;

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibraryDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	void	Initial(AlgorithmBase *InstBase);
	int		SelectedID;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

private:
    Ui::SelectLibraryDialog *ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//BuslineLibrary	*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	AlgorithmLibraryListContainer	LibIDList;

	BuslineBase	*GetBuslineBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // SELECTLIBRARYDIALOG_H