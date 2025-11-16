#include "HoughInspectionResource.h"
#include "EditThresholdForm.h"
#include "ui_EditThresholdForm.h"
#include "XHoughInspection.h"
#include "XDataInLayerCommander.h"
#include "swap.h"

EditThresholdForm::EditThresholdForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
    ,ui(new Ui::EditThresholdForm)
	,SimPanel(Base,parent)
{
    ui->setupUi(this);
	IData=NULL;
	HistgramPage	=-1;
	InstallOperationLog(this);
}

EditThresholdForm::~EditThresholdForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
    delete ui;
}


void	EditThresholdForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(D->Layer);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			HistgramPage	=D->GlobalPage;
			HoughItem	*BData=dynamic_cast<HoughItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				//SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
				//SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
			}
		}
	}

	ShowLibrary();
	ShowThreshold();
	SetMMFromPixel();
}

void	EditThresholdForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		HoughItem	*BData=dynamic_cast<HoughItem *>(DA);
		if(BData==NULL)
			continue;
		HoughThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->ZoneWidth			=ui->EditZoneWidth				->value();
		Thr->MaxIsolation		=ui->EditMaxIsolation			->value();
		Thr->BinarizedLength	=ui->EditBinarizedLength		->value();
		Thr->MinPixels			=ui->EditMinPixels				->value();
		Thr->NGLength			=ui->EditNGLength				->value();
		Thr->PickupL			=ui->EditPickupL				->value();
		Thr->PickupH			=ui->EditPickupH				->value();
		Thr->RemoveDynamicMask	=ui->checkBoxRemoveDynamicMask	->isChecked();
		Thr->ReducedSize		=ui->EditReducedSize			->value();
		Thr->MaxLineCount		=ui->EditMaxLineCount			->value();
		Thr->MinNGWidth			=ui->EditMinNGWidth				->value();
		Thr->MaxNGWidth			=ui->EditMaxNGWidth				->value();
		Thr->MinAverageContinuous=ui->EditMinAverageContinuous	->value();
		Thr->DynamicBinarize	=ui->checkBoxDynamicBinarize	->isChecked();

		BData->SetItemName(ui->EditItemName	->text());
		return;
	}
}

