#include "PickupColorFormResource.h"
#include "PropertyPixelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyPixel\PropertyPixelInspectionForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyPixelInspectionForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyPixelInspectionPacket.h"
#include "XPixelInspection.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include <QHeaderView>
#include "XGeneralDialog.h"
//#include "XPropertyStatisticImagerCommon.h"

PropertyPixelInspectionForm::PropertyPixelInspectionForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base ,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	{
		LibType=BBase->GetLibType();
	}
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui.tableWidgetLibList->setColumnWidth (0, 50);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetLibList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

	TempLib		=NULL;
	if(BBase!=NULL){
		CmdCreateTempPixelInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.pbDelete	->setEnabled(true);
	ui.pbUpdate	->setEnabled(true);

	connect(ui.pbClearNew			,SIGNAL(clicked())						,this,SLOT(pbClearNewClicked()));
	connect(ui.pbDelete				,SIGNAL(clicked())						,this,SLOT(pbDeleteClicked()));
	connect(ui.pbSaveNew			,SIGNAL(clicked())						,this,SLOT(pbSaveNewClicked()));
	connect(ui.pbUpdate				,SIGNAL(clicked())						,this,SLOT(pbUpdateClicked()));
	connect(ui.tableWidgetLibList	,SIGNAL(clicked(const QModelIndex &))	,this,SLOT(tableWidgetLibListClicked(const QModelIndex &)));
}

PropertyPixelInspectionForm::~PropertyPixelInspectionForm()
{
}

void	PropertyPixelInspectionForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->clear();
	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	if(BBase!=NULL){
		CmdGetPixelInspectionLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyPixelInspectionForm::BuildForShow(void)
{
	AlgorithmBase	*AutoAlignmentBasePointer=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
	if(AutoAlignmentBasePointer==NULL)
		return;
	//?A???a??
	CmdReqAutoAlignmentEnumLibs	CmdEnum(GetLayersBase());
	AutoAlignmentBasePointer->TransmitDirectly(&CmdEnum);

	//???C?u?????I?Å˜?Å ?R?[?h?a?3?-?A?a???z?O???A?Å˜?Å ?A?Å·?e
	AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(AutoAlignmentBasePointer->GetLibraryContainer()->CreateNew());
	if(ALib==NULL)
		return;

	AlgorithmLibraryContainer	*Container=AutoAlignmentBasePointer->GetLibraryContainer();
	AlgorithmLibraryLevelContainer	AutoAlignmentLib(Container);
	for(IntClass *LibIDPoint=CmdEnum.LibIDList.GetFirst();LibIDPoint!=NULL;LibIDPoint=LibIDPoint->GetNext()){
		int	LibID=LibIDPoint->GetValue();	
		AutoAlignmentBasePointer->GetLibraryContainer()->GetLibrary(LibID,AutoAlignmentLib);
	}

	AutoAlignmentBasePointer->GetLibraryContainer()->Update(AutoAlignmentLib);
	
	//?A?a?Ecreate?É ???a?I?I???|?I?E?i???ÅE?e
	delete	ALib;
}

PixelInspectionBase	*PropertyPixelInspectionForm::GetPixelInspectionBase(void)
{
	PixelInspectionBase	*ABase=dynamic_cast<PixelInspectionBase *>(GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PixelInspection"));
	return ABase;
}

void	PropertyPixelInspectionForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0){
		ui.EditLibID->setText(/**/"");
	}
	else{
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	}
	ui.EditLibName	->setText(data.GetLibName());

	PixelInspectionLibrary	*ALib=dynamic_cast<PixelInspectionLibrary *>(data.GetLibrary());
    ui.chbDetailSettingNarrow		->setChecked(ALib->DetailSettingNarrow);
    ui.sbSearchDotMasterNarrow		->setValue	(ALib->SearchDotMasterNarrow);
    ui.sbSearchDotTargetNarrow		->setValue	(ALib->SearchDotTargetNarrow);
    ui.dsbRelativeNGThresholdNarrow	->setValue	(ALib->RelativeNGThresholdNarrow);
    ui.sbAbsoluteNGThresholdNarrow	->setValue	(ALib->AbsoluteNGThresholdNarrow);
    ui.sbNGSizeNarrow				->setValue	(ALib->NGSizeNarrow);

    ui.chbDetailSettingBroad		->setChecked(ALib->DetailSettingBroad);
    ui.sbSearchDotMasterBroad		->setValue	(ALib->SearchDotMasterBroad);
    ui.sbSearchDotTargetBroad		->setValue	(ALib->SearchDotTargetBroad);
    ui.dsbRelativeNGThresholdBroad	->setValue	(ALib->RelativeNGThresholdBroad);
    ui.sbAbsoluteNGThresholdBroad	->setValue	(ALib->AbsoluteNGThresholdBroad);
    ui.sbNGSizeBroad				->setValue	(ALib->NGSizeBroad);

    ui.chbIsCalcPixelInterPoration	->setChecked(ALib->IsCalcPixelInterPoration);
}

