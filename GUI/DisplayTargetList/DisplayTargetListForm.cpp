#include "DisplayTargetList.h"
#include "XGeneralFunc.h"
#include "XResult.h"
#include "ListSelectFixedPage.h"
#include "XDataInLayer.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


TargetImageWindow::TargetImageWindow(TargetPanelInList *p)
	:ServiceForLayers(p->GetLayersBase())
	,Parent(p)
{}
TargetImageWindow::~TargetImageWindow()
{
}

void TargetImageWindow::paintEvent(QPaintEvent *event)
{
	GUICmdReqImageForList	RCmd(GetLayersBase(),sRoot,sName,Parent->Page);
	GUICmdAckImageForList	ACmd(GetLayersBase(),sRoot,sName,Parent->Page);
	RCmd.Phase	=GetLayersBase()->GetCurrentPhase();
	RCmd.GWidth	=width();
	RCmd.GHeight=height();
	RCmd.ShowNGMark=Parent->IsBlickON();
	if(RCmd.Send(Parent->Page,0,ACmd)==true){
		if(Image.width()!=RCmd.GWidth || Image.height()!=RCmd.GHeight){
			Image=QImage(RCmd.GWidth,RCmd.GHeight,QImage::Format_RGB32);
		}
		for(int y=0;y<RCmd.GHeight;y++){
			QRgb	*d=(QRgb *)Image.scanLine(y);
			BYTE	*s=&ACmd.ImageData[y*RCmd.GWidth*3];
			for(int x=0;x<RCmd.GWidth;x++){
				*d=qRgb(*(s+0),*(s+1),*(s+2));
				s+=3;
				d++;
			}
		}
		Parent->SetResult(ACmd.ResultOK,ACmd.MaxError,ACmd.TimeOver);
	}
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,Image);
}
void TargetImageWindow::mouseReleaseEvent(QMouseEvent *event)
{
	Parent->MouseReleased(event);
}


//======================================================================
TargetPanelInList::TargetPanelInList(DisplayTargetList *p ,QWidget *parent,int page)
	:ServiceForLayers(p->GetLayersBase())
	,Parent(p),Page(page),ImageWindow(this)
{
	setParent(parent);

	Title.setParent(this);
	Title.setGeometry(1,1,width(),TitleHeightTarget);
	Title.setAutoFillBackground(true);
	ImageWindow.setParent(this);
	ImageWindow.move(1,1+TitleHeightTarget);
}

void	TargetPanelInList::SetPage(int page)
{
	Page=page;
	Title.setText(QString::number(Page));
}

void	TargetPanelInList::resizeEvent(QResizeEvent *event)
{
	Title.setGeometry(0,0,width(),TitleHeightTarget);
	ImageWindow.resize(width()-2,height()-TitleHeightTarget-2);
}

bool	TargetPanelInList::IsBlickON(void)
{
	return Parent->BlinkNG;
}

void	TargetPanelInList::SetResult(bool3 ResultOK,bool MaxError,bool TimeOver)
{
	QString		TitleMessage;
	QPalette	P=Title.palette();
	if(ResultOK==none3){
		P.setColor(QPalette::Window,Qt::lightGray);
		TitleMessage=":---";
	}
	else
	if(ResultOK==true3){
		P.setColor(QPalette::Window,Qt::green);
		TitleMessage=":OK";
	}
	else
	if(ResultOK==false3){
		P.setColor(QPalette::Window,Qt::red);
		TitleMessage=":NG";
	}
	Title.setPalette(P);

	if(MaxError==true){
		TitleMessage=TitleMessage+QString("-Max");
	}
	if(TimeOver==true){
		TitleMessage=TitleMessage+QString("-TM");
	}

	Title.setText(QString::number(Page)+TitleMessage);
}
void	TargetPanelInList::MouseReleased(QMouseEvent *event)
{
	Parent->MouseReleased(Page,event);
}
//======================================================================

DisplayTargetList::DisplayTargetList(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	PanelSizeX=250;
	PanelSizeY=250;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	ScrollArea.setParent(this);
	ScrollArea.move(0,0);
	ScrollWidget	=new QWidget();
	ScrollWidget->setParent(&ScrollArea);
	ScrollWidget->move(0,0);
	ScrollArea.setWidget(ScrollWidget);

	GetParamGUI()->SetParam(&PanelSizeX, /**/"DisplayTargetList",/**/"PanelSizeX"	
												,"Panel width");
	GetParamGUI()->SetParam(&PanelSizeY, /**/"DisplayTargetList",/**/"PanelSizeY"	
												,"Panel height");
	BlinkNG	=false;
	Timer.setParent(this);
	Timer.setSingleShot(false);
	Timer.setInterval(300);
	connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	Timer.start();
}


