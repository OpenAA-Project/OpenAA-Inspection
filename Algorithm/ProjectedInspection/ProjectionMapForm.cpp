#include "ProjectionMapForm.h"
#include "ui_ProjectionMapForm.h"
#include "XProjectedInspection.h"
#include "XProjectedInspectionLibrary.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "mtColorFrame.h"
#include "XGeneralDialog.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ProjectionMapForm::ProjectionMapForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::ProjectionMapForm)
	
{
    ui->setupUi(this);
	OnChanging	=false;
	connect(this,SIGNAL(SignalStartCalc()),this,SLOT(SlotStartCalc()),Qt::QueuedConnection);

	LGraph.setParent(ui->frameLineGraph);
	LGraph.SetScaleTypeY(mtLineGraph::mtConstant);
	LGraph.move(0,0);
	LGraph.resize(ui->frameLineGraph->width(),ui->frameLineGraph->height());

	QColor	TargetColor=Qt::yellow;
	QColor	ThreshColor=Qt::red;

	GraphColTarget	.SetLineColor(TargetColor);
	GraphColTarget	.SetLineWidth(1);
	GraphColTarget	.SetOffsetX(1);
	GraphNG			.SetLineColor(ThreshColor);	
	GraphNG			.SetLineWidth(1);
	GraphNG			.SetOffsetX(2);

	LGraph.AddGraph(&GraphColTarget);
	LGraph.AddGraph(&GraphNG);
	connect(&LGraph,SIGNAL(SignalLineGraphDClick(int ,int )),this,SLOT(SlotLineGraphDClick(int ,int )));

	IData=NULL;

	ui->labelResultMaxDIfference	->setText(/**/"");
	SetupPassword();

	InstallOperationLog(this);
}

ProjectionMapForm::~ProjectionMapForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	ProjectionMapForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	CreateThreshld();
	ShowHistgramList();
}

void	ProjectionMapForm::ShowHistgramList(void)
{
	ui->listWidgetHistList->clear();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ProjectedInspectionItem	*BData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_EnumHistList(HContainer);
		for(HistgramTypeListInAlgo *a=HContainer.GetFirst();a!=NULL;a=a->GetNext()){
			ui->listWidgetHistList->addItem(a->HistName);
		}
		return;
	}
}

void	ProjectionMapForm::CreateThreshld(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ProjectedInspectionItem	*BData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,ProjectedInspectionReqThresholdReqCommand ,ProjectedInspectionReqThresholdSendCommand);
		((ProjectedInspectionThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((ProjectedInspectionThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((ProjectedInspectionThresholdReq *)PacketReq.Data)->ProjectedInspectionItemID	=DA->GetID();
		((ProjectedInspectionThresholdReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		ProjectedInspectionThresholdSend	*ThrePoint=(ProjectedInspectionThresholdSend *)PacketSend.GetData();
		//CenterBright		=ThrePoint->CenterBright;

		Angle				=ThrePoint->Angle				;
		ExcludeDynamicMask	=ThrePoint->ExcludeDynamicMask	;
		TransitWidth		=ThrePoint->TransitWidth		;
		OKWidthDiffereceL	=ThrePoint->OKWidthDiffereceL	;
		OKWidthDiffereceH	=ThrePoint->OKWidthDiffereceH	;
		UseAbsolute			=ThrePoint->UseAbsolute			;
		EvenLength			=ThrePoint->EvenLength			;
		PartialSwingAngle	=ThrePoint->PartialSwingAngle	;
		break;
	}
	ShowLibrary();
	GetHistogramData();
	ShowThreshold();
	LGraph.repaint();
}

void ProjectionMapForm::GetHistogramData(void)
{
	GraphColTarget.DeleteXY();

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ProjectedInspectionItem	*BData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,ProjectedInspectionHistogramListReqCommand ,ProjectedInspectionHistogramListSendCommand);
		((ProjectedInspectionHistogramListReq *)PacketReq.Data)->GlobalPage=D->GlobalPage;
		((ProjectedInspectionHistogramListReq *)PacketReq.Data)->Layer=D->Layer;
		((ProjectedInspectionHistogramListReq *)PacketReq.Data)->ProjectedInspectionItemID	=DA->GetID();
		((ProjectedInspectionHistogramListReq *)PacketReq.Data)->Mastered=true;
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		ProjectedInspectionHistogramListSend	*L=(ProjectedInspectionHistogramListSend *)PacketSend.GetData();
		YMax=0;
		for(int i=0;i<BData->ProjectedDataLen;i++){
			YMax=max(YMax,L->ProjectedData[i]);
			GraphColTarget.AddXY(i	,L->ProjectedData[i]);
		}
		return;
	}
}


void	ProjectionMapForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ProjectedInspectionItem	*BData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->EditLibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->EditLibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
		ui->EditItemName				->setText(BData->GetItemName());

		ui->EditTransitWidth				->setValue(BData->GetThresholdR(GetLayersBase())->TransitWidth);
		ui->EditOKWidthDiffereceL			->setValue(BData->GetThresholdR(GetLayersBase())->OKWidthDiffereceL);
		ui->EditOKWidthDiffereceH			->setValue(BData->GetThresholdR(GetLayersBase())->OKWidthDiffereceH);
		ui->doubleSpinBoxAngle				->setValue(BData->GetThresholdR(GetLayersBase())->Angle			);
		ui->checkBoxUseAbsolute				->setChecked(BData->GetThresholdR(GetLayersBase())->UseAbsolute	);
		ui->EditEvenLength					->setValue(BData->GetThresholdR(GetLayersBase())->EvenLength		);
		ui->doubleSpinBoxPartialSwingAngle	->setValue(BData->GetThresholdR(GetLayersBase())->PartialSwingAngle*360.0/(2.0*M_PI)		);
		return;
	}
}

