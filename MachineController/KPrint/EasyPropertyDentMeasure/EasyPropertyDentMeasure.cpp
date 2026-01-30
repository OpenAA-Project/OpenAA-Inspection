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

#include "EasyPropertyDentMeasureResource.h"

#include "EasyPropertyDentMeasure.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertyDentMeasureForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertyDentMeasure";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy property for Dent-Measure inspection");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdGenerateDentAndMeasure(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqCorrectValues		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckCorrectValues		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetCorrectValues		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetMeasureEndPoint	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetOnlyBladeThreshold	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdFilm					(Base,sRoot,sName);
	(*Base)=new IntegrationReqMeasurePosition		(Base,sRoot,sName);
	(*Base)=new IntegrationAckMeasurePosition		(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertyDentMeasureForm(Base,parent));
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
	Data[0].Pointer			  =&((EasyPropertyDentMeasureForm *)Instance)->SlaveNo;

	return(1);
}
DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	Array0;
	GuiAdditionalDatabase	*A0=new GuiAdditionalDatabase(/**/"MASTERRELATION",/**/"DentMeasureBlade0",Array0);
	Data.AppendList(A0);

	QByteArray	Array1;
	GuiAdditionalDatabase	*A1=new GuiAdditionalDatabase(/**/"MASTERRELATION",/**/"DentMeasureBlade1",Array1);
	Data.AppendList(A1);

	QByteArray	Array2;
	GuiAdditionalDatabase	*A2=new GuiAdditionalDatabase(/**/"MASTERRELATION",/**/"DentMeasureBlade2",Array2);
	Data.AppendList(A2);

	QByteArray	Array3;
	GuiAdditionalDatabase	*A3=new GuiAdditionalDatabase(/**/"MASTERRELATION",/**/"DentMeasureBlade3",Array3);
	Data.AppendList(A3);
}
DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertyDentMeasure.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate Automatically");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAutomatically;
		ret++;
	}
	return ret;
}

static	bool	MacroGenerateAutomatically(GUIFormBase *Instance ,QStringList &Args)
{
	EasyPropertyDentMeasureForm	*V=dynamic_cast<EasyPropertyDentMeasureForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateAutomatically();

	return true;
}