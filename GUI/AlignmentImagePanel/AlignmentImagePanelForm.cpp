/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\AlignmentImagePanel\AlignmentImagePanelForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "AlignmentImagePanelFormResource.h"
#include "AlignmentImagePanel.h"
#include "XCrossObj.h"
#include "XGUI.h"
#include "AlignmentImagePropertyPacket.h"
#include "XGeneralFunc.h"
#include "XPacketAlignment.h"
#include "ImagePanelTools.h"
#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

//==================================================================================================
AlignmentImagePanel::AlignmentImagePanel(LayersBase *Base,QWidget *parent)
:DisplayImageWithAlgorithm(Base,/**/"Basic" ,/**/"Alignment",QString(sRoot),QString(sName),__Master,parent)
{
	AreaButton	=new mtToolButtonWithBalloon(NULL);
	InsideButton=new mtToolButtonWithBalloon(NULL);
	ShiftButton	=new mtToolButtonWithBalloon(NULL);
	OutsideButton=new mtToolButtonWithBalloon(NULL);

	ABar.setParent(this);
	ABar.move(0,0);

	ItemsBmpCounts=GetPageNumb();
	ItemsBmpReceiver	=new GUICmdSendAlignmentItemsBmp*[ItemsBmpCounts];
	ItemsBmpRequester	=new GUICmdReqAlignmentItemsBmp*[ItemsBmpCounts];
	for(int page=0;page<ItemsBmpCounts;page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		ItemsBmpReceiver[page]=new GUICmdSendAlignmentItemsBmp(GetLayersBase(),sRoot,sName,globalPage);
		ItemsBmpRequester[page]=new GUICmdReqAlignmentItemsBmp(GetLayersBase(),sRoot,sName,globalPage);		
	}
}

AlignmentImagePanel::~AlignmentImagePanel(void)
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


void	AlignmentImagePanel::Prepare(void)
{
	int	ButtonSize=32+4;
	int	X=0;
	//AreaButton.setGeometry(X,0,ButtonSize,ButtonSize);
	X+=ButtonSize;
	connect(AreaButton,SIGNAL(clicked(bool)),this,SLOT(AreaButtonDown(bool)));
	
	AreaButton->setMessage(LangSolver.GetString(AlignmentImagePanelForm_LS,LID_0)/*"Draw Area zone"*/);
	AreaButton->setAutoExclusive(true);
	AreaButton->setCheckable(true);
	AreaButton->setAutoRaise(true);
	if(AreaButton->icon().isNull()){
		if(IconSize<=32){
			AreaButton->setIcon(QIcon(/**/":Resources/AlignmentArea32.png"));
		}
		else if(IconSize<=64){
			AreaButton->setIcon(QIcon(/**/":Resources/AlignmentArea64.png"));
		}
		else{
			AreaButton->setIcon(QIcon(/**/":Resources/AlignmentArea100.png"));
		}
	}
    ABar.addWidget(AreaButton);
  
//InsideButton.setGeometry(X,0,ButtonSize,ButtonSize);
	X+=ButtonSize;
	connect(InsideButton,SIGNAL(clicked(bool)),this,SLOT(InsideButtonDown(bool)));
	InsideButton->setMessage(LangSolver.GetString(AlignmentImagePanelForm_LS,LID_1)/*"Draw Inside zone"*/);
	InsideButton->setAutoExclusive(true);
	InsideButton->setCheckable(true);
	InsideButton->setAutoRaise(true);
	if(InsideButton->icon().isNull()){
		if(IconSize<=32){
            InsideButton->setIcon(QIcon(/**/":Resources/AlignmentInside32.png"));
		}
		else if(IconSize<=64){
			InsideButton->setIcon(QIcon(/**/":Resources/AlignmentInside64.png"));
		}
		else{
			InsideButton->setIcon(QIcon(/**/":Resources/AlignmentInside100.png"));
		}
	}
    ABar.addWidget(InsideButton);

//ShiftButton.setGeometry(X,0,ButtonSize,ButtonSize);
	X+=ButtonSize;
	connect(ShiftButton,SIGNAL(clicked(bool)),this,SLOT(ShiftButtonDown(bool)));
	ShiftButton->setMessage(LangSolver.GetString(AlignmentImagePanelForm_LS,LID_2)/*"Draw Shift zone"*/);
	ShiftButton->setAutoExclusive(true);
	ShiftButton->setCheckable(true);
	ShiftButton->setAutoRaise(true);
	if(ShiftButton->icon().isNull()){
		if(IconSize<=32){
		    ShiftButton->setIcon(QIcon(/**/":Resources/AlignmentShift32.png"));
		}
		else if(IconSize<=64){
			ShiftButton->setIcon(QIcon(/**/":Resources/AlignmentShift64.png"));
		}
		else{
			ShiftButton->setIcon(QIcon(/**/":Resources/AlignmentShift100.png"));
		}
	}
	ABar.addWidget(ShiftButton);

//OutsideButton.setGeometry(X,0,ButtonSize,ButtonSize);
	X+=ButtonSize;
	connect(OutsideButton,SIGNAL(clicked(bool)),this,SLOT(OutsideButtonDown(bool)));
	OutsideButton->setMessage(LangSolver.GetString(AlignmentImagePanelForm_LS,LID_3)/*"Draw Outside zone"*/);
	OutsideButton->setAutoExclusive(true);
	OutsideButton->setCheckable(true);
	OutsideButton->setAutoRaise(true);
	if(OutsideButton->icon().isNull()){
		if(IconSize<=32){
            OutsideButton->setIcon(QIcon(/**/":Resources/AlignmentOutside32.png"));
		}
		else if(IconSize<=64){
			OutsideButton->setIcon(QIcon(/**/":Resources/AlignmentOutside64.png"));
		}
		else{
			OutsideButton->setIcon(QIcon(/**/":Resources/AlignmentOotside100.png"));
		}
	}
    ABar.addWidget(OutsideButton);

	ABar.resize(X,ButtonSize);
	SetTopPosition(ButtonSize);
	DisplayImageWithAlgorithm::Prepare();
}

