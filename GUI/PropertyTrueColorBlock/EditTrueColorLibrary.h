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


#ifndef EDITTRUECOLORLIBRARY_H
#define EDITTRUECOLORLIBRARY_H

#include <QDialog>
#include "ui_EditTrueColorLibrary.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class EditTrueColorLibrary : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	EditTrueColorLibrary(LayersBase *base ,QWidget *parent);
	~EditTrueColorLibrary();

private:
	Ui::EditTrueColorLibraryClass ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;

	//TrueColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	TrueColorBlockBase	*GetTrueColorBlockBase(void);
	void		ShowSubtractList(TrueColorBlockLibrary &data);
	AlgorithmLibraryListContainer	LibList;

	ShowRGBSpace	ColorGenerator;
	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

private slots:
	void on_pushButtonGColor_clicked();
	void on_ButtonDelSubtractLib_3_clicked();
	void on_ButtonAddSubtractLib_3_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_pushButtonClose_clicked();
	void on_ButtonLibSave_clicked();
	void on_ButtonLibSaveNew_clicked();
	void on_ButtonLibDelete_clicked();
	void on_ButtonLibNew_clicked();
	void on_pushButtonBColor_clicked();
	void on_pushButtonNColor_clicked();
	void on_toolButtonInspect_clicked();
	void on_toolButtonPickup_clicked();

	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
};

#endif // EDITTRUECOLORLIBRARY_H