#include "ButtonShowConfirmResource.h"
#include "ConfirmPropAlignmentForm.h"
#include "ui_ConfirmPropAlignmentForm.h"
#include "ConfirmForm.h"
#include "XConfirmPacket.h"
#include "XAlignmentLargeLibrary.h"
#include "XPropPacketAlignment.h"
#include "ButtonShowConfirm.h"

ConfirmPropAlignmentForm::ConfirmPropAlignmentForm(ConfirmForm *p ,QWidget *parent) :
    ConfirmAlgorithm(p)
    ,ServiceForLayers(p->GetLayersBase())
    ,ui(new Ui::ConfirmPropAlignmentForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
    AreaListInPage  =NULL;
    MarkListInArea =NULL;

    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,0, 35);
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,1, 20);
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,2, 20);
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,3, 25);
}

ConfirmPropAlignmentForm::~ConfirmPropAlignmentForm()
{
    delete ui;

    if(AreaListInPage!=NULL){
        delete  []AreaListInPage;
        AreaListInPage=NULL;
    }
    if(MarkListInArea!=NULL){
        delete  MarkListInArea;
        MarkListInArea=NULL;
    }
}

QString	ConfirmPropAlignmentForm::GetButtonName(void)
{
    return LangSolver.GetString(ConfirmPropAlignmentForm_LS,LID_4)/*"菴咲ｽｮ蜷医ｏ縺�*/;
}

void	ConfirmPropAlignmentForm::InitialShow(void)
{
    ui->stackedWidgetAlignmentLarge->setCurrentIndex(0);
    ui->listWidgetAlignmentLargeArea->clear();
    int AreaNumb=0;
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        if(AreaListInPage!=NULL){
            delete  []AreaListInPage;
        }
        AreaListInPage=new AlignmentAreaListContainer[m->GetPageNumb()];

        for(int page=0;page<m->GetPageNumb();page++){
            IntegrationReqAlignmentAreaInfo RCmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
            RCmd.Phase  =m->GetCurrentPhase();
            IntegrationAckAlignmentAreaInfo ACmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
            if(RCmd.Send(GetSlaveNo(),m->GetLocalPageFromGlobal(page),ACmd)==true){
                AreaListInPage[page]=ACmd.Container;
                for(AlignmentAreaList *a=AreaListInPage[page].GetFirst();a!=NULL;a=a->GetNext()){
                    ui->listWidgetAlignmentLargeArea->addItem(a->GetPriorityString());
                    AreaNumb++;
                }
            }
        }
    }

    if(AreaNumb!=0){
        ui->listWidgetAlignmentLargeArea->setCurrentRow(0);
        on_toolButtonAlignmentLargeArea_clicked();
    }
}
int		ConfirmPropAlignmentForm::GetLibType(void)
{   
    return DefLibTypeAlignmentLarge;
}
void	ConfirmPropAlignmentForm::SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)
{
    s.Add(DefLibTypeAlignmentLarge,false,true,false);
}

void	ConfirmPropAlignmentForm::AlgoMouseMove(int ux ,int uy)
{
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        ConfirmAlgorithm::AlgoMouseMove(ux ,uy);

        int localX ,localY;
        int Page=m->GetLocalMatrixFromGlobal(ux,uy ,localX ,localY);
        if(Page>=0){
            IntegrationReqAlignmentPointResult RCmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
            RCmd.Phase=m->GetCurrentPhase();
            RCmd.localX=localX;
            RCmd.localY=localY;
            IntegrationAckAlignmentPointResult ACmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
            if(RCmd.Send(GetSlaveNo(),Page,ACmd)==true){
                ui->labelResultAlignmentLargeShiftX->setText(QString::number(ACmd.ShiftX));
                ui->labelResultAlignmentLargeShiftY->setText(QString::number(ACmd.ShiftY));
                ui->labelResultAlignmentLargeAngle ->setText(QString::number(ACmd.RotationRadian*180.0/M_PI,'f',2));

                double  ShiftXMM=m->TransformPixelToUnit(ACmd.ShiftX);
                ui->labelResultAlignmentLargeShiftXMM->setText(QString::number(ShiftXMM,'f',2));
                double  ShiftYMM=m->TransformPixelToUnit(ACmd.ShiftY);
                ui->labelResultAlignmentLargeShiftYMM->setText(QString::number(ShiftYMM,'f',2));
            }
        }
    }
}

