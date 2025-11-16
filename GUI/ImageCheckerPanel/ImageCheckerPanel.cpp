#include "ImageCheckerPanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageCheckerPanel\ImageCheckerPanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ImageCheckerPanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XImageChecker.h"
//#include "ImageControlTools.h"
//#include "XPropertyMaskingPacket.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"ImageCheckerPanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ImageCheckerPanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdSendAlignmentBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddAlignment(QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ImageCheckerPanel	*B=new ImageCheckerPanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	ImageCheckerPanel *InstancePtr=dynamic_cast<ImageCheckerPanel*>((ImageCheckerPanel *)Instance);
	if(InstancePtr!=NULL){
		int	N=InstancePtr->SetPropertyInDLL(Data ,maxDataDim);
		if(N<0)
			return -1;
		Data[N].Type				 =/**/"QString";
		Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
		Data[N].Pointer				 =&((ImageCheckerPanel *)Instance)->ImageControlToolsName;
		N++;
		return(N);
	}
	return -1;
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ImageCheckerPanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ImageChecker"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ImageCheckerPanel::ImageCheckerPanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ImageChecker",QString(sRoot),QString(sName),__Master,parent)
{
}

void	ImageCheckerPanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	ImageCheckerPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	ImageCheckerPanel::DrawEndAfterOperation(FlexArea &area)
{
	IntList LayerList;
	GetActiveLayerList(LayerList);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyImageChecker" ,/**/"");
	if(GProp!=NULL){
		AddAreaPacket	Da(GetLayersBase());
		Da.Area			=area;
		Da.LayerList	=LayerList;
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*ImageCheckerPanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyImageChecker" ,/**/"");
	CmdImageCheckerDrawMode	Da(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ImageChecker");
	if(Ab!=NULL){
		ImageCheckerBase	*M=(ImageCheckerBase *)Ab;
		ImageCheckerDrawAttr	*mattr=new ImageCheckerDrawAttr(
														M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorMask		
								  ,M->NegColorSelected
								  ,Da.Mode);
		return mattr;
	}
	return new ImageCheckerDrawAttr();
}

void ImageCheckerPanel::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	/*
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyImageCheckerForm" ,"");
	if(GProp!=NULL)
		GProp->BuildForShow();
	*/
}

void	ImageCheckerPanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================

