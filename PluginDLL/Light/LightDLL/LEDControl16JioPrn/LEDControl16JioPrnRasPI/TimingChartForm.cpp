#include "TimingChartForm.h"
#include "ui_TimingChartForm.h"
#include <QMenu>
#include <QPainter>
#include <QMouseEvent>
#include "swap.h"
#include "LEDControl16JioPrnRasPIMain.h"
#include "XCriticalFunc.h"

#define	SignalLineHeight	40
#define	SignalHigh			(SignalLineHeight/6)
#define	SignalLow			(3*SignalLineHeight/6)

TitlePanelWidget::TitlePanelWidget(TimingSignalPort *parent)
	:Parent(parent)\
    ,LabelPortType(this),LabelPortName(this),LabelCurrentValue(this)
{
}
TitlePanelWidget::~TitlePanelWidget()
{
}

void	TitlePanelWidget::Initial(void)
{
    LabelPortType   .setGeometry(0,2,160,SignalLineHeight/2-3);
    LabelPortName   .setGeometry(0,SignalLineHeight/2+1,160,SignalLineHeight/2-3);
    LabelCurrentValue.setGeometry(162,SignalLineHeight/4+1,30,SignalLineHeight/2-3);

    LabelPortType.setText(Parent->Parent->Panel->JIOPortName.GetTypeName(Parent->PortType,Parent->BitNo));
    LabelPortName.setText(Parent->Parent->Panel->JIOPortName.GetString(Parent->PortType,Parent->BitNo));
}

void TitlePanelWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QMenu	Menu;
	if(Parent->TurnN!=0)
		Menu.addAction ("Up"		, this, SLOT(SlotUpper()));
	if((Parent->TurnN+1)<Parent->Parent->SignalCount)
		Menu.addAction ("Down"		, this, SLOT(SlotLower()));
	QPoint	Q=mapToGlobal(geometry().center());
	Menu.exec(Q);
}
void    TitlePanelWidget::ShowTimeLine(DWORD TimeLine)
{
    DWORD	StartMilisec  =Parent->Parent->GetStartMilisec();
    struct  TimingData	*t=Parent->Parent->Panel->FindTimingAhead(StartMilisec+TimeLine);
    if(t!=NULL){
        bool    b=Parent->Parent->Panel->JIOPortName.GetSignal(Parent->PortType,Parent->BitNo ,*t);
        LabelCurrentValue.setText((b==true)?"1":"0");
    }
}
void	TitlePanelWidget::SlotUpper()
{
	emit	SignalUpper(Parent->ID);
}

void	TitlePanelWidget::SlotLower()
{
	emit	SignalLower(Parent->ID);
}

//========================================================================
	
SignalPanelWidget::SignalPanelWidget(TimingSignalPort *parent)
	:Parent(parent)
{
    TimeLine=0;
    setMouseTracking(true);
}
SignalPanelWidget::~SignalPanelWidget()
{
}
void    SignalPanelWidget::ShowTimeLine(DWORD _TimeLine)
{
    TimeLine=_TimeLine;
}
void SignalPanelWidget::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);

	QBrush	B(Qt::black);
	Pnt.setBrush(B);
	Pnt.drawRect(0,0,width(),height());

    Pnt.setPen(Qt::red);

    DWORD	ScrollStartMilisec  =Parent->Parent->GetScrollStartMilisec();
    int     CurrentFirstPoint   =Parent->Parent->CurrentFirstPoint;
    DWORD   CurrrentMilisec     =Parent->Parent->CurrrentMilisec;
    int     CurrentTimingCount  =Parent->Parent->CurrentTimingCount;
    int	XLen=width();
    int		TimeUnit=Parent->Parent->GetTimeUnit();
    DWORD	EndMilisec  =ScrollStartMilisec+XLen*TimeUnit;
    int     EndX=(CurrrentMilisec>=ScrollStartMilisec)?(CurrrentMilisec-ScrollStartMilisec)/TimeUnit:0;
    if(EndX>XLen)
        EndX=XLen;

    struct  TimingData	*LastT=Parent->Parent->Panel->GetTiming(CurrentFirstPoint);
    bool	LastB=Parent->Parent->Panel->JIOPortName.GetSignal(Parent->PortType,Parent->BitNo,*LastT);
    int     LastX=0;
    for(int i=1;i<CurrentTimingCount;i++){
        struct  TimingData	*t=Parent->Parent->Panel->GetTiming(CurrentFirstPoint+i);
        if(ScrollStartMilisec<=t->CurrentMiliSec){
            bool	b=Parent->Parent->Panel->JIOPortName.GetSignal(Parent->PortType,Parent->BitNo,*t);
            int     x=(t->CurrentMiliSec-ScrollStartMilisec)/TimeUnit;
            if(EndX<x){
                x=EndX;
            }
            if(LastB==true){
                Pnt.drawLine(LastX,SignalHigh,x,SignalHigh);
            }
            else{
                Pnt.drawLine(LastX,SignalLow,x,SignalLow);
            }
            if(LastB!=b){
                Pnt.drawLine(x,SignalHigh,x,SignalLow);
            }
            LastB=b;
            LastX=x;
        }
        if(EndMilisec<=t->CurrentMiliSec){
            break;
        }
    }
    if(LastX<EndX){
        if(LastB==true){
            Pnt.drawLine(LastX,SignalHigh,EndX,SignalHigh);
        }
        else{
            Pnt.drawLine(LastX,SignalLow,EndX,SignalLow);
        }
    }
    DWORD	StartMilisec  =Parent->Parent->GetStartMilisec();
    int     XTimeLine=(StartMilisec+TimeLine-ScrollStartMilisec)/TimeUnit;
    if(0<=XTimeLine && XTimeLine<XLen){
        Pnt.setPen(Qt::yellow);
        Pnt.drawLine(XTimeLine,0,XTimeLine,height());
    }
}

