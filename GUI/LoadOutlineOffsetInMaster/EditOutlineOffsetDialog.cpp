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

#include "EditOutlineOffsetDialogResource.h"
#include "EditOutlineOffsetDialog.h"
#include "ui_EditOutlineOffsetDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

EditOutlineOffsetDialog::EditOutlineOffsetDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditOutlineOffsetDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setRowCount(GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int32	iOffsetX=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
		int32	iOffsetY=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
		::SetDataToTable(ui->tableWidget ,0,page ,QString::number(iOffsetX) ,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidget ,1,page ,QString::number(iOffsetY) ,Qt::ItemIsEditable);
	}
	InstallOperationLog(this);
}

EditOutlineOffsetDialog::~EditOutlineOffsetDialog()
{
    delete ui;
}

void EditOutlineOffsetDialog::on_pushButtonOK_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int32	iOffsetX=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x;
		int32	iOffsetY=GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y;
		::SetDataToTable(ui->tableWidget ,0,page ,QString::number(iOffsetX) ,Qt::ItemIsEditable);

		bool	ok;
		QString	Sx=GetDataToTable(ui->tableWidget ,0,page);
		int	X=Sx.toInt(&ok);
		if(ok==true){
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->x=X;
		}
		QString Sy=GetDataToTable(ui->tableWidget ,1,page);
		int	Y=Sy.toInt(&ok);
		if(ok==true){
			GetLayersBase()->GetPageData(page)->GetOutlineOffset()->y=Y;
		}
	}
	done(true);
}

void EditOutlineOffsetDialog::on_pushButtonCancel_clicked()
{
	done(false);
}