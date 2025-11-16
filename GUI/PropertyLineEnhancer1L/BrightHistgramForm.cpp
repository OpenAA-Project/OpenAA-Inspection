#include "PropertyLineEnhancer1LFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBlock\BrightHistogramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QPalette>
#include "BrightHistgramForm.h"
#include "ui_BrightHistgramForm.h"
#include "XLineEnhancer1L.h"
//#include "XDataInLayerCommander.h"
#include "XDataInLayer.h"
#include "swap.h"
#include "LineEnhancer1LImagePanel.h"
#include "XPropertyLineEnhancer1LPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

BrightHistgramForm::BrightHistgramForm(FlexArea &area ,LineEnhancer1LImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrightHistgramForm)
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
	parentPanel->GetLayersBase()->InstallOperationLog(this);
}

BrightHistgramForm::~BrightHistgramForm()
{
    delete ui;
}


void	BrightHistgramForm::Reflect(int pickupL ,int pickupH)
{
	PickupL=pickupL;
	PickupH=pickupH;
	ui->EditPickupL->setValue(PickupL);
	ui->EditPickupH->setValue(PickupH);
	ShowThreshold();
}

void BrightHistgramForm::GetHistogramData(void)
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

void	BrightHistgramForm::SlotLineGraphDClick(int X,int Y)
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


void BrightHistgramForm::ShowThreshold(void)
{
	GraphThresh.DeleteXY();
	GraphThresh.AddXY(PickupL,MaxY);
	GraphThresh.AddXY(PickupH,MaxY);
}

void BrightHistgramForm::on_ButtonReflect_clicked()
{
	int	iPickupL=ui->EditPickupL->value();
	int	iPickupH=ui->EditPickupH->value();
	if(iPickupL<=iPickupH){
		PickupL=iPickupL;
		PickupH=iPickupH;
		done(true);
	}
}

void BrightHistgramForm::on_ButtonClose_clicked()
{
	done(false);
}

void BrightHistgramForm::on_EditPickupL_valueChanged(int arg1)
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

void BrightHistgramForm::on_EditPickupH_valueChanged(int arg1)
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
