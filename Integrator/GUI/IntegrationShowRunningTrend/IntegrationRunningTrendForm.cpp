#include "IntegrationRunningTrendResource.h"
#include "IntegrationRunningTrendForm.h"
#include "ui_IntegrationRunningTrendForm.h"
#include "XParamIntegrationMaster.h"
#include "swap.h"
#define	_USE_MATH_DEFINES
#include <math.h>

TrendWidget::TrendWidget(LayersBase *base ,IntegrationRunningTrendForm *p)
	:ServiceForLayers(base),Parent(p)
{
}

struct	TrendStruct
{
	struct	RunningTrendData	TM;
	int			OKCount;
	int			NGCount;
};

double	GetLog10Graph(double m)
{
	if(m>0){
		double	Ret=log10(m);
		if(Ret<0)
			return 0.0;
		return Ret;
	}
	return 0.0;
}

void TrendWidget::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	Pnt.fillRect(geometry(),Qt::white);
	int	YPosOrg	=height()-24;
	Pnt.setPen(Qt::black);
	Pnt.drawLine(0,YPosOrg,width(),YPosOrg);

	struct	TrendStruct		TrendStructDim[5000];
	int			DimCount=-1;
	QDateTime	Now=QDateTime::currentDateTime();

	if(Parent->GetTimeScale()==0){
		for(int i=Parent->CurrentPoint-1;i>=0;i--){
			struct	RunningTrendData	*f=&Parent->RunningData[i];
			if(DimCount<0
			|| f->Year	!=TrendStructDim[DimCount].TM.Year
			|| f->Month	!=TrendStructDim[DimCount].TM.Month
			|| f->Day	!=TrendStructDim[DimCount].TM.Day
			|| f->Hour	!=TrendStructDim[DimCount].TM.Hour
			|| f->Minute!=TrendStructDim[DimCount].TM.Minute){
				DimCount++;
				TrendStructDim[DimCount].TM=*f;
				TrendStructDim[DimCount].OKCount=0;
				TrendStructDim[DimCount].NGCount=0;
			}
			if(f->Ok==true)
				TrendStructDim[DimCount].OKCount++;
			else
				TrendStructDim[DimCount].NGCount++;
			if(DimCount>width()){
				DimCount++;
				break;
			}
		}
		

		int	MaxCount=0;
		for(int i=0;i<DimCount;i++){
			MaxCount=max(MaxCount,TrendStructDim[i].OKCount);
			MaxCount=max(MaxCount,TrendStructDim[i].NGCount);
		}
		QPen	Pen(Qt::black,Qt::DotLine);
		Pnt.setPen(Pen);
		int	YRes;
		bool	LogMode;
		Parent->ScaleYDimCount=0;
		if(MaxCount<height()-32){
			YRes=25;
			for(int y=25;y<height()-32;y+=25,Parent->ScaleYDimCount++){
				Pnt.drawLine(0,YPosOrg-y,width(),YPosOrg-y);
				Parent->ScaleYDim[Parent->ScaleYDimCount].YPos=YPosOrg-y;
				Parent->ScaleYDim[Parent->ScaleYDimCount].Scale=y;
			}
			LogMode=false;
		}
		else{
			int	tOrder=10;
			int	CountOrder=GetOrder(MaxCount)+1;
			YRes=(height()-32)/CountOrder;
			for(int y=YRes;y<height()-32;y+=YRes,Parent->ScaleYDimCount++){
				Pnt.drawLine(0,YPosOrg-y,width(),YPosOrg-y);
				Parent->ScaleYDim[Parent->ScaleYDimCount].YPos=YPosOrg-y;
				Parent->ScaleYDim[Parent->ScaleYDimCount].Scale=tOrder;
				tOrder*=10;
			}
			LogMode=true;
		}
		int		OKLastY=0;
		int		NGLastY=0;
		for(int x=0;x<width();x++){
			QDateTime	t=Now.addSecs(-60*(width()-20-x));
			int	Year	=t.date().year()-2000;
			int	Month	=t.date().month();
			int	Day		=t.date().day();
			int	Hour	=t.time().hour();
			int	Minute	=t.time().minute();
			int	i;
			for(i=0;i<DimCount;i++){
				if(TrendStructDim[i].TM.Year==Year
				&& TrendStructDim[i].TM.Month==Month
				&& TrendStructDim[i].TM.Day==Day
				&& TrendStructDim[i].TM.Hour==Hour
				&& TrendStructDim[i].TM.Minute==Minute){
					if(LogMode==false){
						Pnt.setPen(Parent->OKColor);
						Pnt.drawLine(x-1,YPosOrg-OKLastY,x,YPosOrg-TrendStructDim[i].OKCount);
						OKLastY=TrendStructDim[i].OKCount;
						Pnt.setPen(Parent->NGColor);
						Pnt.drawLine(x-1,YPosOrg-NGLastY,x,YPosOrg-TrendStructDim[i].NGCount);
						NGLastY=TrendStructDim[i].NGCount;
					}
					else{
						Pnt.setPen(Parent->OKColor);
						double	Y11=GetLog10Graph((double)OKLastY)*YRes;
						double	Y12=GetLog10Graph((double)TrendStructDim[i].OKCount)*YRes;
						Pnt.drawLine(x-1,YPosOrg-Y11,x,YPosOrg-Y12);
						OKLastY=TrendStructDim[i].OKCount;
						double	Y21=GetLog10Graph((double)NGLastY)*YRes;
						double	Y22=GetLog10Graph((double)TrendStructDim[i].OKCount)*YRes;
						Pnt.setPen(Parent->NGColor);
						Pnt.drawLine(x-1,YPosOrg-Y21,x,YPosOrg-Y22);
						NGLastY=TrendStructDim[i].NGCount;
					}
					break;
				}
			}
			if(i>=DimCount){
				if(LogMode==false){
					Pnt.setPen(Parent->OKColor);
					Pnt.drawLine(x-1,YPosOrg-OKLastY,x,YPosOrg);
					OKLastY=0;
					Pnt.setPen(Parent->NGColor);
					Pnt.drawLine(x-1,YPosOrg-NGLastY,x,YPosOrg);
					NGLastY=0;
				}
				else{
					Pnt.setPen(Parent->OKColor);
					double	Y11=GetLog10Graph((double)OKLastY)*YRes;
					Pnt.drawLine(x-1,YPosOrg-Y11,x,YPosOrg);
					OKLastY=0;
					double	Y21=GetLog10Graph((double)NGLastY)*YRes;
					Pnt.setPen(Parent->NGColor);
					Pnt.drawLine(x-1,YPosOrg-Y21,x,YPosOrg);
					NGLastY=0;
				}
			}
			if(Minute==0){
				Pnt.setBrush(Qt::black);
				Pnt.setPen(Qt::black);
				int	TextHeight=fontMetrics ().height();
				Pnt.drawText(x,YPosOrg+TextHeight,QString::number(Hour));
			}
		}
	}
	else
	if(Parent->GetTimeScale()==1){
		for(int i=Parent->CurrentPoint-1;i>=0;i--){
			struct	RunningTrendData	*f=&Parent->RunningData[i];
			if(DimCount<0
			|| f->Year	!=TrendStructDim[DimCount].TM.Year
			|| f->Month	!=TrendStructDim[DimCount].TM.Month
			|| f->Day	!=TrendStructDim[DimCount].TM.Day
			|| f->Hour	!=TrendStructDim[DimCount].TM.Hour){
				DimCount++;
				TrendStructDim[DimCount].TM=*f;
				TrendStructDim[DimCount].OKCount=0;
				TrendStructDim[DimCount].NGCount=0;
			}
			if(f->Ok==true)
				TrendStructDim[DimCount].OKCount++;
			else
				TrendStructDim[DimCount].NGCount++;
			if(DimCount>width()){
				DimCount++;
				break;
			}
		}
		

		int	MaxCount=0;
		for(int i=0;i<DimCount;i++){
			MaxCount=max(MaxCount,TrendStructDim[i].OKCount);
			MaxCount=max(MaxCount,TrendStructDim[i].NGCount);
		}
		QPen	Pen(Qt::black,Qt::DotLine);
		Pnt.setPen(Pen);
		int	YRes;
		bool	LogMode;
		Parent->ScaleYDimCount=0;
		if(MaxCount<height()-32){
			YRes=25;
			for(int y=25;y<height()-32;y+=25,Parent->ScaleYDimCount++){
				Pnt.drawLine(0,YPosOrg-y,width(),YPosOrg-y);
				Parent->ScaleYDim[Parent->ScaleYDimCount].YPos=YPosOrg-y;
				Parent->ScaleYDim[Parent->ScaleYDimCount].Scale=y;
			}
			LogMode=false;
		}
		else{
			int	tOrder=10;
			int	CountOrder=GetOrder(MaxCount)+1;
			YRes=(height()-32)/CountOrder;
			for(int y=YRes;y<height()-32;y+=YRes,Parent->ScaleYDimCount++){
				Pnt.drawLine(0,YPosOrg-y,width(),YPosOrg-y);
				Parent->ScaleYDim[Parent->ScaleYDimCount].YPos=YPosOrg-y;
				Parent->ScaleYDim[Parent->ScaleYDimCount].Scale=tOrder;
				tOrder*=10;
			}
			LogMode=true;
		}
		int		OKLastY=0;
		int		NGLastY=0;
		for(int x=0;x<width();x++){
			QDateTime	t=Now.addSecs(-60*60*(width()-20-x));
			int	Year	=t.date().year()-2000;
			int	Month	=t.date().month();
			int	Day		=t.date().day();
			int	Hour	=t.time().hour();
			int	i;
			for(i=0;i<DimCount;i++){
				if(TrendStructDim[i].TM.Year==Year
				&& TrendStructDim[i].TM.Month==Month
				&& TrendStructDim[i].TM.Day==Day
				&& TrendStructDim[i].TM.Hour==Hour){
					if(LogMode==false){
						Pnt.setPen(Parent->OKColor);
						Pnt.drawLine(x-1,YPosOrg-OKLastY,x,YPosOrg-TrendStructDim[i].OKCount);
						OKLastY=TrendStructDim[i].OKCount;
						Pnt.setPen(Parent->NGColor);
						Pnt.drawLine(x-1,YPosOrg-NGLastY,x,YPosOrg-TrendStructDim[i].NGCount);
						NGLastY=TrendStructDim[i].NGCount;
					}
					else{
						Pnt.setPen(Parent->OKColor);
						double	Y11=GetLog10Graph((double)OKLastY)*YRes;
						double	Y12=GetLog10Graph((double)TrendStructDim[i].OKCount)*YRes;
						Pnt.drawLine(x-1,YPosOrg-Y11,x,YPosOrg-Y12);
						OKLastY=TrendStructDim[i].OKCount;
						double	Y21=GetLog10Graph((double)NGLastY)*YRes;
						double	Y22=GetLog10Graph((double)TrendStructDim[i].OKCount)*YRes;
						Pnt.setPen(Parent->NGColor);
						Pnt.drawLine(x-1,YPosOrg-Y21,x,YPosOrg-Y22);
						NGLastY=TrendStructDim[i].NGCount;
					}
					break;
				}
			}
			if(i>=DimCount){
				if(LogMode==false){
					Pnt.setPen(Parent->OKColor);
					Pnt.drawLine(x-1,YPosOrg-OKLastY,x,YPosOrg);
					OKLastY=0;
					Pnt.setPen(Parent->NGColor);
					Pnt.drawLine(x-1,YPosOrg-NGLastY,x,YPosOrg);
					NGLastY=0;
				}
				else{
					Pnt.setPen(Parent->OKColor);
					double	Y11=GetLog10Graph((double)OKLastY)*YRes;
					Pnt.drawLine(x-1,YPosOrg-Y11,x,YPosOrg);
					OKLastY=0;
					double	Y21=GetLog10Graph((double)NGLastY)*YRes;
					Pnt.setPen(Parent->NGColor);
					Pnt.drawLine(x-1,YPosOrg-Y21,x,YPosOrg);
					NGLastY=0;
				}
			}
			if(Hour==0){
				Pnt.setBrush(Qt::black);
				Pnt.setPen(Qt::black);
				int	TextHeight=fontMetrics ().height();
				Pnt.drawText(x,YPosOrg+TextHeight,QString::number(Day));
			}
		}
	}
	else
	if(Parent->GetTimeScale()==2){
		for(int i=Parent->CurrentPoint-1;i>=0;i--){
			struct	RunningTrendData	*f=&Parent->RunningData[i];
			if(DimCount<0
			|| f->Year	!=TrendStructDim[DimCount].TM.Year
			|| f->Month	!=TrendStructDim[DimCount].TM.Month
			|| f->Day	!=(TrendStructDim[DimCount].TM.Day)){
				DimCount++;
				TrendStructDim[DimCount].TM=*f;
				TrendStructDim[DimCount].OKCount=0;
				TrendStructDim[DimCount].NGCount=0;
			}
			if(f->Ok==true)
				TrendStructDim[DimCount].OKCount++;
			else
				TrendStructDim[DimCount].NGCount++;
			if(DimCount>width()){
				DimCount++;
				break;
			}
		}
		

		int	MaxCount=0;
		for(int i=0;i<DimCount;i++){
			MaxCount=max(MaxCount,TrendStructDim[i].OKCount);
			MaxCount=max(MaxCount,TrendStructDim[i].NGCount);
		}
		QPen	Pen(Qt::black,Qt::DotLine);
		Pnt.setPen(Pen);
		int	YRes;
		bool	LogMode;
		Parent->ScaleYDimCount=0;
		if(MaxCount<height()-32){
			YRes=25;
			for(int y=25;y<height()-32;y+=25,Parent->ScaleYDimCount++){
				Pnt.drawLine(0,YPosOrg-y,width(),YPosOrg-y);
				Parent->ScaleYDim[Parent->ScaleYDimCount].YPos=YPosOrg-y;
				Parent->ScaleYDim[Parent->ScaleYDimCount].Scale=y;
			}
			LogMode=false;
		}
		else{
			int	tOrder=10;
			int	CountOrder=GetOrder(MaxCount)+1;
			YRes=(height()-32)/CountOrder;
			for(int y=YRes;y<height()-32;y+=YRes,Parent->ScaleYDimCount++){
				Pnt.drawLine(0,YPosOrg-y,width(),YPosOrg-y);
				Parent->ScaleYDim[Parent->ScaleYDimCount].YPos=YPosOrg-y;
				Parent->ScaleYDim[Parent->ScaleYDimCount].Scale=tOrder;
				tOrder*=10;
			}
			LogMode=true;
		}
		int		OKLastY=0;
		int		NGLastY=0;
		for(int x=0;x<width();x++){
			QDateTime	t=Now.addSecs(-60*60*24*(width()-20-x));
			int	Year	=t.date().year()-2000;
			int	Month	=t.date().month();
			int	Day		=t.date().day();
			int	i;
			for(i=0;i<DimCount;i++){
				if(TrendStructDim[i].TM.Year==Year
				&& TrendStructDim[i].TM.Month==Month
				&& TrendStructDim[i].TM.Day==Day){
					if(LogMode==false){
						Pnt.setPen(Parent->OKColor);
						Pnt.drawLine(x-1,YPosOrg-OKLastY,x,YPosOrg-TrendStructDim[i].OKCount);
						OKLastY=TrendStructDim[i].OKCount;
						Pnt.setPen(Parent->NGColor);
						Pnt.drawLine(x-1,YPosOrg-NGLastY,x,YPosOrg-TrendStructDim[i].NGCount);
						NGLastY=TrendStructDim[i].NGCount;
					}
					else{
						Pnt.setPen(Parent->OKColor);
						double	Y11=GetLog10Graph((double)OKLastY)*YRes;
						double	Y12=GetLog10Graph((double)TrendStructDim[i].OKCount)*YRes;
						Pnt.drawLine(x-1,YPosOrg-Y11,x,YPosOrg-Y12);
						OKLastY=TrendStructDim[i].OKCount;
						double	Y21=GetLog10Graph((double)NGLastY)*YRes;
						double	Y22=GetLog10Graph((double)TrendStructDim[i].OKCount)*YRes;
						Pnt.setPen(Parent->NGColor);
						Pnt.drawLine(x-1,YPosOrg-Y21,x,YPosOrg-Y22);
						NGLastY=TrendStructDim[i].NGCount;
					}
					break;
				}
			}
			if(i>=DimCount){
				if(LogMode==false){
					Pnt.setPen(Parent->OKColor);
					Pnt.drawLine(x-1,YPosOrg-OKLastY,x,YPosOrg);
					OKLastY=0;
					Pnt.setPen(Parent->NGColor);
					Pnt.drawLine(x-1,YPosOrg-NGLastY,x,YPosOrg);
					NGLastY=0;
				}
				else{
					Pnt.setPen(Parent->OKColor);
					double	Y11=GetLog10Graph((double)OKLastY)*YRes;
					Pnt.drawLine(x-1,YPosOrg-Y11,x,YPosOrg);
					OKLastY=0;
					double	Y21=GetLog10Graph((double)NGLastY)*YRes;
					Pnt.setPen(Parent->NGColor);
					Pnt.drawLine(x-1,YPosOrg-Y21,x,YPosOrg);
					NGLastY=0;
				}
			}
			if(Day==1){
				Pnt.setBrush(Qt::black);
				Pnt.setPen(Qt::black);
				int	TextHeight=fontMetrics ().height();
				Pnt.drawText(x,YPosOrg+TextHeight,QString::number(Month));
			}
		}
	}
	Parent->ScaleY.repaint();
}

