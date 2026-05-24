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

#include "PropertyAutoAlignmentFormResource.h"
#include "PropertyAutoAlignment.h"
#include "PropertyAutoAlignmentForm.h"
#include "XGUIDLL.h"
#include "XAutoAlignmentPacket.h"
#include "XPropertyAutoAlignmentPacket.h"
#include "XMacroFunction.h"

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAutoAlignment";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return /**/"Show Property for AutoAlignment";
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdCreateAutoAlignmentSheet	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAutoAlignmentInfo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAutoAlignmentInfo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAutoAlignmentSheet		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAutoAlignmentSheet		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetAutoAlignmentShowingState(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddAutoAlignmentSheet		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAutoAlignmentForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAutoAlignment.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearLibList";
		Functions[ret].Explain.append(/**/"Clear all LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroClearLibList;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetLib";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].Explain.append(/**/"Set LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroSetLib;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate blocks");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateBlocks;
		ret++;
	}

	return ret;
}


static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAutoAlignmentForm	*V=dynamic_cast<PropertyAutoAlignmentForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAutoAlignmentForm	*V=dynamic_cast<PropertyAutoAlignmentForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SetLib(LibID);

	return true;
}

static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAutoAlignmentForm	*V=dynamic_cast<PropertyAutoAlignmentForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateBlocks();

	return true;
}