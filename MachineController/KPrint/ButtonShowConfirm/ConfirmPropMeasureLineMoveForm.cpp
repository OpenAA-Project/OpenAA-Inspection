#include "ButtonShowConfirmResource.h"
#include "ConfirmPropMeasureLineMoveForm.h"
#include "ui_ConfirmPropMeasureLineMoveForm.h"
#include "ConfirmForm.h"
#include "XConfirmPacket.h"
#include "XIntegrationBase.h"
#include "XMeasureLineMoveLibrary.h"
#include "XMeasureLineMove.h"
#include "XPropPacketMeasureLineMove.h"
#include "CartonMenuForm.h"

ConfirmPropMeasureLineMoveForm::ConfirmPropMeasureLineMoveForm(ConfirmForm *p ,QWidget *parent) :
    ConfirmAlgorithm(p)
    ,ServiceForLayers(p->GetLayersBase())
    ,ui(new Ui::ConfirmPropMeasureLineMoveForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
}

ConfirmPropMeasureLineMoveForm::~ConfirmPropMeasureLineMoveForm()
{
    delete ui;
}

QString	ConfirmPropMeasureLineMoveForm::GetButtonName(void)
{
    return LangSolver.GetString(ConfirmPropMeasureLineMoveForm_LS,LID_18)/*"貂ｬ髟ｷ"*/;
}
int		ConfirmPropMeasureLineMoveForm::GetLibType(void)
{   
    return DefLibTypeMeasureLineMove;
}
void	ConfirmPropMeasureLineMoveForm::SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)
{
    s.Add(DefLibTypeMeasureLineMove,false,true,true);
}

void	ConfirmPropMeasureLineMoveForm::InitialShow(void)
{
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        ui->comboBoxMeasureLineMoveLineUsedLayer1->clear();
        ui->comboBoxMeasureLineMoveLineUsedLayer2->clear();
        for(int Layer=0;Layer<m->GetMaxLayerNumb();Layer++){
            ui->comboBoxMeasureLineMoveLineUsedLayer1->addItem(GetParamGlobal()->GetLayerName(Layer));
            ui->comboBoxMeasureLineMoveLineUsedLayer2->addItem(GetParamGlobal()->GetLayerName(Layer));
        }
    }
}

void	ConfirmPropMeasureLineMoveForm::AlgoMouseLDownWithShift(int ux ,int uy)
{
	GetItemsByPoint(ux, uy);
	ShowItemData();
	SetSelectItems();
	ShowResult();
}
void	ConfirmPropMeasureLineMoveForm::CanvasSlotDrawEnd(FlexArea &Area)
{
	ConfirmAlgorithm::CanvasSlotDrawEnd(Area);

	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
	if(GProp!=NULL){
		int	SlaveNo=GetSlaveNo();
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
		if(m!=NULL){
			GetItemsByArea(GProp->Param.BladeDistanceLib,Area);
			ShowItemData();
			SetSelectItems();
			ShowResult();
		}
	}
}
void	ConfirmPropMeasureLineMoveForm::SetProperty(void)
{
	ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
	if(t!=NULL){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqMeasureLineMoveItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckMeasureLineMoveItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateThresholdMeasureLineMove	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	BuffD(&ACmd.ThresholdDataDistance);
				BuffD.open(QIODevice::ReadWrite);
				Cmd.ThresholdD->Load(&BuffD);

                QBuffer	BuffL1(&ACmd.ThresholdDataLine1);
				BuffL1.open(QIODevice::ReadWrite);
				Cmd.ThresholdL1->Load(&BuffL1);

                QBuffer	BuffL2(&ACmd.ThresholdDataLine2);
				BuffL2.open(QIODevice::ReadWrite);
				Cmd.ThresholdL2->Load(&BuffL2);

				GetThresholdFromWindow(Cmd.ThresholdL1,Cmd.ThresholdL2,Cmd.ThresholdD);


				BuffD.seek(0);
				Cmd.ThresholdD->Save(&BuffD);
				BuffL1.seek(0);
				Cmd.ThresholdL1->Save(&BuffL1);
				BuffL2.seek(0);
				Cmd.ThresholdL2->Save(&BuffL2);

				IntegrationSetMeasureLineMoveItemThresholdData	SCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				SCmd.LibType=GetLibType();
				SCmd.ItemIndex=*t;
				SCmd.ThresholdDataDistance	=BuffD.buffer();
				SCmd.ThresholdDataLine1		=BuffL1.buffer();
				SCmd.ThresholdDataLine2		=BuffL2.buffer();
				SCmd.Send(NULL,SlaveNo ,t->Data.Page);
			}
		}
	}
}

