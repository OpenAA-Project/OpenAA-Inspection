#include "IntegrationStackMultiNGThumbnailForm.h"
#include "ui_IntegrationStackMultiNGThumbnailForm.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "LargeWindowForm.h"
#include "LargeMeasureWindowForm.h"
#include "LargeColorDifferenceForm.h"
#include "swap.h"
#include "XDLLType.h"
#include "XCriticalFunc.h"
#include <QScrollArea>
#include <QScrollBar>
#include "XMeasureLineMoveLibrary.h"
#include "XColorDifferenceLibrary.h"
#include "XDataAlgorithmList.h"
#include "XIntegrationStackNGThumbnailPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


ThumbnailPanel::ThumbnailPanel(InspectionList *L,IntegrationStackMultiNGThumbnailForm *p,EachMaster *m,int phase,NGPointInPage *page,IntegNGImage *imagePoint)
	:QWidget(p->GetParentWidget()),Parent(p),Result(L)
{
	Master		=m;
	Phase		=phase;
	RPage		=page;
	ImagePoint	=imagePoint;
	CurrentInspection	=NULL;
	RepresentativePoint	=NULL;
	MasterImage		=NULL;
	NGMarkImage		=NULL;
	Visible			=true;
	setMouseTracking(true);
}
ThumbnailPanel::~ThumbnailPanel(void)
{
	if(MasterImage!=NULL){
		delete	MasterImage;
		MasterImage=NULL;
	}
	if(NGMarkImage!=NULL){
		delete	NGMarkImage;
		NGMarkImage=NULL;
	}
}

LayersBase	*ThumbnailPanel::GetLayersBase(void)
{	
	return Parent->GetLayersBase();	
}

const	int	MessageHeight=13;
const	int	MessageRowCount=3;

void	ThumbnailPanel::MakeImage(void)
{
	int	W=Parent->ThumbnailWidth;
	int	H=Parent->ThumbnailHeight;
	int	Mergin=Parent->ThumbnailMergin;

	if(Parent->ShowInformation==true){
		H-=(MessageHeight+2)*MessageRowCount;
	}
	int	Cx,Cy;
	ImagePoint->GetCenter(Cx,Cy);
	double	Zx	=((double)W)/((double)ImagePoint->GetImage().width());
	double	Zy	=((double)H)/((double)ImagePoint->GetImage().height());
	double	ZoomRate=(Zx<Zy)?Zx:Zy;
	NGImage		=QImage(W,H,QImage::Format_ARGB32);
	NGImage.fill(Qt::black);
	QImage	Img=ImagePoint->GetImage().scaled (W,H,Qt::KeepAspectRatio,Qt::SmoothTransformation);
	QPainter	NGPnt(&NGImage);
	NGPnt.drawImage(0,0,Img);

	MasterImage	=new QImage(W,H,QImage::Format_ARGB32);
	NGMarkImage	=new QImage(W,H,QImage::Format_ARGB32);
	NGMarkImage->fill(0);
	
	int	r=3;
	int	D=6;
	QPainter	Pnt(NGMarkImage);
	int	dx=0;
	int	dy=0;
	int	AddedN=0;
	for(NGPoint *Rp=RPage->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
		int	TargetCx,TargetCy;
		Rp->GetTargetCenter(TargetCx,TargetCy);

		if(Rp->IsNG()==true
		&& ImagePoint->x1 <=TargetCx && TargetCx<ImagePoint->x2
		&& ImagePoint->y1 <=TargetCy && TargetCy<ImagePoint->y2){
			int	hx=TargetCx-Rp->MasterX;
			int	hy=TargetCy-Rp->MasterY;
			Pnt.setPen(Qt::red);
			Pnt.drawArc((TargetCx-ImagePoint->x1)*ZoomRate-r  ,(TargetCy-ImagePoint->y1)*ZoomRate-r  ,D  ,D  ,0,5760);
			Pnt.setPen(Qt::cyan);
			Pnt.drawArc((TargetCx-ImagePoint->x1)*ZoomRate-r-1,(TargetCy-ImagePoint->y1)*ZoomRate-r-1,D+2,D+2,0,5760);
			if(RepresentativePoint==NULL){
				RepresentativePoint=Rp;
			}
			int	mx,my;
			Rp->GetMasterCenter(mx,my);
			dx+=TargetCx-mx;
			dy+=TargetCy-my;
			AddedN++;
		}
	}
	if(AddedN!=0){
		dx/=AddedN;
		dy/=AddedN;
	}
	if(RepresentativePoint==NULL){
		for(NGPoint *Rp=RPage->NPListPack<NGPoint>::GetFirst();Rp!=NULL;Rp=Rp->GetNext()){
			if(Rp->IsNG()==true){
				int	cx,cy;
				Rp->GetTargetCenter(cx,cy);
				Pnt.setPen(Qt::red);
				Pnt.drawArc((cx-ImagePoint->x1)*ZoomRate-r  ,(cy-ImagePoint->y1)*ZoomRate-r  ,D  ,D  ,0,5760);
				Pnt.setPen(Qt::cyan);
				Pnt.drawArc((cx-ImagePoint->x1)*ZoomRate-r-1,(cy-ImagePoint->y1)*ZoomRate-r-1,D+2,D+2,0,5760);
				if(RepresentativePoint==NULL){
					RepresentativePoint=Rp;
				}
			}
		}
	}
	QPainter	ImgPnt(&NGImage);
	if(Parent->ShowInformation==true && RepresentativePoint!=NULL){
		Messages=Parent->GetInformation(Master->GetIntegrationSlaveNo(),Result,RepresentativePoint);
	}
	LayersBase	*LBase=GetLayersBase()->GetShadowTree(ImagePoint->ShadowLevel ,ImagePoint->ShadowNumber);
	int	Mx1=ImagePoint->x1;
	int	My1=ImagePoint->y1;
	int	Mx2=ImagePoint->x2;
	int	My2=ImagePoint->y2;
	double	tZoomRate=ZoomRate;
	if(LBase!=NULL){
		LBase->ConvertToTop(Mx1,My1);
		LBase->ConvertToTop(Mx2,My2);
		tZoomRate=ZoomRate/((double)(Mx2-Mx1))*((double)(ImagePoint->x2-ImagePoint->x1));
	}
	RPage->MakeMasterImage(MasterImage,(Mx1+Mx2)/2-dx,(My1+My2)/2-dy,tZoomRate);
}

