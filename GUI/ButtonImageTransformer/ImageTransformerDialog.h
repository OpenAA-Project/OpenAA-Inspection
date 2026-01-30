/*
 * Copyright (C) 2012
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

#ifndef IMAGETRANSFORMERDIALOG_H
#define IMAGETRANSFORMERDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
    class ImageTransformerDialog;
}

class ImageTransformerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ImageTransformerDialog(LayersBase *Base,QWidget *parent = 0);
    ~ImageTransformerDialog();

	IntList		SelectedPages;
	bool		MasterImage;
	bool		TargetImage;

private slots:
    void on_pushButton_3_clicked();
    void on_pushButtonUpsideDown_clicked();
    void on_pushButtonLeftsideRight_clicked();

private:
    Ui::ImageTransformerDialog *ui;
};

#endif // IMAGETRANSFORMERDIALOG_H