//#include "Process3DImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\Process3DImagePanel\Process3DImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "Process3DImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "ImageControlTools.h"
#include "XProcess3D.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"Process3DImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Process3DImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//(*Base)=new GUICmdPickupTestList(Base,QString(sRoot),QString(sName));

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
	Process3DImagePanel	*B=new Process3DImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((Process3DImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((Process3DImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/Process3DImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Process3D"));
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

Process3DImagePanel::Process3DImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Process3D",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	Process3DImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	Process3DImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	Process3DImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	DisplayImageWithAlgorithm::SlotMouseLDown(globalX,globalY);
	if(GetLastHookResult()==false)
		return;
	IntList PageList;
	GetLayersBase()->GetGlobalPage(globalX,globalY,globalX,globalY,PageList);
	if(PageList.GetCount()>1){
		SelectPages	D(GetLayersBase(),PageList,0);
		if(D.exec()==(int)true){
			PageList=D.SelectedPages;
		}
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyProcess3D" ,/**/"");
	if(GProp!=NULL){
		CmdExecuteMouseLDown	Da(GetLayersBase());
		Da.CurrentItem=CurrentItem;
		Da.PageList=PageList;
		GProp->TransmitDirectly(&Da);
	}
}

AlgorithmDrawAttr	*Process3DImagePanel::CreateDrawAttrPointer(void)
{
	Process3DBase	*Base=(Process3DBase *)GetAlgorithmBase();
	if(Base!=NULL){
		return new Process3DDrawAttr(GetLayersBase()
								,Base->Process3DNormal		,100
								,Base->Process3DSelected	,100
								,Base->Process3DActive		,100
								,80
								,Base->BlockColor0
								,Base->BlockColor1
								,Base->BlockColor2
								,Base->BlockColor3
								,Base->BlockColor4
								,Base->BlockColor5
								,Base->BlockColor6
								,Base->BlockColor7);
	}
	return NULL;
}

void	Process3DImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyProcess3D" ,/**/"");
	if(GProp!=NULL){
		CmdProcess3DDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		GetActiveLayerList(Da.LayerList);
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}
void	Process3DImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdProcess3DDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyProcess3D" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);
	}
}

void	Process3DImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

