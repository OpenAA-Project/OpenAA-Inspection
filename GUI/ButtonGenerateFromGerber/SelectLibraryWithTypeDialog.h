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

#ifndef SELECTLIBRARYWITHTYPEDIALOG_H
#define SELECTLIBRARYWITHTYPEDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibraryWithTypeDialog;
}

class	GerberFastBase;
class	GeneralLibFolderForm;

class SelectLibraryWithTypeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectLibraryWithTypeDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectLibraryWithTypeDialog();

	int								CurrentLibType;
	int								SelectedLibID;

	void	Initial(void);

private slots:
    void on_comboBoxLibTypeSelect_currentIndexChanged(int index);
    void on_tableWidgetLibListSelect_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotSelectLibFolderSelect(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibraryWithTypeDialog *ui;

	GeneralLibFolderForm			*pLibFolderSelect;
	AlgorithmLibraryListContainer	LibIDListSelect;
	int								CurrentLibFolderID;

	void	SetLibTypeInComboBox(void);
	void	ShowFolder(int LibType);
	void	ShowSelectedList(void);

	GerberFastBase	*GetGerberFastBase(void);

};

#endif // SELECTLIBRARYWITHTYPEDIALOG_H