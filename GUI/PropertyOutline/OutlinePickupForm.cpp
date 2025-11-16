#include "PropertyOutlineResource.h"
#include "OutlinePickupForm.h"
#include "ui_OutlinePickupForm.h"
#include "OutlinePickupForm.h"
#include "XDataInLayer.h"

OutlinePickupForm::OutlinePickupForm(LayersBase* Base
                                    , RGBStock* Stocker
                                    , ColorLogic* ArgLogic
                                    , QWidget *parent) :
    QDialog(parent)
	, ServiceForLayers(Base)
	, ColorSamples(Base)
    ,ui(new Ui::OutlinePickupForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ColorPanel.Cube.ClearAll();
	ColorPanel.setParent(ui->frameColorCube);
	if (ArgLogic != NULL) {
		ColorPanel.Cube = *ArgLogic;
	}
	if (Stocker != NULL) {
		ColorSphere* b = new ColorSphere();
		b->Create(*Stocker);
		ColorPanel.Cube.AddBase(b);
		ColorPanel.InitializedDoneCube();
	}
	ColorPanel.Fit(ui->frameColorCube);

	ColorSamples.setParent(ui->frameColorSample);
	ColorSamples.move(0, 0);

	connect(&ColorSamples, SIGNAL(SignalBeforeSave()), this, SLOT(SlotColorSampleBeforeSave()));
	connect(&ColorSamples, SIGNAL(SignalSelectCData()), this, SLOT(SlotColorSampleSelectOne()));
	InstallOperationLog(this);
}

OutlinePickupForm::~OutlinePickupForm()
{
    delete ui;
}


void	OutlinePickupForm::SlotColorSampleBeforeSave()
{
	ColorSamples.CData.Set(ColorPanel.Cube);
}
void	OutlinePickupForm::SlotColorSampleSelectOne()
{
	ColorPanel.Cube = *ColorSamples.CData.GetColorLogic();
	ColorPanel.InitializedDoneCube();
	ColorPanel.Repaint();
}

void OutlinePickupForm::on_pushButtonClose_clicked()
{
	done((int)false);
}

void OutlinePickupForm::on_pushButtonSetToColor_clicked()
{
	done((int)true);
}

void OutlinePickupForm::on_pushButtonClearColor_clicked()
{
	ColorPanel.Cube.ClearAll();
	ColorPanel.Repaint();
}

void OutlinePickupForm::on_pushButtonClearBaseColor_clicked()
{
	ColorPanel.Cube.ClearBase();
	ColorPanel.Repaint();
}

void OutlinePickupForm::on_pushButtonClearEliminateColor_clicked()
{
	ColorPanel.Cube.ClearEliminate();
	ColorPanel.Repaint();
}

void OutlinePickupForm::on_pushButtonAddColor_clicked()
{
	if (ColorSamples.CData.GetColorLogic() != NULL) {
		ColorPanel.Cube.Add(*ColorSamples.CData.GetColorLogic());
		ColorPanel.Repaint();
	}
}

void OutlinePickupForm::on_pushButtonEliminateColor_clicked()
{
	if (ColorSamples.CData.GetColorLogic() != NULL) {
		ColorPanel.Cube.Eliminate(*ColorSamples.CData.GetColorLogic());
		ColorPanel.Repaint();
	}
}