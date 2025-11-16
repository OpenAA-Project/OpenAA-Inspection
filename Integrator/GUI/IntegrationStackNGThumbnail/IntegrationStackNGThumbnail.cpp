#include "IntegrationStackNGThumbnailResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationStackNGThumbnail\IntegrationStackNGThumbnail.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationStackNGThumbnail.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationStackNGThumbnailForm.h"
#include "XIntegrationStackNGThumbnailPacket.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"StackNGThumbnail";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show stack thumbnails");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new IntegrationStackNGThumbnailForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<12)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->SlaveNo;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"MachineID";
	Data[1].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->MachineID;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"ThumbnailWidth";
	Data[2].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->ThumbnailWidth;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"ThumbnailHeight";
	Data[3].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->ThumbnailHeight;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowInformation";
	Data[4].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->ShowInformation;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowInformationTime";
	Data[5].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->ShowInformationTime;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ShowInformationNumber";
	Data[6].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->ShowInformationNumber;
	Data[7].Type				 =/**/"double";
	Data[7].VariableNameWithRoute=/**/"ZoomRate";
	Data[7].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->ZoomRate;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"MaxXCount";
	Data[8].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->MaxXCount;
	Data[9].Type				 =/**/"int32";
	Data[9].VariableNameWithRoute=/**/"MaxYCount";
	Data[9].Pointer				 =&((IntegrationStackNGThumbnailForm *)Instance)->MaxYCount;
	Data[10].Type				 =/**/"int32";
	Data[10].VariableNameWithRoute=/**/"ScrollerWidth";
	Data[10].Pointer			=&((IntegrationStackNGThumbnailForm *)Instance)->ScrollerWidth;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"ShowRemarkData";
	Data[11].Pointer			 =&((IntegrationStackNGThumbnailForm *)Instance)->ShowRemarkData;
	

	return(12);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationStackNGThumbnail.png")));
}