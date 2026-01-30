/*
 * Copyright (C) 2024
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

#include "SettingFilmPositionDialog.h"
#include "ui_SettingFilmPositionDialog.h"
#include "EasyPropertyDentMeasureForm.h"
#include "XGeneralFunc.h"

SettingFilmPositionDialog::SettingFilmPositionDialog(EasyPropertyDentMeasureForm *p
                                                    ,int FilmIndex,int FilmPointNo 
                                                    ,QWidget *parent) :
    QDialog(parent)
    ,Parent(p)
    ,ui(new Ui::SettingFilmPositionDialog)
{
    ui->setupUi(this);

    ui->tableWidget->setRowCount(Parent->BladeMeasureData.CountGenDatas);
	for(int grow=0;grow<Parent->BladeMeasureData.CountGenDatas;grow++){
		int	row=Parent->GUI2RowTable[grow];
		struct	MeasureHVInfo	&p=Parent->BladeMeasureData.GenDatas[row];

        ::SetDataToTable(ui->tableWidget,0, grow,QString::fromLocal8Bit(p.MeasureName));
       
		QWidget *b1=ui->tableWidget->cellWidget(grow,1);
		if(b1==NULL){
			DentMeasurePointButton	*b=new DentMeasurePointButton();
			b->EndNo=0;
			b->MeasureNo=grow;
			ui->tableWidget->setCellWidget(grow,1,b);
			connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotEndPointClicked(int,int)));
		}
		QWidget *b2=ui->tableWidget->cellWidget(grow,2);
		if(b2==NULL){
			DentMeasurePointButton	*b=new DentMeasurePointButton();
			b->EndNo=1;
			b->MeasureNo=grow;
			ui->tableWidget->setCellWidget(grow,2,b);
			connect(b,SIGNAL(SignalClicked(int,int)),this,SLOT(SlotEndPointClicked(int,int)));
		}
	}
	if(FilmPointNo==0 && FilmIndex>=0){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidget->cellWidget(FilmIndex,1));
		if(tb!=NULL){
			tb->setChecked(true);
		}
	}
	else
	if(FilmPointNo==1 && FilmIndex>=0){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidget->cellWidget(FilmIndex,2));
		if(tb!=NULL){
			tb->setChecked(true);
		}
	}
	::SetColumnWidthInTable(ui->tableWidget,0,60);
	::SetColumnWidthInTable(ui->tableWidget,1,16);
	::SetColumnWidthInTable(ui->tableWidget,2,16);
}

SettingFilmPositionDialog::~SettingFilmPositionDialog()
{
    delete ui;
}
void	SettingFilmPositionDialog::SlotEndPointClicked(int EndNo,int MeasureNo)
{
	int RCount=ui->tableWidget->rowCount();
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidget->cellWidget(i,1));
		if(tb!=NULL && (tb->EndNo!=EndNo || tb->MeasureNo!=MeasureNo)){
			tb->setChecked(false);
		}
	}
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidget->cellWidget(i,2));
		if(tb!=NULL && (tb->EndNo!=EndNo || tb->MeasureNo!=MeasureNo)){
			tb->setChecked(false);
		}
	}
}
void SettingFilmPositionDialog::on_PushButtonOK_clicked()
{
	int RCount=ui->tableWidget->rowCount();
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidget->cellWidget(i,1));
		if(tb!=NULL && tb->isChecked()==true){
			FilmIndex=i;
			FilmPointNo=0;
		}
	}
	for(int i=0;i<RCount;i++){
		DentMeasurePointButton	*tb=dynamic_cast<DentMeasurePointButton *>(ui->tableWidget->cellWidget(i,2));
		if(tb!=NULL && tb->isChecked()==true){
			FilmIndex=i;
			FilmPointNo=1;
		}
	}
	done(true);
}


void SettingFilmPositionDialog::on_PushButtonCancel_clicked()
{
	done(false);
}
