#include "PropertyResultBinderFormResource.h"
#include "RuleAlgorithmItemDialog.h"
#include "ui_RuleAlgorithmItemDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include"XPropertyResultBinderPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

RuleAlgorithmItemDialog::RuleAlgorithmItemDialog(LayersBase *Base ,bool CreateMode ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::RuleAlgorithmItemDialog)
{
    ui->setupUi(this);
	ui->pushButtonDelete->setVisible(!CreateMode);

	ui->comboBoxLibTypeSelect->clear();
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
		if(ABase!=NULL){
			ui->comboBoxLibTypeSelect->addItem(ABase->GetNameByCurrentLanguage()
												,(int)L->GetLibType());
		}
	}
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	ui->spinBoxPage	->setMaximum(GetPageNumb());
	ui->spinBoxLayer->setMaximum(LayerNumb);
	InstallOperationLog(this);
}

RuleAlgorithmItemDialog::~RuleAlgorithmItemDialog()
{
    delete ui;
}

void	RuleAlgorithmItemDialog::Initial(ChildOfRuleAlgorithmItem *rule)
{
	int	Row=0;
	for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase((int)L->GetLibType());
		if(Ab!=NULL){
			QString	DLLRoot;
			QString DLLName;
			Ab->GetAlgorithmRootName(DLLRoot ,DLLName);
			if(DLLRoot==rule->AlgoRoot && DLLName==rule->AlgoName){
				ui->comboBoxLibTypeSelect->setCurrentIndex(Row);
				break;
			}
			Row++;
		}
	}
	ui->spinBoxPage	->setValue(rule->Page);
	ui->spinBoxLayer->setValue(rule->Layer);

	on_pushButtonFindItem_clicked();
	Row=0;
	for(ItemIDNameList *a=ItemIDNameData.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->ItemID==rule->ItemID && a->ItemName==rule->ItemName){
			ui->tableWidgetItems->setCurrentCell(Row,0);
			ui->tableWidgetItems->setCurrentCell(Row,1);
			break;
		}
	}

	ui->lineEditName	->setText(rule->Name);
	ui->lineEditRemark	->setText(rule->Remark);
	ui->checkBoxConclusion	->setChecked(rule->Conclusion);
}

void RuleAlgorithmItemDialog::on_pushButtonFindItem_clicked()
{
	int	LibRow=ui->comboBoxLibTypeSelect->currentIndex();
	QVariant V=ui->comboBoxLibTypeSelect->itemData ( LibRow);
	bool	ok;
	int	LibType=V.toInt(&ok);
	if(ok==false)
		return;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(LibType);
	if(Ab!=NULL){
		Ab->GetAlgorithmRootName(SelectedDLLRoot ,SelectedDLLName);
	}

	SelectedPage	=ui->spinBoxPage	->value();
	SelectedLayer	=ui->spinBoxLayer	->value();
	GUICmdReqItemList	DReq (GetLayersBase(),sRoot,sName,SelectedPage);
	GUICmdAckItemList	DAck(GetLayersBase(),sRoot,sName,SelectedPage);
	DReq.Layer	=SelectedLayer;
	DReq.LibType=LibType;
	if(DReq.Send(SelectedPage,0,DAck)==false){
		return;
	}
	ItemIDNameData	=DAck.Data;
	ui->tableWidgetItems->setRowCount(ItemIDNameData.GetCount());
	int	Row=0;
	for(ItemIDNameList *a=ItemIDNameData.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetItems,0,Row ,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidgetItems,1,Row ,a->ItemName);
	}
}

void RuleAlgorithmItemDialog::on_pushButtonOK_clicked()
{
	int	R=ui->tableWidgetItems->currentRow();
	if(R<0)
		return;
	ItemIDNameList *a=ItemIDNameData[R];

	SelectedItemID	=a->ItemID;
	SelectedItemName=a->ItemName;
	RuleName	=ui->lineEditName	->text();
	RuleRemark	=ui->lineEditRemark	->text();
	Conclusion	=ui->checkBoxConclusion	->isChecked();
	done(true);
}

void RuleAlgorithmItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void RuleAlgorithmItemDialog::on_pushButtonDelete_clicked()
{
    done(2);
}
