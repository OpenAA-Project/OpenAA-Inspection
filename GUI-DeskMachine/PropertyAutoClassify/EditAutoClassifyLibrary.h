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


#ifndef EDITAUTOCLASSIFYLIBRARY_H
#define EDITAUTOCLASSIFYLIBRARY_H

#include <QDialog>
#include <QModelIndex>
#include "ui_EditAutoClassifyLibrary.h"
#include "LibFolderForm.h"
#include "XAutoClassify.h"
#include "XServiceForLayers.h"

class GeneralLibFolderForm;

class EditAutoClassifyLibrary : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	EditAutoClassifyLibrary(LayersBase *base ,QWidget *parent = 0);
	~EditAutoClassifyLibrary();

private:
	Ui::EditAutoClassifyLibraryClass ui;
	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AutoClassifyBase	*GetAutoClassifyBase(void);
	AlgorithmLibraryListContainer	LibList;


private slots:
	void on_pushButton_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITAUTOCLASSIFYLIBRARY_H