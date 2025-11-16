#include "IntegrationChangePhaseResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationChangePhase\IntegrationChangePhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationChangePhase.h"
#include "XAlgorithmBase.h"
#include "XGUIDLL.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationChangePhaseForm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ChangePhase";

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
	(*Base)=new IntegrationReqCurrentPhase	(Base ,sRoot,sName ,-1);
	(*Base)=new IntegrationAckCurrentPhase	(Base ,sRoot,sName ,-1);

	(*Base)=new IntegrationReqEnableExecute	(Base ,sRoot,sName ,-1);
	(*Base)=new IntegrationAckEnableExecute	(Base ,sRoot,sName ,-1);
	(*Base)=new IntegrationSendEnableExecute	(Base ,sRoot,sName ,-1);

	(*Base)=new GUICmdReqEnableExecute		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckEnableExecute		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendEnableExecute		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationChangePhaseForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"MachineCode";
	Data[0].Pointer				 =&((IntegrationChangePhaseForm *)Instance)->MachineCode;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowEnable";
	Data[1].Pointer				 =&((IntegrationChangePhaseForm *)Instance)->ShowEnable;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"AlgoRootToShowEnable";
	Data[2].Pointer				 =&((IntegrationChangePhaseForm *)Instance)->AlgoRootToShowEnable;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"AlgoNameToShowEnable";
	Data[3].Pointer				 =&((IntegrationChangePhaseForm *)Instance)->AlgoNameToShowEnable;

	return(4);
}
DEFFUNCEX	void	DLL_AssociateGUI(RootNameListContainer &List)
{
	List.Add(/**/"Camera",/**/"ChangeQuickProperty");
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationChangePhase.png")));
}