void AlignmentImagePanel::AreaButtonDown (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAlignmentButton	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.DAttr=AlignmentDrawAttr::_AreaMode;
		RCmd.Send(NULL,globalPage,0);
	}
	Repaint();
	ReEntrant=false;
}
void AlignmentImagePanel::InsideButtonDown (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAlignmentButton	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.DAttr=AlignmentDrawAttr::_InsideMode;
		RCmd.Send(NULL,globalPage,0);
	}
	Repaint();
	ReEntrant=false;
}
void AlignmentImagePanel::ShiftButtonDown (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAlignmentButton	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.DAttr=AlignmentDrawAttr::_ShiftMode;
		RCmd.Send(NULL,globalPage,0);
	}
	Repaint();
	ReEntrant=false;
}

void AlignmentImagePanel::OutsideButtonDown (bool checked)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdSetAlignmentButton	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.DAttr=AlignmentDrawAttr::_OutsideMode;
		RCmd.Send(NULL,globalPage,0);
	}
	Repaint();
	ReEntrant=false;
}
void	AlignmentImagePanel::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdSetAlignmentButton	*GUICmdSetAlignmentButtonVar=dynamic_cast<GUICmdSetAlignmentButton *>(packet);
	if(GUICmdSetAlignmentButtonVar!=NULL){
		if(GUICmdSetAlignmentButtonVar->DAttr==AlignmentDrawAttr::_AreaMode)
			AreaButton->click();
		else if(GUICmdSetAlignmentButtonVar->DAttr==AlignmentDrawAttr::_InsideMode)
			InsideButton->click();
		else if(GUICmdSetAlignmentButtonVar->DAttr==AlignmentDrawAttr::_OutsideMode)
			OutsideButton->click();
		else if(GUICmdSetAlignmentButtonVar->DAttr==AlignmentDrawAttr::_ShiftMode)
			ShiftButton->click();
	}
}

