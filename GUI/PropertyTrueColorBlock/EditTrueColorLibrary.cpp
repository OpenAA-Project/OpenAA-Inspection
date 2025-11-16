/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTrueColorBlock\EditTrueColorLibrary.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "TrueColorFormResource.h"
#include "EditTrueColorLibrary.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyTrueColorBlockPacket.h"
#include "TrueColorPickupForm.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

EditTrueColorLibrary::EditTrueColorLibrary(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());
	
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetSubtractLibList->setColumnWidth (0, 30);
	ui.tableWidgetSubtractLibList->setColumnWidth (1, 80);
	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ColorGenerator	.setParent(ui.frameGenerate);
	ColorNarrow		.setParent(ui.frameNarrowPanel);
	ColorBroad		.setParent(ui.frameBroadPanel);

	ColorGenerator	.Fit(ui.frameGenerate);
	ColorNarrow		.Fit(ui.frameNarrowPanel);
	ColorBroad		.Fit(ui.frameBroadPanel);

	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
	on_toolButtonPickup_clicked();
	on_toolButtonInspect_clicked();

	InstallOperationLog(this);
}

EditTrueColorLibrary::~EditTrueColorLibrary()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

TrueColorBlockBase	*EditTrueColorLibrary::GetTrueColorBlockBase(void)
{
	return (TrueColorBlockBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"TrueColorBlock");
}

void	EditTrueColorLibrary::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	if(BBase!=NULL){
		CmdGetTrueColorBlockLibraryListPacket	Packet(GetLayersBase());
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

void EditTrueColorLibrary::on_toolButtonPickup_clicked()
{
	if(ui.toolButtonPickup->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(0);
}

void EditTrueColorLibrary::on_toolButtonInspect_clicked()
{
	if(ui.toolButtonInspect->isChecked()==true)
		ui.stackedWidget->setCurrentIndex(1);
}

void EditTrueColorLibrary::on_pushButtonNColor_clicked()
{
	TrueColorPickupForm	D(GetLayersBase()
						,NULL
						,&ColorNarrow.Cube
						,this);
	//D.ColorPanel.Cube	=ColorNarrow.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorNarrow.Cube=D.ColorPanel.Cube;
		ColorNarrow.InitializedDoneCube();
		ColorNarrow.Repaint();
		TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());
		ALib->NInsColor	=D.ColorPanel.Cube;
	}
}

void EditTrueColorLibrary::on_pushButtonBColor_clicked()
{
	TrueColorPickupForm	D(GetLayersBase()
						,NULL
						,&ColorBroad.Cube
						,this);
	//D.ColorPanel.Cube	=ColorBroad.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorBroad.Cube=D.ColorPanel.Cube;
		ColorBroad.InitializedDoneCube();
		ColorBroad.Repaint();
		if(TempLib!=NULL){
			TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());
			ALib->BInsColor	=D.ColorPanel.Cube;
		}
	}
}
void	EditTrueColorLibrary::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(data.GetLibrary());
	ShowSubtractList(*ALib);

	ColorGenerator.Cube=ALib->PickupColor;
	ColorGenerator.InitializedDoneCube();
	ColorGenerator.Repaint();

	ui.EditMinBlockSize		->setValue(ALib->MinBlockSize);
	ui.EditMaxBlockSize		->setValue(ALib->MaxBlockSize);
	ui.EditMinBlockDots		->setValue(ALib->MinBlockDots);
	ui.EditMaxBlockDots		->setValue(ALib->MaxBlockDots);
	ui.EditLimitBlockSize	->setValue(ALib->LimitBlockSize);
	ui.EditSpaceToOutline	->setValue(ALib->SpaceToOutline);
	ui.EditNoiseSize		->setValue(ALib->NoiseSize);
	ui.EditNoiseSizePinHole	->setValue(ALib->NoiseSizePinHole);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.comboBGenerationCategory	->setCurrentIndex((int)ALib->GenerationCategory);
	ui.checkBTransparent	->setChecked(ALib->GenerationMode.Transparent);
	ui.checkBLeftPickup		->setChecked(ALib->GenerationMode.LeftPickup);
	ui.checkBOverlappedGen	->setChecked(ALib->GenerationMode.OverlappedGen);

	ui.EditNMinNGCount		->setValue(ALib->NMinNGCount);
	ui.EditBMinNGCount		->setValue(ALib->BMinNGCount);
	ui.EditNOKLength		->setValue(ALib->NOKLength);
	ui.EditBOKLength		->setValue(ALib->BOKLength);

	ui.EditNMergin			->setValue(ALib->NMergin);
	ui.EditNOKDot			->setValue(ALib->NOKDot);
	ColorNarrow.Cube		=ALib->NInsColor;
	ColorNarrow.InitializedDoneCube();
	ColorNarrow.Repaint();

	ui.EditBMergin			->setValue(ALib->BMergin);
	ui.EditBOKDot			->setValue(ALib->BOKDot);
	ColorBroad.Cube			=ALib->BInsColor;
	ColorBroad.InitializedDoneCube();
	ColorBroad.Repaint();
	ui.checkBModeEnabled		->setChecked(ALib->PointMove.ModeEnabled);
	ui.checkBModeNGCluster		->setChecked(ALib->PointMove.ModeNGCluster);
	ui.checkBModeOnlyMatching	->setChecked(ALib->PointMove.ModeOnlyMatching);
	ui.checkBModeCenterBrightFromParts	->setChecked(ALib->PointMove.ModeCenterBrightFromParts);
	ui.checkBModeAdjustable		->setChecked(ALib->PointMove.ModeAdjustable);
	ui.checkBModeInvertLogic	->setChecked(ALib->PointMove.ModeInvertLogic);

	ui.EditAdjustBlack			->setValue	(ALib->AdjustBlack);
	ui.EditAdjustWhite			->setValue	(ALib->AdjustWhite);
	ui.checkBModeCommonMovable	->setChecked(ALib->PointMove.ModeCommonMovable);
	ui.EditSelfSearch			->setValue	(ALib->SelfSearch);
	ui.EditCommonMoveDot		->setValue	(ALib->CommonMoveDot);
}

