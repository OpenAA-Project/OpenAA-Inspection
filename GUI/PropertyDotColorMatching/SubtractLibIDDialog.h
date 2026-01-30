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

#ifndef SUBTRACTLIBIDDIALOG_H
#define SUBTRACTLIBIDDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SubtractLibIDDialog;
}
class   LibFolderForm;

class SubtractLibIDDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SubtractLibIDDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~SubtractLibIDDialog();

    AlgorithmLibraryListContainer	SelectedList;
    void	SetSelected(AlgorithmLibraryListContainer &selectedList);

    void	ShowFolder(int LibType);
    void	ShowSelectedList(void);
private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSend_clicked();
    void on_pushButtonBack_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_tableWidgetSelectedList_doubleClicked(const QModelIndex &index);

private:
    Ui::SubtractLibIDDialog *ui;

    LibFolderForm					*pLibFolderForm;
    int                             LibType;
    int								LibFolderID;
    AlgorithmLibraryListContainer	LibIDList;
};

#endif // SUBTRACTLIBIDDIALOG_H