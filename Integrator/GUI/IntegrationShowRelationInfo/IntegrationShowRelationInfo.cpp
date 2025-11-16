#include "IntegrationShowRelationInfoResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationShowRelationInfo\IntegrationShowRelationInfo.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationShowRelationInfo.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationShowRelationInfoForm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowRelationInfo";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show relation info");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationShowRelationInfoForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<12)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowMasterID";
	Data[0].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->ShowMasterID;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowMasterName";
	Data[1].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->ShowMasterName;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowLotName";
	Data[3].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->ShowLotName;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowWorkerID";
	Data[4].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->ShowWorkerID;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowWorkerName";
	Data[5].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->ShowWorkerName;

	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"TitleMasterID";
	Data[6].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->TitleMasterID;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"TitleMasterName";
	Data[7].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->TitleMasterName;
	Data[9].Type				 =/**/"QString";
	Data[9].VariableNameWithRoute=/**/"TitleLotName";
	Data[9].Pointer				 =&((IntegrationShowRelationInfoForm *)Instance)->TitleLotName;
	Data[10].Type				 =/**/"QString";
	Data[10].VariableNameWithRoute=/**/"TitleWorkerID";
	Data[10].Pointer			 =&((IntegrationShowRelationInfoForm *)Instance)->TitleWorkerID;
	Data[11].Type				 =/**/"QString";
	Data[11].VariableNameWithRoute=/**/"TitleWorkerName";
	Data[11].Pointer			 =&((IntegrationShowRelationInfoForm *)Instance)->TitleWorkerName;

	Data[12].Type				 =/**/"QFont";
	Data[12].VariableNameWithRoute=/**/"TitleFont";
	Data[12].Pointer			 =&((IntegrationShowRelationInfoForm *)Instance)->TitleFont;
	Data[13].Type				 =/**/"QFont";
	Data[13].VariableNameWithRoute=/**/"DataFont";
	Data[13].Pointer			 =&((IntegrationShowRelationInfoForm *)Instance)->DataFont;
	return(14);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowRelationInfo.png")));
}