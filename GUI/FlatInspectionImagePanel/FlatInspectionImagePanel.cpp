//#include "FlatInspectionImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\FlatInspectionImagePanel\FlatInspectionImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "FlatInspectionImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyFlatInspectionPacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"FlatInspectionImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"FlatInspectionImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	FlatInspectionImagePanel	*B=new FlatInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((FlatInspectionImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((FlatInspectionImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/FlatInspectionImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"FlatInspection"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
//{
//	LangSolver.SetLanguage(Pkg,LanguageCode);
//}

//====================================================================================

FlatInspectionImagePanel::FlatInspectionImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"FlatInspection",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	FlatInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


AlgorithmDrawAttr	*FlatInspectionImagePanel::CreateDrawAttrPointer(void)
{
	FlatInspectionBase	*Base=(FlatInspectionBase *)GetAlgorithmBase();
	if(Base!=NULL){
		FlatInspectionDrawAttr	*d=new FlatInspectionDrawAttr(GetLayersBase()
											,Base->ColorArea		,100
											,Base->ColorSelected	,100
											,Base->ColorActive		,100);
		CmdReqFIT_Type	Cmd(GetLayersBase());
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyFlatInspection" ,/**/"");
		if(GProp!=NULL){
			GProp->TransmitDirectly(&Cmd);
			d->FIT_Type		=Cmd.FIT_Type;
			d->ShowMaskMap	=Cmd.ShowMaskMap;
		}
		return d;
	}
	return NULL;
}

void	FlatInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyFlatInspection" ,/**/"");
	if(GProp!=NULL){
		CmdFlatInspectionDrawEnd	Da(GetLayersBase());
		//GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}

void	FlatInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


