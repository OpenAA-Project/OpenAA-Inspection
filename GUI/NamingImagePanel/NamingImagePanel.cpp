#include "NamingImagePanelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\NamingImagePanel\NamingImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "NamingImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "XNaming.h"
#include "ImageControlTools.h"
#include "XPropertyNamingPacket.h"
#include "XGeneralDialog.h"
//#include "ImagePanelTools.h"
#include "XDisplayImagePacket.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"NamingImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"NamingImagePanel");
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
	NamingImagePanel	*B=new NamingImagePanel(Base,parent);
	B->Initial(sRoot,sName);
	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((NamingImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QString";
	Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N].Pointer				 =&((NamingImagePanel *)Instance)->ImageControlToolsName;
	N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/NamingImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Naming"));
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
NamingImagePanel::NamingImagePanel(LayersBase *Base ,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Naming",QString(sRoot),QString(sName),__Master,parent)
{
}

void	NamingImagePanel::Prepare(void)
{
	DisplayImageWithAlgorithm::Prepare();
}

void	NamingImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	DisplayImageWithAlgorithm::TransmitDirectly(packet);
	ChangeToCountModePacket	*ChangeToCountModePacketVar=dynamic_cast<ChangeToCountModePacket *>(packet);
	if(ChangeToCountModePacketVar!=NULL){
		SetDrawingMode(DisplayImage::_Normal);
		SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::magenta);
		return;
	}
}

void	NamingImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	AddNamingAreaPacket	Da(GetLayersBase());
	Da.Area			=area;
	GProp->TransmitDirectly(&Da);
}


AlgorithmDrawAttr	*NamingImagePanel::CreateDrawAttrPointer(void)
{	
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	//CmdMaskingDrawOnOffPacket	Da;
	//if(GProp!=NULL){
	//	GProp->TransmitDirectly(&Da);
	//}
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
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

void	NamingImagePanel::ExecuteMouseRDownWithShift(int globalX ,int globalY)
{
	CmdNamingDrawModePacket	Da(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&Da);

		IntList PageList;
		GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
		for(IntClass *Pg=PageList.GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
			DataInPage	*P=GetLayersBase()->GetPageData(Pg->GetValue());

			GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.TargetPhase=ShowFixedPhase;
			P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
			GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,RecPacket);
			if(RecPacket.IsReceived()==true){
				LogicDLL	*L=GetAlgorithmBase()->GetLogicDLL();
				ShowAndSetItemsNaming	ShowAndSetItemsNamingData;
				ShowAndSetItemsNamingData.Form=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"NamingImagePanel" ,/**/"");
				L->ShowAndSetItems(this,0,L->GetInstance(),RecPacket.IData,&ShowAndSetItemsNamingData);
			}
		}
	}
}

void NamingImagePanel::ExecutePasteShape(const QString &OriginRoot ,const QString &OriginName)
{
	DisplayImageWithAlgorithm::ExecutePasteShape(OriginRoot ,OriginName);
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	if(GProp!=NULL)
		GProp->BuildForShow();
}

void	NamingImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	NamingImagePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	DisplayImageWithAlgorithm::DrawAfterImage(pnt ,PntImage);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Naming");
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	if(GProp!=NULL){
		GetCountPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		if(Da.EnabledCountMode==true){
			MakeAreaNamePacket	MPacket(GetLayersBase());
			MPacket.FormatStr	=Da.Format;

			if(Da.CountX!=0 && Da.CountY!=0){
				double	ZoomRate=GetZoomRate();
				int		MovX	=GetMovx();
				int		MovY	=GetMovy();

				int		X1=GetRawSDataPoint()->UData.RectangleData.x1;
				int		Y1=GetRawSDataPoint()->UData.RectangleData.y1;
				int		X2=GetRawSDataPoint()->UData.RectangleData.x2;
				int		Y2=GetRawSDataPoint()->UData.RectangleData.y2;

				if(X1>X2)
					swap(X1,X2);
				if(Y1>Y2)
					swap(Y1,Y2);

				double	CellX=(X2-X1)/((double)Da.CountX);
				double	CellY=(Y2-Y1)/((double)Da.CountY);
				pnt.setPen(Qt::magenta);
				for(int i=1;i<Da.CountX;i++){
					pnt.drawLine((X1+CellX*i+MovX)*ZoomRate,(Y1+MovY)*ZoomRate,(X1+CellX*i+MovX)*ZoomRate,(Y2+MovY)*ZoomRate);
				}
				for(int i=1;i<Da.CountY;i++){
					pnt.drawLine((X1+MovX)*ZoomRate,(Y1+CellY*i+MovY)*ZoomRate,(X2+MovX)*ZoomRate,(Y1+CellY*i+MovY)*ZoomRate);
				}
				for(int y=0;y<Da.CountY;y++){
					for(int x=0;x<Da.CountX;x++){
						MPacket.X	=x;
						MPacket.Y	=y;
						MPacket.CountX=Da.CountX-1;
						MPacket.CountY=Da.CountY-1;
						Ab->TransmitDirectly(&MPacket);
						QRect	rect((int)((X1+CellX*x+MovX)*ZoomRate)
									,(int)((Y1+CellY*y+MovY)*ZoomRate)
									,(int)(CellX*ZoomRate)
									,(int)(CellY*ZoomRate));
						pnt.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter
									,MPacket.AreaName);
					}
				}
			}
		}
	}
}
void	NamingImagePanel::SlotCancelDraw()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyNamingForm" ,/**/"");
	if(GProp!=NULL){
		CancelCountPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
		Repaint();
	}
}
//=======================================================================