void SignalPanelWidget::mouseMoveEvent(QMouseEvent *event)
{
    int X=event->x();
    int Y=event->y();
    if(0<=X && X<width() && 0<=Y && Y<height()){
        int		TimeUnit=Parent->Parent->GetTimeUnit();
        DWORD	ScrollStartMilisec  =Parent->Parent->GetScrollStartMilisec();
        DWORD	StartMilisec  =Parent->Parent->GetStartMilisec();
        TimeLine=ScrollStartMilisec+X*TimeUnit-StartMilisec;
        Parent->Parent->ShowTimeLine(TimeLine);
    }
}

//========================================================================

TimingSignalPort::TimingSignalPort(TimingChartForm *p,int id,int _PortType ,int _BitNo)
	:QObject(p)
	,Parent(p)
	,ID(id)
	,TitlePanel(this)
	,SignalPanel(this)
{
	PortType=_PortType;
	BitNo	=_BitNo;
	TurnN	=0;
}
TimingSignalPort::~TimingSignalPort()
{
}

void	TimingSignalPort::Initial(void)
{
	TitlePanel.Initial();
	connect(&TitlePanel,SIGNAL(SignalUpper(int)),Parent,SLOT(SlotUpper(int)));
	connect(&TitlePanel,SIGNAL(SignalLower(int)),Parent,SLOT(SlotLower(int)));
}
void	TimingSignalPort::SetTurn(int n ,QWidget *WidgetSignal ,QWidget *WidgetTitle)
{
	TurnN	=n;
	TitlePanel .setParent(WidgetTitle );
	SignalPanel.setParent(WidgetSignal);
	TitlePanel.Initial();
	Resize();
}

void	TimingSignalPort::Resize(void)
{
	TitlePanel .setGeometry(0,TurnN*SignalLineHeight,Parent->WidgetTitle ->width(),SignalLineHeight);
	SignalPanel.setGeometry(0,TurnN*SignalLineHeight,Parent->WidgetSignal->width(),SignalLineHeight);

	TitlePanel.show();
	SignalPanel.show();
}
void    TimingSignalPort::ShowTimeLine(DWORD TimeLine)
{
    TitlePanel .ShowTimeLine(TimeLine);
    SignalPanel.ShowTimeLine(TimeLine);
}
void	TimingSignalPort::Repaint(void)
{
	TitlePanel .repaint();
	SignalPanel.repaint();
}

void	TimingSignalPort::RepaintSignal(void)
{
    SignalPanel.repaint();
}

//========================================================================
const   int frameScaleHeight=24;

SignalScale::SignalScale(TimingChartForm *p,QWidget *parent)
    :QWidget(parent),Parent(p)
{
    TimeLine=0;
}

