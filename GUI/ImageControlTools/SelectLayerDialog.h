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

#ifndef SELECTLAYERDIALOG_H
#define SELECTLAYERDIALOG_H

#include <QDialog>
#include <QToolButton>
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLayerDialog;
}

class ImageControlTools;

class SelectLayerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	mtToolButtonColored	**LButtonList;
	int						LNumb;
    ImageControlTools   *Parent;

public:
    explicit SelectLayerDialog(ImageControlTools *p,LayersBase *Base,QWidget *parent = nullptr);
    ~SelectLayerDialog();

private slots:
    void on_pushButtonOK_clicked();
    void LayerClicked(bool checked);
    void on_pushButtonAllON_clicked();
    void on_pushButtonAllOFF_clicked();
    void SlotValueChanged(int value);
private:
    Ui::SelectLayerDialog *ui;

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTLAYERDIALOG_H