#include "MapForm.h"
#include "ui_MapForm.h"
#include "XDataInLayer.h"
#include "NGMapForm.h"
#include "XIntegrationBase.h"
#include "swap.h"

MapGraphic::MapGraphic(QWidget *parent
				,bool	EnableMeasure
				,bool	EnableToolArea
				,bool	EnableVScroller
				,bool	EnableHScroller
				,bool	EnableZoom
				,bool	EnableMove
				,bool	EnableFitZoom)
	:mtGraphicUnit(parent
				,EnableMeasure
				,EnableToolArea
				,EnableVScroller
				,EnableHScroller
				,EnableZoom
				,EnableMove
				,EnableFitZoom)
{
}

MapGraphic::~MapGraphic()
{
}

MapForm::MapForm(NGMapForm *p,QWidget *parent) :
    QWidget(parent)
	,Parent(p)
    ,ui(new Ui::MapForm)
{
    ui->setupUi(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

	MapPanel.setParent(ui->frame);
	connect(&MapPanel,SIGNAL(SignalOnPaint(QPainter &)),this,SLOT(SlotOnPaint(QPainter &)));

	LastMovX	=-9999999;
	LastMovY	=-9999999;
	LastZoomRate=0;
	LastMaster	=-1;
	connect(&MapPanel,SIGNAL(SignalMouseLDown(int,int))	   ,this,SLOT(SlotMouseLDown(int,int)));
	connect(&MapPanel,SIGNAL(SignalMouseRDown(int,int))	   ,this,SLOT(SlotMouseRDown(int,int)));
	connect(&MapPanel,SIGNAL(SignalMouseWheel(int,int,int)),this,SLOT(SlotMouseWheel(int,int,int)));

	ui->comboBoxMachine->clear();
	IntegrationBase	*LBase=Parent->GetLayersBase()->GetIntegrationBasePointer();
	for(EachMaster *m=LBase->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
		ui->comboBoxMachine->addItem(m->GetMachineName());
	}
}

MapForm::~MapForm()
{
    delete ui;
}

void	MapForm::resizeEvent(QResizeEvent *event)
{
	ui->frame->setGeometry(0,ui->comboBoxMachine->height()
						   ,width(),height()-ui->comboBoxMachine->height());
	MapPanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
	LastMaster=-1;
	MakeMapDim();
}
void	MapForm::MakeMapDim(void)
{
	int	Index=ui->comboBoxMachine->currentIndex();
	if(Index<0)
		Index=0;
	IntegrationBase	*LBase=Parent->GetLayersBase()->GetIntegrationBasePointer();
	EachMaster	*M=LBase->MasterDatas[Index];
	int		MovX	=MapPanel.GetMovx();
	int		MovY	=MapPanel.GetMovy();
	double	ZoomRate=MapPanel.GetZoomRate();

	if(LastMovX	==MovX
	&& LastMovY	==MovY
	&& LastZoomRate==ZoomRate
	&& LastMaster==Index){
		return;
	}
	LastMovX	=MovX;
	LastMovY	=MovY;
	LastZoomRate=ZoomRate;
	LastMaster	=Index;

	int	mx1,my1,mx2,my2;
	M->GetXY(mx1,my1,mx2,my2);
	MapPanel.SetAreaSize(mx2,my2);

	for(int x=0;x<DivX;x++){
		for(int y=0;y<DivY;y++){
			MapDim[x][y]=0;
		}
	}
	int	GWidth	=MapPanel.GetCanvasWidth();
	int	GHeight	=MapPanel.GetCanvasHeight();
	QImage	Image(GWidth,GHeight ,QImage::Format_ARGB32);
	
	int	Phase=0;
	Parent->DrawMasterImage(M ,Image,Phase ,MovX,MovY ,ZoomRate);
	MasterImage=Image;

	int	x1=0/ZoomRate-MovX;
	int	y1=0/ZoomRate-MovY;
	int	x2=(GWidth )/ZoomRate-MovX;
	int	y2=(GHeight)/ZoomRate-MovY;

	double	XDivLen=((double)(x2-x1))/DivX;
	double	YDivLen=((double)(y2-y1))/DivY;
	MapListByMaster *ResultList=NULL;
	for(MapListByMaster *t=Parent->MapList.GetFirst();t!=NULL;t=t->GetNext()){
		if(t->MachineID==M->GetMachineCode()){
			ResultList=t;
			break;
		}
	}
	if(ResultList!=NULL){

		for(NGPointList *p=ResultList->NGPoints.GetFirst();p!=NULL;p=p->GetNext()){
			if(x1<=p->XPos && p->XPos<x2
			&& y1<=p->YPos && p->YPos<y2){
				int	Lx=(p->XPos-x1)/XDivLen;
				int	Ly=(p->YPos-y1)/YDivLen;
				if(0<=Lx && Lx<DivX && 0<=Ly && Ly<DivY){
					MapDim[Lx][Ly]++;
				}
			}
		}
		int	MaxD=0;
		for(int x=0;x<DivX;x++){
			for(int y=0;y<DivY;y++){
				MaxD=max(MaxD,MapDim[x][y]);
			}
		}
		if(MaxD>0){
			double	XGLen=((double)(GWidth ))/DivX;
			double	YGLen=((double)(GHeight))/DivY;
			QImage	tMapMask(GWidth,GHeight ,QImage::Format_ARGB32);
			for(int y=0;y<GHeight;y++){
				QRgb	*d=(QRgb *)tMapMask.scanLine(y);
				for(int x=0;x<GWidth;x++,d++){
					int	Lx=x/XGLen;
					int	Ly=y/YGLen;
					if(0<=Lx && Lx<DivX && 0<Ly && Ly<DivY){
						double	e=255.0*((double)MapDim[Lx][Ly])/(double)MaxD;
						*d=qRgba(0,0,e,128);
					}
					else{
						*d=qRgba(0,0,0,128);
					}
				}
			}
			MapMask=tMapMask;
		}
	}
}
void	MapForm::SlotOnPaint(QPainter &pnt)
{
	MakeMapDim();
	pnt.drawImage(0,0,MasterImage);
	pnt.drawImage(0,0,MapMask);
}
void MapForm::on_comboBoxMachine_currentIndexChanged(int index)
{
	MakeMapDim();
}
void	MapForm::SlotMouseLDown(int x,int y)
{
	int		MovX	=MapPanel.GetMovx();
	int		MovY	=MapPanel.GetMovy();
	double	ZoomRate=MapPanel.GetZoomRate();
	int	X=(x+MovX)*ZoomRate;
	int	Y=(y+MovY)*ZoomRate;
	MapPanel.ZoomIn(X,Y);
	MakeMapDim();
}
void	MapForm::SlotMouseRDown(int x,int y)
{
	int		MovX	=MapPanel.GetMovx();
	int		MovY	=MapPanel.GetMovy();
	double	ZoomRate=MapPanel.GetZoomRate();
	int	X=(x+MovX)*ZoomRate;
	int	Y=(y+MovY)*ZoomRate;
	MapPanel.ZoomOut(X,Y);
	MakeMapDim();
}
void	MapForm::SlotMouseWheel(int delta ,int x,int y)
{
	int		MovX	=MapPanel.GetMovx();
	int		MovY	=MapPanel.GetMovy();
	double	ZoomRate=MapPanel.GetZoomRate();
	int	X=(x+MovX)*ZoomRate;
	int	Y=(y+MovY)*ZoomRate;
	if(delta>0){
		MapPanel.ZoomIn(X,Y);
	}
	else{
		MapPanel.ZoomOut(X,Y);
	}
	MakeMapDim();
}
