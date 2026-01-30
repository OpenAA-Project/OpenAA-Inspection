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

#ifndef SELECTITEMDIALOG_H
#define SELECTITEMDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XMatchShiftRotation.h"
#include "XServiceForLayers.h"
#include "XMatchShiftRotationLibrary.h"

namespace Ui {
class SelectItemDialog;
}
class	GeneralLibFolderForm;

class SelectItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int	SelectedLibID;
public:
    explicit SelectItemDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectItemDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	QString			ItemName;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

    void on_ButtonDelete_clicked();

private:
    Ui::SelectItemDialog *ui;

	//MatchShiftRotationLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
public:
	int		MatchShiftRotationLibID;
};

#endif // SELECTITEMDIALOG_H