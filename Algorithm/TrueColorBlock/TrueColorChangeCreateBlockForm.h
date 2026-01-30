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



#ifndef TRUECOLORCHANGECREATEBLOCKFORM_H
#define TRUECOLORCHANGECREATEBLOCKFORM_H

#include <QDialog>
#include "ui_TrueColorChangeCreateBlockForm.h"
#include "XTrueColorBlock.h"
#include "XTrueColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "ShowRGBCube.h"

class GeneralLibFolderForm;

class TrueColorChangeCreateBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

public:
	TrueColorChangeCreateBlockForm(TrueColorBlockBase *base ,QWidget *parent = 0);
	~TrueColorChangeCreateBlockForm();

	TrueColorBlockBase		*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	TrueColorBlockItem		ResultBlock;
	GeneralLibFolderForm	*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(TrueColorBlockItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

private:
	Ui::TrueColorChangeCreateBlockFormClass ui;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // TRUECOLORCHANGECREATEBLOCKFORM_H