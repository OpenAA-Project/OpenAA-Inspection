/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "EditStatisticBlockLibraryResource.h"

#include "StatisticBrightHistogramForm.h"
#include "XStatisticBlock.h"
#include "XDataInLayerCommander.h"
#include "StatisticBlockImagePanel.h"
#include "XDataInLayer.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

StatisticBrightHistogramForm::StatisticBrightHistogramForm(FlexArea &area ,StatisticBlockImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	GlobalArea=area;
	ParentPanel=parentPanel;
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
	parentPanel->GetLayersBase()->InstallOperationLog(this);
}

StatisticBrightHistogramForm::~StatisticBrightHistogramForm()
{

}


void	StatisticBrightHistogramForm::Reflect(int pickupL ,int pickupH)
{
	PickupL=pickupL;
	PickupH=pickupH;
	ui.EditPickupL->setValue(PickupL);
	ui.EditPickupH->setValue(PickupH);
	ShowThreshold();
}

void StatisticBrightHistogramForm::GetHistogramData(void)
{
	IntList PageList;
	ParentPanel->GetLayersBase()->GetLocalPageFromArea(GlobalArea,PageList);
	if(PageList.GetFirst()==NULL)
		return;
	int	globalPage=PageList.GetFirst()->GetValue();
	GUICmdReqAreaHistgramInMaster	PacketReq(ParentPanel->GetLayersBase(),sRoot,sName,globalPage);
	IntList LayerList;
	FlexArea	A;
	A=GlobalArea;
	ParentPanel->GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);
	PacketReq.Area=A;
	ParentPanel->GetActiveLayerList(LayerList);
	int	N=0;
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext(),N++){
		GraphColMaster[N].SetLineColor(ParentPanel->GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(L->GetValue()));
		GraphColMaster[N].SetLineWidth(1);
		GraphColMaster[N].SetOffsetX(N);
		LGraph.AddGraph(&GraphColMaster[N]);
	}
	PacketReq.LayerList=LayerList;
	GUICmdSendAreaHistgramInMaster	PacketSend(ParentPanel->GetLayersBase(),QString(sRoot),QString(sName),globalPage);
	PacketReq.Send(globalPage,0,PacketSend);
	N=0;
	MaxY=0;
	for(BrightnessMapList *L=PacketSend.MapList.GetFirst();L!=NULL;L=L->GetNext(),N++){
		GraphColMaster[N].DeleteXY();
		for(int i=0;i<256;i++){		
			GraphColMaster[N].AddXY(i	,L->BrightList[i]);
			MaxY=max(MaxY,L->BrightList[i]);
		}
	}
}

void	StatisticBrightHistogramForm::SlotLineGraphDClick(int X,int Y)
{
	if(ui.radioButtonDarkSide1->isChecked()==true){
		if(PickupH>=X){
			PickupL=X;
			ui.EditPickupL->setValue(PickupL);
		}
	}
	else{
		if(PickupL<=X){
			PickupH=X;
			ui.EditPickupH->setValue(PickupH);
		}
	}
	ShowThreshold();
}


void StatisticBrightHistogramForm::ShowThreshold(void)
{
	GraphThresh.DeleteXY();
	GraphThresh.AddXY(PickupL,MaxY);
	GraphThresh.AddXY(PickupH,MaxY);
}

void StatisticBrightHistogramForm::on_EditPickupL_valueChanged(int)
{
	if(PickupH>=ui.EditPickupL->value()){
		PickupL=ui.EditPickupL->value();
		ShowThreshold();
		LGraph.repaint();
	}
	else{
		ui.EditPickupL->setValue(PickupH);
	}
}

void StatisticBrightHistogramForm::on_EditPickupH_valueChanged(int)
{
	if(PickupL<=ui.EditPickupH->value()){
		PickupH=ui.EditPickupH->value();
		ShowThreshold();
		LGraph.repaint();
	}
	else{
		ui.EditPickupH->setValue(PickupL);
	}
}

void StatisticBrightHistogramForm::on_ButtonClose_clicked()
{
	done(false);
}

void StatisticBrightHistogramForm::on_ButtonReflect_clicked()
{
	int	iPickupL=ui.EditPickupL->value();
	int	iPickupH=ui.EditPickupH->value();
	if(iPickupL<=iPickupH){
		PickupL=iPickupL;
		PickupH=iPickupH;
	}
	done(true);

}