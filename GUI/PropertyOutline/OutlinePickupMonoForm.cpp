#include "PropertyOutlineResource.h"
#include "OutlinePickupMonoForm.h"
#include "ui_OutlinePickupMonoForm.h"
#include "XOutlineInspect.h"
//#include "XDataInLayerCommander.h"
#include "OutlineImagePanel.h"
#include "XDataInLayer.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

OutlinePickupMonoForm::OutlinePickupMonoForm(FlexArea& area, OutlineImagePanel* parentPanel, int pickupL, int pickupH, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OutlinePickupMonoForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	GlobalArea = area;
	ParentPanel = parentPanel;
	PickupL = pickupL;
	PickupH = pickupH;

	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0, 0);
	LGraph.resize(ui->frameLineGraph->width(), ui->frameLineGraph->height());

	GraphThresh.SetLineColor(Qt::red);
	GraphThresh.SetLineWidth(2);

	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph, SIGNAL(SignalLineGraphDClick(int, int)), this, SLOT(SlotLineGraphDClick(int, int)));

	GetHistogramData();
	ShowThreshold();

	ui->EditPickupL->setValue(PickupL);
	ui->EditPickupH->setValue(PickupH);
	parentPanel->GetLayersBase()->InstallOperationLog(this);
}

OutlinePickupMonoForm::~OutlinePickupMonoForm()
{
    delete ui;
}

void	OutlinePickupMonoForm::Reflect(int pickupL, int pickupH)
{
	PickupL = pickupL;
	PickupH = pickupH;
	ui->EditPickupL->setValue(PickupL);
	ui->EditPickupH->setValue(PickupH);
	ShowThreshold();
}

void OutlinePickupMonoForm::GetHistogramData(void)
{
	IntList PageList;
	ParentPanel->GetLayersBase()->GetLocalPageFromArea(GlobalArea, PageList);
	if (PageList.GetFirst() == NULL)
		return;

	IntList	LayerList;
	ParentPanel->GetActiveLayerList(LayerList);

	BrightnessMapList	BMap;
	for (IntClass* PageClass = PageList.GetFirst(); PageClass != NULL; PageClass = PageClass->GetNext()) {
		int	globalPage = PageClass->GetValue();
		GUICmdReqAreaHistgramInMaster	PacketReq(ParentPanel->GetLayersBase(), sRoot, sName, globalPage);
		FlexArea	A;
		A = GlobalArea;
		ParentPanel->GetLayersBase()->GetPageData(globalPage)->ClipMoveAreaFromGlobal(A);
		PacketReq.Area = A;
		GUICmdSendAreaHistgramInMaster	PacketSend(ParentPanel->GetLayersBase(), QString(sRoot), QString(sName), globalPage);
		PacketReq.Send(globalPage, 0, PacketSend);

		BrightnessMapList* s;
		if (LayerList.GetFirst() != NULL) {
			s = PacketSend.MapList.GetItem(LayerList.GetFirst()->GetValue());
		}
		else {
			s = PacketSend.MapList.GetItem(0);
		}
		for (int i = 0; i < 256; i++) {
			BMap.BrightList[i] += s->BrightList[i];
		}
	}

	GraphColMaster.SetLineColor(ParentPanel->GetLayersBase()->GetParamGlobal()->GetOneGraphLayerColor(0));
	GraphColMaster.SetLineWidth(1);
	GraphColMaster.SetOffsetX(0);
	LGraph.AddGraph(&GraphColMaster);

	MaxY = 0;
	GraphColMaster.DeleteXY();
	for (int i = 0; i < 256; i++) {
		GraphColMaster.AddXY(i, BMap.BrightList[i]);
		MaxY = max(MaxY, BMap.BrightList[i]);
	}
}
void	OutlinePickupMonoForm::SlotLineGraphDClick(int X, int Y)
{
	if (ui->radioButtonDarkSide1->isChecked() == true) {
		if (PickupH >= X) {
			PickupL = X;
			ui->EditPickupL->setValue(PickupL);
		}
	}
	else {
		if (PickupL <= X) {
			PickupH = X;
			ui->EditPickupH->setValue(PickupH);
		}
	}
	ShowThreshold();
}

void OutlinePickupMonoForm::ShowThreshold(void)
{
	GraphThresh.DeleteXY();
	GraphThresh.AddXY(PickupL, MaxY);
	GraphThresh.AddXY(PickupH, MaxY);
}

void OutlinePickupMonoForm::on_ButtonReflect_clicked()
{
	int	iPickupL = ui->EditPickupL->value();
	int	iPickupH = ui->EditPickupH->value();
	if (iPickupL <= iPickupH) {
		PickupL = iPickupL;
		PickupH = iPickupH;
	}
	done(true);
}

void OutlinePickupMonoForm::on_ButtonClose_clicked()
{
	done(false);
}

void OutlinePickupMonoForm::on_EditPickupL_valueChanged(int)
{
	if (PickupH >= ui->EditPickupL->value()) {
		PickupL = ui->EditPickupL->value();
		ShowThreshold();
		LGraph.repaint();
	}
	else {
		ui->EditPickupL->setValue(PickupH);
	}
}

void OutlinePickupMonoForm::on_EditPickupH_valueChanged(int)
{
	if (PickupL <= ui->EditPickupH->value()) {
		PickupH = ui->EditPickupH->value();
		ShowThreshold();
		LGraph.repaint();
	}
	else {
		ui->EditPickupH->setValue(PickupL);
	}
}