//#include "OCRImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\OCRImagePanel\OCRImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OCRImagePanel.h"
#include "XCrossObj.h"
#include "XOCRInspection.h"
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"OCRImagePanel";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"OCR ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdPickupTestList(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	OCRImagePanel	*B=new OCRImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((OCRImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute =/**/"ImageControlToolsName";
	Data[N].Pointer			  	=&((OCRImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/OCRImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"OCRInspection"));
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

OCRImagePanel::OCRImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"OCRInspection",QString(sRoot),QString(sName),__Target,parent)
{
}

void	OCRImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*OCRImagePanel::CreateDrawAttrPointer(void)
{
	OCRInspectionBase	*Base=(OCRInspectionBase *)GetAlgorithmBase();
	if(Base!=NULL){
		OCRInspectionDrawAttr	*r=new OCRInspectionDrawAttr(Base->ColorOCR			,Base->TransparentLevel
															,Base->ColorSelected	,Base->TransparentLevel
															,Base->ColorActive		,Base->TransparentLevel
															,Base->NegColorOCR		,Base->NegColorSelected);
		//GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyOCR" ,"");
		//if(GProp!=NULL){
		//	OCRInspectionDrawAttr	Da;
		//	GProp->TransmitDirectly(&Da);
		//}
		return r;
	}
	return NULL;
}

void	OCRImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyOCR" ,/**/"");
	if(GProp!=NULL){
		CmdOCRInspectionDrawPacket	Da(GetLayersBase());
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}
void	OCRImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
