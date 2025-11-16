/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegulusWorldGUI\RWCamRecognitionImagePanel\RWCamRecognitionImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "RWCamRecognitionImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
//#include "ImageControlTools.h"
#include "XRWCamRecognition.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
//#include "XPropertyRWCamRecognitionPacket.h"

const	char	*sRoot=/**/"RegulusWorld";
const	char	*sName=/**/"RWCamRecognitionImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"RWCamRecognitionImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdReqItemIndependentPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendIndependentPack		(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	RWCamRecognitionImagePanel	*B=new RWCamRecognitionImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((RWCamRecognitionImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((RWCamRecognitionImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/RWCamRecognitionImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"RegulusWorld",/**/"CamRecognition"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

RWCamRecognitionImagePanel::RWCamRecognitionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"RegulusWorld" ,/**/"CamRecognition",QString(sRoot),QString(sName),__Target,parent)
{
}

void	RWCamRecognitionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*RWCamRecognitionImagePanel::CreateDrawAttrPointer(void)
{
	RWCamRecognitionDrawAttr	*A=new RWCamRecognitionDrawAttr();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"RegulusWorld" ,/**/"PropertyCamRecognition" 											,/**/"");
	if(GProp!=NULL){
		//CmdRWCamRecognitionDrawAttr	Da(GetLayersBase());
		//GProp->TransmitDirectly(&Da);
		//A->BlockColor0=Da.BlockColor0;
		//A->BlockColor1=Da.BlockColor1;
		//A->BlockColor2=Da.BlockColor2;
		//A->BlockColor3=Da.BlockColor3;
		//A->BlockColor4=Da.BlockColor4;
		//A->BlockColor5=Da.BlockColor5;
		//A->BlockColor6=Da.BlockColor6;
		//A->BlockColor7=Da.BlockColor7;
	}
	return A;
}

void	RWCamRecognitionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"RegulusWorld" ,/**/"PropertyCamRecognition" 											,/**/"");
	//if(GProp!=NULL){
	//	GUICmdRWCamRecognitionDrawEnd	Da(GetLayersBase());
	//	Da.Area=area;
	//	GProp->TransmitDirectly(&Da);
	//}
}

void	RWCamRecognitionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
