/*
 * Copyright (C) 2017
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

#include "sendmessagerResource.h"
#include "SendMessagerForm.h"
#include "XDataInLayer.h"

SendMessagerForm::SendMessagerForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),MClient(this)
{
	ui.setupUi(this);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		QVariant	v(GlobalPage);
		ui.comboBoxPage->addItem(QString(/**/"Page ")+QString::number(GlobalPage),v);
	}
	IPAddress=/**/"localhost";
	GetParamGUI()->SetParam(&IPAddress, /**/"SendMessager",/**/"IPAddress"		,LangSolver.GetString(SendMessagerForm_LS,LID_0)/*"Messager\'s IP Address"*/		);
}

SendMessagerForm::~SendMessagerForm()
{
}

void	SendMessagerForm::Prepare(void)
{
	MClient.Start();
	MClient.Initial(IPAddress);
}
void SendMessagerForm::on_pushButtonSend_clicked()
{
	int	r=ui.comboBoxPage->currentIndex();
	if(r>=0){
		int	GlobalPage=ui.comboBoxPage->itemData(r).toInt();
		QString	Message=ui.lineEditMessage->text();
		MClient.Send(1,GlobalPage,Message);
	}
}