void SignalScale::paintEvent(QPaintEvent *event)
{
    QPainter	Pnt(this);

    QBrush	B(Qt::lightGray);
    Pnt.setBrush(B);
    Pnt.drawRect(0,0,width(),height());

    QBrush	BChar(Qt::black);
    Pnt.setBrush(BChar);

    DWORD	StartMilisec  =Parent->GetStartMilisec();
    DWORD	ScrollStartMilisec  =Parent->GetScrollStartMilisec();
    int	XLen=width();
    int		TimeUnit=Parent->GetTimeUnit();
    DWORD   TermMilisec =XLen*TimeUnit;
    DWORD	EndMilisec  =ScrollStartMilisec+TermMilisec;

    int     XTimeLine=(StartMilisec+TimeLine-ScrollStartMilisec)/TimeUnit;
    if(0<=XTimeLine && XTimeLine<XLen){
        Pnt.setPen(Qt::yellow);
        Pnt.drawText(XTimeLine,frameScaleHeight,QString::number(TimeLine));
    }

    Pnt.setPen(Qt::red);
    Pnt.drawLine(0,2,XLen,2);

    for(int d=1;d<=1000;d=d*10){
        int n=TermMilisec/d;
        if(1<n && n<15){
            DWORD   St=((ScrollStartMilisec-StartMilisec)/d)*d;
            for(int i=0;i<n;i++){
                if(ScrollStartMilisec<=(StartMilisec+St)){
                    int X=(StartMilisec+St-ScrollStartMilisec)/TimeUnit;
                    Pnt.setPen(Qt::red);
                    Pnt.drawLine(X,0,X,5);
                    Pnt.setPen(Qt::black);
                    QString s=QString::number(St);
                    Pnt.drawText(X,frameScaleHeight,s);
                }
                else if(i==0){

                }
                St+=d;
            }
            return;
        }
    }
    for(int d=5;d<=1000;d=d*10){
        int n=TermMilisec/d;
        if(0<n && n<15){
            DWORD   St=((ScrollStartMilisec-StartMilisec)/d)*d;
            for(int i=0;i<n;i++){
                if(ScrollStartMilisec<=(StartMilisec+St)){
                    int X=(StartMilisec+St-ScrollStartMilisec)/TimeUnit;
                    Pnt.setPen(Qt::red);
                    Pnt.drawLine(X,0,X,5);
                    QString s=QString::number(St);
                    Pnt.drawText(X,frameScaleHeight,s);
                }
                else if(i==0){

                }
                St+=d;
            }
            return;
        }
    }
    for(long d=10000;d<=100000;d=d*10){
        int n=TermMilisec/d;
        if(1<n && n<15){
            DWORD   St=((ScrollStartMilisec-StartMilisec)/d)*d;
            for(int i=0;i<n;i++){
                if(ScrollStartMilisec<=(StartMilisec+St)){
                    int X=(StartMilisec+St-ScrollStartMilisec)/TimeUnit;
                    Pnt.setPen(Qt::red);
                    Pnt.drawLine(X,0,X,5);
                    double  fSt=St/1000.0;
                    QString s=QString::number(fSt,'f',1);
                    Pnt.drawText(X,frameScaleHeight,s);
                }
                else if(i==0){

                }
                St+=d;
            }
            return;
        }
    }
    for(long d=10000;d<=100000;d=d*10){
        int n=TermMilisec/d;
        if(0<n && n<15){
            DWORD   St=((ScrollStartMilisec-StartMilisec)/d)*d;
            for(int i=0;i<n;i++){
                if(ScrollStartMilisec<=(StartMilisec+St)){
                    int X=(StartMilisec+St-ScrollStartMilisec)/TimeUnit;
                    Pnt.setPen(Qt::red);
                    Pnt.drawLine(X,0,X,5);
                    double  fSt=St/1000.0;
                    QString s=QString::number(fSt,'f',1);
                    Pnt.drawText(X,frameScaleHeight,s);
                }
                else if(i==0){

                }
                St+=d;
            }
            return;
        }
    }
}
//========================================================================

