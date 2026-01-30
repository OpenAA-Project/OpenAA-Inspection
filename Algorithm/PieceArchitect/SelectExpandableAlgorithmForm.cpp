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



#include "SelectExpandableAlgorithmForm.h"

SelectExpandableAlgorithmGrid::SelectExpandableAlgorithmGrid(LayersBase *Base,QWidget *parent)
:WMultiGrid(parent),ServiceForLayers(Base)
{
}
void	SelectExpandableAlgorithmGrid::ShowGrid(void)
{
	SetColumnCount(3);
	SetRowCount(GetLayersBase()->GetLogicDLLBase()->GetDLLCounts());

	int	n=0;
	for(LogicDLL *r=GetLayersBase()->GetLogicDLLBase()->GetFirst();r!=NULL;r=r->GetNext(),n++){
		WMultiGrid::CellData *L;
		L=GetData(n ,0);
		L->Value	=r->GetEnabledExpandable();
		L->CType	=WMultiGrid::_CType_CheckBox;
		L->Alignment=Qt::AlignVCenter | Qt::AlignCenter;

		L=GetData(n ,1);
		L->Value	=r->GetDLLRoot();
		L->CType	=WMultiGrid::_CType_Label;
		L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;

		L=GetData(n ,2);
		L->Value	=r->GetDLLName();
		L->CType	=WMultiGrid::_CType_Label;
		L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
	}

	SetTopHeader(0, tr(/**/""));
	SetTopHeader(1, tr(/**/"DLLRoot"));
	SetTopHeader(2, tr(/**/"DLLName"));
	setColumnWidth (0,40);
	setColumnWidth (1,120);
	setColumnWidth (2,120);
	InitialGrid();
}
void	SelectExpandableAlgorithmGrid::ChangeValue(int row ,int col,const QVariant &value)
{
	LogicDLL *r=GetLayersBase()->GetLogicDLLBase()->GetItem(row);
	if(r!=NULL){
		if(col==0)
			r->SetEnabledExpandable(value.toBool());
	}
}
void	SelectExpandableAlgorithmGrid::GetValue(int row ,int col,QVariant &value)
{
	LogicDLL *r=GetLayersBase()->GetLogicDLLBase()->GetItem(row);
	if(r!=NULL){
		if(col==0)
			value=r->GetEnabledExpandable();
		if(col==1)
			value=r->GetDLLRoot();
		if(col==2)
			value=r->GetDLLName();
	}
}


SelectExpandableAlgorithmForm::SelectExpandableAlgorithmForm(ReflectionAttrPack *_ReflectionAttrData ,LayersBase *base ,QWidget *parent)
	: QDialog(parent) ,ServiceForLayers(base),Grid(base)
{
	ui.setupUi(this);
	if(_ReflectionAttrData!=NULL)
		ReflectionAttrData=*_ReflectionAttrData;
	for(ReflectionAttr *p=ReflectionAttrData.GetFirst();p!=NULL;p=p->GetNext()){
		for(LogicDLL *r=GetLayersBase()->GetLogicDLLBase()->GetFirst();r!=NULL;r=r->GetNext()){
			if(r->CheckDLL(p->DLLRoot,p->DLLName)==true){
				r->SetEnabledExpandable(p->EnabledReflection);
			}
		}
	}

	Grid.setParent(ui.frameCheckbox);
	Grid.move(0,0);
	Grid.resize(ui.frameCheckbox->width(),ui.frameCheckbox->height());
	Grid.ShowGrid();

	InstallOperationLog(this);
}

SelectExpandableAlgorithmForm::~SelectExpandableAlgorithmForm()
{
}


void SelectExpandableAlgorithmForm::on_pushButtonOK_clicked()
{
	int	N=0;
	ReflectionAttrData.RemoveAll();
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),N++){
		ReflectionAttr	*p=new ReflectionAttr();
		p->DLLRoot=L->GetDLLRoot();
		p->DLLName=L->GetDLLName();
		if(L->GetEnabledExpandable()==true){
			p->EnabledReflection=true;
		}
		else{
			p->EnabledReflection=false;
		}
		ReflectionAttrData.AppendList(p);
	}
	done(true);
}