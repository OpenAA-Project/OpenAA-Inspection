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

#include "CreateManualEulerRingFormResource.h"
#include "CreateManualEulerRingForm.h"
#include "XDLLOnly.h"
#include "XEulerRing.h"
#include "XEulerRingLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

CreateManualEulerRingForm::CreateManualEulerRingForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);

	SelectedLibID=-1;
	BlockLibID	 =-1;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRing");
	int	LibType=-1;
	if(Ab!=NULL){
		CmdCreateTempEulerRingItemPacket	ItemPacket(GetLayersBase());
		Ab->TransmitDirectly(&ItemPacket);
		BItem=(EulerRingItem *)ItemPacket.Point;
		CmdCreateTempEulerRingLibraryPacket	LibPacket(GetLayersBase());
		Ab->TransmitDirectly(&LibPacket);
		TempLib=LibPacket.Point;
		LibType=Ab->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetLibList->setRowCount(0);

	ColorInspection.setParent(ui.framePanel);
	ColorInspection.Fit(ui.framePanel);

	ui.pushButtonOK->setEnabled(false);

	InstallOperationLog(this);
}

CreateManualEulerRingForm::~CreateManualEulerRingForm()
{

}

void	CreateManualEulerRingForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->setRowCount(0);
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRing");
	if(Ab!=NULL){
		CmdGetEulerRingLibraryListPacket	Packet(GetLayersBase());
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

void CreateManualEulerRingForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	AlgorithmLibraryList	*a=LibList.GetItem(Index.row());
	if(a==NULL)
		return;
	TempLib->SetLibID(a->GetLibID());

	CmdLoadEulerRingLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"EulerRing");
	if(Ab!=NULL){
		Ab->TransmitDirectly(&Packet);
		if(Packet.Success==true){
			BlockLibID					=TempLib->GetLibID();

			EulerRingLibrary	*ALib=static_cast<EulerRingLibrary *>(TempLib->GetLibrary());

			ui.EditLibID		->setText(QString::number(ALib->GetLibID()));
			ui.EditLibName		->setText(a->GetLibName());

			ui.EditMergin		->setValue(ALib->Mergin);
			ui.EditExpandedDot	->setValue(ALib->ExpandedDot);
			ColorInspection.Cube=ALib->InspectionColor;
			ColorInspection.InitializedDoneCube();
			ColorInspection.Repaint();

			ui.EditAdjustBlack	->setValue(ALib->AdjustBlack);
			ui.EditAdjustWhite	->setValue(ALib->AdjustWhite);
			ui.pushButtonOK->setEnabled(true);
		}
		else{
			QMessageBox::critical(NULL, LangSolver.GetString(CreateManualEulerRingForm_LS,LID_0)/*"Library error"*/, LangSolver.GetString(CreateManualEulerRingForm_LS,LID_1)/*"Not loaded this library record"*/);
		}
	}
}

void	CreateManualEulerRingForm::GetDataFromWindow(EulerRingItem &data)
{
	data.SetLibID(BlockLibID);

	data.GetThresholdW()->InspectionColor	=ColorInspection.Cube;
	data.GetThresholdW()->Mergin			=ui.EditMergin			->value();
	data.GetThresholdW()->ExpandedDot		=ui.EditExpandedDot		->value();
	data.GetThresholdW()->AdjustBlack		=ui.EditAdjustBlack		->value();
	data.GetThresholdW()->AdjustWhite		=ui.EditAdjustWhite		->value();
}


void CreateManualEulerRingForm::on_pushButtonOK_clicked()
{
	GetDataFromWindow(*BItem);
	done(true);
}

void CreateManualEulerRingForm::on_pushButtonCancel_clicked()
{
	done(false);
}