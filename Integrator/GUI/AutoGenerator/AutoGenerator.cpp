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


#include "AutoGenerator.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "XMacroFunction.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include "AutoGeneratorButtonForm.h"
#include "XAutoGenerator.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"AutoGenerator";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for AutoGenerator");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdExecuteAutoGenerator(Base,sRoot,sName);
	//(*Base)	=new IntegrationCmdAckRepeatCount(Base,sRoot,sName);
	//(*Base)	=new IntegrationCmdSetRepeatCount(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new AutoGeneratorButtonForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"DefaultListFileName";
	Data[0].Pointer				 =&((AutoGeneratorButtonForm *)Instance)->DefaultListFileName;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"RegNumberEnableRunning";
	Data[1].Pointer				 =&((AutoGeneratorButtonForm *)Instance)->RegNumberEnableRunning;
	
	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutoGenerator.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	ListContainerData;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERRELATION",/**/"AutoGenerator",ListContainerData);
	Data.AppendList(A);
}

static bool	MacroSetRun(GUIFormBase *Instance ,QStringList &Args);
static bool	MacroSetInspectionRunOnly(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetRun";
		Functions[ret].Explain.append(/**/"Set state of running");
		Functions[ret].ArgName.append(/**/"true(Run)/false(Stop)");
		Functions[ret].DLL_ExcuteMacro	=MacroSetRun;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetInspectionRunOnly";
		Functions[ret].Explain.append(/**/"Set state of InspectionRun");
		Functions[ret].ArgName.append(/**/"true(Run)/false(Stop)");
		Functions[ret].DLL_ExcuteMacro	=MacroSetInspectionRunOnly;
		ret++;
	}
	return ret;
}


static bool	MacroSetRun(GUIFormBase *Instance ,QStringList &Args)
{
	AutoGeneratorButtonForm	*V=dynamic_cast<AutoGeneratorButtonForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()>=1){
		bool	StateRun=false;
		if(Args[0].toUpper()==QString(/**/"TRUE")
		|| Args[0].toUpper()==QString(/**/"RUN")){
			StateRun=true;
		}
		else
		if(Args[0].toUpper()==QString(/**/"false")
		|| Args[0].toUpper()==QString(/**/"STOP")){
			StateRun=false;
		}
		else{
			return false;
		}
		V->SetRun(StateRun);
	}
	return true;
}

static bool	MacroSetInspectionRunOnly(GUIFormBase *Instance ,QStringList &Args)
{
	AutoGeneratorButtonForm	*V=dynamic_cast<AutoGeneratorButtonForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()>=1){
		bool	StateRun=false;
		if(Args[0].toUpper()==QString(/**/"TRUE")
		|| Args[0].toUpper()==QString(/**/"RUN")){
			StateRun=true;
		}
		else
		if(Args[0].toUpper()==QString(/**/"false")
		|| Args[0].toUpper()==QString(/**/"STOP")){
			StateRun=false;
		}
		else{
			return false;
		}
		V->SetInspectionRunOnly(StateRun);
	}
	return true;
}