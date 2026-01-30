/*
 * Copyright (C) 2021
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

#ifndef EDITLAYERTYPEDIALOG_H
#define EDITLAYERTYPEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditLayerTypeDialog;
}
class	GeneralLibFolderForm;
class	GerberFastBase;
class	GerberLayerAttr;
class	GerberFastLibrary;

class EditLayerTypeDialog : public QDialog , public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditLayerTypeDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditLayerTypeDialog();

	void	SetLibID(int LibID);

private slots:
    void on_pushButtonClose_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_tableWidgetLibList_clicked(const QModelIndex &index);

    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);

private:
    Ui::EditLayerTypeDialog *ui;
	GerberFastBase	*GetGerberFastBase(void);

	GeneralLibFolderForm			*pLibFolder;
	int								LibFolderID;
	AlgorithmLibraryListContainer	LibIDList;
	//GerberFastLibrary				*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;

	void	ShowList(void);
	void	ShowDataToWindow(AlgorithmLibraryLevelContainer *Attr);
	void	GetDataFromWindow(AlgorithmLibraryLevelContainer *Attr);
	void	LibNewFunc(void);
};

#endif // EDITLAYERTYPEDIALOG_H