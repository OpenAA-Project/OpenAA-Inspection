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

#include "ResultCategorizer.h"
#include "XResultAnalizerDLL.h"
#include "XLanguageClass.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XPointer.h"
#include "XResult.h"
#include "swap.h"

const	char	*sRoot=/**/"ResultAnalizer";
const	char	*sName=/**/"ResultCategorizer";

DEFFUNCEX	void	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
}

DEFFUNCEX	bool	DLL_GetOrganization(QString &str)
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	WORD	DLL_GetVersion(void)
{
	return 1;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangLibSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	ResultAnalizerItemBase	*DLL_Initial(LayersBase *base)
{
	return new ResultCategorizer(base);
}
DEFFUNCEX	void			DLL_Release(ResultAnalizerItemBase *handle)
{
	delete	handle;
}
DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	ResultCategorizer	*d=(ResultCategorizer *)handle;
	d->Allocate();
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	ResultCategorizer	*d=(ResultCategorizer *)handle;
	d->ExecuteStartByInspection();
	return _ER_true;
}
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res)
{
	ResultCategorizer	*d=(ResultCategorizer *)handle;
	return d->Execute(Res);
}