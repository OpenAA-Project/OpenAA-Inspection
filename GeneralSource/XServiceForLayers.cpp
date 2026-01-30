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

#include "XTypeDef.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XShadowTree.h"

LayersBase		*ServiceForLayers::GetTreeTopLayersBase(void)	const
{
	return Base->GetTopLayersBase();
}
int	ServiceForLayers::GetDotPerLine(int page)	const	{	return Base->GetDotPerLine(page);	}
int	ServiceForLayers::GetMaxLines(int page)		const	{	return Base->GetMaxLines(page);		}
int	ServiceForLayers::GetPageNumb(void)			const	{	return Base->GetPageNumb();			}
int	ServiceForLayers::GetPhaseNumb(void)		const	{	return Base->GetPhaseNumb();		}
int	ServiceForLayers::GetLayerNumb(int page)	const	{	return Base->GetLayerNumb(page);	}
bool	ServiceForLayers::IsValid(int page ,int layer)	const
{
	return GetParamGlobal()->IsValid(page ,layer);
}

int	ServiceForLayers::GetCountAllMasterBuff(void)		const	{	return GetLayersBase()->GetCountAllMasterBuff();		}
int	ServiceForLayers::GetCountOnlyMasterBuff(void)		const	{	return GetLayersBase()->GetCountOnlyMasterBuff();		}
int	ServiceForLayers::GetCountDispatchMasterBuff(void)	const	{	return GetLayersBase()->GetCountDispatchMasterBuff();	}

ParamGlobal	*ServiceForLayers::GetParamGlobal(void)		const	{	return (Base==NULL)?NULL:Base->GetParamGlobal();	}
ParamComm	*ServiceForLayers::GetParamComm(void)		const	{	return (Base==NULL)?NULL:Base->GetParamComm();	}
ParamGUI	*ServiceForLayers::GetParamGUI(void)		const	{	return (Base==NULL)?NULL:Base->GetParamGUI();	}
EntryPointBase	*ServiceForLayers::GetEntryPoint(void)	const	{	return (Base==NULL)?NULL:Base->GetEntryPoint();	}
int		ServiceForLayers::GetCurrentShadowLevel(void)	const	{	return (Base==NULL)?0:Base->ShadowTree::GetShadowLevel();	}
//----------- Unit-------------
	
bool	ServiceForLayers::IsUnitMode(void)
{
	return GetParamGlobal()->IsUnitMode();
}

double	ServiceForLayers::TransformPixelToUnit(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnit(Page,pixel);
}

double	ServiceForLayers::TransformUnitToPixel(int Page,double unit)
{
	return GetParamGlobal()->TransformUnitToPixel(Page,unit);
}

QString	ServiceForLayers::TransformPixelToUnitStr(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitStr(Page,pixel);
}

QString	ServiceForLayers::GetUnitStr(double unit)
{
	return GetParamGlobal()->GetUnitStr(unit);
}

double	ServiceForLayers::TransformPixelToUnitSquare(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquare(Page,pixel);
}

double	ServiceForLayers::TransformUnitToPixelSquare(int Page,double unit)
{
	return GetParamGlobal()->TransformUnitToPixelSquare(Page,unit);
}

QString	ServiceForLayers::TransformPixelToUnitSquareStr(int Page,double pixel)
{
	return GetParamGlobal()->TransformPixelToUnitSquareStr(Page,pixel);
}

QString	ServiceForLayers::GetUnitSquareStr(double unit)
{
	return GetParamGlobal()->GetUnitSquareStr(unit);
}
void	ServiceForLayers::InstallOperationLog(QObject *window)
{
	if(GetLayersBase()!=NULL){
		GetLayersBase()->InstallOperationLog(window);
	}
}