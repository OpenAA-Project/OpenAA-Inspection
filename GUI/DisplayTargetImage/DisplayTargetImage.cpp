/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayTargetImage\DisplayTargetImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayTargetImage.h"
#include "XAlgorithmBase.h"
#include "TargetImageControlTools.h"
#include "XGUI.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "SelectItemIndependent.h"
#include "DisplayTargetImageResource.h"
#include "XDisplayImagePacket.h"
#include "XPassword.h"
#include "XDataInLayer.h"
#include "XImageStocker.h"
#include "XCriticalFunc.h"
#include "mtImageToolButtonWithBalloon.h"
#include "SelectMultiItemsDialog.h"
#include <QMenu>

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"DisplayTargetImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Target Image for Inspeaction");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Target);

	(*Base)=new GUICmdReqItemIndependentPack(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendIndependentPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSelectCopied		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSyncDrawingMode		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqTargetItemsBmp		(Base, NULL,sRoot,sName);
	(*Base)=new GUICmdSendTargetItemsBmp	(Base,sRoot,sName);
	(*Base)=new GUICmdReqItemsZone			(Base,sRoot,sName);
	(*Base)=new GUICmdSendItemsZone			(Base,sRoot,sName);
	(*Base)=new GUICmdReqMultiItemsByArea	(Base,sRoot,sName);
	(*Base)=new GUICmdSendMultiItemsByArea	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayTargetImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DisplayTargetImage *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type					=/**/"QStringList";
	Data[N].VariableNameWithRoute	=/**/"RelatedItems";
	Data[N].Pointer					=&((DisplayTargetImage *)Instance)->RelatedItems;
	Data[N+1].Type					=/**/"QString";
	Data[N+1].VariableNameWithRoute	=/**/"ImageControlToolsName";
	Data[N+1].Pointer				=&((DisplayTargetImage *)Instance)->ImageControlToolsName;
	Data[N+2].Type					=/**/"int32";
	Data[N+2].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[N+2].Pointer				=&((DisplayTargetImage *)Instance)->ShowFixedPhase;
	Data[N+3].Type					=/**/"bool";
	Data[N+3].VariableNameWithRoute	=/**/"ZoomForEveryInspection";
	Data[N+3].Pointer				=&((DisplayTargetImage *)Instance)->ZoomForEveryInspection;
	Data[N+4].Type					=/**/"int32";
	Data[N+4].VariableNameWithRoute	=/**/"Mergin";
	Data[N+4].Pointer				=&((DisplayTargetImage *)Instance)->Mergin;

	Data[N+5].Type					=/**/"bool";
	Data[N+5].VariableNameWithRoute	=/**/"ShiftLeftClicked";
	Data[N+5].Pointer				=&((DisplayTargetImage *)Instance)->ShiftLeftClicked;
	Data[N+6].Type					=/**/"bool";
	Data[N+6].VariableNameWithRoute	=/**/"ShiftRightClicked";
	Data[N+6].Pointer				=&((DisplayTargetImage *)Instance)->ShiftRightClicked;
	Data[N+7].Type					=/**/"bool";
	Data[N+7].VariableNameWithRoute	=/**/"tModeShowOnlyTopTurn";
	Data[N+7].Pointer				=&((DisplayTargetImage *)Instance)->tModeShowOnlyTopTurn;
	Data[N+8].Type					=/**/"bool";
	Data[N+8].VariableNameWithRoute	=/**/"MultiItemSelection";
	Data[N+8].Pointer				=&((DisplayTargetImage *)Instance)->MultiItemSelection;

	return(N+9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayTargetImage.png")));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImage::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

//==================================================================================================
DisplayTargetImage::DisplayTargetImage(LayersBase *Base ,QWidget *parent)
:DisplayImage(Base,QString(sRoot),QString(sName),Base->GetParamGlobal()->AllocViewTargetBuffer==false?__Target:__DelayedView,parent)
,TimeStocker(10)
{
	emitterRoot=sRoot;
	emitterName=sName;
	
	GlobalX1					=99999999;
	GlobalY1					=99999999;
	GlobalX2					=-99999999;
	GlobalY2					=-99999999;
	ZoomForEveryInspection		=false;
	Mergin						=100;
	ShiftLeftClicked			=true;
	ShiftRightClicked			=true;
	tModeShowOnlyTopTurn		=false;
	TargetImageControlToolsProp	=NULL;
	MultiItemSelection			=true;
	MultiItemSelectionBtn		=NULL;
	MultiItemShapeMode			=mtFrameDraw::fdRectangle;

	ItemsBmpCounts=GetPageNumb();
	ItemsBmpReceiver	=new GUICmdSendTargetItemsBmp*[ItemsBmpCounts];
	ItemsBmpRequester	=new GUICmdReqTargetItemsBmp*[ItemsBmpCounts];
	for(int page=0;page<ItemsBmpCounts;page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		ItemsBmpReceiver[page]=new GUICmdSendTargetItemsBmp(GetLayersBase(),emitterRoot,emitterName,globalPage);
		ItemsBmpRequester[page]=new GUICmdReqTargetItemsBmp(GetLayersBase(),this,emitterRoot,emitterName,globalPage);		
	}
}
DisplayTargetImage::~DisplayTargetImage(void)
{
	for(int i=0;i<ItemsBmpCounts;i++){
		delete	ItemsBmpRequester[i];
		delete	ItemsBmpReceiver[i];
	}
	delete	[]ItemsBmpRequester;
	delete	[]ItemsBmpReceiver;

	ItemsBmpRequester	=NULL;
	ItemsBmpReceiver	=NULL;
}

void	DisplayTargetImage::Prepare(void)
{
	DisplayImage::ModeShowOnlyTopTurn=tModeShowOnlyTopTurn;
	DisplayImage::Prepare();

	if(MultiItemSelection==true){
		if(MultiItemSelectionBtn==NULL){
			MultiItemSelectionBtn	=new mtImageToolButtonWithBalloon(QImage(),NULL);	//mtToolButtonWithBalloon();
			MultiItemSelectionBtn->setInvertMode(true);
			MultiItemSelectionBtn->setMessage("Multi-Item selection operation");
			connect(MultiItemSelectionBtn,SIGNAL(clicked()),this,SLOT(MultiItemSelectionBtnDown()));
			connect(MultiItemSelectionBtn,SIGNAL(RClick(QMouseEvent *)),this,SLOT(SlotItemsSelectDrawShape(QMouseEvent *)));
			MultiItemSelectionBtn->setAutoExclusive(true);
			MultiItemSelectionBtn->setIconSize (QSize(DefIconSize,DefIconSize));
			MultiItemSelectionBtn->setCheckable(true);
			MultiItemSelectionBtn->setAutoRaise(true);
			MultiItemSelectionBtn->setObjectName(/**/"MultiItemSelectionBtn");
			DisplayImage::InsertIconButton(/**/"ZoomIn",MultiItemSelectionBtn);
		}

		if(IconSize<=32){
			MultiItemSelectionBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/MultiItemSelectionBtn32.png"));
		}
		else if(IconSize<=64){
			MultiItemSelectionBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/MultiItemSelectionBtn64.png"));
		}
		else{
			MultiItemSelectionBtn->setFaceImage(GetLayersBase()->GetListOfQImageStocker()->GetImage(/**/":Resources/MultiItemSelectionBtn100.png"));
		}
	}
	else if(MultiItemSelectionBtn!=NULL){
		delete MultiItemSelectionBtn;
		MultiItemSelectionBtn=NULL;
	}
	
	//if(MultiItemSelection==true){
	//	SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
	//}
}

void	DisplayTargetImage::ReadyParam(void)
{
	TargetImageControlToolsProp=(GUIFormBase *)GetLayersBase()->FindByName(/**/"Button" ,/**/"TargetImageControlTools" ,ImageControlToolsName);
}
void	DisplayTargetImage::MultiItemSelectionBtnDown()
{
	//SetModeByOthers(mtFrameDraw::fdRectangle ,Qt::red);
	SetModeToImagePanelTools(MultiItemShapeMode ,Qt::red);
	ModeFromOther=MultiItemShapeMode;
	if(MainCanvas!=NULL){
		MainCanvas->Clear();
		MainCanvas->SetMode(ModeFromOther);
		MainCanvas->SetFrameColor(Qt::red);
	}
}
void	DisplayTargetImage::ExecuteMouseLDownWithShift(int globalX,int globalY)
{
	if(ShiftLeftClicked==false)
		return;

	if(GetLayersBase()->GetPasswordHolder()->PasswordCheck()==false)
		return;

	SelectItemIndependent	D(GetLayersBase(),this);

	IntList PageList;
	GetLayersBase()->GetGlobalPage(globalX ,globalY,PageList);
	if(PageList.GetCount()==0)
		return;

	GUICmdSendIndependentPack	**RecPacket=new GUICmdSendIndependentPack	*[GetPageNumb()];
	for(int page=0;page<GetPageNumb();page++){
		RecPacket[page]=NULL;
	}
	int	ListCount=0;
	for(IntClass *c=PageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	Page=c->GetValue();
		if(GetShowOnePage()<0 || GetShowOnePage()==Page){
			DataInPage *P=GetLayersBase()->GetPageData(Page);
			if(P==NULL)
				continue;

			GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.TargetPhase=ShowFixedPhase;
			P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
			RecPacket[Page]=new GUICmdSendIndependentPack(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
			CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,*RecPacket[Page]);
			if(RecPacket[Page]->IsReceived()==true){
				RecPacket[Page]->IData.LocalX=CmdPacket.localX;
				RecPacket[Page]->IData.LocalY=CmdPacket.localY;
				for(AlgorithmItemIndependent *p=RecPacket[Page]->IData.Items.GetFirst();p!=NULL;p=p->GetNext()){
					D.AddItem(p);
					ListCount++;
				}
			}
		}
	}
	QString	DLLRoot,DLLName;
	GUICmdSendIndependentPack	*RPoint=NULL;
	if(ListCount>1){
		D.Show();
		if(D.exec()==false){
			goto	EndFunc;
		}
		if(D.SelectedList==NULL){
			goto	EndFunc;
		}
		DLLRoot=D.SelectedList->DLLRoot;
		DLLName=D.SelectedList->DLLName;
		for(int page=0;page<GetPageNumb();page++){
			if(RecPacket[page]==NULL)
				continue;
			for(AlgorithmItemIndependent *p=RecPacket[page]->IData.Items.GetFirst();p!=NULL;){
				ItemIndependentList *q;
				for(q=D.SelectedList->ItemList.GetFirst();q!=NULL;q=q->GetNext()){
					if(q->Point==p && q->Selected==true)
						break;
				}
				if(q==NULL){
					AlgorithmItemIndependent *NextP=p->GetNext();
					RecPacket[page]->IData.Items.RemoveList(p);
					delete	p;
					p=NextP;
				}
				else{
					RPoint=RecPacket[page];
					p=p->GetNext();
				}
			}
		}
	}
	else if(ListCount==1){
		for(int page=0;page<GetPageNumb();page++){
			if(RecPacket[page]==NULL)
				continue;
			AlgorithmItemIndependent *p=RecPacket[page]->IData.Items.GetFirst();
			RPoint=RecPacket[page];
			DLLRoot	=p->AlgorithmRoot;
			DLLName	=p->AlgorithmName;
		}
	}
	if(RPoint!=NULL){
		LogicDLL	*L=GetLayersBase()->GetAlgorithmDLL(DLLRoot,DLLName);
		L->ShowAndSetItems(this,0,L->GetInstance(),RPoint->IData,NULL);
	}
EndFunc:;
	for(int page=0;page<GetPageNumb();page++){
		if(RecPacket[page]!=NULL){
			delete	RecPacket[page];
		}
	}
	delete	[]RecPacket;
}

void	DisplayTargetImage::ExecuteMouseRDownWithShift(int globalX,int globalY)
{
	if(ShiftRightClicked==false)
		return;

	DataInPage *P=GetLayersBase()->GetPageDataByPoint(globalX ,globalY);
	if(P==NULL)
		return;
	GUICmdReqItemIndependentPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
	CmdPacket.TargetPhase=ShowFixedPhase;
	P->GetLocalMatrixFromGlobalInMaster(globalX ,globalY ,CmdPacket.localX,CmdPacket.localY);
	
	GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),P->GetPage());
	CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(P->GetPage()),0,RecPacket);
	if(RecPacket.IsReceived()==true){
		int	RetNumb=RecPacket.IData.Items.GetNumber();
		if(RetNumb==0)
			return;
		QString	DLLRoot,DLLName;
		if(RetNumb>1){
			SelectItemIndependent	D(GetLayersBase(),this);
			for(AlgorithmItemIndependent *p=RecPacket.IData.Items.GetFirst();p!=NULL;p=p->GetNext()){
				D.AddItem(p);
			}
			D.Show();
			if(D.exec()==false)
				return;
			if(D.SelectedList==NULL)
				return;
			DLLRoot=D.SelectedList->DLLRoot;
			DLLName=D.SelectedList->DLLName;
			for(AlgorithmItemIndependent *p=RecPacket.IData.Items.GetFirst();p!=NULL;){
				ItemIndependentList *q;
				for(q=D.SelectedList->ItemList.GetFirst();q!=NULL;q=q->GetNext()){
					if(q->Point==p && q->Selected==true)
						break;
				}
				if(q==NULL){
					AlgorithmItemIndependent *NextP=p->GetNext();
					RecPacket.IData.Items.RemoveList(p);
					delete	p;
					p=NextP;
				}
				else{
					p=p->GetNext();
				}
			}
		}
		else{
			AlgorithmItemIndependent *p=RecPacket.IData.Items.GetFirst();
			DLLRoot	=p->AlgorithmRoot;
			DLLName	=p->AlgorithmName;
		}
		LogicDLL	*L=GetLayersBase()->GetAlgorithmDLL(DLLRoot,DLLName);
		L->ChangeItemsAttr(this,0,L->GetInstance(),RecPacket.IData);
	}

}