void	PropertyPixelInspectionForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	PixelInspectionLibrary	*ALib=dynamic_cast<PixelInspectionLibrary *>(data.GetLibrary());
	ALib->DetailSettingNarrow		=ui.chbDetailSettingNarrow		->isChecked();
	ALib->SearchDotMasterNarrow		=ui.sbSearchDotMasterNarrow		->value();
	ALib->SearchDotTargetNarrow		=ui.sbSearchDotTargetNarrow		->value();
	ALib->RelativeNGThresholdNarrow	=ui.dsbRelativeNGThresholdNarrow->value();
	ALib->AbsoluteNGThresholdNarrow	=ui.sbAbsoluteNGThresholdNarrow	->value();
	ALib->NGSizeNarrow				=ui.sbNGSizeNarrow				->value();

	ALib->DetailSettingBroad		=ui.chbDetailSettingBroad		->isChecked();
	ALib->SearchDotMasterBroad		=ui.sbSearchDotMasterBroad		->value();
	ALib->SearchDotTargetBroad		=ui.sbSearchDotTargetBroad		->value();
	ALib->RelativeNGThresholdBroad	=ui.dsbRelativeNGThresholdBroad	->value();
	ALib->AbsoluteNGThresholdBroad	=ui.sbAbsoluteNGThresholdBroad	->value();
	ALib->NGSizeBroad				=ui.sbNGSizeBroad				->value();

	ALib->IsCalcPixelInterPoration	=ui.chbIsCalcPixelInterPoration	->isChecked();
}

void	PropertyPixelInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	/*
	CmdPixelInsMouseMove	*CmdPixelInsMouseMoveVar=dynamic_cast<CmdPixelInsMouseMove *>(packet);
	if(CmdPixelInsMouseMoveVar!=NULL){
		int	Page=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(CmdPixelInsMouseMoveVar->GlobalX ,CmdPixelInsMouseMoveVar->GlobalY);
		if(Page>=0){
			PixelInspectionBase	*ABase=GetPixelInspectionBase();
			if(ABase!=NULL){
				PixelInspectionInPage	*P=dynamic_cast<PixelInspectionInPage *>(ABase->GetPageData(Page));
				if(P!=NULL){
					CmdGetPixelInsDataFromGlobalPoint	RCmd;
					RCmd.GlobalX=CmdPixelInsMouseMoveVar->GlobalX;
					RCmd.GlobalY=CmdPixelInsMouseMoveVar->GlobalY;
					ABase->TransmitDirectly(&RCmd);
					//ColorLogic	L=P->GetColorTable(RCmd.PData.LogicCode);
					ui.spinBoxSearchDot->setValue(RCmd.PData.SearchDot);
					//ColorRaw.Cube=L;
					//ColorRaw.InitializedDoneCube();
					//ColorRaw.Repaint();
					return;
				}
			}
		}
	}
	*/
	CmdPixelPickupArea	*CmdPixelPickupAreaVar=dynamic_cast<CmdPixelPickupArea *>(packet);
	if(CmdPixelPickupAreaVar!=NULL){
		int	Page=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(CmdPixelPickupAreaVar->Area);
		if(Page>=0){
			PixelInspectionBase	*ABase=GetPixelInspectionBase();
			if(ABase!=NULL){
				PixelInspectionInPage	*P=dynamic_cast<PixelInspectionInPage *>(ABase->GetPageData(Page));
				if(P!=NULL){
					CmdGetPixelGenerateDataFromArea	RCmd(GetLayersBase());
					RCmd.LocalArea=CmdPixelPickupAreaVar->Area;
					P->GetDataInPage()->ClipMoveAreaFromGlobal(RCmd.LocalArea);
					P->TransmitDirectly(&RCmd);
					return;
				}
			}
		}
	}
}


