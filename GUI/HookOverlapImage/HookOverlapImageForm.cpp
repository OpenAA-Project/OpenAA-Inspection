#include "HookOverlapImageForm.h"
#include "ui_HookOverlapImageForm.h"
#include "XDisplayImagePacket.h"
#include "XCrossObj.h"
#include "XCameraClass.h"
#include "XAnyData.h"
#include "XGeneralFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

HookOverlapImageForm::HookOverlapImageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::HookOverlapImageForm)
{
    ui->setupUi(this);
    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	ImageType		=/**/"MasterImage";
	OverlapImage	=NULL;
	SlidebarPosition=0;
	SliderDirection	=/**/"RightFaint";
	ShowNGMarkInTarget	=false;
	Active			=true;

	BmpReceiver	=NULL;
	BmpRequester=NULL;
	AllocedBmp	=0;
}

HookOverlapImageForm::~HookOverlapImageForm()
{
    delete ui;

	for(int page=0;page<AllocedBmp;page++){
		if(BmpReceiver!=NULL){
			delete	BmpReceiver[page];
		}
		if(BmpRequester!=NULL){
			delete	BmpRequester[page];
		}
	}
	if(BmpReceiver!=NULL){
		delete	[]BmpReceiver;
	}
	if(BmpRequester!=NULL){
		delete	[]BmpRequester;
	}
	if(OverlapImage!=NULL){
		delete	OverlapImage;
		OverlapImage=NULL;
	}
	AllocedBmp=0;
}

void	HookOverlapImageForm::ResizeAction()
{
	ui->labelValue->move(width()-53,ui->labelValue->geometry().top());
	ui->labelPeercentage	->move(width()-23,ui->labelPeercentage	->geometry().top());
	ui->horizontalSlider	->resize(width()-72,22);
}

void	HookOverlapImageForm::Prepare(void)
{
	AllocInnerBuff();
	SlidebarPosition	=ui->horizontalSlider->value();
}
static	bool	DbgLocked=false;
static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		HookOverlapImageForm	*Form=dynamic_cast<HookOverlapImageForm *>(Obj);
		if(Form!=NULL && Form->GetActive()==true){
			if(Form->GetLayersBase()->TryLockWeakDraw()==true){
				Form->Draw(DImage,pnt,PntImage
						,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy()
						,DImage->GetCanvasWidth(),DImage->GetCanvasHeight());
				Form->GetLayersBase()->UnlockWeakDraw();
				//TargetObj->GetLayersBase()->GetAnyData()->Set(/**/"HookOverlap",1);
				DbgLocked=false;
			}
			else{
				DbgLocked=true;
			}
		}
	}
	return true;
}

void	HookOverlapImageForm::ReadyParam(void)
{
	for(int i=0;i<HookTargetListInst.count();i++){
		QString	HookTargetInst=HookTargetListInst[i];
		GUIFormBase *s=dynamic_cast<GUIFormBase *>(GetLayersBase()->FindByName(HookTargetInst));
		if(s!=NULL){
			TargetPanels.Add(s);
			DisplayImageHooked *TargetPanel=dynamic_cast<DisplayImageHooked *>(s);
			if(TargetPanel!=NULL){
				TargetPanel->SetHookInPaintLast		(this,TargetFunctionPaintLast);
			}
		}
	}
}

void HookOverlapImageForm::on_horizontalSlider_valueChanged(int value)
{
	SlidebarPosition	=ui->horizontalSlider->value();
	ui->labelValue->setText(QString::number(SlidebarPosition));
	TargetPanels.Repaint();
}

