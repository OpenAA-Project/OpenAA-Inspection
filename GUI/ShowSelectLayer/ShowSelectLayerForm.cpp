#include "ShowSelectLayerForm.h"
#include "ui_ShowSelectLayerForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XCrossObj.h"
#include "XDisplayBitImage.h"
#include "mtPushButtonColored.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShowSelectLayerForm::ShowSelectLayerForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowSelectLayerForm)
{
    ui->setupUi(this);

    DisplayImagePointDim=NULL;
}

ShowSelectLayerForm::~ShowSelectLayerForm()
{
    delete ui;

    if(DisplayImagePointDim!=NULL){
        delete  []DisplayImagePointDim;
        DisplayImagePointDim=NULL;
    }
}
bool FunctionMouseMove(FunctionServerClass *Obj,GUIFormBase *TargetObj,int GlobalPosX,int GlobalPosY)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL && DImage->IsShown()==true){
		ShowSelectLayerForm	*Form=dynamic_cast<ShowSelectLayerForm *>(Obj);
		if(Form!=NULL && Form->isEnabled()==true){
			Form->ShowXY(DImage,GlobalPosX,GlobalPosY);
		}
	}
	return true;
}

void	ShowSelectLayerForm::ReadyParam(void)
{
    if(DisplayImagePointDim!=NULL){
        delete  []DisplayImagePointDim;
    }
    int N=DisplayImageInst.count();
    DisplayImagePointDim=new DisplayImage *[N];

	for(int i=0;i<DisplayImageInst.count();i++){
		QString	HookTargetInst=DisplayImageInst[i];
		GUIFormBase *s=dynamic_cast<GUIFormBase *>(GetLayersBase()->FindByName(HookTargetInst));
		if(s!=NULL){
			DisplayImage *TargetPanel=dynamic_cast<DisplayImage *>(s);
			if(TargetPanel!=NULL){
				TargetPanel->SetHookInMouseMove		(this,FunctionMouseMove);
			}
		}
	}
}

void ShowSelectLayerForm::paintEvent(QPaintEvent *event)
{
    QPainter    Pnt(this);

    Pnt.fillRect(0,0,width(),height(),Qt::white);

	if(Color.GetLayerNumb()>0){
		int	MerginX=30;
		int	MerginY=50;
		int	GraphW=width()-MerginX;
		int	GraphH=height()-MerginY;
		double	ZoomX=GraphW/((double)Color.GetLayerNumb());
		double	ZoomY=GraphH/256.0;

		Pnt.setPen(Qt::black);
		Pnt.drawLine(MerginX,0,MerginX,height());
		Pnt.drawLine(0,height()-MerginY,width(),height()-MerginY);

		Pnt.setPen(Qt::black);
		Pnt.setBrush(Qt::black);
		int	CDivX=1;
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		if(LayerNumb<=5)
			CDivX=1;
		else if(LayerNumb<=20)
			CDivX=5;
		else if(LayerNumb<=50)
			CDivX=10;
		else if(LayerNumb<=128)
			CDivX=20;
		else if(LayerNumb<=256)
			CDivX=50;
		else{
			CDivX=LayerNumb/5;
		}
		int	CDivN=LayerNumb/CDivX;
		QFontMetrics Fnt=fontMetrics();
		for(int nx=0;nx<=CDivN;nx++){
			Pnt.drawText(MerginX+nx*CDivX*ZoomX,height()-MerginY+Fnt.height()+2
						,QString::number(nx*CDivX));
		}

		Pnt.setPen(Qt::DashDotLine);
		for(int i=50;i<256;i+=50){
			Pnt.drawLine(0,height()-MerginY-i*ZoomY,width(),height()-MerginY-i*ZoomY);
		}
		Pnt.setPen(Qt::SolidLine);
		Pnt.setPen(Qt::red);
		int	LastX=0;
		int	LastY=0;
		for(int i=0;i<Color.GetLayerNumb();i++){
			int	c=Color.GetBrightness(i);
			int	X=i*ZoomX;
			int	Y=c*ZoomY;
			Pnt.drawLine(LastX+MerginX,height()-MerginY-LastY
						,X+MerginX,height()-MerginY-Y);
			LastX=X;
			LastY=Y;
		}
	}
}

void    ShowSelectLayerForm::ShowXY(DisplayImage *DImage,int GlobalPosX,int GlobalPosY)
{
	int	LocalX,LocalY;
	int	Page=GetLayersBase()->GetLocalMatrixFromGlobal(GlobalPosX,GlobalPosY,LocalX,LocalY);
	if(Page>=0){
		GUICmdReqMultiLayerColor	RCmd(GetLayersBase(),sRoot,sName,Page);
		GUICmdAckMultiLayerColor	ACmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.DType=DImage->GetDisplayType();
		RCmd.LocalX=LocalX;
		RCmd.LocalY=LocalY;
		if(RCmd.Send(Page,0,ACmd)==true){
			Color=ACmd.Color;
			repaint();
		}
	}	
}


//================================================================================
GUICmdReqMultiLayerColor::GUICmdReqMultiLayerColor(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMultiLayerColor::Load(QIODevice *f)
{
	int32	d;
	if(::Load(f,d)==false)	return false;
	DType=(DisplayImage::DisplayType)d;
	if(::Load(f,LocalX)==false)	return false;
	if(::Load(f,LocalY)==false)	return false;
	return true;
}
bool	GUICmdReqMultiLayerColor::Save(QIODevice *f)
{
	int32	d=(int32)DType;
	if(::Save(f,d)==false)	return false;
	if(::Save(f,LocalX)==false)	return false;
	if(::Save(f,LocalY)==false)	return false;
	return true;
}

void	GUICmdReqMultiLayerColor::Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName)
{
	GUICmdAckMultiLayerColor	*SendBack=GetSendBack(GUICmdAckMultiLayerColor,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	DataInPage	*dp=GetLayersBase()->GetPageData(localPage);
	if(DType==DisplayImage::__Master)
		dp->GetMasterPixel(SendBack->Color ,LocalX,LocalY);
	else
	if(DType==DisplayImage::__Target)
		dp->GetTargetPixel(SendBack->Color ,LocalX,LocalY);

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMultiLayerColor::GUICmdAckMultiLayerColor(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckMultiLayerColor::Load(QIODevice *f)
{
	if(Color.Load(f)==false)	return false;
	return true;
}
bool	GUICmdAckMultiLayerColor::Save(QIODevice *f)
{
	if(Color.Save(f)==false)	return false;
	return true;
}

