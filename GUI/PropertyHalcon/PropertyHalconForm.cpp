#include "PropertyHalconResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHalcon\PropertyHalconForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyHalconForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyHalconInspectionPacket.h"
#include "XHalconInspection.h"
#include "XGeneralFunc.h"
#include "RegistHalconFunc.h"
#include "XGeneralDialog.h"

PropertyHalconForm::PropertyHalconForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base ,parent)
{
	ui.setupUi(this);

	LibFolderID =-1;
	HalconInspectionBase	*BBase=GetHalconInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);

	ui.tableViewSampleList->setColumnWidth (0, 130);
	ui.tableViewSampleList->setColumnWidth (1, 70);
	ui.tableViewSampleList->setColumnWidth (2, 70);
	ui.tableViewSampleList->setColumnWidth (3, 70);
	ui.tableViewSampleList->setColumnWidth (4, 70);
	ui.tableViewSampleList->setColumnWidth (5, 70);
	ui.tableViewSampleList->setColumnWidth (6, 70);
	ui.tableViewSampleList->setColumnWidth (7, 70);
	ui.tableViewSampleList->setColumnWidth (8, 70);
	ui.tableViewSampleList->setColumnWidth (9, 70);
	ui.tableViewSampleList->setColumnWidth (10,70);

	TempLib		=NULL;
	TempSample	=NULL;
	if(BBase!=NULL){
		CmdCreateTempHalconInspectionLibraryPacket	Packet;
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.pushButtonUpdateLib	->setEnabled(false);
	ui.pushButtonDeleteLib	->setEnabled(false);

	connect(ui.tableViewSampleList,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(tableViewSampleListDoubleClicked(QModelIndex)));
/*
	int i=0;
	HalconFuncString[i++]="";
	HalconFuncString[i++]="area_center";
	HalconFuncString[i++]="closing_circle";
	HalconFuncString[i++]="concat_obj";
	HalconFuncString[i++]="connection";
	HalconFuncString[i++]="count_obj";
	HalconFuncString[i++]="difference";
	HalconFuncString[i++]="emphasize";
	HalconFuncString[i++]="gen_image1";
	HalconFuncString[i++]="gen_image3";
	HalconFuncString[i++]="get_region_points";
	HalconFuncString[i++]="invert_image";
	HalconFuncString[i++]="mean_image";
	HalconFuncString[i++]="min_max_gray";
	HalconFuncString[i++]="select_obj";
	HalconFuncString[i++]="select_shape";
	HalconFuncString[i++]="threshold";
	HalconFuncString[i++]="tuple_max";
	HalconFuncString[i++]="tuple_sum";
	FuncListCount=i;
*/
}

PropertyHalconForm::~PropertyHalconForm()
{
}

void	PropertyHalconForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	ui.tableWidgetLibList->clear();
	HalconInspectionBase	*BBase=GetHalconInspectionBase();
	if(BBase!=NULL){
		CmdGetHalconInspectionLibraryListPacket	Packet;
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
			W->setText(QString::number(a->LibID));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->LibName);
		}
	}
}

void	PropertyHalconForm::BuildForShow(void)
{
}

HalconInspectionBase	*PropertyHalconForm::GetHalconInspectionBase(void)
{
	HalconInspectionBase	*ABase=dynamic_cast<HalconInspectionBase *>(GetLayersBase()->GetAlgorithmBase(LangSolver.GetString(PropertyHalconForm_LS,LID_0)/*"Basic"*/,LangSolver.GetString(PropertyHalconForm_LS,LID_1)/*"HalconInspection"*/));
	return ABase;
}


