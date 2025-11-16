#include "IntegrationThumbnailResource.h"
#include "IntegrationThumbnailForm.h"
#include "ui_IntegrationThumbnailForm.h"
#include "IntegrationShowHistoryLoadImageForm.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"

ThumbnailPanel::ThumbnailPanel(int id,IntegrationThumbnailForm *p,EachMaster *m,int phase,int page,IntegBindedNGArea *point)
	:QWidget(p),Parent(p),ID(id)
{
	Master	=m;
	Phase	=phase;
	Page	=page;
	Point	=point;
	Image=NULL;
}
ThumbnailPanel::~ThumbnailPanel(void)
{
	if(Image!=NULL){
		delete	Image;
		Image=NULL;
	}
	if(Point!=NULL){
		delete	Point;
		Point=NULL;
	}
}

const	int	MessageHeight=24;

void	ThumbnailPanel::MakeImage(void)
{
	if(Image!=NULL)
		delete	Image;
	int	W=Parent->ThumbnailWidth;
	int	H=Parent->ThumbnailHeight;
	int	Mergin=Parent->ThumbnailMergin;
	Image=new QImage(W,H,QImage::Format_ARGB32);

	if(Parent->ShowInformation==true){
		H-=MessageHeight;
	}
	int	Cx,Cy;
	Point->GetCenter(Cx,Cy);
	int	Phase	=Point->Parent->GetPhase();
	int	Page	=Point->Parent->GetPage();

	double	Z=1.0/Parent->ZoomRate;
	if(Parent->GetLayerNumb(Page)>=3){
		ImageBuffer	*ImgR=Master->GetTargetImage(Phase,Page,0);
		ImageBuffer	*ImgG=Master->GetTargetImage(Phase,Page,1);
		ImageBuffer	*ImgB=Master->GetTargetImage(Phase,Page,2);
		for(int y=Mergin;y<H-Mergin;y++){
			int	Y=Cy+(y-H/2)*Z;
			QRgb	*d=(QRgb *)Image->scanLine(y);
			if(Y<0 || Master->GetMaxLines(Phase,Page)<=Y){
				for(int x=Mergin;x<W-Mergin;x++,d++){
					*d=qRgba(0,0,0,255);
				}
				continue;
			}
			BYTE	*sR=ImgR->GetY(Y);
			BYTE	*sG=ImgG->GetY(Y);
			BYTE	*sB=ImgB->GetY(Y);
			d+=Mergin;
			for(int x=Mergin;x<W-Mergin;x++,d++){
				int	X=Cx+(x-W/2)*Z;
				if(X<0 || Master->GetDotPerLine(Phase,Page)<=X){
					*d=qRgba(0,0,0,255);
					continue;
				}
				*d=qRgba(sR[X],sG[X],sB[X],255);
			}
		}
	}
	if(Parent->GetLayerNumb(Page)==1){
		ImageBuffer	*ImgR=Master->GetTargetImage(Phase,Page,0);
		for(int y=Mergin;y<H-Mergin;y++){
			int	Y=Cy+(y-H/2)*Z;
			QRgb	*d=(QRgb *)Image->scanLine(y);
			if(Y<0 || Master->GetMaxLines(Phase,Page)<=Y){
				for(int x=Mergin;x<W-Mergin;x++,d++){
					*d=qRgba(0,0,0,255);
				}
				continue;
			}
			BYTE	*sR=ImgR->GetY(Y);
			d+=Mergin;
			for(int x=Mergin;x<W-Mergin;x++,d++){
				int	X=Cx+(x-W/2)*Z;
				if(X<0 || Master->GetDotPerLine(Phase,Page)<=X){
					*d=qRgba(0,0,0,255);
					continue;
				}
				*d=qRgba(sR[X],sR[X],sR[X],255);
			}
		}
	}
	if(Parent->ShowInformation==true){
		QPainter	Pnt(Image);
		Pnt.setBrush(Qt::black);
		Pnt.setPen(Qt::black);
		Pnt.drawRect(0,H,W-1,MessageHeight);

		Pnt.setBrush(Qt::white);
		Pnt.setPen(Qt::white);
		QString	Msg=Parent->GetInformation(Point->NGPointerList.GetFirst()->NG);
		Pnt.drawText(0,H+MessageHeight/2,Msg);
	}
}


