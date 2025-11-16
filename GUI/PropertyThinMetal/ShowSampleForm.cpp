#include "PropertyThinMetalFormResource.h"
#include "ShowSampleForm.h"
#include "ui_ShowSampleForm.h"
#include "XPropertyThinMetalPacket.h"
#include "PropertyThinMetalForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

SampleImagePanel::SampleImagePanel(LayersBase *base ,ShowSampleForm *parent)
	:QWidget(parent),ServiceForLayers(base)
{
	Parent=parent;

	MovX	=0;
	MovY	=0;
	ZoomRate	=1.0;

	InstallOperationLog(this);
}

void	SampleImagePanel::SetInitial(CoeffImageList *a)
{
	int	W=a->XLen;
	int	H=a->YLen;

	MovX=0;
	MovY=0;
	double	Z1=100000000;
	Z1=((double)width())/((double)W);
	double	Z2=100000000;
	Z2=((double)height())/((double)H);
	ZoomRate=(Z1<Z2)?Z1:Z2;
}
void	SampleImagePanel::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);

	QImage	TmpImage(width(),height(),QImage::Format_ARGB32);
	TmpImage.fill(0);

	double	Z=1.0/ZoomRate;
	for(int y=0;y<height();y++){
		BYTE	*d=TmpImage.scanLine(y);
		int	Y=y*Z-MovY;
		if(0<=Y && Y<Parent->CurrentSample.YLen){
			BYTE	*sR=Parent->CurrentSample.Image[Y];
			double	fX=-MovX;
			for(int x=0;x<width();x++){
				int	X=fX;
				if(0<=X && X<Parent->CurrentSample.XLen){
					*((int32 *)d)=0xFF000000+((*(sR+X))<<16)+((*(sR+X))<<8)+((*(sR+X)));
				}
				else{
					*((int32 *)d)=0xFF000000;
				}
				fX+=Z;
				d+=4;
			}
		}
	}
	Pnt.drawImage(0,0,TmpImage);
}

void	SampleImagePanel::mousePressEvent ( QMouseEvent *Ev )
{
}
void	SampleImagePanel::mouseMoveEvent ( QMouseEvent * e )
{
}
void	SampleImagePanel::mouseReleaseEvent ( QMouseEvent * e )
{
}
void	SampleImagePanel::wheelEvent ( QWheelEvent * e )
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
//=========================================================================================

ShowSampleForm::ShowSampleForm(ThinMetalInfoList *L ,LayersBase *base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(base)
	,SamplePanel(base,this)
	,ui(new Ui::ShowSampleForm)
{
    ui->setupUi(this);
	ItemInfo	=L;

	SamplePanel.setParent(ui->frame);
	SamplePanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());

	ShowList();
}

ShowSampleForm::~ShowSampleForm()
{
    delete ui;
}

void	ShowSampleForm::ShowList(void)
{
	GUICmdReqThinMetalSampleList	CmdReq (GetLayersBase(),sRoot,sName,ItemInfo->GlobalPage);
	GUICmdSendThinMetalSampleList	CmdSend(GetLayersBase(),sRoot,sName,ItemInfo->GlobalPage);
	CmdReq.Layer	=ItemInfo->Layer;
	CmdReq.ItemID	=ItemInfo->ItemID;
	CmdReq.Send(ItemInfo->GlobalPage,0,CmdSend);
	Judgements=CmdSend.Judgements;

	int	row=0;
	ui->tableWidget->setRowCount(Judgements.GetCount());
	for(IntClass *d=Judgements.GetFirst();d!=NULL;d=d->GetNext(),row++){
		if(d->GetValue()==0)
			SetDataToTable(ui->tableWidget,0 ,row ,LangSolver.GetString(ShowSampleForm_LS,LID_16)/*"None"*/);
		if(d->GetValue()==1)
			SetDataToTable(ui->tableWidget,0 ,row ,LangSolver.GetString(ShowSampleForm_LS,LID_17)/*"OK"*/);
		else if(d->GetValue()==2)
			SetDataToTable(ui->tableWidget,0 ,row ,LangSolver.GetString(ShowSampleForm_LS,LID_18)/*"NG1"*/);
		else if(d->GetValue()==3)
			SetDataToTable(ui->tableWidget,0 ,row ,LangSolver.GetString(ShowSampleForm_LS,LID_19)/*"NG2"*/);
		else if(d->GetValue()==4)
			SetDataToTable(ui->tableWidget,0 ,row ,LangSolver.GetString(ShowSampleForm_LS,LID_20)/*"NG3"*/);
		else if(d->GetValue()==5)
			SetDataToTable(ui->tableWidget,0 ,row ,LangSolver.GetString(ShowSampleForm_LS,LID_21)/*"NG4"*/);
	}
}


void ShowSampleForm::on_pushButtonDeleteSelection_clicked()
{
	GUICmdReqThinMetalDeleteSamples	CmdReq (GetLayersBase(),sRoot,sName,ItemInfo->GlobalPage);

	GetSelectedRows(ui->tableWidget,CmdReq.Numbers);
	CmdReq.Layer	=ItemInfo->Layer;
	CmdReq.ItemID	=ItemInfo->ItemID;
	CmdReq.Send(NULL,ItemInfo->GlobalPage,0);

	ShowList();
}

void ShowSampleForm::on_pushButtonClose_clicked()
{
	close();
}

void ShowSampleForm::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
	GUICmdReqThinMetalSampleDetail	CmdReq (GetLayersBase(),sRoot,sName,ItemInfo->GlobalPage);
	GUICmdSendThinMetalSampleDetail	CmdSend(GetLayersBase(),sRoot,sName,ItemInfo->GlobalPage);
	CmdReq.Layer	=ItemInfo->Layer;
	CmdReq.ItemID	=ItemInfo->ItemID;
	CmdReq.Number	=ui->tableWidget->currentRow();
	CmdReq.Send(ItemInfo->GlobalPage,0,CmdSend);
	CurrentSample	=CmdSend.DetailSample;
	SamplePanel.SetInitial(&CurrentSample);
	SamplePanel.repaint();
}
