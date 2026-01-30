/*
 * Copyright (C) 2025
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

#ifndef EDITALIGNMENTBLOCKLIBRARYDIALOG_H
#define EDITALIGNMENTBLOCKLIBRARYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QTableWidget>
#include <QToolButton>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XDataAlgorithm.h"
#include "XAlignmentBlock.h"
#include "XGeneralDialog.h"

namespace Ui {
class EditAlignmentBlockLibraryDialog;
}

class EditAlignmentBlockLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditAlignmentBlockLibraryDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~EditAlignmentBlockLibraryDialog();

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonClose_clicked();
    void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::EditAlignmentBlockLibraryDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
    int     MasterNoOriginCode;
	bool	OnChanging;

	AlgorithmLibraryLevelContainer	*LLib;

	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);

	AlignmentBlockBase	*GetAlignmentBlockBase(void);
	AlgorithmLibraryListContainer	LibList;
};

#endif // EDITALIGNMENTBLOCKLIBRARYDIALOG_H