void ThumbnailPanel::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	Pnt.drawImage(0,0,*Image);

	if(ID==Parent->CurrentIndex){
		int	W=Parent->ThumbnailWidth;
		int	H=Parent->ThumbnailHeight;
		int	Mergin=Parent->ThumbnailMergin;
		QColor	Col=Qt::red;

		QPen	Pen(Col);
		Pen.setWidth(3);
		Pnt.setPen(Pen);

		if(Parent->ShowInformation==true){
			Pnt.drawLine(Mergin		,Mergin						,W-1-Mergin	,Mergin						);
			Pnt.drawLine(W-1-Mergin	,Mergin						,W-1-Mergin	,H-1-Mergin-MessageHeight	);
			Pnt.drawLine(W-1-Mergin	,H-1-Mergin-MessageHeight	,Mergin		,H-1-Mergin-MessageHeight	);
			Pnt.drawLine(Mergin		,H-1-Mergin-MessageHeight	,Mergin		,Mergin						);
		}
		else{
			Pnt.drawLine(Mergin		,Mergin		,W-1-Mergin	,Mergin		);
			Pnt.drawLine(W-1-Mergin	,Mergin		,W-1-Mergin	,H-1-Mergin	);
			Pnt.drawLine(W-1-Mergin	,H-1-Mergin	,Mergin		,H-1-Mergin	);
			Pnt.drawLine(Mergin		,H-1-Mergin	,Mergin		,Mergin		);
		}
	}
}

IntegrationThumbnailForm::IntegrationThumbnailForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationThumbnailForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ShownMachineCode	=0;
	ShownPhase			=-1;
	ShowMaster			=true;
	ThumbnailWidth		=200;
	ThumbnailHeight		=200;
	ThumbnailMergin		=5;
	CurrentInspection	=NULL;
	CurrentIndex		=0;
	ShowInformation		=true;
	ZoomRate			=0.20;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationThumbnailForm::~IntegrationThumbnailForm()
{
    delete ui;
}

void	IntegrationThumbnailForm::Prepare(void)
{
	if(GetEditMode()==false){
		grabKeyboard();
	}
}
void	IntegrationThumbnailForm::ResizeAction()
{
}
void	IntegrationThumbnailForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdLoadedImage	*CmdLoadedImageVar=dynamic_cast<CmdLoadedImage *>(v);
	if(CmdLoadedImageVar!=NULL){
		CurrentInspection	=CmdLoadedImageVar->Pointer;
		ShownMachineCode	=CmdLoadedImageVar->Pointer->GetMaster()->GetMachineCode();
		CurrentIndex		=0;
		ShowNGImages();

		BroadcastNGPoint();
		BroadcastRepaintAll();
		return;
	}
}
void	IntegrationThumbnailForm::StartLot	(void)
{
	CurrentInspection=NULL;
	Panels.RemoveAll();
	CurrentIndex=0;
}
void	IntegrationThumbnailForm::BroadcastNGPoint(void)
{
	ThumbnailPanel	*p=GetPanel(CurrentIndex);
	if(p!=NULL){
		CmdShowNGPoint	NGCmd;
		NGCmd.NG=p->Point->NGPointerList.GetFirst()->NG;
		BroadcastSpecifiedDirectly(&NGCmd);
	}
}
void	IntegrationThumbnailForm::RepaintPanel(void)
{
	for(ThumbnailPanel *a=Panels.GetFirst();a!=NULL;a=a->GetNext()){
		a->repaint();
	}
}
void	IntegrationThumbnailForm::ShowNGImages(void)
{
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(ShownMachineCode);
	if(m==NULL)
		return;
	if(CurrentInspection==NULL)
		return;
	Panels.RemoveAll();

	if(ShownPhase>=0)
		ShowNGImages(ShownPhase,m);
	else{
		for(int phase=0;phase<m->GetPhaseNumb();phase++){
			ShowNGImages(phase,m);
		}
	}
}

void	IntegrationThumbnailForm::ShowNGImages(int _ShownPhase ,EachMaster *m)
{
	NGPointInAllPage	*Ph=CurrentInspection->NGPointAllPhases.GetItem(_ShownPhase);
	if(Ph==NULL)
		return;

	int	XPos=0;
	int	YPos=0;
	int	Row=0;
	int	Column=0;
	int	ID=0;
	for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
		NPListPack<IntegBindedNGArea> NGAreaPack;
		Pg->BindNGPoint(ThumbnailWidth*0.8/ZoomRate,ThumbnailHeight*0.8/ZoomRate,NGAreaPack);

		IntegBindedNGArea *n;
		while((n=NGAreaPack.GetFirst())!=NULL){
			NGAreaPack.RemoveList(n);
			ThumbnailPanel	*Thumb=new ThumbnailPanel(ID,this,m,Ph->Phase,Pg->Page,n);
			ID++;
			Thumb->MakeImage();
			Thumb->Row		=Row;
			Thumb->Column	=Column;
			Thumb->move(XPos,YPos);
			XPos+=ThumbnailWidth;
			Column++;
			if((XPos+ThumbnailWidth)>width()){
				XPos=0;
				YPos+=ThumbnailHeight;
				Column=0;
				Row++;
			}
			Thumb->resize(ThumbnailWidth,ThumbnailHeight);
			Thumb->show();
			Panels.AppendList(Thumb);
		}
	}
}

