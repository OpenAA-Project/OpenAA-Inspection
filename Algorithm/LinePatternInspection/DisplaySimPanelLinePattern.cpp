#include "DisplaySimPanelLinePattern.h"
#include "XGeneralFunc.h"
#include "ShowOperationalPanel.h"
#include "XResult.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DisplaySimPanelLinePattern::DisplaySimPanelLinePattern(LayersBase *base ,ShowOperationalPanel *parentw ,QWidget *parent)
	:QWidget(parent),ServiceForLayers(base),ParentWidget(parentw)
{
	ModeShowArea	=true;
	ModeShowInside	=true;
	ModeShowOutside	=true;
	ModeShowNGMark	=true;
	MovX	=0;
	MovY	=0;
	ZoomRate	=1.0;
	GlobalPage	=0;
	Result=NULL;
	ResultImage				=NULL;
}

DisplaySimPanelLinePattern::~DisplaySimPanelLinePattern(void)
{
	if(ResultImage!=NULL){
		delete	ResultImage;
	}
	ResultImage=NULL;
}

void	DisplaySimPanelLinePattern::SetLayer(int layer)
{
	Layer=layer;
}

void	DisplaySimPanelLinePattern::SetAlgo(const QString	&_AlgoRoot ,const QString &_AlgoName)
{	
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(_AlgoRoot,_AlgoName);
	if(Ab!=NULL){
		Result=Ab->GetPageData(0)->CreateResult();
	}
}

void	DisplaySimPanelLinePattern::SetResult(ResultInItemRoot *res)
{
	QBuffer	Buff;

	Buff.open(QIODevice::ReadWrite);

	res->Save(&Buff);
	Buff.seek(0);
	if(Result!=NULL){
		Result->Load(&Buff);
	}
}

void	DisplaySimPanelLinePattern::SetInitial(int _ItemID ,FlexArea &InitialArea)
{
	ItemID	=_ItemID;
	ItemArea=InitialArea;

	int	W=InitialArea.GetWidth();
	int	H=InitialArea.GetHeight();
	int	X1=InitialArea.GetMinX()-W/4;
	int	X2=InitialArea.GetMaxX()+W/4;
	int	Y1=InitialArea.GetMinY()-H/4;
	int	Y2=InitialArea.GetMaxY()+H/4;

	MovX=-X1;
	MovY=-Y1;
	double	Z1=100000000;
	if(X2-X1!=0){
		Z1=((double)width())/((double)(X2-X1));
	}
	double	Z2=100000000;
	if(Y2-Y1!=0){
		Z2=((double)height())/((double)(Y2-Y1));
	}
	ZoomRate=(Z1<Z2)?Z1:Z2;

	if(ResultImage!=NULL){
		delete	ResultImage;
	}
	ResultImage=new QImage(width(),height(),QImage::Format_ARGB32);
}

void	DisplaySimPanelLinePattern::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);

	GUICmdReqDSimPanelImage	ReqCmd(GetLayersBase(),GUIRoot,GUIName,GlobalPage);
	GUICmdAckDSimPanelImage	AckCmd(GetLayersBase(),GUIRoot,GUIName,GlobalPage);
	ReqCmd.ItemID		=ItemID;
	ReqCmd.ImageWidth	=width();
	ReqCmd.ImageHeight	=height();
	ReqCmd.MovX		=MovX;
	ReqCmd.MovY		=MovY;
	ReqCmd.ZoomRate	=ZoomRate;
	ReqCmd.Layer	=Layer;
	ReqCmd.ModeShowArea		=ModeShowArea		;
	ReqCmd.ModeShowInside	=ModeShowInside		;
	ReqCmd.ModeShowOutside	=ModeShowOutside	;
	ReqCmd.ModeShowNGMark	=ModeShowNGMark		;
	ReqCmd.Rx		=0;
	ReqCmd.Ry		=0;
	ReqCmd.ResultAngleNumber=0;

	int	CircleWidth=0;
	if(GetParamGlobal()!=NULL){
		CircleWidth=GetParamGlobal()->ResultNGCircleWidth;
	}
	if(Result!=NULL){
		ReqCmd.Rx=Result->GetTotalShiftedX();
		ReqCmd.Ry=Result->GetTotalShiftedY();
		ReqCmd.ResultAngleNumber=Result->GetResult2();
	}
	if(ReqCmd.Send(GlobalPage,0,AckCmd)==true && ResultImage!=NULL){
		Pnt.drawImage(0,0,AckCmd.AckImage);
		ResultImage	->fill(0);
		if(ModeShowNGMark==true && Result!=NULL){
			QRgb Col=qRgba(255,0,0,120);
			for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
				if(r->result>=0x10000){
					r->DrawResultDetail(Result,*ResultImage,Pnt
										//,MovX-r->Rx// + ReqCmd.Rx
										//,MovY-r->Ry// + ReqCmd.Ry
										,MovX-ParentWidget->ShiftBySelfX
										,MovY-ParentWidget->ShiftBySelfY
										,ZoomRate,5
										,Col,CircleWidth
										,true);
				}
			}
		}
		else{
			QRgb Col=qRgba(255,0,0,0);
			Pnt.drawImage(0,0,AckCmd.AckImage);
			for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
				if(r->result>=0x10000){
					r->DrawResult(Result,*ResultImage,Pnt
										//,MovX-r->Rx	//+Result->GetTotalShiftedX() 
										//,MovY-r->Ry	//+Result->GetTotalShiftedY()  
										,MovX-ParentWidget->ShiftBySelfX
										,MovY-ParentWidget->ShiftBySelfY
										,ZoomRate,5
										,Col,CircleWidth
										,true);
				}
			}
		}
		DrawOther(Pnt);
		Pnt.setCompositionMode(QPainter::CompositionMode_SourceOver);
		Pnt.drawImage(0,0,*ResultImage);
	}
}

