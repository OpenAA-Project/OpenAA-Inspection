#include "XDisplaySimPanel.h"
#include "XGeneralFunc.h"
#include "XResult.h"

DisplaySimPanel::DisplaySimPanel(LayersBase *base ,QWidget *parent)
	:QWidget(parent),ServiceForLayers(base)
{
	ModeShowBlock			=true;
	ModeShowBrightnessNG	=true;
	ItemID		=-1;
	Layer		=-1;
	MovX		=0;
	MovY		=0;
	ZoomRate	=1.0;
	GlobalPage	=0;
	Result		=NULL;
	ResultImage	=NULL;
	LastShitX				=0;
	LastShitY				=0;
	//grabMouse();
	setMouseTracking(true);
}

DisplaySimPanel::~DisplaySimPanel(void)
{
	if(ResultImage!=NULL){
		delete	ResultImage;
	}
	ResultImage=NULL;
}

void	DisplaySimPanel::SetModeShowBlock(bool b)
{
	ModeShowBlock=b;
}
void	DisplaySimPanel::SetModeShowBrightnessNG(bool b)
{
	ModeShowBrightnessNG=b;
}

void	DisplaySimPanel::SetLayer(int layer)
{
	Layer=layer;
}

void	DisplaySimPanel::SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName)
{	
	AlgoRoot=_AlgoRoot;
	AlgoName=_AlgoName;	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
	if(Ab!=NULL){
		Result=Ab->GetPageData(0)->CreateResult();
	}
}

void	DisplaySimPanel::SetResult(ResultInItemRoot *res)
{
	QBuffer	Buff;

	Buff.open(QIODevice::ReadWrite);

	res->Save(&Buff);
	Buff.seek(0);
	if(Result!=NULL){
		Result->Load(&Buff);
	}
}

void	DisplaySimPanel::SetInitial(int _ItemID ,FlexArea &InitialArea)
{
	ItemID	=_ItemID;
	ItemArea=InitialArea;

	int	W=InitialArea.GetWidth();
	int	H=InitialArea.GetHeight();
	int	X1=InitialArea.GetMinX()-W/4;
	int	X2=InitialArea.GetMaxX()+W/4;
	int	Y1=InitialArea.GetMinY()-H/4;
	int	Y2=InitialArea.GetMaxY()+H/4;

	int	Cx,Cy;
	InitialArea.GetCenter(Cx,Cy);

	double	Z1=100000000;
	if(X2-X1!=0){
		Z1=((double)width())/((double)(X2-X1));
	}
	double	Z2=100000000;
	if(Y2-Y1!=0){
		Z2=((double)height())/((double)(Y2-Y1));
	}
	ZoomRate=(Z1<Z2)?Z1:Z2;

	MovX=-(Cx-width()/ZoomRate/2);
	MovY=-(Cy-height()/ZoomRate/2);
	if(ResultImage!=NULL){
		delete	ResultImage;
	}
	ResultImage=new QImage(width(),height(),QImage::Format_ARGB32);
}
void	DisplaySimPanel::SetZoomRate(double Z)
{
	ZoomRate=Z;
}
void	DisplaySimPanel::SetCenter(int LocalX,int LocalY)
{
	MovX=-(LocalX-width()/ZoomRate/2);
	MovY=-(LocalY-height()/ZoomRate/2);
}
void	DisplaySimPanel::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);

	QByteArray	Something;
	GetDrawInformation(Something);

	GUICmdReqDSimPanelImage	ReqCmd(GetLayersBase(),GUIRoot,GUIName,GlobalPage);
	GUICmdAckDSimPanelImage	AckCmd(GetLayersBase(),GUIRoot,GUIName,GlobalPage);
	ReqCmd.ItemID		=ItemID;
	ReqCmd.ImageWidth	=width();
	ReqCmd.ImageHeight	=height();
	ReqCmd.MovX		=MovX;
	ReqCmd.MovY		=MovY;
	ReqCmd.ZoomRate	=ZoomRate;
	ReqCmd.Layer	=Layer;
	ReqCmd.AlgoRoot	=AlgoRoot;
	ReqCmd.AlgoName	=AlgoName;
	ReqCmd.ModeShowBlock	=ModeShowBlock;
	ReqCmd.ModeShowBrightnessNG=ModeShowBrightnessNG;
	ReqCmd.Something	=Something;
	int	CircleWidth=0;
	if(GetParamGlobal()!=NULL){
		CircleWidth=GetParamGlobal()->ResultNGCircleWidth;
	}
	if(Result!=NULL){
		ReqCmd.Rx=Result->GetTotalShiftedX();
		ReqCmd.Ry=Result->GetTotalShiftedY();
	}
	if(ReqCmd.Send(GlobalPage,0,AckCmd)==true && ResultImage!=NULL){
		Pnt.drawImage(0,0,AckCmd.AckImage);
		//ResultImage	->fill(0);
		::ClearImage(*ResultImage, 0);
		if(ModeShowBrightnessNG==true && Result!=NULL){
			int	Kx=Result->GetTotalShiftedX() ;
			int	Ky=Result->GetTotalShiftedY() ;
			QRgb Col=qRgba(255,0,0,120);
			for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
				if(r->result>=0x10000){
					r->DrawResultDetail(Result,*ResultImage,Pnt
										,MovX-Kx
										,MovY-Ky
										//,MovX+r->Rx
										//,MovY+r->Ry
										//,MovX
										//,MovY
										,ZoomRate,5
										,Col,CircleWidth
										,true);
				}
			}
		}
		else{
			QRgb Col=qRgba(255,0,0,0);
			Pnt.drawImage(0,0,AckCmd.AckImage);
			if(Result!=NULL){
				int	Kx=Result->GetTotalShiftedX() ;
				int	Ky=Result->GetTotalShiftedY() ;
				for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
					if(r->result>=0x10000){
						r->DrawResult(Result,*ResultImage,Pnt
											,MovX-Kx
											,MovY-Ky
											//,MovX+r->Rx-Result->GetTotalShiftedX() 
											//,MovY+r->Ry-Result->GetTotalShiftedY()  
											//,MovX+r->Rx
											//,MovY+r->Ry
											,ZoomRate,5
											,Col,CircleWidth
											,true);
					}
				}
			}
		}
		DrawOther(Pnt);
		Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
		Pnt.drawImage(0,0,*ResultImage);
	}
	PaintAfter(Pnt);
}