void	PropertyHalconForm::TransmitDirectly(GUIDirectMessage *packet)
{
	/*
	CmdHalconInsMouseMove	*CmdHalconInsMouseMoveVar=dynamic_cast<CmdHalconInsMouseMove *>(packet);
	if(CmdHalconInsMouseMoveVar!=NULL){
		int	Page=GetLayersBase()->GetLocalPageFromAreaFromDrawingTop(CmdHalconInsMouseMoveVar->GlobalX ,CmdHalconInsMouseMoveVar->GlobalY);
		if(Page>=0){
			HalconInspectionBase	*ABase=GetHalconInspectionBase();
			if(ABase!=NULL){
				HalconInspectionInPage	*P=dynamic_cast<HalconInspectionInPage *>(ABase->GetPageData(Page));
				if(P!=NULL){
					CmdGetHalconInsDataFromGlobalPoint	RCmd;
					RCmd.GlobalX=CmdHalconInsMouseMoveVar->GlobalX;
					RCmd.GlobalY=CmdHalconInsMouseMoveVar->GlobalY;
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
}

void	PropertyHalconForm::ShowInEdit(void)
{
}

void PropertyHalconForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->LibID=a->LibID;
		CmdLoadHalconInspectionLibraryPacket	Packet;
		Packet.Point=TempLib;
		HalconInspectionBase	*BBase=GetHalconInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ui.lineEditLibName	->setText(TempLib->LibName );
			ui.lineEditLibID	->setText(QString::number(TempLib->GetLibID()));
			ShowSampleList();
			ui.pushButtonUpdateLib	->setEnabled(true);
			ui.pushButtonDeleteLib	->setEnabled(true);
		}
	}

	//常時使用のチェックを反映
	if(GetHalconInspectionBase()->DefaultLibraryID==TempLib->GetLibID())
		ui.checkBoxDefault->setChecked(true);
	else
		ui.checkBoxDefault->setChecked(false);
}

void PropertyHalconForm::ShowSampleList(void)
{
	if(TempLib==NULL)
		return;
	int	row=0;
	ui.tableViewSampleList->setRowCount(TempLib->SampleLists.GetNumber());
	for(HalconSampleList *c=TempLib->SampleLists.GetFirst();c!=NULL;c=c->GetNext() ,row++){
		QTableWidgetItem *W;
		W=ui.tableViewSampleList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableViewSampleList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(c->FuncName);

		int	col=1;
		for(HalconArg *A=c->ArgList.GetFirst();A!=NULL;A=A->GetNext() ,col++){
			W=ui.tableViewSampleList->item ( row, col);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableViewSampleList->setItem ( row, col,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(QString(A->Arg));
		}
	}
}

void PropertyHalconForm::tableViewSampleListDoubleClicked(const QModelIndex &CIndex)
{
	if(TempLib==NULL)
		return;
	int	row=ui.tableViewSampleList->currentRow();
	TempSample=TempLib	->SampleLists.GetItem(row);

	RegistHalconFunc RegistHalconFuncDialog(this);
	if(!RegistHalconFuncDialog.exec()){
		return;
	}
	ShowSampleList();
}

void PropertyHalconForm::on_pushButtonRegistLib_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	TempLib->LibName		=ui.lineEditLibName	->text();

	ui.pushButtonUpdateLib	->setEnabled(false);
	ui.pushButtonDeleteLib	->setEnabled(false);

	TempLib->LibFolderID=LibFolderID;
	CmdInsertHalconInspectionLibraryPacket	Packet;
	Packet.Point=TempLib;
	HalconInspectionBase	*BBase=GetHalconInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
		if(TempLib->GetLibID()<0)
			ui.lineEditLibID->setText(LangSolver.GetString(PropertyHalconForm_LS,LID_2)/*""*/);
		else
			ui.lineEditLibID->setText(QString::number(TempLib->GetLibID()));

		ui.pushButtonUpdateLib	->setEnabled(true);
		ui.pushButtonDeleteLib	->setEnabled(true);
		SlotSelectLibFolder(LibFolderID ,LangSolver.GetString(PropertyHalconForm_LS,LID_3)/*""*/);
	}
}

void PropertyHalconForm::on_pushButtonUpdateLib_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib	->LibName		=ui.lineEditLibName	->text();

	if(TempLib->LibName==LangSolver.GetString(PropertyHalconForm_LS,LID_4)/*""*/){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyHalconForm_LS,LID_5)/*"Warning"*/, LangSolver.GetString(PropertyHalconForm_LS,LID_6)/*"No Library Name"*/, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->LibFolderID=LibFolderID;
		CmdInsertHalconInspectionLibraryPacket	Packet;
		Packet.Point=TempLib;
		HalconInspectionBase	*BBase=GetHalconInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(TempLib->GetLibID()<0)
				ui.lineEditLibID->setText(LangSolver.GetString(PropertyHalconForm_LS,LID_7)/*""*/);
			else
				ui.lineEditLibID->setText(QString::number(TempLib->GetLibID()));

			ui.pushButtonUpdateLib	->setEnabled(true);
			ui.pushButtonDeleteLib	->setEnabled(true);
		}
	}
	else{
		CmdUpdateHalconInspectionLibraryPacket	Packet;
		Packet.Point=TempLib;
		HalconInspectionBase	*BBase=GetHalconInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,LangSolver.GetString(PropertyHalconForm_LS,LID_8)/*""*/);

	//常時使用のチェックを反映
	if(ui.checkBoxDefault->isChecked())
		GetHalconInspectionBase()->DefaultLibraryID=TempLib->GetLibID();
}

void PropertyHalconForm::on_pushButtonDeleteLib_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(PropertyHalconForm_LS,LID_9)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(PropertyHalconForm_LS,LID_10)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteHalconInspectionLibraryPacket	Packet;
		Packet.Point=TempLib;
		HalconInspectionBase	*BBase=GetHalconInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_pushButtonRegistLib_clicked();
			SlotSelectLibFolder(LibFolderID ,LangSolver.GetString(PropertyHalconForm_LS,LID_11)/*""*/);
		}
	}
}

void PropertyHalconForm::on_pushButtonRegist_2_clicked()
{
	if(TempLib==NULL)
		return;
	TempSample=new HalconSampleList();
	TempLib->SampleLists.AppendList(TempSample);
	ShowSampleList();
}

void PropertyHalconForm::on_pushButtonUpdate_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempSample==NULL)
		return;
//	TempSample->Name	=ui.lineEditName->text();
//	TempSample->PickupColor	=ColorGenerate.Cube;
	ShowSampleList();
}

void PropertyHalconForm::on_pushButtonDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempSample==NULL)
		return;
	TempLib->SampleLists.RemoveList(TempSample);
	delete	TempSample;
	TempSample=NULL;
	ShowSampleList();
}
