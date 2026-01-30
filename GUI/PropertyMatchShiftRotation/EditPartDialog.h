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

#ifndef EDITPARTDIALOG_H
#define EDITPARTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMatchShiftRotation.h"
#include "XPropertyMatchShiftRotationPacket.h"
#include "XMatchShiftRotationLibrary.h"

namespace Ui {
class EditPartDialog;
}
class	GeneralLibFolderForm;

class EditPartDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	int	SelectedLibID;
public:
    explicit EditPartDialog(LayersBase *base ,QWidget *parent = 0);
    ~EditPartDialog();

	GeneralLibFolderForm	*pLibFolderForm;
	int				LibFolderID;
	AlgorithmLibraryListContainer	LibList;
	QString		AreaName;

	void	Reflect(bool EditMode=false);

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();
	void	SlotSelectLibFolder(int libFolderID ,QString FolderName);

    void on_tableWidgetLibList_clicked(const QModelIndex &index);

    void on_ButtonDelete_clicked();

private:
    Ui::EditPartDialog *ui;

	//MatchShiftRotationLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
public:
	int		MatchShiftRotationLibID;
};

#endif // EDITPARTDIALOG_H