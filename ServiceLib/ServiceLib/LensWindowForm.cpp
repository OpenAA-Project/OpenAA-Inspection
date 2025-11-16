#include "XTypeDef.h"
#include "LensWindowForm.h"
#include "ui_LensWindowForm.h"
#include "XDisplayImagePacket.h"
#include "XDisplayImage.h"
#include "XDataInLayer.h"
#include "XCrossObj.h"
#include "XGUI.h"

class	GUICmdSendBmp;
class	GUICmdReqBmp;

LensWindowForm::LensWindowForm(LayersBase *base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base),
    ui(new Ui::LensWindowForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);

	BmpReceiver	=NULL;
	BmpRequester=NULL;
	AllocedBmp	=0;
	ZoomRate	=2;
	TargetPanel=NULL;
	DType=DisplayImage::__Master;
	CurrentGlobalX	=0;
	CurrentGlobalY	=0;
	MainGUIFormBase	*f=dynamic_cast<MainGUIFormBase	*>(GetLayersBase()->GetMainWidget());
	if(f!=NULL){
		connect(f,SIGNAL(SignalCloseEvent()),this,SLOT(SlotCloseEvent()));
	}

	TM.setInterval(200);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}

LensWindowForm::~LensWindowForm()
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
	AllocedBmp=0;
}
void	LensWindowForm::AllocInnerBuff(void)
{
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

	BmpReceiver=new GUICmdSendBmp*[GetLayersBase()->GetPageNumb()];
	BmpRequester=new GUICmdReqBmp*[GetLayersBase()->GetPageNumb()];
	AllocedBmp=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[page]=new GUICmdSendBmp(GetLayersBase(),/**/"ANY",/**/"ANY",globalPage);
		BmpRequester[page]=new GUICmdReqBmp(GetLayersBase(),/**/"ANY",/**/"ANY",DType,globalPage);
		AllocedBmp++;
	}
}

void	LensWindowForm::ShowLens(DisplayImage *_TargetPanel ,int GlobalX ,int GlobalY , DisplayImage::DisplayType dtype)
{
	DType=dtype;
	CurrentGlobalX	=GlobalX;
	CurrentGlobalY	=GlobalY;
	TargetPanel		=_TargetPanel;
	if(TargetPanel	->GetZoomRate()<=1.0){
		ZoomRate=2.0;
	}
	else{
		ZoomRate=TargetPanel->GetZoomRate()*2;
	}
	update();
}

void	LensWindowForm::ChangeDxy2Gxy(int Dx,int Dy ,int &Gx ,int &Gy)
{
	Gx=(Dx-CurrentGlobalX)*ZoomRate +width()/2;
	Gy=(Dy-CurrentGlobalY)*ZoomRate +height()/2;
}
void	LensWindowForm::ChangeGxy2Dxy(int Gx,int Gy ,int &Dx ,int &Dy)
{
	Dx=(Gx-width ()/2)/ZoomRate+CurrentGlobalX;
	Dy=(Gy-height()/2)/ZoomRate+CurrentGlobalY;
}
void	LensWindowForm::SlotTimeout()
{
	if(GetLayersBase()->GetOnTerminating()==true){
		close();
	}
	else{
		repaint();
	}
}

void LensWindowForm::hideEvent ( QHideEvent * event )
{
	emit	SignalClose();
}

void LensWindowForm::closeEvent ( QCloseEvent * event )
{
	emit	SignalClose();
}

