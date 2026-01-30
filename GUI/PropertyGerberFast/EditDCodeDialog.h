/*
 * Copyright (C) 2017
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

#ifndef EDITDCODEDIALOG_H
#define EDITDCODEDIALOG_H

#include <QDialog>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditDCodeDialog;
}

class EditDCodeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	GerberApertureInfoContainer *ApertureList;
public:
    explicit EditDCodeDialog(int FileLayerNo ,LayersBase *base, GerberApertureInfoContainer *ApertureList ,QWidget *parent = 0);
    ~EditDCodeDialog();
    
	BoolList	SelectedList;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonCreateDCode_clicked();
    void on_tableWidgetDCode_doubleClicked(const QModelIndex &index);

private:
    Ui::EditDCodeDialog *ui;
};

#endif // EDITDCODEDIALOG_H