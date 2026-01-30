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

#ifndef ADDVCUTAREADIALOG_H
#define ADDVCUTAREADIALOG_H

#include <QDialog>
#include "ui_AddVCutAreaDialog.h"
#include "XServiceForLayers.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XVCutInspection.h"
#include "VCutImagePacket.h"

class	VCutInspectionBase;
class	VCutInspectionLibrary;
class	GeneralLibFolderForm;

class AddVCutAreaDialog : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	AddVCutAreaDialog(LayersBase *Base ,QWidget *parent = 0);
	~AddVCutAreaDialog();

	int		ThresholdShift;
	double	ThresholdLevel;
	int		ThresholdLength;
	int		SelectedLibID;
private:
	Ui::AddVCutAreaDialogClass ui;

	VCutInspectionBase	*GetVCutInspectionBase(void);

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//VCutInspectionLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;

	AlgorithmLibraryListContainer	LibList;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(void);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonGenerateLib_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
};

#endif // ADDVCUTAREADIALOG_H