void	EditTrueColorLibrary::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(data.GetLibrary());
	ALib->PickupColor		=ColorGenerator.Cube;
	ALib->MinBlockSize		=ui.EditMinBlockSize	->value();
	ALib->MaxBlockSize		=ui.EditMaxBlockSize	->value();
	ALib->MinBlockDots		=ui.EditMinBlockDots	->value();
	ALib->MaxBlockDots		=ui.EditMaxBlockDots	->value();
	ALib->LimitBlockSize	=ui.EditLimitBlockSize	->value();
	ALib->SpaceToOutline	=ui.EditSpaceToOutline	->value();
	ALib->NoiseSize			=ui.EditNoiseSize		->value();
	ALib->NoiseSizePinHole	=ui.EditNoiseSizePinHole->value();
	ALib->Priority			=ui.EditPriority		->value();
	ALib->GenerationCategory=(TrueColorBlockLibrary::_GenerationCategory)ui.comboBGenerationCategory	->currentIndex();
	ALib->GenerationMode.Transparent	=ui.checkBTransparent	->isChecked();
	ALib->GenerationMode.LeftPickup		=ui.checkBLeftPickup	->isChecked();
	ALib->GenerationMode.OverlappedGen	=ui.checkBOverlappedGen	->isChecked();

	ALib->NMergin		=ui.EditNMergin			->value();
	ALib->NOKDot		=ui.EditNOKDot			->value();
	ALib->NInsColor		=ColorNarrow.Cube;
	ALib->BMergin		=ui.EditBMergin			->value();
	ALib->BOKDot		=ui.EditBOKDot			->value();
	ALib->BInsColor		=ColorBroad.Cube;
	ALib->PointMove.ModeEnabled				=ui.checkBModeEnabled			->isChecked();
	ALib->PointMove.ModeNGCluster			=ui.checkBModeNGCluster			->isChecked();
	ALib->PointMove.ModeOnlyMatching		=ui.checkBModeOnlyMatching		->isChecked();
	ALib->PointMove.ModeCenterBrightFromParts=ui.checkBModeCenterBrightFromParts	->isChecked();
	ALib->PointMove.ModeAdjustable			=ui.checkBModeAdjustable		->isChecked();
	ALib->PointMove.ModeInvertLogic			=ui.checkBModeInvertLogic		->isChecked();
	ALib->AdjustBlack	=ui.EditAdjustBlack		->value();
	ALib->AdjustWhite	=ui.EditAdjustWhite		->value();
	ALib->PointMove.ModeCommonMovable		=ui.checkBModeCommonMovable	->isChecked();
	ALib->SelfSearch	=ui.EditSelfSearch		->value();
	ALib->CommonMoveDot	=ui.EditCommonMoveDot	->value();
	
	ALib->NMinNGCount	=ui.EditNMinNGCount		->value();
	ALib->BMinNGCount	=ui.EditBMinNGCount		->value();
	ALib->NOKLength		=ui.EditNOKLength		->value();
	ALib->BOKLength		=ui.EditBOKLength		->value();
}

