#include "EditHolePosDialog.h"
#include "ui_EditHolePosDialog.h"
#include "XPieceArchitect.h"
#include "swap.h"
#include "XMeasureHolePos.h"
#include "XGeneralDialog.h"
#include "XDataInLayerCommander.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EditHolePosDialog::EditHolePosDialog(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base)
	,ui(new Ui::EditHolePosDialog)
{
    ui->setupUi(this);

	IData=NULL;
	InstallOperationLog(this);
}

EditHolePosDialog::~EditHolePosDialog()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	EditHolePosDialog::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
}

void EditHolePosDialog::on_pushButtonChangeLib_clicked()
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
			MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
			if(BData!=NULL){
				int	OldID=DA->GetLibID();
				DA->SetLibID(RetSelectedLibID);

				ui->EditLibID	->setText(QString::number(DA->GetLibID()));
				for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
					if(L->GetLibID()==OldID){
						L->SetLibID(RetSelectedLibID);
						ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
						ui->Edit_LibName	->setText(L->GetLibName());
						break;
					}
				}
			}
		}
	}
}

void	EditHolePosDialog::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(BData==NULL)
			continue;
		MeasureHolePosThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->DiaPrecision	=ui->doubleSpinBoxDiaPrecision->value();	//micron size
		Thr->PosPrecision	=ui->doubleSpinBoxPosPrecision->value();	//micron size
		Thr->NoiseSize		=ui->spinBoxNoiseSize	->value();
		Thr->BandWidth		=ui->spinBoxBandWidth	->value();
		Thr->SearchDot		=ui->EditSearchDot		->value();
		Thr->CalcMode		=ui->comboBoxCalcMode->currentIndex();
		BData->SetItemName(ui->EditName			->text());
		return;
	}
}

void EditHolePosDialog::ShowThreshold(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			return;
		MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(BData==NULL)
			continue;
		MeasureHolePosThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		ui->doubleSpinBoxDiaPrecision	->setValue(Thr->DiaPrecision);	//micron size
		ui->doubleSpinBoxPosPrecision	->setValue(Thr->PosPrecision);	//micron size
		ui->spinBoxNoiseSize			->setValue(Thr->NoiseSize);
		ui->spinBoxBandWidth			->setValue(Thr->BandWidth);
		ui->EditSearchDot				->setValue(Thr->SearchDot);
		ui->comboBoxCalcMode			->setCurrentIndex(Thr->CalcMode);
		ui->EditName					->setText(BData->GetItemName());
		return;
	}
}
void EditHolePosDialog::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(BData==NULL)
			continue;
		MeasureHolePosThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		if(DA->GetLibID()<0){
			ui->EditLibID->setText(/**/"");
			ui->Edit_LibName->setText(/**/"");
		}
		else{
			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			ui->Edit_LibName->setText(/**/"");
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==DA->GetLibID()){
					ui->Edit_LibName	->setText(L->GetLibName());
					break;
				}
			}
		}

		ui->doubleSpinBoxDiaPrecisionLib->setValue(Thr->DiaPrecision);	//micron size
		ui->doubleSpinBoxPosPrecisionLib->setValue(Thr->PosPrecision);	//micron size
		ui->spinBoxNoiseSizeLib			->setValue(Thr->NoiseSize);
		ui->spinBoxBandWidthLib			->setValue(Thr->BandWidth);
		ui->EditSearchDotLib			->setValue(Thr->SearchDot);
		ui->comboBoxCalcMode			->setCurrentIndex(Thr->CalcMode);
		break;
	}
}

void EditHolePosDialog::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE item threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one item threshold");
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

void EditHolePosDialog::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL items\' threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all items threshold");
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

void EditHolePosDialog::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(BData==NULL)
			continue;
		MeasureHolePosThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,DestLib)==true){
			MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void EditHolePosDialog::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(BData==NULL)
			continue;
		MeasureHolePosThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(BData->GetLibraryContainer()->GetLibrary(LibID ,SrcLib)==true){
			MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			Thr->FromLibrary(ALib);
			ShowLibrary();
			ShowThreshold();
		
			ui->doubleSpinBoxDiaPrecision	->setValue(Thr->DiaPrecision);	//micron size
			ui->doubleSpinBoxPosPrecision	->setValue(Thr->PosPrecision);	//micron size
			ui->spinBoxNoiseSize			->setValue(Thr->NoiseSize);
			ui->spinBoxBandWidth			->setValue(Thr->BandWidth);
			ui->EditSearchDot				->setValue(Thr->SearchDot);
			return;
		}
	}
}

void EditHolePosDialog::on_ButtonClose_clicked()
{
	close();
}

void EditHolePosDialog::on_listWidgetHistList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetHistList->currentRow();
	if(Row<0)
		return;
	HistgramTypeListInAlgo	*H=HContainer[Row];
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureHolePosItemBase	*BData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(BData==NULL)
			continue;
		
		BData->TF_ShowHistgramGraph(H->HistID);
		return;
	}
}

void EditHolePosDialog::on_pushButtonTest_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		MeasureHolePosItemBase	*nBData=dynamic_cast<MeasureHolePosItemBase *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,ReqTryThresholdCommand ,SendTryThresholdCommand);
		MeasureHolePosItemBase	*BData=&((HolePosReqTryThreshold *)PacketReq.Data)->Threshold;
		((HolePosReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((HolePosReqTryThreshold *)PacketReq.Data)->ItemID		=DA->GetID();

		MeasureHolePosThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->DiaPrecision	=ui->doubleSpinBoxDiaPrecision->value();	//micron size
		Thr->PosPrecision	=ui->doubleSpinBoxPosPrecision->value();	//micron size
		Thr->NoiseSize		=ui->spinBoxNoiseSize	->value();
		Thr->BandWidth		=ui->spinBoxBandWidth	->value();
		Thr->SearchDot		=ui->EditSearchDot		->value();
		Thr->CalcMode		=ui->comboBoxCalcMode->currentIndex();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.Send(D->GlobalPage,0,PacketSend);

		HolePosSendTryThreshold	*R=((HolePosSendTryThreshold *)PacketSend.Data);

		ui->labelHoleV	->setText(QString::number(R->HoleV	));
		ui->labelHoleH	->setText(QString::number(R->HoleH	));
		ui->labelPosDiffX->setText(QString::number(R->PosDiffX	));
		ui->labelPosDiffY->setText(QString::number(R->PosDiffY	));
		break;
	}
}
