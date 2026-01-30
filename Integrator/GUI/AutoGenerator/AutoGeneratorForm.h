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

#ifndef AUTOGENERATORFORM_H
#define AUTOGENERATORFORM_H

#include <QWidget>
#include"XServiceForLayers.h"

namespace Ui {
class AutoGeneratorForm;
}

class AutoGeneratorButtonForm;


class AutoGeneratorForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    AutoGeneratorButtonForm *Parent;

public:
    explicit AutoGeneratorForm(LayersBase *base,AutoGeneratorButtonForm *p ,QWidget *parent = nullptr);
    ~AutoGeneratorForm();

private slots:
    void on_pushButtonAddLine_clicked();
    void on_pushButtonDelLine_clicked();
    void on_pushButtonClearAll_clicked();
    void on_pushButtonSaveList_clicked();
    void on_pushButtonLoadList_clicked();

    void    SlotChangeDXFFileName(int column,int row);
    void    SlotChangePDFFileName(int column,int row);
    void    SlotChangeAlignFileName(int column,int row);
    void    SlotChangeSpecialFileName(int column,int row);
private:
    Ui::AutoGeneratorForm *ui;

    void    ShowGrid(void);
    void    SetGridButton(void);
    void    GetDataFromWindow(void);

    virtual void    closeEvent(QCloseEvent *event)  override;
    virtual void    resizeEvent(QResizeEvent *)     override;
};

#endif // AUTOGENERATORFORM_H