void    ConfirmPropMeasureLineMoveForm::ShowThreshold(MeasureLineMoveThreshold *sLine1,MeasureLineMoveThreshold *sLine2,MeasureLineMoveThreshold *sDistance)
{
 	OnChanging=true;
	ui->doubleSpinBoxMeasureLineMoveDistanceThresholdM      ->setValue(sDistance->ThresholdM);
    ui->doubleSpinBoxMeasureLineMoveDistanceThresholdP      ->setValue(sDistance->ThresholdP);
    ui->checkBoxMeasureLineMoveDistanceModeToSetInInitial   ->setChecked(sDistance->ModeToSetInInitial);
    ui->doubleSpinBoxMeasureLineMoveDistanceOKRangeInInitial->setValue(sDistance->OKRangeInInitial);
    ui->comboBoxMeasureLineMoveDistanceOutputType           ->setCurrentIndex(sDistance->OutputType);

    ui->EditMeasureLineMoveLineSearchDot1                   ->setValue(sLine1->SearchDot);
    ui->EditMeasureLineMoveLineEdgeWidth1                   ->setValue(sLine1->EdgeWidth);
    ui->comboBoxMeasureLineMoveLineUsedLayer1               ->setCurrentIndex(sLine1->UsageLayer);

    ui->EditMeasureLineMoveLineSearchDot2                   ->setValue(sLine2->SearchDot);
    ui->EditMeasureLineMoveLineEdgeWidth2                   ->setValue(sLine2->EdgeWidth);
    ui->comboBoxMeasureLineMoveLineUsedLayer2               ->setCurrentIndex(sLine2->UsageLayer);

	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveDistanceThresholdMMM->setValue(m->TransformPixelToUnit(ui->doubleSpinBoxMeasureLineMoveDistanceThresholdM->value()));
		ui->doubleSpinBoxMeasureLineMoveDistanceThresholdPMM->setValue(m->TransformPixelToUnit(ui->doubleSpinBoxMeasureLineMoveDistanceThresholdP->value()));
		ui->doubleSpinBoxMeasureLineMoveLineSearchDot1MM->setValue(m->TransformPixelToUnit(ui->EditMeasureLineMoveLineSearchDot1->value()));
		ui->doubleSpinBoxMeasureLineMoveLineSearchDot2MM->setValue(m->TransformPixelToUnit(ui->EditMeasureLineMoveLineSearchDot2->value()));
	}

	OnChanging=false;
}
void    ConfirmPropMeasureLineMoveForm::ShowItemData(void)
{
	ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
	if(t!=NULL){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqMeasureLineMoveItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckMeasureLineMoveItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateThresholdMeasureLineMove	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	BuffD(&ACmd.ThresholdDataDistance);
				BuffD.open(QIODevice::ReadWrite);
				Cmd.ThresholdD->Load(&BuffD);

                QBuffer	BuffL1(&ACmd.ThresholdDataLine1);
				BuffL1.open(QIODevice::ReadWrite);
				Cmd.ThresholdL1->Load(&BuffL1);

                QBuffer	BuffL2(&ACmd.ThresholdDataLine2);
				BuffL2.open(QIODevice::ReadWrite);
				Cmd.ThresholdL2->Load(&BuffL2);

				ShowThreshold(Cmd.ThresholdL1,Cmd.ThresholdL2,Cmd.ThresholdD);
			}
		}
	}
}
void    ConfirmPropMeasureLineMoveForm::ShowResult(void)
{
   EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
		if(t!=NULL){
			int	SlaveNo=GetSlaveNo();
			IntegrationReqMeasureLineMoveItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckMeasureLineMoveItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.LibType=GetLibType();
			RCmd.ItemIndex=*t;
			if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
				CmdCreateThresholdMeasureLineMove	Cmd(GetLayersBase());
				AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
				if(ABase!=NULL){
					ABase->TransmitDirectly(&Cmd);
					QBuffer	BuffD(&ACmd.ThresholdDataDistance);
					BuffD.open(QIODevice::ReadWrite);
					Cmd.ThresholdD->Load(&BuffD);

					QBuffer	BuffL1(&ACmd.ThresholdDataLine1);
					BuffL1.open(QIODevice::ReadWrite);
					Cmd.ThresholdL1->Load(&BuffL1);

					QBuffer	BuffL2(&ACmd.ThresholdDataLine2);
					BuffL2.open(QIODevice::ReadWrite);
					Cmd.ThresholdL2->Load(&BuffL2);

					GetThresholdFromWindow(Cmd.ThresholdL1,Cmd.ThresholdL2,Cmd.ThresholdD);


					BuffD.seek(0);
					Cmd.ThresholdD->Save(&BuffD);
					BuffL1.seek(0);
					Cmd.ThresholdL1->Save(&BuffL1);
					BuffL2.seek(0);
					Cmd.ThresholdL2->Save(&BuffL2);

					IntegrationReqMeasureLineMoveTryResult	RTryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					IntegrationAckMeasureLineMoveTryResult	ATryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RTryCmd.ThresholdDataDistance=BuffD.buffer();
					RTryCmd.ThresholdDataLine1	 =BuffL1.buffer();
					RTryCmd.ThresholdDataLine2	 =BuffL2.buffer();
					RTryCmd.ItemIndex=*t;
					if(RTryCmd.Send(SlaveNo ,t->Data.Page,ATryCmd)==true){
						ui->labelMeasureLineMoveDistanceLengthUnit->setText(QString::number(ATryCmd.Distance,'f',2));

					}
				}
			}
		}
	}
}
void    ConfirmPropMeasureLineMoveForm::GetThresholdFromWindow(MeasureLineMoveThreshold *sLine1,MeasureLineMoveThreshold *sLine2,MeasureLineMoveThreshold *sDistance)
{
    sDistance->ThresholdM           =ui->doubleSpinBoxMeasureLineMoveDistanceThresholdM      ->value();
    sDistance->ThresholdP           =ui->doubleSpinBoxMeasureLineMoveDistanceThresholdP      ->value();
    sDistance->ModeToSetInInitial   =ui->checkBoxMeasureLineMoveDistanceModeToSetInInitial   ->isChecked();
    sDistance->OKRangeInInitial     =ui->doubleSpinBoxMeasureLineMoveDistanceOKRangeInInitial->value();
    sDistance->OutputType           =ui->comboBoxMeasureLineMoveDistanceOutputType           ->currentIndex();

    sLine1->SearchDot               =ui->EditMeasureLineMoveLineSearchDot1                   ->value();
    sLine1->EdgeWidth               =ui->EditMeasureLineMoveLineEdgeWidth1                   ->value();
    sLine1->UsageLayer              =ui->comboBoxMeasureLineMoveLineUsedLayer1               ->currentIndex();

    sLine2->SearchDot               =ui->EditMeasureLineMoveLineSearchDot2                   ->value();
    sLine2->EdgeWidth               =ui->EditMeasureLineMoveLineEdgeWidth2                   ->value();
    sLine2->UsageLayer              =ui->comboBoxMeasureLineMoveLineUsedLayer2               ->currentIndex();
}

