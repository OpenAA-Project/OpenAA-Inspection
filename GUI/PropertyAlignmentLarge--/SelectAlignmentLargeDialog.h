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

#ifndef SELECTALIGNMENTLARGEDIALOG_H
#define SELECTALIGNMENTLARGEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QToolButton>
#include "XAlignmentLarge.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectAlignmentLargeDialog;
}

class	GeneralLibFolderForm;

class SelectAlignmentLargeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    int	SelectedLibID;
public:
    explicit SelectAlignmentLargeDialog(LayersBase *Base,QWidget *parent = 0);
    ~SelectAlignmentLargeDialog();

 	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;

	int				AlignmentLargeLibID;   
private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
private:
    Ui::SelectAlignmentLargeDialog *ui;

	void	GetDataFromWindow(XAlignmentLarge &data);
	AlgorithmLibraryLevelContainer	*TempLib;
	QList<QToolButton *>	LayerGenButtons;
};

#endif // SELECTALIGNMENTLARGEDIALOG_H