int	ThumbnailPanel::Compare(ThumbnailPanel &src)
{
	int	d=Result->ID-src.Result->ID;
	if(d==0){
		if(RepresentativePoint!=NULL && src.RepresentativePoint!=NULL){
			d=RepresentativePoint->MasterY-src.RepresentativePoint->MasterY;
			if(d==0){
				d=RepresentativePoint->MasterX-src.RepresentativePoint->MasterX;
			}
		}
	}
	return -d;
}
void ThumbnailPanel::paintEvent ( QPaintEvent * event )
{
	if(Visible==true){
		QPainter	Pnt(this);

		if(Row!=Parent->GetCurrentIndex() || ShowingNGOnFlip==false){
			Pnt.drawImage(0,0,NGImage);
		}
		else{
			Pnt.drawImage(0,0,*MasterImage);
		}
		if(Row!=Parent->CurrentIndex){
			Pnt.drawImage(0,0,*NGMarkImage);
		}
		
		if(Parent->ShowInformation==true){
			{
				int	H=Parent->ThumbnailHeight;
				H-=(MessageHeight+2)*MessageRowCount;
				Pnt.setBrush(Qt::black);
				Pnt.setPen(Qt::black);
				Pnt.drawRect(0,H,width(),(MessageHeight+2)*MessageRowCount);
			}
			{
				int	H=Parent->ThumbnailHeight;
				H-=(MessageHeight+2)*MessageRowCount;
				Pnt.setBrush(Qt::white);
				Pnt.setPen(Qt::white);
				int	Mergin=Parent->ThumbnailMergin;
				int	CMessageRow=Messages.count();
				for(int row=0;row<CMessageRow;row++){
					Pnt.drawText(Mergin,H+MessageHeight+MessageHeight*row,Messages[row]);
				}
			}
		}

		if(Row==Parent->CurrentIndex){
			int	W=Parent->ThumbnailWidth;
			int	H=Parent->ThumbnailHeight;
			int	Mergin=Parent->ThumbnailMergin;
			QColor	Col=Qt::red;

			QPen	Pen(Col);
			Pen.setWidth(1);
			Pnt.setPen(Pen);

			if(Parent->ShowInformation==true){
				int	mh=0;	//MessageHeight*MessageRowCount;
				for(int L=0;L<Mergin;L++){
					Pnt.drawLine(L		,L			,W-1-L	,L			);
					Pnt.drawLine(W-1-L	,L			,W-1-L	,H-1-L-mh	);
					Pnt.drawLine(W-1-L	,H-1-L-mh	,L		,H-1-L-mh	);
					Pnt.drawLine(L		,H-1-L-mh	,L		,L			);
				}
			}
			else{
				for(int L=0;L<Mergin;L++){
					Pnt.drawLine(L		,L		,W-1-L	,L		);
					Pnt.drawLine(W-1-L	,L		,W-1-L	,H-1-L	);
					Pnt.drawLine(W-1-L	,H-1-L	,L		,H-1-L	);
					Pnt.drawLine(L		,H-1-L	,L		,L		);
				}
			}
			ShowingNGOnFlip=!ShowingNGOnFlip;
		}
	}
}
void ThumbnailPanel::mousePressEvent ( QMouseEvent * event )
{
	if(Visible==true){
		Parent->LastPressedTime	=::GetComputerMiliSec();
		Parent->CurrentIndex=Row;
		Parent->PressPanel();
		Parent->RepaintPanel();
		Parent->BroadcastNGPoint();
	}
}
void ThumbnailPanel::mouseDoubleClickEvent ( QMouseEvent * event )
{
	if(Visible==true){
		if(Parent->LargeWindow!=NULL){
			Parent->LargeWindow->Parent=NULL;
			delete	Parent->LargeWindow;
			Parent->LargeWindow=NULL;
		}
		if(Parent->LargeMeasureWindow!=NULL){
			Parent->LargeMeasureWindow->Parent=NULL;
			delete	Parent->LargeMeasureWindow;
			Parent->LargeMeasureWindow=NULL;
		}
		if(Parent->LargeColorDifferenceWindow!=NULL){
			Parent->LargeColorDifferenceWindow->Parent=NULL;
			delete	Parent->LargeColorDifferenceWindow;
			Parent->LargeColorDifferenceWindow=NULL;
		}
		if(RepresentativePoint->LibType==DefLibTypeMeasureLineMove){
			Parent->LargeMeasureWindow=new LargeMeasureWindowForm(this);
			Parent->LargeMeasureWindow->Initial();
			Parent->LargeMeasureWindow->show();
		}
		else
		if(RepresentativePoint->LibType==DefLibTypeColorDifference){
			Parent->LargeColorDifferenceWindow=new LargeColorDifferenceForm(this);
			Parent->LargeColorDifferenceWindow->Initial();
			Parent->LargeColorDifferenceWindow->show();
		}
		else{
			Parent->LargeWindow=new LargeWindowForm(this);
			Parent->LargeWindow->show();
		}
	}
}
void	ThumbnailPanel::SlotShowDetail()
{
	if(Visible==true){
		Parent->DetailFromThumbnail(this);
	}
}

void	ThumbnailPanel::SendLearning(int LearningMenuID, bool AllItems)
{
	Parent->SendLearning(ImagePoint ,RepresentativePoint
						,Phase ,RPage->Page
						,LearningMenuID, AllItems);
}

//===========================================================================
ThumbnailColumHeaderPanel::ThumbnailColumHeaderPanel(InspectionList *L,IntegrationStackMultiNGThumbnailForm *p ,EachMaster *m,int phase,NGPointInPage *page,IntegNGImage *ImagePoint)
:ThumbnailPanel(L,p,m,phase,page,ImagePoint)
{
}

ThumbnailColumHeaderPanel::~ThumbnailColumHeaderPanel(void)
{
}

