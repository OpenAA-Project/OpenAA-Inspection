#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(double _ThresholdBrightness ,double _ThresholdWidth ,LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	ThresholdBrightness	=_ThresholdBrightness;
	ThresholdWidth		=_ThresholdWidth;

	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	LGraph.move(0,0);
	LGraph.resize(ui->frameLineGraph->width(),ui->frameLineGraph->height());
	GraphBrightness	.SetLineColor(Qt::red);
	GraphBrightness	.SetLineWidth(1);
	GraphBrightness	.SetOffsetX(0);
	LGraph.AddGraph(&GraphBrightness);

	ui->doubleSpinBoxThresholdBrightness->setValue(ThresholdBrightness);
	ui->doubleSpinBoxThresholdWidth		->setValue(ThresholdWidth);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_doubleSpinBoxThresholdBrightness_valueChanged(double arg1)
{
	ShowGraph();
}

void SettingDialog::on_doubleSpinBoxThresholdWidth_valueChanged(double arg1)
{
	ShowGraph();
}

void SettingDialog::on_pushButtonOK_clicked()
{
	ThresholdBrightness	=ui->doubleSpinBoxThresholdBrightness	->value();
	ThresholdWidth		=ui->doubleSpinBoxThresholdWidth		->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void	SettingDialog::ShowGraph(void)
{
	double	Brightness	=ui->doubleSpinBoxThresholdBrightness	->value();
	double	Width		=ui->doubleSpinBoxThresholdWidth		->value();
	if(Width<=0.0)
		Width=0.1;
	GraphBrightness.DeleteXY();
	for(int r=0;r<256;r++){
		int	y=256/(1+exp((double)(Brightness-r)/Width));
		GraphBrightness.AddXY(r	,y);
	}
	LGraph.repaint();
}