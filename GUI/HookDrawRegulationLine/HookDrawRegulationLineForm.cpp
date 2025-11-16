#include "HookDrawRegulationLineForm.h"
#include "ui_HookDrawRegulationLineForm.h"
#include "HookDrawRegulationLine.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QColorDialog>

//==========================================================================

CrossButton::CrossButton ( QWidget * parent)
	:QToolButton(parent)
{
}

void	CrossButton::mouseReleaseEvent ( QMouseEvent * e )
{
	if(e->button()==Qt::RightButton){
		emit	SignalRightButton();
	}
	QToolButton::mouseReleaseEvent(e);
}

HookDrawRegulationLineForm::HookDrawRegulationLineForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::HookDrawRegulationLineForm)
{
	ui->setupUi(this);

	for(int i=0;i<sizeof(TargetPanel)/sizeof(TargetPanel[0]);i++){
		TargetPanel[i]=NULL;
	}
	delete	ui->toolButton;

	Mode=0;
	Color	=Qt::yellow;
	LineWidth=1;
	ui->toolButton=new CrossButton(this);
    ui->toolButton->setObjectName(QString::fromUtf8("toolHookDraw"));
    ui->toolButton->setGeometry(QRect(0, 0, 48, 48));
	//ui->toolButton->setToolButtonStyle (Qt::ToolButtonIconOnly);
        
	QIcon icon;
    icon.addFile(QString::fromUtf8(":/Resources/Resources/Nothing.png"), QSize(), QIcon::Normal, QIcon::Off);
	ui->toolButton->setIcon(icon);
	ui->toolButton->setIconSize(QSize(48, 48));

	connect(ui->toolButton					,SIGNAL(clicked())			,this,SLOT(SlotClicked()));
	connect(((CrossButton *)ui->toolButton) ,SIGNAL(SignalRightButton()),this,SLOT(SlotRClicked()));

    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	TM.setSingleShot(true);
	TM.setInterval(200);
	connect(&TM,SIGNAL(timeout()), this ,SLOT(SlotRedraw()),Qt::QueuedConnection);	
}

HookDrawRegulationLineForm::~HookDrawRegulationLineForm()
{
	delete ui;
}
void	HookDrawRegulationLineForm::ResizeAction()
{
	ui->toolButton->setGeometry(0,0,width(),height());
	ui->toolButton->setIconSize(QSize(ui->toolButton->width(), ui->toolButton->height()));
}
static	bool TargetFunctionPaintLast(FunctionServerClass *Obj,GUIFormBase *TargetObj,QPainter &pnt ,QImage &PntImage)
{
	DisplayImage	*DImage=dynamic_cast<DisplayImage *>(TargetObj);
	if(DImage!=NULL){
		HookDrawRegulationLineForm	*Form=dynamic_cast<HookDrawRegulationLineForm *>(Obj);
		if(Form!=NULL){
			LayersBase	*LBase=Form->GetLayersBase();
			int	page=DImage->ShowOnePage;
			if(page<0)
				page=0;
			DataInPage *P;
			if(DImage->ShowFixedPhase==-1){
				P=LBase->GetPageData(page);
			}
			else{
				P=LBase->GetPageDataPhase(DImage->ShowFixedPhase)->GetPageData(page);
			}
			if(P!=NULL){
				DImage->LockPaintMutex();
				if(LBase->TryLockWeakDraw()==true){
					Form->Draw(pnt,P,DImage->GetZoomRate(),DImage->GetMovx(),DImage->GetMovy()
									,DImage->GetCanvasWidth(),DImage->GetCanvasHeight());
					LBase->UnlockWeakDraw();
				}
				DImage->UnlockPaintMutex();
			}
		}
	}
	return true;
}
void	HookDrawRegulationLineForm::Prepare(void)
{
}

void	HookDrawRegulationLineForm::ReadyParam(void)
{
	for(int i=0;i<sizeof(TargetPanel)/sizeof(TargetPanel[0]) && i<HookTargetInst.count();i++){
		GUIFormBase	*f=GetLayersBase()->FindByName(HookTargetInst[i]);
		if(f!=NULL){
			TargetPanel[i]=dynamic_cast<DisplayImage *>(f);
			TargetPanel[i]->SetHookInPaintLast		(this,TargetFunctionPaintLast);
		}
	}
}

