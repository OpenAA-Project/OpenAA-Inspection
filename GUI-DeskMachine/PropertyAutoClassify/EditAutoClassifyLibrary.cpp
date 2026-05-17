/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\PropertyAutoClassify\EditAutoClassifyLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditAutoClassifyLibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XAutoClassify.h"
#include <QMessageBox>
//#include "XGUI.h"
#include "XGeneralDialog.h"

class	LayersBase;

EditAutoClassifyLibrary::EditAutoClassifyLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	LibFolderID =-1;
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAutoClassifyLibraryPacket	Packet(base);
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

EditAutoClassifyLibrary::~EditAutoClassifyLibrary()
{
	if(TempLib!=NULL){
		delete	TempLib;
		TempLib=NULL;
	}
}

AutoClassifyBase	*EditAutoClassifyLibrary::GetAutoClassifyBase(void)
{
	return (AutoClassifyBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
}

void	EditAutoClassifyLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibList->setRowCount(0);
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	if(BBase!=NULL){
		CmdGetAutoClassifyLibraryListPacket	Packet(GetLayersBase());
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
void EditAutoClassifyLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAutoClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoClassifyBase	*BBase=GetAutoClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL	,"Library error"
											,"Not loaded this library record");
			}
		}
	}
}

void	EditAutoClassifyLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	AutoClassifyLibrary	*ALib=dynamic_cast<AutoClassifyLibrary *>(data.GetLibrary());
	ui.EditMinBlockSize		->setValue(ALib->MinAreaSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxAreaSize);
	ui.EditMinBlockDots		->setValue(ALib->MinAreaDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxAreaDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitAreaSize);

	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditPriority			->setValue(ALib->Priority);
}

void	EditAutoClassifyLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());
	AutoClassifyLibrary	*ALib=dynamic_cast<AutoClassifyLibrary *>(data.GetLibrary());

	ALib->MinAreaSize	=ui.EditMinBlockSize	->value();
	ALib->MaxAreaSize	=ui.EditMaxBlockSize	->value();
	ALib->MinAreaDots	=ui.EditMinBlockDots	->value();
	ALib->MaxAreaDots	=ui.EditMaxBlockDots	->value();
	ALib->LimitAreaSize	=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize		=ui.EditNoiseSize		->value();
	ALib->Priority		=ui.EditPriority		->value();
}

void EditAutoClassifyLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearAutoClassifyLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditAutoClassifyLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=QString("Delete OK?");
	int	ret=QMessageBox::question(NULL, "Choose"
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAutoClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoClassifyBase	*BBase=GetAutoClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditAutoClassifyLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning"
																, "No Library Name"
																, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertAutoClassifyLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoClassifyBase	*BBase=GetAutoClassifyBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditAutoClassifyLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, /**/"Warning"
																	, "No Library Name"
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertAutoClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoClassifyBase	*BBase=GetAutoClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAutoClassifyLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoClassifyBase	*BBase=GetAutoClassifyBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditAutoClassifyLibrary::on_pushButton_clicked()
{
	close();

}
