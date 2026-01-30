/*
 * Copyright (C) 2015
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

#ifndef LOADAUTOSAVEIMAGEDIALOG_H
#define LOADAUTOSAVEIMAGEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAutoSaveImage.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class LoadAutoSaveImageDialog;
}

class LoadAutoSaveImageDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit LoadAutoSaveImageDialog(LayersBase *base ,QWidget *parent = 0);
    ~LoadAutoSaveImageDialog();

	BandImageFileContainer	FoundFile;
	BandImageFileList		*Selected;

private slots:
    void on_checkBoxAllDrives_clicked();
    void on_pushButtonStartSearch_clicked();
    void on_tableWidgetFound_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::LoadAutoSaveImageDialog *ui;
};


#endif // LOADAUTOSAVEIMAGEDIALOG_H