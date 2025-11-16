#include "AdjustAlignmentBlockForm.h"
#include "ui_AdjustAlignmentBlockForm.h"
#include "XDataInLayerCommander.h"
#include "XAlignmentBlock.h"
#include "XPieceArchitect.h"
#include "XGeneralDialog.h"
#include "swap.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

DisplaySimPanelAlignmentBlock::DisplaySimPanelAlignmentBlock(LayersBase *base ,AdjustAlignmentBlockForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
}

	
//======================================================================================
AdjustAlignmentBlockForm::AdjustAlignmentBlockForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base),PasswordInQWodget(Base,this)
	,SimPanel(Base,this,parent)
    ,ui(new Ui::AdjustAlignmentBlockForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	OnChanging	=false;
	IData		=NULL;
	Preparing	=true;

	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(sRoot,sName);
	SimPanel.SetGUI(/**/"Button",/**/"PropertyDotColorMatching");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());

	InstallOperationLog(this);
}

AdjustAlignmentBlockForm::~AdjustAlignmentBlockForm()
{
    delete ui;
}

void	AdjustAlignmentBlockForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;
	GlobalPage=0;
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(-1);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			AlignmentBlockItem	*BData=dynamic_cast<AlignmentBlockItem *>(DA);
			if(BData!=NULL){
				ui->spinBoxItemID->setValue(BData->GetID());
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock	(ui->toolButtonSimShowItem ->isChecked());
				ModeShowItem	=ui->toolButtonSimShowItem ->isChecked();
			}
		}
	}

	ShowDataToWindow();
}
void	AdjustAlignmentBlockForm::showEvent ( QShowEvent * event )
{
	Preparing=false;
	ShowCalc();
}
void	AdjustAlignmentBlockForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		AlignmentBlockItem	*BData=dynamic_cast<AlignmentBlockItem *>(DA);
		if(BData==NULL)
			continue;
		AlignmentBlockThreshold	*Thr=BData->GetThresholdW(GetLayersBase());
		Thr->SearchDot		=ui->spinBoxSearchDot		->value();
		Thr->MaxDegree		=ui->doubleSpinBoxMaxDegree	->value();
		Thr->LineLength		=ui->spinBoxLineLength		->value();
		Thr->MinVar			=ui->doubleSpinBoxMinVar	->value();

		//return;
	}
}
void	AdjustAlignmentBlockForm::ShowDataToWindow(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			AlignmentBlockItem	*BData=dynamic_cast<AlignmentBlockItem *>(DA);
			if(BData!=NULL){
				const	AlignmentBlockThreshold	*Thr=BData->GetThresholdR(GetLayersBase());
				ui->spinBoxSearchDot		->setValue(Thr->SearchDot	);
				ui->doubleSpinBoxMaxDegree	->setValue(Thr->MaxDegree	);
				ui->spinBoxLineLength		->setValue(Thr->LineLength	);
				ui->doubleSpinBoxMinVar		->setValue(Thr->MinVar		);
				break;
			}
		}
	}
}

void AdjustAlignmentBlockForm::on_pushButtonSetOne_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change one point");

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


void AdjustAlignmentBlockForm::on_pushButtonSetAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Change all points");

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

void AdjustAlignmentBlockForm::on_pushButtonClose_clicked()
{
	close();
}


void AdjustAlignmentBlockForm::on_spinBoxSearchDot_valueChanged(int arg1)
{
	ShowCalc();
}


void AdjustAlignmentBlockForm::on_doubleSpinBoxMaxDegree_valueChanged(double arg1)
{
	ShowCalc();
}


void AdjustAlignmentBlockForm::on_spinBoxLineLength_valueChanged(int arg1)
{
	ShowCalc();
}


void AdjustAlignmentBlockForm::on_doubleSpinBoxMinVar_valueChanged(double arg1)
{
	ShowCalc();
}

void AdjustAlignmentBlockForm::ShowCalc(void)
{
	if(Preparing==false){
		for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
			AlgorithmItemRoot	*DA=D->Data;
			if(DA==NULL)
				continue;
			AlignmentBlockItem	*nBData=dynamic_cast<AlignmentBlockItem *>(DA);
			if(nBData==NULL)
				continue;

			GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			PacketReq.BuildData(sRoot,sName,AlignmentBlockReqTryThresholdCommand ,AlignmentBlockSendTryThresholdCommand);
			AlignmentBlockItem	*BData=&((AlignmentBlockReqTryThreshold *)PacketReq.Data)->Threshold;
			((AlignmentBlockReqTryThreshold *)PacketReq.Data)->GlobalPage			=D->GlobalPage;
			((AlignmentBlockReqTryThreshold *)PacketReq.Data)->AlignmentBlockItemID	=DA->GetID();

			AlignmentBlockThreshold	*DThr=BData->GetThresholdW(GetLayersBase());


			DThr->SearchDot		=ui->spinBoxSearchDot	->value();
			DThr->MaxDegree		=ui->doubleSpinBoxMaxDegree	->value();
			DThr->LineLength	=ui->spinBoxLineLength	->value();
			DThr->MinVar		=ui->doubleSpinBoxMinVar	->value();

			GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
			if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

				AlignmentBlockSendTryThreshold	*R=((AlignmentBlockSendTryThreshold *)PacketSend.Data);

				ui->EditShowShiftXY->setText(QString::number(R->Result->GetTotalShiftedX())
											+QString(/**/",")
											+QString::number(R->Result->GetTotalShiftedY()));


				SimPanel.SetResult(R->Result);
				SimPanel.repaint();
				break;
			}
		}
	}
}

void AdjustAlignmentBlockForm::on_pushButtonCalc_clicked()
{
	ShowCalc();
}

