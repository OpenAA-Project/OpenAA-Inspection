/*
 * Copyright (C) 2026
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

#ifndef SELECTBYLIBRARYDIALOG_H
#define SELECTBYLIBRARYDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "LibFolderForm.h"
#include "SelectLibrariesForm.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectByLibraryDialog;
}

class SelectByLibraryDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectByLibraryDialog(int libType ,LayersBase *Base,QWidget *parent = 0);
    ~SelectByLibraryDialog();

    SelectLibrariesForm		Libs;

private slots:
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectByLibraryDialog *ui;
};

#endif // SELECTBYLIBRARYDIALOG_H