void	HookOverlapImageForm::Draw	(DisplayImage	*DImage
									,QPainter &pnt	,QImage &PntImage
									,double ZoomRate,int movx ,int movy
									,int CanvasWidth ,int CanvasHeight)
{
	static	int	NoImage=0;

	int	V=SlidebarPosition;
	if(isEnabled()==false){
		V=0;
	}

	if(OverlapImage==NULL){
		if(DImage!=NULL)	DImage->LockPaintMutex();
		OverlapImage	=new QImage(CanvasWidth,CanvasHeight,QImage::Format_ARGB32);
		if(DImage!=NULL)	DImage->UnlockPaintMutex();
	}
	else if(OverlapImage->width()!=CanvasWidth || OverlapImage->height()!=CanvasHeight){
		if(DImage!=NULL)	DImage->LockPaintMutex();
		delete	OverlapImage;
		OverlapImage	=new QImage(CanvasWidth,CanvasHeight,QImage::Format_ARGB32);
		if(DImage!=NULL)	DImage->UnlockPaintMutex();
	}

	if(ImageType==/**/"MasterImage"){
		DType=DisplayImage::__Master;
	}
	else if(ImageType==/**/"TargetImage"){
		DType=DisplayImage::__Target;
	}
	else if(ImageType==/**/"BitImage"){
		DType=DisplayImage::__BitBuff;
	}
	else if(ImageType==/**/"CameraRawImage"){
		DType=DisplayImage::__CamTarget;
	}

	if(DImage!=NULL){
		IntList tLayerList;
		DImage->GetActiveLayerList(tLayerList);
		if(SliderDirection==/**/"RightFaint"){
			while(DrawImage(DImage,pnt ,PntImage,tLayerList , V*255/100)==false){
				GSleep(1);
			}
		}
		else
		if(SliderDirection==/**/"LeftFaint"){
			while(DrawImage(DImage,pnt ,PntImage,tLayerList , (100-V)*255/100)==false){
				GSleep(1);
			}
		}
	}
	else{
		IntList tLayerList;
		if(SliderDirection==/**/"RightFaint"){
			while(DrawImage(pnt ,PntImage,tLayerList , V*255/100		,movx ,movy ,ZoomRate)==false){
				GSleep(1);
			}
		}
		else
		if(SliderDirection==/**/"LeftFaint"){
			while(DrawImage(pnt ,PntImage,tLayerList , (100-V)*255/100,movx ,movy ,ZoomRate)==false){
				GSleep(1);
			}
		}
	}
}

void	HookOverlapImageForm::AllocInnerBuff(void)
{
	BmpReceiver=new GUICmdSendBmp*[GetLayersBase()->GetPageNumb()];
	BmpRequester=new GUICmdReqBmp*[GetLayersBase()->GetPageNumb()];
	AllocedBmp=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[page]=new GUICmdSendBmp(GetLayersBase(),sRoot,sName,globalPage);
		BmpRequester[page]=new GUICmdReqBmp(GetLayersBase(),sRoot,sName,DType,globalPage);
		AllocedBmp++;
	}
}
void	HookOverlapImageForm::SetActive(bool b)
{
	Active=b;
	ui->horizontalSlider->setEnabled(Active);
}
void	HookOverlapImageForm::ChangeDxy2Gxy(DisplayImage *DImage ,int Dx,int Dy ,int &Gx ,int &Gy)
{
	int	Mx=DImage->GetMovx();
	int	My=DImage->GetMovy();
	Gx=(Dx+Mx)*DImage->GetZoomRate();
	Gy=(Dy+My)*DImage->GetZoomRate();
}
void	HookOverlapImageForm::ChangeGxy2Dxy(DisplayImage *DImage ,int Gx,int Gy ,int &Dx ,int &Dy)
{
	int	Mx=DImage->GetMovx();
	int	My=DImage->GetMovy();
	Dx=Gx/DImage->GetZoomRate() - Mx;
	Dy=Gy/DImage->GetZoomRate() - My;
}

