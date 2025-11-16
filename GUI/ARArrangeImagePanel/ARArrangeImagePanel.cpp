#include "ARArrangeImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ARArrangeImagePanel\ARArrangeImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ARArrangeImagePanel.h"

#include "XCrossObj.h"
#include "XGUI.h"
#include "XARArrange.h"
#include "ImageControlTools.h"
#include "XGeneralDialog.h"
#include "ImagePanelTools.h"
#include "XPropertyARArrangePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"ARArrange";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ARArrangePanel");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}


DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	ARArrangeImagePanel	*B=new ARArrangeImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((ARArrangeImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((ARArrangeImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ARArrangeImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ARArrange"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
ARArrangeImagePanel::ARArrangeImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ARArrange",QString(sRoot),QString(sName),__Master,parent)
{
}

void	ARArrangeImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


void	ARArrangeImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyARArrange" ,/**/"");
	if(GProp!=NULL){
		GUICmdARArrangeDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}


AlgorithmDrawAttr	*ARArrangeImagePanel::CreateDrawAttrPointer(void)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ARArrange");
//	if(Ab!=NULL){
//		ARArrangeBase	*M=(ARArrangeBase *)Ab;
//		ARArrangeDrawAttr	*mattr=new ARArrangeDrawAttr(
//									   M->ColorVCut			,M->TransparentLevel
//									  ,M->ColorSelected		,M->TransparentLevel
//									  ,M->ColorActive		,M->TransparentLevel);
//		return mattr;
//	}
	//return new ARArrangeDrawAttr();
	return NULL;
}


void	ARArrangeImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}
//=======================================================================


