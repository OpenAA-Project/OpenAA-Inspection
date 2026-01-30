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

#ifndef GENERATEPATTERNEDGEONSELECTEDDIALOG_H
#define GENERATEPATTERNEDGEONSELECTEDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"
namespace Ui {
class GeneratePatternEdgeOnSelectedDialog;
}
class SelectLibrariesForAnyType;

class GeneratePatternEdgeOnSelectedDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    bool    OnChanging;
    SelectLibrariesForAnyType		*Libs;
public:
    explicit GeneratePatternEdgeOnSelectedDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~GeneratePatternEdgeOnSelectedDialog();

    int     BoundaryDiff;
    bool	Effective;
    int     WidthDot ;
    AlgorithmLibraryListContainer		GetSelectedList(void);

private slots:
    void on_ButtonEffective_clicked();
    void on_ButtonNotEffective_clicked();
    void on_ButtonCancel_clicked();

    void on_spinBoxWidthDot_valueChanged(int arg1);
    void on_doubleSpinBoxWidthMM_valueChanged(double arg1);

private:
    Ui::GeneratePatternEdgeOnSelectedDialog *ui;

    virtual	void resizeEvent(QResizeEvent *event)	override;
};

#endif // GENERATEPATTERNEDGEONSELECTEDDIALOG_H