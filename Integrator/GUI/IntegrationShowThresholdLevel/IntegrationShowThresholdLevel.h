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

#pragma once

#include "integrationshowthresholdlevel_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QWidget>
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class SetThresholdLevelForm;

class IntegrationShowThresholdLevel: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	SetThresholdLevelForm	*SForm;
public:
    IntegrationShowThresholdLevel(LayersBase *Base ,QWidget *parent);
	~IntegrationShowThresholdLevel(void);

	virtual void	ReadyParam(void)	override;
private slots:
	void	ResizeAction();
	void	SlotChangeThresholdLevel(int oldLevel ,int newLevel);
	void    SlotChangeThresholdLevelID(int ThresholdLevelID);
};