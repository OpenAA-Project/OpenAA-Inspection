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

#include "IntegrationInputLotResource.h"
#include "IntegrationInputLot.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationInputLotForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"InputLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Input integration lot");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new IntegrationCmdInputLot	(Base	,sRoot	,sName	,-1);
	(*Base)=new IntegrationReqInputLot	(Base	,sRoot	,sName	,-1);
	(*Base)=new IntegrationAckInputLot	(Base	,sRoot	,sName	,-1);
	(*Base)=new GUICmdSelectLot			(Base	,sRoot	,sName	,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationInputLotForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<11)
		return(-1);
	Data[0].Type					=/**/"QFont";
	Data[0].VariableNameWithRoute	=/**/"TitleFont";
	Data[0].Pointer					=&((IntegrationInputLotForm *)Instance)->TitleFont;
	Data[1].Type					=/**/"QFont";
	Data[1].VariableNameWithRoute	=/**/"CharFont";
	Data[1].Pointer					=&((IntegrationInputLotForm *)Instance)->CharFont;
	Data[2].Type					=/**/"QFont";
	Data[2].VariableNameWithRoute	=/**/"ButtonFont";
	Data[2].Pointer					=&((IntegrationInputLotForm *)Instance)->ButtonFont;
	Data[3].Type					=/**/"QString";
	Data[3].VariableNameWithRoute	=/**/"TitleLotID";
	Data[3].Pointer					=&((IntegrationInputLotForm *)Instance)->TitleLotID;
	Data[3].Translatable			=true;
	Data[4].Type					=/**/"QString";
	Data[4].VariableNameWithRoute	=/**/"TitleLotNumber";
	Data[4].Pointer					=&((IntegrationInputLotForm *)Instance)->TitleLotNumber;
	Data[4].Translatable			=true;
	Data[5].Type					=/**/"QString";
	Data[5].VariableNameWithRoute	=/**/"TitleSubCode";
	Data[5].Pointer					=&((IntegrationInputLotForm *)Instance)->TitleSubCode;
	Data[5].Translatable			=true;
	Data[6].Type					=/**/"QColor";
	Data[6].VariableNameWithRoute	=/**/"TitleColor";
	Data[6].Pointer					=&((IntegrationInputLotForm *)Instance)->TitleColor;
	Data[7].Type					=/**/"QString";
	Data[7].VariableNameWithRoute	=/**/"ButtonText";
	Data[7].Pointer					=&((IntegrationInputLotForm *)Instance)->ButtonText;
	Data[7].Translatable			=true;
	Data[8].Type					=/**/"QString";
	Data[8].VariableNameWithRoute	=/**/"DefaultLotID";
	Data[8].Pointer					=&((IntegrationInputLotForm *)Instance)->DefaultLotID;
	Data[8].Translatable			=true;
	Data[9].Type					=/**/"QString";
	Data[9].VariableNameWithRoute	=/**/"DefaultLotNumber";
	Data[9].Pointer					=&((IntegrationInputLotForm *)Instance)->DefaultLotNumber;
	Data[9].Translatable			=true;
	Data[10].Type					=/**/"QString";
	Data[10].VariableNameWithRoute	=/**/"DefaultSubCode";
	Data[10].Pointer				=&((IntegrationInputLotForm *)Instance)->DefaultSubCode;
	Data[10].Translatable			=true;

	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationInputLot.png")));
}

static bool	MacroRegisterLot(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RegisterLot";
		Functions[ret].ArgName.append(/**/"Lot ID");
		Functions[ret].ArgName.append(/**/"Lot number");
		Functions[ret].ArgName.append(/**/"Lot subcode");
		Functions[ret].Explain.append(/**/"Register Lot");
		Functions[ret].DLL_ExcuteMacro	=MacroRegisterLot;
		ret++;
	}
	return ret;
}


static bool	MacroRegisterLot(GUIFormBase *Instance ,QStringList &Args)
{
	IntegrationInputLotForm	*V=dynamic_cast<IntegrationInputLotForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()>=3){
		QString	LotID	=Args[0];
		QString	LotNumber	 =Args[1];
		QString	LotSubcode=Args[2];

		V->RegisterLot(LotID,LotNumber,LotSubcode);
	}
	return true;
}