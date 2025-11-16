/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoPCBHoleAligner\PropertyAutoPCBHoleAlignerForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyAutoPCBHoleAlignerFormResource.h"
#include "PropertyAutoPCBHoleAlignerForm.h"
#include "ui_PropertyAutoPCBHoleAlignerForm.h"
#include "EditAutoPCBHoleAlignerLibrary.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XAutoPCBHoleAlignerPacket.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


PropertyAutoPCBHoleAlignerForm::PropertyAutoPCBHoleAlignerForm(LayersBase* Base, QWidget *parent)
    : GUIFormBase(Base, parent),
    ui(new Ui::PropertyAutoPCBHoleAlignerForm)
{
    ui->setupUi(this);
	LibFolderID = -1;
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	LibType = -1;
	if (BBase != NULL)
		LibType = BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth(0, 30);
	ui->tableWidgetLibList->setColumnWidth(1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth(0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth(1, 80);

	TempLib = NULL;
	if (BBase != NULL) {
		CmdCreateTempAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib = Packet.Point;
	}

	//?a?E?\?|???I???e?I??
	LangSolver.SetUI(this);
}

PropertyAutoPCBHoleAlignerForm::~PropertyAutoPCBHoleAlignerForm()
{
    delete ui;
}

AutoPCBHoleAlignerBase* PropertyAutoPCBHoleAlignerForm::GetAutoPCBHoleAlignerBase(void)
{
	return (AutoPCBHoleAlignerBase*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
}



void PropertyAutoPCBHoleAlignerForm::on_pushButtonEditLibrary_clicked()
{
	EditAutoPCBHoleAlignerLibrary	D(GetLayersBase(), this);
	D.exec();
}

void PropertyAutoPCBHoleAlignerForm::on_pushButtonEditLibFolder_clicked()
{
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyAutoPCBHoleAlignerForm::SetLibFolder(int _LibFolderID, const QString& LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID = _LibFolderID;
	ShowLibList();
}
void	PropertyAutoPCBHoleAlignerForm::BuildForShow(void)
{
	ShowAreaList();
}


void	PropertyAutoPCBHoleAlignerForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	if (BBase != NULL) {
		CmdGetAutoPCBHoleAlignerLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID = LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList = Packet.AList;
		int	row = 0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for (AlgorithmLibraryList* a = Packet.AList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
			QTableWidgetItem* W;
			W = ui->tableWidgetLibList->item(row, 0);
			if (W == NULL) {
				W = new QTableWidgetItem();
				ui->tableWidgetLibList->setItem(row, 0, W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString::number(a->GetLibID()));
			W = ui->tableWidgetLibList->item(row, 1);
			if (W == NULL) {
				W = new QTableWidgetItem();
				ui->tableWidgetLibList->setItem(row, 1, W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}
struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList* a;
};

void	PropertyAutoPCBHoleAlignerForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	AutoPCBHoleAlignerBase* BBase = GetAutoPCBHoleAlignerBase();
	if (BBase != NULL) {
		CmdCreateTempAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer* SLib = Packet.Point;

		int	row = 0;
		for (AlgorithmLibraryList* a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
			DDim[row].a = a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadAutoPCBHoleAlignerLibraryPacket	Packet(GetLayersBase());
			Packet.Point = SLib;
			BBase->TransmitDirectly(&Packet);
		}
		for (;;) {
			AlgorithmLibraryList* a = SelectedLibList.GetFirst();
			if (a == NULL)
				break;
			SelectedLibList.RemoveList(a);
		}
		for (int i = 0; i < row; i++) {
			SelectedLibList.AppendList(DDim[i].a);
		}
	}

	int	row = 0;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for (AlgorithmLibraryList* a = SelectedLibList.GetFirst(); a != NULL; a = a->GetNext(), row++) {
		QTableWidgetItem* W;
		W = ui->tableWidgetGeneratedLibList->item(row, 0);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem(row, 0, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W = ui->tableWidgetGeneratedLibList->item(row, 1);
		if (W == NULL) {
			W = new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem(row, 1, W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}

void PropertyAutoPCBHoleAlignerForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyAutoPCBHoleAlignerForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &)
{
	on_pushButtonGetBack_clicked();
}

void PropertyAutoPCBHoleAlignerForm::on_pushButtonSetFrom_clicked()
{
	int	r = ui->tableWidgetLibList->currentRow();
	if (r < 0)
		return;
	AlgorithmLibraryList* a = LibList.GetItem(r);
	for (AlgorithmLibraryList* c = SelectedLibList.GetFirst(); c != NULL; c = c->GetNext()) {
		if (c->GetLibID() == a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType, a->GetLibID(), a->GetLibName()));
	ShowSelectedLibList();
}

void PropertyAutoPCBHoleAlignerForm::on_pushButtonGetBack_clicked()
{
	int	r = ui->tableWidgetGeneratedLibList->currentRow();
	if (r < 0)
		return;
	AlgorithmLibraryList* a = SelectedLibList.GetItem(r);
	if (a != NULL) {
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}
void	PropertyAutoPCBHoleAlignerForm::TransmitDirectly(GUIDirectMessage* packet)
{
	GUICmdReqAutoPCBHoleAlignerDrawMode* GUICmdReqAutoPCBHoleAlignerDrawModeVar = dynamic_cast<GUICmdReqAutoPCBHoleAlignerDrawMode*>(packet);
	if (GUICmdReqAutoPCBHoleAlignerDrawModeVar != NULL) {
		if (ui->checkBoxShowHole->isChecked() == true)
			GUICmdReqAutoPCBHoleAlignerDrawModeVar->DrawHole = true;
		else
			GUICmdReqAutoPCBHoleAlignerDrawModeVar->DrawHole = false;

		if (ui->checkBoxShowFringe->isChecked() == true)
			GUICmdReqAutoPCBHoleAlignerDrawModeVar->DrawFringe = true;
		else
			GUICmdReqAutoPCBHoleAlignerDrawModeVar->DrawFringe = false;

		for (int i = 0; i < ui->tableWidgetAreaList->selectedItems().count(); i++) {
			QTableWidgetItem* s = ui->tableWidgetAreaList->selectedItems()[i];
			if (s->column() == 0) {
				GUICmdReqAutoPCBHoleAlignerDrawModeVar->SelectedLDList.Add(AAInfos.GetItem(s->row())->ID);
			}
		}
		return;
	}
	CmdSetAutoPCBHoleAlignerShowingState* CmdSetAutoPCBHoleAlignerShowingStateVar = dynamic_cast<CmdSetAutoPCBHoleAlignerShowingState*>(packet);
	if (CmdSetAutoPCBHoleAlignerShowingStateVar != NULL) {
		ui->checkBoxShowHole->setChecked(CmdSetAutoPCBHoleAlignerShowingStateVar->ModeShowingHole);
		ui->checkBoxShowFringe->setChecked(CmdSetAutoPCBHoleAlignerShowingStateVar->ModeShowingFringe);
		ShowAreaList();
		ui->tableWidgetAreaList->clearSelection();
		for (IntClass* c = CmdSetAutoPCBHoleAlignerShowingStateVar->ShowingLibIDs.GetFirst(); c != NULL; c = c->GetNext()) {
			int	Row = 0;
			for (AAHoleInfoList* b = AAInfos.GetFirst(); b != NULL; b = b->GetNext(), Row++) {
				if (b->ID == c->GetValue()) {
					break;
				}
			}
			for (int Col = 0; Col < ui->tableWidgetAreaList->columnCount(); Col++) {
				QTableWidgetItem* Item = ui->tableWidgetAreaList->item(Row, Col);
				Item->setSelected(true);
			}
		}
		return;
	}
}

void PropertyAutoPCBHoleAlignerForm::ShowAreaList(void)
{
	AAInfos.RemoveAll();
	for (int page = 0; page < GetPageNumb(); page++) {
		GUICmdReqAutoPCBHoleAlignerInfo		RCmd(GetLayersBase(), sRoot, sName, page);
		GUICmdSendAutoPCBHoleAlignerInfo	SCmd(GetLayersBase(), sRoot, sName, page);
		RCmd.Send(page, 0, SCmd);
		for (AAHoleInfoList* a = SCmd.AAInfoData.GetFirst(); a != NULL; a = a->GetNext()) {
			AAHoleInfoList* b;
			for (b = AAInfos.GetFirst(); b != NULL; b = b->GetNext()) {
				if (a->ID == b->ID) {
					break;
				}
			}
			if (b == NULL) {
				AAInfos.AppendList(new AAHoleInfoList(*a));
			}
		}
	}

	AutoPCBHoleAlignerBase* PBase = (AutoPCBHoleAlignerBase*)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoPCBHoleAligner");
	ui->tableWidgetAreaList->setRowCount(AAInfos.GetCount());
	int	Row = 0;
	for (AAHoleInfoList* b = AAInfos.GetFirst(); b != NULL; b = b->GetNext(), Row++) {
		SetDataToTable(ui->tableWidgetAreaList, 0, Row, b->ID);
		CmdGetAutoPCBHoleAlignerLibraryNamePacket	GCmd(GetLayersBase());
		GCmd.LibID = b->ID;
		PBase->TransmitDirectly(&GCmd);
		if (GCmd.Success == true) {
			SetDataToTable(ui->tableWidgetAreaList, 1, Row, GCmd.LibName);
		}
		else {
			SetDataToTable(ui->tableWidgetAreaList, 1, Row,/**/"");
		}
		SetDataToTable(ui->tableWidgetAreaList, 2, Row, b->MinDiameter);
		SetDataToTable(ui->tableWidgetAreaList, 3, Row, b->MaxDiameter);
	}
}

void PropertyAutoPCBHoleAlignerForm::on_tableWidgetAreaList_clicked(const QModelIndex&)
{
	BroadcastBuildForShow();
}
