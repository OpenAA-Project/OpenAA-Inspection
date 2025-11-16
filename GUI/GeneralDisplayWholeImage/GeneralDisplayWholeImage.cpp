#include "GeneralDisplayWholeImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralDisplayWholeImage\GeneralDisplayWholeImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralDisplayWholeImage.h"
#include "XGUIFormBase.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XCriticalFunc.h"



static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"GeneralDisplayWholeImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display whole image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	(*Base)=new GUICmdReqWholeBmp	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendWholeBmp	(Base,QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralDisplayWholeImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);
	Data[0].Type					=/**/"QColor";
	Data[0].VariableNameWithRoute	=/**/"FrameColor";
	Data[0].Pointer					=&((GeneralDisplayWholeImage *)Instance)->FrameColor;
	Data[1].Type					=/**/"QColor";
	Data[1].VariableNameWithRoute	=/**/"ZoneColor";
	Data[1].Pointer					=&((GeneralDisplayWholeImage *)Instance)->ZoneColor;
	Data[2].Type					=/**/"QStringList";
	Data[2].VariableNameWithRoute	=/**/"RelatedPanel";
	Data[2].Pointer					=&((GeneralDisplayWholeImage *)Instance)->RelatedPanel;
	Data[3].Type					=/**/"bool";
	Data[3].VariableNameWithRoute	=/**/"Mastered";
	Data[3].Pointer					=&((GeneralDisplayWholeImage *)Instance)->Mastered;
	Data[4].Type					=/**/"bool";
	Data[4].VariableNameWithRoute	=/**/"ShowNG";
	Data[4].Pointer					=&((GeneralDisplayWholeImage *)Instance)->ShowNG;
	Data[5].Type					=/**/"bool";
	Data[5].VariableNameWithRoute	=/**/"BlinkNG";
	Data[5].Pointer					=&((GeneralDisplayWholeImage *)Instance)->BlinkNG;
	Data[6].Type					=/**/"int32";
	Data[6].VariableNameWithRoute	=/**/"ShowFixedPhase";
	Data[6].Pointer					=&((GeneralDisplayWholeImage *)Instance)->ShowFixedPhase;
	Data[7].Type					=/**/"int32";
	Data[7].VariableNameWithRoute	=/**/"ShowOnePage";
	Data[7].Pointer					=&((GeneralDisplayWholeImage *)Instance)->ShowOnePage;
	Data[8].Type					=/**/"bool";
	Data[8].VariableNameWithRoute	=/**/"FollowImagePanel";
	Data[8].Pointer					=&((GeneralDisplayWholeImage *)Instance)->FollowImagePanel;
	Data[9].Type					=/**/"QStringList";
	Data[9].VariableNameWithRoute	=/**/"RelatedOperations";
	Data[9].Pointer					=&((GeneralDisplayWholeImage *)Instance)->RelatedOperations;
	Data[10].Type					=/**/"int32";
	Data[10].VariableNameWithRoute	=/**/"MinUpdateSpanMilisec";
	Data[10].Pointer				=&((GeneralDisplayWholeImage *)Instance)->MinUpdateSpanMilisec;

	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralDisplayWholeImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//===================================================================================================
GeneralDisplayWholeImageDisplayImage::GeneralDisplayWholeImageDisplayImage(GeneralDisplayWholeImage *parent,LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,DisplayType dtype)
	:DisplayImage(Base,emitterRoot ,emitterName,dtype ,NULL),Parent(parent)
{
	SetFModeRepaintOnMouseMove(false);
}

bool	GeneralDisplayWholeImageDisplayImage::HookedExecutePaintFirst		(QPainter &pnt ,QImage &PntImage)
{
	bool	Ret=DisplayImage::HookedExecutePaintFirst	(pnt ,PntImage);
	return Ret;
}

bool	GeneralDisplayWholeImageDisplayImage::HookedExecutePaintLast		(QPainter &pnt ,QImage &PntImage)
{
	bool	Ret=DisplayImage::HookedExecutePaintLast	(pnt ,PntImage);
	return Ret;
}

