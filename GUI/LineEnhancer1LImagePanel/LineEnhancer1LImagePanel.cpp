#include "LineEnhancer1LImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LineEnhancer1LImagePanel\LineEnhancer1LImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XLineEnhancer1L.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XPropertyLineEnhancer1LPacket.h"
#include "LineEnhancer1LImagePanel.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"LineEnhancer1LImagePanel";
LayersBase *_Base;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"LineEnhancer1L ImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	//(*Base)=new GUICmdReqLineEnhancer1LInfoOnPoint	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendLineEnhancer1LInfoOnPoint(Base,QString(sRoot),QString(sName));

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
	LineEnhancer1LImagePanel	*B=new LineEnhancer1LImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((LineEnhancer1LImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((LineEnhancer1LImagePanel *)Instance)->ImageControlToolsName;
	N++;

	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	QPixmap	D(/**/":Resources/LineEnhancer1LImagePanel.png");
	return(new QIcon(D));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"LineEnhancer1L"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
LineEnhancer1LImagePanel::LineEnhancer1LImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"LineEnhancer1L",QString(sRoot),QString(sName),__Master,parent)
{
	ClickAreaSize=5;
}

void	LineEnhancer1LImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}


AlgorithmDrawAttr	*LineEnhancer1LImagePanel::CreateDrawAttrPointer(void)
{
	GUICmdReqLineEnhancer1LDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLineEnhancer1L" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}
	LineEnhancer1LBase	*Ab=(LineEnhancer1LBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
	LineEnhancer1LDrawAttr	*A=new LineEnhancer1LDrawAttr(Ab->AreaColor,Ab->TransparentLevel
															,Ab->NegAreaColor,Ab->TransparentLevel
															,Ab->NegAreaColorSelected,Ab->TransparentLevel);
	A->DrawingArea	=DrawMode.DrawingArea;
	return A;
}
void	LineEnhancer1LImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	LineEnhancer1LImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyLineEnhancer1L" ,/**/"");
	if(GProp!=NULL){
		CmdLineEnhancer1LExecuteDrawEnd	Da(GetLayersBase());
		GetActiveLayerList(Da.LayerList);
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	LineEnhancer1LImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
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
