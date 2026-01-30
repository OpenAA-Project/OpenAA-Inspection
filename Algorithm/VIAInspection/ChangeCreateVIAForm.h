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

#ifndef CHANGECREATEVIAFORM_H
#define CHANGECREATEVIAFORM_H

#include <QDialog>
#include "XViaInspection.h"
#include "XViaInspectionLibrary.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;
namespace Ui {
class ChangeCreateVIAForm;
}

class ChangeCreateVIAForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit ChangeCreateVIAForm(VIABase *base ,QWidget *parent = 0);
    ~ChangeCreateVIAForm();
    
	VIABase					*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	VIAItem					ResultVIA;
	GeneralLibFolderForm	*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(VIAItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::ChangeCreateVIAForm *ui;
};

#endif // CHANGECREATEVIAFORM_H