//===================================================================================================
GeneralDisplayWholeImage::GeneralDisplayWholeImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),DisplayImageHooked(this)
{
	Mastered		=true;
	BlinkOn			=true;
	ShowNG			=false;
	BlinkNG			=false;
	FollowImagePanel=false;
	LastPaintTime	=0;
	LastWidth		=0;
	LastHeight		=0;

	ShowFixedPhase	=-1;
	ShowOnePage		=-1;
	FrameColor		=Qt::red;
	ZoneColor		=Qt::yellow;
	MainCanvas.setParent(this);
	MainCanvas.SetMode(mtFrameDraw::fdRectangle);
	MainCanvas.SetFrameColor(Qt::red);
	BmpReceiver			=NULL;
	BmpRequester		=NULL;
	AllocatedPageNumb	=0;
	LastFocusPanel		=NULL;
	PhaseNumbInPixMap	=0;
	PageNumbInPixMap	=0;
	MasterPixMap		=NULL;
	RPnt				=NULL;
	MinUpdateSpanMilisec=100;
	RelatedPanelPointer	=new GeneralDisplayWholeImageDisplayImage(this,Base,sRoot,sName,DisplayImage::__Master);

	MainCanvas.SetFModeRepaintOnMouseMove(false);
	connect(&MainCanvas,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter&)));
	connect(&MainCanvas,SIGNAL(SignalDrawEnd(void)),this,SLOT(SlotDrawEnd(void)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	RealPos.setTop(0);
	RealPos.setLeft(0);
	int	x1,y1,x2,y2;
	GetLayersBase()->GetArea(x1 ,y1 ,x2 ,y2);
	RealPos.setRight(x2);
	RealPos.setBottom(y2);
	TM.setInterval(500);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
}
GeneralDisplayWholeImage::~GeneralDisplayWholeImage()
{
	if(BmpRequester!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			delete	BmpRequester[page];
		}
		delete	[]BmpRequester;
	}
	if(BmpReceiver!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			delete	BmpReceiver[page];
		}
		delete	[]BmpReceiver;
	}
	if(RelatedPanelPointer!=NULL){
		delete	RelatedPanelPointer;
		RelatedPanelPointer=NULL;
	}
	AllocatedPageNumb=NULL;
}

void	GeneralDisplayWholeImage::Prepare(void)
{
	connect(GetLayersBase(),SIGNAL(SignalChangedXY())				,this,SLOT(SlotChangedXY()));
	connect(GetLayersBase(),SIGNAL(SignalChangedPhasePageLayer())	,this,SLOT(SlotChangedPhasePageLayer()));
	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentPhase())		,this,SLOT(SlotChangeCurrentPhase())	,Qt::QueuedConnection);
	connect(GetLayersBase(),SIGNAL(SignalChangedMasterImage(int,int,int)),this,SLOT(SlotChangedMasterImage(int ,int ,int)));

	AllocatePacketMap();
	MainCanvas.SetFrameColor(FrameColor);
	MainCanvas.SetZoomRate(GetZoomRate());
	RelatedPanelPointer->Prepare();
	TM.start();
}
void	GeneralDisplayWholeImage::ReadyParam(void)
{
	for(int i=0;i<RelatedPanel.count();i++){
		QString	str=RelatedPanel.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
		if(m!=NULL){
			connect(m,SIGNAL(SignalDraw(DisplayImage *)),this,SLOT(SlotDraw(DisplayImage *)));
		}
	}
	SetConnectionInMasterBuff();
}
void	GeneralDisplayWholeImage::ResizeAction()
{
	MainCanvas.resize(width(),height());
	RelatedPanelPointer->resize(width(),height());
	MainCanvas.SetZoomRate(GetZoomRate());
	ReleaseMasterPixMap();
}

void	GeneralDisplayWholeImage::SlotTimeout()
{
	if(ShowNG==true && BlinkNG==true){
		BlinkOn=!BlinkOn;
		MainCanvas.repaint();
	}
}
void	GeneralDisplayWholeImage::ShowInEdit(void)
{
	MainCanvas.repaint();
}

void	GeneralDisplayWholeImage::SlotDraw(DisplayImage *target)
{
	if(GetCurrentImagePanel()==target){
		QRect	OldPos=RealPos;
		RealPos.setLeft		(-target->GetMovx());
		RealPos.setTop		(-target->GetMovy());
		RealPos.setWidth	(target->GetCanvasWidth	()/target->GetZoomRate());
		RealPos.setHeight	(target->GetCanvasHeight()/target->GetZoomRate());
		if(RealPos!=OldPos){
			repaint();
		}
	}
}

