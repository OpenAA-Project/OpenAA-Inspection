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

#ifndef SELECTCOMPOSITEDEFDIALOG_H
#define SELECTCOMPOSITEDEFDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"

namespace Ui {
class SelectCompositeDefDialog;
}

class	GeneralLibFolderForm;

class SelectCompositeDefDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	int		LibType;
public:
    explicit SelectCompositeDefDialog(LayersBase *base,QWidget *parent = 0);
    ~SelectCompositeDefDialog();

	int	SelectedCompositeID;

private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectCompositeDefDialog *ui;

	void ShowCompositeList(void);
};

#endif // SELECTCOMPOSITEDEFDIALOG_H