AlgorithmDrawAttr	*AlignmentImagePanel::CreateDrawAttrPointer(void)
{
	GUICmdReqAlignmentDrawMode	DrawMode(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentForm" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
	}

	AlignmentDrawAttr	*A=new AlignmentDrawAttr();
	
	if(AreaButton->isChecked()==true)
		A->DrawMode=AlignmentDrawAttr::_AreaMode;
	else if(InsideButton->isChecked()==true)
		A->DrawMode=AlignmentDrawAttr::_InsideMode;
	else if(ShiftButton->isChecked()==true)
		A->DrawMode=AlignmentDrawAttr::_ShiftMode;
	else if(OutsideButton->isChecked()==true)
		A->DrawMode=AlignmentDrawAttr::_OutsideMode;
	else
		A->DrawMode=AlignmentDrawAttr::_AreaMode;

	for(ReqAlignmentAreaList *a=DrawMode.AList.GetFirst();a!=NULL;a=a->GetNext()){
		ReqAlignmentAreaList *b=new ReqAlignmentAreaList();
		*b=*a;
		A->AList.AppendList(b);
	}
	return A;
}

void	AlignmentImagePanel::DrawEndAfterOperation(FlexArea &area)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentForm" ,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentDrawEnd	Da(GetLayersBase());
		Da.Area=area;
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentImagePanel::ButtonExecuteDeleteSelected(void)
{
	DisplayImageWithAlgorithm::ButtonExecuteDeleteSelected();
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyAlignmentForm" ,/**/"");
	if(GProp!=NULL){
		GUICmdAlignmentReflectChangeItems	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}
void	AlignmentImagePanel::StartPage(void)
{
	ExecuteClickButton(/**/"DrawBtn");
	DisplayImageWithAlgorithm::StartPage();
}

void	AlignmentImagePanel::DrawAfterImage(QPainter &pnt ,QImage &PntImage)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	IntList	LayerList;
	CmdReqImageLayer	DrawMode(GetLayersBase(),GetLayerNumb(0));
	GUIFormBase	*TProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"ImageControlTools" ,ImageControlToolsName);
	if(TProp!=NULL){
		TProp->TransmitDirectly(&DrawMode);
		LayerList=DrawMode.LayerList;
	}
	if(DrawMode.DType==DisplayImage::__Target || DrawMode.DType==DisplayImage::__DelayedView){
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
			int	Dx2	=P->GetOutlineOffset()->x+GetDotPerLine(page);
			int	Dy2	=P->GetOutlineOffset()->x+GetMaxLines(page);
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);
			ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, GetCanvasWidth(), GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==false)
				continue;
			ItemsBmpRequester[N]->Data.ZoomRate		=GetZoomRate();
			ItemsBmpRequester[N]->Data.MovX			=GetMovx()+P->GetOutlineOffset()->x;
			ItemsBmpRequester[N]->Data.MovY			=GetMovy()+P->GetOutlineOffset()->y;

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
	else{
		DisplayImageWithAlgorithm::DrawAfterImage(pnt ,PntImage);
	}
	ReEntrant=false;
}

//=======================================================================

GUICmdReqAddAlignment::GUICmdReqAddAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	GlobalPage	=globalPage;
}

bool	GUICmdReqAddAlignment::Save(QIODevice *f)
{
	f->write((const char *)&GlobalPage,sizeof(GlobalPage));
	Area.Write(f);
	return(true);
}
bool	GUICmdReqAddAlignment::Load(QIODevice *f)
{
	f->read((char *)&GlobalPage,sizeof(GlobalPage));
	Area.Read(f);
	return(true);
}


void	GUICmdReqAddAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{

}

GUICmdSetAlignmentButton::GUICmdSetAlignmentButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetAlignmentButton::Save(QIODevice *f)
{
	f->write((const char *)&DAttr,sizeof(DAttr));
	return(true);
}
bool	GUICmdSetAlignmentButton::Load(QIODevice *f)
{
	f->read((char *)&DAttr,sizeof(DAttr));
	return(true);
}
void	GUICmdSetAlignmentButton::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(this);
	}
}
//=================================================================================================

