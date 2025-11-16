#include "EulerRingL1PickupForm.h"
#include "ui_EulerRingL1PickupForm.h"
#include "XEulerRingL1.h"
//#include "XDataInLayerCommander.h"
#include "XDataInLayer.h"
#include "swap.h"
#include "EulerRingL1ImagePanel.h"
#include "XPropertyEulerRingL1Packet.h"

extern	char	*sRoot;
extern	char	*sName;

EulerRingL1PickupForm::EulerRingL1PickupForm(FlexArea &area ,EulerRingL1ImagePanel *parentPanel ,int pickupL,int pickupH, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EulerRingL1PickupForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);
	GlobalArea=area;
	ParentPanel=parentPanel;
	PickupL=pickupL;
	PickupH=pickupH;
	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui->frameLineGraph->width(),ui->frameLineGraph->height());

	GraphThresh		.SetLineColor(Qt::red);
	GraphThresh		.SetLineWidth(2);

	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	GetHistogramData();
	ShowThreshold();
}

EulerRingL1PickupForm::~EulerRingL1PickupForm()
{
    delete ui;
}

void	EulerRingL1PickupForm::Reflect(int pickupL ,int pickupH)
{
	PickupL=pickupL;
	PickupH=pickupH;
	ui->EditPickupL->setValue(PickupL);
	ui->EditPickupH->setValue(PickupH);
	ShowThreshold();
}

void EulerRingL1PickupForm::GetHistogramData(void)
{
	IntList PageList;
	ParentPanel->GetLayersBase()->GetLocalPageFromArea(GlobalArea,PageList);
	if(PageList.GetFirst()==NULL)
		return;

	IntList LayerList;
	ParentPanel->GetActiveLayerList(LayerList);
	NPListPack<BrightnessMapList>	MapList;
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		MapList.AppendList(new BrightnessMapList());
	}

	for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
		int	globalPage=PageClass->GetValue();
		GUICmdReqAreaHistgramInMaster	PacketReq(ParentPanel->GetLayersBase(),sRoot,sName,globalPage);
		FlexArea	A;
		A=GlobalArea;
		ParentPanel->GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);
		PacketReq.Area=A;
		PacketReq.LayerList=LayerList;
		GUICmdSendAreaHistgramInMaster	PacketSend(ParentPanel->GetLayersBase(),QString(sRoot),QString(sName),globalPage);
		PacketReq.Send(globalPage,0,PacketSend);

		BrightnessMapList *s=PacketSend.MapList.GetFirst();
		for(BrightnessMapList *d=MapList.GetFirst();d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
			for(int i=0;i<256;i++){
				d->BrightList[i]+=s->BrightList[i];
			}
		}
	}

	int	N=0;
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext(),N++){
		GraphColMaster[N].SetLineColor(ParentPanel->GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(L->GetValue()));
		GraphColMaster[N].SetLineWidth(1);
		GraphColMaster[N].SetOffsetX(N);
		LGraph.AddGraph(&GraphColMaster[N]);
	}
	N=0;
	MaxY=0;
	for(BrightnessMapList *d=MapList.GetFirst();d!=NULL;d=d->GetNext()){
		GraphColMaster[N].DeleteXY();
		for(int i=0;i<256;i++){		
			GraphColMaster[N].AddXY(i	,d->BrightList[i]);
			MaxY=max(MaxY,d->BrightList[i]);
		}
	}
}

void	EulerRingL1PickupForm::SlotLineGraphDClick(int X,int Y)
{
	int	c=(PickupL+PickupH)/2;
	if(c>X){
		PickupL=X;
		ui->EditPickupL->setValue(PickupL);
	}
	else{
		PickupH=X;
		ui->EditPickupH->setValue(PickupH);
	}

	ShowThreshold();
}


void EulerRingL1PickupForm::ShowThreshold(void)
{
	GraphThresh.DeleteXY();
	GraphThresh.AddXY(PickupL,MaxY);
	GraphThresh.AddXY(PickupH,MaxY);
}

void EulerRingL1PickupForm::on_ButtonReflect_clicked()
{
	int	iPickupL=ui->EditPickupL->value();
	int	iPickupH=ui->EditPickupH->value();
	if(iPickupL<=iPickupH){
		PickupL=iPickupL;
		PickupH=iPickupH;
		done(true);
	}
}

void EulerRingL1PickupForm::on_ButtonClose_clicked()
{
	done(false);
}

void EulerRingL1PickupForm::on_EditPickupL_valueChanged(int arg1)
{
	if(PickupH>=ui->EditPickupL->value()){
		PickupL=ui->EditPickupL->value();
		ShowThreshold();
		QPalette	Pal(ui->EditPickupL->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui->EditPickupL->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui->EditPickupL->setValue(PickupH);
		QPalette	Pal(ui->EditPickupL->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui->EditPickupL->setPalette(Pal);
	}
}

void EulerRingL1PickupForm::on_EditPickupH_valueChanged(int arg1)
{
	if(PickupL<=ui->EditPickupH->value()){
		PickupH=ui->EditPickupH->value();
		ShowThreshold();
		QPalette	Pal(ui->EditPickupH->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui->EditPickupH->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui->EditPickupH->setValue(PickupL);
		QPalette	Pal(ui->EditPickupH->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui->EditPickupH->setPalette(Pal);
	}
}