void ProjectionMapForm::ShowThreshold(void)
{
	GraphNG.DeleteXY();
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		ProjectedInspectionItem	*BData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		GraphNG.AddXY(0						 ,BData->GetThresholdR(GetLayersBase())->TransitWidth);
		GraphNG.AddXY(BData->ProjectedDataLen,BData->GetThresholdR(GetLayersBase())->TransitWidth);

		return;
	}
}
void	ProjectionMapForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		ProjectedInspectionItem	*BData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		ProjectedInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		BData->SetItemName(ui->EditItemName	->text());
		Thr->TransitWidth		=ui->EditTransitWidth		->value();
		Thr->OKWidthDiffereceL	=ui->EditOKWidthDiffereceL	->value();
		Thr->OKWidthDiffereceH	=ui->EditOKWidthDiffereceH	->value();
		Thr->Angle				=ui->doubleSpinBoxAngle		->value();
		Thr->UseAbsolute		=ui->checkBoxUseAbsolute	->isChecked();
		Thr->EvenLength			=ui->EditEvenLength			->value();
		Thr->PartialSwingAngle	=ui->doubleSpinBoxPartialSwingAngle	->value()*2*M_PI/360.0;
		//return;
	}
}

void ProjectionMapForm::on_pushButtonChangeLib_clicked()
{

}

void ProjectionMapForm::on_pushButtonTransmitItemNameAll_clicked()
{

}

void ProjectionMapForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE Projection threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one block threshold");
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

void ProjectionMapForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL Projection threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all blocks threshold");
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

void ProjectionMapForm::on_ButtonSaveToLibrary_clicked()
{

}

void ProjectionMapForm::on_ButtonLoadFromLibrary_clicked()
{

}

void ProjectionMapForm::on_ButtonClose_clicked()
{
	close();
}

void ProjectionMapForm::on_EditOKWidthDifferece_valueChanged(int arg1)
{

}

void ProjectionMapForm::on_EditTransitWidth_valueChanged(int arg1)
{

}

void ProjectionMapForm::on_ButtonCalc_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		ProjectedInspectionItem	*nBData=dynamic_cast<ProjectedInspectionItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,ProjectedInspectionReqTryThresholdCommand ,ProjectedInspectionSendTryThresholdCommand);
		ProjectedInspectionItem	*BData=&((ProjectedInspectionReqTryThreshold *)PacketReq.Data)->Threshold;
		((ProjectedInspectionReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((ProjectedInspectionReqTryThreshold *)PacketReq.Data)->Layer			=D->Layer;
		((ProjectedInspectionReqTryThreshold *)PacketReq.Data)->ProjectedInspectionItemID	=DA->GetID();

		ProjectedInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->TransitWidth		=ui->EditTransitWidth		->value();
		Thr->OKWidthDiffereceL	=ui->EditOKWidthDiffereceL	->value();
		Thr->OKWidthDiffereceH	=ui->EditOKWidthDiffereceH	->value();
		Thr->Angle				=ui->doubleSpinBoxAngle		->value();
		Thr->UseAbsolute		=ui->checkBoxUseAbsolute	->isChecked();
		Thr->EvenLength			=ui->EditEvenLength			->value();
		Thr->PartialSwingAngle	=ui->doubleSpinBoxPartialSwingAngle	->value()*2*M_PI/360.0;

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			ProjectedInspectionSendTryThreshold	*R=((ProjectedInspectionSendTryThreshold *)PacketSend.Data);
			ui->labelResultMaxDIfference	->setText(QString::number(R->NGDots	));
			break;
		}
	}	
}

void	ProjectionMapForm::SlotStartCalc()
{
	on_ButtonCalc_clicked();
}