void	DisplaySimPanel::mousePressEvent ( QMouseEvent *Ev )
{
	int	X=Ev->x();
	int	Y=Ev->y();
	int GlobalX	=X/ZoomRate-MovX;
	int GlobalY	=Y/ZoomRate-MovY;
	LastShitX=X;
	LastShitY=Y;
	ExecuteMousePress	(GlobalX ,GlobalY);
}
void	DisplaySimPanel::mouseMoveEvent ( QMouseEvent * Ev )
{
	int	X=Ev->x();
	int	Y=Ev->y();
	if((Ev->buttons()&Qt::LeftButton)!=0){
		if(abs(X-LastShitX)>5 || abs(Y-LastShitY)>5){
			int	Dx=X-LastShitX;
			int	Dy=Y-LastShitY;
			MovX+=Dx/ZoomRate;
			MovY+=Dy/ZoomRate;
			LastShitX=X;
			LastShitY=Y;
			repaint();
			return;
		}
	}
	else{
		int GlobalX	=Ev->x()/ZoomRate-MovX;
		int GlobalY	=Ev->y()/ZoomRate-MovY;
		ExecuteMouseMove	(GlobalX ,GlobalY);
	}
}
void	DisplaySimPanel::mouseReleaseEvent ( QMouseEvent * Ev )
{
	int GlobalX	=Ev->x()/ZoomRate-MovX;
	int GlobalY	=Ev->y()/ZoomRate-MovY;
	ExecuteMouseRelease	(GlobalX ,GlobalY);
}
void	DisplaySimPanel::wheelEvent ( QWheelEvent * e )
{
	int	D=e->pixelDelta().y();

	if(D>0){
	    int LX=(int)((double)e->position().x()/ZoomRate)/2;
		int LY=(int)((double)e->position().y()/ZoomRate)/2;
		MovX=MovX-LX;
		MovY=MovY-LY;
		ZoomRate=ZoomRate*2.0;
		repaint();
	}
	else if(D<0){
	    int LX=(int)((double)e->position().x()/ZoomRate);
		int LY=(int)((double)e->position().y()/ZoomRate);
		MovX=MovX+LX;
		MovY=MovY+LY;
		ZoomRate=ZoomRate/2.0;
		repaint();
	}
}


