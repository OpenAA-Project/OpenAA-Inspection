/*
 * Copyright (C) 2023
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

#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "FilterInPhaseForm.h"
#include "ui_FilterInPhaseForm.h"
#include "XDataInLayer.h"
#include "XFilterManager.h"
#include "XFilterInstance.h"

FilterInPhaseForm::FilterInPhaseForm(LayersBase *base ,int phaseNo,int pageNo,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::FilterInPhaseForm)
    
{
    ui->setupUi(this);

    PhaseNo	=phaseNo;
    PageNo	=pageNo;
    ShowFilterBank();
    ShowFilterInstance();
}

FilterInPhaseForm::~FilterInPhaseForm()
{
    delete ui;
}

void	FilterInPhaseForm::ShowFilterBank(void)
{
    ui->listWidgetFilterbank->clear();
    for(FilterDLLList *d=GetLayersBase()->GetFilterBank()->GetFirst();d!=NULL;d=d->GetNext()){
        ui->listWidgetFilterbank->addItem(d->GetFilterName());
    }
}

void	FilterInPhaseForm::ShowFilterInstance(void)
{
    ui->listWidgetFilterInstance->clear();
    PageDataInOnePhase	*P=GetLayersBase()->GetPageDataPhase(PhaseNo);
    FilterInstanceContainer	*F=P->GetFilterContainer(PageNo);
    for(FilterInstanceList *L=F->GetFirst();L!=NULL;L=L->GetNext()){
        ui->listWidgetFilterInstance->addItem(L->GetFilterName());
    }
}
void FilterInPhaseForm::on_listWidgetFilterInstance_doubleClicked(const QModelIndex &index)
{
    int	R=ui->listWidgetFilterInstance->currentRow();
    PageDataInOnePhase	*P=GetLayersBase()->GetPageDataPhase(PhaseNo);
    FilterInstanceContainer	*F=P->GetFilterContainer(PageNo);
    FilterInstanceList *L=F->GetItem(R);
    L->ShowSetting(this);
}

void FilterInPhaseForm::on_pushButtonOK_clicked()
{
    close();
}

void FilterInPhaseForm::on_pushButtonGet_clicked()
{
    int	R=ui->listWidgetFilterbank->currentRow();
    FilterDLLList *d=GetLayersBase()->GetFilterBank()->GetItem(R);
    if(d!=NULL){
        //PageDataInOnePhase* P = GetLayersBase()->GetPageDataPhase(PhaseNo);
        //FilterInstanceContainer* F = P->GetFilterContainer(PageNo);
        //FilterInstanceList *L;
        //for(L=F->GetFirst();L!=NULL;L=L->GetNext()){
        //	if(L->GetFilterName()==d->GetFilterName()){
        //		break;
        //	}
        //}
        //if(L==NULL){
            PageDataInOnePhase	*P=GetLayersBase()->GetPageDataPhase(PhaseNo);
            FilterInstanceContainer	*F=P->GetFilterContainer(PageNo);
            F->AppendFilter(d->GetFilterName());
            ShowFilterInstance();
        //}
    }
}

void FilterInPhaseForm::on_pushButtonReturn_clicked()
{
    int	R=ui->listWidgetFilterInstance->currentRow();
    PageDataInOnePhase	*P=GetLayersBase()->GetPageDataPhase(PhaseNo);
    FilterInstanceContainer	*F=P->GetFilterContainer(PageNo);
    FilterInstanceList *L=F->GetItem(R);
    F->RemoveList(L);
    delete	L;
    ShowFilterInstance();
}