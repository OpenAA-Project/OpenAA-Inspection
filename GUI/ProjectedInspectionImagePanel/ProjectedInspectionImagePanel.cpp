#include "ProjectedInspectionImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ProjectedInspectionImagePanel\ProjectedInspectionImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XProjectedInspection.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XPropertyProjectedInspectionPacket.h"
#include "ProjectedInspectionImagePanel.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"ProjectedInspectionImagePanel";
LayersBase *_Base;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ProjectedInspection ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	//(*Base)=new GUICmdReqProjectedInspectionInfoOnPoint	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendProjectedInspectionInfoOnPoint(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	_Base=Base;
	ProjectedInspectionImagePanel	*B=new ProjectedInspectionImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((ProjectedInspectionImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((ProjectedInspectionImagePanel *)Instance)->ImageControlToolsName;
	N++;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/ProjectedInspectionImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ProjectedInspection"));
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
ProjectedInspectionImagePanel::ProjectedInspectionImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ProjectedInspection",QString(sRoot),QString(sName),__Master,parent)
{
	ClickAreaSize=5;
}

void	ProjectedInspectionImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


AlgorithmDrawAttr	*ProjectedInspectionImagePanel::CreateDrawAttrPointer(void)
{
	//GUICmdReqProjectedInspectionDrawMode	DrawMode(GetLayersBase());
	//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyProjectedInspection" ,/**/"");
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&DrawMode);
	//}
	ProjectedInspectionBase	*Ab=(ProjectedInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ProjectedInspection");
	ProjectedInspectionDrawAttr	*A=new ProjectedInspectionDrawAttr(GetLayersBase()
															,Ab->ColorArea,Ab->TransparentLevel
															,Ab->ColorSelected,Ab->TransparentLevel
															,Ab->ColorActive,Ab->TransparentLevel);
	//A->DrawingArea	=DrawMode.DrawingArea;
	return A;
}
void	ProjectedInspectionImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	ProjectedInspectionImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyProjectedInspection" ,/**/"");
	if(GProp!=NULL){
		CmdProjectedInspectionExecuteDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	ProjectedInspectionImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	DataInPage *P=GetLayersBase()->GetPageDataByPoint(globalX ,globalY);
	if(P==NULL)
		return;
	GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
	CmdPacket.TargetPhase=ShowFixedPhase;
	P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
	GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
	CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,RecPacket);
	if(RecPacket.IsReceived()==true){
		ListLayerAndID SelectedItem;
		if(SelectOneItem(globalX ,globalY ,SelectedItem)==true){
			for(AlgorithmItemIndependent *p=RecPacket.IData.Items.GetFirst();p!=NULL;){
				if(p->ItemID!=SelectedItem.ID){
					AlgorithmItemIndependent *NextP=p->GetNext();
					RecPacket.IData.Items.RemoveList(p);
					delete	p;
					p=NextP;
				}
				else{
					p=p->GetNext();
				}
			}
			if(RecPacket.IData.Items.IsEmpty()==false){
				LogicDLL	*L=GetAlgorithmBase()->GetLogicDLL();
				L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,NULL);
			}
		}
	}
}

//=======================================================================
