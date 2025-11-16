#include "XLineEnhancer1LResource.h"
#include "ThresholdLineEnhancer1L.h"
#include "ui_ThresholdLineEnhancer1L.h"
#include "XLineEnhancer1L.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "swap.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;


ThresholdLineEnhancer1L::ThresholdLineEnhancer1L(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),
    ui(new Ui::ThresholdLineEnhancer1L)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	IData=NULL;

	InstallOperationLog(this);
}

ThresholdLineEnhancer1L::~ThresholdLineEnhancer1L()
{
    delete ui;
}

void	ThresholdLineEnhancer1L::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	CreateThreshld();
}

void	ThresholdLineEnhancer1L::CreateThreshld(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancer1LItem	*BData=dynamic_cast<LineEnhancer1LItem *>(DA);
		if(BData==NULL)
			continue;
		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,LineEnhancer1LReqThresholdReqCommand ,LineEnhancer1LReqThresholdSendCommand);
		((LineEnhancer1LThresholdReq *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((LineEnhancer1LThresholdReq *)PacketReq.Data)->Layer		=D->Layer;
		((LineEnhancer1LThresholdReq *)PacketReq.Data)->ItemID		=DA->GetID();
		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			LineEnhancer1LThresholdSend	*ThrePoint=(LineEnhancer1LThresholdSend *)PacketSend.GetData();
			EmphasizeRate		=ThrePoint->EmphasizeRate;
			MaxLineWidth		=ThrePoint->MaxLineWidth;		
			StepDot				=ThrePoint->StepDot;		
			SelfSearch			=ThrePoint->SelfSearch;
			StartAngle			=ThrePoint->StartAngle;
			EndAngle			=ThrePoint->EndAngle;
			ExcludeDynamicMask	=ThrePoint->ExcludeDynamicMask;
			FixedAngle			=ThrePoint->FixedAngle;
			break;
		}
	}
	ShowLibrary();
}

void	ThresholdLineEnhancer1L::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancer1LItem	*BData=dynamic_cast<LineEnhancer1LItem *>(DA);
		if(BData==NULL)
			continue;
		LineEnhancer1LThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->EmphasizeRate		=ui->doubleSpinBoxEmphasizeRate	->value();
		Thr->MaxLineWidth		=ui->EditMaxLineWidth		->value();
		Thr->SelfSearch			=ui->EditSelfSearch			->value();
		Thr->StartAngle			=ui->EditStartAngle			->value();
		Thr->EndAngle			=ui->EditEndAngle			->value();
		Thr->ExcludeDynamicMask	=ui->checkBoxExcludeDynamicMask	->isChecked();
		Thr->FixedAngle			=ui->checkBoxFixedAngle		->isChecked();
	}
}

void	ThresholdLineEnhancer1L::ShowLibrary(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancer1LItem	*BData=dynamic_cast<LineEnhancer1LItem *>(DA);
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

		ui->doubleSpinBoxEmphasizeRate	->setValue(BData->GetThresholdR(GetLayersBase())->EmphasizeRate);
		ui->EditMaxLineWidth			->setValue(BData->GetThresholdR(GetLayersBase())->MaxLineWidth);
		ui->EditSelfSearch				->setValue(BData->GetThresholdR(GetLayersBase())->SelfSearch);
		ui->EditStartAngle				->setValue(BData->GetThresholdR(GetLayersBase())->StartAngle);
		ui->EditEndAngle				->setValue(BData->GetThresholdR(GetLayersBase())->EndAngle);
		ui->checkBoxExcludeDynamicMask	->setChecked(BData->GetThresholdR(GetLayersBase())->ExcludeDynamicMask);

		ui->checkBoxFixedAngle			->setChecked(BData->GetThresholdR(GetLayersBase())->FixedAngle);
		on_checkBoxFixedAngle_clicked();
		return;
	}
}