int	TrendWidget::GetOrder(int n)
{
	if(n<10)
		return 1;
	if(n<100)
		return 2;
	if(n<1000)
		return 3;
	if(n<10000)
		return 4;
	if(n<100000)
		return 5;
	if(n<1000000)
		return 6;
	if(n<10000000)
		return 7;
	if(n<100000000)
		return 8;
	if(n<1000000000)
		return 9;
	return 0;
}

ScaleYWidget::ScaleYWidget(LayersBase *base ,IntegrationRunningTrendForm *p)
	:ServiceForLayers(base),Parent(p)
{
}
void ScaleYWidget::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	Pnt.fillRect(QRect(0,0,width(),height()),Qt::white);

	Pnt.setPen(Qt::black);
	for(int i=0;i<Parent->ScaleYDimCount;i++){
		Pnt.drawText(0,Parent->ScaleYDim[i].YPos,QString::number(Parent->ScaleYDim[i].Scale));
	}
}
//-----------------------------------------------------------------------------------------

IntegrationRunningTrendForm::IntegrationRunningTrendForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
	,Window(Base,this)
	,ScaleY(Base,this)
	,ui(new Ui::IntegrationRunningTrendForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	RunningData			=NULL;
	AllocRunningDataNumb=0;
	CurrentPoint		=0;
	WPoint				=0;
	LastWTime			=0;

	for(int i=0;i<10;i++){
		for(int j=0;j<100;j++){
			Result[i][j].InspectionID=-1;
		}
	}
	Window.setParent(this);
	Window.move(ui->frameScaleY->width(),0);
	ScaleY.setParent(ui->frameScaleY);
	ScaleY.move(0,0);
	on_comboBoxSpan_currentIndexChanged(0);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationRunningTrendForm::~IntegrationRunningTrendForm()
{
	AppendData();
	Release();
    delete ui;
}

void	IntegrationRunningTrendForm::Release(void)
{
	if(RunningData!=NULL){
		delete	[]RunningData;
		RunningData			=NULL;
		AllocRunningDataNumb=0;
		CurrentPoint		=0;
		WPoint				=0;
		LastWTime			=0;
	}
}

void	IntegrationRunningTrendForm::ReadyParam(void)
{
	AllocRunningDataNumb	=20*60*60*24*93;
	CurrentPoint			=0;
	WPoint					=0;
	RunningData=new struct	RunningTrendData[AllocRunningDataNumb];

	QFile	File(GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->RunningTimeFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		int	N=File.read((char *)RunningData,sizeof(struct RunningTrendData)*AllocRunningDataNumb);
		CurrentPoint=N/sizeof(struct RunningTrendData);
		WPoint		=CurrentPoint;
	}
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int,int64,bool))
			,this,SLOT(SlotInspectionDone(int,int64,bool))
			,Qt::QueuedConnection);

	NGColor	=ui->labelNG->palette().color(QPalette::Window);
	OKColor	=ui->labelOK->palette().color(QPalette::Window);
	ResizeAction();
}

