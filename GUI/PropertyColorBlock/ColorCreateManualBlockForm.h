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


#ifndef COLORCREATEMANUALBLOCKFORM_H
#define COLORCREATEMANUALBLOCKFORM_H

#include <QDialog>
#include "ui_ColorCreateManualBlockForm.h"
#include "XColorBlockInspection.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	GeneralLibFolderForm;

class ColorCreateManualBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

	mtToolButtonColored	ButtonR;
	mtToolButtonColored	ButtonG;
	mtToolButtonColored	ButtonB;
	int	CurrentColor;
public:
	ColorCreateManualBlockForm(LayersBase *Base,QWidget *parent);
	~ColorCreateManualBlockForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	ColorBlockItem			*BItem;

	void	Reflect(void);
private:
	Ui::ColorCreateManualBlockFormClass ui;

	void	GetDataFromWindow(ColorBlockItem &data);
	//ColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int					BlockLibID;

	void ShowLibrary(AlgorithmLibraryLevelContainer	*tempLib);

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
	void on_ToolButton_clicked();
};

#endif // CREATEMANUALBLOCKFORM_H