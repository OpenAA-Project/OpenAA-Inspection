//#include "AlignmentFlexAreaImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentFlexAreaImagePanel\AlignmentFlexAreaImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AlignmentFlexAreaImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "AlignmentFlexAreaImagePropertyPacket.h"
#include "XGeneralFunc.h"
#include "XPacketAlignmentFlexArea.h"
#include "ImagePanelTools.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"AlignmentFlexAreaImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"AlignmentFlexAreaImagePanel");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdReqAlignmentFlexAreaResultInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentFlexAreaResultInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentPointInfo				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentPointInfo				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSetAlignmentPointInfo			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentFlexAreaCheckBitBuff	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentFlexAreaCheckBitBuff	(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlignmentFlexAreaImagePanel	*B=new AlignmentFlexAreaImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	//_CrtCheckMemory();
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((AlignmentFlexAreaImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((AlignmentFlexAreaImagePanel *)Instance)->ImageControlToolsName;
	N++;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/AlignmentFlexAreaImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentFlexArea"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}
