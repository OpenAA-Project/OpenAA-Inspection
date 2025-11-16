#include "VCutInspectionResource.h"
#include "ShowSettingVCutForm.h"
#include "ui_ShowSettingVCutForm.h"
#include "XVCutInspection.h"
#include "XDataInLayer.h"
#include "XDataInLayerCommander.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DisplaySimPanelVCutInspection::DisplaySimPanelVCutInspection(LayersBase *base ,ShowSettingVCutForm *parentw ,QWidget *parent)
	:DisplaySimPanel(base ,parent)
{
	ParentWidget=parentw;
}

void	DisplaySimPanelVCutInspection::DrawOther(QPainter &Pnt)
{
	if(ParentWidget->ModeShowItem==true && Result!=NULL){
		QRgb ItemCol=qRgba(60,180,0,120);
		ItemArea.DrawAlpha(0,0
						//Result->GetAlignedX()
						//,  Result->GetAlignedY()
						,ResultImage ,ItemCol
						,ZoomRate ,MovX ,MovY);
	}
	/*
	if(ParentWidget->ModeShowNGMark==true && Result!=NULL){
		QRgb NGMarkCol=qRgba(200,160,0,120);
		for(ResultPosList *r=Result->GetPosListFirst();r!=NULL;r=r->GetNext()){
			r->NGShape.DrawAlpha(Result->GetAlignedX()+r->Rx
								,Result->GetAlignedY()+r->Ry
								,ResultImage ,NGMarkCol
								,ZoomRate ,MovX ,MovY);
		}
	}
	*/
}


ShowSettingVCutForm::ShowSettingVCutForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),PasswordInQWodget(Base,this)
    ,ui(new Ui::ShowSettingVCutForm)
	,SimPanel(Base,this,parent)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	//OnChanging=false;
	IData=NULL;
	SimPanel.setParent(ui->frame_SimImage);
	SimPanel.SetAlgo(sRoot,sName);
	SimPanel.SetGUI(/**/"Button",/**/"PropertyDotMatchingForm");
	SimPanel.setGeometry(0,0,ui->frame_SimImage->width(),ui->frame_SimImage->height());

	InstallOperationLog(this);
}

ShowSettingVCutForm::~ShowSettingVCutForm()
{
    delete ui;
}

void	ShowSettingVCutForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		SimPanel.SetLayer(0);
		AlgorithmItemRoot	*DA=D->Data;
		if(DA!=NULL){
			VCutInspectionItem	*BData=dynamic_cast<VCutInspectionItem *>(DA);
			if(BData!=NULL){
				SimPanel.SetGlobalPage(D->GlobalPage);
				SimPanel.SetInitial(BData->GetID(),BData->GetArea());
				SimPanel.SetModeShowBlock		(ui->toolButtonSimShowItem ->isChecked());
				ModeShowItem	=ui->toolButtonSimShowItem ->isChecked();

				ui->EditThresholdLevel		->setValue(BData->GetThresholdR(GetLayersBase())->ThresholdLevel	);
				ui->EditThresholdShift		->setValue(BData->GetThresholdR(GetLayersBase())->ThresholdShift	);
				ui->EditThresholdLength		->setValue(BData->GetThresholdR(GetLayersBase())->ThresholdLength	);
				ui->checkBoxGenDynamicMask	->setChecked(BData->GetThresholdR(GetLayersBase())->GenDynamicMask	);
				ui->EditExpandGenMask		->setValue(BData->GetThresholdR(GetLayersBase())->ExpandGenMask	);
				BData->TF_EnumHistList(HContainer);
				break;
			}
		}
	}
}

void	ShowSettingVCutForm::GetDataFromWindow(void)
{
	for(AlgorithmItemIndependent *D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		VCutInspectionItem	*BData=dynamic_cast<VCutInspectionItem *>(DA);
		if(BData==NULL)
			continue;
		VCutInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->ThresholdLevel	=ui->EditThresholdLevel		->value();
		Thr->ThresholdShift	=ui->EditThresholdShift		->value();
		Thr->ThresholdLength=ui->EditThresholdLength	->value();
		Thr->GenDynamicMask	=ui->checkBoxGenDynamicMask	->isChecked();
		Thr->ExpandGenMask	=ui->EditExpandGenMask		->value();
		//return;
	}
}

