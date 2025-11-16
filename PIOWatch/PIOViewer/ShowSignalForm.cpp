#include "ShowSignalForm.h"
#include "ui_ShowSignalForm.h"
#include "PIOViewer.h"
#include <QPainter>
#include <QMouseEvent>

int	SignalHeight=19;

ShowSignalForm::ShowSignalForm(PIOViewer *parent) :
    QDialog(parent),Parent(parent),
    ui(new Ui::ShowSignalForm)
{
    ui->setupUi(this);

	int	InBitCount=Parent->GetSignalInBitCount();
	int	OutBitCount=Parent->GetSignalOutBitCount();

	IndexSignal=new ShowOneSignal*[InBitCount+OutBitCount];
	AllocIndex	=0;

	InSignal=new ShowOneSignal[InBitCount];
	int	YPoint=0;
	for(int i=0;i<InBitCount;i++){
		InSignal[i].setParent(ui->frame);
		InSignal[i].move(0,YPoint+1);
		InSignal[i].resize(ui->frame->width(),SignalHeight+1);
		InSignal[i].Set(true,i,Parent,this);
		IndexSignal[AllocIndex++]=&InSignal[i];
		YPoint+=SignalHeight+1;
	}

	OutSignal=new ShowOneSignal[OutBitCount];
	for(int i=0;i<OutBitCount;i++){
		OutSignal[i].setParent(ui->frame);
		OutSignal[i].move(0,YPoint+1);
		OutSignal[i].resize(ui->frame->width(),SignalHeight+1);
		OutSignal[i].Set(false,i,Parent,this);
		IndexSignal[AllocIndex++]=&OutSignal[i];
		YPoint+=SignalHeight+1;
	}

	ui->verticalScrollBar->setMaximum(InBitCount+OutBitCount);
}

ShowSignalForm::~ShowSignalForm()
{
	int	InBitCount=Parent->GetSignalInBitCount();
	for(int i=0;i<InBitCount;i++){
		InSignal[i].setParent(NULL);
	}

	int	OutBitCount=Parent->GetSignalOutBitCount();
	for(int i=0;i<OutBitCount;i++){
		OutSignal[i].setParent(NULL);
	}
	delete	[]InSignal;
	delete	[]OutSignal;

    delete ui;
}

void ShowSignalForm::resizeEvent ( QResizeEvent * event )
{
	ui->frame->resize(width()-ui->verticalScrollBar->width()
					 ,height()-ui->frame->geometry().y());
	ui->verticalScrollBar->move(width()-ui->verticalScrollBar->width(),ui->verticalScrollBar->geometry().y());
	ui->verticalScrollBar->resize(ui->verticalScrollBar->width()
								 ,height()-ui->verticalScrollBar->geometry().y());
	ui->horizontalScrollBar->resize(width()-ui->horizontalScrollBar->geometry().x()
									,ui->horizontalScrollBar->height());

	int	InBitCount=Parent->GetSignalInBitCount();
	for(int i=0;i<InBitCount;i++){
		InSignal[i].resize(ui->frame->width(),SignalHeight+1);
	}

	int	OutBitCount=Parent->GetSignalOutBitCount();
	for(int i=0;i<OutBitCount;i++){
		OutSignal[i].resize(ui->frame->width(),SignalHeight+1);
	}

	DWORD	LMax=Parent->GetTotalSignalMilisec();
	if(LMax==0){
		ui->horizontalScrollBar->setMaximum(100);
	}
	else{
		ui->horizontalScrollBar->setMaximum(LMax);
	}
	ui->horizontalScrollBar->setPageStep(GetZoomRate()*(width()-200));
}

int	ShowSignalForm::GetStartMilisec(void)
{
	return ui->horizontalScrollBar->value();
}
int		ShowSignalForm::GetZoomRate(void)
{
	QString	Str=ui->comboBox->currentText();
	bool	ok;
	int	ret=Str.toInt(&ok);
	if(ok==true){
		return ret;
	}
	return 1;
}
void ShowSignalForm::on_verticalScrollBar_valueChanged(int value)
{
	int	L=ui->verticalScrollBar->value();
	for(int i=0;i<L;i++){
		IndexSignal[i]->move(0,-100);
	}
	int	YPoint=0;
	for(int i=L;i<AllocIndex;i++){
		IndexSignal[i]->move(0,YPoint+1);
		YPoint+=SignalHeight+1;
	}
}

void ShowSignalForm::on_horizontalScrollBar_valueChanged(int value)
{
	ReDrawSignal();
}

void ShowSignalForm::on_comboBox_currentIndexChanged(int index)
{
	ui->horizontalScrollBar->setPageStep(GetZoomRate()*(width()-200));
	for(int i=0;i<AllocIndex;i++){
		IndexSignal[i]->ReDraw();
	}
}

void	ShowSignalForm::ReDrawSignal(void)
{
	for(int i=0;i<AllocIndex;i++){
		IndexSignal[i]->ReDraw();
	}
}

void	ShowSignalForm::ShowCurrentMilisec(void)
{
	ui->lineEditCurrentMilisec->setText(QString::number(CurrentMilisec));
}