void	ConfirmPropAlignmentForm::SetProperty(void)
{
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){    int Row= ui->tableWidgetAlignmentLargeMark->currentRow();
        if(Row>=0){
            AlignmentMarkList *A=MarkListInArea->GetItem(Row);
            if(A!=NULL){
                int AreaRow= ui->listWidgetAlignmentLargeArea->currentRow();
                int n=0;
                for(int page=0;page<m->GetPageNumb();page++){
                    for(AlignmentAreaList *a=AreaListInPage[page].GetFirst();a!=NULL;a=a->GetNext()){
                        if(AreaRow==n){
		                    int	SlaveNo=GetSlaveNo();
		                    IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		                    IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		                    RCmd.LibType=GetLibType();
		                    RCmd.ItemIndex.Data.Phase=m->GetCurrentPhase();
                            RCmd.ItemIndex.Data.Layer=a->Layer;
                            RCmd.ItemIndex.Data.Page=page;
                            RCmd.ItemIndex.Data.ItemID=A->MarkThresholdData.ItemID;
		                    if(RCmd.Send(SlaveNo ,m->GetLocalPageFromGlobal(page),ACmd)==true){
		                    	CmdCreateAlignmentLargeThreshold	Cmd(GetLayersBase());
		                    	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
		                    	if(ABase!=NULL){
		                    		ABase->TransmitDirectly(&Cmd);
		                    		QBuffer	Buff(&ACmd.ThresholdData);
		                    		Buff.open(QIODevice::ReadWrite);
		                    		Cmd.Threshold->Load(&Buff);
		                    		GetThresholdFromWindow(Cmd.Threshold);
		                    		Buff.seek(0);
		                    		Cmd.Threshold->Save(&Buff);

		                    		IntegrationSetItemThresholdData	SCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		                    		SCmd.LibType=GetLibType();
		                    		SCmd.ItemIndex.Data.Phase=m->GetCurrentPhase();
                                    SCmd.ItemIndex.Data.Layer=a->Layer;
                                    SCmd.ItemIndex.Data.Page=page;
                                    SCmd.ItemIndex.Data.ItemID=A->MarkThresholdData.ItemID;
		                    		SCmd.ThresholdData=Buff.buffer();
		                    		SCmd.Send(NULL,SlaveNo ,m->GetLocalPageFromGlobal(page));
		                    	}
		                    }
                        }
                    }
                }
            }
        }
	}
}

void    ConfirmPropAlignmentForm::GetThresholdFromWindow(AlignmentLargeThreshold *s)
{
    s->MoveDotX         =ui->spinBoxAlignmentLargeSearchDot  ->value();
    s->MoveDotY         =ui->spinBoxAlignmentLargeSearchDotY ->value();
    s->MoveDotX2        =ui->spinBoxAlignmentLargeSearchDot2 ->value();
    s->MoveDotY2        =ui->spinBoxAlignmentLargeSearchDot2Y->value();
    
    s->MaxCountHLine    =ui->spinBoxAlignmentLargeMaxCountHLine  ->value();
    s->MaxCountVLine    =ui->spinBoxAlignmentLargeMaxCountVLine  ->value();
    s->JudgeWithBrDif   =ui->checkBoxAlignmentLargeJudgeWithBrDif->isChecked();
}

void ConfirmPropAlignmentForm::on_toolButtonAlignmentLargeArea_clicked()
{
    if(MarkListInArea!=NULL){
        delete  MarkListInArea;
        MarkListInArea=NULL;
    }
    int Row= ui->listWidgetAlignmentLargeArea->currentRow();
    ShowMarkList(Row);
}

void ConfirmPropAlignmentForm::ShowMarkList(int AreaRow)
{
    static  bool    ReEntrant=false;

    if(ReEntrant==true)
        return;
    ReEntrant=true;

    if(AreaRow>=0){
        EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
        if(m!=NULL){
            int n=0;
             for(int page=0;page<m->GetPageNumb();page++){
                 for(AlignmentAreaList *a=AreaListInPage[page].GetFirst();a!=NULL;a=a->GetNext()){
                     if(AreaRow==n){
                        IntegrationReqAlignmentMarkInfo RCmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
                        IntegrationAckAlignmentMarkInfo ACmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
                        RCmd.AreaID=a->AreaID;
                        RCmd.Phase  =m->GetCurrentPhase();
                        RCmd.Layer  =a->Layer;
                        if(RCmd.Send(GetSlaveNo(),m->GetLocalPageFromGlobal(page),ACmd)==true){
                            MarkListInArea=new AlignmentMarkListContainer();
                            *MarkListInArea=ACmd.Container;
                        }
                     }
                     n++;
                 }
             }
        }
    }
    ui->stackedWidgetAlignmentLarge->setCurrentIndex(0);

    if(MarkListInArea!=NULL){
        int N=MarkListInArea->GetCount();
        if(ui->tableWidgetAlignmentLargeMark->rowCount()!=N){
            ui->tableWidgetAlignmentLargeMark->setRowCount(N);
        }
        int row=0;
        for(AlignmentMarkList *a=MarkListInArea->GetFirst();a!=NULL;a=a->GetNext(),row++){
            ::SetDataToTable(ui->tableWidgetAlignmentLargeMark, 0, row, QString::number(a->MarkThresholdData.x1)+QString(/**/",")+QString::number(a->MarkThresholdData.y1)
                                                                        +QString(/**/"-")
                                                                        +QString::number(a->MarkThresholdData.x2)+QString(/**/",")+QString::number(a->MarkThresholdData.y2));
            ::SetDataToTable(ui->tableWidgetAlignmentLargeMark, 1, row, QString::number(a->MarkThresholdData.MoveDotX)+QString(/**/",")+QString::number(a->MarkThresholdData.MoveDotY));
            ::SetDataToTable(ui->tableWidgetAlignmentLargeMark, 2, row, QString::number(a->MarkThresholdData.MoveDotX2)+QString(/**/",")+QString::number(a->MarkThresholdData.MoveDotY2));
            ::SetDataToTable(ui->tableWidgetAlignmentLargeMark, 3, row, QString::number(a->MatchingRate,'f',3));
        }
    }
    else{
        ui->tableWidgetAlignmentLargeMark->setRowCount(0);
    }
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,0, 35);
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,1, 20);
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,2, 20);
    ::SetColumnWidthInTable(ui->tableWidgetAlignmentLargeMark,3, 25);

    ReEntrant=false;
}