void	ThumbnailColumHeaderPanel::MakeImage(void)
{
	Messages.append(Result->InspectionTime.toString("hh:mm:ss")
					+QString(/**/" (")
					+QString::number(Result->ID)
					+QString(/**/")"));
}
int	ThumbnailColumHeaderPanel::Compare(ThumbnailPanel &src)
{
	return -99999999;
}
void	ThumbnailColumHeaderPanel::SendLearning(int LearningMenuID, bool AllItems)
{
}
void ThumbnailColumHeaderPanel::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);
	
	if(Parent->ShowInformation==true){
		{
			int	H=Parent->ThumbnailHeight;
			H-=(MessageHeight+2)*MessageRowCount;
			Pnt.setBrush(Qt::black);
			Pnt.setPen(Qt::black);
			Pnt.drawRect(0,H,width(),(MessageHeight+2)*MessageRowCount);
		}
		{
			int	H=Parent->ThumbnailHeight;
			H-=(MessageHeight+2)*MessageRowCount;
			Pnt.setBrush(Qt::white);
			Pnt.setPen(Qt::white);
			int	Mergin=Parent->ThumbnailMergin;
			int	CMessageRow=Messages.count();
			for(int row=0;row<CMessageRow;row++){
				Pnt.drawText(Mergin,H+MessageHeight+MessageHeight*row,Messages[row]);
			}
		}
	}
}
void ThumbnailColumHeaderPanel::mousePressEvent ( QMouseEvent * event )
{
}
void ThumbnailColumHeaderPanel::mouseDoubleClickEvent ( QMouseEvent * event )
{
}
//===========================================================================
NGLineList::NGLineList(IntegrationStackMultiNGThumbnailForm *p)
	:Parent(p)
{
}
NGLineList::~NGLineList(void)
{
}
int	NGLineList::Compare(NGLineList &src)
{
	return -(InspectionID-src.InspectionID);
}

//===========================================================================

IntegrationStackMultiNGThumbnailForm::IntegrationStackMultiNGThumbnailForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationStackMultiNGThumbnailForm)
{
    ui->setupUi(this);

	ThumbnailWidth		=200;
	ThumbnailHeight		=200;
	ThumbnailMergin		=5;
	CurrentIndex		=0;
	CurrentPanelNo		=0;
	ShowInformation		=true;
	ShowInformationTime	=true;
	ShowInformationNumber=true;
	ZoomRate			=0.20;
	MaxXCount			=10;
	MaxYCount			=1000;
	ScrollerWidth		=32;
	LargeWindow			=NULL;
	LargeMeasureWindow	=NULL;
	LargeColorDifferenceWindow	=NULL;
	LastPressedTime		=0;
	EnableUpdate		=true;

	ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	ui->scrollArea->setVerticalScrollBarPolicy	(Qt::ScrollBarAlwaysOn);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	connect(ui->scrollArea->horizontalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(SlotScrollerChanged(int)));

}

IntegrationStackMultiNGThumbnailForm::~IntegrationStackMultiNGThumbnailForm()
{
    delete ui;
}
void	IntegrationStackMultiNGThumbnailForm::Prepare(void)
{
	QWidget	*w=GetParentWidget();
	w->setGeometry(0,0,MaxXCount*ThumbnailWidth,MaxYCount*ThumbnailHeight);
	w->setMinimumSize(MaxXCount*ThumbnailWidth,MaxYCount*ThumbnailHeight);	
	
	QString	s=QString(/**/"QScrollBar:vertical { width: ")
		+QString::number(ScrollerWidth)
		+QString(/**/"px;} ")
		+QString(/**/"QScrollBar:horizontal { height: ")
		+QString::number(ScrollerWidth)
		+QString(/**/"px;}");
	ui->scrollArea->setStyleSheet(s);

	FlipTimer.setInterval(400);
	FlipTimer.setSingleShot(false);
	connect(&FlipTimer,SIGNAL(timeout()),this,SLOT(SlotFlipTimer()));
	FlipTimer.start();
}

void	IntegrationStackMultiNGThumbnailForm::ResizeAction()
{
	//ui->tableWidget->setGeometry(0,0,width(),height());
	ui->scrollArea->setGeometry(0,0,width(),height());

	//IntegrationBase	*IBase=GetLayersBase()->GetIntegrationBasePointer();
	//int	N	=IBase->GetIntegrationSlaveCount();
	//QStringList	TitleNames;
	//TitleNames.append(/**/"ID");
	//for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
	//	EachMaster	*m=IBase->GetMaster(SlaveNo);
	//	TitleNames.append(m->GetMachineName());
	//}
	//ui->tableWidget->setColumnCount(N+1);

	//::SetColumnWidthInTable(ui->tableWidget ,0,15);
	//::SetColumnWidthInTable(ui->tableWidget ,1,80);

	//for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
	//	::SetColumnWidthInTable(ui->tableWidget ,SlaveNo+1, 80/N);
	//}

	//ui->tableWidget->setHorizontalHeaderLabels(TitleNames);
}
QWidget	*IntegrationStackMultiNGThumbnailForm::GetParentWidget(void)
{
	QWidget	*w=ui->scrollArea->widget();
	return w;
}

void	IntegrationStackMultiNGThumbnailForm::StartLot(void)
{
	AddNGImagesAll();
}
static	int	IntervalToKeepPosition=5000;

void	IntegrationStackMultiNGThumbnailForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	if(CmdChangeLotIDVar!=NULL){
		AddNGImagesAll();
		return;
	}
	CmdChangeNewLotID	*CmdChangeNewLotIDVar=dynamic_cast<CmdChangeNewLotID *>(v);
	if(CmdChangeNewLotIDVar!=NULL){
		NGLineListPack.RemoveAll();
		return;
	}
	CmdAppendResult	*CmdAppendResultVar=dynamic_cast<CmdAppendResult *>(v);
	if(CmdAppendResultVar!=NULL){
		if(EnableUpdate==true){
			if(AddNGImagesAll(CmdAppendResultVar->SlaveNo)==true){
				if((::GetComputerMiliSec()-LastPressedTime)>IntervalToKeepPosition){
					NGLineList *a=NGLineListPack.GetFirst();
					if(a!=NULL){
						CurrentIndex	=0;
						CurrentPanelNo	=0;
					}
					BroadcastNGPoint();
				}
			}
		}
		return;
	}
	CmdSelectResult	*CmdSelectResultVar=dynamic_cast<CmdSelectResult *>(v);
	if(CmdSelectResultVar!=NULL){

		//for(ThumbnailPanel *a=Panels.GetFirst();a!=NULL;a=a->GetNext()){
		//	if(a->Result->ID==CmdSelectResultVar->ResultID){
		//		CurrentIndex=a->Index;
		//		SetToShowPanel(CurrentIndex);
		//		RepaintPanel();
		//		BroadcastNGPoint();
		//		break;
		//	}
		//}
		return;
	}
	CmdClearMasterData	*CmdClearMasterDataVar=dynamic_cast<CmdClearMasterData *>(v);
	if(CmdClearMasterDataVar!=NULL){
		NGLineListPack.RemoveAll();
		return;
	}
	//CmdSelectNGLine	*CmdSelectNGLineVar=dynamic_cast<CmdSelectNGLine *>(v);
	//if(CmdSelectNGLineVar!=NULL){
	//	for(ThumbnailPanel *a=Panels.GetFirst();a!=NULL;a=a->GetNext()){
	//		if(a->ImagePoint==CmdSelectNGLineVar->NG){
	//			CurrentIndex=a->Index;
	//			SetToShowPanel(CurrentIndex);
	//			RepaintPanel();
	//			BroadcastNGPoint();
	//			break;
	//		}
	//	}
	//	return;
	//}
	LoadMasterSpecifiedBroadcaster	*CmdLoadedMasterDataVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(CmdLoadedMasterDataVar!=NULL){
		NGLineListPack.RemoveAll();
		return;
	}
}

void	IntegrationStackMultiNGThumbnailForm::SetToShowPanel(int Index ,int PanelNo)
{
	int	x1=ui->scrollArea->horizontalScrollBar()->value();
	int	y1=ui->scrollArea->verticalScrollBar()->value();

	ThumbnailPanel	*p=GetPanel(Index,PanelNo);
	if(p!=NULL){
		while((ui->scrollArea->horizontalScrollBar()->value()+ui->scrollArea->horizontalScrollBar()->pageStep())<p->geometry().right()){
			x1+=ui->scrollArea->horizontalScrollBar()->pageStep()/2;
			//ui->scrollArea->scroll(x1,y1);
			ui->scrollArea->horizontalScrollBar()->setValue(x1);
		}
		while(p->geometry().left()<ui->scrollArea->horizontalScrollBar()->value()){
			x1-=ui->scrollArea->horizontalScrollBar()->pageStep()/2;
			//ui->scrollArea->scroll(x1,y1);
			ui->scrollArea->horizontalScrollBar()->setValue(x1);
		}
		while((ui->scrollArea->verticalScrollBar()->value()+ui->scrollArea->verticalScrollBar()->pageStep())<p->geometry().bottom()){
			y1+=ui->scrollArea->verticalScrollBar()->pageStep()/2;
			//ui->scrollArea->scroll(x1,y1);
			ui->scrollArea->verticalScrollBar()->setValue(y1);
		}
		while(p->geometry().top()<ui->scrollArea->verticalScrollBar()->value()){
			y1-=ui->scrollArea->verticalScrollBar()->pageStep()/2;
			//ui->scrollArea->scroll(x1,y1);
			ui->scrollArea->verticalScrollBar()->setValue(y1);
		}
	}
}
void	IntegrationStackMultiNGThumbnailForm::SlotScrollerChanged(int value)
{
	BroadcastNGPoint();
}
void	IntegrationStackMultiNGThumbnailForm::BroadcastNGPoint(void)
{
	ThumbnailPanel	*p=GetPanel(CurrentIndex,CurrentPanelNo);
	if(p!=NULL){
		CmdShowNGPoint	NGCmd;
		NGCmd.Master	=p->Master;
		NGCmd.NG		=p->RepresentativePoint;
		NGCmd.NGImage	=p->ImagePoint;
		NGCmd.Result	=p->Result;
		BroadcastSpecifiedDirectly(&NGCmd);
	}
}
ThumbnailPanel	*IntegrationStackMultiNGThumbnailForm::GetPanel(int index ,int PanelNo)
{
	NGLineList	*a=NGLineListPack[index];
	if(a!=NULL){
		ThumbnailPanel	*w=a->Panels[PanelNo+1];
		return w;
	}
	return NULL;
}
bool	IntegrationStackMultiNGThumbnailForm::ExistsInPanel(InspectionList *L)
{
	for(NGLineList *a=NGLineListPack.GetFirst();a!=NULL;a=a->GetNext()){
		for(ThumbnailPanel	*w=a->Panels.GetFirst();w!=NULL;w=w->GetNext()){
			if(w->Result==L){
				return true;
			}
		}
	}
	return false;
}