GUICmdReqAlignmentItemsBmp::GUICmdReqAlignmentItemsBmp(LayersBase *Base
									,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUICmdReqAlignmentItemsBmp::~GUICmdReqAlignmentItemsBmp(void)
{
}

bool	GUICmdReqAlignmentItemsBmp::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	if(LayerList.Load(f)==false)
		return false;

	return(true);
}
bool	GUICmdReqAlignmentItemsBmp::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(LayerList.Save(f)==false)
		return false;

	return(true);
}

void	GUICmdReqAlignmentItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*SelectedAlgorithm=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Alignment");
	GUICmdSendAlignmentItemsBmp	*SendBack=(GUICmdSendAlignmentItemsBmp *)((GetSendBackPacket()==NULL)?new GUICmdSendAlignmentItemsBmp(GetLayersBase(),EmitterRoot,EmitterName) : GetSendBackPacket())->SetLocalPage(localPage);
	SendBack->MakeImage(LayerList
						,Data.Gx1,Data.Gy1 ,Data.Gx2,Data.Gy2
						,Data.Dx1,Data.Dy1 ,Data.Dx2,Data.Dy2
						,Data.MovX,Data.MovY,Data.ZoomRate
						,localPage
						,Data.MoveGlobalDx ,Data.MoveGlobalDy
						,SelectedAlgorithm
						,*GetLayersBase());

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
GUICmdSendAlignmentItemsBmp::GUICmdSendAlignmentItemsBmp(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	IData=NULL;
	PntFromIData=NULL;
}

GUICmdSendAlignmentItemsBmp::~GUICmdSendAlignmentItemsBmp(void)
{
	if(PntFromIData!=NULL)
		delete	PntFromIData;
	PntFromIData=NULL;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

bool	GUICmdSendAlignmentItemsBmp::Load(QIODevice *f)
{
	if(IData==NULL)
		IData=new QImage();
	IData->load(f,/**/"PNG");
	return(true);
}
bool	GUICmdSendAlignmentItemsBmp::Save(QIODevice *f)
{
	IData->save(f,/**/"PNG");
	return(true);
}

void	GUICmdSendAlignmentItemsBmp::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}


void	GUICmdSendAlignmentItemsBmp::MakeImage(
								  IntList &LayerList
								 ,int Gx1,int Gy1 ,int Gx2,int Gy2
								 ,int Dx1,int Dy1 ,int Dx2,int Dy2
								 ,int MovX,int MovY, double ZoomRate
								 ,int localPage
								 ,int MoveGlobalDx ,int MoveGlobalDy
								 ,AlgorithmBase	*L
								 ,LayersBase &LocalLBase)
{
	//DataInPage *P=LocalLBase.GetPageData(localPage);
	int	LGx=Gx2-Gx1;
	int	LGy=Gy2-Gy1;

	if(L==NULL)
		return;
	if(IData!=NULL && (IData->width()!=LGx || IData->height()!=LGy)){
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		delete	IData;
		IData=NULL;
		PntFromIData=NULL;
	}
	if(IData==NULL){
		IData=new QImage(LGx,LGy,QImage::Format_ARGB32);
		if(PntFromIData!=NULL)
			delete	PntFromIData;
		PntFromIData=NULL;
	}
	if(PntFromIData==NULL)
		PntFromIData=new QPainter(IData);
	IData->fill(0);
	ResultInspection	*R=LocalLBase.GetCurrentResultForDraw();
	if(R!=NULL){
		ResultBaseForAlgorithmRoot *Res=R->GetResultBaseForAlgorithm(L);
		if(Res!=NULL){
			int	Phase=GetLayersBase()->GetCurrentPhase();
			ResultBasePhase		*Ph=Res->GetPageDataPhase(Phase);
			L->GetPageData(localPage)->DrawResultItem(Ph->GetPageData(localPage),LayerList,*IData ,*PntFromIData,MovX-Gx1/ZoomRate ,MovY-Gy1/ZoomRate ,ZoomRate,false);
		}
	}
}
//=======================================================================