void ShowSettingVCutForm::Calc(void)
{
	for(AlgorithmItemIndependent	*D=IData->Items.GetFirst();D!=NULL;D=D->GetNext()){
		AlgorithmItemRoot	*DA=D->Data;
		if(DA==NULL)
			continue;
		VCutInspectionItem	*nBData=dynamic_cast<VCutInspectionItem *>(DA);
		if(nBData==NULL)
			continue;

		GUICmdReqAlgorithmGeneralData	PacketReq(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		PacketReq.BuildData(sRoot,sName,VCutReqTryThresholdCommand ,VCutSendTryThresholdCommand);
		VCutInspectionItem	*BData	=&((VCutReqTryThreshold *)PacketReq.Data)->Threshold;
		((VCutReqTryThreshold *)PacketReq.Data)->GlobalPage	=D->GlobalPage;
		((VCutReqTryThreshold *)PacketReq.Data)->ItemID		=DA->GetID();
		VCutInspectionThreshold	*Thr=BData->GetThresholdW(GetLayersBase());

		Thr->ThresholdLevel	=ui->EditThresholdLevel		->value();
		Thr->ThresholdShift	=ui->EditThresholdShift		->value();
		Thr->ThresholdLength=ui->EditThresholdLength	->value();
		Thr->GenDynamicMask	=ui->checkBoxGenDynamicMask	->isChecked();
		Thr->ExpandGenMask	=ui->EditExpandGenMask		->value();

		GUICmdSendAlgorithmGeneralData	PacketSend(IData->Base,/**/"ANY",/**/"ANY",D->GlobalPage);
		if(PacketReq.Send(D->GlobalPage,0,PacketSend)==true){

			VCutSendTryThreshold	*R=((VCutSendTryThreshold *)PacketSend.Data);

			ui->EditShowShiftXY->setText(QString::number(R->Result->GetTotalShiftedX())
										+QString(/**/",")
										+QString::number(R->Result->GetTotalShiftedY()));

			if(R->ResultMinDifference<99999999)
				ui->EditResultMinDifference->setText(QString::number(R->ResultMinDifference));
			else
				ui->EditResultMinDifference->setText(/**/"OK");
			SimPanel.SetResult(R->Result);
			SimPanel.repaint();
			break;
		}
	}	
}

void ShowSettingVCutForm::on_pushButtonSetOne_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowSettingVCutForm_LS,LID_9)/*"Change one Line"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change one Line");
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

void ShowSettingVCutForm::on_pushButtonSetAll_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ShowSettingVCutForm_LS,LID_10)/*"Change all Lines"*/);

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Change all Lines");
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

void ShowSettingVCutForm::on_pushButtonClose_clicked()
{
	close();
}

void ShowSettingVCutForm::on_toolButtonSimShowItem_clicked()
{
	Calc();
}

void ShowSettingVCutForm::on_toolButtonSimShowNGMark_clicked()
{
	Calc();
}

void ShowSettingVCutForm::on_pushButtonSimShowCenterPos_clicked()
{
	Calc();
}

void ShowSettingVCutForm::on_EditThresholdLevel_valueChanged(int arg1)
{
	Calc();
}

void ShowSettingVCutForm::on_EditThresholdShift_valueChanged(int arg1)
{
	Calc();
}

void ShowSettingVCutForm::on_EditThresholdLength_valueChanged(int arg1)
{
	Calc();
}

void ShowSettingVCutForm::on_EditExpandGenMask_valueChanged(int arg1)
{
	Calc();
}

void ShowSettingVCutForm::on_checkBoxGenDynamicMask_clicked()
{
	Calc();
}

void ShowSettingVCutForm::on_EditThresholdLevel_valueChanged(double arg1)
{
    Calc();
}
