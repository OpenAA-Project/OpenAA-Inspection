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

#ifndef SELECTLIBFORVALIDATIONFORM_H
#define SELECTLIBFORVALIDATIONFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectLibForValidationForm;
}
class   LibFolderForm;

class SelectLibForValidationForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT


public:
    explicit SelectLibForValidationForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~SelectLibForValidationForm();

    bool    Initial(int LibType, int LibID);

    void	ShowFolder(int LibType);

private slots:
    void on_comboBoxAlgorithm_currentIndexChanged(int index);
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibForValidationForm *ui;
    LibFolderForm					*pLibFolderForm;
    int                             SelectedLibType;
    int								LibFolderID;
    AlgorithmLibraryListContainer	LibIDList;

signals:
    void    SignalSelectedLib(int LibType,int LibID);
};

#endif // SELECTLIBFORVALIDATIONFORM_H