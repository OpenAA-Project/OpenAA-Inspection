#include "ButtonShowConfirmResource.h"
#include "ConfirmPropBCRInspectionForm.h"
#include "ui_ConfirmPropBCRInspectionForm.h"
#include "ConfirmForm.h"
#include "XConfirmPacket.h"
#include "XIntegrationBase.h"
#include "XBCRInspectionLibrary.h"
#include "XBCRInspection.h"
#include "XGeneralFunc.h"

ConfirmPropBCRInspectionForm::ConfirmPropBCRInspectionForm(ConfirmForm *p ,QWidget *parent) :
    ConfirmAlgorithm(p)
    ,ServiceForLayers(p->GetLayersBase())
    ,ui(new Ui::ConfirmPropBCRInspectionForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
    ::SetColumnWidthInTable(ui->tableWidgetBCRInspectionItem ,0, 40);
    ::SetColumnWidthInTable(ui->tableWidgetBCRInspectionItem ,1, 20);
    ::SetColumnWidthInTable(ui->tableWidgetBCRInspectionItem ,2, 40);

	::SetColumnWidthInTable(ui->tableWidgetBCRInspectionGradeList ,0, 50);
	::SetColumnWidthInTable(ui->tableWidgetBCRInspectionGradeList ,1, 50);
}

ConfirmPropBCRInspectionForm::~ConfirmPropBCRInspectionForm()
{
    delete ui;
}

QString	ConfirmPropBCRInspectionForm::GetButtonName(void)
{
    return LangSolver.GetString(ConfirmPropBCRInspectionForm_LS,LID_6)/*"繝舌�繧ｳ繝ｼ繝�*/;
}
int		ConfirmPropBCRInspectionForm::GetLibType(void)
{   
    return DefLibTypeBCRInspection;
}
void	ConfirmPropBCRInspectionForm::SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)
{
    s.Add(DefLibTypeBCRInspection,false,true,true);
}

void	ConfirmPropBCRInspectionForm::InitialShow(void)
{
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		BCodeItemListContainerData.RemoveAll();
        for(int page=0;page<m->GetPageNumb();page++){
            IntegrationReqBCodeItemListInfo RCmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
            RCmd.Phase  =m->GetCurrentPhase();
            IntegrationAckBCodeItemListInfo ACmd(GetLayersBase(),sRoot,sName,GetSlaveNo());
            if(RCmd.Send(GetSlaveNo(),m->GetLocalPageFromGlobal(page),ACmd)==true){
                BCodeItemListContainerData+=ACmd.Container;
            }
        }
        ui->tableWidgetBCRInspectionItem->setRowCount(BCodeItemListContainerData.GetCount());
        int Row=0;
        for(BCodeItemList *a=BCodeItemListContainerData.GetFirst();a!=NULL;a=a->GetNext(),Row++){
            ::SetDataToTable(ui->tableWidgetBCRInspectionItem,0, Row,QString::number(a->x1)+QString(/**/",")+QString::number(a->y1)
                                                                    +QString(/**/"-")
                                                                    +QString::number(a->x2)+QString(/**/",")+QString::number(a->y2));
            ::SetDataToTable(ui->tableWidgetBCRInspectionItem,1, Row,QString::number(a->ItemIndex.Data.ItemID));
            ::SetDataToTable(ui->tableWidgetBCRInspectionItem,2, Row,a->Result);
        }
    }
}

void	ConfirmPropBCRInspectionForm::AlgoMouseLDownWithShift(int ux ,int uy)
{
	GetItemsByPoint(ux, uy);
	ShowItemData();
	SetSelectItems();
	ShowResult();
}
void	ConfirmPropBCRInspectionForm::CanvasSlotDrawEnd(FlexArea &Area)
{
	ConfirmAlgorithm::CanvasSlotDrawEnd(Area);

	int	SlaveNo=GetSlaveNo();
    EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
    if(m!=NULL){
		GetItemsByArea(-1,Area);
		ShowItemData();
		SetSelectItems();
		ShowResult();
	}
}
void	ConfirmPropBCRInspectionForm::SetProperty(void)
{
	ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
	if(t!=NULL){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateBCRInspectionThreshold	Cmd(GetLayersBase());
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
				SCmd.ItemIndex=*t;
				SCmd.ThresholdData=Buff.buffer();
				SCmd.Send(NULL,SlaveNo ,t->Data.Page);
			}
		}
	}
}
    