void	GeneralDisplayWholeImage::SlotDrawEnd(void)
{
	RealPos.setTop	 (MainCanvas.SData.UData.RectangleData.y1);
	RealPos.setLeft	 (MainCanvas.SData.UData.RectangleData.x1);
	RealPos.setRight (MainCanvas.SData.UData.RectangleData.x2);
	RealPos.setBottom(MainCanvas.SData.UData.RectangleData.y2);

	bool	Found=false;
	if(RelatedOperations.count()>0){
		for(int i=0;i<RelatedOperations.count();i++){
			QString	str=RelatedOperations.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(ShowOnePage<0
				|| ShowOnePage==m->GetShowOnePage()){
					m->SetDrawPosition(MainCanvas.SData.UData.RectangleData.x1,MainCanvas.SData.UData.RectangleData.y1
									  ,MainCanvas.SData.UData.RectangleData.x2,MainCanvas.SData.UData.RectangleData.y2);
					Found=true;
				}
			}
		}
	}
	else
	if(RelatedPanel.count()>0){
		for(int i=0;i<RelatedPanel.count();i++){
			QString	str=RelatedPanel.value(i);
			GUIFormBase		*r=GetFormByName(str);
			if(r==NULL)
				continue;
			DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
			if(m!=NULL){
				if(ShowOnePage<0
				|| ShowOnePage==m->GetShowOnePage()){
					m->SetDrawPosition(MainCanvas.SData.UData.RectangleData.x1,MainCanvas.SData.UData.RectangleData.y1
									  ,MainCanvas.SData.UData.RectangleData.x2,MainCanvas.SData.UData.RectangleData.y2);
					Found=true;
				}
			}
		}
	}
	else if(FollowImagePanel==true){
		DisplayImage	*m=GetCurrentImagePanel();
		if(m!=NULL){
			if(ShowOnePage<0
			|| ShowOnePage==m->GetShowOnePage()){
				m->SetDrawPosition(MainCanvas.SData.UData.RectangleData.x1,MainCanvas.SData.UData.RectangleData.y1
								  ,MainCanvas.SData.UData.RectangleData.x2,MainCanvas.SData.UData.RectangleData.y2);
				Found=true;
			}
		}
	}
	MainCanvas.Clear();
	MainCanvas.repaint();
}

DisplayImage	*GeneralDisplayWholeImage::GetCurrentImagePanel(void)
{
	for(int CamNo=0;CamNo<GetParamGlobal()->TotalCameraNumb;CamNo++){
		IntList PageList;
		GetParamGlobal()->GetPageListFromCameraNo(CamNo ,PageList);
		for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
			int	Page=p->GetValue();
			for(int i=0;i<RelatedPanel.count();i++){
				QString	str=RelatedPanel.value(i);
				GUIFormBase		*r=GetFormByName(str);
				if(r==NULL)
					continue;
				DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
				if(m!=NULL){
					if(m->ShowOnePage<0){
						return m;
					}
					if(m->ShowOnePage==Page){
						return m;
					}
				}
			}
		}
	}
	//GUIFormBase	*GUIPointer[1000];
	//int	N=GetLayersBase()->EnumGUI(GUIPointer,sizeof(GUIPointer)/sizeof(GUIPointer[0]));
	//for(int i=0;i<N;i++){
	//	DisplayImage	*m=dynamic_cast<DisplayImage *>(GUIPointer[i]);
	//	if(m!=NULL){
	//		if(m->IsShown()==true){
	//			return m;
	//		}
	//	}
	//}

	return NULL;
}
void	GeneralDisplayWholeImage::SlotChangedMasterImage(int Phase ,int Page ,int Layer)
{
	if(0<=Phase && Phase<PhaseNumbInPixMap && MasterPixMap!=NULL){
		delete	MasterPixMap[Phase];
		MasterPixMap[Phase]=NULL;
	}
	Repaint();
}

double	GeneralDisplayWholeImage::GetZoomRate(void)
{
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

	double	zx=((double)MainCanvas.width())/((double)globalX2);
	double	zy=((double)MainCanvas.height())/((double)globalY2);
	double	ZoomRate=(zx>zy)?zy:zx;
	MainCanvas.SetZoomRate(ZoomRate);
	return ZoomRate;
}

void	GeneralDisplayWholeImage::AllocatePacketMap(void)
{
	if(BmpRequester!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			delete	BmpRequester[page];
		}
		delete	[]BmpRequester;
	}
	if(BmpReceiver!=NULL){
		for(int page=0;page<AllocatedPageNumb;page++){
			delete	BmpReceiver[page];
		}
		delete	[]BmpReceiver;
	}
	AllocatedPageNumb=GetPageNumb();
	BmpReceiver =new GUICmdSendWholeBmp*[AllocatedPageNumb];
	BmpRequester=new GUICmdReqWholeBmp *[AllocatedPageNumb];

	for(int page=0;page<AllocatedPageNumb;page++){
		BmpRequester[page]=new GUICmdReqWholeBmp (GetLayersBase(),QString(sRoot),QString(sName),page);
		BmpReceiver [page]=new GUICmdSendWholeBmp(GetLayersBase(),QString(sRoot),QString(sName),page);
	}
}
void	GeneralDisplayWholeImage::BuildForShow(void)
{
	AllocatePacketMap();
	MainCanvas.repaint();
}

