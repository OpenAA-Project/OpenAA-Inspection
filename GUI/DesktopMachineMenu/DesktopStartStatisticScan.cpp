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

#include "DesktopMachineMenuResource.h"

#include "DesktopStartStatisticScan.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


DesktopStartStatisticScan::DesktopStartStatisticScan(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),StartStatisticScanBase(Base)
{
	Counter	=0;
	TotalCount=10;
}

void	DesktopStartStatisticScan::SlotToggled(bool checked)
{
	SlotToggledInside(checked);
}

bool DesktopStartStatisticScan::OnIdle(void)
{
	GUIFormBase::OnIdle();
	StartStatisticScanBase::OnIdleFunc();
	return true;
}

void DesktopStartStatisticScan::OnIdleEnd(void)
{
	Counter++;
	if(Counter<TotalCount){
		SlotToggledInside(true);
	}
}

//==================================================================================================