void	DisplayTargetImage::DrawEndAfterOperation(FlexArea &area)
{
	if(MultiItemSelection==true && MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		ItemsByAlgorithm			*Selected=NULL;
		SelectMultiItemsDialog	D(GetLayersBase(),area);
		if(D.ContainersEachPhase.GetCount()>1){
			if(D.exec()==true){
				Selected=D.Selected;
			}
		}
		else if(D.ContainersEachPhase.GetCount()==1){
			Selected=D.ContainersEachPhase.GetFirst();
		}
		if(Selected!=NULL){
			AlgorithmItemIndependentPack	IData(GetLayersBase());
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(area,PageList);
			if(ShowFixedPhase>=0){
				for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
					int	Page=p->GetValue();
					if(GetShowOnePage()<0 || GetShowOnePage()==Page){
						IntList IDList;
						Selected->ItemID.MakeIDList(ShowFixedPhase,Page ,IDList);
						GUICmdReqItemIndependentsPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),Page);
						CmdPacket.TargetPhase=ShowFixedPhase;
						CmdPacket.Items		=IDList;
						CmdPacket.LibType	=Selected->LibType;
						CmdPacket.LibID		=Selected->LibID;
						CmdPacket.Layer		=Selected->Layer;
						GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),Page);
						CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(Page),0,RecPacket);
						if(RecPacket.IsReceived()==true){
							IData.Items+=RecPacket.IData.Items;
						}
					}
				}
			}
			else{
				for(int phase=0;phase<GetPhaseNumb();phase++){
					for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
						int	Page=p->GetValue();
						if(GetShowOnePage()<0 || GetShowOnePage()==Page){
							IntList IDList;
							Selected->ItemID.MakeIDList(phase,Page ,IDList);
							GUICmdReqItemIndependentsPack	CmdPacket(GetLayersBase(),QString(sRoot),QString(sName),Page);
							CmdPacket.TargetPhase=phase;
							CmdPacket.Items		=IDList;
							CmdPacket.LibType	=Selected->LibType;
							CmdPacket.LibID		=Selected->LibID;
							CmdPacket.Layer		=Selected->Layer;
							GUICmdSendIndependentPack	RecPacket(GetLayersBase(),QString(sRoot),QString(sName),Page);
							CmdPacket.Send(GetLayersBase()->GetGlobalPageFromLocal(Page),0,RecPacket);
							if(RecPacket.IsReceived()==true){
								IData.Items+=RecPacket.IData.Items;
							}
						}
					}
				}
			}
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(Selected->LibType);
			if(ABase!=NULL){
				LogicDLL	*L=ABase->GetLogicDLL();
				L->ShowAndSetItems(this,0,L->GetInstance(),IData,NULL);
			}
		}
	}
	else{
		DisplayImage::DrawEndAfterOperation(area);
	}
}

