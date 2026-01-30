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

#ifndef PANELOFFSETVRSFORM_H
#define PANELOFFSETVRSFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandInt;

namespace Ui {
class PanelOffsetVRSForm;
}

class PanelOffsetVRSForm : public GUIFormBase
{
    Q_OBJECT
	SignalOperandInt	*iRegOffsetFrontX;		//Unit:um
	SignalOperandInt	*iRegOffsetFrontY;		
	SignalOperandInt	*iRegOffsetBackX;
	SignalOperandInt	*iRegOffsetBackY;
public:
	int32		OffsetFrontX;					//Unit:um
	int32		OffsetFrontY;
	int32		OffsetBackX;
	int32		OffsetBackY;
	int32		SysRegisterFrontX;
	int32		SysRegisterFrontY;
	int32		SysRegisterBackX;
	int32		SysRegisterBackY;

    explicit PanelOffsetVRSForm(LayersBase *Base ,QWidget *parent = 0);
    ~PanelOffsetVRSForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;

private slots:
    void on_pushButtonSet_clicked();

private:
    Ui::PanelOffsetVRSForm *ui;
};

#endif // PANELOFFSETVRSFORM_H