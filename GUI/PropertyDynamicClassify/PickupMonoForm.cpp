#include "EditDynamicClassifyLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDnamicClassify\PickupMonoForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include <QPalette>
#include "PickupMonoForm.h"
#include "XDynamicClassify.h"
#include "XDataInLayerCommander.h"
#include "XDataInLayer.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PickupMonoForm::PickupMonoForm(LayersBase *Base,FlexArea &area
					,int pickupL,int pickupH
					,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);

	GlobalArea=area;
	PickupL=pickupL;
	PickupH=pickupH;
	LGraph.setParent(ui.frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui.frameLineGraph->width(),ui.frameLineGraph->height());

	GraphThresh		.SetLineColor(Qt::red);
	GraphThresh		.SetLineWidth(2);

	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	GetHistogramData();
	ShowThreshold();
	InstallOperationLog(this);
}

PickupMonoForm::~PickupMonoForm()
{

}


void	PickupMonoForm::Reflect(int pickupL ,int pickupH)
{
	PickupL=pickupL;
	PickupH=pickupH;
	ui.EditPickupL->setValue(PickupL);
	ui.EditPickupH->setValue(PickupH);
	ShowThreshold();
}

void PickupMonoForm::GetHistogramData(void)
{
	IntList PageList;
	GetLayersBase()->GetLocalPageFromArea(GlobalArea,PageList);
	if(PageList.GetFirst()==NULL)
		return;

	NPListPack<BrightnessMapList>	MapList;
	MapList.AppendList(new BrightnessMapList());

	for(IntClass *PageClass=PageList.GetFirst();PageClass!=NULL;PageClass=PageClass->GetNext()){
		int	globalPage=PageClass->GetValue();
		GUICmdReqAreaHistgramInMaster	PacketReq(GetLayersBase(),sRoot,sName,globalPage);
		FlexArea	A;
		A=GlobalArea;
		GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);
		PacketReq.Area=A;
		GUICmdSendAreaHistgramInMaster	PacketSend(GetLayersBase(),QString(sRoot),QString(sName),globalPage);
		PacketReq.Send(globalPage,0,PacketSend);

		BrightnessMapList *s=PacketSend.MapList.GetFirst();
		for(BrightnessMapList *d=MapList.GetFirst();d!=NULL && s!=NULL;d=d->GetNext(),s=s->GetNext()){
			for(int i=0;i<256;i++){
				d->BrightList[i]+=s->BrightList[i];
			}
		}
	}

	int	N=0;
	GraphColMaster[N].SetLineColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(0));
	GraphColMaster[N].SetLineWidth(1);
	GraphColMaster[N].SetOffsetX(N);
	LGraph.AddGraph(&GraphColMaster[N]);

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

void	PickupMonoForm::SlotLineGraphDClick(int X,int Y)
{
	int	c=(PickupL+PickupH)/2;
	if(c>X){
		PickupL=X;
		ui.EditPickupL->setValue(PickupL);
	}
	else{
		PickupH=X;
		ui.EditPickupH->setValue(PickupH);
	}

	ShowThreshold();
}


void PickupMonoForm::ShowThreshold(void)
{
	GraphThresh.DeleteXY();
	GraphThresh.AddXY(PickupL,MaxY);
	GraphThresh.AddXY(PickupH,MaxY);
}

void PickupMonoForm::on_ButtonReflect_clicked()
{
	int	iPickupL=ui.EditPickupL->value();
	int	iPickupH=ui.EditPickupH->value();
	if(iPickupL<=iPickupH){
		PickupL=iPickupL;
		PickupH=iPickupH;
		done(true);
	}
}

void PickupMonoForm::on_ButtonClose_clicked()
{
	done(false);
}

void PickupMonoForm::on_EditPickupL_valueChanged(int)
{
	if(PickupH>=ui.EditPickupL->value()){
		PickupL=ui.EditPickupL->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupL->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupL->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupL->setValue(PickupH);
		QPalette	Pal(ui.EditPickupL->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupL->setPalette(Pal);
	}
}

void PickupMonoForm::on_EditPickupH_valueChanged(int)
{
	if(PickupL<=ui.EditPickupH->value()){
		PickupH=ui.EditPickupH->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupH->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupH->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupH->setValue(PickupL);
		QPalette	Pal(ui.EditPickupH->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupH->setPalette(Pal);
	}
}