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

#ifndef SELECTALIGNMENTFLEXAREADIALOG_H
#define SELECTALIGNMENTFLEXAREADIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XAlignmentFlexArea.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectAlignmentFlexAreaDialog;
}
class	AlgorithmLibraryLevelContainer;
class	GeneralLibFolderForm;

class SelectAlignmentFlexAreaDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	int	SelectedLibID;

public:
    explicit SelectAlignmentFlexAreaDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectAlignmentFlexAreaDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

	int				AlignmentFlexAreaLibID;

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectAlignmentFlexAreaDialog *ui;

	void	GetDataFromWindow(AlignmentFlexAreaItem &data);
	AlgorithmLibraryLevelContainer	*TempLib;

};

#endif // SELECTALIGNMENTFLEXAREADIALOG_H