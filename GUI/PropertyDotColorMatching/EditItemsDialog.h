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

#ifndef EDITITEMSDIALOG_H
#define EDITITEMSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class EditItemsDialog;
}

class EditItemsDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemsDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~EditItemsDialog();

    void    SetItemInfo(int MasterNoOriginCode
                        ,AlgorithmLibraryListContainer &SubLibBlock
                        ,int ExpandToSubBlock);

    bool    AvailableMasterNo;
    int     MasterNoOriginCode;

    bool    AvailableSubBlock;
    AlgorithmLibraryListContainer	SubBlockList;
    int 	ExpandToSubBlock;

private slots:
    void on_pushButtonMasterNo_clicked();
    void on_pushButtonSubtractLibID_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemsDialog *ui;
};

#endif // EDITITEMSDIALOG_H