bool	HookOverlapImageForm::DrawImage(DisplayImage *DImage ,QPainter &pnt ,QImage &PntImage,IntList &_LayerList , int Alpha)
{
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		if(GetLayersBase()->GetSendingData(globalPage)==true){
			return false;
		}
	}

	if(AllocedBmp!=GetLayersBase()->GetPageNumb()){
		for(int page=0;page<AllocedBmp;page++){
			if(BmpReceiver[page]!=NULL){
				delete	BmpReceiver[page];
			}
			if(BmpRequester[page]!=NULL){
				delete	BmpRequester[page];
			}
		}
		delete	[]BmpReceiver;
		delete	[]BmpRequester;
		AllocInnerBuff();
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		BmpReceiver[page]->ClearReceivedFlag();
	}
	if(GetTargetPage()<0){
		int	N=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			DataInPage *P=GetLayersBase()->GetPageData(page);
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(DImage,Dx1,Dy1 ,Gx1 ,Gy1);	
			ChangeDxy2Gxy(DImage,Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, DImage->GetCanvasWidth(), DImage->GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==false){
				continue;
			}
			BmpRequester[N]->Data.DType=DType;
			BmpRequester[N]->Data.ShowFixedPhase	=DImage->ShowFixedPhase;
			BmpRequester[N]->Data.ZoomRate	=DImage->GetZoomRate();
			BmpRequester[N]->Data.Yz		=DImage->Yz;
			BmpRequester[N]->Data.MovX		=DImage->GetMovx()+P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.MovY		=DImage->GetMovy()+P->GetOutlineOffset()->y;

			BmpRequester[N]->Data.GlobalPage	=globalPage;
			BmpReceiver[N]->SetGlobalPage(globalPage);
			if(Gx1<0){
				Gx1=0;
			}
			if(Gy1<0){
				Gy1=0;
			}

			if(Gx2>DImage->GetCanvasWidth()){
				Gx2=DImage->GetCanvasWidth();
			}
			if(Gy2>DImage->GetCanvasHeight()){
				Gy2=DImage->GetCanvasHeight();
			}

			BmpRequester[N]->Data.RedCircleMode=false;
			BmpRequester[N]->LayerList	=_LayerList;		//??`??a??i??C??????[
			BmpRequester[N]->Data.Gx1		=Gx1;
			BmpRequester[N]->Data.Gy1		=Gy1;
			BmpRequester[N]->Data.Gx2		=Gx2;
			BmpRequester[N]->Data.Gy2		=Gy2;
			ChangeGxy2Dxy(DImage,Gx1,Gy1 ,Dx1 ,Dy1);
			ChangeGxy2Dxy(DImage,Gx2,Gy2 ,Dx2 ,Dy2);
			BmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.TransparentLevelInBitBuff	=true;
			BmpRequester[N]->Data.ShowNGMarkInTarget		=ShowNGMarkInTarget;
			BmpRequester[N]->Data.RepaintContinuously		=false;
			N++;
		}
		if(GetParamComm()->GetConnectedPCNumb()!=0){
			NPListPack<GUICmdPacketDim>	GUICmdDim;
			for(int n=0;n<N;n++){
				if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
					&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
					GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[n],BmpReceiver[n],BmpRequester[n]->Data.GlobalPage,0));
				}
			}

			if(GetLayersBase()->PacketSender(GUICmdDim,5000)==false){
				return false;
			}
		}
		else{
			for(int n=0;n<N;n++){
				if(BmpReceiver[n]->MakeImage(DType
								 , BmpRequester[n]->Data.Gx1, BmpRequester[n]->Data.Gy1 , BmpRequester[n]->Data.Gx2, BmpRequester[n]->Data.Gy2
								 , BmpRequester[n]->Data.Dx1, BmpRequester[n]->Data.Dy1 , BmpRequester[n]->Data.Dx2, BmpRequester[n]->Data.Dy2
								 , BmpRequester[n]->Data.MovX, BmpRequester[n]->Data.MovY,  BmpRequester[n]->Data.ZoomRate, BmpRequester[n]->Data.Yz
								 , BmpRequester[n]->Data.GlobalPage
								 ,*GetLayersBase()
								 ,0
								 , DImage->LayerList
								 , DImage->RedCircleMode
								 , DImage->ShowFixedPhase
								 , DImage->TransparentLevelInBitBuff
								 ,ShowNGMarkInTarget
								 ,false)==false){
					return false;
				}
				BmpReceiver[n]->SetReceived(true);
			}
		}

		if(GetLayersBase()->GetOnTerminating()==true){
			return true;
		}

		if(DImage!=NULL)	DImage->LockPaintMutex();
		//QBrush	brush(Qt::black);
		//pnt.fillRect (0,0,TargetPanel->GetCanvasWidth(),TargetPanel->GetCanvasHeight(), brush );
		pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
		for(int page=GetLayersBase()->GetPageNumb()-1;page>=0;page--){
			int	n=GetLayersBase()->GetDrawturn(page)->GetPage();
			if(BmpReceiver[n]->IsReceived()==true){
				if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
				&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2
				&& BmpReceiver[n]->IData!=NULL){

				CombinePixels(PntImage,*BmpReceiver[n]->IData,BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1,Alpha);
				}
			}
		}
		if(DImage!=NULL)	DImage->UnlockPaintMutex();
	}
	else{
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(GetTargetPage());

		DataInPage *P=GetLayersBase()->GetPageData(GetTargetPage());
		if(P!=NULL){
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(DImage,Dx1,Dy1 ,Gx1 ,Gy1);	
			ChangeDxy2Gxy(DImage,Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, DImage->GetCanvasWidth(), DImage->GetCanvasHeight()
										,Gx1, Gy1, Gx2, Gy2)==true){

				BmpRequester[0]->Data.DType=DType;
				BmpRequester[0]->Data.ShowFixedPhase	=DImage->ShowFixedPhase;
				BmpRequester[0]->Data.ZoomRate	=DImage->GetZoomRate();
				BmpRequester[0]->Data.Yz		=DImage->Yz;
				BmpRequester[0]->Data.MovX		=DImage->GetMovx()+P->GetOutlineOffset()->x;
				BmpRequester[0]->Data.MovY		=DImage->GetMovy()+P->GetOutlineOffset()->y;

				BmpRequester[0]->Data.GlobalPage	=globalPage;
				BmpReceiver[0]->SetGlobalPage(globalPage);
				if(Gx1<0){
					Gx1=0;
				}
				if(Gy1<0){
					Gy1=0;
				}

				if(Gx2>DImage->GetCanvasWidth()){
					Gx2=DImage->GetCanvasWidth();
				}
				if(Gy2>DImage->GetCanvasHeight()){
					Gy2=DImage->GetCanvasHeight();
				}

				BmpRequester[0]->Data.RedCircleMode=false;
				BmpRequester[0]->LayerList	=_LayerList;
				BmpRequester[0]->Data.Gx1		=Gx1;
				BmpRequester[0]->Data.Gy1		=Gy1;
				BmpRequester[0]->Data.Gx2		=Gx2;
				BmpRequester[0]->Data.Gy2		=Gy2;
				ChangeGxy2Dxy(DImage,Gx1,Gy1 ,Dx1 ,Dy1);
				ChangeGxy2Dxy(DImage,Gx2,Gy2 ,Dx2 ,Dy2);
				BmpRequester[0]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
				BmpRequester[0]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
				BmpRequester[0]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
				BmpRequester[0]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
				BmpRequester[0]->Data.TransparentLevelInBitBuff	=true;
				BmpRequester[0]->Data.ShowNGMarkInTarget		=ShowNGMarkInTarget;
				BmpRequester[0]->Data.RepaintContinuously		=false;
			}
			if(GetParamComm()->GetConnectedPCNumb()!=0){
				NPListPack<GUICmdPacketDim>	GUICmdDim;

				if(BmpRequester[0]->Data.Gx1!=BmpRequester[0]->Data.Gx2
				&& BmpRequester[0]->Data.Gy1!=BmpRequester[0]->Data.Gy2){
					GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[0],BmpReceiver[0],BmpRequester[0]->Data.GlobalPage,0));
				}

				if(GetLayersBase()->PacketSender(GUICmdDim,5000)==false){
					return false;
				}
			}
			else{
				if(BmpReceiver[0]->MakeImage(DType
									 , BmpRequester[0]->Data.Gx1, BmpRequester[0]->Data.Gy1 , BmpRequester[0]->Data.Gx2	   , BmpRequester[0]->Data.Gy2
									 , BmpRequester[0]->Data.Dx1, BmpRequester[0]->Data.Dy1 , BmpRequester[0]->Data.Dx2    , BmpRequester[0]->Data.Dy2
									 , BmpRequester[0]->Data.MovX,BmpRequester[0]->Data.MovY, BmpRequester[0]->Data.ZoomRate,BmpRequester[0]->Data.Yz
									 , BmpRequester[0]->Data.GlobalPage
									 ,*GetLayersBase()
									 ,0
									 , DImage->LayerList
									 , DImage->RedCircleMode
									 , DImage->ShowFixedPhase
									 , DImage->TransparentLevelInBitBuff
									 ,ShowNGMarkInTarget
									 ,false)==false){
					return false;
				}
				BmpReceiver[0]->SetReceived(true);
			}

			if(GetLayersBase()->GetOnTerminating()==true){
				return true;
			}

			if(DImage!=NULL)	DImage->LockPaintMutex();

			pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
			if(BmpReceiver[0]->IsReceived()==true){
				if(BmpRequester[0]->Data.Gx1!=BmpRequester[0]->Data.Gx2
				&& BmpRequester[0]->Data.Gy1!=BmpRequester[0]->Data.Gy2
				&& BmpReceiver[0]->IData!=NULL){

					CombinePixels(PntImage,*BmpReceiver[0]->IData,BmpRequester[0]->Data.Gx1 ,BmpRequester[0]->Data.Gy1,Alpha);
				}
			}
			if(DImage!=NULL)	DImage->UnlockPaintMutex();
		}
	}
	return true;
}

