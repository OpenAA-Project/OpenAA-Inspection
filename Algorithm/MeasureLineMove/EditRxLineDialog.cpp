#include "XMeasureLineMoveResource.h"
#include "EditRxLineDialog.h"
#include "ui_EditRxLineDialog.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "swap.h"
#include "XMeasureLineMove.h"
#include "XGeneralDialog.h"
#include "EditItemIDDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

EditRxLineDialog::EditRxLineDialog(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),
    ui(new Ui::EditRxLineDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	IData		=NULL;
	OnChanging	=false;
	HistgramPage=-1;

	InstallOperationLog(this);
}

EditRxLineDialog::~EditRxLineDialog()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void	EditRxLineDialog::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	AlgorithmLibraryContainerForEnum		LibList(InstBase->GetLayersBase());
	LibIDList.RemoveAll();
	LibList.EnumAllLibraries(GetLayersBase()->GetDatabase(),InstBase->GetLibType(),LibIDList);

	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureLineMoveRxLineItem	*BData=dynamic_cast<MeasureLineMoveRxLineItem *>(DA);
		if(BData==NULL)
			continue;
		HistgramPage=D->GlobalPage;
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
		ui->EditItemID			->setText(QString::number(BData->GetID()));
		ui->spinBoxRxID			->setValue(BData->RxID	);
		ui->spinBoxHookedItemID	->setValue(BData->HookedItemID);
		ui->checkBoxEnable		->setChecked(BData->IsEffective());
		ui->EditName			->setText(BData->GetItemName());
	}

	ui->labelUnitName_4	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_7	->setText(GetParamGlobal()->UnitName);
	ui->labelUnitName_8	->setText(GetParamGlobal()->UnitName);
}

void EditRxLineDialog::on_pushButtonChangeLib_clicked()
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
			MeasureLineMoveItemBase	*BData=dynamic_cast<MeasureLineMoveItemBase *>(DA);
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


void	EditRxLineDialog::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		MeasureLineMoveRxLineItem	*BData=dynamic_cast<MeasureLineMoveRxLineItem *>(DA);
		if(BData==NULL)
			continue;

		BData->RxID			=ui->spinBoxRxID->value();
		BData->HookedItemID	=ui->spinBoxHookedItemID->value();
		BData->SetEffective(ui->checkBoxEnable->isChecked());
		BData->SetItemName(ui->EditName	->text());
		return;
	}
}

void EditRxLineDialog::on_ButtonRelrectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(EditLineDialog_LS,LID_17)/*"Reflecting ONE item threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect one item threshold");
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


void EditRxLineDialog::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(EditLineDialog_LS,LID_18)/*"Reflecting ALL items\' threshold"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Reflect all items threshold");
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


void EditRxLineDialog::on_pushButtonTest_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;

		MeasureLineMoveItemBase	*nBData=dynamic_cast<MeasureLineMoveItemBase *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,ReqTryThresholdCommand ,SendTryThresholdCommand);
		MeasureLineMoveRxLineItem	*BData=(MeasureLineMoveRxLineItem *)&((LineMoveReqTryThreshold *)PacketReq.Data)->ItemRxLine;
		((LineMoveReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((LineMoveReqTryThreshold *)PacketReq.Data)->ItemID		=DA->GetID();

		BData->RxID			=ui->spinBoxRxID->value();
		BData->HookedItemID	=ui->spinBoxHookedItemID->value();
		BData->SetEffective(ui->checkBoxEnable->isChecked());

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			LineMoveSendTryThreshold	*R=((LineMoveSendTryThreshold *)PacketSend.Data);

			ui->labelPosDiffX->setText(QString::number(R->PosDiffX	));
			ui->labelPosDiffY->setText(QString::number(R->PosDiffY	));

			ui->labelPosDiffXUnit->setText(TransformPixelToUnitStr(HistgramPage,R->PosDiffX	));
			ui->labelPosDiffYUnit->setText(TransformPixelToUnitStr(HistgramPage,R->PosDiffY	));
			break;
		}
	}
}


void EditRxLineDialog::on_ButtonClose_clicked()
{
	close();
}


void EditRxLineDialog::on_pushButtonUpdateRxValue_clicked()
{

}


void EditRxLineDialog::on_pushButtonChangeItemID_clicked()
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		EditItemIDDialog	EDialog(GetLayersBase());
		EDialog.Initial(GetLayersBase()->GetAlgorithmBase(sRoot,sName)
				,DA->GetPhaseCode(),DA->GetPage(),DA->GetLayer()
				,DA->GetID(), DA->GetID()
                ,true);
		EDialog.exec();
		DA->SetID(EDialog.NewItemID);
		ui->EditItemID	->setText(QString::number(DA->GetID()));
		break;
	}
}

