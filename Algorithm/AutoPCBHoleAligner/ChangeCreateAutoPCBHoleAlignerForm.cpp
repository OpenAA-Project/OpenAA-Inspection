#include "AutoPCBHoleAlignerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AutoPCBHoleAligner\ChangeCreateAutoPCBHoleAlignerForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAutoPCBHoleAligner.h"
#include "ChangeCreateAutoPCBHoleAlignerForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XGeneralDialog.h"

ChangeCreateAutoPCBHoleAlignerForm::ChangeCreateAutoPCBHoleAlignerForm(AutoPCBHoleAlignerBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base->GetLayersBase())
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	Base=base;
	LibFolderID =-1;
	pLibFolderForm=new GeneralLibFolderForm(base->GetLibType(),GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	CmdCreateTempAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
	Base->TransmitDirectly(&Packet);
	TempLib=Packet.Point;

	InstallOperationLog(this);
}

ChangeCreateAutoPCBHoleAlignerForm::~ChangeCreateAutoPCBHoleAlignerForm()
{

}

void	ChangeCreateAutoPCBHoleAlignerForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);

	CmdGetAutoPCBHoleAlignerLibraryListPacket	Packet(GetLayersBase());
	Packet.LibFolderID=LibFolderID;
	Base->TransmitDirectly(&Packet);
	LibList	=Packet.AList;
	int	row=0;
	ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
	for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetLibList->setItem ( row, 0,W);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui.tableWidgetLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetLibList->setItem ( row, 1,W);
		}
		W->setText(a->GetLibName());		
	}
}

void ChangeCreateAutoPCBHoleAlignerForm::on_ButtonOK_clicked()
{
	GetItemFromWindow(ResultAutoPCBHoleAligner);
	done(true);
}

void ChangeCreateAutoPCBHoleAlignerForm::on_ButtonCancel_clicked()
{
	done(false);
}

void	ChangeCreateAutoPCBHoleAlignerForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	AutoPCBHoleAlignerLibrary	*ALib=dynamic_cast<AutoPCBHoleAlignerLibrary *>(data.GetLibrary());
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	ui.EditExpandForPickup		->setValue	(ALib->ExpandForPickup);
	ui.checkBoxStartupExecute	->setChecked(ALib->StartupExecute);
	ui.EditMinDiameter			->setValue	(ALib->MinDiameter);
	ui.EditMaxDiameter			->setValue	(ALib->MaxDiameter);
	ui.EditFringeDot			->setValue	(ALib->FringeDot);
	ui.EditMaxSearch			->setValue	(ALib->MaxSearch);
	ui.EditThresholdDiff		->setValue	(ALib->ThresholdDiff);
	ui.checkBoxCheckOutside		->setChecked(ALib->CheckOutside);
}


void ChangeCreateAutoPCBHoleAlignerForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;

		Base->TransmitDirectly(&Packet);
		ShowLibrary(*TempLib);
	}
}

void	ChangeCreateAutoPCBHoleAlignerForm::GetItemFromWindow(AutoPCBHoleAlignerHole &data)
{
	data.SetLibID(TempLib->GetLibID());

	data.GetThresholdW()->ExpandForPickup	=ui.EditExpandForPickup		->value();
//	data.GetThresholdW()->StartupExecute	=ui.checkBoxStartupExecute	->isChecked();
	data.GetThresholdW()->MinDiameter		=ui.EditMinDiameter			->value();
	data.GetThresholdW()->MaxDiameter		=ui.EditMaxDiameter			->value();
	data.GetThresholdW()->FringeDot			=ui.EditFringeDot			->value();
//	data.GetThresholdW()->MaxSearch			=ui.EditMaxSearch			->value();
//	data.GetThresholdW()->ThresholdDiff		=ui.EditThresholdDiff		->value();
	data.GetThresholdW()->CheckOutside		=ui.checkBoxCheckOutside	->isChecked();
	data.GetThresholdW()->FromOtherAlgorithm=true;
	int FromOtherAlgorithmCount=Base->GetFromOtherAlgorithmCount(TempLib->GetLibID());
	data.GetThresholdW()->FromOtherAlgorithmIndex=FromOtherAlgorithmCount;

	Base->SetFromOtherAlgorithmCount(TempLib->GetLibID(),FromOtherAlgorithmCount+1);
}
