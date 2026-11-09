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

#include "LoadImageFilesForm.h"
#include "ui_LoadImageFilesForm.h"
#include "CameraFromLoadedImages.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QFileInfo>

LoadImageFilesForm::LoadImageFilesForm(CameraFromLoadedImages *p,QWidget *parent) :
    QWidget(parent)
    ,Parent(p)
    ,ui(new Ui::LoadImageFilesForm)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 47);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 47);
}

LoadImageFilesForm::~LoadImageFilesForm()
{
    delete ui;
}

void LoadImageFilesForm::on_pushButtonSeletFiles_clicked()
{
    QStringList List=QFileDialog::getOpenFileNames(NULL
                                                    ,/**/"Image files (*.pix)"
                                                    ,QString()
                                                    ,"PIX(*.pix)");
    ui->lineEdit->setText(List.join(';'));
    FileLists   =List;

    ui->tableWidget->clear();
	ui->tableWidget->setRowCount(FileLists.size());
    for(int row=0;row<FileLists.size();row++)
    {
		QFileInfo FInfo(FileLists[row]);
        ::SetDataToTable(ui->tableWidget, 0, row, FInfo.path());
        ::SetDataToTable(ui->tableWidget, 1, row, FInfo.fileName());
	}
}


void LoadImageFilesForm::on_pushButtonLoadImages_clicked()
{
    
    QStringList List=ui->lineEdit->text().split(';');
    Parent->LoadImages(List);    
}


void LoadImageFilesForm::on_pushButtonTransferImages_clicked()
{
    Parent->RPoint=0;
}


void LoadImageFilesForm::on_pushButtonResetStrategicNumber_clicked()
{
    Parent->ResetStrategicNumber();
}


void LoadImageFilesForm::on_pushButtonResetScanPhaseNumber_clicked()
{
    Parent->ResetScanPhaseNumber();
}


void LoadImageFilesForm::on_pushButtonLoadResetTransfer_clicked()
{
	int Row = ui->tableWidget->currentRow();
    if (Row < 0 || Row >= FileLists.size())
		return;
    QString s=FileLists[Row];

    QStringList List;
	List.append(s);
    Parent->LoadImages(List);
    Parent->ResetStrategicNumber();
    Parent->ResetScanPhaseNumber();
    Parent->RPoint=0;
    if(Row+1<FileLists.size()){
        ::SetCurrentRow(ui->tableWidget, Row+1);
    }
}