void	DisplayTargetImage::GetActiveLayerList(IntList &LayerList)	const
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqTargetImageLayer	DrawMode(GetLayersBase(),LayerNumb);
	if(TargetImageControlToolsProp!=NULL){
		TargetImageControlToolsProp->TransmitDirectly(&DrawMode);
		LayerList=DrawMode.LayerList;
	}
	else{
		for(int Layer=0;Layer<LayerNumb;Layer++){
			LayerList.Add(Layer);
		}
	}
}

void	DisplayTargetImage::SetDrawPosition(int datax1 ,int datay1 , int datax2 ,int datay2)
{
	DisplayImage::SetDrawPosition(datax1 ,datay1 , datax2 ,datay2);
	repaint();
}

void	DisplayTargetImage::CanvasSlotOnPaint(QPainter &pnt)
{
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqTargetImageLayer	DrawMode(GetLayersBase(),LayerNumb);
	if(GetEditMode()==false){
		if(TargetImageControlToolsProp!=NULL){
			TargetImageControlToolsProp->TransmitDirectly(&DrawMode);
			RedCircleMode=DrawMode.RedCircleMode;
		}
	}
	DisplayImage::CanvasSlotOnPaint(pnt);
}

void	DisplayTargetImage::BuildForShow(void)
{
	DisplayImage::BuildForShow();
	if(ZoomForEveryInspection==true){
		GlobalX1=99999999;
		GlobalY1=99999999;
		GlobalX2=-99999999;
		GlobalY2=-99999999;

		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			DataInPage *P=GetLayersBase()->GetPageData(page);

			GUICmdReqItemsZone	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			GUICmdSendItemsZone	SCmd(GetLayersBase(),sRoot,sName,globalPage);
			if(RCmd.Send(globalPage,0,SCmd)==true){
				if(SCmd.X1<SCmd.X2 && SCmd.Y1<SCmd.Y2){
					if(GlobalX1>SCmd.X1+P->GetOutlineOffset()->x)
						GlobalX1=SCmd.X1+P->GetOutlineOffset()->x;
					if(GlobalY1>SCmd.Y1+P->GetOutlineOffset()->y)
						GlobalY1=SCmd.Y1+P->GetOutlineOffset()->y;
					if(GlobalX2<SCmd.X2+P->GetOutlineOffset()->x)
						GlobalX2=SCmd.X2+P->GetOutlineOffset()->x;
					if(GlobalY2<SCmd.Y2+P->GetOutlineOffset()->y)
						GlobalY2=SCmd.Y2+P->GetOutlineOffset()->y;
				}
			}
		}
		if(GlobalX1<GlobalX2 && GlobalY1<GlobalY2){
			ZoomRect(GlobalX1-Mergin, GlobalY1-Mergin, GlobalX2+Mergin, GlobalY2+Mergin);
		}
	}
	else{
		DisplayImage::ViewRefreshInEdit();
	}
}

