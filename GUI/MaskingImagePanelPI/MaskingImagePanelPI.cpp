#include "MaskingImagePanelPIResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MaskingImagePanelPI\MaskingImagePanelPI.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MaskingImagePanelPI.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XMaskingPI.h"
#include "ImageControlTools.h"
#include "XPropertyMaskingPIPacket.h"
#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"MaskingImagePIPanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"MaskingImagePanelPI");
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
	MaskingImagePanelPI	*B=new MaskingImagePanelPI(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((MaskingImagePanelPI *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((MaskingImagePanelPI *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MaskingImagePanelPI.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MaskingPI"));
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
MaskingImagePanelPI::MaskingImagePanelPI(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"MaskingPI",QString(sRoot),QString(sName),__Master,parent)
{
}

void	MaskingImagePanelPI::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	MaskingImagePanelPI::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
}

void	MaskingImagePanelPI::DrawEndAfterOperation(FlexArea &area)
{
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(true,GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	D.exec();
	if(DForm->RetOK==false)
		return;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingPIForm" ,/**/"");
	AddMaskingPIAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	Da.LimitedLib	=DForm->GetSelectedList();
	Da.Effective	=DForm->Effective;
	GProp->TransmitDirectly(&Da);
}

void	MaskingImagePanelPI::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingPIForm" ,/**/"");
	if(GProp!=NULL){
		CmdMaskingPIDeleteItemPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*MaskingImagePanelPI::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingPIForm" ,/**/"");
	CmdMaskingPIDrawOnOffPacket	Da(GetLayersBase());
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MaskingPI");
	if(Ab!=NULL){
		MaskingPIBase	*M=(MaskingPIBase *)Ab;
		MaskingPIDrawAttr	*mattr=new MaskingPIDrawAttr(
								   M->ColorMask			,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorMask		
								  ,M->NegColorSelected);
		mattr->EffectiveMode	=Da.Effective;
		mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new MaskingPIDrawAttr();
}

void MaskingImagePanelPI::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyMaskingPIForm" ,/**/"");
	if(GProp!=NULL)
		GProp->BuildForShow();
}

void	MaskingImagePanelPI::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================

