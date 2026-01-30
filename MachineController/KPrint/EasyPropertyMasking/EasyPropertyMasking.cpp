/*
 * Copyright (C) 2025
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

#include "EasyPropertyMaskingResource.h"

#include "EasyPropertyMasking.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertyMaskingForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertyMasking";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Property Masking");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new IntegrationCmdAutoPickup		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqLibrary		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckLibrary		(Base,sRoot,sName);
	(*Base)=new IntegrationDeleteAllMask		(Base,sRoot,sName);
	(*Base)=new IntegrationDeleteOnlyCADMask	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqMaskCount		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckMaskCount		(Base,sRoot,sName);
	(*Base)=new IntegrationMakeEffectiveFromCAD	(Base,sRoot,sName);
	(*Base)=new IntegrationGenerateOutlineArea	(Base,sRoot,sName);
	(*Base)=new IntegrationCreatePatternEdge	(Base,sRoot,sName);
	(*Base)=new IntegrationSetItemSelection		(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertyMaskingForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return -1;
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((EasyPropertyMaskingForm *)Instance)->SlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertyMasking.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Masking"));
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroDeleteOriginCAD(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate Automatically");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAutomatically;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteOriginCAD";
		Functions[ret].Explain.append(/**/"Delete Origin-CAD mask");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteOriginCAD;
		ret++;
	}
	return ret;
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyMaskingForm	*V=dynamic_cast<EasyPropertyMaskingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->DeleteAutomaticItems();
	GSleep(1000);
	V->GenerateAutomatically();

	return true;
}

static	bool	MacroDeleteOriginCAD(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyMaskingForm	*V=dynamic_cast<EasyPropertyMaskingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->DeleteOriginCAD();

	return true;
}