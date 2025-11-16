#include "XTypeDef.h"
#include "EasyShowAlignmentForm.h"
#include "ui_EasyShowAlignmentForm.h"
#include "EasyShowAlignment.h"
#include "EasyPropertyAlignmentForm.h"
#include "swap.h"
#include "XDrawFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

AlignmentMarkPanel::AlignmentMarkPanel(AlignmentLargePointList *L,EasyShowAlignmentForm *p)
:Parent(p),Data(*L)
{
	Selected=false;
	LastX=LastY=-1;
}

void    AlignmentMarkPanel::MakeData(void)
{
	EachMaster *m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(Parent->Parent->SlaveNo);
	if(m!=NULL){
		XYData	*XY=m->GetOutlineOffset(m->GetCurrentPhase(), Data.Page);
		int	ShiftX=max(Data.XSize,Data.MoveDotX);
		int	ShiftY=max(Data.YSize,Data.MoveDotY);
		movx=-(XY->x+Data.Cx-ShiftX);
		movy=-(XY->y+Data.Cy-ShiftY);
		double	Zx=width ()/(double)(2*ShiftX);
		double	Zy=height()/(double)(2*ShiftY);
		ZoomRate=min(Zx,Zy);
	}
}

void    AlignmentMarkPanel::paintEvent(QPaintEvent *event)
{
	int	SlaveNo=Parent->Parent->SlaveNo;
	EachMaster *m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		IntegrationCmdReqAlignmentImage	RCmd(Parent->GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationCmdAckAlignmentImage	ACmd(Parent->GetLayersBase(),sRoot,sName,SlaveNo);

		RCmd.Data.Phase=m->GetCurrentPhase();
		RCmd.Data.movx		=movx;
		RCmd.Data.movy		=movy;
		RCmd.Data.ZoomRate	=ZoomRate;
		RCmd.Data.ImageWidth=width();
		RCmd.Data.ImageHeight=height();
		RCmd.Data.Layer		=Data.Layer;
		RCmd.Data.ItemID	=Data.ItemID;
		if(RCmd.Send(SlaveNo,Data.Page,ACmd)==true){
			if(ACmd.Image!=NULL){
				AlignmentImage=*ACmd.Image;
				QPainter	Pnt(this);
				Pnt.drawImage(0,0,AlignmentImage);

				if(Selected==true){
					Pnt.setPen(Qt::red);
					for(int L=0;L<4;L++){
						Pnt.drawLine(L,L,width()-L,L);
						Pnt.drawLine(L,L,L,height()-L);
						Pnt.drawLine(L,height()-L-1,width()-L,height()-L-1);
						Pnt.drawLine(width()-1-L,L,width()-1-L,height()-L);
					}
				}
				else{
					Pnt.setPen(Qt::yellow);
					for(int L=0;L<2;L++){
						Pnt.drawLine(L,L,width()-L,L);
						Pnt.drawLine(L,L,L,height()-L);
						Pnt.drawLine(L,height()-L-1,width()-L,height()-L-1);
						Pnt.drawLine(width()-1-L,L,width()-1-L,height()-L);
					}
				}
			}
		}
	}
}
void    AlignmentMarkPanel::mousePressEvent(QMouseEvent *e)
{
	Parent->SetSelect(this);
	LastX=e->pos().x();
	LastY=e->pos().y();
}
void    AlignmentMarkPanel::mouseReleaseEvent(QMouseEvent *event)
{
}
void    AlignmentMarkPanel::mouseMoveEvent(QMouseEvent *e)
{
	if(e->button()==Qt::LeftButton){
		int	dx=e->pos().x()-LastX;
		int	dy=e->pos().y()-LastY;
		movx+=dx/ZoomRate;
		movy+=dy/ZoomRate;
		LastX+=dx;
		LastY+=dy;
	}
}
void    AlignmentMarkPanel::wheelEvent(QWheelEvent *e)
{
	int	D=e->pixelDelta().y();

	if(D>0){
	    int LX=(int)((double)e->position().x()/ZoomRate)/2;
		int LY=(int)((double)e->position().y()/ZoomRate)/2;
		movx=movx-LX;
		movy=movy-LY;
		ZoomRate=ZoomRate*2.0;
		repaint();
	}
	else if(D<0){
	    int LX=(int)((double)e->position().x()/ZoomRate);
		int LY=(int)((double)e->position().y()/ZoomRate);
		movx=movx+LX;
		movy=movy+LY;
		ZoomRate=ZoomRate/2.0;
		repaint();
	}
}

