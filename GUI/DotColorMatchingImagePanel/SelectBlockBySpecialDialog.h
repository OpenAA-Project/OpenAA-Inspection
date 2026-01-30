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

#ifndef SELECTBLOCKBYSPECIALDIALOG_H
#define SELECTBLOCKBYSPECIALDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "LibFolderForm.h"
#include "SelectLibrariesForm.h"

namespace Ui {
class SelectBlockBySpecialDialog;
}

class	DotColorMatchingImagePanel;

class SelectBlockBySpecialDialog : public QDialog
{
    Q_OBJECT

    DotColorMatchingImagePanel  *Parent;
public:
    SelectLibrariesForm		Libs;
public:
    explicit SelectBlockBySpecialDialog(DotColorMatchingImagePanel *p,int libType ,LayersBase *Base,QWidget *parent = nullptr);
    ~SelectBlockBySpecialDialog();

    bool    OutlineMode;
private slots:
    void on_ButtonSelect_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::SelectBlockBySpecialDialog *ui;
};

#endif // SELECTBLOCKBYSPECIALDIALOG_H