void	PropertyPixelInspectionForm::ShowInEdit(void)
{
}

void PropertyPixelInspectionForm::pbClearNewClicked()
{
/*
	if(TempLib==NULL){
		return;
	}
	TempLib->Reset();
	TempLib->SetLibName(ui.EditLibName	->text());

	ui.pbDelete	->setEnabled(false);
	ui.pbUpdate	->setEnabled(false);

	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertPixelInspectionLibraryPacket	Packet;
	Packet.Point=TempLib;
	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
		if(TempLib->GetLibID()<0){
			ui.EditLibName->setText("");
		}
		else{
			ui.EditLibName->setText(QString::number(TempLib->GetLibID()));
		}

		ui.pbDelete	->setEnabled(true);
		ui.pbUpdate	->setEnabled(true);
		SlotSelectLibFolder(LibFolderID ,"");
	}
*/
	if(TempLib==NULL){
		return;
	}
	TempLib->Reset();
	CmdCreateTempPixelInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*(Packet.Point));
	ui.pbDelete	->setEnabled(false);
	ui.pbUpdate	->setEnabled(false);
}

void PropertyPixelInspectionForm::pbDeleteClicked()
{
	if(TempLib==NULL){
		return;
	}
	if(TempLib->GetLibID()<0){
		return;
	}
	QString  msg=LangSolver.GetString(PropertyPixelInspectionForm_LS,LID_0)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(PropertyPixelInspectionForm_LS,LID_1)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeletePixelInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		PixelInspectionBase	*BBase=GetPixelInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			pbClearNewClicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void PropertyPixelInspectionForm::pbSaveNewClicked()
{
	if(TempLib==NULL){
		return;
	}
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyPixelInspectionForm_LS,LID_2)/*"Warning"*/, LangSolver.GetString(PropertyPixelInspectionForm_LS,LID_3)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok){
			return;
		}
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertPixelInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
///		ShowLibrary(*TempLib);
		ui.pbDelete	->setEnabled(true);
		ui.pbUpdate	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void PropertyPixelInspectionForm::pbUpdateClicked()
{
	if(TempLib==NULL){
		return;
	}
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName().isEmpty()==true){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyPixelInspectionForm_LS,LID_4)/*"Warning"*/, LangSolver.GetString(PropertyPixelInspectionForm_LS,LID_5)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok){
			return;
		}
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);
		CmdInsertPixelInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		PixelInspectionBase	*BBase=GetPixelInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(TempLib->GetLibID()<0){
				ui.EditLibID->setText(/**/"");
			}
			else{
				ui.EditLibID->setText(QString::number(TempLib->GetLibID()));
			}
			ui.pbDelete	->setEnabled(true);
			ui.pbUpdate	->setEnabled(true);
		}
	}
	else{
		CmdUpdatePixelInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		PixelInspectionBase	*BBase=GetPixelInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");

	//if(TempLib==NULL){
	//	return;
	//}
	//GetLibraryFromWindow(*TempLib);
	//if(TempLib->GetLibName()==/**/""){
	//	QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, "Warning", "No Library Name", QMessageBox::Ok | QMessageBox::Cancel);
	//	if(ret!=QMessageBox::Ok){
	//		return;
	//	}
	//}
	//if(TempLib->GetLibID()<0){
	//	TempLib->SetLibFolderID(LibFolderID);

	//	CmdInsertPixelInspectionLibraryPacket	Packet;
	//	Packet.Point=TempLib;
	//	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	//	if(BBase!=NULL){
	//		BBase->TransmitDirectly(&Packet);
	//		ShowLibrary(*TempLib);
	//		ui.pbDelete	->setEnabled(true);
	//		ui.pbUpdate	->setEnabled(true);
	//	}
	//}
	//else{
	//	CmdInsertPixelInspectionLibraryPacket	Packet;
	//	Packet.Point=TempLib;
	//	PixelInspectionBase	*BBase=GetPixelInspectionBase();
	//	if(BBase!=NULL){
	//		BBase->TransmitDirectly(&Packet);
	//	}
	//}
	//SlotSelectLibFolder(LibFolderID ,/**/"");
}

void PropertyPixelInspectionForm::tableWidgetLibListClicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadPixelInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		PixelInspectionBase	*BBase=GetPixelInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.pbDelete	->setEnabled(true);
			ui.pbUpdate	->setEnabled(true);
		}
	}
}
