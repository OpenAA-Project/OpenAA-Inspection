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


#ifndef CREATEMANUALBLOCKFORM_H
#define CREATEMANUALBLOCKFORM_H

#include <QDialog>
#include "ui_CreateManualBlockForm.h"
#include "XBlockInspection.h"
#include "XServiceForLayers.h"

class	GeneralLibFolderForm;

class CreateManualBlockForm : public QDialog ,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;
	int	PastedLayer;
public:
	CreateManualBlockForm(LayersBase *Base,int Layer,QWidget *parent);
	~CreateManualBlockForm();
	
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	BlockItem			*BItem;

	void	Reflect(void);
private:
	Ui::CreateManualBlockFormClass ui;

	void	GetDataFromWindow(BlockItem &data);
	//BlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int				BlockLibID;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
	void	on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
};

#endif // CREATEMANUALBLOCKFORM_H