void	DisplaySimPanelLinePattern::mousePressEvent ( QMouseEvent *Ev )
{
}
void	DisplaySimPanelLinePattern::mouseMoveEvent ( QMouseEvent * e )
{
}
void	DisplaySimPanelLinePattern::mouseReleaseEvent ( QMouseEvent * e )
{
}
void	DisplaySimPanelLinePattern::wheelEvent ( QWheelEvent * e )
{
	int	D=e->pixelDelta().y();
	int	X=e->position().x()/ZoomRate-MovX;
	int	Y=e->position().y()/ZoomRate-MovY;

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
	ImageWidth	=0;
	ImageHeight	=0;
	MovX		=0;
	MovY		=0;
	ZoomRate	=1.0;
	ModeShowArea	=true;
	ModeShowInside	=true;
	ModeShowOutside	=true;
	ModeShowNGMark	=true;
	Rx=0;
	Ry=0;
	ResultAngleNumber=0;
	ShiftBySelfX	=0;
	ShiftBySelfY	=0;
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
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ModeShowArea)==false)
		return false;
	if(::Load(f,ModeShowInside)==false)
		return false;
	if(::Load(f,ModeShowOutside)==false)
		return false;
	if(::Load(f,ModeShowNGMark)==false)
		return false;
	if(::Load(f,Rx)==false)
		return false;
	if(::Load(f,Ry)==false)
		return false;
	if(::Load(f,ResultAngleNumber)==false)
		return false;
	if(::Load(f,ShiftBySelfX)==false)
		return false;
	if(::Load(f,ShiftBySelfY)==false)
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
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ModeShowArea)==false)
		return false;
	if(::Save(f,ModeShowInside)==false)
		return false;
	if(::Save(f,ModeShowOutside)==false)
		return false;
	if(::Save(f,ModeShowNGMark)==false)
		return false;
	if(::Save(f,Rx)==false)
		return false;
	if(::Save(f,Ry)==false)
		return false;
	if(::Save(f,ResultAngleNumber)==false)
		return false;
	if(::Save(f,ShiftBySelfX)==false)
		return false;
	if(::Save(f,ShiftBySelfY)==false)
		return false;

	return true;
}

void	GUICmdReqDSimPanelImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckDSimPanelImage	*SendBack=GetSendBack(GUICmdAckDSimPanelImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	QImage	RetImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	SendBack->AckImage=RetImage;
	SendBack->MakeImage(localPage,Layer,MovX,MovY,ZoomRate);

	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(sRoot,sName);
	if(Ab!=NULL){
		QImage	TmpImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
		TmpImage.fill(0);
		CmdAlgoSimulate	Da(GetLayersBase());
		Da.Image			=&TmpImage;
		Da.ItemID			=ItemID;
		Da.Layer			=Layer;
		Da.MovX				=MovX;//+Rx;
		Da.MovY				=MovY;//+Ry;
		Da.ZoomRate			=ZoomRate;
		Da.ModeShowArea		=ModeShowArea		;
		Da.ModeShowInside	=ModeShowInside		;
		Da.ModeShowOutside	=ModeShowOutside	;
		Da.ResultAngleNumber=ResultAngleNumber;
		Da.ResultGlobalShiftX=Rx;
		Da.ResultGlobalShiftY=Ry;
		Da.ShiftBySelfX		=ShiftBySelfX	;
		Da.ShiftBySelfY		=ShiftBySelfY	;
		Ab->GetPageData(localPage)->TransmitDirectly(&Da);
		QPainter	Pnt(&SendBack->AckImage);
		Pnt.drawImage(0,0,TmpImage);
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

	DataInPage	*Pg=GetLayersBase()->GetPageData(LocalPage);
	if(Pg->GetLayerData(Layer)->GetTargetBuff().IsNull()==true){
		return;
	}
	if(Layer<0){
		for(int y=0;y<H;y++){
			BYTE	*d=AckImage.scanLine(y);
			int	Y=y*Z-movy;
			if(0<=Y && Y<GetMaxLines(LocalPage)){
				BYTE	*sR=Pg->GetLayerData(0)->GetTargetBuff().GetY(Y);
				BYTE	*sG=Pg->GetLayerData(1)->GetTargetBuff().GetY(Y);
				BYTE	*sB=Pg->GetLayerData(2)->GetTargetBuff().GetY(Y);
				double	fX=-movx;
				for(int x=0;x<W;x++){
					int	X=fX;
					if(0<=X && X<GetDotPerLine(LocalPage)){
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
	else{
		if(Layer>=GetLayerNumb(LocalPage)){
			Layer=GetLayerNumb(LocalPage)-1;
		}
		for(int y=0;y<H;y++){
			BYTE	*d=AckImage.scanLine(y);
			int	Y=y*Z-movy;
			if(0<=Y && Y<GetMaxLines(LocalPage)){
				BYTE	*sR=Pg->GetLayerData(Layer)->GetTargetBuff().GetY(Y);
				double	fX=-movx;
				for(int x=0;x<W;x++){
					int	X=fX;
					if(0<=X && X<GetDotPerLine(LocalPage)){
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
