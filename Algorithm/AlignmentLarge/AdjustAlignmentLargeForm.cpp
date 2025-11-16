#include "XAlignmentLargeResource.h"
#include "AdjustAlignmentLargeForm.h"
#include "ui_AdjustAlignmentLargeForm.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "swap.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

AdjustAlignmentLargeForm::AdjustAlignmentLargeForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::AdjustAlignmentLargeForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	OnChanging	=false;
	IData		=NULL;
	HistgramPage=-1;

	ui->comboBoxUseLayer	->clear();
	ui->comboBoxUseLayer	->addItem(LangSolver.GetString(AdjustAlignmentLargeForm_LS,LID_79)/*"Auto select"*/);
	for(int layer=0;layer<GetLayerNumb(0);layer++){
		ui->comboBoxUseLayer	->addItem(QString(/**/"Layer")
										 +QString::number(layer)
										 +QString(/**/" ")
										 +GetParamGlobal()->GetLayerName(layer));
	}

	InstallOperationLog(this);
}

AdjustAlignmentLargeForm::~AdjustAlignmentLargeForm()
{
    delete ui;
}
void	AdjustAlignmentLargeForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			HistgramPage	=D->GlobalPage;
			DA->SetParentPointer(InstBase,D->PhaseCode,D->GlobalPage,D->Layer);
			XAlignmentLarge	*BData=dynamic_cast<XAlignmentLarge *>(DA);
			if(BData!=NULL){
				const	AlignmentLargeThreshold	*RThr=BData->GetThresholdR(GetLayersBase());
				ui->spinBoxSearchDot	->setValue(RThr->MoveDotX);
				ui->spinBoxSearchDotY	->setValue(RThr->MoveDotY);
				ui->spinBoxSearchDot2	->setValue(RThr->MoveDotX2);
				ui->spinBoxSearchDot2Y	->setValue(RThr->MoveDotY2);
				ui->spinBoxMaxCountHLine->setValue(RThr->MaxCountHLine);
				ui->spinBoxMaxCountVLine->setValue(RThr->MaxCountVLine);
				ui->checkBoxJudgeWithBrDif	->setChecked(RThr->JudgeWithBrDif);
				ui->checkBoxCharacterMode	->setChecked(RThr->CharacterMode);
				ui->comboBoxUseLayer		->setCurrentIndex(RThr->UseLayer+1);
				ui->spinBoxThresholdColor	->setValue(RThr->ThresholdColor);


				GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				PacketReq.BuildData(sRoot,sName,AlignmentLargeThresholdReqCommand ,AlignmentLargeThresholdSendCommand);
				((AlignmentLargeThresholdReq *)PacketReq.Data)->Data.GlobalPage	=D->GlobalPage;
				((AlignmentLargeThresholdReq *)PacketReq.Data)->Data.Layer		=D->Layer;
				((AlignmentLargeThresholdReq *)PacketReq.Data)->Data.AlignmentLargeItemID	=DA->GetID();

				GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
				if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

					AlignmentLargeThresholdSend	*R=((AlignmentLargeThresholdSend *)PacketSend.Data);
					ui->labelSelectedLayer		->setText(QString::number(R->ThresholdValues.SelectedLayer));
					ui->labelThresholdColor		->setText(QString::number(R->ThresholdValues.ThresholdColor));
				}
				BData->TF_EnumHistList(HContainer);
				break;
			}
		}
	}
	if(HContainer[0]!=NULL)
		ui->pushButtonHistogramX->setEnabled(true);
	else
		ui->pushButtonHistogramX->setEnabled(false);

	if(HContainer[1]!=NULL)
		ui->pushButtonHistogramY->setEnabled(true);
	else
		ui->pushButtonHistogramY->setEnabled(false);

	ui->doubleSpinBoxSearchDotUnit->setDecimals(GetParamGlobal()->SmallNumberFigure);
	ui->labelUnitName1	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName2	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName3	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName4	->setText(GetParamGlobal()->UnitName);
}

void	AdjustAlignmentLargeForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		XAlignmentLarge	*BData=dynamic_cast<XAlignmentLarge *>(DA);
		if(BData==NULL)
			continue;

		AlignmentLargeThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->MoveDotX		=ui->spinBoxSearchDot	->value();
		Thr->MoveDotY		=ui->spinBoxSearchDotY	->value();
		Thr->MoveDotX2		=ui->spinBoxSearchDot2	->value();
		Thr->MoveDotY2		=ui->spinBoxSearchDot2Y	->value();
		Thr->MaxCountHLine	=ui->spinBoxMaxCountHLine->value();
		Thr->MaxCountVLine	=ui->spinBoxMaxCountVLine->value();
		Thr->JudgeWithBrDif	=ui->checkBoxJudgeWithBrDif	->isChecked();
		Thr->CharacterMode	=ui->checkBoxCharacterMode	->isChecked();
		Thr->UseLayer		=ui->comboBoxUseLayer->currentIndex()-1;
		Thr->ThresholdColor	=ui->spinBoxThresholdColor	->value();
		//return;
	}
}


void AdjustAlignmentLargeForm::on_pushButtonSetOne_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(AdjustAlignmentLargeForm_LS,LID_25)/*"Change one point"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one point");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentAlignmentLargeItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void AdjustAlignmentLargeForm::on_pushButtonSetAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(AdjustAlignmentLargeForm_LS,LID_26)/*"Change all points"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all points");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentAlignmentLargeItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void AdjustAlignmentLargeForm::on_pushButtonClose_clicked()
{
	close();
}

void AdjustAlignmentLargeForm::on_pushButtonHistogramX_clicked()
{
    IntList LayerList;
    HistgramTypeListInAlgo	*H=HContainer[0];
    for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
        AlgorithmItemRoot	*DA=D->Data;
        if(DA==NULL)
            continue;
        XAlignmentLarge	*BData=dynamic_cast<XAlignmentLarge *>(DA);
        if(BData==NULL)
            continue;

        BData->TF_ShowHistgramGraph(H->HistID);
        return;
    }
}

void AdjustAlignmentLargeForm::on_pushButtonHistogramY_clicked()
{
    IntList LayerList;
    HistgramTypeListInAlgo	*H=HContainer[1];
    for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
        AlgorithmItemRoot	*DA=D->Data;
        if(DA==NULL)
            continue;
        XAlignmentLarge	*BData=dynamic_cast<XAlignmentLarge *>(DA);
        if(BData==NULL)
            continue;

        BData->TF_ShowHistgramGraph(H->HistID);
        return;
    }
}

void AdjustAlignmentLargeForm::on_spinBoxSearchDot_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDotUnit->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_doubleSpinBoxSearchDotUnit_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->spinBoxSearchDot->setValue(TransformUnitToPixel(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_spinBoxSearchDotY_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDotUnitY->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_doubleSpinBoxSearchDotUnitY_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->spinBoxSearchDotY->setValue(TransformUnitToPixel(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_spinBoxSearchDot2_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDot2Unit->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_doubleSpinBoxSearchDot2Unit_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->spinBoxSearchDot2->setValue(TransformUnitToPixel(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_spinBoxSearchDot2Y_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->doubleSpinBoxSearchDot2UnitY->setValue(TransformPixelToUnit(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_doubleSpinBoxSearchDot2UnitY_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ui->spinBoxSearchDot2Y->setValue(TransformUnitToPixel(HistgramPage,arg1));
	OnChanging=false;
}

void AdjustAlignmentLargeForm::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetHistList->currentRow();
	if(Row<0)
		return;
	HistgramTypeListInAlgo *H=HContainer.GetItem(Row);
	if(H!=NULL){
		for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			DA->TF_ShowHistgramGraph(H->HistID);
			return;
		}
	}
}