void    ConfirmPropBCRInspectionForm::ShowThreshold(BCRInspectionThreshold *s)
{
    OnChanging=true;
    ui->comboBoxBCRInspectionCheckType          ->setCurrentIndex(s->CheckType);
    ui->doubleSpinBoxBCRInspectionQuilityGrade  ->setValue(s->QuilityGrade);
	ShowGradeList(s->GradeList);
    OnChanging=false;
}
    
void    ConfirmPropBCRInspectionForm::ShowItemData(void)
{
	ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
	if(t!=NULL){
		int	SlaveNo=GetSlaveNo();
		IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.LibType=GetLibType();
		RCmd.ItemIndex=*t;
		if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
			CmdCreateBCRInspectionThreshold	Cmd(GetLayersBase());
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
			if(ABase!=NULL){
				ABase->TransmitDirectly(&Cmd);
				QBuffer	Buff(&ACmd.ThresholdData);
				Buff.open(QIODevice::ReadWrite);
				Cmd.Threshold->Load(&Buff);
				ShowThreshold(Cmd.Threshold);
			}
		}
	}
}
    
void    ConfirmPropBCRInspectionForm::ShowResult(void)
{
   EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
    if(m!=NULL){
		ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
		if(t!=NULL){
			int	SlaveNo=GetSlaveNo();
			IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.LibType=GetLibType();
			RCmd.ItemIndex=*t;
			if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
				CmdCreateBCRInspectionThreshold	Cmd(GetLayersBase());
				AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
				if(ABase!=NULL){
					ABase->TransmitDirectly(&Cmd);
					QBuffer	Buff(&ACmd.ThresholdData);
					Buff.open(QIODevice::ReadWrite);
					Cmd.Threshold->Load(&Buff);
					GetThresholdFromWindow(Cmd.Threshold);

					Buff.seek(0);
					Cmd.Threshold->Save(&Buff);

					IntegrationReqBCRInspectionTryResult	RTryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					IntegrationAckBCRInspectionTryResult	ATryCmd(GetLayersBase(),sRoot,sName,SlaveNo);
					RTryCmd.ThresholdData=Buff.buffer();
					RTryCmd.ItemIndex=*t;
					if(RTryCmd.Send(SlaveNo ,t->Data.Page,ATryCmd)==true){
						int Row=0;
						for(BCodeItemList *a=BCodeItemListContainerData.GetFirst();a!=NULL;a=a->GetNext(),Row++){
							if(a->ItemIndex==*t){
							    ::SetDataToTable(ui->tableWidgetBCRInspectionItem,2, Row,ATryCmd.Result);
							}
						}
					}
				}
			}
		}
	}
}

void    ConfirmPropBCRInspectionForm::ShowGradeList(BCRGradeListContainer &List)
{
	ui->tableWidgetBCRInspectionGradeList->setRowCount(List.GetCount());
	int	Row=0;
	for(BCRGradeList *a=List.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetBCRInspectionGradeList, 0, Row, a->Grade, Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetBCRInspectionGradeList, 1, Row, QString::number(a->Quality,'f',3), Qt::ItemIsEditable);
	}
}
void    ConfirmPropBCRInspectionForm::LoadGradeListFromWindow(BCRGradeListContainer &List)
{
	List.RemoveAll();
	int	N=ui->tableWidgetBCRInspectionGradeList->rowCount();
	for(int Row=0;Row<N;Row++){
		BCRGradeList *a=new BCRGradeList();
		a->Grade	=GetDataToTable(ui->tableWidgetBCRInspectionGradeList, 0, Row);
		a->Quality	=GetDataToTable(ui->tableWidgetBCRInspectionGradeList, 1, Row).toDouble();;
		List.AppendList(a);
	}
}
void    ConfirmPropBCRInspectionForm::GetThresholdFromWindow(BCRInspectionThreshold *s)
{
    s->CheckType    =ui->comboBoxBCRInspectionCheckType          ->currentIndex();
    s->QuilityGrade =ui->doubleSpinBoxBCRInspectionQuilityGrade  ->value();
	LoadGradeListFromWindow(s->GradeList);
}
void	ConfirmPropBCRInspectionForm::ForceDraw(void)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropBCRInspectionForm::on_tableWidgetBCRInspectionItem_itemSelectionChanged()
{
	if(OnChanging==true)
		return;
	OnChanging=true;

	int	row=ui->tableWidgetBCRInspectionItem->currentRow();
	if(row>=0){
		BCodeItemList *a=BCodeItemListContainerData.GetItem(row);
		SelectedItems.RemoveAll();
		SelectedItems.Add(a->ItemIndex.Data.Phase 
						, a->ItemIndex.Data.Page 
						, a->ItemIndex.Data.Layer
						, a->ItemIndex.Data.ItemID);

		ZoomArea(a->x1,a->y1,a->x2,a->y2);

		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(GetSlaveNo());
		if(m!=NULL){
			ListPhasePageLayerItem	*t=SelectedItems.GetFirst();
			if(t!=NULL){
				int	SlaveNo=GetSlaveNo();
				IntegrationReqItemThresholdData	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckItemThresholdData	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.LibType=GetLibType();
				RCmd.ItemIndex=*t;
				if(RCmd.Send(SlaveNo ,t->Data.Page,ACmd)==true){
					CmdCreateBCRInspectionThreshold	Cmd(GetLayersBase());
					AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(GetLibType());
					if(ABase!=NULL){
						ABase->TransmitDirectly(&Cmd);
						QBuffer	Buff(&ACmd.ThresholdData);
						Buff.open(QIODevice::ReadWrite);
						Cmd.Threshold->Load(&Buff);

						ShowThreshold(Cmd.Threshold);
					}
				}
			}
		}
	}
	OnChanging=false;
}

