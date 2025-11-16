/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\InputAlignmentLargeAreaForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "EditLibraryDialogResource.h"
#include "InputAlignmentAreaForm.h"
#include "XGeneralDialog.h"

InputAlignmentAreaForm::InputAlignmentAreaForm(bool ModifyMode ,LayersBase *base ,QString areaName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base),Libs(base,this)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	setWindowTitle(LangSolver.GetString(InputAlignmentAreaForm_LS,LID_0)/*"Input"*/);
	AreaName=areaName;
	ui.EditAreaName->setText(AreaName);

	Libs.setParent(ui.frameLibrary);
	Libs.move(0,0);
	DeleteMode		=false;
	if(ModifyMode==true){
		ui.ButtonDelete->setEnabled(true);
	}
	else{
		ui.ButtonDelete->setEnabled(false);
	}

	LibFolderID =-1;
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui.tableWidgetLibList->setColumnWidth ( 0, 32);
	ui.tableWidgetLibList->setColumnWidth ( 1, 160);

	ui.tableWidgetLibListGen->setColumnWidth ( 0, 32);
	ui.tableWidgetLibListGen->setColumnWidth ( 1, 160);

	InstallOperationLog(this);
}

InputAlignmentAreaForm::~InputAlignmentAreaForm()
{

}
AlignmentFlexAreaBase	*InputAlignmentAreaForm::GetAlignmentFlexAreaBase(void)
{
	return (AlignmentFlexAreaBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentFlexArea");
}
void	InputAlignmentAreaForm::Reflect(AlignmentFlexAreaAreaList *a)
{
	ui.EditAreaName->setText(a->AreaName);
	if(a->Priority==XAlignmentFlexAreaArea::_PriorityHigh)
		ui.radioButtonPriorityHigh	->setChecked(true);
	if(a->Priority==XAlignmentFlexAreaArea::_PriorityMiddle)
		ui.radioButtonPriorityMiddle->setChecked(true);
	if(a->Priority==XAlignmentFlexAreaArea::_PriorityLow)
		ui.radioButtonPriorityLow	->setChecked(true);
	if(a->Priority==XAlignmentFlexAreaArea::_PriorityGlobal)
		ui.radioButtonPriorityLGlobal->setChecked(true);
	Libs.SetSelected(a->LimitedLib);

	LibToCreateItems=a->LibToCreateItems;
	ShowGenList();
}

void	InputAlignmentAreaForm::Reflect(void)
{
	Libs.ShowSelectedList();
	ui.EditAreaName->setText(AreaName);
	if(Priority==XAlignmentFlexAreaArea::_PriorityHigh){
		ui.radioButtonPriorityHigh	->setChecked(true);
	}
	else if(Priority==XAlignmentFlexAreaArea::_PriorityMiddle){
		ui.radioButtonPriorityMiddle	->setChecked(true);
	}
	else if(Priority==XAlignmentFlexAreaArea::_PriorityLow){
		ui.radioButtonPriorityLow	->setChecked(true);
	}
	else if(Priority==XAlignmentFlexAreaArea::_PriorityGlobal){
		ui.radioButtonPriorityLGlobal	->setChecked(true);
	}

}

void InputAlignmentAreaForm::on_ButtonCancel_clicked()
{
	reject();
}

void InputAlignmentAreaForm::on_ButtonOK_clicked()
{
	DeleteMode=false;
	AreaName=ui.EditAreaName->text();
	if(ui.radioButtonPriorityHigh->isChecked()==true){
		Priority=XAlignmentFlexAreaArea::_PriorityHigh;
	}
	else if(ui.radioButtonPriorityMiddle->isChecked()==true){
		Priority=XAlignmentFlexAreaArea::_PriorityMiddle;
	}
	else if(ui.radioButtonPriorityLow->isChecked()==true){
		Priority=XAlignmentFlexAreaArea::_PriorityLow;
	}
	else if(ui.radioButtonPriorityLGlobal->isChecked()==true){
		Priority=XAlignmentFlexAreaArea::_PriorityGlobal;
	}
	accept();
}

void InputAlignmentAreaForm::on_ButtonDelete_clicked()
{
	DeleteMode=true;
	accept();	
}
void	InputAlignmentAreaForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		CmdGetAlignmentFlexAreaLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	InputAlignmentAreaForm::ShowGenList(void)
{
	AlignmentFlexAreaBase	*BBase=GetAlignmentFlexAreaBase();
	if(BBase!=NULL){
		int	row=0;
		ui.tableWidgetLibListGen->setRowCount(LibToCreateItems.GetNumber());
		for(AlgorithmLibraryList *a=LibToCreateItems.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibListGen->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibListGen->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibListGen->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibListGen->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
void InputAlignmentAreaForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonToGenList_clicked();
}

void InputAlignmentAreaForm::on_tableWidgetLibListGen_doubleClicked(const QModelIndex &index)
{
	on_pushButtonFromGenList_clicked();
}

void InputAlignmentAreaForm::on_pushButtonToGenList_clicked()
{
	int	R=ui.tableWidgetLibList->currentRow();
	if(R<0)
		return;
	AlgorithmLibraryList	*L=LibList[R];
	if(L!=NULL){
		for(AlgorithmLibraryList *a=LibToCreateItems.GetFirst();a!=NULL;a=a->GetNext()){
			if(a->GetLibID()==L->GetLibID()){
				return;
			}
		}
		AlgorithmLibraryList *a=new AlgorithmLibraryList(*L);
		LibToCreateItems.AppendList(a);
		ShowGenList();
	}
}

void InputAlignmentAreaForm::on_pushButtonFromGenList_clicked()
{
	int	R=ui.tableWidgetLibListGen->currentRow();
	if(R<0)
		return;
	AlgorithmLibraryList *a=LibToCreateItems[R];
	if(a!=NULL){
		LibToCreateItems.RemoveList(a);
		delete	a;
		ShowGenList();
	}
}

void InputAlignmentAreaForm::on_radioButtonPriorityLGlobal_clicked()
{

}

void InputAlignmentAreaForm::on_radioButtonPriorityHigh_clicked()
{

}

void InputAlignmentAreaForm::on_radioButtonPriorityMiddle_clicked()
{

}

void InputAlignmentAreaForm::on_radioButtonPriorityLow_clicked()
{

}
