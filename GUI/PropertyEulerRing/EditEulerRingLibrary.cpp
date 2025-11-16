#include "CreateManualEulerRingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyEulerRing\EditEulerRingLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "EditEulerRingLibrary.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyEulerRingPacket.h"
#include "EulerRingPickupForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditEulerRingLibrary::EditEulerRingLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);

	LibFolderID =-1;
	EulerRingBase	*BBase=GetEulerRingBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempEulerRingLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ColorGeneratorH	.setParent(ui.frameGenerateH);
	ColorGeneratorC	.setParent(ui.frameGenerateC);
	ColorInspection	.setParent(ui.framePanel);

	ColorGeneratorH	.Fit(ui.frameGenerateH);
	ColorGeneratorC	.Fit(ui.frameGenerateC);
	ColorInspection	.Fit(ui.framePanel);

	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();

	InstallOperationLog(this);
}

EditEulerRingLibrary::~EditEulerRingLibrary()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

EulerRingBase	*EditEulerRingLibrary::GetEulerRingBase(void)
{
	return (EulerRingBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRing");
}

void	EditEulerRingLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	EulerRingBase	*BBase=GetEulerRingBase();
	if(BBase!=NULL){
		CmdGetEulerRingLibraryListPacket	Packet(GetLayersBase());
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

void	EditEulerRingLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(data.GetLibrary());
	ColorGeneratorH.Cube=ALib->HoleColor;
	ColorGeneratorH.InitializedDoneCube();
	ColorGeneratorH.Repaint();

	ColorGeneratorC.Cube=ALib->CupperColor;
	ColorGeneratorC.InitializedDoneCube();
	ColorGeneratorC.Repaint();

	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditExpandedDotToPad	->setValue(ALib->ExpandedDotToPad);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);

	ui.EditMergin			->setValue(ALib->Mergin);
	ui.EditExpandedDot		->setValue(ALib->ExpandedDot);
	ColorInspection.Cube		=ALib->InspectionColor;
	ColorInspection.InitializedDoneCube();
	ColorInspection.Repaint();

	ui.EditAdjustBlack		->setValue(ALib->AdjustBlack);
	ui.EditAdjustWhite		->setValue(ALib->AdjustWhite);
}

void	EditEulerRingLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(data.GetLibrary());
	ALib->HoleColor			=ColorGeneratorH.Cube;
	ALib->CupperColor		=ColorGeneratorC.Cube;
	ALib->MinBlockSize		=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize		=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots		=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots		=ui.EditMaxBlockDots	->value();
	ALib->ExpandedDotToPad	=ui.EditExpandedDotToPad->value();
	ALib->NoiseSize			=ui.EditNoiseSize		->value();

	ALib->Mergin			=ui.EditMergin			->value();
	ALib->ExpandedDot		=ui.EditExpandedDot		->value();
	ALib->InspectionColor	=ColorInspection.Cube;
	ALib->AdjustBlack		=ui.EditAdjustBlack		->value();
	ALib->AdjustWhite		=ui.EditAdjustWhite		->value();
}

void EditEulerRingLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadEulerRingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingBase	*BBase=GetEulerRingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(EditEulerRingLibrary_LS,LID_2)/*"Library error"*/, LangSolver.GetString(EditEulerRingLibrary_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void EditEulerRingLibrary::on_toolButtonPickup_clicked()
{
	if(ui.toolButtonPickup->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(0);
}

void EditEulerRingLibrary::on_toolButtonInspect_clicked()
{
	if(ui.toolButtonInspect->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(1);
}

void EditEulerRingLibrary::on_pushButtonGColor_clicked()
{
	EulerRingPickupForm	D(GetLayersBase()
						,NULL
						,this);
	D.ColorPanel.Cube	=ColorGeneratorH.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorGeneratorH.Cube=D.ColorPanel.Cube;
		ColorGeneratorH.InitializedDoneCube();
		ColorGeneratorH.Repaint();
		if(TempLib!=NULL){
			EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(TempLib->GetLibrary());
			ALib->HoleColor=D.ColorPanel.Cube;
		}
	}
}

void EditEulerRingLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditEulerRingLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditEulerRingLibrary_LS,LID_4)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditEulerRingLibrary_LS,LID_5)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteEulerRingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingBase	*BBase=GetEulerRingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditEulerRingLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditEulerRingLibrary_LS,LID_6)/*"Warning"*/, LangSolver.GetString(EditEulerRingLibrary_LS,LID_7)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertEulerRingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	EulerRingBase	*BBase=GetEulerRingBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditEulerRingLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditEulerRingLibrary_LS,LID_8)/*"Warning"*/, LangSolver.GetString(EditEulerRingLibrary_LS,LID_9)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertEulerRingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingBase	*BBase=GetEulerRingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateEulerRingLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		EulerRingBase	*BBase=GetEulerRingBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditEulerRingLibrary::on_pushButtonClose_clicked()
{
	close();
}

void EditEulerRingLibrary::on_pushButtonNColor_clicked()
{
	EulerRingPickupForm	D(GetLayersBase()
						,NULL
						,this);
	D.ColorPanel.Cube	=ColorInspection.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorInspection.Cube=D.ColorPanel.Cube;
		ColorInspection.InitializedDoneCube();
		ColorInspection.Repaint();
		EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(TempLib->GetLibrary());
		ALib->InspectionColor	=D.ColorPanel.Cube;
	}
}

void EditEulerRingLibrary::on_pushButtonCColor_clicked()
{
	EulerRingPickupForm	D(GetLayersBase()
						,NULL
						,this);
	D.ColorPanel.Cube	=ColorGeneratorC.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorGeneratorC.Cube=D.ColorPanel.Cube;
		ColorGeneratorC.InitializedDoneCube();
		ColorGeneratorC.Repaint();
		if(TempLib!=NULL){
			EulerRingLibrary	*ALib=dynamic_cast<EulerRingLibrary *>(TempLib->GetLibrary());
			ALib->CupperColor=D.ColorPanel.Cube;
		}
	}
}