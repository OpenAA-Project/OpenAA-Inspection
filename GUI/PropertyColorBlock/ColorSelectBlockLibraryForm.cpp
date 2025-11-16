/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorBlock\ColorSelectBlockLibraryForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyColorBlockFormResource.h"
#include "ColorSelectBlockLibraryForm.h"
#include "XDLLOnly.h"
#include "XColorBlockInspection.h"
#include "XGeneralDialog.h"

ColorSelectBlockLibraryForm::ColorSelectBlockLibraryForm(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	SelectedLibID=-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	int	LibType=-1;
	if(Ab!=NULL){
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	InstallOperationLog(this);
}

ColorSelectBlockLibraryForm::~ColorSelectBlockLibraryForm()
{

}

void	ColorSelectBlockLibraryForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"ColorBlockInspection");
	if(Ab!=NULL){
		CmdGetColorBlockLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		Ab->TransmitDirectly(&Packet);
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


void ColorSelectBlockLibraryForm::on_ButtonSelect_clicked()
{
	QModelIndex	RIndex=ui.tableWidgetLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	AlgorithmLibraryList	*a=LibList.GetItem(R);
	if(a!=NULL){
		SelectedLibID=a->GetLibID();
		accept ();
	}
}

void ColorSelectBlockLibraryForm::on_ButtonCancel_clicked()
{
	 reject();
}

void ColorSelectBlockLibraryForm::on_tableWidgetLibList_doubleClicked(QModelIndex Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a!=NULL){
		SelectedLibID=a->GetLibID();
		accept ();
	}
}
