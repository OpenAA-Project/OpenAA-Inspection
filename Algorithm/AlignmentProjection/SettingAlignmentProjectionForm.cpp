#include "SettingAlignmentProjectionForm.h"
#include "ui_SettingAlignmentProjectionForm.h"
#include "XDataInLayerCommander.h"
#include "XGeneralDialog.h"
#include "swap.h"

extern	char	*sRoot;
extern	char	*sName;

SettingAlignmentProjectionForm::SettingAlignmentProjectionForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::SettingAlignmentProjectionForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	OnChanging=false;
	IData=NULL;

	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	LGraph.move(0,0);
	LGraph.resize(ui->frameLineGraph->width(),ui->frameLineGraph->height());

	QColor	MasterColor=Qt::green;
	QColor	ThreshColorM=Qt::magenta;
	QColor	TargetColor=Qt::yellow;
	QColor	ThreshColorT=Qt::red;

	GraphMapTarget	.SetLineColor(MasterColor);
	GraphMapTarget	.SetLineWidth(1);
	GraphMapTarget	.SetOffsetX(0);
	GraphMapMaster	.SetLineColor(TargetColor);
	GraphMapMaster	.SetLineWidth(1);
	GraphMapMaster	.SetOffsetX(1);
	GraphPeakMaster		.SetLineColor(ThreshColorM);	
	GraphPeakMaster		.SetLineWidth(1);
	GraphPeakMaster		.SetOffsetX(0);
	GraphPeakTarget		.SetLineColor(ThreshColorT);	
	GraphPeakTarget		.SetLineWidth(1);
	GraphPeakTarget		.SetOffsetX(1);

	LGraph.AddGraph(&GraphMapTarget);
	LGraph.AddGraph(&GraphMapMaster);
	LGraph.AddGraph(&GraphPeakMaster);
	LGraph.AddGraph(&GraphPeakTarget);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));


	InstallOperationLog(this);
}

SettingAlignmentProjectionForm::~SettingAlignmentProjectionForm()
{
    delete ui;
}

void	SettingAlignmentProjectionForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	ShowGraph();

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			DA->SetParentPointer(InstBase,D->PhaseCode,D->GlobalPage,D->Layer);
			AlignmentProjectionItem	*BData=dynamic_cast<AlignmentProjectionItem *>(DA);
			if(BData!=NULL){
				ui->lineEditItemName			->setText (BData->GetItemName()		);
				ui->spinBoxPeakCount			->setValue(BData->GetThresholdR(GetLayersBase())->PeakCount	);
				ui->doubleSpinBoxAngle			->setValue(BData->GetThresholdR(GetLayersBase())->Angle		);
				ui->doubleSpinBoxPeakIsolation	->setValue(BData->GetThresholdR(GetLayersBase())->PeakIsolation);
				ui->spinBoxUsageLayer			->setValue(BData->GetThresholdR(GetLayersBase())->UsageLayer	);
				ui->doubleSpinBoxAbandonRateL	->setValue(BData->GetThresholdR(GetLayersBase())->AbandonRateL	);
				ui->doubleSpinBoxAbandonRateH	->setValue(BData->GetThresholdR(GetLayersBase())->AbandonRateH	);

				BData->TF_EnumHistList(HContainer);
				break;
			}
		}
	}
}


void	SettingAlignmentProjectionForm::ShowGraph(void)
{
	GraphMapMaster.DeleteXY();
	GraphMapTarget.DeleteXY();
	GraphPeakMaster.DeleteXY();
	GraphPeakTarget.DeleteXY();

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentProjectionItem	*BData=dynamic_cast<AlignmentProjectionItem *>(DA);
		if(BData==NULL)
			continue;
		
		YMax=0;
		for(int i=0;i<BData->MapDimCount;i++){
			YMax=max(YMax,BData->MasterMapDim[i]);
			YMax=max(YMax,BData->TargetMapDim[i]);
			GraphMapMaster.AddXY(i		,BData->MasterMapDim[i]);
			GraphMapTarget.AddXY(i+0.5	,BData->TargetMapDim[i]);
		}

		for(int i=0;i<BData->GetThresholdR(GetLayersBase())->PeakCount;i++){
			GraphPeakMaster.AddXY(BData->MasterPeak[i]-BData->LMinD		,YMax);
			GraphPeakTarget.AddXY(BData->TargetPeak[i]-BData->LMinD		,YMax);
		}
		return;
	}
}

void	SettingAlignmentProjectionForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentProjectionItem	*BData=dynamic_cast<AlignmentProjectionItem *>(DA);
		if(BData==NULL)
			continue;
		AlignmentProjectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->PeakCount		=ui->spinBoxPeakCount			->value();
		Thr->Angle			=ui->doubleSpinBoxAngle			->value();
		Thr->PeakIsolation	=ui->doubleSpinBoxPeakIsolation	->value();
		Thr->UsageLayer		=ui->spinBoxUsageLayer			->value();
		Thr->AbandonRateL	=ui->doubleSpinBoxAbandonRateL	->value();
		Thr->AbandonRateH	=ui->doubleSpinBoxAbandonRateH	->value();

		//return;
	}
}

void SettingAlignmentProjectionForm::on_pushButtonSetOne_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change one point");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one point");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void SettingAlignmentProjectionForm::on_pushButtonSetAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change all points");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all points");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void SettingAlignmentProjectionForm::on_pushButtonClose_clicked()
{
	close();
}