void EditThresholdForm::ShowThreshold(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		HoughItem	*BData=dynamic_cast<HoughItem *>(DA);
		if(BData==NULL)
			continue;
		HoughThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		if(BData->GetLibID()<0)
			ui->EditLibID->setText(/**/"");
		else
			ui->EditLibID->setText(QString::number(BData->GetLibID()));

		ui->EditItemName			->setText(BData->GetItemName());
		ui->EditZoneWidth			->setValue(Thr->ZoneWidth);
		ui->EditMaxIsolation		->setValue(Thr->MaxIsolation);
		ui->EditBinarizedLength		->setValue(Thr->BinarizedLength);
		ui->EditMinPixels			->setValue(Thr->MinPixels);
		ui->EditNGLength			->setValue(Thr->NGLength);
		ui->EditPickupL				->setValue(Thr->PickupL);
		ui->EditPickupH				->setValue(Thr->PickupH);
		ui->checkBoxRemoveDynamicMask	->setChecked(Thr->RemoveDynamicMask);
		ui->EditReducedSize			->setValue(Thr->ReducedSize);
		ui->EditMaxLineCount		->setValue(Thr->MaxLineCount);
		ui->EditMinNGWidth			->setValue(Thr->MinNGWidth);
		ui->EditMaxNGWidth			->setValue(Thr->MaxNGWidth);
		ui->EditMinAverageContinuous->setValue(Thr->MinAverageContinuous);
		ui->checkBoxDynamicBinarize	->setChecked(Thr->DynamicBinarize);
		return;
	}
}
void EditThresholdForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		HoughItem	*BData=dynamic_cast<HoughItem *>(DA);
		if(BData==NULL)
			continue;
		HoughThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
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
		ui->EditItemName			->setText(BData->GetItemName());
		ui->EditZoneWidth			->setValue(Thr->ZoneWidth);
		ui->EditMaxIsolation		->setValue(Thr->MaxIsolation);
		ui->EditBinarizedLength		->setValue(Thr->BinarizedLength);
		ui->EditMinPixels			->setValue(Thr->MinPixels);
		ui->EditNGLength			->setValue(Thr->NGLength);
		ui->EditPickupL				->setValue(Thr->PickupL);
		ui->EditPickupH				->setValue(Thr->PickupH);
		ui->checkBoxRemoveDynamicMask	->setChecked(Thr->RemoveDynamicMask);
		ui->EditReducedSize			->setValue(Thr->ReducedSize);
		ui->EditMaxLineCount		->setValue(Thr->MaxLineCount);
		ui->EditMinNGWidth			->setValue(Thr->MinNGWidth);
		ui->EditMinNGWidth			->setValue(Thr->MaxNGWidth);
		ui->EditMinAverageContinuous->setValue(Thr->MinAverageContinuous);
		ui->checkBoxDynamicBinarize	->setChecked(Thr->DynamicBinarize);
		break;
	}
}
void EditThresholdForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(EditThresholdForm_LS,LID_13)/*"Reflecting ONE item threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one item threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOneHough;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void EditThresholdForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(EditThresholdForm_LS,LID_14)/*"Reflecting ALL items\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all items threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_AllHough;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void EditThresholdForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		HoughItem	*BData=dynamic_cast<HoughItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			HoughThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}

void EditThresholdForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		HoughItem	*BData=dynamic_cast<HoughItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			HoughThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
			SetMMFromPixel();
			return;
		}
	}
}

void EditThresholdForm::on_ButtonClose_clicked()
{
	close();
}

void EditThresholdForm::on_toolButtonSimShowBright_clicked()
{

}

void EditThresholdForm::on_pushButtonSimShowCenterPos_clicked()
{

}

void EditThresholdForm::on_EditZoneWidth_valueChanged(int arg1)
{
	SetMMFromPixel();
}

void EditThresholdForm::on_EditMaxIsolation_valueChanged(int arg1)
{
	SetMMFromPixel();
}

void EditThresholdForm::on_EditNGLength_valueChanged(int arg1)
{
	SetMMFromPixel();
}

void EditThresholdForm::on_EditMinPixels_valueChanged(int arg1)
{
	SetMMFromPixel();
}

void EditThresholdForm::on_EditMinNGWidth_valueChanged(double arg1)
{
	SetMMFromPixel();
}

void EditThresholdForm::on_EditMaxNGWidth_valueChanged(double arg1)
{
	SetMMFromPixel();
}

void	EditThresholdForm::SetMMFromPixel(void)
{
	ui->EditZoneWidthMM				->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(HistgramPage,ui->EditZoneWidth				->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
	ui->EditMaxIsolationMM			->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(HistgramPage,ui->EditMaxIsolation			->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
	ui->EditNGLengthMM				->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(HistgramPage,ui->EditNGLength				->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
	ui->EditMinPixelsMM				->setText(QString::number(GetParamGlobal()->TransformPixelToUnitSquare(HistgramPage,ui->EditMinPixels		->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
	ui->EditMinNGWidthMM			->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(HistgramPage,ui->EditMinNGWidth			->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
	ui->EditMaxNGWidthMM			->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(HistgramPage,ui->EditMaxNGWidth			->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
	ui->EditMinAverageContinuousMM	->setText(QString::number(GetParamGlobal()->TransformPixelToUnit(HistgramPage,ui->EditMinAverageContinuous	->value()),'f',GetParamGlobal()->GetParamGlobal()->SmallNumberFigure));
}
void EditThresholdForm::on_EditMinAverageContinuous_valueChanged(int arg1)
{
	SetMMFromPixel();
}