void	IntegrationStackMultiNGThumbnailForm::AddNGImagesAll(void)
{
	NGLineListPack.RemoveAll();
	int	MaxPanelID=-1;
	int	MaxID=0;

	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		InspectionList *L=NULL;
		for(L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext()){
			MaxID=max(MaxID,L->ID);
		}
	}
	/*
	int	N=MaxXCount*MaxYCount;
	for(int ID=MaxPanelID;ID<=MaxID;ID++){
		if(SlaveNo<0 && MachineID>=0){
			EachMaster *Pointer[10];
			int	MCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
			for(int i=0;i<MCount;i++){
				EachMaster *m=Pointer[i];

				InspectionList *L=NULL;
				for(L=m->CurrentInspection.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->ID==ID){
						break;
					}
				}
				if(L!=NULL){
					for(ThumbnailPanel *p=Panels.GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Result!=NULL){
							if(p->Master==m && p->Result==L){
								goto	ExistPanel3;
							}
						}
					}
					NPListPack<IntegNGImage> NGImages[100000];
					for(NGPointInAllPage *RPhase=L->NGPointAllPhases.GetFirst();RPhase!=NULL;RPhase=RPhase->GetNext()){
						for(NGPointInPage *RPage=RPhase->NPListPack<NGPointInPage>::GetFirst();RPage!=NULL;RPage=RPage->GetNext()){
							if(RPage->ImageFileName.isEmpty()==false){
								LoadNGImageFile(RPage->ImageFileName,NGImages,1000);
							}
							if(RPage->NPListPack<NGPoint>::GetCount()!=0){
								IntegNGImage	*G;
								while((G=NGImages[RPhase->Phase].GetFirst())!=NULL){
									NGImages[RPhase->Phase].RemoveList(G);
									RPage->NGImages.AppendList(G);
								}
								RPage->UncompressImages();
								for(IntegNGImage *Np=RPage->NGImages.GetFirst();Np!=NULL;Np=Np->GetNext()){
									ThumbnailPanel	*P=new ThumbnailPanel(L,this,L->GetMaster(),RPhase->Phase,RPage,Np);
									P->MakeImage();
									Panels.InsertTop(P);
									if(N<Panels.GetCount()){
										goto	NextP;
									}
								}
							}
						}
					}
				}
			}
ExistPanel3:;
		}
		else
		if(SlaveNo<0){
			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				InspectionList *L=NULL;
				for(L=m->CurrentInspection.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->ID==ID){
						break;
					}
				}
				if(L!=NULL){
					for(ThumbnailPanel *p=Panels.GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Result!=NULL){
							if(p->Master==m && p->Result==L){
								goto	ExistPanel;
							}
						}
					}
					NPListPack<IntegNGImage> NGImages[100000];
					for(NGPointInAllPage *RPhase=L->NGPointAllPhases.GetFirst();RPhase!=NULL;RPhase=RPhase->GetNext()){
						for(NGPointInPage *RPage=RPhase->NPListPack<NGPointInPage>::GetFirst();RPage!=NULL;RPage=RPage->GetNext()){
							if(RPage->ImageFileName.isEmpty()==false){
								LoadNGImageFile(RPage->ImageFileName,NGImages,1000);
							}
							if(RPage->NPListPack<NGPoint>::GetCount()!=0){
								IntegNGImage	*G;
								while((G=NGImages[RPhase->Phase].GetFirst())!=NULL){
									NGImages[RPhase->Phase].RemoveList(G);
									RPage->NGImages.AppendList(G);
								}
								RPage->UncompressImages();
								for(IntegNGImage *Np=RPage->NGImages.GetFirst();Np!=NULL;Np=Np->GetNext()){
									ThumbnailPanel	*P=new ThumbnailPanel(L,this,L->GetMaster(),RPhase->Phase,RPage,Np);
									P->MakeImage();
									Panels.InsertTop(P);
									if(N<Panels.GetCount()){
										goto	NextP;
									}
								}
							}
						}
					}
				}
				ExistPanel:;
			}
		}
		else{
			EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas[SlaveNo];
			if(m!=0){
				InspectionList *L=NULL;
				for(L=m->CurrentInspection.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->ID==ID){
						break;
					}
				}
				if(L!=NULL){
					for(ThumbnailPanel *p=Panels.GetFirst();p!=NULL;p=p->GetNext()){
						if(p->Result!=NULL){
							if(p->Master==m && p->Result==L){
								goto	ExistPanel2;
							}
						}
					}
					NPListPack<IntegNGImage> NGImages[100000];
					for(NGPointInAllPage *RPhase=L->NGPointAllPhases.GetFirst();RPhase!=NULL;RPhase=RPhase->GetNext()){
						for(NGPointInPage *RPage=RPhase->NPListPack<NGPointInPage>::GetFirst();RPage!=NULL;RPage=RPage->GetNext()){
							if(RPage->ImageFileName.isEmpty()==false){
								LoadNGImageFile(RPage->ImageFileName,NGImages,1000);
							}
							if(RPage->NPListPack<NGPoint>::GetCount()!=0){
								IntegNGImage	*G;
								while((G=NGImages[RPhase->Phase].GetFirst())!=NULL){
									NGImages[RPhase->Phase].RemoveList(G);
									RPage->NGImages.AppendList(G);
								}
								RPage->UncompressImages();
								for(IntegNGImage *Np=RPage->NGImages.GetFirst();Np!=NULL;Np=Np->GetNext()){
									ThumbnailPanel	*P=new ThumbnailPanel(L,this,L->GetMaster(),RPhase->Phase,RPage,Np);
									P->MakeImage();
									Panels.InsertTop(P);
									if(N<Panels.GetCount()){
										goto	NextP;
									}
								}
							}
						}
					}
				}
ExistPanel2:;
			}
		}	
	}
	NextP:;
	Panels.Sort();
	ArrangePanelPosition();
	RepaintPanel();
	*/
}

bool	IntegrationStackMultiNGThumbnailForm::AddNGImagesAll(int SlaveNo)
{
	int	MaxID=-1;
	bool	AddedPanel=false;
	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		for(NGLineList *e=NGLineListPack.GetFirst();e!=NULL;e=e->GetNext()){
			for(ThumbnailPanel *p=e->Panels.GetFirst();p!=NULL;p=p->GetNext()){
				if(p->Master==m && p->Result!=NULL){
					MaxID=max(MaxID,p->Result->ID);
				}
			}
		}
		for(InspectionList *L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext()){
			if(L->ID>MaxID){
				NPListPack<IntegNGImage> NGImages[1000];
				NGLineList	*E=NULL;
				for(E=NGLineListPack.GetFirst();E!=NULL;E=E->GetNext()){
					if(E->InspectionID==L->ID){
						break;
					}
				}
				bool	CreatedL=false;
				if(E==NULL){
					E=new NGLineList(this);
					E->InspectionID=L->ID;
					CreatedL=true;
					
				}

				for(NGPointInAllPage *RPhase=L->NGPointAllPhases.GetFirst();RPhase!=NULL;RPhase=RPhase->GetNext()){
					for(NGPointInPage *RPage=RPhase->NPListPack<NGPointInPage>::GetFirst();RPage!=NULL;RPage=RPage->GetNext()){
						if(RPage->ImageFileName.isEmpty()==false){
							LoadNGImageFile(RPage->ImageFileName,NGImages,1000);
						}
						if(RPage->NPListPack<NGPoint>::GetCount()!=0){
							IntegNGImage	*G;
							while((G=NGImages[RPhase->Phase].GetFirst())!=NULL){
								NGImages[RPhase->Phase].RemoveList(G);
								RPage->NGImages.AppendList(G);
							}
							RPage->UncompressImages();
							for(IntegNGImage *Np=RPage->NGImages.GetFirst();Np!=NULL;Np=Np->GetNext()){
								//if(N<E->Panels.GetCount()){
								//	ThumbnailPanel	*p=Panels.GetLast();
								//	Panels.RemoveList(p);
								//	delete	p;
								//}
								ThumbnailPanel	*P=new ThumbnailPanel(L,this,L->GetMaster(),RPhase->Phase,RPage,Np);
								P->MakeImage();
								E->Panels.InsertTop(P);
								AddedPanel=true;
							}
						}
					}
				}
				if(CreatedL==true){
					if(E->Panels.GetCount()==0){
						delete	E;
					}
					else{
						ThumbnailColumHeaderPanel	*t=new ThumbnailColumHeaderPanel(L,this,NULL,0,NULL,NULL);
						t->MakeImage();
						E->Panels.InsertList(0,t);
						NGLineListPack.AppendList(E);
					}
				}
			}
		}
	}
	if(AddedPanel==true){
		NGLineListPack.Sort();
		ArrangePanelPosition();
		RepaintPanel();
		return true;
	}
	return false;
}

