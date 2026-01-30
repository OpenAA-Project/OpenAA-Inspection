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

#include "XDataInLayer.h"
#include "Regulus64Version.h"
#include <QtGlobal>
#include "XFilterDLL.h"
#include "XFilterClass.h"
#include "XDLLType.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}
WORD	DLL_GetDLLType(void)
//	return	DLL type for FilterDLL
{
	return(DLLFilterMode);
}

bool		DLL_Close(void *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	FilterClassBase	*hBase=(FilterClassBase *)handle;
	delete	hBase;
	return true;
}
DEFFUNCEX	void	DLL_ExecuteBeforeScan	(FilterClassBase *handle)
//	Execute something image before scanning
{
	handle->ExecuteBeforeScan();
}