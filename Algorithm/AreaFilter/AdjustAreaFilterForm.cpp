#include "AdjustAreaFilterForm.h"
#include "ui_AdjustAreaFilterForm.h"
#include "XAreaFilter.h"
#include "XDataInLayerCommander.h"
#include "swap.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

AdjustAreaFilterForm::AdjustAreaFilterForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::AdjustAreaFilterForm)
{
    ui->setupUi(this);

	IData=NULL;
	InstallOperationLog(this);
}

AdjustAreaFilterForm::~AdjustAreaFilterForm()
{
	if(IData!=NULL)
		delete	IData;
	IData=NULL;

	delete ui;
}

void	AdjustAreaFilterForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			AreaFilterItem	*BData=dynamic_cast<AreaFilterItem *>(DA);
			if(BData!=NULL){
			}
		}
	}
	ShowLibrary();
}

void	AdjustAreaFilterForm::ShowLibrary(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		//if(LayerList.GetFirst()->GetValue()!=D->Layer)
		//	continue;
		AreaFilterItem	*BData=dynamic_cast<AreaFilterItem *>(DA);
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

		if(BData->GetItemClassType()==0){
			ui->labelItemType	->setText("PatternInverted");
			ui->stackedWidget->setCurrentIndex(0);
		}
		if(BData->GetItemClassType()==1){
			ui->labelItemType	->setText("VerticalEmphasize");
			ui->stackedWidget->setCurrentIndex(1);
		}
		if(BData->GetItemClassType()==2){
			AreaFilterItemLineEmphasize	*A=dynamic_cast<AreaFilterItemLineEmphasize *>(BData);
			ui->labelItemType	->setText("線強調");
			ui->stackedWidget->setCurrentIndex(2);
			ui->spinBoxBlockSize		->setValue(A->GetThresholdR(GetLayersBase())->BlockSize);
			ui->spinBoxEmphasizeRate	->setValue(A->GetThresholdR(GetLayersBase())->EmphasizeRate);
			ui->spinBoxUpperBlocksPercentageByVariance->setValue(A->GetThresholdR(GetLayersBase())->UpperBlocksPercentageByVariance);
			ui->spinBoxSkipSita			->setValue(A->GetThresholdR(GetLayersBase())->SkipTheta);
			ui->spinBoxSkipKy			->setValue(A->GetThresholdR(GetLayersBase())->SkipKy);
			ui->spinBoxUnifiedLineNumb	->setValue(A->GetThresholdR(GetLayersBase())->UnifiedLineNumb);
		}
		if(BData->GetItemClassType()==3){
			AreaFilterItemLineLargeEnflat	*A=dynamic_cast<AreaFilterItemLineLargeEnflat *>(BData);
			ui->labelItemType	->setText("大域均一化");
			ui->stackedWidget->setCurrentIndex(3);
			ui->spinBoxLineLargeEnflat_BlockSize->setValue(A->GetThresholdR(GetLayersBase())->BlockSize);
			ui->checkBoxMoveByAlignment			->setChecked(A->GetThresholdR(GetLayersBase())->MoveByAlignment);
			ui->spinBoxSkipDot					->setValue(A->GetThresholdR(GetLayersBase())->SkipDot);
			ui->spinBoxGeneratedBrightness		->setValue(A->GetThresholdR(GetLayersBase())->GeneratedBrightness);
			ui->doubleSpinBoxAdoptedRate		->setValue(A->GetThresholdR(GetLayersBase())->AdoptedRate	);
		}
		if(BData->GetItemClassType()==4){
			AreaFilterItemHorizontalEmphasize	*A=dynamic_cast<AreaFilterItemHorizontalEmphasize *>(BData);
			ui->labelItemType	->setText("HorizontalEmphasize");
			ui->stackedWidget->setCurrentIndex(4);
			ui->spinBoxHorizEmphaBlockSize		->setValue(A->GetThresholdR(GetLayersBase())->BlockSize);
			ui->checkBoxMoveByAlignment2		->setChecked(A->GetThresholdR(GetLayersBase())->MoveByAlignment);
			ui->spinBoxEmphasizeRate2			->setValue(A->GetThresholdR(GetLayersBase())->EmphasizeRate);
			ui->spinBoxSkipDot2					->setValue(A->GetThresholdR(GetLayersBase())->SkipDot);
			ui->spinBoxBlockHeight				->setValue(A->GetThresholdR(GetLayersBase())->BlockHeight);
		}

		return;
	}
}
void	AdjustAreaFilterForm::GetDataFromWindow(void)
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AreaFilterItem	*BData=dynamic_cast<AreaFilterItem *>(DA);
		if(BData==NULL)
			continue;
		if(BData->GetItemClassType()==0){
		}
		if(BData->GetItemClassType()==1){

		}
		if(BData->GetItemClassType()==2){
			AreaFilterItemLineEmphasize	*A=dynamic_cast<AreaFilterItemLineEmphasize *>(BData);
			A->GetThresholdW()->BlockSize		=ui->spinBoxBlockSize->value();
			A->GetThresholdW()->EmphasizeRate	=ui->spinBoxEmphasizeRate->value();
			A->GetThresholdW()->UpperBlocksPercentageByVariance=ui->spinBoxUpperBlocksPercentageByVariance->value();
			A->GetThresholdW()->SkipTheta		=ui->spinBoxSkipSita->value();
			A->GetThresholdW()->SkipKy			=ui->spinBoxSkipKy->value();
			A->GetThresholdW()->UnifiedLineNumb	=ui->spinBoxUnifiedLineNumb->value();
		}
		if(BData->GetItemClassType()==3){
			AreaFilterItemLineLargeEnflat	*A=dynamic_cast<AreaFilterItemLineLargeEnflat *>(BData);
			A->GetThresholdW()->BlockSize		=ui->spinBoxLineLargeEnflat_BlockSize->value();
			A->GetThresholdW()->MoveByAlignment	=ui->checkBoxMoveByAlignment			->isChecked();
			A->GetThresholdW()->SkipDot			=ui->spinBoxSkipDot					->value();
			A->GetThresholdW()->GeneratedBrightness	=ui->spinBoxGeneratedBrightness	->value();
			A->GetThresholdW()->AdoptedRate		=ui->doubleSpinBoxAdoptedRate		->value();
		}
		if(BData->GetItemClassType()==4){
			AreaFilterItemHorizontalEmphasize	*A=dynamic_cast<AreaFilterItemHorizontalEmphasize *>(BData);
			A->GetThresholdW()->BlockSize		=ui->spinBoxHorizEmphaBlockSize	->value	();
			A->GetThresholdW()->MoveByAlignment	=ui->checkBoxMoveByAlignment2	->isChecked();
			A->GetThresholdW()->EmphasizeRate	=ui->spinBoxEmphasizeRate2		->value	();
			A->GetThresholdW()->SkipDot			=ui->spinBoxSkipDot2				->value	();
			A->GetThresholdW()->BlockHeight		=ui->spinBoxBlockHeight			->value();
		}
		//return;
	}
}
void AdjustAreaFilterForm::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE area threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one area threshold");
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

void AdjustAreaFilterForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL blocks\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all blocks threshold");
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

void AdjustAreaFilterForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AreaFilterItem	*BData=dynamic_cast<AreaFilterItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			AreaFilterLibrary	*ALib=dynamic_cast<AreaFilterLibrary *>(DestLib.GetLibrary());
			BData->GetThresholdBaseWritable(GetLayersBase())->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void AdjustAreaFilterForm::on_ButtonLoadFromLibrary_clicked()
{
	IntList LayerList;
	//GetActiveLayerList(LayerList);
	//if(LayerList.GetFirst()==NULL)
	//	return;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AreaFilterItem	*BData=dynamic_cast<AreaFilterItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			AreaFilterLibrary	*ALib=dynamic_cast<AreaFilterLibrary *>(SrcLib.GetLibrary());
			BData->GetThresholdBaseWritable(GetLayersBase())->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}

void AdjustAreaFilterForm::on_ButtonClose_clicked()
{
	close();
}

void AdjustAreaFilterForm::on_pushButtonTransmitItemNameAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Transmiting ItemName all");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Transmit ItemName all");
	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"),-1,true);
	Packet.Command=SetIndependentItemNameDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void AdjustAreaFilterForm::on_pushButtonChangeLib_clicked()
{
	AlgorithmBase	*ABase=IData->Base->GetAlgorithmBase(sRoot,sName);
	int		RetSelectedLibID;
	QString RetSelectedLibName;
	ExeSelectLibraryForm(ABase->GetLibType(),IData->Base, this
						,RetSelectedLibID
						,RetSelectedLibName);
	if(RetSelectedLibID>=0){
		for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			AreaFilterItem	*BData=dynamic_cast<AreaFilterItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
		}
	}
}
