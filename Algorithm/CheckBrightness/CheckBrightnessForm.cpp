#include "CheckBrightnessForm.h"
#include "ui_CheckBrightnessForm.h"
#include "XCheckBrightness.h"
#include "XDataInLayerCommander.h"
#include "swap.h"

CheckBrightnessForm::CheckBrightnessForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::CheckBrightnessForm)
	,SimPanel(Base,parent)
{
    ui->setupUi(this);
	IData=NULL;

	InstallOperationLog(this);
}

CheckBrightnessForm::~CheckBrightnessForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
    delete ui;
}


void	CheckBrightnessForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
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
			CheckBrightnessItem	*BData=dynamic_cast<CheckBrightnessItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				//SimPanel.SetModeShowBlock		(ui.toolButtonSimShowBlock ->isChecked());
				//SimPanel.SetModeShowBrightnessNG(ui.toolButtonSimShowBright->isChecked());
			}
		}
	}

	ShowThreshold();
}

void	CheckBrightnessForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		CheckBrightnessItem	*BData=dynamic_cast<CheckBrightnessItem *>(DA);
		if(BData==NULL)
			continue;

		BData->ThreshL			=ui->spinBoxThreshL			->value();
		BData->ThreshH			=ui->spinBoxThreshH			->value();
		BData->RepeatableCount	=ui->spinBoxRepeatableCount	->value();
		BData->RegNumber		=ui->spinBoxRegNumber		->value();
		BData->Condition		=(CheckBrightnessItem::_Condition)(ui->comboBoxCondition		->currentIndex()+1);
		BData->WidthL			=ui->spinBoxWidthL			->value();
		BData->WidthH			=ui->spinBoxWidthH			->value();
		BData->SetItemName(ui->lineEditItemName	->text());
		return;
	}
}

void CheckBrightnessForm::ShowThreshold(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		CheckBrightnessItem	*BData=dynamic_cast<CheckBrightnessItem *>(DA);
		if(BData==NULL)
			continue;

		ui->spinBoxThreshL			->setValue(BData->ThreshL);
		ui->spinBoxThreshH			->setValue(BData->ThreshH);
		ui->spinBoxRepeatableCount	->setValue(BData->RepeatableCount);
		ui->spinBoxRegNumber		->setValue(BData->RegNumber);
		ui->comboBoxCondition		->setCurrentIndex((int)BData->Condition-1);
		ui->spinBoxWidthL			->setValue(BData->WidthL);
		ui->spinBoxWidthH			->setValue(BData->WidthH);
		ui->lineEditItemName	->setText(BData->GetItemName());
		return;
	}
}


void CheckBrightnessForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE item threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one item threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_OnlyOneCheckBrightness;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void CheckBrightnessForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting all items threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect ALL items threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_AllCheckBrightness;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void CheckBrightnessForm::on_pushButtonSetThresholdOne_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change one item threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one item threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_SetThreBrightnessThis;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();

}

void CheckBrightnessForm::on_pushButtonSetThresholdAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change one item threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one item threshold");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemDataCommand_SetThreBrightnessAll;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void CheckBrightnessForm::on_ButtonClose_clicked()
{
	close();
}
