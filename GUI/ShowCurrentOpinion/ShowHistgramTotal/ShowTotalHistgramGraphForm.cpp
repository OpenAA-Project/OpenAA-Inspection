#include "ShowTotalHistgramGraphForm.h"
#include "ui_ShowTotalHistgramGraphForm.h"
#include <QString>
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "swap.h"

extern	char	*sRoot;
extern	char	*sName;

ShowTotalHistgramGraphForm::ShowTotalHistgramGraphForm(HistgramTypeList &PointH ,LibraryItemList &PointL,LayersBase *base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowTotalHistgramGraphForm) ,ServiceForLayers(base)
{
    ui->setupUi(this);
	HistPoint	=PointH;
	LibPoint	=PointL;

	LGraph.setParent(ui->frame);
	LGraph.SetScaleTypeY(mtLineGraph::mtLog);
	LGraph.move(0,0);
	LGraph.resize(ui->frame->width(),ui->frame->height());

	GraphHistgram	.SetLineColor(GetParamGlobal()->HistgramGraphColor);
	GraphHistgram	.SetLineWidth(1);
	GraphHistgram	.SetOffsetX(0);
	GraphThresh		.SetLineColor(GetParamGlobal()->HistgramThreshColor);	
	GraphThresh		.SetLineWidth(1);
	GraphThresh		.SetOffsetX(2);

	LGraph.AddGraph(&GraphHistgram);
	LGraph.AddGraph(&GraphThresh);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	ui->lineEditAlgoRoot->setText(PointH.AlgoRoot);
	ui->lineEditAlgoName->setText(PointH.AlgoName);
	ui->lineEditLibID	->setText(QString::number(PointL.LibID));
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(PointH.AlgoRoot,PointH.AlgoName);
	if(ABase!=NULL){
		QString	LibName=ABase->GetLibraryContainer()->GetLibraryName(PointL.LibID);
		ui->lineEditLibName	->setText(LibName);
	}
	ui->lineEditHistName->setText(PointH.HistName);
	Initial();
}

ShowTotalHistgramGraphForm::~ShowTotalHistgramGraphForm()
{
    delete ui;
}

void ShowTotalHistgramGraphForm::Initial(void)
{
	GraphData.Clear();
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqHistgramTotalData	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		GUICmdSendHistgramTotalData	SCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
		RCmd.PointData	=HistPoint;
		RCmd.LibData	=LibPoint;
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			GraphData+=SCmd.Data;
		}
	}
	ThresholdA	=GraphData.GetMinData();
	ThresholdB	=GraphData.GetMaxData();

	Average		=GraphData.GetAverage();
	Dispersion	=GraphData.GetDispersion();

	ui->lineEditNumCenter	->setText(QString::number(Average));
	ui->lineEditNumDev		->setText(QString::number(sqrt(Dispersion)));

	ShowGrah();
}

void ShowTotalHistgramGraphForm::ShowGrah(void)
{
	GraphHistgram.DeleteXY();
	GraphThresh.DeleteXY();

	for(int i=0;i<GraphData.GetDimCount();i++){
		GraphHistgram.AddXY(GraphData.GetMinData()+i*GraphData.GetStep(),GraphData.GetHistData(i));
	}
	GraphThresh.AddXY(ThresholdA,GraphData.GetMaxData());
	GraphThresh.AddXY(ThresholdB,GraphData.GetMaxData());
}

void	ShowTotalHistgramGraphForm::SlotLineGraphDClick(int X,int Y)
{
	if(ui->toolButtonThreshold1->isChecked()==true){
		ThresholdA=X;
	}
	else if(ui->toolButtonThreshold2->isChecked()==true){
		ThresholdB=X;
	}
	if(ThresholdA>ThresholdB){
		swap(ThresholdA,ThresholdB);
	}
	ShowCalculated();
	ShowGrah();
	LGraph.repaint();
}

void ShowTotalHistgramGraphForm::ShowCalculated(void)
{
	ui->lineEditThresh1->setText(QString::number(ThresholdA));
	ui->lineEditThresh2->setText(QString::number(ThresholdB));
}

void ShowTotalHistgramGraphForm::on_pushButtonClose_clicked()
{
	done(true);
}

void ShowTotalHistgramGraphForm::on_pushButtonCalc_clicked()
{
	bool	ok;
	double	d1=ui->lineEditThresh1->text().toDouble(&ok);
	if(ok==true){
		ThresholdA=d1;
	}
	double	d2=ui->lineEditThresh2->text().toDouble(&ok);
	if(ok==true){
		ThresholdB=d2;
	}
	double	d=GraphData.RealPercentage(ThresholdA,ThresholdB);
	ui->lineEditNumPercent->setText(QString::number(d));
}

void ShowTotalHistgramGraphForm::on_pushButtonCalc2_clicked()
{
	double	DRate=0;
	bool	ok;
	double	d1=ui->lineEditNumPercent->text().toDouble(&ok);
	if(ok==true){
		DRate=d1;
	}
	GraphData.GetRealThreshold((1.0-DRate)/2.0,(1.0-DRate)/2.0
								,ThresholdA,ThresholdB);
	ui->lineEditThresh1->setText(QString::number(ThresholdA));
	ui->lineEditThresh2->setText(QString::number(ThresholdB));
	ShowGrah();
}

void ShowTotalHistgramGraphForm::on_pushButtonCalcD_clicked()
{
	bool	ok;
	double	d1=ui->lineEditThresh1->text().toDouble(&ok);
	if(ok==true){
		ThresholdA=d1;
	}
	double	d2=ui->lineEditThresh2->text().toDouble(&ok);
	if(ok==true){
		ThresholdB=d2;
	}
	double	d=GraphData.IdealPercentage(ThresholdA,ThresholdB);
	ui->lineEditNumPercent->setText(QString::number(d));
}

void ShowTotalHistgramGraphForm::on_pushButtonCalcU_clicked()
{
	double	DRate=0;
	bool	ok;
	double	d1=ui->lineEditNumPercent->text().toDouble(&ok);
	if(ok==true){
		DRate=d1;
	}
	GraphData.GetIdealThreshold(DRate/2.0,DRate/2.0
								,ThresholdA,ThresholdB);
	ui->lineEditThresh1->setText(QString::number(ThresholdA));
	ui->lineEditThresh2->setText(QString::number(ThresholdB));
	ShowGrah();
}
