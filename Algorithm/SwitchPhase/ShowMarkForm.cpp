#include "SwitchPhaseResource.h"
#include "ShowMarkForm.h"
#include "ui_ShowMarkForm.h"
#include "XDataInLayerCommander.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "swap.h"

ShowMarkForm::ShowMarkForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this),
    ui(new Ui::ShowMarkForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	OnChanging=false;
	IData=NULL;

	InstallOperationLog(this);
}

ShowMarkForm::~ShowMarkForm()
{
    delete ui;
}

void	ShowMarkForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			DA->SetParentPointer(InstBase,D->PhaseCode,D->GlobalPage,D->Layer);
			SwitchPhaseItem	*BData=dynamic_cast<SwitchPhaseItem *>(DA);
			if(BData!=NULL){
				ui->spinBoxSearchDot	->setValue(BData->GetThresholdR(GetLayersBase())->SearchDot);
				BData->TF_EnumHistList(HContainer);
				break;
			}
		}
	}
}

void	ShowMarkForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		SwitchPhaseItem	*BData=dynamic_cast<SwitchPhaseItem *>(DA);
		if(BData==NULL)
			continue;

		BData->GetThresholdW()->SearchDot		=ui->spinBoxSearchDot	->value();
		//return;
	}
}

void ShowMarkForm::on_tableWidgetPhaseList_clicked(const QModelIndex &index)
{

}

void ShowMarkForm::on_ButtonReflectOnlyBlock_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowMarkForm_LS,LID_0)/*"Change one point"*/);

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

void ShowMarkForm::on_ButtonReflectAllBlocks_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowMarkForm_LS,LID_1)/*"Change all points"*/);

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

void ShowMarkForm::on_ButtonClose_clicked()
{
	close();
}