//===========================================================

EasyShowAlignmentForm::EasyShowAlignmentForm(LayersBase *Base,EasyShowAlignment *p,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::EasyShowAlignmentForm)
{
    ui->setupUi(this);
	ZoomRate=1.0;

	connect(ui->scrollArea->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(SlotScrollerChanged(int)));
}

EasyShowAlignmentForm::~EasyShowAlignmentForm()
{
    delete ui;
}

void    EasyShowAlignmentForm::ShowStart(void)
{
	int	SlaveNo=Parent->SlaveNo;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		Panels.RemoveAll();
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentMark	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=m->GetCurrentPhase();
			RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityGlobal);
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				for(AlignmentLargePointList *L=ACmd.Marks.GetFirst();L!=NULL;L=L->GetNext()){
					AlignmentMarkPanel	*P=new AlignmentMarkPanel(L,this);
					Panels.AppendList(P);
				}
			}
		}
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentMark	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=m->GetCurrentPhase();
			RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityHigh);
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				for(AlignmentLargePointList *L=ACmd.Marks.GetFirst();L!=NULL;L=L->GetNext()){
					AlignmentMarkPanel	*P=new AlignmentMarkPanel(L,this);
					Panels.AppendList(P);
				}
			}
		}
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentMark	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=m->GetCurrentPhase();
			RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityMiddle);
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				for(AlignmentLargePointList *L=ACmd.Marks.GetFirst();L!=NULL;L=L->GetNext()){
					AlignmentMarkPanel	*P=new AlignmentMarkPanel(L,this);
					Panels.AppendList(P);
				}
			}
		}
		for(int page=0;page<m->GetPageNumb();page++){
			IntegrationCmdReqAlignmentMark	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationCmdAckAlignmentMark	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.Phase		=m->GetCurrentPhase();
			RCmd.AreaPriority.Add(XAlignmentLargeArea::_PriorityLow);
			if(RCmd.Send(SlaveNo,m->GetLocalPageFromGlobal(page),ACmd)==true){
				for(AlignmentLargePointList *L=ACmd.Marks.GetFirst();L!=NULL;L=L->GetNext()){
					AlignmentMarkPanel	*P=new AlignmentMarkPanel(L,this);
					Panels.AppendList(P);
				}
			}
		}
	}
	QWidget	*w=ui->scrollArea->widget();
	QScrollBar *V=ui->scrollArea->verticalScrollBar();
	int	VWidth=26;	//V->width();
	int	W=ui->scrollArea->width()-VWidth-4;
	int	N=0;
	for(AlignmentMarkPanel *P=Panels.GetFirst();P!=NULL;P=P->GetNext(),N++){
		P->setParent(w);
		P->setGeometry(0,W*N,W,W);
		P->MakeData();
	}
	w->setGeometry(0,0,W,W*N);
	w->setMinimumSize(W,W*N);

	resizeEvent(NULL);
}

void EasyShowAlignmentForm::resizeEvent(QResizeEvent *event)
{
	ui->scrollArea->setGeometry(width()-ui->scrollArea->width(),0,ui->scrollArea->width(),height());
	ui->scrollArea->update();
	AlignmentImage=QImage(width()-ui->scrollArea->width(),height(),QImage::Format_ARGB32);

	int	SlaveNo=Parent->SlaveNo;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		int x1, y1 ,x2 ,y2;
		if(m->GetXY(x1, y1 ,x2 ,y2)==true){
			int	MasterWidth	=x2-x1;
			int	MasterHeight=y2-y1;
			double	Zx=AlignmentImage.width() /(double)MasterWidth;
			double	Zy=AlignmentImage.height()/(double)MasterHeight;
			ZoomRate=min(Zx,Zy);
		}
	}
}

