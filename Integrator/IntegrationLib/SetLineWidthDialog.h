/*
 * Copyright (C) 2024
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

#ifndef SETLINEWIDTHDIALOG_H
#define SETLINEWIDTHDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"

namespace Ui {
class SetLineWidthDialog;
}

class SetLineWidthDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int SlaveNo;
    bool    ReEntrant;
public:
    explicit SetLineWidthDialog(LayersBase *base,int SlaveNo
                                ,int _LineWidth,QWidget *parent = nullptr);
    ~SetLineWidthDialog();

    int LineWidth;
private slots:
    void on_spinBoxLineWidth_valueChanged(int arg1);
    void on_doubleSpinBoxLineWidthMM_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SetLineWidthDialog *ui;
};

#endif // SETLINEWIDTHDIALOG_H