void	IntegrationStackMultiNGThumbnailForm::ArrangePanelPosition(void)
{
	int	MaxRow=0;
	int	MaxCol=0;

	int	Row=0;
	for(NGLineList *a=NGLineListPack.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		int	Column=0;
		for(ThumbnailPanel	*p=a->Panels.GetFirst();p!=NULL;p=p->GetNext(),Column++){
			p->Row	 =Row;
			p->Column=Column;
			MaxRow=max(MaxRow,p->Row);
			MaxCol=max(MaxCol,p->Column);
			p->setGeometry(p->Column*ThumbnailWidth ,p->Row*ThumbnailHeight,ThumbnailWidth,ThumbnailHeight);
			p->show();
		}
	}

	QWidget	*w=GetParentWidget();
	w->setGeometry(0,0,(MaxCol+1)*ThumbnailWidth,(MaxRow+1)*ThumbnailHeight);
	w->setMinimumSize((MaxCol+1)*ThumbnailWidth,(MaxRow+1)*ThumbnailHeight);	
}
void	IntegrationStackMultiNGThumbnailForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqNGPositionInPanel	*CmdReqNGPositionInPanelVar=dynamic_cast<CmdReqNGPositionInPanel *>(packet);
	if(CmdReqNGPositionInPanelVar!=NULL){
		ThumbnailPanel	*p=GetPanel(CurrentIndex,CurrentPanelNo);
		if(p!=NULL && CmdReqNGPositionInPanelVar->Master->GetMasterCode()==p->Master->GetMasterCode()){
			int	x1=p->geometry().left();
			int	y1=p->geometry().top();
			int	x2=p->geometry().right();
			int	y2=p->geometry().bottom();
			QWidget	*w=GetParentWidget();
			QPoint	P1=w->mapToGlobal(QPoint(x1,y1));
			QPoint	P2=w->mapToGlobal(QPoint(x2,y2));
			CmdReqNGPositionInPanelVar->WorldX1	=P1.x();
			CmdReqNGPositionInPanelVar->WorldY1	=P1.y();
			CmdReqNGPositionInPanelVar->WorldX2	=P2.x();
			CmdReqNGPositionInPanelVar->WorldY2	=P2.y();
			CmdReqNGPositionInPanelVar->Found=true;
		}
		else{
			CmdReqNGPositionInPanelVar->Found=false;
		}
		return;
	}
	CmdSetInvisibleAll	*CmdSetInvisibleAllVar=dynamic_cast<CmdSetInvisibleAll *>(packet);
	if(CmdSetInvisibleAllVar!=NULL){
		SetInvisibleAll();
		return;
	}
	CmdSetUpdateMode	*CmdSetUpdateModeVar=dynamic_cast<CmdSetUpdateMode *>(packet);
	if(CmdSetUpdateModeVar!=NULL){
		EnableUpdate=CmdSetUpdateModeVar->StartUpdate;
		if(CmdSetUpdateModeVar->StartUpdate==true){
			for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
				AddNGImagesAll(m->GetIntegrationSlaveNo());
			}
		}
		return;
	}
}
void	IntegrationStackMultiNGThumbnailForm::RepaintPanel(void)
{
	for(NGLineList *a=NGLineListPack.GetFirst();a!=NULL;a=a->GetNext()){
		for(ThumbnailPanel	*w=a->Panels.GetFirst();w!=NULL;w=w->GetNext()){
			w->repaint();
		}
	}
}

void	IntegrationStackMultiNGThumbnailForm::SlotFlipTimer()
{
	for(NGLineList *a=NGLineListPack.GetFirst();a!=NULL;a=a->GetNext()){
		for(ThumbnailPanel	*w=a->Panels.GetFirst();w!=NULL;w=w->GetNext()){
			w->repaint();
		}
	}

}
	
void	IntegrationStackMultiNGThumbnailForm::PressPanel(void)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"History",/**/"");
	if(f!=NULL){
		ThumbnailPanel	*p=GetPanel(CurrentIndex,CurrentPanelNo);
		if(p!=NULL && p->Result!=NULL){
			CmdPressLine	Cmd(GetLayersBase());
			Cmd.MachineID	=p->Master->GetMachineCode();
			Cmd.InspectionID=p->Result->ID;
			f->TransmitDirectly(&Cmd);
		}
	}
}

