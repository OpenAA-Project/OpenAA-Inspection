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


#ifndef TRUECOLORCREATEMANUALBLOCKFORM_H
#define TRUECOLORCREATEMANUALBLOCKFORM_H

#include <QDialog>
#include "ui_TrueColorCreateManualBlockForm.h"
#include "XTrueColorBlock.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"

class	GeneralLibFolderForm;

class TrueColorCreateManualBlockForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT
	int	SelectedLibID;

public:
	TrueColorCreateManualBlockForm(LayersBase *Base,QWidget *parent);
	~TrueColorCreateManualBlockForm();
	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	TrueColorBlockItem			*BItem;

	void	Reflect(void);

private:
	Ui::TrueColorCreateManualBlockFormClass ui;
	//TrueColorBlockLibrary	*TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
	int						BlockLibID;

	ShowRGBSpace	ColorNarrow;
	ShowRGBSpace	ColorBroad;

	void	GetDataFromWindow(TrueColorBlockItem &data);

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
	void on_tableWidgetLibList_clicked(const QModelIndex &);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
};

#endif // TRUECOLORCREATEMANUALBLOCKFORM_H