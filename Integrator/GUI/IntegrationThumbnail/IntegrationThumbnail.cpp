#include "IntegrationThumbnailResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationThumbnail\IntegrationThumbnail.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationThumbnail.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationThumbnailForm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"Thumbnail";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show thumbnail");
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
	return(new IntegrationThumbnailForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"ShownMachineCode";
	Data[0].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ShownMachineCode;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"ShownPhase";
	Data[1].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ShownPhase;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowMaster";
	Data[2].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ShowMaster;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"ThumbnailWidth";
	Data[3].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ThumbnailWidth;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"ThumbnailHeight";
	Data[4].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ThumbnailHeight;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowInformation";
	Data[5].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ShowInformation;
	Data[6].Type				 =/**/"double";
	Data[6].VariableNameWithRoute=/**/"ZoomRate";
	Data[6].Pointer				 =&((IntegrationThumbnailForm *)Instance)->ZoomRate;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationThumbnail.png")));
}