bool	IntegrationStackMultiNGThumbnailForm::LoadNGImageFile(const QString &FileName,NPListPack<IntegNGImage> NGImages[] ,int PhaseCount)
{
	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(LoadNGImageFile(&File,NGImages, PhaseCount
							,0,0)==false){
			return false;
		}
		int32	ShadowNumb;
		if(::Load(&File,ShadowNumb)==false){
			return false;
		}
		for(int i=0;i<ShadowNumb;i++){
			int		ShadowLevel=0;
			int		ShadowNumber=0;
			if(::Load(&File,ShadowLevel)==false){
				return false;
			}
			if(::Load(&File,ShadowNumber)==false){
				return false;
			}

			if(LoadNGImageFile(&File,NGImages, PhaseCount
								,ShadowLevel,ShadowNumber)==false){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool	IntegrationStackMultiNGThumbnailForm::LoadNGImageFile(QIODevice *f ,NPListPack<IntegNGImage> NGImages[],int PhaseCount
														,int ShadowLevel,int ShadowNumber)
{
	DWORD	Ver;

	LayersBase	*LBase=GetLayersBase()->GetShadowTree(ShadowLevel ,ShadowNumber);

	if(::Load(f,Ver)==false){
		return false;
	}
	int32	PhaseNumb;
	if(::Load(f,PhaseNumb)==false){
		return false;
	}
	for(int phase=0;phase<PhaseNumb;phase++){
		DWORD	PVer;
		if(::Load(f,PVer)==false){
			return false;
		}
		int32	Phase;
		if(::Load(f,Phase)==false){
			return false;
		}
		if(PVer<5){
			int32	N;
			if(::Load(f,N)==false){
				return false;
			}
			for(int i=0;i<N;i++){
				IntegNGImage	*G=new IntegNGImage(ShadowLevel,ShadowNumber);
				if(G->LoadJDT(f)==false)
					return false;
				//if(LBase!=NULL){
				//	LBase->ConvertToTop(G->x1,G->y1);
				//	LBase->ConvertToTop(G->x2,G->y2);
				//}
				if(0<=Phase && Phase<PhaseCount){
					NGImages[Phase].AppendList(G);
				}
				else{
					delete	G;
				}
			}
		}
		else{
			int16	SaveMode;
			if(::Load(f,SaveMode)==false){
				return false;
			}
			int32	N;
			if(::Load(f,N)==false){
				return false;
			}
			for(int i=0;i<N;i++){
				IntegNGImage	*G=new IntegNGImage(ShadowLevel,ShadowNumber);
				if(SaveMode==1){
					if(G->LoadJDT(f)==false)
						return false;
				}
				else
				if(SaveMode==0){
					if(G->LoadRawImage(f)==false)
						return false;
				}
				//if(LBase!=NULL){
				//	LBase->ConvertToTop(G->x1,G->y1);
				//	LBase->ConvertToTop(G->x2,G->y2);
				//}
				if(0<=Phase && Phase<PhaseCount){
					NGImages[Phase].AppendList(G);
				}
				else{
					delete	G;
				}
			}
		}
	}
	return true;
}

class AlgorithmItemDummy : public AlgorithmItemRoot
{
public:
	AlgorithmItemDummy(){}
	~AlgorithmItemDummy(){}

private:
	virtual	LogicDLL			*GetLogicDLL(void)				{	return NULL;	}
	virtual	ResultInspection	*GetResultInspection(void)		{	return NULL;	}
	virtual	int					GetPage(void)					{	return 0;		}
	virtual	AlgorithmItemRoot	*GetAlgorithmItemRoot(void)		{	return NULL;	}
	virtual	LayersBase			*GetLayersBase(void)	const	{	return NULL;	}
	virtual	int					GetDotPerLine(void)				{	return 0;		}
	virtual	int					GetMaxLines(void)				{	return 0;		}
};

void	IntegrationStackMultiNGThumbnailForm::GetInformation(int SlaveNo
															,InspectionList *L,NGPoint *Rp
															,QString &StrLibID ,QString &LibName ,QString &CauseStr)
{
	DetailResultInfoListContainer ItemDetailList;
	if(Rp!=NULL && Rp->LibType!=0){
		if(Rp->LibID>=0){
			StrLibID=QString::number(Rp->LibID);
			LibName=GetLayersBase()->GetIntegrationBasePointer()->GetLibraryName(Rp->LibType ,Rp->LibID);
		}
		if(Rp->ResultType==_ResultDouble){
			CauseStr=QString::number(L->GetMaster()->TransformUnitToPixel(Rp->DoubleCause),'f',2)
					+QString('[')
					+QString::number(Rp->DoubleCause,'f',2)
					+QString(']');
		}
		else{
			if((Rp->PosResult&0xFF)==2){
				CauseStr=QString::number(Rp->Cause[1])
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnit(Rp->Cause[1]),'f',2)
						+QString(/**/"mm]");
			}
			else{
				CauseStr=QString::number(Rp->Cause[0])
						+QString('[')
						+QString::number(L->GetMaster()->TransformPixelToUnitSquare(Rp->Cause[0]),'f',2)
						+QString(/**/"mm2]");
			}
		}
	}
	else if(Rp!=NULL){
		LibName=Rp->Message;
		if(Rp->ResultType==_ResultDouble){
			CauseStr=QString::number(Rp->DoubleCause,'f',2);
		}
	}
}
	
QStringList	IntegrationStackMultiNGThumbnailForm::GetInformation(int SlaveNo
																,InspectionList *L,NGPoint *Rp)
{
	QString StrLibID;
	QString LibName;
	QString CauseStr;
	GetInformation(SlaveNo,L,Rp ,StrLibID ,LibName ,CauseStr);

	DetailResultInfoListContainer ItemDetailList;
	if(Rp!=NULL && Rp->LibType!=0){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(Rp->LibType);
		if(ABase!=NULL){
			QRgb		NGColor;

			ResultPosList	RPos;
			RPos.result		=Rp->PosResult;
			if(Rp->ResultType==_ResultDouble){
				RPos.SetResult(Rp->DoubleCause);
			}
			else
			if(Rp->ResultType==_ResultDWORD){
				RPos.SetResult1(Rp->Cause[0]);
				RPos.SetResult2(Rp->Cause[1]);
			}
			RPos.Px			=Rp->MasterX;
			RPos.Py			=Rp->MasterY;
			RPos.Rx			=Rp->HX;
			RPos.Ry			=Rp->HY;

			ABase->GetDrawResultDetail(NULL ,&RPos ,ItemDetailList);
		}
	}

	QStringList	Ret;
	if(ShowInformationTime==true && ShowInformationNumber==true){
		if(LibName.isEmpty()==false){
			Ret.append(LibName
						+QString(/**/",")
						+CauseStr);
		}
		else{
			Ret.append(CauseStr);
		}
		//Ret.append(L->InspectionTime.toString("hh:mm:ss")
		//			+QString(/**/" (")
		//			+QString::number(L->ID)
		//			+QString(/**/")"));
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			Ret.append(m->GetMachineName());
		}

		if(ItemDetailList.count()>0){
			DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
			Ret.append(L->MessageString+QString(/**/":")+L->GetInfoString());
		}
	}
	else
	if(ShowInformationTime==false && ShowInformationNumber==true){
		Ret.append(LibName
					+QString(/**/",")
					+CauseStr
					+QString(/**/" (")
					+QString::number(L->ID)
					+QString(/**/")"));
		if(ItemDetailList.count()>0){
			DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
			Ret.append(L->MessageString+QString(/**/":")+L->GetInfoString());
		}
	}
	else
	if(ShowInformationTime==true && ShowInformationNumber==false){
		Ret.append(LibName
					+QString(/**/",")
					+CauseStr);

		Ret.append(L->InspectionTime.toString("hh:mm:ss"));
		if(ItemDetailList.count()>0){
			DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
			Ret.append(L->MessageString+QString(/**/":")+L->GetInfoString());
		}
	}
	else{
		Ret.append(LibName
					+QString(/**/",")
					+CauseStr);
		if(ItemDetailList.count()>0){
			DetailResultInfoList	*L=ItemDetailList.NPListPack<DetailResultInfoList>::GetFirst();
			Ret.append(L->MessageString+QString(/**/":")+L->GetInfoString());
		}
	}
	return Ret;
}
void	IntegrationStackMultiNGThumbnailForm::DetailFromThumbnail(ThumbnailPanel *p)
{
	NPListPack<NGPointPointerList> NGList;
	p->ImagePoint->EnumNGPoint(p->RPage ,NGList);
	IntList	ItemIDList;
	for(NGPointPointerList *g=NGList.GetFirst();g!=NULL;g=g->GetNext()){
		ItemIDList.Add(g->NG->UniqueID);
	}
	emit	SignalReqDetail(p->Master ,p->Result, p->CurrentInspection, p->RepresentativePoint
							,p->Phase ,p->RPage->Page,ItemIDList);
}

void	IntegrationStackMultiNGThumbnailForm::SetInvisibleAll(void)
{
	for(NGLineList *a=NGLineListPack.GetFirst();a!=NULL;a=a->GetNext()){
		for(ThumbnailPanel	*w=a->Panels.GetFirst();w!=NULL;w=w->GetNext()){
			w->Visible=false;
		}
	}
	EmitRepaint();
}

void	IntegrationStackMultiNGThumbnailForm::SendLearning(IntegNGImage	*ImagePoint ,NGPoint *RepresentativePoint
													  ,int Phase ,int Page
													  ,int LearningMenuID, bool AllItems)
{
	//if(RepresentativePoint!=NULL){
	//	if(SlaveNo>=0){
	//		IntegrationCmdUpdateThreshold	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	//		RCmd.LibType		=RepresentativePoint->LibType;
	//		RCmd.LibID			=RepresentativePoint->LibID;
	//		RCmd.LearningMenuID	=LearningMenuID	;
	//		RCmd.InspectionID	=RepresentativePoint->UniqueID;
	//		RCmd.Phase			=Phase;
	//		RCmd.Page			=Page;
	//		RCmd.ItemID			=(AllItems==true)?-1:RepresentativePoint->UniqueID;
	//		RCmd.ShadowLevel	=ImagePoint->ShadowLevel;
	//		RCmd.ShadowNumber	=ImagePoint->ShadowNumber;
	//		RCmd.LRes.x1		=ImagePoint->x1;
	//		RCmd.LRes.y1		=ImagePoint->y1;
	//		RCmd.LRes.x2		=ImagePoint->x2;
	//		RCmd.LRes.y2		=ImagePoint->y2;
	//		RCmd.LRes.Image		=ImagePoint->Image;
	//		RCmd.LRes.Cause[0]	=RepresentativePoint->Cause[0];
	//		RCmd.LRes.Cause[1]	=RepresentativePoint->Cause[1];
	//		RCmd.LRes.DoubleCause=RepresentativePoint->DoubleCause;
	//		RCmd.LRes.Hx		=RepresentativePoint->HX;
	//		RCmd.LRes.Hy		=RepresentativePoint->HY;
	//		RCmd.Send(NULL,SlaveNo,0);
	//	}
	//	else
	//	if(SlaveNo<0 && MachineID>=0){
	//		EachMaster *Pointer[10];
	//		int		MasterCount=GetLayersBase()->GetIntegrationBasePointer()->EnumMaster(MachineID,Pointer,10);
	//		for(int m=0;m<MasterCount;m++){				
	//			int	SlaveNo=Pointer[m]->GetIntegrationSlaveNo();
	//			IntegrationCmdUpdateThreshold	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
	//			RCmd.LibType		=RepresentativePoint->LibType;
	//			RCmd.LibID			=RepresentativePoint->LibID;
	//			RCmd.LearningMenuID	=LearningMenuID	;
	//			RCmd.InspectionID	=RepresentativePoint->UniqueID;
	//			RCmd.Phase			=Phase;
	//			RCmd.Page			=Page;
	//			RCmd.ItemID			=(AllItems==true)?-1:RepresentativePoint->UniqueID;
	//			RCmd.ShadowLevel	=ImagePoint->ShadowLevel;
	//			RCmd.ShadowNumber	=ImagePoint->ShadowNumber;
	//			RCmd.LRes.x1		=ImagePoint->x1;
	//			RCmd.LRes.y1		=ImagePoint->y1;
	//			RCmd.LRes.x2		=ImagePoint->x2;
	//			RCmd.LRes.y2		=ImagePoint->y2;
	//			RCmd.LRes.Image		=ImagePoint->Image;
	//			RCmd.LRes.Cause[0]	=RepresentativePoint->Cause[0];
	//			RCmd.LRes.Cause[1]	=RepresentativePoint->Cause[1];
	//			RCmd.LRes.DoubleCause=RepresentativePoint->DoubleCause;
	//			RCmd.LRes.Hx		=RepresentativePoint->HX;
	//			RCmd.LRes.Hy		=RepresentativePoint->HY;
	//			RCmd.Send(NULL,SlaveNo,0);
	//		}
	//	}
	//}
}
//==========================================================================================================
