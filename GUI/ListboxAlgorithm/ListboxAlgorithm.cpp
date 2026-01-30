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

#include "ListboxAlgorithmResource.h"

#include "ListboxAlgorithm.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmInterfaceDLL.h"


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Inspection";
	Name=/**/"Listbox Algorithm";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Listbox to view Loaded algorithms");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListboxAlgorithm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"IsShowOrganization";
	Data[0].Pointer				 =&((ListboxAlgorithm *)Instance)->IsShowOrganization;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"IsShowPath";
	Data[1].Pointer				 =&((ListboxAlgorithm *)Instance)->IsShowPath;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"IsShowRoot";
	Data[2].Pointer				 =&((ListboxAlgorithm *)Instance)->IsShowRoot;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"IsShowName";
	Data[3].Pointer				 =&((ListboxAlgorithm *)Instance)->IsShowName;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListboxAlgorithm.png")));
}

//==================================================================================================

AlgorithmList::AlgorithmList(LayersBase *Base,QWidget *parent)
:WMultiGrid(parent),ServiceForLayers(Base)
{
}
void	AlgorithmList::ShowGrid(void)
{
	ListboxAlgorithm	*P=dynamic_cast<ListboxAlgorithm *>(parentWidget());
	int	ColumnNumb=0;
	if(P->IsShowOrganization	==true)
		ColumnNumb++;
	if(P->IsShowPath			==true)
		ColumnNumb++;
	if(P->IsShowRoot			==true)
		ColumnNumb++;
	if(P->IsShowName			==true)
		ColumnNumb++;
	SetColumnCount(ColumnNumb);
	SetRowCount(GetLayersBase()->GetLogicDLLBase()->GetDLLCounts());

	move(0,0);
	resize(width(),height());
	int	n=0;
	for(AlgorithmDLLList *r=GetLayersBase()->GetAlgoDLLContPointer()->GetFirst();r!=NULL;r=r->GetNext(),n++){
		int	ColumnNumb=0;
		if(P->IsShowOrganization	==true){
			WMultiGrid::CellData *L=GetData(n ,ColumnNumb);
			QString	Str;
			r->GetOrganization(Str);
			L->Value	=Str;
			L->CType	=WMultiGrid::_CType_Label;
			L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
			ColumnNumb++;
		}
		if(P->IsShowPath			==true){
			WMultiGrid::CellData *L=GetData(n ,ColumnNumb);
			L->Value	=r->GetFileName();
			L->CType	=WMultiGrid::_CType_Label;
			L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
			ColumnNumb++;
		}
		if(P->IsShowRoot			==true){
			WMultiGrid::CellData *L=GetData(n ,ColumnNumb);
			L->Value	=r->GetDLLRoot();
			L->CType	=WMultiGrid::_CType_Label;
			L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
			ColumnNumb++;
		}
		if(P->IsShowName			==true){
			WMultiGrid::CellData *L=GetData(n ,ColumnNumb);
			L->Value	=r->GetDLLName();
			L->CType	=WMultiGrid::_CType_Label;
			L->Alignment=Qt::AlignVCenter | Qt::AlignLeft;
			ColumnNumb++;
		}
	}

	ColumnNumb=0;
	if(P->IsShowOrganization	==true){
		SetTopHeader(ColumnNumb, LangSolver.GetString(ListboxAlgorithm_LS,LID_0)/*"Organization"*/);
		ColumnNumb++;
	}
	if(P->IsShowPath			==true){
		SetTopHeader(ColumnNumb, LangSolver.GetString(ListboxAlgorithm_LS,LID_1)/*"Path & File"*/);
		ColumnNumb++;
	}
	if(P->IsShowRoot			==true){
		SetTopHeader(ColumnNumb, LangSolver.GetString(ListboxAlgorithm_LS,LID_2)/*"Root"*/);
		ColumnNumb++;
	}
	if(P->IsShowName			==true){
		SetTopHeader(ColumnNumb, LangSolver.GetString(ListboxAlgorithm_LS,LID_3)/*"Name"*/);
		ColumnNumb++;
	}
	InitialGrid();
}
void	AlgorithmList::ChangeValue(int row ,int col,const QVariant &value)
{
}
void	AlgorithmList::GetValue(int row ,int col,QVariant &value)
{
	ListboxAlgorithm	*P=dynamic_cast<ListboxAlgorithm *>(parentWidget());
	AlgorithmDLLList *r=GetLayersBase()->GetAlgoDLLContPointer()->GetItem(row);
	if(r!=NULL){
		int	ColumnNumb=0;
		if(P->IsShowOrganization	==true){
			if(ColumnNumb==col){
				QString	Str;
				r->GetOrganization(Str);
				value=Str;
				return;
			}
			ColumnNumb++;			
		}
		if(P->IsShowPath			==true){
			if(ColumnNumb==col){
				value=r->GetFileName();
				return;
			}
			ColumnNumb++;
		}
		if(P->IsShowRoot			==true){
			if(ColumnNumb==col){
				value=r->GetDLLRoot();
				return;
			}
			ColumnNumb++;
		}
		if(P->IsShowName			==true){
			if(ColumnNumb==col){
				value=r->GetDLLName();
				return;
			}
			ColumnNumb++;
		}
	}
}

ListboxAlgorithm::ListboxAlgorithm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),MainList(Base)
{
	IsShowOrganization	=true;
	IsShowPath			=true;
	IsShowRoot			=true;
	IsShowName			=true;
	resize(400,250);
	MainList.setParent(this);
	MainList.ShowGrid();
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
ListboxAlgorithm::~ListboxAlgorithm(void)
{
}
void	ListboxAlgorithm::Prepare(void)
{
	MainList.ShowGrid();
}
void	ListboxAlgorithm::ResizeAction()
{
	MainList.resize(width(),height());
}