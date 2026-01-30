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

#if	!defined(XResultAnalizerDLL_h)
#define	XResultAnalizerDLL_h

#include <QtGui>
#include "XTypeDef.h"
#include "NList.h"
#include <QString>
#include <QIODevice>
#include "XDLLType.h"
#include "XResultAnalizer.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif


class	ResultAnalizerItemBase;

extern	"C"{

DEFFUNCEX	void			DLL_GetName(QString &Root ,QString &Name);
DEFFUNCEX	bool			DLL_GetOrganization(QString &str);
DEFFUNCEX	WORD			DLL_GetDLLType(void);
DEFFUNCEX	WORD			DLL_GetVersion(void);
DEFFUNCEX	const char		*DLL_GetSystemVersion(VersionType vtype);
DEFFUNCEX	void			DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);
DEFFUNCEX	void			DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
DEFFUNCEX	ResultAnalizerItemBase	*DLL_Initial(LayersBase *base);
DEFFUNCEX	void			DLL_Release(ResultAnalizerItemBase *handle);
DEFFUNCEX	bool			DLL_CheckParallelExecution(ModeParallelExecution mode);

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPost(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteCapturedPost			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignmentPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignmentPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessingPost	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevivedPost(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessingPost	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
};

#endif