void	DisplayTargetImage::ShowInPlayer(int64 shownInspectionID)
{
	if(GetStackedViewPlayerCount()<2){
		if(ZoomForEveryInspection==true){
			if(GlobalX1<GlobalX2 && GlobalY1<GlobalY2){
				ZoomRect(GlobalX1-Mergin, GlobalY1-Mergin, GlobalX2+Mergin, GlobalY2+Mergin);
			}
		}
		else{
			DWORD	t=::GetComputerMiliSec();
			//DWORD	Len=TimeStocker.GetSpanToLastTime(t);			
			//if(Len>=(TimeStocker.GetAverage()*0.5) || Len>=2000){

			TimeStocker.SetCurrentMilisec(t);
			DisplayImage::ShowInPlayer(shownInspectionID);
		}
	}
}
void	DisplayTargetImage::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	if(0<=GetShowOnePage() && GetShowOnePage()<GetPageNumb()){
		DrawAfterImageOnePage(pnt ,PntImage);
		ReEntrant=false;
		return;
	}
	if(GetPageNumb()<=GetShowOnePage()){
		ReEntrant=false;
		return;
	}

	IntList	LayerList;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqTargetImageLayer	DrawMode(GetLayersBase(),LayerNumb);
	//GUIFormBase	*TargetImageControlToolsProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"TargetImageControlTools" ,ImageControlToolsName);
	if(TargetImageControlToolsProp!=NULL){
		TargetImageControlToolsProp->TransmitDirectly(&DrawMode);
		LayerList=DrawMode.LayerList;
	}
	if(ItemsBmpCounts!=GetPageNumb()){
		for(int i=0;i<ItemsBmpCounts;i++){
			delete	ItemsBmpRequester[i];
			delete	ItemsBmpReceiver[i];
		}
		delete	[]ItemsBmpReceiver;
		delete	[]ItemsBmpRequester;

		ItemsBmpCounts=GetPageNumb();
		ItemsBmpReceiver	=new GUICmdSendTargetItemsBmp*[ItemsBmpCounts];
		ItemsBmpRequester	=new GUICmdReqTargetItemsBmp*[ItemsBmpCounts];
		for(int page=0;page<ItemsBmpCounts;page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			ItemsBmpReceiver[page]=new GUICmdSendTargetItemsBmp(GetLayersBase(),emitterRoot,emitterName,globalPage);
			ItemsBmpRequester[page]=new GUICmdReqTargetItemsBmp(GetLayersBase(),this,emitterRoot,emitterName,globalPage);		
		}	
	}
	if(ModeShowOnlyTopTurn==false){
		if(DrawMode.ShowNGItemButton==true || DrawMode.ShowAllItemsButton==true){
			int	globalX1;
			int	globalY1;
			int	globalX2;
			int	globalY2;
			GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);
			int	N=0;
			for(int page=0;page<GetPageNumb();page++){
				int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

				ItemsBmpRequester[N]->LayerList	=LayerList;
				DataInPage *P=GetLayersBase()->GetPageData(page);
				int	Dx1	=P->GetOutlineOffset()->x;
				int	Dy1	=P->GetOutlineOffset()->y;
				int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
				int	Dy2	=P->GetOutlineOffset()->x+P->GetMaxLines();
				int	Gx1,Gy1,Gx2,Gy2;
				ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
				ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
				if(CheckOverlapRectRectFast(0, 0, GetCanvasWidth(), GetCanvasHeight()
											,Gx1, Gy1, Gx2, Gy2)==false)
					continue;
				ItemsBmpRequester[N]->Data.ZoomRate	=GetZoomRate();
				ItemsBmpRequester[N]->Data.MovX			=GetMovx()+P->GetOutlineOffset()->x;
				ItemsBmpRequester[N]->Data.MovY			=GetMovy()+P->GetOutlineOffset()->y;
				//if(ItemsBmpRequester[N]->Data.MovX>0)
				//	ItemsBmpRequester[N]->Data.MovX=0;
				//if(ItemsBmpRequester[N]->Data.MovY>0)
				//	ItemsBmpRequester[N]->Data.MovY=0;

				ItemsBmpRequester[N]->Data.GlobalPage	=globalPage;
				if(Gx1<0)
					Gx1=0;
				if(Gy1<0)
					Gy1=0;
				if(Gx2>GetCanvasWidth())
					Gx2=GetCanvasWidth();
				if(Gy2>GetCanvasHeight())
					Gy2=GetCanvasHeight();
				ItemsBmpRequester[N]->Data.Gx1		=Gx1;
				ItemsBmpRequester[N]->Data.Gy1		=Gy1;
				ItemsBmpRequester[N]->Data.Gx2		=Gx2;
				ItemsBmpRequester[N]->Data.Gy2		=Gy2;
				ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
				ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
				ItemsBmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
				ItemsBmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
				ItemsBmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
				ItemsBmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
				ItemsBmpRequester[N]->Data.MoveGlobalDx	=MoveCurrentGlobalX - MoveStartGlobalX;
				ItemsBmpRequester[N]->Data.MoveGlobalDy	=MoveCurrentGlobalY - MoveStartGlobalY;
				ItemsBmpRequester[N]->InstName	=GetName();
				ItemsBmpRequester[N]->Data.ShowNGItemButton		=DrawMode.ShowNGItemButton;
				ItemsBmpRequester[N]->Data.ShowAllItemsButton	=DrawMode.ShowAllItemsButton;
				ItemsBmpRequester[N]->SelectedAlgorithm	=DrawMode.SelectedAlgorithm;

				N++;
			}
			for(int n=0;n<N;n++){
				ItemsBmpRequester[n]->Send(ItemsBmpRequester[n]->Data.GlobalPage,0,*ItemsBmpReceiver[n]);
			}
			for(int n=0;n<N;n++){
				if(ItemsBmpReceiver[n]->IsReceived()==true && ItemsBmpReceiver[n]->IData!=NULL){
					pnt.drawImage(ItemsBmpRequester[n]->Data.Gx1 ,ItemsBmpRequester[n]->Data.Gy1
						 ,*(const QImage *)ItemsBmpReceiver[n]->IData);
				}
			}
		}
	}
	else{
		int	Pn=GetLayersBase()->GetDrawturn(0)->GetPage();

		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(Pn);
		
		int	globalX1;
		int	globalY1;
		int	globalX2;
		int	globalY2;
		GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

		ItemsBmpRequester[Pn]->LayerList	=LayerList;
		DataInPage *P=GetLayersBase()->GetPageData(Pn);
		int	Dx1	=P->GetOutlineOffset()->x;
		int	Dy1	=P->GetOutlineOffset()->y;
		int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
		int	Dy2	=P->GetOutlineOffset()->x+P->GetMaxLines();
		int	Gx1,Gy1,Gx2,Gy2;
		ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
		ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
		if(CheckOverlapRectRectFast(0, 0, GetCanvasWidth(), GetCanvasHeight()
									,Gx1, Gy1, Gx2, Gy2)==false){
			ReEntrant=false;
			return;
		}
		ItemsBmpRequester[Pn]->Data.ZoomRate	=GetZoomRate();
		ItemsBmpRequester[Pn]->Data.MovX		=GetMovx()+P->GetOutlineOffset()->x;
		ItemsBmpRequester[Pn]->Data.MovY		=GetMovy()+P->GetOutlineOffset()->y;
		//if(ItemsBmpRequester[N]->Data.MovX>0)
		//	ItemsBmpRequester[N]->Data.MovX=0;
		//if(ItemsBmpRequester[N]->Data.MovY>0)
		//	ItemsBmpRequester[N]->Data.MovY=0;

		ItemsBmpRequester[Pn]->Data.GlobalPage	=globalPage;
		if(Gx1<0)
			Gx1=0;
		if(Gy1<0)
			Gy1=0;
		if(Gx2>GetCanvasWidth())
			Gx2=GetCanvasWidth();
		if(Gy2>GetCanvasHeight())
			Gy2=GetCanvasHeight();
		ItemsBmpRequester[Pn]->Data.Gx1		=Gx1;
		ItemsBmpRequester[Pn]->Data.Gy1		=Gy1;
		ItemsBmpRequester[Pn]->Data.Gx2		=Gx2;
		ItemsBmpRequester[Pn]->Data.Gy2		=Gy2;
		ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
		ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
		ItemsBmpRequester[Pn]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
		ItemsBmpRequester[Pn]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
		ItemsBmpRequester[Pn]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
		ItemsBmpRequester[Pn]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
		ItemsBmpRequester[Pn]->Data.MoveGlobalDx	=MoveCurrentGlobalX - MoveStartGlobalX;
		ItemsBmpRequester[Pn]->Data.MoveGlobalDy	=MoveCurrentGlobalY - MoveStartGlobalY;
		ItemsBmpRequester[Pn]->InstName	=GetName();
		ItemsBmpRequester[Pn]->Data.ShowNGItemButton	=DrawMode.ShowNGItemButton;
		ItemsBmpRequester[Pn]->Data.ShowAllItemsButton	=DrawMode.ShowAllItemsButton;
		ItemsBmpRequester[Pn]->SelectedAlgorithm	=DrawMode.SelectedAlgorithm;

		if(ItemsBmpRequester[Pn]->Send(ItemsBmpRequester[Pn]->Data.GlobalPage,0,*ItemsBmpReceiver[Pn])==true){
			if(ItemsBmpReceiver[Pn]->IsReceived()==true && ItemsBmpReceiver[Pn]->IData!=NULL){
				pnt.drawImage(ItemsBmpRequester[Pn]->Data.Gx1 ,ItemsBmpRequester[Pn]->Data.Gy1
							 ,*(const QImage *)ItemsBmpReceiver[Pn]->IData);
			}
		}
	}
	ReEntrant=false;
}

