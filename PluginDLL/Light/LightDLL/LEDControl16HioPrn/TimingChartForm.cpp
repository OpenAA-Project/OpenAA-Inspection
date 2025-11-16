#include "TimingChartForm.h"
#include "ui_TimingChartForm.h"
#include <QMenu>
#include "swap.h"

#define	SignalLineHeight	50
#define	SignalHigh			(SignalLineHeight/4)
#define	SignalLow			(3*SignalLineHeight/4)

TitlePanelWidget::TitlePanelWidget(TimingSignalPort *parent)
	:Parent(parent)\
	,LabelPortType(this),LabelPortName(this)
{
}
TitlePanelWidget::~TitlePanelWidget()
{
}

void	TitlePanelWidget::Initial(void)
{
	LabelPortType.setGeometry(0,2,190,SignalLineHeight/2-3);
	LabelPortName.setGeometry(0,SignalLineHeight/2+1,190,SignalLineHeight/2-3);

	LabelPortType.setText(Parent->Parent->Panel->HIOPortName.GetTypeName(Parent->PortType,Parent->BitNo));
	LabelPortName.setText(Parent->Parent->Panel->HIOPortName.GetString(Parent->PortType,Parent->BitNo));
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
}
SignalPanelWidget::~SignalPanelWidget()
{
}

void SignalPanelWidget::paintEvent(QPaintEvent *event)
{
	QPainter	Pnt(this);

	QBrush	B(Qt::black);
	Pnt.setBrush(B);
	Pnt.drawRect(0,0,width(),height());

	DWORD	st=Parent->Parent->GetStartTime();
	int		TimeUnit=Parent->Parent->GetTimeUnit();
	int	k=Parent->Parent->Panel->FindTiming(st);
	bool	CurrentData=false;
	if(0<k){
		struct  TimingData	*a=Parent->Parent->Panel->GetTiming(k-1);
		CurrentData=Parent->Parent->Panel->HIOPortName.GetSignal(Parent->PortType,Parent->BitNo,*a);
	}
	if(0<=k){
		int	LastX=0;
		Pnt.setPen(Qt::red);
		int	XLen=width();
		struct  TimingData	*NextP=Parent->Parent->Panel->GetTiming(k);
		for(int x=0;x<XLen;x++){
			int	s=x*TimeUnit+st;
			if(NextP!=NULL){
				bool	Both=false;
				bool	LastData=CurrentData;
				while(s>=NextP->CurrentMiliSec){
					bool	b=Parent->Parent->Panel->HIOPortName.GetSignal(Parent->PortType,Parent->BitNo,*NextP);
					if(CurrentData!=b){
						Both=true;
					}
					LastData=b;
					NextP++;
					k++;
					if(k>=Parent->Parent->Panel->WPointTiming){
						break;
					}
				}
				if(Both==true){
					if(CurrentData==true){
						Pnt.drawLine(LastX,SignalHigh,x,SignalHigh);
						Pnt.drawLine(x,SignalHigh,x,SignalLow);
					}
					else if(CurrentData==false){
						Pnt.drawLine(LastX,SignalLow,x,SignalLow);
						Pnt.drawLine(x,SignalHigh,x,SignalLow);
					}
					CurrentData=LastData;
					LastX=x;
				}
			}
		}
		if(CurrentData==true){
			Pnt.drawLine(LastX,SignalHigh,XLen-1,SignalHigh);
		}
		else{
			Pnt.drawLine(LastX,SignalLow,XLen-1,SignalLow);
		}
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

void	TimingSignalPort::Repaint(void)
{
	TitlePanel .repaint();
	SignalPanel.repaint();
}

//========================================================================

TimingChartForm::TimingChartForm(LEDControl16HioPanel *p,QWidget *parent) :
    QWidget(parent),Panel(p)
	,ui(new Ui::TimingChartForm)
{
    ui->setupUi(this);

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
}

TimingChartForm::~TimingChartForm()
{
    delete ui;
}

void TimingChartForm::resizeEvent(QResizeEvent *event)
{
	ui->scrollAreaTitle	->resize(190		,height()-24-ui->frameScale->height());
	ui->scrollAreaSignal->resize(width()-192,height()-24-ui->frameScale->height());
	WidgetTitle ->resize(ui->scrollAreaTitle->width() ,SignalCount*SignalLineHeight);
	WidgetSignal->resize(ui->scrollAreaSignal->width(),SignalCount*SignalLineHeight);
	ui->horizontalScrollBar	->resize(width()-192,24);
	ui->frameScale			->setGeometry(192,height()-24-ui->frameScale->height(),width()-192,ui->frameScale->height());
	ui->pushButtonUpdate	->setGeometry(0,height()-24-ui->frameScale->height() ,190,ui->pushButtonUpdate->height());
	for(int i=0;i<SignalCount;i++){
		TimingSignal[i]->Resize();
	}
}
	
DWORD	TimingChartForm::GetStartTime(void)
{
	return ui->horizontalScrollBar->value();
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
void TimingChartForm::on_pushButtonUpdate_clicked()
{
	if(Panel->WPointTiming>0){
		ui->horizontalScrollBar->setMinimum(Panel->TimingDim[0].CurrentMiliSec);
		ui->horizontalScrollBar->setMaximum(Panel->TimingDim[Panel->WPointTiming-1].CurrentMiliSec);
	}
}

void TimingChartForm::on_horizontalScrollBar_valueChanged(int value)
{
	for(int i=0;i<SignalCount;i++){
		TimingSignal[i]->Repaint();
	}
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