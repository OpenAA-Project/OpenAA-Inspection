#include "ShowListDialog.h"
#include "ui_ShowListDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"

ChildImagePanel::ChildImagePanel(LayersBase *Base,ShowListDialog *parent)
	:ServiceForLayers(Base)
{
	Buffer	=NULL;
	Img		=NULL;
}
ChildImagePanel::~ChildImagePanel(void)
{
}
	
void	ChildImagePanel::SetImage(ImageBufferWithInfo *buff)
{
	Buffer=buff;
	repaint();
}

void	ChildImagePanel::SlotOnPaint(QPainter &pnt)
{
	if(Buffer==NULL)
		return;
	DataInPage	*Dp=NULL;
	if(GetLayersBase()->GetPageDataPhase(Buffer->Phase)!=NULL
	&& GetLayersBase()->GetPageDataPhase(Buffer->Phase)->GetPageData(Buffer->Page)!=NULL){
		Dp=GetLayersBase()->GetPageDataPhase(Buffer->Phase)->GetPageData(Buffer->Page);
	}
	else{
		return;
	}
	int	W=GetCanvasWidth();
	int	H=GetCanvasHeight();
	if(Img==NULL || Img->width()!=W || Img->height()!=H){
		if(Img!=NULL)
			delete	Img;
		Img=new QImage(W,H,QImage::Format_ARGB32);
	}
	Img->fill(Qt::black);
	double	Z=1.0/GetZoomRate();

	int	gx1=(GetMovx())*GetZoomRate();
	int	gy1=(GetMovy())*GetZoomRate();
	int	gx2=(GetMovx()+Dp->GetDotPerLine()	)*GetZoomRate();
	int	gy2=(GetMovy()+Dp->GetMaxLines()	)*GetZoomRate();

	gx1=max(gx1,0);
	gy1=max(gy1,0);
	gx2=min(gx2,W);
	gy2=min(gy2,H);
	int	X1=Clipping((int)(gx1*Z-GetMovx()),0,Dp->GetDotPerLine());
	int	X2=Clipping((int)(gx2*Z-GetMovx()),0,Dp->GetDotPerLine());
	for(int y=gy1;y<gy2;y++){
		QRgb	*d=(QRgb *)Img->scanLine(y);
		d+=gx1;
		int	Y =Clipping((int)(y*Z-GetMovy()),0,Dp->GetMaxLines());
		BYTE	*s=Buffer->GetY(Y);
		
		for(double DX=X1;DX<X2;DX+=Z,d++){
			BYTE	c=s[(int)DX];
			*d=qRgba(c,c,c,255);
		}
	}

	pnt.drawImage(0,0,*Img);
}


ShowListDialog::ShowListDialog(ButtonShowStockedImage *p,LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
	,Panel(Base,this)
	,Parent(p)
    ,ui(new Ui::ShowListDialog)
{
    ui->setupUi(this);

	Parent->MakeList(List);
	Panel.setParent(ui->frame);
	Panel.setGeometry(0,0,ui->frame->width(),ui->frame->height());

	ui->tableWidgetShotList->setColumnWidth(0,64);
	ui->tableWidgetShotList->setColumnWidth(1,32);
	ui->tableWidgetShotList->setColumnWidth(2,32);
	ui->tableWidgetShotList->setColumnWidth(3,32);

	ui->tableListInOneShot->setColumnWidth(0,32);
	ui->tableListInOneShot->setColumnWidth(1,32);
	ui->tableListInOneShot->setColumnWidth(2,32);

	ui->tableWidgetShotList->setRowCount(List.GetCount());
	int	row=0;
	for(ImageBufferWithInfoPointerContainer *L=List.GetFirst();L!=NULL;L=L->GetNext(),row++){
		ImageBufferWithInfoPointer	*F=L->NPListPack<ImageBufferWithInfoPointer>::GetFirst();
		ImageBufferWithInfo	*P=F->Point;
		::SetDataToTable(ui->tableWidgetShotList ,0 ,row ,P->DateTime.toString(/**/"dd-hh:mm:ss")
														 +QString(/**/" ")
														 +QString::number(P->ComputerMilisec%1000));

		IntList	PhaseNumb;
		IntList	PageNumb;
		IntList	LayerNumb;
		for(ImageBufferWithInfoPointer	*F=L->NPListPack<ImageBufferWithInfoPointer>::GetFirst();F!=NULL;F=F->GetNext()){
			ImageBufferWithInfo	*P=F->Point;
			if(PhaseNumb.IsInclude(P->Phase)==false)
				PhaseNumb.Add(P->Phase);
			if(PageNumb.IsInclude(P->Page)==false)
				PageNumb.Add(P->Page);
			if(LayerNumb.IsInclude(P->Layer)==false)
				LayerNumb.Add(P->Layer);
		}
		::SetDataToTable(ui->tableWidgetShotList ,1 ,row ,QString::number(PhaseNumb.GetCount()));
		::SetDataToTable(ui->tableWidgetShotList ,2 ,row ,QString::number(PageNumb.GetCount()));
		::SetDataToTable(ui->tableWidgetShotList ,3 ,row ,QString::number(LayerNumb.GetCount()));
	}
}

ShowListDialog::~ShowListDialog()
{
    delete ui;
}

void	ShowListDialog::resizeEvent ( QResizeEvent * event )
{
	ui->tableWidgetShotList->resize(ui->tableWidgetShotList->width(),height());
	ui->tableListInOneShot->resize(ui->tableListInOneShot->width(),height());
	ui->frame->resize(width()-ui->frame->geometry().left(),height());
	Panel.setGeometry(0,0,ui->frame->width(),ui->frame->height());
}

void ShowListDialog::on_tableWidgetShotList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetShotList->currentRow();
	if(Row<0)
		return;
	ImageBufferWithInfoPointerContainer *L=List.GetItem(Row);
	if(L==NULL)
		return;

	ui->tableListInOneShot->setRowCount(L->GetCount());
	int	row=0;
	for(ImageBufferWithInfoPointer	*F=L->NPListPack<ImageBufferWithInfoPointer>::GetFirst();F!=NULL;F=F->GetNext(),row++){
		ImageBufferWithInfo	*P=F->Point;
		::SetDataToTable(ui->tableListInOneShot ,0 ,row ,QString::number(P->Phase));
		::SetDataToTable(ui->tableListInOneShot ,1 ,row ,QString::number(P->Page));
		::SetDataToTable(ui->tableListInOneShot ,2 ,row ,QString::number(P->Layer));
	}
}

void ShowListDialog::on_tableListInOneShot_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetShotList->currentRow();
	if(Row<0)
		return;
	ImageBufferWithInfoPointerContainer *L=List.GetItem(Row);
	if(L==NULL)
		return;
	Row=ui->tableListInOneShot->currentRow();
	if(Row<0)
		return;
	ImageBufferWithInfoPointer	*F=L->NPListPack<ImageBufferWithInfoPointer>::GetItem(Row);
	if(F==NULL)
		return;
	Panel.SetImage(F->Point);
}
