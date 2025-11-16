//#include "IntegrationStackMultiNGThumbnailResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationStackMultiNGThumbnail\IntegrationStackMultiNGThumbnail.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationStackMultiNGThumbnail.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationStackMultiNGThumbnailForm.h"
#include "XIntegrationStackNGThumbnailPacket.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"StackMultiNGThumbnail";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show stack multiple thumbnails");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdUpdateThreshold(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdReqLearningMenu(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdAckLearningMenu(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdReqItemInfo	(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdAckItemInfo	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationStackMultiNGThumbnailForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"ThumbnailWidth";
	Data[0].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ThumbnailWidth;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"ThumbnailHeight";
	Data[1].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ThumbnailHeight;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowInformation";
	Data[2].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ShowInformation;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowInformationTime";
	Data[3].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ShowInformationTime;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowInformationNumber";
	Data[4].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ShowInformationNumber;
	Data[5].Type				 =/**/"double";
	Data[5].VariableNameWithRoute=/**/"ZoomRate";
	Data[5].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ZoomRate;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"MaxXCount";
	Data[6].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->MaxXCount;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"MaxYCount";
	Data[7].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->MaxYCount;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"ScrollerWidth";
	Data[8].Pointer				 =&((IntegrationStackMultiNGThumbnailForm *)Instance)->ScrollerWidth;

	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationStackMultiNGThumbnail.png")));
}