void ThresholdLineEnhancer1L::on_pushButtonChangeLib_clicked()
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
			LineEnhancer1LItem	*BData=dynamic_cast<LineEnhancer1LItem *>(DA);
			if(BData==NULL)
				continue;
			int	OldID=DA->GetLibID();
			DA->SetLibID(RetSelectedLibID);

			ui->EditLibID	->setText(QString::number(DA->GetLibID()));
			for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext()){
				if(L->GetLibID()==OldID){
					L->SetLibID(RetSelectedLibID);
					ABase->GetLibraryContainer()->GetLibraryNames(LibIDList);
					ui->EditLibName	->setText(L->GetLibName());
					break;
				}
			}
		}
	}
}

void ThresholdLineEnhancer1L::on_ButtonReflectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ONE item threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_OnlyOne;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ThresholdLineEnhancer1L::on_ButtonSaveToLibrary_clicked()
{
	GetDataFromWindow();
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancer1LItem	*BData=dynamic_cast<LineEnhancer1LItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	DestLib(Container);
		if(Container->GetLibrary(LibID ,DestLib)==true){
			LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(DestLib.GetLibrary(ThresholdLevel));
			LineEnhancer1LThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->ToLibrary(ALib);
			BData->GetLibraryContainer()->Update(DestLib);
			return;
		}
	}
}

void ThresholdLineEnhancer1L::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Reflecting ALL items\' threshold");

	GetDataFromWindow();
	GUICmdSendAlgorithmItemIndependentPack	Packet(IData->Base,QString(/**/"ANY"),QString(/**/"ANY"));
	Packet.Command=SetIndependentItemDataCommand_All;
	Packet.IData=*IData;
	for(int page=0;page<GetPageNumb();page++){
		Packet.Send(NULL,page,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*10);
	GetLayersBase()->CloseProcessingForm();
}

void ThresholdLineEnhancer1L::on_ButtonLoadFromLibrary_clicked()
{
	int	ThresholdLevel=GetLayersBase()->SelectThresholdLevel();
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		LineEnhancer1LItem	*BData=dynamic_cast<LineEnhancer1LItem *>(DA);
		if(BData==NULL)
			continue;

		int	LibID=BData->GetLibID();
		AlgorithmLibraryContainer	*Container=BData->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	SrcLib(Container);
		if(Container->GetLibrary(LibID ,SrcLib)==true){
			LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(SrcLib.GetLibrary(ThresholdLevel));
			LineEnhancer1LThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
			Thr->FromLibrary(ALib);
			ShowLibrary();
			//ShowThreshold();
			return;
		}
	}
}

void ThresholdLineEnhancer1L::on_ButtonReflectSaveParts_clicked()
{
	GetDataFromWindow();

	LineEnhancer1LItem	*BData;
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		BData=dynamic_cast<LineEnhancer1LItem *>(DA);
		if(BData==NULL)
			continue;

		int	Page=D->GlobalPage;
		GUICmdReqUpdateAlgorithmOnPiece	Req(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		Req.PieceCode=BData->GetPartsID();
		Req.DLLRoot=sRoot;
		Req.DLLName=sName;
		Req.IData=*IData;
		Req.Command=SetIndependentItemDataCommand_All;
		GUICmdAckUpdateAlgorithmOnPiece	Ack(GetLayersBase() ,/**/"ANY",/**/"ANY",Page);
		if(Req.Send(Page ,0,Ack)==false)
			QMessageBox::warning (NULL, /**/"Error", /**/"Error occurs in saving algorithm data of parts" );
		while(Ack.IsReceived()==false);
		if(Ack.Ret==false){
			QMessageBox::warning (NULL, /**/"Error", /**/"Error occurs in saving algorithm data of parts" );
		}
	}
}

void ThresholdLineEnhancer1L::on_ButtonClose_clicked()
{
	close();
}

void ThresholdLineEnhancer1L::on_checkBoxFixedAngle_clicked()
{
	if(ui->checkBoxFixedAngle->isChecked()==true){
		ui->EditEndAngle	->setEnabled(false);
	}
	else{
		ui->EditEndAngle	->setEnabled(true);
	}
}