ThumbnailPanel	*IntegrationThumbnailForm::GetPanel(int index)
{
	for(ThumbnailPanel *a=Panels.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->ID==index){
			return a;
		}
	}
	return NULL;
}
ThumbnailPanel	*IntegrationThumbnailForm::GetPanel(int row ,int column)
{
	for(ThumbnailPanel *a=Panels.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Row==row && a->Column==column){
			return a;
		}
	}
	return NULL;
}
ThumbnailPanel	*IntegrationThumbnailForm::GetPanelRight(int row)
{
	int	Comumn=0;
	ThumbnailPanel *Left=NULL;
	for(ThumbnailPanel *a=Panels.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Row==row && a->Column>Comumn){
			Comumn=a->Column;
			Left=a;
		}
	}
	return Left;
}
void	IntegrationThumbnailForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqNGPositionInPanel	*CmdReqNGPositionInPanelVar=dynamic_cast<CmdReqNGPositionInPanel *>(packet);
	if(CmdReqNGPositionInPanelVar!=NULL){
		ThumbnailPanel	*p=GetPanel(CurrentIndex);
		if(p!=NULL){
			QPoint	Local1(p->geometry().left(),p->geometry().top());
			QPoint	Local2(p->geometry().right(),p->geometry().bottom());
			QPoint	G1=mapToGlobal(Local1);
			QPoint	G2=mapToGlobal(Local2);
			CmdReqNGPositionInPanelVar->WorldX1	=G1.x();
			CmdReqNGPositionInPanelVar->WorldY1	=G1.y();
			CmdReqNGPositionInPanelVar->WorldX2	=G2.x();
			CmdReqNGPositionInPanelVar->WorldY2	=G2.y();
			CmdReqNGPositionInPanelVar->Found=true;
		}
		return;
	}
}

void IntegrationThumbnailForm::keyPressEvent ( QKeyEvent * event )
{
	int	key=event->key();
	if(key==Qt::Key_Up){
		ThumbnailPanel	*p=GetPanel(CurrentIndex);
		if(p!=NULL){
			int	row=p->Row;
			int	col=p->Column;
			row--;
			ThumbnailPanel	*q=GetPanel(row,col);
			if(q!=NULL){
				CurrentIndex=q->ID;
				BroadcastNGPoint();
				RepaintPanel();
			}
		}
	}
	else if(key==Qt::Key_Down){
		ThumbnailPanel	*p=GetPanel(CurrentIndex);
		if(p!=NULL){
			int	row=p->Row;
			int	col=p->Column;
			row++;
			ThumbnailPanel	*q=GetPanel(row,col);
			if(q!=NULL){
				CurrentIndex=q->ID;
				BroadcastNGPoint();
				RepaintPanel();
			}
		}
	}
	else if(key==Qt::Key_Left){
		ThumbnailPanel	*p=GetPanel(CurrentIndex);
		if(p!=NULL){
			int	row=p->Row;
			int	col=p->Column;
			col--;
			ThumbnailPanel	*q=GetPanel(row,col);
			if(q!=NULL){
				CurrentIndex=q->ID;
				BroadcastNGPoint();
				RepaintPanel();
			}
			else{
				row--;
				ThumbnailPanel	*r=GetPanelRight(row);
				if(r!=NULL){
					CurrentIndex=r->ID;
					BroadcastNGPoint();
					RepaintPanel();
				}
			}
		}
	}
	else if(key==Qt::Key_Right){
		ThumbnailPanel	*p=GetPanel(CurrentIndex);
		if(p!=NULL){
			int	row=p->Row;
			int	col=p->Column;
			col++;
			ThumbnailPanel	*q=GetPanel(row,col);
			if(q!=NULL){
				CurrentIndex=q->ID;
				BroadcastNGPoint();
				RepaintPanel();
			}
			else{
				row++;
				col=0;
				ThumbnailPanel	*r=GetPanel(row,col);
				if(r!=NULL){
					CurrentIndex=r->ID;
					BroadcastNGPoint();
					RepaintPanel();
				}
			}
		}
	}
}
QString	IntegrationThumbnailForm::GetInformation(NGPoint *p)
{
	QString	LibName=GetLayersBase()->GetIntegrationBasePointer()->GetLibraryName(p->LibType ,p->LibID);
	return LibName
			+QString(/**/",")
			+QString::number(p->Cause[0]);
}