void	DisplayTargetImage::DrawAfterImageOnePage(QPainter &pnt ,QImage &PntImage)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	IntList	LayerList;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	CmdReqTargetImageLayer	DrawMode(GetLayersBase(),LayerNumb);
	//GUIFormBase	*TargetImageControlToolsProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"TargetImageControlTools" ,ImageControlToolsName);
	if(TargetImageControlToolsProp!=NULL){
		TargetImageControlToolsProp->TransmitDirectly(&DrawMode);
		LayerList=DrawMode.LayerList;
	}
	if(ItemsBmpCounts!=GetPageNumb()){
		for(int i=0;i<ItemsBmpCounts;i++){
			delete	ItemsBmpRequester[i];
			delete	ItemsBmpReceiver[i];
		}
		delete	[]ItemsBmpReceiver;
		delete	[]ItemsBmpRequester;

		ItemsBmpCounts=GetPageNumb();
		ItemsBmpReceiver	=new GUICmdSendTargetItemsBmp*[ItemsBmpCounts];
		ItemsBmpRequester	=new GUICmdReqTargetItemsBmp*[ItemsBmpCounts];
		for(int page=0;page<ItemsBmpCounts;page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			ItemsBmpReceiver[page]=new GUICmdSendTargetItemsBmp(GetLayersBase(),emitterRoot,emitterName,globalPage);
			ItemsBmpRequester[page]=new GUICmdReqTargetItemsBmp(GetLayersBase(),this,emitterRoot,emitterName,globalPage);		
		}	
	}
	if((DrawMode.ShowNGItemButton==true || DrawMode.ShowAllItemsButton==true) && 0<=GetShowOnePage() && GetShowOnePage()<GetPageNumb()){
		DataInPage *P=GetLayersBase()->GetPageData(GetShowOnePage());
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(GetShowOnePage());

		ItemsBmpRequester[GetShowOnePage()]->LayerList	=LayerList;
		int	Dx1	=P->GetOutlineOffset()->x;
		int	Dy1	=P->GetOutlineOffset()->y;
		int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
		int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
		int	Gx1,Gy1,Gx2,Gy2;
		ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
		ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
		if(CheckOverlapRectRectFast(0, 0, GetCanvasWidth(), GetCanvasHeight()
									,Gx1, Gy1, Gx2, Gy2)==true){
			ItemsBmpRequester[GetShowOnePage()]->Data.ZoomRate	=GetZoomRate();
			ItemsBmpRequester[GetShowOnePage()]->Data.MovX		=GetMovx();
			ItemsBmpRequester[GetShowOnePage()]->Data.MovY		=GetMovy();
			//if(ItemsBmpRequester[N]->Data.MovX>0)
			//	ItemsBmpRequester[N]->Data.MovX=0;
			//if(ItemsBmpRequester[N]->Data.MovY>0)
			//	ItemsBmpRequester[N]->Data.MovY=0;

			ItemsBmpRequester[GetShowOnePage()]->Data.GlobalPage	=globalPage;
			if(Gx1<0)
				Gx1=0;
			if(Gy1<0)
				Gy1=0;
			if(Gx2>GetCanvasWidth())
				Gx2=GetCanvasWidth();
			if(Gy2>GetCanvasHeight())
				Gy2=GetCanvasHeight();
			ItemsBmpRequester[GetShowOnePage()]->Data.Gx1		=Gx1;
			ItemsBmpRequester[GetShowOnePage()]->Data.Gy1		=Gy1;
			ItemsBmpRequester[GetShowOnePage()]->Data.Gx2		=Gx2;
			ItemsBmpRequester[GetShowOnePage()]->Data.Gy2		=Gy2;
			ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
			ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
			ItemsBmpRequester[GetShowOnePage()]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			ItemsBmpRequester[GetShowOnePage()]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			ItemsBmpRequester[GetShowOnePage()]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			ItemsBmpRequester[GetShowOnePage()]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			ItemsBmpRequester[GetShowOnePage()]->Data.MoveGlobalDx	=MoveCurrentGlobalX - MoveStartGlobalX;
			ItemsBmpRequester[GetShowOnePage()]->Data.MoveGlobalDy	=MoveCurrentGlobalY - MoveStartGlobalY;
			ItemsBmpRequester[GetShowOnePage()]->InstName	=GetName();
			ItemsBmpRequester[GetShowOnePage()]->Data.ShowNGItemButton	=DrawMode.ShowNGItemButton;
			ItemsBmpRequester[GetShowOnePage()]->Data.ShowAllItemsButton=DrawMode.ShowAllItemsButton;
			ItemsBmpRequester[GetShowOnePage()]->SelectedAlgorithm	=DrawMode.SelectedAlgorithm;

			ItemsBmpRequester[GetShowOnePage()]->Send(ItemsBmpRequester[GetShowOnePage()]->Data.GlobalPage,0,*ItemsBmpReceiver[GetShowOnePage()]);

			if(ItemsBmpReceiver[GetShowOnePage()]->IsReceived()==true && ItemsBmpReceiver[GetShowOnePage()]->IData!=NULL){
				pnt.drawImage(ItemsBmpRequester[GetShowOnePage()]->Data.Gx1 ,ItemsBmpRequester[GetShowOnePage()]->Data.Gy1
					 ,*(const QImage *)ItemsBmpReceiver[GetShowOnePage()]->IData);
			}
		}
	}
	ReEntrant=false;
}
//=================================================================================================

