#include "AdjustItemForm.h"
#include "ui_AdjustItemForm.h"
#include "XRasterInspection.h"
#include "XRasterInspectionLibrary.h"
#include "XDataInLayerCommander.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "ReferenceColorDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;
	
DisplayAdjustPanel::DisplayAdjustPanel (LayersBase *base ,AdjustItemForm *p ,QWidget *parent)
	:DisplaySimPanel(base,parent),Parent(p)
{
}

void	DisplayAdjustPanel::GetDrawInformation(QByteArray &Something)
{
	Parent->GetDrawInformation(Something);
}
//===========================================================================
AdjustItemForm::AdjustItemForm(LayersBase *Base,QWidget *parent) :
	 QWidget(parent)
	,ServiceForLayers(Base)
	,PasswordInQWodget(Base,this)
	,DPanel(Base,this)
    ,ui(new Ui::AdjustItemForm)
{
    ui->setupUi(this);
	OnChanging	=false;
	InstBase	=NULL;
	IData=NULL;

	DPanel.setParent(ui->frame);
	DPanel.SetAlgo(sRoot,sName);
	DPanel.setGeometry(0,0,ui->frame->width(),ui->frame->height());

	SetupPassword();
	InstallOperationLog(this);
}

AdjustItemForm::~AdjustItemForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	AdjustItemForm::Initial(AlgorithmBase *_InstBase ,AlgorithmItemIndependentPack &Data)
{
	InstBase	=_InstBase;
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
			RasterInspectionItem	*BData=dynamic_cast<RasterInspectionItem *>(DA);
			if(BData!=NULL){
				DPanel.SetGlobalPage(D->GlobalPage);
				DPanel.SetInitial(BData->GetID(),BData->GetArea());
				DPanel.SetModeShowBlock			(ui->toolButtonSimShowBlock ->isChecked());
				DPanel.SetModeShowBrightnessNG	(ui->toolButtonSimShowBright->isChecked());

				OldLibID		=DA->GetLibID();
				NewLibID		=OldLibID			;
			}
		}
	}
	ShowLibrary();
}
int     AdjustItemForm::GetItemID(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			return DA->GetID();
		}
	}
	return -1;
}

void	AdjustItemForm::GetDrawInformation(QByteArray &Something)
{
	bool	b=ui->toolButtonShowResult->isChecked();
	Something.append(b);
}


void	AdjustItemForm::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		RasterInspectionItem	*BData=dynamic_cast<RasterInspectionItem *>(DA);
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

		const	RasterInspectionThreshold	*d=BData->GetThresholdR(GetLayersBase());

		ui->doubleSpinBoxGenColorDistance	->setValue(d->GenColorDistance);
		ui->spinBoxSearchAreaDot			->setValue(d->SearchAreaDot);
		ui->doubleSpinBoxSearchWaveDiv		->setValue(d->SearchWaveDiv);
		ui->doubleSpinBoxWaveDistance		->setValue(d->WaveDistance);
		ui->spinBoxOKDot					->setValue(d->OKDot);
		//OnChanging=false;
		SlotStartCalc();
		return;
	}
}
void	AdjustItemForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		RasterInspectionItem	*BData=dynamic_cast<RasterInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		RasterInspectionThreshold	*d=BData->GetThresholdW(GetLayersBase());

		d->GenColorDistance	=ui->doubleSpinBoxGenColorDistance	->value();
		d->SearchAreaDot	=ui->spinBoxSearchAreaDot			->value();
		d->SearchWaveDiv	=ui->doubleSpinBoxSearchWaveDiv		->value();
		d->WaveDistance		=ui->doubleSpinBoxWaveDistance		->value();
		d->OKDot			=ui->spinBoxOKDot					->value();
	}
}
void AdjustItemForm::on_pushButtonReferencePDF_clicked()
{
	ReferenceColorDialog	D(GetLayersBase());
	D.exec();
}

void AdjustItemForm::on_ButtonRelrectOnlyItem_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE block threshold");

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one block threshold");
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


void AdjustItemForm::on_ButtonReflectAllItems_clicked()
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


void AdjustItemForm::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();

	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		RasterInspectionItem	*BData=dynamic_cast<RasterInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			RasterInspectionLibrary	*ALib=dynamic_cast<RasterInspectionLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			RasterInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			Container->Update(DestLib);
			return;
		}
	}
}


void AdjustItemForm::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		RasterInspectionItem	*BData=dynamic_cast<RasterInspectionItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			RasterInspectionLibrary	*ALib=dynamic_cast<RasterInspectionLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			RasterInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			return;
		}
	}
}


void AdjustItemForm::on_ButtonClose_clicked()
{
	close();
}

void AdjustItemForm::SlotStartCalc()
{
	if(OnChanging==true){
		return;
	}
	OnChanging=true;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		RasterInspectionItem	*nBData=dynamic_cast<RasterInspectionItem *>(DA);
		if(nBData==NULL)
			continue;
	
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,RasterInspectionReqTryThresholdCommand ,RasterInspectionSendTryThresholdCommand);
		RasterInspectionItem	*BData=&((RasterInspectionReqTryThreshold *)PacketReq.Data)->Threshold;
		RasterInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->CopyFrom(*nBData->GetThresholdW());
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.GlobalPage	=D->GlobalPage;
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.ItemID		=DA->GetID();
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.GenColorDistance	=ui->doubleSpinBoxGenColorDistance	->value();
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.SearchAreaDot		=ui->spinBoxSearchAreaDot			->value();
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.SearchWaveDiv		=ui->doubleSpinBoxSearchWaveDiv		->value();
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.WaveDistance		=ui->doubleSpinBoxWaveDistance		->value();
		((RasterInspectionReqTryThreshold *)PacketReq.Data)->Data.OKDot				=ui->spinBoxOKDot					->value();
	
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){
	
			RasterInspectionSendTryThreshold	*R=((RasterInspectionSendTryThreshold *)PacketSend.Data);
			R->Result->SetAlignedXY(0,0);
			DPanel.SetResult(R->Result);
			DPanel.repaint();
			break;
		}
	}

	OnChanging=false;
}



void AdjustItemForm::on_spinBoxSearchAreaDot_valueChanged(int arg1)
{
	SlotStartCalc();
}


void AdjustItemForm::on_doubleSpinBoxSearchWaveDiv_valueChanged(double arg1)
{
	SlotStartCalc();
}


void AdjustItemForm::on_doubleSpinBoxWaveDistance_valueChanged(double arg1)
{
	SlotStartCalc();
}


void AdjustItemForm::on_spinBoxOKDot_valueChanged(int arg1)
{
	SlotStartCalc();
}


void AdjustItemForm::on_toolButtonSimShowBlock_clicked()
{
	SlotStartCalc();
}


void AdjustItemForm::on_toolButtonShowResult_clicked()
{
	SlotStartCalc();
}


void AdjustItemForm::on_doubleSpinBoxGenColorDistance_valueChanged(double arg1)
{
	SlotStartCalc();
}

