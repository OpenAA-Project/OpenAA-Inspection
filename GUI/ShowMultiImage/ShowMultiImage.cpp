/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMultiImage\ShowMultiImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowMultiImage.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"ShowMultiImage";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show multiple image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendImagePartial	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowMultiImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<14)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"ImageCountX";
	Data[0].Pointer				 =&((ShowMultiImage *)Instance)->ImageCountX;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"ImageCountY";
	Data[1].Pointer				 =&((ShowMultiImage *)Instance)->ImageCountY;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"FontFileName";
	Data[2].Pointer				 =&((ShowMultiImage *)Instance)->FontFileName;

	return(3);
}
//==================================================================================================
void	ChildImagePanel::ImageBufferPhase::ImageBufferPage::ImageBufferLayer::Allocate(int DotPerLine ,int MaxLines)
{
	Image.Set(0,0,DotPerLine,MaxLines);
}

void	ChildImagePanel::ImageBufferPhase::ImageBufferPage::Allocate(int LayerNumb ,int DotPerLine ,int MaxLines)
{
	BufferLayer.RemoveAll();
	for(int layer=0;layer<LayerNumb;layer++){
		ImageBufferLayer	*L=new ImageBufferLayer(layer ,this,ParentImage);
		L->Allocate(DotPerLine ,MaxLines);
		BufferLayer.AppendList(L);
	}
	OutlineOffset	=*GetLayersBase()->GetPageDataPhase(Parent->Phase)->GetPageData(Page)->GetOutlineOffset();
}
ImageBuffer	*ChildImagePanel::ImageBufferPhase::ImageBufferPage::GetImage(int Layer)
{
	ImageBufferLayer	*L=BufferLayer.GetItem(Layer);
	if(L!=NULL){
		return L->GetImage();
	}
	return NULL;
}

void	ChildImagePanel::ImageBufferPhase::Allocate(int PageNumb ,int LayerNumb ,int DotPerLine ,int MaxLines)
{
	BufferPage.RemoveAll();
	for(int page=0;page<PageNumb;page++){
		ImageBufferPage	*P=new ImageBufferPage(page,this,ParentImage);
		P->Allocate(LayerNumb ,DotPerLine ,MaxLines);
		BufferPage.AppendList(P);
	}
}
ImageBuffer	*ChildImagePanel::ImageBufferPhase::GetImage(int Page ,int Layer)
{
	ImageBufferPage	*P=BufferPage.GetItem(Page);
	if(P!=NULL){
		return P->GetImage(Layer);
	}
	return NULL;
}

void	ChildImagePanel::ImageBufferPhase::GetXY(int &x1,int &y1,int &x2,int &y2)
{
	for(ImageBufferPage	*P=BufferPage.GetFirst();P!=NULL;P=P->GetNext()){
		int	tx1=P->GetOutlineOffset().x;
		int	ty1=P->GetOutlineOffset().y;
		int	tx2=P->GetOutlineOffset().x+GetLayersBase()->GetDotPerLine(P->GetPage());
		int	ty2=P->GetOutlineOffset().y+GetLayersBase()->GetMaxLines(P->GetPage());
		x1=min(x1,tx1);
		y1=min(y1,ty1);
		x2=max(x2,tx2);
		y2=max(y2,ty2);
	}
}

//----------------------------------------------------------------