bool	HookOverlapImageForm::DrawImage(QPainter &pnt ,QImage &PntImage
										,IntList &_LayerList , int Alpha
										,int movx ,int movy ,double ZoomRate)
{
	int	globalX1;
	int	globalY1;
	int	globalX2;
	int	globalY2;
	GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		if(GetLayersBase()->GetSendingData(globalPage)==true){
			return false;
		}
	}

	if(AllocedBmp!=GetLayersBase()->GetPageNumb()){
		for(int page=0;page<AllocedBmp;page++){
			if(BmpReceiver[page]!=NULL){
				delete	BmpReceiver[page];
			}
			if(BmpRequester[page]!=NULL){
				delete	BmpRequester[page];
			}
		}
		delete	[]BmpReceiver;
		delete	[]BmpRequester;
		AllocInnerBuff();
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		BmpReceiver[page]->ClearReceivedFlag();
	}
	if(GetTargetPage()<0){
		int	N=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			DataInPage *P=GetLayersBase()->GetPageData(page);
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1=Dx1;
			int	Gy1=Dy1;
			int	Gx2=Dx2;
			int	Gy2=Dy2;

			if(CheckOverlapRectRectFast(0, 0, PntImage.width(), PntImage.height()
										,Gx1, Gy1, Gx2, Gy2)==false){
				continue;
			}
			BmpRequester[N]->Data.DType=DType;
			BmpRequester[N]->Data.ShowFixedPhase=-1;
			BmpRequester[N]->Data.ZoomRate		=ZoomRate;
			BmpRequester[N]->Data.Yz			=1.0;
			BmpRequester[N]->Data.MovX			=movx;
			BmpRequester[N]->Data.MovY			=movy;

			BmpRequester[N]->Data.GlobalPage	=globalPage;
			BmpReceiver[N]->SetGlobalPage(globalPage);
			if(Gx1<0){
				Gx1=0;
			}
			if(Gy1<0){
				Gy1=0;
			}

			if(Gx2>PntImage.width()){
				Gx2=PntImage.width();
			}
			if(Gy2>PntImage.height()){
				Gy2=PntImage.height();
			}

			BmpRequester[N]->Data.RedCircleMode=false;
			BmpRequester[N]->LayerList	=_LayerList;		//??`??a??i??C??????[
			BmpRequester[N]->Data.Gx1		=Gx1;
			BmpRequester[N]->Data.Gy1		=Gy1;
			BmpRequester[N]->Data.Gx2		=Gx2;
			BmpRequester[N]->Data.Gy2		=Gy2;

			BmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.TransparentLevelInBitBuff	=true;
			BmpRequester[N]->Data.ShowNGMarkInTarget		=ShowNGMarkInTarget;
			BmpRequester[N]->Data.RepaintContinuously		=false;
			N++;
		}
		if(GetParamComm()->GetConnectedPCNumb()!=0){
			NPListPack<GUICmdPacketDim>	GUICmdDim;
			for(int n=0;n<N;n++){
				if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
					&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
					GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[n],BmpReceiver[n],BmpRequester[n]->Data.GlobalPage,0));
				}
			}

			if(GetLayersBase()->PacketSender(GUICmdDim,5000)==false){
				return false;
			}
		}
		else{
			for(int n=0;n<N;n++){
				if(BmpReceiver[n]->MakeImage(DType
								 , BmpRequester[n]->Data.Gx1, BmpRequester[n]->Data.Gy1 , BmpRequester[n]->Data.Gx2, BmpRequester[n]->Data.Gy2
								 , BmpRequester[n]->Data.Dx1, BmpRequester[n]->Data.Dy1 , BmpRequester[n]->Data.Dx2, BmpRequester[n]->Data.Dy2
								 , BmpRequester[n]->Data.MovX, BmpRequester[n]->Data.MovY,  BmpRequester[n]->Data.ZoomRate, BmpRequester[n]->Data.Yz
								 , BmpRequester[n]->Data.GlobalPage
								 ,*GetLayersBase()
								 ,0
								 , _LayerList
								 , false
								 , -1
								 , 0
								 ,ShowNGMarkInTarget
								 ,false)==false){
					return false;
				}
				BmpReceiver[n]->SetReceived(true);
			}
		}

		if(GetLayersBase()->GetOnTerminating()==true){
			return true;
		}

		pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
		for(int page=GetLayersBase()->GetPageNumb()-1;page>=0;page--){
			int	n=GetLayersBase()->GetDrawturn(page)->GetPage();
			if(BmpReceiver[n]->IsReceived()==true){
				if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
				&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2
				&& BmpReceiver[n]->IData!=NULL){

				CombinePixels(PntImage,*BmpReceiver[n]->IData,BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1,Alpha);
				}
			}
		}
	}
	else{
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(GetTargetPage());

		DataInPage *P=GetLayersBase()->GetPageData(GetTargetPage());
		if(P!=NULL){
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1=Dx1;
			int	Gy1=Dy1;
			int	Gx2=Dx2;
			int	Gy2=Dy2;
			if(CheckOverlapRectRectFast(0, 0, PntImage.width(), PntImage.height()
										,Gx1, Gy1, Gx2, Gy2)==true){

				BmpRequester[0]->Data.DType=DType;
				BmpRequester[0]->Data.ShowFixedPhase	=-1;
				BmpRequester[0]->Data.ZoomRate	=ZoomRate;
				BmpRequester[0]->Data.Yz		=1;
				BmpRequester[0]->Data.MovX		=movx+P->GetOutlineOffset()->x;
				BmpRequester[0]->Data.MovY		=movx+P->GetOutlineOffset()->y;

				BmpRequester[0]->Data.GlobalPage	=globalPage;
				BmpReceiver[0]->SetGlobalPage(globalPage);
				if(Gx1<0){
					Gx1=0;
				}
				if(Gy1<0){
					Gy1=0;
				}

				if(Gx2>PntImage.width()){
					Gx2=PntImage.width();
				}
				if(Gy2>PntImage.height()){
					Gy2=PntImage.height();
				}

				BmpRequester[0]->Data.RedCircleMode=false;
				BmpRequester[0]->LayerList	=_LayerList;
				BmpRequester[0]->Data.Gx1		=Gx1;
				BmpRequester[0]->Data.Gy1		=Gy1;
				BmpRequester[0]->Data.Gx2		=Gx2;
				BmpRequester[0]->Data.Gy2		=Gy2;

				BmpRequester[0]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
				BmpRequester[0]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
				BmpRequester[0]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
				BmpRequester[0]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
				BmpRequester[0]->Data.TransparentLevelInBitBuff	=true;
				BmpRequester[0]->Data.ShowNGMarkInTarget		=ShowNGMarkInTarget;
				BmpRequester[0]->Data.RepaintContinuously		=false;
			}
			if(GetParamComm()->GetConnectedPCNumb()!=0){
				NPListPack<GUICmdPacketDim>	GUICmdDim;

				if(BmpRequester[0]->Data.Gx1!=BmpRequester[0]->Data.Gx2
				&& BmpRequester[0]->Data.Gy1!=BmpRequester[0]->Data.Gy2){
					GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[0],BmpReceiver[0],BmpRequester[0]->Data.GlobalPage,0));
				}

				if(GetLayersBase()->PacketSender(GUICmdDim,5000)==false){
					return false;
				}
			}
			else{
				if(BmpReceiver[0]->MakeImage(DType
									 , BmpRequester[0]->Data.Gx1, BmpRequester[0]->Data.Gy1 , BmpRequester[0]->Data.Gx2	   , BmpRequester[0]->Data.Gy2
									 , BmpRequester[0]->Data.Dx1, BmpRequester[0]->Data.Dy1 , BmpRequester[0]->Data.Dx2    , BmpRequester[0]->Data.Dy2
									 , BmpRequester[0]->Data.MovX,BmpRequester[0]->Data.MovY, BmpRequester[0]->Data.ZoomRate,BmpRequester[0]->Data.Yz
									 , BmpRequester[0]->Data.GlobalPage
									 ,*GetLayersBase()
									 ,0
									 , _LayerList
									 , false
									 , -1
									 , 0
									 ,ShowNGMarkInTarget
									 ,false)==false){
					return false;
				}
				BmpReceiver[0]->SetReceived(true);
			}

			if(GetLayersBase()->GetOnTerminating()==true){
				return true;
			}

			pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);	//CompositionMode_Plus);
			if(BmpReceiver[0]->IsReceived()==true){
				if(BmpRequester[0]->Data.Gx1!=BmpRequester[0]->Data.Gx2
				&& BmpRequester[0]->Data.Gy1!=BmpRequester[0]->Data.Gy2
				&& BmpReceiver[0]->IData!=NULL){

					CombinePixels(PntImage,*BmpReceiver[0]->IData,BmpRequester[0]->Data.Gx1 ,BmpRequester[0]->Data.Gy1,Alpha);
				}
			}
		}
	}
	return true;
}
void	 HookOverlapImageForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetAlphaMasterToTarget	*CmdGetAlphaMasterToTargetVar=dynamic_cast<CmdGetAlphaMasterToTarget *>(packet);
	if(CmdGetAlphaMasterToTargetVar!=NULL){
		CmdGetAlphaMasterToTargetVar->Alpha	=ui->horizontalSlider->value()/((double)ui->horizontalSlider->maximum());
		CmdGetAlphaMasterToTargetVar->Active=Active;
		return;
	}
	CmdSetAlphaMasterToTarget	*CmdSetAlphaMasterToTargettVar=dynamic_cast<CmdSetAlphaMasterToTarget *>(packet);
	if(CmdSetAlphaMasterToTargettVar!=NULL){
		int	V=CmdSetAlphaMasterToTargettVar->Alpha*ui->horizontalSlider->maximum();
		ui->horizontalSlider->setValue(V);
		SetActive(CmdSetAlphaMasterToTargettVar->Active);
		return;
	}
	CmdDrawOverlapImage	*CmdDrawOverlapImageVar=dynamic_cast<CmdDrawOverlapImage *>(packet);
	if(CmdDrawOverlapImageVar!=NULL){
		QPainter	Pnt(CmdDrawOverlapImageVar->PntImage);
		Draw	(NULL
					,Pnt	,*CmdDrawOverlapImageVar->PntImage
					,CmdDrawOverlapImageVar->ZoomRate
					,CmdDrawOverlapImageVar->movx ,CmdDrawOverlapImageVar->movy
					,CmdDrawOverlapImageVar->CanvasWidth ,CmdDrawOverlapImageVar->CanvasHeight);
		return;
	}
}

void	HookOverlapImageForm::GetState(DisplayImage::DisplayType &dType ,bool &Checked,int &Value)
{
	dType	=DType;
	Checked	=Active;
	Value	=ui->horizontalSlider->value();
}

void	HookOverlapImageForm::CalledFromDeridedParent(GUIFormBase *Parent, QEvent * event)
{
	HookOverlapImageForm	*src=dynamic_cast<HookOverlapImageForm *>(DeridedParent);
	if(src!=NULL){
		bool	Checked;
		int		Value;
		DisplayImage::DisplayType dType;
		src->GetState(dType,Checked,Value);
		SetTargetPage(src->GetTargetPage());
		DType	=dType;
		if(Checked==true)
			Active	=true;
		else
			Active	=false;
		ui->horizontalSlider->setValue(Value);
	}
}