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

#ifndef CONFIRMLAYERSDIALOG_H
#define CONFIRMLAYERSDIALOG_H

#include <QDialog>
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XGUIGerberPacket.h"
#include "XServiceForLayers.h"

namespace Ui {
class ConfirmLayersDialog;
}

class	PropertyGerberFastForm;
class	GerberLayerListOnScreen;
class	GerberCompositeLayerListOnScreen;

class ConfirmLayersDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	PropertyGerberFastForm	*Parent;
	bool					CompositeMode;
	GerberLayerListOnScreen				*IndexChild[MaxGerberLayer];
	GerberCompositeLayerListOnScreen	*IndexCompChild[MaxGerberLayer];

public:
    explicit ConfirmLayersDialog(PropertyGerberFastForm *p,bool CompositeMode ,QWidget *parent = 0);
    ~ConfirmLayersDialog();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonClearAll_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ConfirmLayersDialog *ui;
};

#endif // CONFIRMLAYERSDIALOG_H