void	DisplayTargetList::ResizeAction()
{
	ScrollArea.resize(width(),height());
	int	MaxXk=0;
	int	MaxYk=0;
	if(PanelSizeX>0 && PanelSizeY>0){
		int	Xn=width()/PanelSizeX;
		if(Xn==0)
			Xn=1;
		int	Yn=height()/PanelSizeY;
		if(Yn==0)
			Yn=1;

		int	N=0;
		for(TargetPanelInList *p=TargetPaneStocker.GetFirst();p!=NULL;p=p->GetNext(),N++){
			int	Yk=N/Xn;
			int	Xk=N%Xn;
			p->move(Xk*PanelSizeX,Yk*PanelSizeY);
			MaxXk=max(MaxXk,Xk);
			MaxYk=max(MaxYk,Yk);
		}
	}
	ScrollWidget->resize((MaxXk+1)*PanelSizeX,(MaxYk+1)*PanelSizeY);
}

bool	DisplayTargetList::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	for(TargetPanelInList *p=TargetPaneStocker.GetFirst();p!=NULL;p=p->GetNext()){
		p->repaint();
	}
	return true;
}
bool	DisplayTargetList::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	bool	Reallocated=false;
	while(newPageNumb>TargetPaneStocker.GetCount()) {
		TargetPanelInList	*p=new TargetPanelInList(this,ScrollWidget,0);
		p->resize(PanelSizeX,PanelSizeY);
		TargetPaneStocker.AppendList(p);
		Reallocated=true;
	}
	while(newPageNumb<TargetPaneStocker.GetCount()) {
		TargetPanelInList	*p=TargetPaneStocker.GetLast();
		TargetPaneStocker.RemoveList(p);
		delete	p;
		Reallocated=true;
	}
	if(Reallocated==true){
		int	Page=0;
		for(TargetPanelInList *p=TargetPaneStocker.GetFirst();p!=NULL;p=p->GetNext(),Page++){
			p->SetPage(Page);
		}
		ResizeAction();
		for(TargetPanelInList *p=TargetPaneStocker.GetFirst();p!=NULL;p=p->GetNext()){
			p->show();
			p->repaint();
		}
	}
	return true;
}
bool	DisplayTargetList::InsertPage(int IndexPage)	//Create page before Indexed page
{
	Reallocate(GetPhaseNumb(), GetPageNumb(),GetLayerNumb(0));
}
bool	DisplayTargetList::RemovePage(int IndexPage)
{
	Reallocate(GetPhaseNumb(), GetPageNumb(),GetLayerNumb(0));
}
void	DisplayTargetList::BuildForShow(void)
{
	Reallocate(GetPhaseNumb(), GetPageNumb(),GetLayerNumb(0));
}

void	DisplayTargetList::SlotTimeOut()
{
	for(TargetPanelInList *p=TargetPaneStocker.GetFirst();p!=NULL;p=p->GetNext()){
		p->repaint();
	}
	BlinkNG	=!BlinkNG;
}
void	DisplayTargetList::MouseReleased(int Page,QMouseEvent *event)
{
    for(int i=0;i<RelatedInst.count();i++){
        GUIFormBase *f=GetLayersBase()->FindByName(RelatedInst[i]);
        if(f!=NULL){
			CmdSetCurrentPage	Cmd(GetLayersBase());
			Cmd.CurrentPage=Page;
			f->TransmitDirectly(&Cmd);
		}
	}
}
//======================================================================
GUICmdReqImageForList::GUICmdReqImageForList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqImageForList::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)		return false;
	if(::Load(f,GWidth )==false)	return false;
	if(::Load(f,GHeight)==false)	return false;
	if(::Load(f,ShowNGMark)==false)	return false;
	return(true);
}
bool	GUICmdReqImageForList::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)		return false;
	if(::Save(f,GWidth )==false)	return false;
	if(::Save(f,GHeight)==false)	return false;
	if(::Save(f,ShowNGMark)==false)	return false;
	return(true);
}

