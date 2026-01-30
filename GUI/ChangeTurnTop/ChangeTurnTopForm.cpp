/*
 * Copyright (C) 2019
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

#include "ChangeTurnTopForm.h"
#include "ui_ChangeTurnTopForm.h"

ChangeTurnTopForm::ChangeTurnTopForm(LayersBase *Base ,QWidget *parent)
    :GUIFormBase(Base,parent),
    ui(new Ui::ChangeTurnTopForm)
{
    ui->setupUi(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ChangeTurnTopForm::~ChangeTurnTopForm()
{
    delete ui;
}

void	ChangeTurnTopForm::Prepare(void)
{
	ui->listWidget->clear();
	for(int page=0;page<GetPageNumb();page++){
		ui->listWidget->addItem(QString::number(page));
	}
}
void	ChangeTurnTopForm::BuildForShow(void)
{
	if(ui->listWidget->count()!=GetPageNumb()){
		ui->listWidget->clear();
		for(int page=0;page<GetPageNumb();page++){
			ui->listWidget->addItem(QString::number(page));
		}
	}
}
void ChangeTurnTopForm::on_listWidget_currentRowChanged(int currentRow)
{
	if(currentRow<0)
		return;
	DataInPage	*Dp=GetLayersBase()->GetPageData(currentRow);
	GetLayersBase()->SetTopInPage(Dp);

	for(int i=0;i<RelatedPanels.count();i++){
		QString	str=RelatedPanels.value(i);
		GUIFormBase		*r=GetFormByName(str);
		if(r==NULL)
			continue;
		r->Repaint();
	}
}
void	ChangeTurnTopForm::ResizeAction()
{
	ui->listWidget->resize(width(),height());
}