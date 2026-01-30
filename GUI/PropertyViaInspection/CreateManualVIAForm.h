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

#ifndef CREATEMANUALVIAFORM_H
#define CREATEMANUALVIAFORM_H

#include <QDialog>
#include "XViaInspection.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualVIAForm;
}
class	GeneralLibFolderForm;
class	VIALibrary;

class CreateManualVIAForm : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
 	int	SelectedLibID;   
public:
    explicit CreateManualVIAForm(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualVIAForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	VIAItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::CreateManualVIAForm *ui;

	void	GetDataFromWindow(VIAItem &data);
	//VIALibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int				VIALibID;
};

#endif // CREATEMANUALVIAFORM_H