void EditTrueColorLibrary::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void EditTrueColorLibrary::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(EditTrueColorLibrary_LS,LID_0)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(EditTrueColorLibrary_LS,LID_1)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}

}

void EditTrueColorLibrary::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditTrueColorLibrary_LS,LID_2)/*"Warning"*/, LangSolver.GetString(EditTrueColorLibrary_LS,LID_3)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);

	CmdInsertTrueColorBlockLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditTrueColorLibrary::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(EditTrueColorLibrary_LS,LID_4)/*"Warning"*/, LangSolver.GetString(EditTrueColorLibrary_LS,LID_5)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void EditTrueColorLibrary::on_pushButtonClose_clicked()
{
	close();
}

void EditTrueColorLibrary::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadTrueColorBlockLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(EditTrueColorLibrary_LS,LID_6)/*"Library error"*/, LangSolver.GetString(EditTrueColorLibrary_LS,LID_7)/*"Not loaded this library record"*/);
			}
		}
	}

}

void EditTrueColorLibrary::on_ButtonAddSubtractLib_3_clicked()
{
	if(TempLib==NULL)
		return;
	/*
	TrueColorSelectBlockLibraryForm	D(GetLayersBase(),this);
	if(D.exec()==QDialog::Accepted){
		int	LibID=D.SelectedLibID;
		if(TempLib->SubtractBlock.IsInclude(LibID)==true)
			return;
		TempLib->SubtractBlock.AppendList(new IntClass(LibID));
		ShowSubtractList(*TempLib);
	}
	*/
}

void EditTrueColorLibrary::on_ButtonDelSubtractLib_3_clicked()
{
	QModelIndex	RIndex=ui.tableWidgetSubtractLibList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());
	IntClass *c=ALib->SubtractBlock.GetItem(R);
	if(c!=NULL){
		ALib->SubtractBlock.RemoveList(c);
		delete	c;
		ShowSubtractList(*(TrueColorBlockLibrary *)TempLib->GetLibrary());
	}
}
void EditTrueColorLibrary::ShowSubtractList(TrueColorBlockLibrary &data)
{
	if(TempLib==NULL)
		return;
	CmdGetTrueColorBlockLibraryNamePacket	LNamePacket(GetLayersBase());

	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext()){
		LNamePacket.AList.AppendList(new AlgorithmLibraryList(LibType,c->GetValue(),/**/""));
	}
	TrueColorBlockBase	*BBase=GetTrueColorBlockBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&LNamePacket);
	}
	int	row=0;
	ui.tableWidgetSubtractLibList->setRowCount(data.SubtractBlock.GetCount());
	for(IntClass *c=data.SubtractBlock.GetFirst();c!=NULL;c=c->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetSubtractLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetSubtractLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(c->GetValue()));
		AlgorithmLibraryList	*a=LNamePacket.AList.GetItem(row);
		W=ui.tableWidgetSubtractLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetSubtractLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}


void EditTrueColorLibrary::on_pushButtonGColor_clicked()
{
	TrueColorPickupForm	D(GetLayersBase()
						,NULL
						,&ColorGenerator.Cube
						,this);
	//D.ColorPanel.Cube	=ColorGenerator.Cube;
	D.ColorPanel.InitializedDoneCube();
	if(D.exec()==(int)true){
		ColorGenerator.Cube=D.ColorPanel.Cube;
		ColorGenerator.InitializedDoneCube();
		ColorGenerator.Repaint();
		if(TempLib!=NULL){
			TrueColorBlockLibrary	*ALib=dynamic_cast<TrueColorBlockLibrary *>(TempLib->GetLibrary());
			ALib->PickupColor=D.ColorPanel.Cube;
		}
	}
}