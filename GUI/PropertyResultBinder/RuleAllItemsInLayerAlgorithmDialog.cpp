#include "PropertyResultBinderFormResource.h"
#include "RuleAllItemsInLayerAlgorithmDialog.h"
#include "ui_RuleAllItemsInLayerAlgorithmDialog.h"
#include "XLibraryType.h"
#include "XDataInLayer.h"
#include"XPropertyResultBinderPacket.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

RuleAllItemsInLayerAlgorithmDialog::RuleAllItemsInLayerAlgorithmDialog(int Page,LayersBase *Base ,bool CreateMode ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::RuleAllItemsInLayerAlgorithmDialog)
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
	ui->spinBoxPage	->setMaximum(GetPageNumb());
	ui->spinBoxLayer->setMaximum(GetLayerNumb(Page));
	InstallOperationLog(this);
}

RuleAllItemsInLayerAlgorithmDialog::~RuleAllItemsInLayerAlgorithmDialog()
{
    delete ui;
}
void	RuleAllItemsInLayerAlgorithmDialog::Initial(ChildOfRuleAllItemsInLayerAlgorithm *rule)
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

	ui->lineEditName	->setText(rule->Name);
	ui->lineEditRemark	->setText(rule->Remark);
	ui->checkBoxConclusion	->setChecked(rule->Conclusion);
}

void RuleAllItemsInLayerAlgorithmDialog::on_pushButtonOK_clicked()
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

	RuleName	=ui->lineEditName	->text();
	RuleRemark	=ui->lineEditRemark	->text();
	Conclusion	=ui->checkBoxConclusion	->isChecked();
	done(true);
}

void RuleAllItemsInLayerAlgorithmDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void RuleAllItemsInLayerAlgorithmDialog::on_pushButtonDelete_clicked()
{
    done(2);
}
