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

#ifndef EDITSTATISTICBLOCKLIBRARY_H
#define EDITSTATISTICBLOCKLIBRARY_H

#include <QDialog>
#include "ui_EditStatisticBlockLibrary.h"
#include "XStatisticBlock.h"
#include "XStatisticBlockLibrary.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class EditStatisticBlockLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditStatisticBlockLibrary(LayersBase *base ,QWidget *parent);
	~EditStatisticBlockLibrary();

private:
	Ui::EditStatisticBlockLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//StatisticBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	StatisticBlockBase	*GetStatisticBlockBase(void);
	AlgorithmLibraryListContainer	LibList;

private slots:
	void on_checkUseMorphology_toggled(bool checked);
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITSTATISTICBLOCKLIBRARY_H