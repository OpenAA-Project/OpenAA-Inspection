/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\ColorBrightHistogramForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyColorBlockFormResource.h"
#include "ColorBrightHistogramForm.h"
#include "XColorBlockInspection.h"
#include "XDataInLayerCommander.h"
#include "ColorBlockImagePanel.h"
#include "XDataInLayer.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ColorBrightHistogramForm::ColorBrightHistogramForm(FlexArea &area ,ColorBlockImagePanel *parentPanel 
													,int pickupRL,int pickupRH
													,int pickupGL,int pickupGH
													,int pickupBL,int pickupBH
													,QWidget *parent)
	: QDialog(parent),ServiceForLayers(parentPanel->GetLayersBase())
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	SelRButton	=new mtToolButtonColored(false ,ui.frame);
	SelGButton	=new mtToolButtonColored(false ,ui.frame);
	SelBButton	=new mtToolButtonColored(false ,ui.frame);

	SelRButton->setText(QString(/**/"Ly")+QString::number(0));
	SelRButton->setAutoExclusive(true);
	SelRButton->setCheckable(true);
	SelRButton->setAutoRaise(true);
	SelRButton->setChecked(true);
	SelRButton->setColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(0));
	SelRButton->resize(ui.toolButtonL1->width(),ui.toolButtonL1->height());
	SelRButton->move(ui.toolButtonL1->geometry().left(),ui.toolButtonL1->geometry().top());

	SelGButton->setText(QString(/**/"Ly")+QString::number(1));
	SelGButton->setAutoExclusive(true);
	SelGButton->setCheckable(true);
	SelGButton->setAutoRaise(true);
	SelGButton->setChecked(false);
	SelGButton->setColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(1));
	SelGButton->resize(ui.toolButtonL2->width(),ui.toolButtonL2->height());
	SelGButton->move(ui.toolButtonL2->geometry().left(),ui.toolButtonL2->geometry().top());

	SelBButton->setText(QString(/**/"Ly")+QString::number(2));
	SelBButton->setAutoExclusive(true);
	SelBButton->setCheckable(true);
	SelBButton->setAutoRaise(true);
	SelBButton->setChecked(false);
	SelBButton->setColor(GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(2));
	SelBButton->resize(ui.toolButtonL3->width(),ui.toolButtonL3->height());
	SelBButton->move(ui.toolButtonL3->geometry().left(),ui.toolButtonL3->geometry().top());

	connect(SelRButton,SIGNAL(clicked()),this,SLOT(on_toolButtonL1_clicked));
	connect(SelGButton,SIGNAL(clicked()),this,SLOT(on_toolButtonL2_clicked));
	connect(SelBButton,SIGNAL(clicked()),this,SLOT(on_toolButtonL3_clicked));

	delete	ui.toolButtonL1;
	delete	ui.toolButtonL2;
	delete	ui.toolButtonL3;

	GlobalArea=area;
	ParentPanel=parentPanel;
	PickupRL=pickupRL;
	PickupRH=pickupRH;
	PickupGL=pickupGL;
	PickupGH=pickupGH;
	PickupBL=pickupBL;
	PickupBH=pickupBH;
	LGraph.setParent(ui.frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui.frameLineGraph->width(),ui.frameLineGraph->height());

	GraphThreshR.SetLineColor(Qt::red);
	GraphThreshR.SetLineWidth(2);
	GraphThreshR.SetOffsetX(0);
	GraphThreshG.SetLineColor(Qt::green);
	GraphThreshG.SetLineWidth(2);
	GraphThreshG.SetOffsetX(1);
	GraphThreshB.SetLineColor(Qt::blue);
	GraphThreshB.SetLineWidth(2);
	GraphThreshB.SetOffsetX(2);

	LGraph.AddGraph(&GraphThreshR);
	LGraph.AddGraph(&GraphThreshG);
	LGraph.AddGraph(&GraphThreshB);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	GetHistogramData();
	ShowThreshold();

	parentPanel->GetLayersBase()->InstallOperationLog(this);
}

ColorBrightHistogramForm::~ColorBrightHistogramForm()
{

}

void	ColorBrightHistogramForm::Reflect(int pickupRL ,int pickupRH
										, int pickupGL ,int pickupGH
										, int pickupBL ,int pickupBH)
{
	int	iPickupRL=pickupRL;
	int	iPickupRH=pickupRH;
	if(iPickupRL<=iPickupRH){
		PickupRL=iPickupRL;
		PickupRH=iPickupRH;
	}
	int	iPickupGL=pickupGL;
	int	iPickupGH=pickupGH;
	if(iPickupGL<=iPickupGH){
		PickupGL=iPickupGL;
		PickupGH=iPickupGH;
	}
	int	iPickupBL=pickupBL;
	int	iPickupBH=pickupBH;
	if(iPickupBL<=iPickupBH){
		PickupBL=iPickupBL;
		PickupBH=iPickupBH;
	}
	ui.EditPickupRL->setValue(PickupRL);
	ui.EditPickupRH->setValue(PickupRH);
	ui.EditPickupGL->setValue(PickupGL);
	ui.EditPickupGH->setValue(PickupGH);
	ui.EditPickupBL->setValue(PickupBL);
	ui.EditPickupBH->setValue(PickupBH);
	ShowThreshold();
}

void ColorBrightHistogramForm::GetHistogramData(void)
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
	for(BrightnessMapList *d=MapList.GetFirst();d!=NULL;d=d->GetNext(),N++){
		GraphColMaster[N].DeleteXY();
		for(int i=0;i<256;i++){		
			GraphColMaster[N].AddXY(i	,d->BrightList[i]);
			MaxY=max(MaxY,d->BrightList[i]);
		}
	}
}
void	ColorBrightHistogramForm::SlotLineGraphDClick(int X,int Y)
{
	if(SelRButton->isChecked()==true){
		int	c=(PickupRL+PickupRH)/2;
		if(c>X){
			PickupRL=X;
			ui.EditPickupRL->setValue(PickupRL);
		}
		else{
			PickupRH=X;
			ui.EditPickupRH->setValue(PickupRH);
		}
	}
	else if(SelGButton->isChecked()==true){
		int	c=(PickupGL+PickupGH)/2;
		if(c>X){
			PickupGL=X;
			ui.EditPickupGL->setValue(PickupGL);
		}
		else{
			PickupGH=X;
			ui.EditPickupGH->setValue(PickupGH);
		}
	}
	else if(SelBButton->isChecked()==true){
		int	c=(PickupBL+PickupBH)/2;
		if(c>X){
			PickupBL=X;
			ui.EditPickupBL->setValue(PickupBL);
		}
		else{
			PickupBH=X;
			ui.EditPickupBH->setValue(PickupBH);
		}
	}
	ShowThreshold();
}


void ColorBrightHistogramForm::ShowThreshold(void)
{
	GraphThreshR.DeleteXY();
	GraphThreshR.AddXY(PickupRL,MaxY);
	GraphThreshR.AddXY(PickupRH,MaxY);
	GraphThreshG.DeleteXY();
	GraphThreshG.AddXY(PickupGL,MaxY);
	GraphThreshG.AddXY(PickupGH,MaxY);
	GraphThreshB.DeleteXY();
	GraphThreshB.AddXY(PickupBL,MaxY);
	GraphThreshB.AddXY(PickupBH,MaxY);
}

void ColorBrightHistogramForm::on_ButtonReflect_clicked()
{
	if(ui.EditPickupRL->value()<=ui.EditPickupRH->value()){
		PickupRL=ui.EditPickupRL->value();
		PickupRH=ui.EditPickupRH->value();
	}
	if(ui.EditPickupGL->value()<=ui.EditPickupGH->value()){
		PickupGL=ui.EditPickupGL->value();
		PickupGH=ui.EditPickupGH->value();
	}
	if(ui.EditPickupBL->value()<=ui.EditPickupBH->value()){
		PickupBL=ui.EditPickupBL->value();
		PickupBH=ui.EditPickupBH->value();
	}
	done(true);
}

void ColorBrightHistogramForm::on_ButtonClose_clicked()
{
	done(false);
}


void ColorBrightHistogramForm::on_EditPickupRL_valueChanged(int)
{
	if(PickupRH>=ui.EditPickupRL->value()){
		PickupRL=ui.EditPickupRL->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupRL->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupRL->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupRL->setValue(PickupRH);
		QPalette	Pal(ui.EditPickupRL->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupRL->setPalette(Pal);
	}
}

void ColorBrightHistogramForm::on_EditPickupRH_valueChanged(int)
{
	if(PickupRL<=ui.EditPickupRH->value()){
		PickupRH=ui.EditPickupRH->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupRH->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupRH->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupRH->setValue(PickupRL);
		QPalette	Pal(ui.EditPickupRH->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupRH->setPalette(Pal);
	}
}

void ColorBrightHistogramForm::on_EditPickupGL_valueChanged(int)
{
	if(PickupGH>=ui.EditPickupGL->value()){
		PickupGL=ui.EditPickupGL->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupGL->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupGL->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupGL->setValue(PickupGH);
		QPalette	Pal(ui.EditPickupGL->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupGL->setPalette(Pal);
	}
}

void ColorBrightHistogramForm::on_EditPickupGH_valueChanged(int)
{
	if(PickupGL<=ui.EditPickupGH->value()){
		PickupGH=ui.EditPickupGH->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupGH->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupGH->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupGH->setValue(PickupGL);
		QPalette	Pal(ui.EditPickupGH->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupGH->setPalette(Pal);
	}
}

void ColorBrightHistogramForm::on_EditPickupBL_valueChanged(int)
{
	if(PickupBH>=ui.EditPickupBL->value()){
		PickupBL=ui.EditPickupBL->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupBL->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupBL->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupBL->setValue(PickupBH);
		QPalette	Pal(ui.EditPickupBL->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupBL->setPalette(Pal);
	}
}

void ColorBrightHistogramForm::on_EditPickupBH_valueChanged(int)
{
	if(PickupBL<=ui.EditPickupBH->value()){
		PickupBH=ui.EditPickupBH->value();
		ShowThreshold();
		QPalette	Pal(ui.EditPickupBH->palette());
		Pal.setColor(QPalette::Base,Qt::white);
		ui.EditPickupBH->setPalette(Pal);
		LGraph.repaint();
	}
	else{
		//ui.EditPickupBH->setValue(PickupBL);
		QPalette	Pal(ui.EditPickupBH->palette());
		Pal.setColor(QPalette::Base,Qt::red);
		ui.EditPickupBH->setPalette(Pal);
	}
}


void ColorBrightHistogramForm::on_toolButtonL1_clicked()
{
	ShowThreshold();
	LGraph.repaint();
}

void ColorBrightHistogramForm::on_toolButtonL2_clicked()
{	
	ShowThreshold();
	LGraph.repaint();
}

void ColorBrightHistogramForm::on_toolButtonL3_clicked()
{
	ShowThreshold();
	LGraph.repaint();
}
