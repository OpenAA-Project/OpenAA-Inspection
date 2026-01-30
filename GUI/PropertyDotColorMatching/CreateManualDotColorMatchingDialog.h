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

#ifndef CREATEMANUALDOTCOLORMATCHINGDIALOG_H
#define CREATEMANUALDOTCOLORMATCHINGDIALOG_H

#include <QDialog>
#include "XDotColorMatching.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualDotColorMatchingDialog;
}
class	GeneralLibFolderForm;
class AlgorithmLibraryLevelContainer;

class CreateManualDotColorMatchingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	int	SelectedLibID;

public:
    explicit CreateManualDotColorMatchingDialog(LayersBase *Base,QWidget *parent = 0);
    ~CreateManualDotColorMatchingDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	DotColorMatchingItem			*BItem;

	void	Reflect(void);

private slots:
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);
    void on_toolButtonBroad_clicked();

    void on_toolButtonNarrow_clicked();

private:
    Ui::CreateManualDotColorMatchingDialog *ui;

	void	GetDataFromWindow(DotColorMatchingItem &data);
	AlgorithmLibraryLevelContainer	*LLib;
	int				DotColorMatchingLibID;
};

#endif // CREATEMANUALDOTCOLORMATCHINGDIALOG_H