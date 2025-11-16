#include "EditStatisticBlockLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticBlock\EditStatisticBlockLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditStatisticBlockLibrary.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyStatisticBlockPacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditStatisticBlockLibrary::EditStatisticBlockLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LibFolderID =-1;
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempStatisticBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();
	InstallOperationLog(this);
}

EditStatisticBlockLibrary::~EditStatisticBlockLibrary()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

StatisticBlockBase	*EditStatisticBlockLibrary::GetStatisticBlockBase(void)
{
	return (StatisticBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
}

void	EditStatisticBlockLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	if(BBase!=NULL){
		CmdGetStatisticBlockLibraryListPacket	Packet(GetLayersBase());
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

void EditStatisticBlockLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadStatisticBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
}

void	EditStatisticBlockLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(data.GetLibrary());
	ui.EditPickupL			->setValue(ALib->PickupL);
	ui.EditPickupH			->setValue(ALib->PickupH);
	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.EditOverlapDot		->setValue(ALib->OverlapDot);
	ui.comboBGenerationCategory	->setCurrentIndex((int)ALib->GenerationCategory);
	ui.checkBTransparent	->setChecked(ALib->GenerationMode.Transparent);
	ui.checkBLeftPickup		->setChecked(ALib->GenerationMode.LeftPickup);
	ui.checkBOverlappedGen	->setChecked(ALib->GenerationMode.OverlappedGen);

	ui.EditBrightWidthL		->setText	(QString::number(ALib->BrightWidthL));
	ui.EditBrightWidthH		->setText	(QString::number(ALib->BrightWidthH));
	ui.EditOKDotL			->setValue	(ALib->OKDotL);
	ui.EditOKDotH			->setValue	(ALib->OKDotH);
	ui.EditOKLengthL		->setValue	(ALib->OKLengthL);
	ui.EditOKLengthH		->setValue	(ALib->OKLengthH);
	ui.checkBModeEnabled	->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeAbsoluteBright	->setChecked(ALib->PointMove.ModeAbsoluteBright);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeWhiteMask		->setChecked(ALib->PointMove.ModeWhiteMask);
	ui.checkBModeBlackMask		->setChecked(ALib->PointMove.ModeBlackMask);
	ui.EditAdjustBlack			->setValue	(ALib->AdjustBlack);
	ui.EditAdjustWhite			->setValue	(ALib->AdjustWhite);

	ui.checkUseMorphology		->setChecked(ALib->UseMorphology);
	ui.comboBoxMorphologyApplyTo->setCurrentIndex((int)ALib->MorphologyApplyTo);
	ui.checkEliminateAcnode		->setChecked(ALib->EliminateAcnode);
	ui.EditDilationDotCount		->setValue	(ALib->DilationDotCount);
	ui.EditErosionDotCount		->setValue	(ALib->ErosionDotCount);

	emit on_checkUseMorphology_toggled(ui.checkUseMorphology->isChecked());
}

void	EditStatisticBlockLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	StatisticBlockLibrary	*ALib=dynamic_cast<StatisticBlockLibrary *>(data.GetLibrary());
	data.SetLibName(ui.EditLibName	->text());
	ALib->PickupL		=ui.EditPickupL			->value();
	ALib->PickupH		=ui.EditPickupH			->value();
	ALib->MinBlockSize	=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize	=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots	=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots	=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize		=ui.EditNoiseSize		->value();
	ALib->Priority		=ui.EditPriority		->value();
	ALib->OverlapDot	=ui.EditOverlapDot		->value();
	ALib->GenerationCategory	=(StatisticBlockLibrary::_GenerationCategory)ui.comboBGenerationCategory->currentIndex();
	ALib->GenerationMode.Transparent	=ui.checkBTransparent	->isChecked();
	ALib->GenerationMode.LeftPickup		=ui.checkBLeftPickup	->isChecked();
	ALib->GenerationMode.OverlappedGen	=ui.checkBOverlappedGen->isChecked();

	ALib->BrightWidthL	=ui.EditBrightWidthL	->text().toDouble();
	ALib->BrightWidthH	=ui.EditBrightWidthH	->text().toDouble();
	ALib->OKDotL		=ui.EditOKDotL			->value();
	ALib->OKDotH		=ui.EditOKDotH			->value();
	ALib->OKLengthL		=ui.EditOKLengthL		->value();
	ALib->OKLengthH		=ui.EditOKLengthH		->value();
	ALib->PointMove.ModeEnabled			=ui.checkBModeEnabled		->isChecked();
	ALib->PointMove.ModeAbsoluteBright	=ui.checkBModeAbsoluteBright->isChecked();
	ALib->PointMove.ModeNGCluster		=ui.checkBModeNGCluster		->isChecked();
	ALib->PointMove.ModeWhiteMask		=ui.checkBModeWhiteMask		->isChecked();
	ALib->PointMove.ModeBlackMask		=ui.checkBModeBlackMask		->isChecked();
	ALib->AdjustBlack	=ui.EditAdjustBlack		->value();
	ALib->AdjustWhite	=ui.EditAdjustWhite		->value();

	ALib->UseMorphology		=ui.checkUseMorphology		->isChecked();
	ALib->MorphologyApplyTo	=(StatisticBlockLibrary::_MorphologyApplyTo)ui.comboBoxMorphologyApplyTo->currentIndex();
	ALib->EliminateAcnode	=ui.checkEliminateAcnode	->isChecked();
	ALib->DilationDotCount	=ui.EditDilationDotCount	->value();
	ALib->ErosionDotCount	=ui.EditErosionDotCount	->value();
}


void EditStatisticBlockLibrary::on_toolButtonPickup_clicked()
{
	if(ui.toolButtonPickup->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(0);
}

void EditStatisticBlockLibrary::on_toolButtonInspect_clicked()
{
	if(ui.toolButtonInspect->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(1);
}

void EditStatisticBlockLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditStatisticBlockLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditStatisticBlockLibrary_LS,LID_0)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditStatisticBlockLibrary_LS,LID_1)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteStatisticBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void EditStatisticBlockLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditStatisticBlockLibrary_LS,LID_2)/*"Warning"*/, LangSolver.GetString(EditStatisticBlockLibrary_LS,LID_3)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);

	CmdInsertStatisticBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	StatisticBlockBase	*BBase=GetStatisticBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditStatisticBlockLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditStatisticBlockLibrary_LS,LID_4)/*"Warning"*/, LangSolver.GetString(EditStatisticBlockLibrary_LS,LID_5)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertStatisticBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateStatisticBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		StatisticBlockBase	*BBase=GetStatisticBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditStatisticBlockLibrary::on_pushButton_clicked()
{
	close();
}

void EditStatisticBlockLibrary::on_checkUseMorphology_toggled(bool checked)
{
	ui.comboBoxMorphologyApplyTo ->setEnabled(checked);
	ui.checkEliminateAcnode      ->setEnabled(checked);
	ui.EditDilationDotCount     ->setEnabled(checked);
	ui.EditErosionDotCount      ->setEnabled(checked);
}