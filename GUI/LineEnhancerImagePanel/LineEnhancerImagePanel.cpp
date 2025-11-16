#include "LineEnhancerImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LineEnhancerImagePanel\LineEnhancerImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LineEnhancerImagePanel.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
//#include "XLineEnhancerPacket.h"
#include "LineEnhancerImagePanel.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LineEnhancerImagePanel";
//LayersBase *_Base;

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"LineEnhancer ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	//(*Base)=new GUICmdReqLineEnhancerInfoOnPoint	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendLineEnhancerInfoOnPoint(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	//_Base=Base;
	LineEnhancerImagePanel	*B=new LineEnhancerImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((LineEnhancerImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((LineEnhancerImagePanel *)Instance)->ImageControlToolsName;
	N++;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/LineEnhancerImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"LineEnhancer"));
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
LineEnhancerImagePanel::LineEnhancerImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"LineEnhancer",QString(sRoot),QString(sName),__Master,parent)
{
	ClickAreaSize=5;
}

void	LineEnhancerImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

AlgorithmDrawAttr	*LineEnhancerImagePanel::CreateDrawAttrPointer(void)
{
	GUICmdReqLineEnhancerDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLineEnhancer" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	LineEnhancerDrawAttr	*A=new LineEnhancerDrawAttr();
	A->DrawingArea	=DrawMode.DrawingArea;
	return A;
}
void	LineEnhancerImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	LineEnhancerImagePanel::ExecuteDrawEnd(FlexArea &Area)
{
	//GUIFormBase	*GProp=GetLayersBase()->FindByName("Button" ,"PropertyLineEnhancer" ,"");
	//if(GProp!=NULL){
	//	CmdLineEnhancerExecuteDrawEnd	RCmd;
	//	RCmd.GlobalArea=Area;
	//	GProp->TransmitDirectly(&RCmd);
	//}
}
void	LineEnhancerImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
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