void LensWindowForm::paintEvent ( QPaintEvent * event )
{
	if(TargetPanel==NULL)
		return;
	QPainter	pnt(this);

	QImage	*PntImage;
	double	SavedZoomRate=TargetPanel->GetZoomRate();
	int		SavedMovX	 =TargetPanel->GetMovx();
	int		SavedMovY	 =TargetPanel->GetMovy();
	{
		TargetPanel->SetZoomRate(ZoomRate);
		TargetPanel->SetMovXY(-CurrentGlobalX
							 ,-CurrentGlobalY);

		//TargetPanel->HookedExecutePaintFirst(IPnt,PntImage);
	}

	if(TargetPanel->ShowOnePage<0){
		int	globalX1;
		int	globalY1;
		int	globalX2;
		int	globalY2;
		GetLayersBase()->GetArea(globalX1,globalY1 ,globalX2,globalY2);

		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			if(GetLayersBase()->GetSendingData(globalPage)==true){
				return;
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
		int	N=0;
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);

			DataInPage *P=GetLayersBase()->GetPageData(page);
			int	Dx1	=P->GetOutlineOffset()->x;
			int	Dy1	=P->GetOutlineOffset()->y;
			int	Dx2	=P->GetOutlineOffset()->x+P->GetDotPerLine();
			int	Dy2	=P->GetOutlineOffset()->y+P->GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);	
			ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, width(), height()
										,Gx1, Gy1, Gx2, Gy2)==false){
				continue;
			}
			BmpRequester[N]->Data.DType=DType;
			BmpRequester[N]->Data.ShowFixedPhase	=TargetPanel->ShowFixedPhase;
			BmpRequester[N]->Data.ZoomRate	=ZoomRate;
			BmpRequester[N]->Data.Yz		=1.0;
			BmpRequester[N]->Data.MovX		=-CurrentGlobalX*ZoomRate +width ()/2+P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.MovY		=-CurrentGlobalY*ZoomRate +height()/2+P->GetOutlineOffset()->y;
			
			BmpRequester[N]->Data.GlobalPage	=globalPage;
			BmpReceiver[N]->SetGlobalPage(globalPage);
			if(Gx1<0){
				Gx1=0;
			}
			if(Gy1<0){
				Gy1=0;
			}
			//??????E?I?I?I?i??????
			if(Gx2>width()){
				Gx2=width();
			}
			if(Gy2>height()){
				Gy2=height();
			}
			IntList	LayerList;
			TargetPanel->GetActiveLayerList(LayerList);
			BmpRequester[N]->Data.RedCircleMode=false;
			BmpRequester[N]->LayerList	=LayerList;		//??`??a??i??C??????[
			BmpRequester[N]->Data.Gx1		=Gx1;
			BmpRequester[N]->Data.Gy1		=Gy1;
			BmpRequester[N]->Data.Gx2		=Gx2;
			BmpRequester[N]->Data.Gy2		=Gy2;
			ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
			ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
			BmpRequester[N]->Data.Dx1	=Dx1-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy1	=Dy1-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.Dx2	=Dx2-P->GetOutlineOffset()->x;
			BmpRequester[N]->Data.Dy2	=Dy2-P->GetOutlineOffset()->y;
			BmpRequester[N]->Data.TransparentLevelInBitBuff	=true;
			BmpRequester[N]->Data.ShowNGMarkInTarget	=false;
			BmpRequester[N]->Data.RepaintContinuously	=false;
			N++;
		}

		NPListPack<GUICmdPacketDim>	GUICmdDim;
		for(int n=0;n<N;n++){
			if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
				&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
				GUICmdDim.AppendList(new GUICmdPacketDim(BmpRequester[n],BmpReceiver[n],BmpRequester[n]->Data.GlobalPage,0));
			}
		}

		if(GetLayersBase()->PacketSender(GUICmdDim,5000)==false){
			return;
		}
		if(GetLayersBase()->GetOnTerminating()==true){
			return;
		}

		for(int page=GetLayersBase()->GetPageNumb()-1;page>=0;page--){
			int	n=GetLayersBase()->GetDrawturn(page)->GetPage();
			if(BmpReceiver[n]->IsReceived()==true){
				if(BmpRequester[n]->Data.Gx1!=BmpRequester[n]->Data.Gx2
				&& BmpRequester[n]->Data.Gy1!=BmpRequester[n]->Data.Gy2){
					PntImage=BmpReceiver[0]->IData;
					QPainter	IPnt(PntImage);
					TargetPanel->HookedExecutePaintFirst(IPnt,*PntImage);
					TargetPanel->HookedExecutePaintLast(IPnt,*PntImage);
					pnt.drawImage(BmpRequester[n]->Data.Gx1 ,BmpRequester[n]->Data.Gy1
							 ,*PntImage);
				}
			}
		}
	}
	else{
		int	localPage=TargetPanel->ShowOnePage;
		DataInPage *P=GetLayersBase()->GetPageData(localPage);
		if(P!=NULL){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
			if(GetLayersBase()->GetSendingData(globalPage)==true){
				return;
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
			BmpReceiver[localPage]->ClearReceivedFlag();
			
			int	Dx1	=0;
			int	Dy1	=0;
			int	Dx2	=P->GetDotPerLine();
			int	Dy2	=P->GetMaxLines();
			int	Gx1,Gy1,Gx2,Gy2;
			ChangeDxy2Gxy(Dx1,Dy1 ,Gx1 ,Gy1);	
			ChangeDxy2Gxy(Dx2,Dy2 ,Gx2 ,Gy2);
			if(CheckOverlapRectRectFast(0, 0, width(), height()
										,Gx1, Gy1, Gx2, Gy2)==true){
				BmpRequester[0]->Data.DType=DType;
				BmpRequester[0]->Data.ShowFixedPhase	=TargetPanel->ShowFixedPhase;
				BmpRequester[0]->Data.ZoomRate	=ZoomRate;
				BmpRequester[0]->Data.Yz		=1.0;
				BmpRequester[0]->Data.MovX		=-CurrentGlobalX*ZoomRate +width ()/2;
				BmpRequester[0]->Data.MovY		=-CurrentGlobalY*ZoomRate +height()/2;
				
				BmpRequester[0]->Data.GlobalPage	=globalPage;
				BmpReceiver[0]->SetGlobalPage(globalPage);
				if(Gx1<0){
					Gx1=0;
				}
				if(Gy1<0){
					Gy1=0;
				}
				if(Gx2>width()){
					Gx2=width();
				}
				if(Gy2>height()){
					Gy2=height();
				}
				IntList	LayerList;
				TargetPanel->GetActiveLayerList(LayerList);
				BmpRequester[0]->Data.RedCircleMode=false;
				BmpRequester[0]->LayerList	=LayerList;		//??`??a??i??C??????[
				BmpRequester[0]->Data.Gx1		=Gx1;
				BmpRequester[0]->Data.Gy1		=Gy1;
				BmpRequester[0]->Data.Gx2		=Gx2;
				BmpRequester[0]->Data.Gy2		=Gy2;
				ChangeGxy2Dxy(Gx1,Gy1 ,Dx1 ,Dy1);
				ChangeGxy2Dxy(Gx2,Gy2 ,Dx2 ,Dy2);
				BmpRequester[0]->Data.Dx1	=Dx1;
				BmpRequester[0]->Data.Dy1	=Dy1;
				BmpRequester[0]->Data.Dx2	=Dx2;
				BmpRequester[0]->Data.Dy2	=Dy2;
				BmpRequester[0]->Data.TransparentLevelInBitBuff	=true;
				BmpRequester[0]->Data.ShowNGMarkInTarget	=false;
				BmpRequester[0]->Data.RepaintContinuously	=false;

				if(BmpRequester[0]->Data.Gx1!=BmpRequester[0]->Data.Gx2
				&& BmpRequester[0]->Data.Gy1!=BmpRequester[0]->Data.Gy2){
					BmpRequester[0]->Send(BmpRequester[0]->Data.GlobalPage,0,*BmpReceiver[0]);
				}

				if(GetLayersBase()->GetOnTerminating()==true){
					return;
				}

				if(BmpReceiver[0]->IsReceived()==true){
					if(BmpRequester[0]->Data.Gx1!=BmpRequester[0]->Data.Gx2
					&& BmpRequester[0]->Data.Gy1!=BmpRequester[0]->Data.Gy2){
						PntImage=BmpReceiver[0]->IData;
						QPainter	IPnt(PntImage);
						TargetPanel->HookedExecutePaintFirst(IPnt,*PntImage);
						TargetPanel->HookedExecutePaintLast (IPnt,*PntImage);
						pnt.drawImage(BmpRequester[0]->Data.Gx1 ,BmpRequester[0]->Data.Gy1
								 ,*PntImage);
					}
				}
			}
		}
	}
	//pnt.drawImage(0,0,PntImage);

	TargetPanel->SetZoomRate(SavedZoomRate);
	TargetPanel->SetMovXY(SavedMovX,SavedMovY);

}
void	LensWindowForm::SlotCloseEvent()
{
	close();
}

void LensWindowForm::resizeEvent ( QResizeEvent * event )
{
	//PntImage=QImage(width(),height(),QImage::Format_ARGB32);
}