void ConfirmPropBCRInspectionForm::on_comboBoxBCRInspectionCheckType_currentIndexChanged(int index)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropBCRInspectionForm::on_doubleSpinBoxBCRInspectionQuilityGrade_valueChanged(double arg1)
{
	if(OnChanging==true)
		return;
	OnChanging=true;
	ShowResult();
	OnChanging=false;
}

void ConfirmPropBCRInspectionForm::on_pushButtonBCRInspectionLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr,LangSolver.GetString(ConfirmPropBCRInspectionForm_LS,LID_7)/*"Load BCR Grade file"*/,QString()
											,/**/"Grade file(BCRGrade:dat);;Data file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){

			BCRGradeListContainer	List;
			if(List.Load(&File)==true){
				ShowGradeList(List);
			}
		}
	}
}

void ConfirmPropBCRInspectionForm::on_pushButtonBCRInspectionSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(nullptr,LangSolver.GetString(ConfirmPropBCRInspectionForm_LS,LID_8)/*"Save BCR Grade file"*/,QString()
											,/**/"Grade file(BCRGrade:dat);;Data file(*.dat);;All files(*.*)");
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){

			BCRGradeListContainer	List;
			LoadGradeListFromWindow(List);
			List.Save(&File);
		}
	}
}

void ConfirmPropBCRInspectionForm::on_pushButtonBCRInspectionAdd_clicked()
{
	int	N=ui->tableWidgetBCRInspectionGradeList->rowCount();
	ui->tableWidgetBCRInspectionGradeList->setRowCount(N+1);
}

void ConfirmPropBCRInspectionForm::on_pushButtonBCRInspectionSub_clicked()
{
	int	N=ui->tableWidgetBCRInspectionGradeList->rowCount();
	ui->tableWidgetBCRInspectionGradeList->setRowCount(N-1);
}
void	ConfirmPropBCRInspectionForm::ShowConfirmItem(ConfirmItemList *Item)
{
	int	row=0;
	for(BCodeItemList *a=BCodeItemListContainerData.GetFirst();a!=NULL;a=a->GetNext(),row++){
		if(a->ItemIndex.Data.Phase==Item->Phase
		&& a->ItemIndex.Data.Page==Item->Page
		&& a->ItemIndex.Data.Layer==Item->Layer
		&& a->ItemIndex.Data.ItemID==Item->ItemID){
			SelectedItems.RemoveAll();
			SelectedItems.Add(Item->Phase ,Item->Page ,Item->Layer,Item->ItemID);
			::SetCurrentRow(ui->tableWidgetBCRInspectionItem,row);
			OnChanging=true;
			ShowItemData();
			ShowResult();
			OnChanging=false;
			return;
		}
	}
	InitialShow();
	for(BCodeItemList *a=BCodeItemListContainerData.GetFirst();a!=NULL;a=a->GetNext(),row++){
		if(a->ItemIndex.Data.Phase==Item->Phase
		&& a->ItemIndex.Data.Page==Item->Page
		&& a->ItemIndex.Data.Layer==Item->Layer
		&& a->ItemIndex.Data.ItemID==Item->ItemID){
			SelectedItems.RemoveAll();
			SelectedItems.Add(Item->Phase ,Item->Page ,Item->Layer,Item->ItemID);
			::SetCurrentRow(ui->tableWidgetBCRInspectionItem,row);
			OnChanging=true;
			ShowItemData();
			ShowResult();
			OnChanging=false;
			return;
		}
	}

}

void ConfirmPropBCRInspectionForm::on_tableWidgetBCRInspectionItem_clicked(const QModelIndex &index)
{
    on_tableWidgetBCRInspectionItem_itemSelectionChanged();
}