void	DisplayTargetImage::SlotItemsSelectDrawShape(QMouseEvent * event )
{
	QMenu	Menu(NULL);
	Menu.addAction ("Rectangle"			, this, SLOT(SlotItemsSelectRectangle()));
	Menu.addAction ("Ellipse-Center"	, this, SLOT(SlotItemsSelectEllipseCenter()));
	Menu.addAction ("Ellipse-4Points"	, this, SLOT(SlotItemsSelectEllipse4Points()));
	Menu.addAction ("Long hole"			, this, SLOT(SlotItemsSelectLongCircle()));
	Menu.addAction ("Rotated rect"		, this, SLOT(SlotItemsSelectRotatedRect()));
	Menu.addAction ("Ring"				, this, SLOT(SlotItemsSelectRing()));
	Menu.addAction ("Polygon"			, this, SLOT(SlotItemsSelectPolygon()));
	Menu.addAction ("Free hand"			, this, SLOT(SlotItemsSelectFreeHand()));

	QPoint	Q=mapToGlobal(MultiItemSelectionBtn->geometry().center());
	Menu.exec(Q);

}
void	DisplayTargetImage::SlotItemsSelectRectangle()
{
	MultiItemShapeMode=mtFrameDraw::fdRectangle;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectEllipseCenter()
{
	MultiItemShapeMode=mtFrameDraw::fdEllipse;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectEllipse4Points()
{
	MultiItemShapeMode=mtFrameDraw::fdEllipse4;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectLongCircle()
{
	MultiItemShapeMode=mtFrameDraw::fdLongCircle;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectRotatedRect()
{
	MultiItemShapeMode=mtFrameDraw::fdRotRectangle;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectRing()
{
	MultiItemShapeMode=mtFrameDraw::fdRing;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectPolygon()
{
	MultiItemShapeMode=mtFrameDraw::fdPoly;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}
void	DisplayTargetImage::SlotItemsSelectFreeHand()
{
	MultiItemShapeMode=mtFrameDraw::fdFree;
	if(MultiItemSelectionBtn!=NULL && MultiItemSelectionBtn->isChecked()==true){
		MultiItemSelectionBtnDown();
	}
}