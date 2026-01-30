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



#ifndef COLORCHANGECREATEBLOCKFORM_H
#define COLORCHANGECREATEBLOCKFORM_H

#include <QDialog>
#include "ui_ColorChangeCreateBlockForm.h"
#include "XColorBlockInspection.h"
#include "XColorBlockLibrary.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	GeneralLibFolderForm;

class ColorChangeCreateBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT

	mtToolButtonColored	ButtonR;
	mtToolButtonColored	ButtonG;
	mtToolButtonColored	ButtonB;
	int	CurrentColor;

public:
	ColorChangeCreateBlockForm(ColorBlockBase *base ,QWidget *parent = 0);
	~ColorChangeCreateBlockForm();

	ColorBlockBase			*Base;
	AlgorithmLibraryLevelContainer	*TempLib;
	ColorBlockItem			ResultBlock;
	GeneralLibFolderForm	*pLibFolderForm;

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetItemFromWindow(ColorBlockItem &data);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
private:
	Ui::ColorChangeCreateBlockFormClass ui;

private slots:
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void on_ToolButton_clicked();
};

#endif // ColorCHANGECREATEBLOCKFORM_H