void	GeneralDisplayWholeImage::ShowInPlayer(int64 shownInspectionID)
{
	DWORD	t=::GetComputerMiliSec();
	DWORD	WorkingTime;
	if(t-LastPaintTime>=MinUpdateSpanMilisec){
		if(LastWidth!=width() || LastHeight!=height()){
			ReleaseMasterPixMap();
			AllocatePixmap();
			LastWidth	=width();
			LastHeight	=height();
		}
		DWORD	t1	=::GetComputerMiliSec();
		//MainCanvas.repaint();
		MainCanvas.update();
		WorkingTime	=::GetComputerMiliSec()-t1;

		LastPaintTime=t;
	}
}
void	GeneralDisplayWholeImage::Repaint(void)
{
	//MainCanvas.repaint();
}


void	GeneralDisplayWholeImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetZoomRate	*CmdGetZoomRateVar=dynamic_cast<CmdGetZoomRate *>(packet);
	if(CmdGetZoomRateVar!=NULL){
		CmdGetZoomRateVar->ZoomRate=GetZoomRate();
		return;
	}
	CmdSetRealPosition	*CmdSetRealPositionVar=dynamic_cast<CmdSetRealPosition *>(packet);
	if(CmdSetRealPositionVar!=NULL){
		RealPos	=CmdSetRealPositionVar->RealPos;
		return;
	}
}
void	GeneralDisplayWholeImage::SetConnectionInMasterBuff(void)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			DataInPage *Pg=Ph->GetPageData(page);
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				DataInLayer	*Lp=Pg->GetLayerData(layer);
				connect(Lp->GetMasterBuffPointer(),SIGNAL(SignalChanged()),this,SLOT(SlotMemoryChanged()));
			}
		}
	}
}
void	GeneralDisplayWholeImage::SlotChangedXY()
{
	MainCanvas.SetZoomRate(GetZoomRate());
	ReleaseMasterPixMap();
	AllocatePixmap();
}
void	GeneralDisplayWholeImage::SlotChangedPhasePageLayer()
{
	MainCanvas.SetZoomRate(GetZoomRate());
	ReleaseMasterPixMap();
	AllocatePacketMap();
	AllocatePixmap();
}
void	GeneralDisplayWholeImage::SlotChangeCurrentPhase()
{
	MainCanvas.repaint();
}
void	GeneralDisplayWholeImage::SlotMemoryChanged()
{
	MainCanvas.SetZoomRate(GetZoomRate());
	ReleaseMasterPixMap();
	AllocatePixmap();
}
void	GeneralDisplayWholeImage::AllocatePixmap(void)
{
	PhaseNumbInPixMap=GetPhaseNumb();
	if(MasterPixMap==NULL){
		MasterPixMap=new QPixmap**[PhaseNumbInPixMap];
		for(int phase=0;phase<PhaseNumbInPixMap;phase++){
			MasterPixMap[phase]=NULL;
		}
	}
	PageNumbInPixMap=GetPageNumb();
	for(int phase=0;phase<PhaseNumbInPixMap;phase++){
		if(MasterPixMap[phase]==NULL){
			MasterPixMap[phase]=new QPixmap*[PageNumbInPixMap];
			for(int page=0;page<PageNumbInPixMap;page++){
				(MasterPixMap[phase])[page]=NULL;
			}
		}
	}
}
void	GeneralDisplayWholeImage::ReleaseMasterPixMap(void)
{
	if(MasterPixMap!=NULL){
		for(int phase=0;phase<PhaseNumbInPixMap;phase++){
			for(int page=0;page<PageNumbInPixMap;page++){
				if(MasterPixMap!=NULL){
					if(MasterPixMap[phase]!=NULL){
						if((MasterPixMap[phase])[page]!=NULL){
							delete	(MasterPixMap[phase])[page];
							(MasterPixMap[phase])[page]=NULL;
						}
					}
				}
			}
			delete	[]MasterPixMap[phase];
			MasterPixMap[phase]=NULL;
		}
		delete	[]MasterPixMap;
		MasterPixMap=NULL;
	}
}
void	GeneralDisplayWholeImage::SetHookInPaintFirst(FunctionServerClass *Obj	,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage),bool Highest)
{
	RelatedPanelPointer->SetHookInPaintFirst(Obj,Function,Highest);
}
void	GeneralDisplayWholeImage::SetHookInPaintLast(FunctionServerClass *Obj	,bool (*Function)(FunctionServerClass *Obj,GUIFormBase *TartgetForm,QPainter &pnt ,QImage &PntImage),bool Highest)
{
	RelatedPanelPointer->SetHookInPaintLast(Obj,Function,Highest);
}
