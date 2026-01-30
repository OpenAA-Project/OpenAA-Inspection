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

#include "Search9PosResource.h"
#include "Search9PosForm.h"
#include "ui_Search9PosForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"
#include <QString>
#include "swap.h"

Search9PosForm::Search9PosForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::Search9PosForm)
{
    ui->setupUi(this);
	ui->tableWidget9Pos->setColumnWidth (0, 40);
	ui->tableWidget9Pos->setColumnWidth (1, 40);
	ui->tableWidget9Pos->setColumnWidth (2, 40);
}

Search9PosForm::~Search9PosForm()
{
    delete ui;
}


bool	Search9PosForm::SaveContent(QIODevice *f)
{
	XYPosData.RemoveAll();
	int	N1=ui->tableWidget9Pos->rowCount();
	for(int i=0;i<N1;i++){
		QString	StrX=::GetDataToTable(ui->tableWidget9Pos ,0,i);
		QString	StrY=::GetDataToTable(ui->tableWidget9Pos ,1,i);
		bool	ok;
		int	X=StrX.toInt(&ok);
		int	Y=StrY.toInt(&ok);
		XYClass	*a=new XYClass(X,Y);
		XYPosData.AppendList(a);
	}

	int N2=XYPosData.GetCount();
	int	N=min(N1,N2);
	if(::Save(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		XYClass	*a=XYPosData.GetItem(i);
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}

bool	Search9PosForm::LoadContent(QIODevice *f)
{
	XYPosData.RemoveAll();
	int	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		XYClass	*a=new XYClass();
		if(a->Load(f)==false){
			return false;
		}
		XYPosData.AppendList(a);
	}
	ui->tableWidget9Pos->setRowCount(N);
	for(int i=0;i<N;i++){
		XYClass	*a=XYPosData.GetItem(i);
		::SetDataToTable(ui->tableWidget9Pos,0,i,QString::number(a->x));
		::SetDataToTable(ui->tableWidget9Pos,0,i,QString::number(a->y));
	}

	return true;
}