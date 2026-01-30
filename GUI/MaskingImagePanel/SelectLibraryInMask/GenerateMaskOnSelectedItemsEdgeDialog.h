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

#ifndef GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H
#define GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class GenerateMaskOnSelectedItemsEdgeDialog;
}
class SelectLibrariesForAnyType;

class GenerateMaskOnSelectedItemsEdgeDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

    bool    OnChanging;
    SelectLibrariesForAnyType		*Libs;
public:
    explicit GenerateMaskOnSelectedItemsEdgeDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~GenerateMaskOnSelectedItemsEdgeDialog();

    bool	Effective;
    int     Expansion;
    int     InsideDot ;
    int     OutsideDot;
    AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_spinBoxInsideDot_valueChanged(int arg1);
    void on_doubleSpinBoxInsideMM_valueChanged(double arg1);
    void on_spinBoxOutsideDot_valueChanged(int arg1);
    void on_doubleSpinBoxOutsideMM_valueChanged(double arg1);
    void on_ButtonEffective_clicked();
    void on_ButtonNotEffective_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::GenerateMaskOnSelectedItemsEdgeDialog *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // GENERATEMASKONSELECTEDITEMSEDGEDIALOG_H