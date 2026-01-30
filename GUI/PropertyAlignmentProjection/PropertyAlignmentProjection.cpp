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

//#include "AlignmentProjectionFormResource.h"
#include "PropertyAlignmentProjection.h"
#include "PropertyAlignmentProjectionForm.h"
#include "PropertyAlignmentProjectionPacket.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAlignmentProjectionForm";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AlignmentProjection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqAlignmentProjectionPoint			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentProjectionPoint			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentProjectionPointListPack	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentProjectionPointListPack	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentProjectionPutPoint		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentProjectionModifyPoint		(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAlignmentProjectionForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertyAlignmentProjection.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentProjection"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

//	if(MaxBuffer>ret){
//		Functions[ret].FuncName	=/**/"SelectArea";
//		Functions[ret].ArgName.append(/**/"AreaCenterX");
//		Functions[ret].ArgName.append(/**/"AreaCenterY");
//		Functions[ret].Explain.append(/**/"Select area in position");
//		Functions[ret].DLL_ExcuteMacro	=MacroSelectArea;
//		ret++;
//	}

	return ret;
}