void	HookDrawRegulationLineForm::SlotClicked()
{
	if(Mode==0)
		Mode=1;
	else if(Mode==1)
		Mode=2;
	else if(Mode==2)
		Mode=0;
	SetMode();
}
void	HookDrawRegulationLineForm::SetMode(void)
{
	if(Mode==0){
		QIcon icon;
		icon.addFile(QString::fromUtf8(":/Resources/Resources/Nothing.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui->toolButton->setIcon(icon);
	}
	if(Mode==1){
		QIcon icon;
		icon.addFile(QString::fromUtf8(":/Resources/Resources/Cross1.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui->toolButton->setIcon(icon);
	}
	if(Mode==2){
		QIcon icon;
		icon.addFile(QString::fromUtf8(":/Resources/Resources/CrossN.png"), QSize(), QIcon::Normal, QIcon::Off);
		ui->toolButton->setIcon(icon);
	}
	TM.start();
}

void HookDrawRegulationLineForm::SlotRClicked()
{
	QColor	Col=QColorDialog::getColor ( Color, NULL
									, "ラインの色");
	if(Col.isValid()==true){
		Color=Col;
	}
}

void	HookDrawRegulationLineForm::SlotRedraw()
{
	for(int i=0;i<sizeof(TargetPanel)/sizeof(TargetPanel[0]) && i<HookTargetInst.count();i++){
		if(TargetPanel[i]!=NULL){
			TargetPanel[i]->Repaint();
		}
	}
}

void	HookDrawRegulationLineForm::Draw(QPainter &pnt	,DataInPage *P
										,double ZoomRate,int movx ,int movy 
										,int CanvasWidth , int CanvasHeight)
{
	if(Mode==1){
		int	Cx=P->GetDotPerLine()/2;
		int	Cy=P->GetMaxLines()/2;
		int	GCx=(Cx+movx)*ZoomRate;
		int	GCy=(Cy+movy)*ZoomRate;
		QPen	Pen(Color);
		Pen.setWidth(LineWidth);
		pnt.setPen(Pen);
		pnt.drawLine(GCx,0,GCx,CanvasHeight);
		pnt.drawLine(GCx+1,0,GCx+1,CanvasHeight);
		pnt.drawLine(0,GCy,CanvasWidth,GCy);
		pnt.drawLine(0,GCy+1,CanvasWidth,GCy+1);
	}
	if(Mode==2){
		int	Cx=P->GetDotPerLine()/2;
		int	Cy=P->GetMaxLines()/2;
		int	GCx=(Cx+movx)*ZoomRate;
		int	GCy=(Cy+movy)*ZoomRate;
		QPen	Pen(Color);
		Pen.setWidth(LineWidth);
		pnt.setPen(Pen);
		pnt.drawLine(GCx,0,GCx,CanvasHeight);
		pnt.drawLine(GCx+1,0,GCx+1,CanvasHeight);
		pnt.drawLine(0,GCy,CanvasWidth,GCy);
		pnt.drawLine(0,GCy+1,CanvasWidth,GCy+1);

		Pen.setStyle(Qt::DotLine);
		pnt.setPen(Pen);
		if(ZoomRate>=0.1 && ZoomRate<10){
			int	L=100*ZoomRate;
			for(int	x=GCx+L;x<CanvasWidth;x+=L){
				pnt.drawLine(x,0,x,CanvasHeight);
			}
			for(int	x=GCx-L;x>=0;x-=L){
				pnt.drawLine(x,0,x,CanvasHeight);
			}
			for(int y=GCy+L;y<CanvasHeight;y+=L){
				pnt.drawLine(0,y,CanvasWidth,y);
			}
			for(int y=GCy-L;y>=0;y-=L){
				pnt.drawLine(0,y,CanvasWidth,y);
			}
		}
	}
}
void	HookDrawRegulationLineForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdHookDrawRegulationLine_GetMode	*CmdHookDrawRegulationLine_GetModeVar=dynamic_cast<CmdHookDrawRegulationLine_GetMode *>(packet);
	if(CmdHookDrawRegulationLine_GetModeVar!=NULL){
		CmdHookDrawRegulationLine_GetModeVar->Mode=Mode;
		return;
	}
	CmdHookDrawRegulationLine_SetMode	*CmdHookDrawRegulationLine_SetModeVar=dynamic_cast<CmdHookDrawRegulationLine_SetMode *>(packet);
	if(CmdHookDrawRegulationLine_SetModeVar!=NULL){
		Mode=CmdHookDrawRegulationLine_SetModeVar->Mode;
		SetMode();
		return;
	}
	CmdReqHookDrawRegulationInfo	*CmdReqHookDrawRegulationInfoVar=dynamic_cast<CmdReqHookDrawRegulationInfo *>(packet);
	if(CmdReqHookDrawRegulationInfoVar!=NULL){
		CmdReqHookDrawRegulationInfoVar->LineWidth=LineWidth;
		CmdReqHookDrawRegulationInfoVar->LineColor=Color;
		return;
	}
	CmdSetHookDrawRegulationInfo	*CmdSetHookDrawRegulationInfoVar=dynamic_cast<CmdSetHookDrawRegulationInfo *>(packet);
	if(CmdSetHookDrawRegulationInfoVar!=NULL){
		LineWidth	=CmdSetHookDrawRegulationInfoVar->LineWidth;
		Color		=CmdSetHookDrawRegulationInfoVar->LineColor;
		return;
	}
}
