/*
 * Copyright (C) 2012
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

#include "IndicatorWindow.h"
#include "ui_IndicatorWindow.h"
#include "XCopyMultiple.h"
#include "CopyMultiple.h"
#include "XGeneralFunc.h"

IndicatorWindow::IndicatorWindow(QWidget *parent) :
    QWidget(NULL),
    ui(new Ui::IndicatorWindow)
{
    ui->setupUi(this);

	Parent=(CopyMultiple*)parent;
	DestCount=Parent->Data.GetDestCount();
	ui->tableWidget->setColumnCount(1+DestCount);
	ui->tableWidget->setColumnWidth(0,300);
	QStringList Header;
	Header << "File";
	for(int i=0;i<DestCount;i++){
		ui->tableWidget->setColumnWidth(1+i,45);
		QString Destnumber="Dest ";
		Destnumber+=Destnumber.number(1+i,10);
		Header << Destnumber;
	}
	ui->tableWidget->setHorizontalHeaderLabels(Header);
	ui->tableWidget->setRowCount(Parent->Data.SourceFiles.GetCount());
	int	Row=0;
	for(CopyMultipleData::FoundFileClass *L=Parent->Data.SourceFiles.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget,0,Row ,L->FoundFile);
	}

	TM.setInterval(200);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	TM.start();
}

IndicatorWindow::~IndicatorWindow()
{
    delete ui;
	Parent->Indicator=NULL;
}

void IndicatorWindow::closeEvent ( QCloseEvent * event )
{
	deleteLater();
}

void	IndicatorWindow::SlotTimeout ()
{
	int	Row=0;
	for(CopyMultipleData::FoundFileClass *L=Parent->Data.SourceFiles.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		for(int i=0;i<DestCount;i++){
			if(L->CopiedState[i]==CopyMultipleData::FoundFileClass::_NotYet){
				::SetDataToTable(ui->tableWidget,i+1,Row ,/**/"");
			}
			if(L->CopiedState[i]==CopyMultipleData::FoundFileClass::_Copied){
				::SetDataToTable(ui->tableWidget,i+1,Row ,/**/"OK");
			}
			if(L->CopiedState[i]==CopyMultipleData::FoundFileClass::_NotCopied){
				::SetDataToTable(ui->tableWidget,i+1,Row ,/**/"X");
			}
		}
	}
}