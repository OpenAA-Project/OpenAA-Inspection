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

#ifndef EDITEULERRINGLIBRARY_H
#define EDITEULERRINGLIBRARY_H

#include <QDialog>
#include "ui_EditEulerRingLibrary.h"
#include "XEulerRing.h"
#include "XEulerRingLibrary.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class EditEulerRingLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditEulerRingLibrary(LayersBase *base ,QWidget *parent);
	~EditEulerRingLibrary();

private:
	Ui::EditEulerRingLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//EulerRingLibrary	*TempLib;
	AlgorithmLibraryLevelContainer *TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	EulerRingBase	*GetEulerRingBase(void);
	AlgorithmLibraryListContainer	LibList;

	ShowRGBSpace	ColorGeneratorH;
	ShowRGBSpace	ColorGeneratorC;
	ShowRGBSpace	ColorInspection;

private slots:
	void on_pushButtonCColor_clicked();
	void on_pushButtonNColor_clicked();
	void on_pushButtonClose_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_pushButtonGColor_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITEULERRINGLIBRARY_H