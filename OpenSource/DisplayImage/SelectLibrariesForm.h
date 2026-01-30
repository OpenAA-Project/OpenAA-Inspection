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


#ifndef SELECTLIBRARIESFORM_H
#define SELECTLIBRARIESFORM_H

#include <QWidget>
#include "XAlgorithmLibrary.h"
#include "LibFolderForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLibrariesForm;
}

class SelectLibrariesForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectLibrariesForm(int libType ,LayersBase *Base,QWidget *parent = 0);
    ~SelectLibrariesForm();

    AlgorithmLibraryListContainer	SelectedList;
    void	SetSelected(const AlgorithmLibraryListContainer &selectedList);

private slots:
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetSelectedList_doubleClicked(const QModelIndex &index);
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);

private:
    Ui::SelectLibrariesForm *ui;

    LibFolderForm					*pLibFolderForm;
    int								LibFolderID;
    int								LibType;
    AlgorithmLibraryListContainer	LibIDList;

    void	ShowFolder(int LibType);
    void	ShowSelectedList(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTLIBRARIESFORM_H