TimingChartForm::TimingChartForm(LEDControl16JioPrnRasPIMain *p,QWidget *parent) :
    QWidget(parent),Panel(p)
	,ui(new Ui::TimingChartForm)
{
    ui->setupUi(this);
    CurrentFirstPoint   =0;
    CurrrentMilisec     =::GetComputerMiliSec();
    CurrentTimingCount  =0;

	int	n=0;
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIOAIN,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIOBIN,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIOCIN,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIODIN,i);
	}

	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIOAOUT,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIOBOUT,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIOCOUT,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortPIODOUT,i);
	}

	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortGIN,i);
	}
	for(int i=0;i<8;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortGOUT,i);
	}
	for(int i=0;i<4;i++,n++){
		TimingSignal[n]=new TimingSignalPort(this,n,DefPortTRGIN,i);
	}
	TimingSignal[n]=new TimingSignalPort(this,n,DefPortOuterSW,0);
	n++;
	TimingSignal[n]=new TimingSignalPort(this,n,DefPortExtDirect,0);
	n++;
	SignalCount=n;

	WidgetSignal=new QWidget();
	WidgetTitle =new QWidget();


	WidgetTitle ->setGeometry(0,0,ui->scrollAreaTitle->width() ,SignalCount*SignalLineHeight);
	WidgetSignal->setGeometry(0,0,ui->scrollAreaSignal->width(),SignalCount*SignalLineHeight);
	
	ui->scrollAreaSignal	->setWidget(WidgetSignal);
	ui->scrollAreaTitle		->setWidget(WidgetTitle);
	WidgetTitle	->show();
	WidgetSignal->show();

	//ui->scrollAreaSignal	->show();
	//ui->scrollAreaTitle		->show();

	for(int i=0;i<SignalCount;i++){
		TimingSignal[i]->SetTurn(i ,WidgetSignal ,WidgetTitle);
	}
	on_pushButtonUpdate_clicked();

	QScrollBar *VScrol=ui->scrollAreaTitle->verticalScrollBar();
	if(VScrol!=NULL){
		connect(VScrol,SIGNAL(valueChanged(int)),this,SLOT(SlotVScrollChanged(int)));
	}

    Scale   =new SignalScale(this,this);
    Scale->setParent(this);

    TimingVerticalScroller  =ui->scrollAreaSignal->verticalScrollBar();
    connect(TimingVerticalScroller,SIGNAL(valueChanged(int)),this,SLOT(SlotTimingValueChanged(int)));

    TitleVerticalScroller  =ui->scrollAreaTitle->verticalScrollBar();
    connect(TitleVerticalScroller,SIGNAL(valueChanged(int)),this,SLOT(SlotTitleValueChanged(int)));

    SamplingMode=ui->toolButtonSampling->isChecked();
}

TimingChartForm::~TimingChartForm()
{
    delete ui;
}

void TimingChartForm::resizeEvent(QResizeEvent *event)
{
    ui->scrollAreaTitle	->resize(190		,height()-24-frameScaleHeight);
    ui->scrollAreaSignal->resize(width()-192,height()-24-frameScaleHeight);
	WidgetTitle ->resize(ui->scrollAreaTitle->width() ,SignalCount*SignalLineHeight);
	WidgetSignal->resize(ui->scrollAreaSignal->width(),SignalCount*SignalLineHeight);
	ui->horizontalScrollBar	->resize(width()-192,24);
    Scale			->setGeometry(192,height()-frameScaleHeight,width()-192,frameScaleHeight);
    ui->frameOperation	->setGeometry(0,height()-24 ,190,ui->frameOperation->height());
	for(int i=0;i<SignalCount;i++){
		TimingSignal[i]->Resize();
	}
    Scale->show();
}

void TimingChartForm::on_pushButtonUpdate_clicked()
{
}

void TimingChartForm::on_pushButtonClear_clicked()
{
    Panel->ClearTiming();
}

void TimingChartForm::on_horizontalScrollBar_valueChanged(int value)
{
    RepaintSignals();
    Scale->repaint();
}

void TimingChartForm::SlotVScrollChanged(int)
{
	QScrollBar *VScrol=ui->scrollAreaTitle->verticalScrollBar();
	if(VScrol!=NULL){
		int	n=VScrol->value();
		QScrollBar *VdScrol=ui->scrollAreaSignal->verticalScrollBar();
		if(VdScrol!=NULL){
			VdScrol->setValue(n);
		}
	}
}
	