void ConfirmPropAlignmentForm::on_toolButtonAlignmentLargeMark_clicked()
{
    ui->stackedWidgetAlignmentLarge->setCurrentIndex(1);
}

void	ConfirmPropAlignmentForm::ForceDraw(void)
{
     int Row= ui->listWidgetAlignmentLargeArea->currentRow();
     ShowMarkList(Row);
}
void ConfirmPropAlignmentForm::on_listWidgetAlignmentLargeArea_itemSelectionChanged()
{
    if(ui->listWidgetAlignmentLargeArea->updatesEnabled()==true){
        int AreaRow= ui->listWidgetAlignmentLargeArea->currentRow();
        if(AreaRow<0)
            return;
        ShowMarkList(AreaRow);
    }
}

void ConfirmPropAlignmentForm::on_tableWidgetAlignmentLargeMark_itemSelectionChanged()
{
    int AreaRow= ui->listWidgetAlignmentLargeArea->currentRow();
    if(AreaRow<0)
        return;
    ShowMarkList(AreaRow);

    int Row= ui->tableWidgetAlignmentLargeMark->currentRow();
    if(Row>=0){
        AlignmentMarkList *a=MarkListInArea->GetItem(Row);
        if(a!=NULL){
            ZoomArea(a->MarkThresholdData.x1,a->MarkThresholdData.y1,a->MarkThresholdData.x2,a->MarkThresholdData.y2);

            ui->spinBoxAlignmentLargeSearchDot  ->setValue(a->MarkThresholdData.MoveDotX);
            ui->spinBoxAlignmentLargeSearchDotY ->setValue(a->MarkThresholdData.MoveDotY);
            ui->spinBoxAlignmentLargeSearchDot2 ->setValue(a->MarkThresholdData.MoveDotX2);
            ui->spinBoxAlignmentLargeSearchDot2Y->setValue(a->MarkThresholdData.MoveDotY2);

            ui->spinBoxAlignmentLargeMaxCountHLine  ->setValue(a->MarkThresholdData.MaxCountHLine);
            ui->spinBoxAlignmentLargeMaxCountVLine  ->setValue(a->MarkThresholdData.MaxCountVLine);
            ui->checkBoxAlignmentLargeJudgeWithBrDif->setChecked(a->MarkThresholdData.JudgeWithBrDif);
        }
    }
}

void ConfirmPropAlignmentForm::on_radioButtonAlignmentLargePriorityLGlobal_clicked()
{

}

void ConfirmPropAlignmentForm::on_radioButtonAlignmentLargePriorityHigh_clicked()
{

}

void ConfirmPropAlignmentForm::on_radioButtonAlignmentLargePriorityMiddle_clicked()
{

}

void ConfirmPropAlignmentForm::on_radioButtonAlignmentLargePriorityLow_clicked()
{

}