ChildImagePanel::ChildImagePanel(LayersBase *Base,ShowMultiImage *parent)
	:mtGraphicUnit(parent),ServiceForLayers(Base)
	,Parent(parent)
{
	Img=NULL;
	CurrentPhase	=0;

	bool	ErrorOccurs;
	if(!connect(this,SIGNAL(SignalOnPaint(QPainter &)) ,this,SLOT(SlotOnPaint(QPainter &)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseMove(int ,int)) ,this,SLOT(SlotMouseMove(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseLDown(int ,int)),this,SLOT(SlotMouseLDown(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseRDown(int ,int)),this,SLOT(SlotMouseRDown(int ,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalMouseWheel(int,int,int))	,this,SLOT(SlotMouseWheel(int,int,int)))){
		ErrorOccurs=true;
	}
	if(!connect(this ,SIGNAL(SignalShiftAll(void))	,this,SLOT(SlotShiftAll(void)))){
		ErrorOccurs=true;
	}
}

ChildImagePanel::~ChildImagePanel(void)
{
	if(Img!=NULL)
		delete	Img;
	Img=NULL;
}
void	ChildImagePanel::Allocate(int PhaseNumb ,int PageNumb ,int LayerNumb ,int DotPerLine ,int MaxLines)
{
	BufferPhase.RemoveAll();
	for(int phase=0;phase<PhaseNumb;phase++){
		ImageBufferPhase	*P=new ImageBufferPhase(phase,this);
		P->Allocate(PhaseNumb,LayerNumb ,DotPerLine ,MaxLines);
		BufferPhase.AppendList(P);
	}
	ImageBufferPhase	*Ph=BufferPhase[0];
	if(Ph==NULL)
		return;

	int	x1,y1,x2,y2;
	x1=y1=x2=y2=0;
	Ph->GetXY(x1,y1,x2,y2);
	SetAreaSize(x2,y2);
}
ImageBuffer	*ChildImagePanel::GetImage(int Phase ,int Page ,int Layer)
{
	ImageBufferPhase	*P=BufferPhase.GetItem(Phase);
	if(P!=NULL){
		return P->GetImage(Page,Layer);
	}
	return NULL;
}
void	ChildImagePanel::SlotOnPaint(QPainter &pnt)
{
	int	Phase=GetLayersBase()->GetCurrentPhase();

	ImageBufferPhase	*Ph=BufferPhase[Phase];
	if(Ph==NULL)
		return;
	if(CurrentPhase!=Phase){
		int	x1,y1,x2,y2;
		x1=y1=x2=y2=0;
		Ph->GetXY(x1,y1,x2,y2);
		SetAreaSize(x2,y2);
	}

	int	W=GetCanvasWidth();
	int	H=GetCanvasHeight();
	if(Img==NULL || Img->width()!=W || Img->height()!=H){
		if(Img!=NULL)
			delete	Img;
		Img=new QImage(W,H,QImage::Format_ARGB32);
	}
	Img->fill(Qt::black);
	double	Z=1.0/GetZoomRate();
	for(int page=0;page<GetPageNumb();page++){
		DataInPage	*Dp=GetLayersBase()->GetPageData(page);
		ImageBufferPhase::ImageBufferPage	*Pg=Ph->GetPageData(page);
		int	gx1=(Pg->GetOutlineOffset().x+GetMovx())*GetZoomRate();
		int	gy1=(Pg->GetOutlineOffset().y+GetMovy())*GetZoomRate();
		int	gx2=(Pg->GetOutlineOffset().x+GetMovx()+Dp->GetDotPerLine()	)*GetZoomRate();
		int	gy2=(Pg->GetOutlineOffset().y+GetMovy()+Dp->GetMaxLines()	)*GetZoomRate();

		gx1=max(gx1,0);
		gy1=max(gy1,0);
		gx2=min(gx2,W);
		gy2=min(gy2,H);
		int	X1=Clipping((int)(gx1*Z-Pg->GetOutlineOffset().x-GetMovx()),0,Dp->GetDotPerLine());
		int	X2=Clipping((int)(gx2*Z-Pg->GetOutlineOffset().x-GetMovx()),0,Dp->GetDotPerLine());
		for(int y=gy1;y<gy2;y++){
			QRgb	*d=(QRgb *)Img->scanLine(y);
			d+=gx1;
			int	Y =Clipping((int)(y*Z-Pg->GetOutlineOffset().y-GetMovy()),0,Dp->GetMaxLines());
			if(Dp->GetLayerNumb()==1){
				BYTE	*s=Pg->GetImage(0)->GetY(Y);
				
				for(double DX=X1;DX<X2;DX+=Z,d++){
					BYTE	c=s[(int)DX];
					*d=qRgba(c,c,c,255);
				}
			}
			else
			if(Dp->GetLayerNumb()==2){
				BYTE	*s0=Pg->GetImage(0)->GetY(Y);
				BYTE	*s1=Pg->GetImage(1)->GetY(Y);
				for(double DX=X1;DX<X2;DX+=Z,d++){
					BYTE	c0=s0[(int)DX];
					BYTE	c1=s1[(int)DX];
					*d=qRgba(c0,c0,c1,255);
				}
			}
			else
			if(Dp->GetLayerNumb()>=3){
				BYTE	*s0=Pg->GetImage(0)->GetY(Y);
				BYTE	*s1=Pg->GetImage(1)->GetY(Y);
				BYTE	*s2=Pg->GetImage(2)->GetY(Y);
				
				for(double DX=X1;DX<X2;DX+=Z,d++){
					int	X=(int)DX;
					BYTE	c0=s0[X];
					BYTE	c1=s1[X];
					BYTE	c2=s2[X];
					*d=qRgba(c0,c1,c2,255);
				}
			}
		}
	}
	pnt.drawImage(0,0,*Img);
}
void	ChildImagePanel::SlotMouseMove(int ,int)
{
}
void	ChildImagePanel::SlotMouseLDown(int globalX,int globalY)
{
	if(GetZoomRate()<Parent->MaxZoomValue){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		ZoomIn(Gx ,Gy);
		Parent->DrawAll(this,GetZoomRate(),GetMovx(),GetMovy());
	}
}
void	ChildImagePanel::SlotMouseRDown(int globalX,int globalY)
{
	if(GetZoomRate()>Parent->MinZoomValue){
		int	Gx=(globalX+GetMovx())*GetZoomRate();
		int	Gy=(globalY+GetMovy())*GetZoomRate();
		ZoomOut(Gx ,Gy);
		Parent->DrawAll(this,GetZoomRate(),GetMovx(),GetMovy());
	}
}
void	ChildImagePanel::SlotMouseWheel(int delta ,int globalX,int globalY)
{
	if(delta>0){
		//int	GlobalPage=GetLayersBase()->GetGlobalPage(globalX,globalY);
		if(GetZoomRate()<Parent->MaxZoomValue){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomIn(Gx ,Gy);
			Parent->DrawAll(this,GetZoomRate(),GetMovx(),GetMovy());
		}
	}
	else if(delta<0){
		//int	GlobalPage=GetLayersBase()->GetGlobalPage(globalX,globalY);
		if(GetZoomRate()>Parent->MinZoomValue){
			int	Gx=(globalX+GetMovx())*GetZoomRate();
			int	Gy=(globalY+GetMovy())*GetZoomRate();
			ZoomOut(Gx ,Gy);
			Parent->DrawAll(this,GetZoomRate(),GetMovx(),GetMovy());
		}
	}
}
void	ChildImagePanel::SlotShiftAll(void)
{
	Parent->DrawAll(this,GetZoomRate(),GetMovx(),GetMovy());
}

//--------------------------------
ImageButton::ImageButton(void)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}

void	ImageButton::SlotClicked()
{
	emit	SignalClicked(ID);
}
//==================================================================================================
ShowMultiImage::ShowMultiImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ButtonFileName			=NULL;
	ChildPanel				=NULL;
	AllocatedChildPanelCount=0;
	ImageCountX	=1;
	ImageCountY	=1;
	MaxZoomValue=10.0;
	MinZoomValue=0.001;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
ShowMultiImage::~ShowMultiImage(void)
{
	if(ChildPanel!=NULL){
		for(int i=0;i<AllocatedChildPanelCount;i++){
			delete	ChildPanel[i];
		}
		delete	[]ChildPanel;
		ChildPanel=NULL;
	}
	AllocatedChildPanelCount=0;
	if(ButtonFileName!=NULL){
		delete	[]ButtonFileName;
	}
}

void	ShowMultiImage::Prepare(void)
{
	AllocatedChildPanelCount	=ImageCountX*ImageCountY;
	ChildPanel=new ChildImagePanel*[AllocatedChildPanelCount];
	for(int i=0;i<AllocatedChildPanelCount;i++){
		ChildPanel[i]=new ChildImagePanel(GetLayersBase(),this);
		ChildPanel[i]->Allocate(GetPhaseNumb()
								,GetPageNumb()
								,GetLayerNumb(0)
								,GetDotPerLine(0)
								,GetMaxLines(0));
		ChildPanel[i]->ZoomDrawWhole();
	}
	ButtonFileName	=new ImageButton[AllocatedChildPanelCount];
	for(int i=0;i<AllocatedChildPanelCount;i++){
		ButtonFileName[i].setParent(this);
		ButtonFileName[i].setFont(FontFileName);
		ButtonFileName[i].SetID(i);
		connect(&ButtonFileName[i],SIGNAL(SignalClicked(int)),this,SLOT(SlotClicked(int)));
	}
}

void	ShowMultiImage::ResizeAction()
{
	QFontInfo	TitleFontInfo(FontFileName);
	int	YLen=TitleFontInfo.pixelSize()+8;

	int	W=(width()-(ImageCountX+1)*4)/ImageCountX;
	int	H=(height()-(ImageCountY+1)*4)/ImageCountY;
	int	N=0;
	for(int y=0;y<ImageCountY;y++){
		for(int x=0;x<ImageCountX;x++){
			if(N<AllocatedChildPanelCount){
				ChildPanel[N]->setGeometry(4+(W+4)*x,4+(H+4)*y+YLen+1,W,H-YLen-1);
				ButtonFileName[N].setGeometry(4+(W+4)*x,4+(H+4)*y,W,YLen);
				N++;
			}
		}
	}
}

void	ShowMultiImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadImages	*CmdLoadImagesVar=dynamic_cast<CmdLoadImages *>(packet);
	if(CmdLoadImagesVar!=NULL){
		for(int i=0;i<CmdLoadImagesVar->FileNames.count() && i<AllocatedChildPanelCount;i++){
			LoadImage(CmdLoadImagesVar->FileNames[i],ChildPanel[i]);
			QFileInfo	FInfo(CmdLoadImagesVar->FileNames[i]);
			ChildPanel[i]->FileName	=CmdLoadImagesVar->FileNames[i];
			ButtonFileName[i].setText(FInfo.fileName());
		}
		return;
	}
	CmdReqPanelCount	*CmdReqPanelCountVar=dynamic_cast<CmdReqPanelCount *>(packet);
	if(CmdReqPanelCountVar!=NULL){
		CmdReqPanelCountVar->PanelCount	=ImageCountX*ImageCountY;
		return;
	}
}

bool	ShowMultiImage::LoadImage(const QString &PixFileName,ChildImagePanel *CPanel)
{
	QFile	RFile(PixFileName);
	if(RFile.open(QIODevice::ReadOnly)==false)
		return false;

	int	Ver;
	if(::Load(&RFile,Ver)==false)
		return false;
	int	iDotPerLine;
	int	iMaxLines;
	int	iPageNumb;
	int	iLayerNumb;
	int	iYCountBase;
	int	iPhaseNumb=1;
	if(Ver>=2){
		if(::Load(&RFile,iPhaseNumb)==false)
			return false;
	}
	if(::Load(&RFile,iPageNumb)==false)
		return false;
	if(::Load(&RFile,iLayerNumb)==false)
		return false;
	if(::Load(&RFile,iDotPerLine)==false)
		return false;
	if(::Load(&RFile,iMaxLines)==false)
		return false;
	if(::Load(&RFile,iYCountBase)==false)
		return false;

	int	ProcessCount[10000];
	for(int page=0;page<GetPageNumb();page++){
		ProcessCount[page]=0;
	}
	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<iPageNumb && page<GetPageNumb();page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines){
					YCount=iMaxLines-TopY;
				}
			}
			ProcessCount[page]++;
		}

		for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<GetMaxLines(page) && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines){
					YCount=iMaxLines-TopY;
				}
				ProcessCount[page]++;
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines){
						YCount=iMaxLines-TopY;
					}
					ProcessCount[page]++;
				}			
			}
			ProcessCount[page]++;
		}
	}

	GetLayersBase()->ShowProcessingForm ("Load PIX image in target buffer");
	GetLayersBase()->SetMaxProcessing(ProcessCount[0]);

	for(int phase=0;phase<iPhaseNumb && phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb() && page<iPageNumb;page++){
			int	YCount=iYCountBase;
			int	TopY;
			for(TopY=0;TopY<GetMaxLines(page) && TopY<iMaxLines;TopY+=YCount){
				if(TopY+YCount>iMaxLines)
					YCount=iMaxLines-TopY;
				int	Layer;
				for(Layer=0;Layer<GetLayerNumb(page) && Layer<iLayerNumb;Layer++){
					ImageBuffer	*Buff=CPanel->GetImage(phase,page,Layer);
					for(int yn=0;yn<YCount;yn++){
						BYTE	*d=Buff->GetY(TopY+yn);
						RFile.read((char *)d,iDotPerLine);
					}
				}
				if(Layer<iLayerNumb){
					for(;Layer<iLayerNumb;Layer++){
						QByteArray	Dummy=RFile.read(YCount*iDotPerLine);
					}
				}
				GetLayersBase()->StepProcessing(page);
			}
			if(TopY<iMaxLines){
				for(;TopY<iMaxLines;TopY+=YCount){
					if(TopY+YCount>iMaxLines)
						YCount=iMaxLines-TopY;
					int	Layer;
					for(Layer=0;Layer<iLayerNumb;Layer++){
						QByteArray	Dummy=RFile.read(YCount*iDotPerLine);
					}
					GetLayersBase()->StepProcessing(page);
				}			
			}
			GetLayersBase()->StepProcessing(page);
		}
	}
	GetLayersBase()->CloseProcessingForm ();
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	return true;
}