//======================================================================================
GUICmdReqDSimPanelImage::GUICmdReqDSimPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName ,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	ItemID		=-1;
	Layer		=-1;
	ImageWidth	=0;
	ImageHeight	=0;
	MovX		=0;
	MovY		=0;
	ZoomRate	=1.0;
	ModeShowBlock		=true;
	ModeShowBrightnessNG=true;
	Rx=0;
	Ry=0;
}
bool	GUICmdReqDSimPanelImage::Load(QIODevice *f)
{
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,ImageWidth)==false)
		return false;
	if(::Load(f,ImageHeight)==false)
		return false;
	if(::Load(f,MovX)==false)
		return false;		
	if(::Load(f,MovY)==false)
		return false;		
	if(::Load(f,ZoomRate	)==false)
		return false;
	if(::Load(f,AlgoRoot)==false)
		return false;
	if(::Load(f,AlgoName)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ModeShowBlock)==false)
		return false;
	if(::Load(f,ModeShowBrightnessNG)==false)
		return false;
	if(::Load(f,Rx)==false)
		return false;
	if(::Load(f,Ry)==false)
		return false;
	if(::Load(f,Something)==false)
		return false;
	return true;
}
bool	GUICmdReqDSimPanelImage::Save(QIODevice *f)
{
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,ImageWidth)==false)
		return false;
	if(::Save(f,ImageHeight)==false)
		return false;
	if(::Save(f,MovX)==false)
		return false;		
	if(::Save(f,MovY)==false)
		return false;		
	if(::Save(f,ZoomRate	)==false)
		return false;
	if(::Save(f,AlgoRoot)==false)
		return false;
	if(::Save(f,AlgoName)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ModeShowBlock)==false)
		return false;
	if(::Save(f,ModeShowBrightnessNG)==false)
		return false;
	if(::Save(f,Rx)==false)
		return false;
	if(::Save(f,Ry)==false)
		return false;
	if(::Save(f,Something)==false)
		return false;
	return true;
}

void	GUICmdReqDSimPanelImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDSimPanelImage	*SendBack=GetSendBack(GUICmdAckDSimPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	QImage	RetImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	SendBack->AckImage=RetImage;
	SendBack->MakeImage(localPage,Layer,MovX-Rx,MovY-Ry,ZoomRate);

	if(ModeShowBlock==true){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoRoot,AlgoName);
		if(Ab!=NULL){
			QImage	TmpImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
			//TmpImage.fill(0);
			::ClearImage(TmpImage, 0);
			CmdAlgoSimulate	Da(GetLayersBase());
			Da.Image				=&TmpImage;
			Da.ItemID				=ItemID;
			Da.Layer				=Layer;
			Da.MovX					=MovX;//-Rx;
			Da.MovY					=MovY;//-Ry;
			Da.ZoomRate				=ZoomRate;
			Da.Something			=Something;
			Ab->GetPageData(localPage)->TransmitDirectly(&Da);
			QPainter	Pnt(&SendBack->AckImage);
			Pnt.drawImage(0,0,TmpImage);
			//SendBack->AckImage.save("TextSimPanel.png","PNG");
			//TmpImage.save("TmpImage.png","PNG");
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckDSimPanelImage::GUICmdAckDSimPanelImage(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckDSimPanelImage::Load(QIODevice *f)
{
	if(::Load(f,AckImage)==false)
		return false;
	return true;
}
bool	GUICmdAckDSimPanelImage::Save(QIODevice *f)
{
	if(::Save(f,AckImage)==false)
		return false;
	return true;
}

void	GUICmdAckDSimPanelImage::MakeImage(int LocalPage ,int Layer
										,int movx ,int movy ,double ZoomRate)
{
	int	W=AckImage.width();
	int	H=AckImage.height();

	double	Z=1.0/ZoomRate;
	int	LayerNumb=GetLayersBase()->GetLayerNumb(LocalPage);
	DataInPage	*Pg=GetLayersBase()->GetPageData(LocalPage);
	if(Layer<0){
		if(LayerNumb>=3){
		//#pragma omp parallel
		//{
		//	#pragma omp for

			for(int y=0;y<H;y++){
				BYTE	*d=AckImage.scanLine(y);
				int	Y=y*Z-movy;
				if(0<=Y && Y<Pg->GetMaxLines()){
					BYTE	*sR=Pg->GetLayerData(0)->GetTargetBuff().GetY(Y);
					BYTE	*sG=Pg->GetLayerData(1)->GetTargetBuff().GetY(Y);
					BYTE	*sB=Pg->GetLayerData(2)->GetTargetBuff().GetY(Y);
					double	fX=-movx;
					for(int x=0;x<W;x++){
						int	X=fX;
						if(0<=X && X<Pg->GetDotPerLine()){
							*((int32 *)d)=0xFF000000+((*(sR+X))<<16)+((*(sG+X))<<8)+((*(sB+X)));
						}
						else{
							*((int32 *)d)=0xFF000000;
						}
						fX+=Z;
						d+=4;
					}
				}
				else{
					for(int x=0;x<W;x++){
						*((int32 *)d)=0xFF000000;
						d+=4;
					}
				}
			}
		}
		else if(LayerNumb==2){
		//#pragma omp parallel
		//{
		//	#pragma omp for

			for(int y=0;y<H;y++){
				BYTE	*d=AckImage.scanLine(y);
				int	Y=y*Z-movy;
				if(0<=Y && Y<Pg->GetMaxLines()){
					BYTE	*sR=Pg->GetLayerData(0)->GetTargetBuff().GetY(Y);
					BYTE	*sG=Pg->GetLayerData(1)->GetTargetBuff().GetY(Y);
					double	fX=-movx;
					for(int x=0;x<W;x++){
						int	X=fX;
						if(0<=X && X<Pg->GetDotPerLine()){
							*((int32 *)d)=0xFF000000+((*(sR+X))<<16)+((*(sG+X))<<8)+((*(sG+X)));
						}
						else{
							*((int32 *)d)=0xFF000000;
						}
						fX+=Z;
						d+=4;
					}
				}
				else{
					for(int x=0;x<W;x++){
						*((int32 *)d)=0xFF000000;
						d+=4;
					}
				}
			}
		}
		else if(LayerNumb==1){
		//#pragma omp parallel
		//{
		//	#pragma omp for

			for(int y=0;y<H;y++){
				BYTE	*d=AckImage.scanLine(y);
				int	Y=y*Z-movy;
				if(0<=Y && Y<Pg->GetMaxLines()){
					BYTE	*sR=Pg->GetLayerData(0)->GetTargetBuff().GetY(Y);
					double	fX=-movx;
					for(int x=0;x<W;x++){
						int	X=fX;
						if(0<=X && X<Pg->GetDotPerLine()){
							*((int32 *)d)=0xFF000000+((*(sR+X))<<16)+((*(sR+X))<<8)+((*(sR+X)));
						}
						else{
							*((int32 *)d)=0xFF000000;
						}
						fX+=Z;
						d+=4;
					}
				}
				else{
					for(int x=0;x<W;x++){
						*((int32 *)d)=0xFF000000;
						d+=4;
					}
				}
			}
		}
	}
	else{
		if(Layer>=GetLayerNumb(LocalPage)){
			Layer=GetLayerNumb(LocalPage)-1;
		}
		//#pragma omp parallel
		//{
		//	#pragma omp for
			for(int y=0;y<H;y++){
				BYTE	*d=AckImage.scanLine(y);
				int	Y=y*Z-movy;
				if(0<=Y && Y<Pg->GetMaxLines()){
					BYTE	*sR=Pg->GetLayerData(Layer)->GetTargetBuff().GetY(Y);
					double	fX=-movx;
					for(int x=0;x<W;x++){
						int	X=fX;
						if(0<=X && X<Pg->GetDotPerLine()){
							*((int32 *)d)=0xFF000000+((*(sR+X))<<16)+((*(sR+X))<<8)+((*(sR+X)));
						}
						else{
							*((int32 *)d)=0xFF000000;
						}
						fX+=Z;
						d+=4;
					}
				}
				else{
					for(int x=0;x<W;x++){
						*((int32 *)d)=0xFF000000;
						d+=4;
					}
				}
			}
		//}
	}
}