void ConfirmPropAlignmentForm::on_spinBoxAlignmentLargeSearchDot_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        int     d=ui->spinBoxAlignmentLargeSearchDot->value();
        double  mm=m->TransformPixelToUnit(d);
        ui->doubleSpinBoxAlignmentLargeSearchDotUnit->setValue(mm);
    }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_doubleSpinBoxAlignmentLargeSearchDotUnit_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        double  mm=ui->doubleSpinBoxAlignmentLargeSearchDotUnit->value();
        int     d=m->TransformUnitToPixel(mm);
        ui->spinBoxAlignmentLargeSearchDot->setValue(d);
      }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_spinBoxAlignmentLargeSearchDotY_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        int     d=ui->spinBoxAlignmentLargeSearchDotY->value();
        double  mm=m->TransformPixelToUnit(d);
        ui->doubleSpinBoxAlignmentLargeSearchDotUnitY->setValue(mm);
    }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_doubleSpinBoxAlignmentLargeSearchDotUnitY_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        double  mm=ui->doubleSpinBoxAlignmentLargeSearchDotUnitY->value();
        int     d=m->TransformUnitToPixel(mm);
        ui->spinBoxAlignmentLargeSearchDotY->setValue(d);
      }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_spinBoxAlignmentLargeSearchDot2_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        int     d=ui->spinBoxAlignmentLargeSearchDot2->value();
        double  mm=m->TransformPixelToUnit(d);
        ui->doubleSpinBoxAlignmentLargeSearchDot2Unit->setValue(mm);
    }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_doubleSpinBoxAlignmentLargeSearchDot2Unit_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        double  mm=ui->doubleSpinBoxAlignmentLargeSearchDot2Unit->value();
        int     d=m->TransformUnitToPixel(mm);
        ui->spinBoxAlignmentLargeSearchDot2->setValue(d);
      }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_spinBoxAlignmentLargeSearchDot2Y_valueChanged(int arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        int     d=ui->spinBoxAlignmentLargeSearchDot2Y->value();
        double  mm=m->TransformPixelToUnit(d);
        ui->doubleSpinBoxAlignmentLargeSearchDot2UnitY->setValue(mm);
    }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_doubleSpinBoxAlignmentLargeSearchDot2UnitY_valueChanged(double arg1)
{
    if(OnChanging==true)
        return;
    OnChanging=true;

    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
        double  mm=ui->doubleSpinBoxAlignmentLargeSearchDot2UnitY->value();
        int     d=m->TransformUnitToPixel(mm);
        ui->spinBoxAlignmentLargeSearchDot2Y->setValue(d);
      }
    OnChanging=false;
}

void ConfirmPropAlignmentForm::on_spinBoxAlignmentLargeMaxCountHLine_valueChanged(int arg1)
{

}

void ConfirmPropAlignmentForm::on_spinBoxAlignmentLargeMaxCountVLine_valueChanged(int arg1)
{

}

void ConfirmPropAlignmentForm::on_checkBoxAlignmentLargeJudgeWithBrDif_clicked()
{

}

void ConfirmPropAlignmentForm::on_tableWidgetAlignmentLargeMark_doubleClicked(const QModelIndex &index)
{
     ui->stackedWidgetAlignmentLarge->setCurrentIndex(1);
     ui->toolButtonAlignmentLargeMark->setChecked(true);
}

void	ConfirmPropAlignmentForm::ShowConfirmItem(ConfirmItemList *Item)
{
    IntegrationReqAlignmentItem RCmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
    IntegrationAckAlignmentItem ACmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
    RCmd.Phase=Item->Phase;
    RCmd.Layer=Item->Layer;
    RCmd.ItemID=Item->ItemID;
    if(RCmd.Send(GetSlaveNo(),Item->Page,ACmd)==true){
        int AreaRow=0;
        for(AlignmentAreaList *A=AreaListInPage[Item->Page].GetFirst();A!=NULL;A=A->GetNext(),AreaRow++){
            if(A->AreaID==ACmd.AreaID){
                SelectedItems.RemoveAll();
	            SelectedItems.Add(Item->Phase ,Item->Page ,Item->Layer,Item->ItemID);
                ui->listWidgetAlignmentLargeArea->setUpdatesEnabled(false);
                ui->listWidgetAlignmentLargeArea->setCurrentRow(AreaRow);
                ui->listWidgetAlignmentLargeArea->setUpdatesEnabled(true);
                ShowMarkList(AreaRow);
                SetSelectItems();
                int row=0;
                for(AlignmentMarkList *a=MarkListInArea->GetFirst();a!=NULL;a=a->GetNext(),row++){
                    if(a->MarkThresholdData.ItemID==Item->ItemID){
                        ::SetCurrentRow(ui->tableWidgetAlignmentLargeMark,row);
                        return;
                    }
                }
                return;
            }
        }
    }
}

void ConfirmPropAlignmentForm::on_listWidgetAlignmentLargeArea_clicked(const QModelIndex &index)
{
    on_listWidgetAlignmentLargeArea_itemSelectionChanged();
}


void ConfirmPropAlignmentForm::on_tableWidgetAlignmentLargeMark_clicked(const QModelIndex &index)
{
    on_tableWidgetAlignmentLargeMark_itemSelectionChanged();
}

