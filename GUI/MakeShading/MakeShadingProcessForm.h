/*
 * Copyright (C) 2022
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

#ifndef MAKESHADINGPROCESSFORM_H
#define MAKESHADINGPROCESSFORM_H

#include <QWidget>
#include <QPainter>
#include "XServiceForLayers.h"
#include "XDisplayImage.h"

namespace Ui {
class MakeShadingProcessForm;
}
class MakeShading;

class MakeShadingProcessForm : public QWidget ,public ServiceForLayers
{
    Q_OBJECT
    
    MakeShading *Parent;
    DisplayImage   ImagePanel;
    FlexArea        ShadingArea;

public:
    explicit MakeShadingProcessForm(LayersBase *base,MakeShading *p,QWidget *parent = 0);
    ~MakeShadingProcessForm();
    
private slots:
    void on_pushButtonRegist_clicked();
    void	SlotDrawEndAfterOperation(FlexArea &area);
    void	SlotDrawFunc(QPainter &pnt ,QImage &PntImage ,const IntList &_LayerList);
    void on_pushButtonStartCapture_clicked();
    void on_toolButtonDown_clicked();
    void on_toolButtonUp_clicked();
    void on_spinBoxMinX_valueChanged(int arg1);
    void on_spinBoxMaxX_valueChanged(int arg1);
    void on_comboBoxCurrentPage_currentIndexChanged(int index);

private:
    Ui::MakeShadingProcessForm *ui;

    virtual	void showEvent(QShowEvent *event)       override;
	virtual	void resizeEvent(QResizeEvent *event)   override;
    virtual	void closeEvent(QCloseEvent *event)     override;
};

#endif // MAKESHADINGPROCESSFORM_H