void	ShowMultiImage::DrawAll(ChildImagePanel *src,double ZoomRate ,int movx ,int movy)
{
	for(int i=0;i<AllocatedChildPanelCount;i++){
		if(src!=ChildPanel[i]){
			ChildPanel[i]->ZoomDraw(movx ,movy ,ZoomRate);
		}
	}
}

void	ShowMultiImage::SlotClicked(int id)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				SendImageToTarget(phase,page,layer,ChildPanel[id]->GetImage(phase,page,layer));
			}
		}
	}
}

void	ShowMultiImage::SendImageToTarget(int phase,int page,int layer ,ImageBuffer *Buff)
{
	GUICmdSendImagePartial	RCmd(GetLayersBase(),sRoot,sName,page);
	int	YCount=100;
	for(int y=0;y<GetMaxLines(page);y+=YCount){
		int	YLen=YCount;
		if(y+YLen>GetMaxLines(page)){
			YLen=GetMaxLines(page)-y;
		}
		RCmd.Data.clear();
		for(int yn=0;yn<YLen;yn++){
			BYTE	*s=Buff->GetY(y+yn);
			RCmd.Data.append((const char *)s,GetDotPerLine(page));
		}
		RCmd.Y=y;
		RCmd.YLen=YLen;
		RCmd.Phase=phase;
		RCmd.Layer=layer;
		RCmd.Send(NULL,page,0);
	}
}

//==================================================================================================
GUICmdSendImagePartial::GUICmdSendImagePartial(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSendImagePartial::Load(QIODevice *f)
{
	if(::Load(f,Y)==false)
		return false;
	if(::Load(f,YLen)==false)
		return false;
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSendImagePartial::Save(QIODevice *f)
{
	if(::Save(f,Y)==false)
		return false;
	if(::Save(f,YLen)==false)
		return false;
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Data)==false)
		return false;
	return true;
}
void	GUICmdSendImagePartial::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ImageBuffer	&Buff=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(localPage)->GetLayerData(Layer)->GetTargetBuff();
	char	*s=Data.data();
	for(int yn=0;yn<YLen;yn++){
		if(0<=Y+yn && Y+yn<GetMaxLines(localPage)){
			memcpy(Buff.GetY(Y+yn),s,GetDotPerLine(localPage));
		}
		s+=GetDotPerLine(localPage);
	}
}