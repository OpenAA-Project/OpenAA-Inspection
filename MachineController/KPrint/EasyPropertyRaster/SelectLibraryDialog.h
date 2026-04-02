/*
 * Copyright (C) 2022
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
#include <QModelIndex>
#include "XRaster.h"
#include "XRasterLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryDialog;
}
class	GeneralLibFolderForm;
class	AlgorithmLibraryLevelContainer;

class SelectLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibraryDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectLibraryDialog();
    
	int	SelectedLibID;
    int ExpandColorR;
    int ExpandColorG;
    int ExpandColorB;

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectLibraryDialog *ui;

	GeneralLibFolderForm			*pLibFolderForm;
	int								LibFolderID;
	int								LibType;
	AlgorithmLibraryListContainer	LibList;

	RasterBase	*GetRasterBase(void);
};

#endif // SELECTLIBRARYDIALOG_H