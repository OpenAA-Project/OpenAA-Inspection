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

#include "ColorDifferenceResource.h"
#include "PropertyColorDifference.h"
#include "PropertyColorDifferenceForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include <QIcon>
#include <QPixmap>
#include "XPropertyColorDifferencePacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAddColorOK(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAddColorNG(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroRegistInFlowON(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroRegistInFlowOFF(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetStatisticThreshold(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearFlowStack(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAutoGenerate(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyColorDifference";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for ColorDifference Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualColorDifference			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendModifySelectedColorDifference		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSelectedColorDifferenceItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new	GUICmdSendSelectedColorDifferenceItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqColorDifferenceInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendColorDifferenceInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqColorDifferenceFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckColorDifferenceFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqSetButtonMode					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckItemListForPageContainer			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdAddColorDifferenceOK					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAddColorDifferenceNG					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdRegistInFlowON						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdRegistInFlowOFF						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetStatisticThreshold					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClearFlowStack						(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqFlowData							(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckFlowData							(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendFlowData							(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAutoGenerate							(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetRegulation							(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"ColorDifference");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyColorDifferenceForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyColorDifference.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ColorDifference"));
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
		Functions[ret].FuncName	=/**/"AddColorOK";
		Functions[ret].Explain.append(/**/"Add target image color as OK");
		Functions[ret].DLL_ExcuteMacro	=MacroAddColorOK;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AddColorNG";
		Functions[ret].Explain.append(/**/"Add target image color as NG");
		Functions[ret].DLL_ExcuteMacro	=MacroAddColorNG;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RegistInFlowON";
		Functions[ret].Explain.append(/**/"Mode to regist as ON");
		Functions[ret].DLL_ExcuteMacro	=MacroRegistInFlowON;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RegistInFlowOFF";
		Functions[ret].Explain.append(/**/"Mode to regist as OFF");
		Functions[ret].DLL_ExcuteMacro	=MacroRegistInFlowOFF;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetStatisticThreshold";
		Functions[ret].ArgName.append(/**/"SigmaH");
		Functions[ret].ArgName.append(/**/"SigmaS");
		Functions[ret].ArgName.append(/**/"SigmaV");
		Functions[ret].Explain.append(/**/"Set statistic threshold");
		Functions[ret].DLL_ExcuteMacro	=MacroSetStatisticThreshold;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearFlowStack";
		Functions[ret].Explain.append(/**/"Clear FlowStack");
		Functions[ret].DLL_ExcuteMacro	=MacroClearFlowStack;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoGenerate";
		Functions[ret].Explain.append(/**/"Auto Generate blocks");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoGenerate;
		ret++;
	}	
	return ret;
}

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
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

static	bool	MacroAddColorOK(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->AddColor(true);

	return true;
}

static	bool	MacroAddColorNG(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->AddColor(false);

	return true;
}

static	bool	MacroRegistInFlowON(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SetRegistInFlow(true);

	return true;
}

static	bool	MacroRegistInFlowOFF(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SetRegistInFlow(false);

	return true;
}

static	bool	MacroSetStatisticThreshold(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	double	SigmaH=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	SigmaS=Args[1].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	SigmaV=Args[2].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->SetStatisticThreshold(SigmaH,SigmaS,SigmaV);

	return true;
}

static	bool	MacroClearFlowStack(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearFlowStack();

	return true;
}
static	bool	MacroAutoGenerate(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyColorDifferenceForm	*V=dynamic_cast<PropertyColorDifferenceForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->AutoGenerate(LibID);

	return true;
}