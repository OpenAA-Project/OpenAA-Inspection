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

#ifndef PANELSIMPLEFORM_H
#define PANELSIMPLEFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class PanelSimpleForm;
}

class PanelSimpleForm : public GUIFormBase
{
    Q_OBJECT
    
	GUIFormBase	*VRSOpe;
public:
	int32		StepPulse;

    explicit PanelSimpleForm(LayersBase *base ,QWidget *parent = 0);
    ~PanelSimpleForm();
    
	virtual	void	Prepare(void)	override;
private slots:
    void on_pushButtonUp_clicked();
    void on_pushButtonDown_clicked();
    void on_pushButtonLeft_clicked();
    void on_pushButtonRight_clicked();
    void on_pushButtonOrg_clicked();
    void on_pushButtonHome_clicked();

private:
    Ui::PanelSimpleForm *ui;
};

#endif // PANELSIMPLEFORM_H