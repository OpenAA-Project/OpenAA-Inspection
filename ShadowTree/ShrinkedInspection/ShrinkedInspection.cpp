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

#include "XShadowControlDLL.h"
#include "ShrinkedInspection.h"
#include "ShadowSettingDialog.h"

WORD		DLL_GetDLLType(void)
{
	return DLLShadowControl;
}

bool		DLL_GetName(QString &str)
{
	str="ShrinkedInspection";
	return true;
}
WORD		DLL_GetVersion(void)
{
	return  1;
}
const char	*DLL_GetExplain(void)
{
	return "Shrinked inspection";
}
void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
}
bool		DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString="Copyright(c) MEGATRADE 2021.12";
	return true;
}

ShadowTree	*DLL_Initial(int ShadowNumber,LayersBase *ParentBase
						,const QString &GlobalParamFileName
						,const QString &GUIFileName)
{
	return new ShrinkedInspection(ShadowNumber,ParentBase);
}
bool		DLL_Close(ShadowTree *handle)
{
	delete	handle;
	return true;
}
bool		DLL_ShowSetting(ShadowTree *handle, QWidget *parent)
{
	ShrinkedInspection	*h=dynamic_cast<ShrinkedInspection *>(handle);
	if(h!=NULL){
		ShadowSettingDialog	D(h);
		if(D.exec()==true){
			return true;
		}
	}
	return false;
}

//================================================================