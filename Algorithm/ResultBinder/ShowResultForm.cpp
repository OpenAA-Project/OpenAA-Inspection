/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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