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

#include "CommonGUIDLLResource.h"
#include "SelectOnePage.h"
#include "ui_SelectOnePage.h"

SelectOnePage::SelectOnePage(LayersBase *pbase ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::SelectOnePage)
{
    ui->setupUi(this);

	for(int page=0;page<GetPageNumb();page++){
		ui->listWidgetPage->addItem(QString(/**/"Page ")+QString::number(page));
		PageList.Add(page);
	}
	InstallOperationLog(this);
}

SelectOnePage::SelectOnePage(LayersBase *pbase ,const IntList &pageList,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::SelectOnePage)
{
    ui->setupUi(this);

	for(IntClass *c=pageList.GetFirst();c!=NULL;c=c->GetNext()){
		int	page=c->GetValue();
		ui->listWidgetPage->addItem(QString(/**/"Page ")+QString::number(page));
		PageList.Add(page);
	}
	InstallOperationLog(this);
}
SelectOnePage::~SelectOnePage()
{
    delete ui;
}

void SelectOnePage::on_listWidgetPage_doubleClicked(const QModelIndex &index)
{
	int	n=ui->listWidgetPage->currentRow();
	SelectedPage=PageList[n];
	done(true);
}

void SelectOnePage::on_pushButtonOK_clicked()
{
	int	n=ui->listWidgetPage->currentRow();
	SelectedPage=PageList[n];
	done(true);
}