void	ConfirmPropMeasureLineMoveForm::GetItemsByPoint(int GlobalX, int GlobalY)
{
    EachMaster	*m=Parent->GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		IntegrationReqMeasureLineMoveSelectItems	RCmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		RCmd.SelectedLib.SetLibType(GetLibType());
		RCmd.SelectedLib.SetLibID(-1);
		RCmd.Phase	=m->GetCurrentPhase();
		RCmd.GlobalX=GlobalX;
		RCmd.GlobalY=GlobalY;
		RCmd.Mode=1;
		IntegrationAckMeasureLineMoveSelectItems	ACmd(Parent->GetLayersBase(),sRoot,sName,GetSlaveNo());
		if(RCmd.Send(GetSlaveNo(),0,ACmd)==true){
			SelectedItems=ACmd.Items;
		}
	}
}
void	ConfirmPropMeasureLineMoveForm::ForceDraw(void)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveDistanceThresholdM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveDistanceThresholdMMM->setValue(m->TransformPixelToUnit(ui->doubleSpinBoxMeasureLineMoveDistanceThresholdM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveDistanceThresholdMMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveDistanceThresholdM->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMeasureLineMoveDistanceThresholdMMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveDistanceThresholdP_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveDistanceThresholdPMM->setValue(m->TransformPixelToUnit(ui->doubleSpinBoxMeasureLineMoveDistanceThresholdP->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveDistanceThresholdPMM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveDistanceThresholdP->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMeasureLineMoveDistanceThresholdPMM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_checkBoxMeasureLineMoveDistanceModeToSetInInitial_clicked()
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveDistanceOKRangeInInitial_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_comboBoxMeasureLineMoveDistanceOutputType_currentIndexChanged(int index)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_EditMeasureLineMoveLineSearchDot1_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveLineSearchDot1MM->setValue(m->TransformPixelToUnit(ui->EditMeasureLineMoveLineSearchDot1->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveLineSearchDot1MM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditMeasureLineMoveLineSearchDot1->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMeasureLineMoveLineSearchDot1MM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_EditMeasureLineMoveLineEdgeWidth1_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_comboBoxMeasureLineMoveLineUsedLayer1_currentIndexChanged(int index)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_EditMeasureLineMoveLineSearchDot2_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->doubleSpinBoxMeasureLineMoveLineSearchDot2MM->setValue(m->TransformPixelToUnit(ui->EditMeasureLineMoveLineSearchDot2->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_doubleSpinBoxMeasureLineMoveLineSearchDot2MM_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ui->EditMeasureLineMoveLineSearchDot2->setValue(m->TransformUnitToPixel(ui->doubleSpinBoxMeasureLineMoveLineSearchDot2MM->value()));
	}
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_EditMeasureLineMoveLineEdgeWidth2_valueChanged(int arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropMeasureLineMoveForm::on_comboBoxMeasureLineMoveLineUsedLayer2_currentIndexChanged(int index)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}
void	ConfirmPropMeasureLineMoveForm::ShowConfirmItem(ConfirmItemList *Item)
{
	SelectedItems.RemoveAll();
	SelectedItems.Add(Item->Phase ,Item->Page ,Item->Layer,Item->ItemID);

	SetEnableChangeMode(false);
	ShowItemData();
	SetSelectItems();
	ShowResult();
	SetEnableChangeMode(true);
}
