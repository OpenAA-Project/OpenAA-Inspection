#include "AutoSaveImageViewPanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AutoSaveImageViewPanel\AutoSaveImageViewPanel.cpp
** Author : YYYYYYYYYY
*******************************************************************************/

#include "AutoSaveImageViewPanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XNaming.h"
#include "ImageControlTools.h"
#include "XPropertyNamingPacket.h"
#include "XAutoSaveImagePacket.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"
#include "XDisplayImagePacket.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"AutoSaveImageViewPanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"AutoSaveImageViewPanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);
	DisplayImageWithAlgorithm::InitialDisplayImageWithAlgorithmInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	(*Base)=new GUICmdReqSelectedItemCount	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendSelectedItemCount	(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AutoSaveImageViewPanel	*B=new AutoSaveImageViewPanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((AutoSaveImageViewPanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((AutoSaveImageViewPanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/AutoSaveImageViewPanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoSaveImage"));
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
AutoSaveImageViewPanel::AutoSaveImageViewPanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"AutoSaveImage",QString(sRoot),QString(sName),__Master,parent)
{
	nStartX = -1;
	nStartY = -1;
	nWidth = -1;
	nHeight = -1;
}

void	AutoSaveImageViewPanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	AutoSaveImageViewPanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);

	CmdPanelParam *CmdPanelParamVar=dynamic_cast<CmdPanelParam *>(packet);
	if(CmdPanelParamVar!=NULL) {
		nStartX = CmdPanelParamVar->nStartX;
		nStartY = CmdPanelParamVar->nStartY;
		nWidth  = CmdPanelParamVar->nWidth;
		nHeight = CmdPanelParamVar->nHeight;
	}
}

void	AutoSaveImageViewPanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	if (GProp==NULL) return;
	AddNamingAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*AutoSaveImageViewPanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	//CmdMaskingDrawOnOffPacket	Da;
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoSaveImage");
	if(Ab!=NULL){
		NamingBase	*M=(NamingBase *)Ab;
		NamingDrawAttr	*mattr=new NamingDrawAttr(
								   M->ColorNaming		,M->TransparentLevel
								  ,M->ColorSelected		,M->TransparentLevel
								  ,M->ColorActive		,M->TransparentLevel
								  ,M->NegColorNaming		
								  ,M->NegColorSelected);
		//mattr->EffectiveMode	=Da.Effective;
		//mattr->IneffectiveMode	=Da.Ineffective;
		return mattr;
	}
	return new NamingDrawAttr();
}

void	AutoSaveImageViewPanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdNamingDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);

		DataInPage *P=GetLayersBase()->GetPageDataByPoint(globalX ,globalY);
		if(P==NULL)
			return;
		GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
		CmdPacket.TargetPhase=ShowFixedPhase;
		P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
		GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
		CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,RecPacket);
		if(RecPacket.IsReceived()==true){
			LogicDLL	*L=GetAlgorithmBase()->GetLogicDLL();
			ShowAndSetItemsNaming	ShowAndSetItemsNamingData;
			ShowAndSetItemsNamingData.Form=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AutoSaveImageViewPanel" ,/**/"");
			L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,&ShowAndSetItemsNamingData);
		}
	}
}

void AutoSaveImageViewPanel::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingingForm" ,/**/"");
	if(GProp!=NULL)
		GProp->BuildForShow();
}

void	AutoSaveImageViewPanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void AutoSaveImageViewPanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	DisplayImageWithAlgorithm::DrawAfterImage(pnt ,PntImage);

	if ( nStartX == -1 ) return;

	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

	double zoom = GetZoomRate();
	int movx = (int)(GetMovx()*zoom);
	int movy = (int)(GetMovy()*zoom);
	int nWid = (int)(globalX2*zoom);
	int nHei = (int)(globalY2*zoom);

	// 画像開始位置
	int startX = 0;
	int startY = 0;
	//if ( movx > 0 ) startX = movx;
	//if ( movy > 0 ) startY = movy;

	// 画像終了位置
	int endX = nWid + movx;
	int endY = nHei + movy;

	QPen pen(Qt::SolidLine);
	pnt.setPen(Qt::yellow);

	// 横線
	int nDiv = (int)(nStartY*zoom)+startY+movy;
	while( 1 ) {
		pnt.drawLine(startX+movx,nDiv,endX,nDiv);
		nDiv += (int)(nHeight*zoom);
		if ( nDiv > endY ) break;
	}

	// 縦線
	nDiv = (int)(nStartX*zoom)+startX+movx;
	while( 1 ) {
		pnt.drawLine(nDiv,startY+movy,nDiv,endY);
		nDiv += (int)(nWidth*zoom);
		if ( nDiv > endX ) break;
	}
}

//=======================================================================