//============================================================================
ShowOneSignal::ShowOneSignal(void)
	:SignalName(this),SignalPanel(this)
{
	SignalName.move(0,0);
	SignalName.resize(200,SignalHeight);
	SignalPanel.move(200,0);
	SignalPanel.resize(width()-200,SignalHeight);

	setFrameStyle(QFrame::Plain);
	setFrameShape(QFrame::Box);
}

void	ShowOneSignal::Set(bool _InData, int _BitNumber ,PIOViewer *VParent,ShowSignalForm *form)
{	
	Parent		=VParent;
	Form		=form;
	InData		=_InData;
	BitNumber	=_BitNumber;

	if(InData==true){
		SignalName.setText(QString("IN ")+Parent->GetSignalInName(BitNumber));
	}
	else{
		SignalName.setText(QString("Out ")+Parent->GetSignalOutName(BitNumber));
	}
}

void ShowOneSignal::resizeEvent ( QResizeEvent * event )
{
	SignalPanel.resize(width()-200,SignalHeight);
}
SignalData		*ShowOneSignal::GetSignal(void)
{
	return Parent->GetSignal(InData,BitNumber);
}

void	ShowOneSignal::ReDraw(void)
{
	SignalPanel.repaint();
}

//============================================================================
ShowSignalPanel::ShowSignalPanel(QWidget *parent)
	:QWidget(parent)
{
	setMouseTracking(true);
}
void	ShowSignalPanel::paintEvent ( QPaintEvent * )
{
	QPainter	Pnt(this);
	ShowOneSignal	*Pa=dynamic_cast<ShowOneSignal *>(parent());
	PIOViewer		*PV=Pa->GetParent();
	SignalData		*s=Pa->GetSignal();

	ShowSignalForm	*form=Pa->GetForm();
	DWORD	StartMilisec=form->GetStartMilisec();
	int		Count;

	SignalOne	*D=s->GetSignalOnePointer(StartMilisec ,Count);
	if(D!=NULL){
		int	ZoomRate=form->GetZoomRate();
		double	dZoomRate=1.0/(double)ZoomRate;
		BYTE	StateSignal=0;
		int		Index=0;
		BYTE	XData[8192];
		XData[0]=StateSignal;

		for(int x=0;x<width();x++){
			XData[x]=0;
		}
		if(Count>0){
			if(D[0].MicroSec<StartMilisec){
				if(D[0].Data==true){
					XData[0] |=1;
				}
				else{
					XData[0] |=2;
				}
			}
		}
			
		for(int Index=0;Index<Count;Index++){
			if(D[Index].MicroSec>=StartMilisec){
				int	L1=(D[Index].MicroSec-StartMilisec)*dZoomRate;
				if(Index+1<Count){
					int	L2=(D[Index+1].MicroSec-StartMilisec)*dZoomRate;
					for(int L=L1;L<=L2 && L<width();L++){
						if(D[Index].Data==true){
							XData[L] |=1;
						}
						else{
							XData[L] |=2;
						}
					}
				}
				else{
					for(int L=L1;L<width();L++){
						if(D[Index].Data==true){
							XData[L] |=1;
						}
						else{
							XData[L] |=2;
						}
					}
				}
			}
		}

		int	X;
		for(X=0;X<width();X++){
			if(XData[X]!=0){
				break;
			}
		}
		Pnt.setPen(Qt::red);
		Pnt.setBrush(QBrush(Qt::red,Qt::Dense3Pattern));
		QPoint	LastPoint(X,16);
		while(X<width()){
			int	x1;
			for(x1=X+1;x1<width();x1++){
				if(XData[x1]!=0 && XData[X]!=XData[x1]){
					break;
				}
			}
			if(XData[X]==1){
				Pnt.drawLine(LastPoint.x(),LastPoint.y(),X,3);
				Pnt.drawLine(X,3,x1,3);
				LastPoint=QPoint(x1,3);
			}
			else if(XData[X]==2){
				Pnt.drawLine(LastPoint.x(),LastPoint.y(),X,16);
				Pnt.drawLine(X,16,x1,16);
				LastPoint=QPoint(x1,16);
			}
			else if(XData[X]==3){
				Pnt.drawRect(X,3,x1-X,16-3);
				LastPoint=QPoint(x1,16);
			}
			X=x1;
		}
		Pnt.setPen(Qt::green);
		int	a=(form->CurrentMilisec-StartMilisec)*dZoomRate;
		Pnt.drawLine(a,0,a,SignalHeight);
	}

}
void	ShowSignalPanel::mouseMoveEvent ( QMouseEvent * event )
{
	ShowOneSignal	*Pa=dynamic_cast<ShowOneSignal *>(parent());
	ShowSignalForm	*form=Pa->GetForm();
	int	ZoomRate=form->GetZoomRate();
	DWORD	StartMilisec=form->GetStartMilisec();
	form->CurrentMilisec	=event->x()*ZoomRate+StartMilisec;
	form->ReDrawSignal();
	form->ShowCurrentMilisec();
}

