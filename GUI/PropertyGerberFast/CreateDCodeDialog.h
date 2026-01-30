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

#ifndef CREATEDCODEDIALOG_H
#define CREATEDCODEDIALOG_H

#include <QDialog>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGerberFastPacket.h"
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class CreateDCodeDialog;
}

class CreateDCodeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	GerberApertureInfoContainer *ApertureList;
public:
    explicit CreateDCodeDialog(LayersBase *base,GerberApertureInfoContainer *_ApertureList,QWidget *parent = 0);
    ~CreateDCodeDialog();

    int     Page;

	void	InitialForEdit(GerberApertureInfo *p);
	GerberDCodeBase		*CreatedAperture;
private slots:
    void on_comboBoxType_currentIndexChanged(int index);
    void on_pushButtonCreate_clicked();
    void on_pushButtonCancel_clicked();
    void on_doubleSpinBoxCircleDiameterPixel_valueChanged(double arg1);
    void on_doubleSpinBoxCircleDiameterMM_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleWidthPixel_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleWidthMM_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleHeightPixel_valueChanged(double arg1);
    void on_doubleSpinBoxRectangleHeightMM_valueChanged(double arg1);
    void on_doubleSpinBoxObroundWidthPixel_valueChanged(double arg1);
    void on_doubleSpinBoxObroundWidthMM_valueChanged(double arg1);
    void on_doubleSpinBoxObroundHeightPixel_valueChanged(double arg1);
    void on_doubleSpinBoxObroundHeightMM_valueChanged(double arg1);
    void on_doubleSpinBoxPolygonDiameterPixel_valueChanged(double arg1);
    void on_doubleSpinBoxPolygonDiameterMM_valueChanged(double arg1);

private:
    Ui::CreateDCodeDialog *ui;
};

#endif // CREATEDCODEDIALOG_H