void	GUICmdReqImageForList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckImageForList	*SendBack=GetSendBack(GUICmdAckImageForList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Phase);
	if(Ph!=NULL){
		DataInPage *Pd=Ph->GetPageData(localPage);
		if(Pd!=NULL){
			int	DotPerLine	=Pd->GetDotPerLine();
			int	MaxLines	=Pd->GetMaxLines();

			double	Zx=((double)GWidth )/((double)DotPerLine);
			double	Zy=((double)GHeight)/((double)MaxLines);
			double	ZoomRate=min(Zx,Zy);

			SendBack->MakeImage(Pd,ZoomRate,GWidth ,GHeight,ShowNGMark);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}


GUICmdAckImageForList::GUICmdAckImageForList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ImageData=NULL;
	GWidth =0;
	GHeight=0;
	ResultOK=none3;
}
GUICmdAckImageForList::~GUICmdAckImageForList(void)
{
	if(ImageData!=NULL){
		delete	[]ImageData;
		ImageData=NULL;
	}
}

bool	GUICmdAckImageForList::Load(QIODevice *f)
{
	if(::Load(f,GWidth )==false)	return false;
	if(::Load(f,GHeight)==false)	return false;
	if(::Load(f,ResultOK)==false)	return false;
	if(::Load(f,MaxError)==false)	return false;
	if(::Load(f,TimeOver)==false)	return false;
	int	DataLen=GWidth*GHeight*3;
	if(f->read((char *)ImageData,DataLen)!=DataLen)	return false;
	return true;
}
bool	GUICmdAckImageForList::Save(QIODevice *f)
{
	if(::Save(f,GWidth )==false)	return false;
	if(::Save(f,GHeight)==false)	return false;
	if(::Save(f,ResultOK)==false)		return false;
	if(::Save(f,MaxError)==false)	return false;
	if(::Load(f,TimeOver)==false)	return false;
	int	DataLen=GWidth*GHeight*3;
	if(f->write((const char *)ImageData,DataLen)!=DataLen)	return false;
	return true;
}