void    EasyShowAlignmentForm::SetSelect(AlignmentMarkPanel *s)
{
	for(AlignmentMarkPanel *P=Panels.GetFirst();P!=NULL;P=P->GetNext()){
		P->Selected=false;
	}
	s->Selected=true;
	for(AlignmentMarkPanel *P=Panels.GetFirst();P!=NULL;P=P->GetNext()){
		P->repaint();
	}
	repaint();
}
void    EasyShowAlignmentForm::SlotScrollerChanged(int)
{
	repaint();
}
void    EasyShowAlignmentForm::paintEvent(QPaintEvent *event)
{
	int	SlaveNo=Parent->SlaveNo;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		for(int page=0;page<m->GetPageNumb();page++){
			ImagePointerContainer ImageList;
			m->GetMasterImage(m->GetCurrentPhase() ,page ,ImageList);
			XYData	*XY=m->GetOutlineOffset(m->GetCurrentPhase(), page);
			ImageList.MakeImage(AlignmentImage ,XY->x ,XY->y,ZoomRate);
		}
	}
	QPainter	Pnt(this);
	Pnt.drawImage(0,0,AlignmentImage);

	Pnt.setPen(Qt::yellow);
	for(AlignmentMarkPanel *P=Panels.GetFirst();P!=NULL;P=P->GetNext()){
		if(P->Selected==true){
			QScrollBar *V=ui->scrollArea->verticalScrollBar();
			int	StartY	=P->geometry().top()+P->height()/2 - V->value();
			int	StartX	=width()-ui->scrollArea->width();
			int	EndX	=P->Data.Cx*ZoomRate;
			int	EndY	=P->Data.Cy*ZoomRate;

			::DrawArrow(StartX/ZoomRate ,StartY/ZoomRate ,EndX/ZoomRate ,EndY/ZoomRate
				 ,Pnt ,0,0 ,ZoomRate ,10);
		}
	}
}
void	EasyShowAlignmentForm::ShowInPlayer		(int64 shownInspectionID)
{
	for(AlignmentMarkPanel *P=Panels.GetFirst();P!=NULL;P=P->GetNext()){
		P->repaint();
	}	
}

//===========================================================
IntegrationCmdReqAlignmentImage::IntegrationCmdReqAlignmentImage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdReqAlignmentImage::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;

}
bool	IntegrationCmdReqAlignmentImage::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	return true;
}

void	IntegrationCmdReqAlignmentImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationCmdAckAlignmentImage	*SendBack
		=GetSendBackIntegration(IntegrationCmdAckAlignmentImage,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	int32	LocalPage	=cmd;
	SendBack->Image		=new QImage(Data.ImageWidth,Data.ImageHeight,QImage::Format_ARGB32);
	SendBack->ImageWidth	=Data.ImageWidth;
	SendBack->ImageHeight	=Data.ImageHeight;

	PageDataInOnePhase	*Dh=GetLayersBase()->GetPageDataPhase(Data.Phase);
	if(Dh!=NULL){
		DataInPage	*Dp=Dh->GetPageData(LocalPage);
		ImagePointerContainer Images;
		Dp->GetTargetImages	(Images);
		Images.MakeImage(*SendBack->Image ,Data.movx ,Data.movy,Data.ZoomRate);
	}
	{
		QPainter	Pnt(SendBack->Image);
		
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AlignmentLarge");
		if(Ab!=NULL){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Data.Phase);
			if(Ah!=NULL){
				AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(LocalPage);
				if(Ap!=NULL){
					AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(Data.Layer);
					if(AL!=NULL){
						XAlignmentLarge	*item=(XAlignmentLarge *)AL->SearchIDItem(Data.ItemID);
						if(item!=NULL){
							ResultInItemRoot	*R=item->GetCurrentResult();
		
							item->DrawResultItem(R,*SendBack->Image 
												,Pnt,Data.movx ,Data.movy,Data.ZoomRate,false);
						}
					}
				}
			}
		}
	}
	SendBack->Send(this ,slaveNo,LocalPage);
	CloseSendBackIntegration(SendBack);
}

IntegrationCmdAckAlignmentImage::IntegrationCmdAckAlignmentImage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
	Image=NULL;
}
IntegrationCmdAckAlignmentImage::~IntegrationCmdAckAlignmentImage(void)
{
	if(Image!=NULL){
		delete	Image;
		Image=NULL;
	}
}
bool	IntegrationCmdAckAlignmentImage::Load(QIODevice *f)
{
	if(::Load(f,ImageWidth)==false)
		return false;
	if(::Load(f,ImageHeight)==false)
		return false;
	if(Image!=NULL){
		if(Image->width()!=ImageWidth || Image->height()!=ImageHeight){
			delete	Image;
			Image=NULL;
		}
	}
	if(Image==NULL){
		Image=new QImage(ImageWidth,ImageHeight,QImage::Format_ARGB32);
	}
	if(::Load(f,*Image)==false)
		return false;
	return true;
}
bool	IntegrationCmdAckAlignmentImage::Save(QIODevice *f)
{
	if(::Save(f,ImageWidth)==false)
		return false;
	if(::Save(f,ImageHeight)==false)
		return false;
	if(::Save(f,*Image)==false)
		return false;
	return true;
}