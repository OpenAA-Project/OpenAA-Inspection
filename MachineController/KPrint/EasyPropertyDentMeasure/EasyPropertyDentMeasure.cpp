#include "EasyPropertyDentMeasureResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyPropertyDentMeasure\EasyPropertyDentMeasure.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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
