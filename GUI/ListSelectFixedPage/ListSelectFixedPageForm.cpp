/*
 * Copyright (C) 2025
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

#include "ListSelectFixedPageForm.h"
#include "ListSelectFixedPage.h"
#include "ui_ListSelectFixedPageForm.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"

ListSelectFixedPageForm::ListSelectFixedPageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ListSelectFixedPageForm)
{
    ui->setupUi(this);

    connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ListSelectFixedPageForm::~ListSelectFixedPageForm()
{
    delete ui;
}

void	ListSelectFixedPageForm::ResizeAction()
{
    ui->listWidgetPage->resize(width(),height());
}
void	ListSelectFixedPageForm::BuildForShow(void)
{
    ShowPageList();
}

void ListSelectFixedPageForm::on_listWidgetPage_itemSelectionChanged()
{
    int CurrentRow=ui->listWidgetPage->currentRow();
    if(CurrentRow<0)
        return;
    int FixedPage=CurrentRow;
    for(int i=0;i<DisplayImageInst.count();i++){
        GUIFormBase *f=GetLayersBase()->FindByName(DisplayImageInst[i]);
        if(f!=NULL){
            DisplayImage    *d=dynamic_cast<DisplayImage *>(f);
            if(d!=NULL){
                d->ShowOnePage=FixedPage;
                d->Repaint();
            }
        }
    }
    BroadcastSetTargetPage(FixedPage);
}

void	ListSelectFixedPageForm::TransmitDirectly(GUIDirectMessage *packet)
{
    CmdGetCurrentPage   *CmdGetCurrentPageVar=dynamic_cast<CmdGetCurrentPage *>(packet);
    if(CmdGetCurrentPageVar!=NULL){
        CmdGetCurrentPageVar->CurrentPage=ui->listWidgetPage->currentRow();
        return;
    }
    CmdSetCurrentPage   *CmdSetCurrentPageVar=dynamic_cast<CmdSetCurrentPage *>(packet);
    if(CmdSetCurrentPageVar!=NULL){
        ui->listWidgetPage->setCurrentRow(CmdSetCurrentPageVar->CurrentPage);
        on_listWidgetPage_itemSelectionChanged();
        return;
    }
}

void ListSelectFixedPageForm::on_listWidgetPage_clicked(const QModelIndex &index)
{
    on_listWidgetPage_itemSelectionChanged();
}

bool	ListSelectFixedPageForm::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
    ShowPageList();
    return true;
}
bool	ListSelectFixedPageForm::InsertPage(int IndexPage)	//Create page before Indexed page
{
    ShowPageList();
	return true;
}
bool	ListSelectFixedPageForm::RemovePage(int IndexPage)
{
    ShowPageList();
    return true;
}
void    ListSelectFixedPageForm::ShowPageList(void)
{
    int CurrentRow=ui->listWidgetPage->currentRow();
    ui->listWidgetPage->clear();
    for(int page=0;page<GetPageNumb();page++){
        ui->listWidgetPage->addItem(QString("Page ")+QString::number(page));
    }
    if(CurrentRow>=0){
        ui->listWidgetPage->setCurrentRow(CurrentRow);
    }
}