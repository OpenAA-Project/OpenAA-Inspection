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

#ifndef ZOOMMECHANICALPANELFORM_H
#define ZOOMMECHANICALPANELFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ZoomMechanicalPanelForm;
}

class SignalOperandFloat;

class ZoomMechanicalPanelForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandFloat	*oValueZ;
	GUIFormBase			*VRSOpe;

public:
	double	MinZoomRate;
	double	MaxZoomRate;
	int32	SysValueZoom;

    explicit ZoomMechanicalPanelForm(LayersBase *base ,QWidget *parent = 0);
    ~ZoomMechanicalPanelForm();

	virtual void	Prepare(void)	override;

private slots:
    void on_verticalSlider_valueChanged(int value);
    void on_pushButtonSetValue_clicked();

private:
    Ui::ZoomMechanicalPanelForm *ui;
};

#endif // ZOOMMECHANICALPANELFORM_H