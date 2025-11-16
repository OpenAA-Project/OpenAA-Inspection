//#include "ShiftMarkImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShiftMarkImagePanel\ShiftMarkImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShiftMarkImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
#include "XShiftMark.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "XPropertyShiftMarkPacket.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ShiftMarkImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"ShiftMarkImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	//new GUICmdReqShiftMarkBmp(QString(sRoot),QString(sName));
	//new GUICmdSendShiftMarkBmp(QString(sRoot),QString(sName));
	//new GUICmdReqAddShiftMark(QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount			(Base ,QString(sRoot) ,QString(sName));

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
	ShiftMarkImagePanel	*B=new ShiftMarkImagePanel(Base,parent);
	B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((ShiftMarkImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				  =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer			  =&((ShiftMarkImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShiftMarkImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ShiftMark"));
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

ShiftMarkImagePanel::ShiftMarkImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"ShiftMark",QString(sRoot),QString(sName),__Master,parent)
{
	connect(this,SIGNAL(TouchItems(ListPageLayerIDPack *)),this,SLOT(SlotTouchItems(ListPageLayerIDPack *)));
}

void	ShiftMarkImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	ShiftMarkImagePanel::SlotTouchItems(ListPageLayerIDPack *ItemInfo)
{
	if(ItemInfo==NULL)
		return;
	CurrentItem=*ItemInfo;
}

void	ShiftMarkImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	__DrawingMode	DMode=GetImageDrawingMode();
	DisplayImageWithAlgorithm::SlotMouseLDown(globalX,globalY);
	if(GetLastHookResult()==false)
		return;
	if(DMode!=_ItemMove){
		IntList PageList;
		GetLayersBase()->GetGlobalPage(globalX,globalY,globalX,globalY,PageList);
		if(PageList.GetCount()>1){
			SelectPages	D(GetLayersBase(),PageList,0);
			if(D.exec()==(int)true){
				PageList=D.SelectedPages;
			}
		}
		//GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyShiftMark" ,/**/"");
		//if(GProp!=NULL){
		//	CmdExecuteMouseLDown	Da(GetLayersBase());
		//	Da.CurrentItem=CurrentItem;
		//	Da.PageList=PageList;
		//	GProp->TransmitDirectly(&Da);
		//}
	}
}

AlgorithmDrawAttr	*ShiftMarkImagePanel::CreateDrawAttrPointer(void)
{
	ShiftMarkBase	*Base=(ShiftMarkBase *)GetAlgorithmBase();
	if(Base!=NULL){
		ShiftMarkDrawAttr	*p=new ShiftMarkDrawAttr(GetLayersBase()
								,Base->ColorShiftMarkNormal		,100
								,Base->ColorShiftMarkSelected	,100
								,Base->ColorShiftMarkActive		,100);
		return p;
	}
	return NULL;
}

void	ShiftMarkImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyShiftMark" ,/**/"");
	ReqItemAddMode	CmdMode(GetLayersBase());
	GProp->TransmitDirectly(&CmdMode);
	
	VectorLineBase	*V=GetVectorLineBase();
	if(V!=NULL && CmdMode.ModeAddLine==true){
		AddLinePacket	Da(GetLayersBase());
		Da.Vector		=V;
		GProp->TransmitDirectly(&Da);
	}
	else if(CmdMode.ModeAddEdge==true || CmdMode.ModeAddMark==true){
		CmdShiftMarkDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		Da.ImagePanelPoint=this;
		GProp->TransmitDirectly(&Da);
	}
}

void	ShiftMarkImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

//=======================================================================