void	TimingChartForm::SlotUpper(int id)
{
	int	IndexA=-1;
	int	TurnA=-1;
	for(int i=0;i<SignalCount;i++){
		if(TimingSignal[i]->ID==id){
			TurnA=TimingSignal[i]->TurnN;
			IndexA=i;
			break;
		}
	}
	int	IndexB=-1;
	if(TurnA>0){
		for(int i=0;i<SignalCount;i++){
			if(TimingSignal[i]->TurnN==(TurnA-1)){
				IndexB=i;
				break;
			}
		}
	}
	if(IndexA>=0 && IndexB>=0){
		swap(TimingSignal[IndexA]->TurnN,TimingSignal[IndexB]->TurnN);
		TimingSignal[IndexA]->Resize();
		TimingSignal[IndexB]->Resize();
	}
}

void	TimingChartForm::SlotLower(int id)
{
	int	IndexA=-1;
	int	TurnA=-1;
	for(int i=0;i<SignalCount;i++){
		if(TimingSignal[i]->ID==id){
			TurnA=TimingSignal[i]->TurnN;
			IndexA=i;
			break;
		}
	}
	int	IndexB=-1;
	if(TurnA>0){
		for(int i=0;i<SignalCount;i++){
			if(TimingSignal[i]->TurnN==(TurnA+1)){
				IndexB=i;
				break;
			}
		}
	}
	if(IndexA>=0 && IndexB>=0){
		swap(TimingSignal[IndexA]->TurnN,TimingSignal[IndexB]->TurnN);
		TimingSignal[IndexA]->Resize();
		TimingSignal[IndexB]->Resize();
	}
}

bool    TimingChartForm::GetSamplingMode(void)
{
    //return ui->toolButtonSampling->isChecked();
    return SamplingMode;
}
DWORD   TimingChartForm::GetStartMilisec(void)
{
    DWORD   FirstMilisec=Panel->GetTiming(CurrentFirstPoint)->CurrentMiliSec;
    return FirstMilisec;
}
DWORD	TimingChartForm::GetScrollStartMilisec(void)
{
    DWORD   FirstMilisec=Panel->GetTiming(CurrentFirstPoint)->CurrentMiliSec;
    int     v=ui->horizontalScrollBar->value();
    return FirstMilisec+v*GetTimeUnit();
}

int		TimingChartForm::GetTimeUnit(void)
{
    switch(ui->comboBoxTimeUnit->currentIndex()){
    case 0:	return 1;
    case 1:	return 10;
    case 2:	return 100;
    case 3:	return 1000;
    }
    return 1;
}
void	TimingChartForm::RepaintSignals(void)
{
    if(GetSamplingMode()==true){
        CurrentFirstPoint   =Panel->GetFirstTimingPoint();
        CurrrentMilisec     =::GetComputerMiliSec();
        CurrentTimingCount  =Panel->GetTimingCount();
    }
    DWORD   FirstMilisec=Panel->GetTiming(CurrentFirstPoint)->CurrentMiliSec;
    //DWORD   LastMilisec=Panel->GetTiming(CurrentFirstPoint+CurrentTimingCount-1)->CurrentMiliSec;
    DWORD   TimeLen=(CurrrentMilisec-FirstMilisec)/GetTimeUnit()+width()/2;
    ui->horizontalScrollBar->setMaximum(TimeLen);

    for(int i=0;i<SignalCount;i++){
        TimingSignal[i]->RepaintSignal();
    }
}

void    TimingChartForm::ShowTimeLine(DWORD TimeLine)
{
    for(int i=0;i<SignalCount;i++){
        TimingSignal[i]->ShowTimeLine(TimeLine);
        TimingSignal[i]->RepaintSignal();
    }
    Scale->TimeLine=TimeLine;
    Scale->repaint();
}
void    TimingChartForm::SlotTimingValueChanged(int v)
{
    QScrollBar *tscroller=ui->scrollAreaTitle->verticalScrollBar();
    if(tscroller!=NULL){
        tscroller->setValue(v);
    }
}
void    TimingChartForm::SlotTitleValueChanged(int v)
{
    QScrollBar *tscroller=ui->scrollAreaSignal->verticalScrollBar();
    if(tscroller!=NULL){
        tscroller->setValue(v);
    }
}

void TimingChartForm::on_toolButtonSampling_clicked()
{
    SamplingMode=ui->toolButtonSampling->isChecked();
}
