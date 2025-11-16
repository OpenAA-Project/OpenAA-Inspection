#include "XResultBinderResource.h"
#include "ShowResultForm.h"
#include "ui_ShowResultForm.h"
#include "XResultBinder.h"
#include "XResult.h"

ShowResultForm::ShowResultForm(LayersBase *Base ,QWidget *parent) :
    QWidget(parent),ServiceForLayers(Base),
    ui(new Ui::ShowResultForm)
{
    ui->setupUi(this);
	IData=NULL;

	InstallOperationLog(this);
}

ShowResultForm::~ShowResultForm()
{
    delete ui;
	if(IData!=NULL)
		delete	IData;
	IData=NULL;
}

void ShowResultForm::on_pushButtonOK_clicked()
{
	close();
}

void	ShowResultForm::Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data)
{
	if(IData!=NULL)
		delete	IData;
	IData=new AlgorithmItemIndependentPack(InstBase->GetLayersBase());
	*IData=Data;

	AlgorithmItemIndependent	*D=IData->Items.GetFirst();

	AlgorithmItemRoot	*DA=D->Data;
	if(DA!=NULL){
		ResultBinderItem	*BData=dynamic_cast<ResultBinderItem *>(DA);
		if(BData!=NULL){
			ItemID	=BData->GetID();
			ItemName=BData->GetItemName();

			ui->lineEditItemName	->setText(ItemName);

			RuleOfBinderBase	*p=BData->Rule.GetConclusionRule();
			if(p!=NULL){
				ui->lineEditRuleName	->setText(p->Name);
				ui->lineEditRuleRemark	->setText(p->Remark);
			}
			else{
				ui->lineEditRuleName	->setText(/**/"");
				ui->lineEditRuleRemark	->setText(/**/"");
			}
		}
	}
}