void	IntegrationRunningTrendForm::ResizeAction(void)
{
	ui->frame->resize(width(),ui->frame->height());
	Window.setGeometry(ui->frameScaleY->width(),ui->frame->height(),width()-ui->frameScaleY->width(),height()-ui->frame->height());
	ui->frameScaleY->resize(ui->frameScaleY->width(),height()-ui->frame->height());
	ScaleY.setGeometry(0,0,ui->frameScaleY->width(),ui->frameScaleY->height());
}

void	IntegrationRunningTrendForm::SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK)
{
	for(int i=0;i<100;i++){
		if(Result[SlaveNo][i].InspectionID<0){
			Result[SlaveNo][i].InspectionID=InspectionID;
			Result[SlaveNo][i].OK	=OK;
			break;
		}
	}
	int	n=0;
	bool	TotalOK=true;
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),n++){
		int	i;
		for(i=0;i<100;i++){
			if(Result[n][i].InspectionID==InspectionID){
				if(Result[n][i].OK==false){
					TotalOK=false;
				}
				break;
			}
		}
		if(i>=100){
			return;
		}
	}
	n=0;
	for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext(),n++){
		int	i;
		for(i=0;i<100;i++){
			if(Result[n][i].InspectionID==InspectionID){
				Result[n][i].InspectionID=-1;
				break;
			}
		}
	}
	QDateTime	tm=QDateTime::currentDateTime();
	struct	RunningTrendData	*f=&RunningData[CurrentPoint];
	f->Ok		=TotalOK;
	f->Second	=tm.time().second();
	f->Minute	=tm.time().minute();
	f->Hour		=tm.time().hour();
	f->Day		=tm.date().day();
	f->Month	=tm.date().month();
	f->Year		=tm.date().year()-2000;
	CurrentPoint++;
	if(CurrentPoint-WPoint>20){
		AppendData();
		Window.repaint();
	}
}

bool	IntegrationRunningTrendForm::AppendData(void)
{
	if(CurrentPoint-WPoint>0){
		int	n=CurrentPoint-WPoint;
		QFile	File(GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->RunningTimeFileName);
		if(File.open(QIODevice::Append)==true){
			int	N=File.write((const char *)&RunningData[WPoint],sizeof(struct RunningTrendData)*n);
			N/=sizeof(struct RunningTrendData);
			if(N==n){
				WPoint=CurrentPoint;
			}
			else{
				return false;
			}
		}
	}
	return true;
}

void IntegrationRunningTrendForm::on_comboBoxSpan_currentIndexChanged(int index)
{
	Window.repaint();
	ui->stackedWidget->setCurrentIndex(ui->comboBoxSpan->currentIndex());
}

int	IntegrationRunningTrendForm::GetTimeScale(void)
{
	return ui->comboBoxSpan->currentIndex();
}
