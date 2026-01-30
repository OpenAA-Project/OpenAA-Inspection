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

#ifndef SELECTACTIONLIBRARYDIALOG_H
#define SELECTACTIONLIBRARYDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectActionLibraryDialog;
}
class EasyPropertyAlignmentForm;

class SelectActionLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    EasyPropertyAlignmentForm   *Parent;
    IntList                         LibTypeList;
    AlgorithmLibraryListContainer   CurrentLibList;
public:
    explicit SelectActionLibraryDialog(LayersBase *base
                                        ,EasyPropertyAlignmentForm *P
                                        ,bool DeleteButton
                                        ,QWidget *parent = nullptr);
    ~SelectActionLibraryDialog();

    AlgorithmLibraryListContainer    Selected;

private slots:
    void on_listWidgetLibType_clicked(const QModelIndex &index);

    void on_toolButtonAddLibrary_clicked();
    void on_toolButtonRemoveLibrary_clicked();
    void on_tableWidgetLibrary_doubleClicked(const QModelIndex &index);

private:
    Ui::SelectActionLibraryDialog *ui;
};

#endif // SELECTACTIONLIBRARYDIALOG_H