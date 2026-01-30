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

#include "AutoSaveImageSelectLotResource.h"
#include "FormAutoSaveImageSelectLot.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "XLotInformation.h"

FormAutoSaveImageSelectLot::FormAutoSaveImageSelectLot(LayersBase *Base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
	,RCmd(Base)
{
	ui.setupUi(this);
	ui.tableWidget->setColumnWidth(0,200);
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"AutoSaveImageViewList",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&RCmd);
		ui.tableWidget->setRowCount(RCmd.LotList.count());
		for(int i=0;i<RCmd.LotList.count();i++){
			SetDataToTable(ui.tableWidget,0,i,RCmd.LotList[i]);
		}
	}
	InstallOperationLog(this);
}

FormAutoSaveImageSelectLot::~FormAutoSaveImageSelectLot()
{

}


void FormAutoSaveImageSelectLot::on_pushButtonSelect_clicked()
{
	int	row=ui.tableWidget->currentRow();
	if(row<0){
		return;
	}
	CmdSetLotString	SCmd(GetLayersBase());
	SCmd.LotString=RCmd.LotList[row];
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"AutoSaveImageViewList",/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&SCmd);
	}
	GetLayersBase()->GetLotBase()->SetLotName(SCmd.LotString);
	done(true);
}

void FormAutoSaveImageSelectLot::on_pushButtonCancel_clicked()
{
	done(false);
}

void FormAutoSaveImageSelectLot::on_tableWidget_doubleClicked(QModelIndex)
{
	on_pushButtonSelect_clicked();
}