void	GUICmdAckImageForList::MakeImage(DataInPage *Pd,double ZoomRate,int tGWidth ,int tGHeight,bool ShowNGMark)
{
	if(tGWidth!=GWidth || tGHeight!=GHeight){
		if(ImageData!=NULL){
			delete	[]ImageData;
			ImageData=NULL;
		}
		GWidth	=tGWidth;
		GHeight	=tGHeight;
	}
	if(tGWidth!=TmpImage.width() || tGHeight!=TmpImage.height()){
		TmpImage=QImage(tGWidth,tGHeight,QImage::Format_RGB32);
	}
	if(ImageData==NULL){
		int	DataLen=tGWidth*tGHeight*3;
		ImageData=new BYTE[DataLen];
	}
	ImageBuffer *Images[3];
	int	N=Pd->GetTargetImages	(Images,3);
	double	Z=1.0/ZoomRate;

	int	MaxY=min((int)(Images[0]->GetHeight()*ZoomRate),GHeight);
	int	MaxX=min((int)(Images[0]->GetWidth()*ZoomRate),GWidth);

	if(ShowNGMark==false){
		ResultInspection	*R=GetLayersBase()->GetCurrentResultForDraw();
		NPListPack<ResultPosInfo> RContainer;
		R->GatherResult(Pd->GetPage() ,ResultOK ,MaxError , TimeOver);

		if(N==3){
			int y;
			for(y=0;y<MaxY;y++){
				int	Y=y*Z;
				double	Xd=0;
				BYTE	*s0=Images[0]->GetYWithoutDepended(Y);
				BYTE	*s1=Images[1]->GetYWithoutDepended(Y);
				BYTE	*s2=Images[2]->GetYWithoutDepended(Y);
				BYTE	*d=&ImageData[y*GWidth*3];
				int x;
				for(x=0;x<MaxX;x++,Xd+=Z){
					int	X=Xd;
					*(d+0)=s0[X];
					*(d+1)=s1[X];
					*(d+2)=s2[X];
					d+=3;
				}
				for(;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
			for(;y<GHeight;y++){
				BYTE	*d=&ImageData[y*GWidth*3];
				for(int x=0;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
		}
		else
		if(N==2){
			int y;
			for(y=0;y<MaxY;y++){
				int	Y=y*Z;
				double	Xd=0;
				BYTE	*s0=Images[0]->GetYWithoutDepended(Y);
				BYTE	*s1=Images[1]->GetYWithoutDepended(Y);
				BYTE	*d=&ImageData[y*GWidth*3];
				int x;
				for(x=0;x<MaxX;x++,Xd+=Z){
					int	X=Xd;
					*(d+0)=s0[X];
					*(d+1)=s1[X];
					*(d+2)=s1[X];
					d+=3;
				}
				for(;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
			for(;y<GHeight;y++){
				BYTE	*d=&ImageData[y*GWidth*3];
				for(int x=0;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
		}
		else
		if(N==1){
			int y;
			for(y=0;y<MaxY;y++){
				int	Y=y*Z;
				double	Xd=0;
				BYTE	*s0=Images[0]->GetYWithoutDepended(Y);
				BYTE	*d=&ImageData[y*GWidth*3];
				int x;
				for(x=0;x<MaxX;x++,Xd+=Z){
					int	X=Xd;
					*(d+0)=s0[X];
					*(d+1)=s0[X];
					*(d+2)=s0[X];
					d+=3;
				}
				for(;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
			for(;y<GHeight;y++){
				BYTE	*d=&ImageData[y*GWidth*3];
				for(int x=0;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
		}
	}
	else{
		ResultInspection	*R=GetLayersBase()->GetCurrentResultForDraw();

		TmpImage.fill(0);
		QPainter	Pnt(&TmpImage);
		QRgb NGCol=qRgb(255,0,0);
		NPListPack<ResultPosInfo> RContainer;
		R->GatherResult(Pd->GetPage() ,RContainer,ResultOK ,MaxError , TimeOver);
		for(ResultPosInfo *r=RContainer.GetFirst();r!=NULL;r=r->GetNext()){
			r->RPos->DrawResult(r->RItem,TmpImage ,Pnt ,0,0 ,ZoomRate
								,5,NGCol,3,true);
		}

		if(N==3){
			int y;
			for(y=0;y<MaxY;y++){
				int	Y=y*Z;
				double	Xd=0;
				BYTE	*s0=Images[0]->GetYWithoutDepended(Y);
				BYTE	*s1=Images[1]->GetYWithoutDepended(Y);
				BYTE	*s2=Images[2]->GetYWithoutDepended(Y);
				QRgb	*q=(QRgb *)TmpImage.scanLine(y);
				BYTE	*d=&ImageData[y*GWidth*3];
				int	x=0;
				for(x=0;x<MaxX;x++,Xd+=Z,q++){
					if((*q & 0xFFFFFF)!=0){
						*(d+0)=qRed(*q);
						*(d+1)=qGreen(*q);
						*(d+2)=qBlue(*q);
					}
					else{
						int	X=Xd;
						*(d+0)=s0[X];
						*(d+1)=s1[X];
						*(d+2)=s2[X];
					}
					d+=3;
				}
				for(;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
			for(;y<GHeight;y++){
				BYTE	*d=&ImageData[y*GWidth*3];
				for(int x=0;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
		}
		else
		if(N==2){
			int y;
			for(y=0;y<MaxY;y++){
				int	Y=y*Z;
				double	Xd=0;
				BYTE	*s0=Images[0]->GetYWithoutDepended(Y);
				BYTE	*s1=Images[1]->GetYWithoutDepended(Y);
				QRgb	*q=(QRgb *)TmpImage.scanLine(y);
				BYTE	*d=&ImageData[y*GWidth*3];
				int	x=0;
				for(x=0;x<MaxX;x++,Xd+=Z,q++){
					if((*q & 0xFFFFFF)!=0){
						*(d+0)=qRed(*q);
						*(d+1)=qGreen(*q);
						*(d+2)=qBlue(*q);
					}
					else{
						int	X=Xd;
						*(d+0)=s0[X];
						*(d+1)=s1[X];
						*(d+2)=s1[X];
					}
					d+=3;
				}
				for(;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
			for(;y<GHeight;y++){
				BYTE	*d=&ImageData[y*GWidth*3];
				for(int x=0;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
		}
		else
		if(N==1){
			int y;
			for(y=0;y<MaxY;y++){
				int	Y=y*Z;
				double	Xd=0;
				BYTE	*s0=Images[0]->GetYWithoutDepended(Y);
				QRgb	*q=(QRgb *)TmpImage.scanLine(y);
				BYTE	*d=&ImageData[y*GWidth*3];
				int	x=0;
				for(x=0;x<MaxX;x++,Xd+=Z,q++){
					if((*q & 0xFFFFFF)!=0){
						*(d+0)=qRed(*q);
						*(d+1)=qGreen(*q);
						*(d+2)=qBlue(*q);
					}
					else{
						int	X=Xd;
						*(d+0)=s0[X];
						*(d+1)=s0[X];
						*(d+2)=s0[X];
					}
					d+=3;
				}
				for(;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
			for(;y<GHeight;y++){
				BYTE	*d=&ImageData[y*GWidth*3];
				for(int x=0;x<GWidth;x++){
					*(d+0)=0;
					*(d+1)=0;
					*(d+2)=0;
					d+=3;
				}
			}
		}
	}
}
