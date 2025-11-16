/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoMaskingPI\PropertyAutoMaskingPIForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "VCutImagePropertyForm.h"
#include "XDisplayImage.h"
#include "XGUI.h"
#include "VCutProperty.h"
//#include "XPropertyAutoMaskingPIPacket.h"
//#include "XAutoMaskingPIPacket.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XDisplayImagePacket.h"
#include "AddVCutAreaDialog.h"
#include "VCutPropertyResource.h"
#include <QMessageBox>
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

VCutImagePropertyForm::VCutImagePropertyForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.tableWidgetVCutList->setColumnWidth (0,40);
	ui.tableWidgetVCutList->setColumnWidth (1,40);
	ui.tableWidgetVCutList->setColumnWidth (2,130);
	ui.tableWidgetVCutList->setColumnWidth (3,40);
	ui.tableWidgetVCutList->setColumnWidth (4,40);
	ui.tableWidgetVCutList->setColumnWidth (5,40);

	LibFolderID =-1;
	VCutInspectionBase	*BBase=GetVCutInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

	ui.tableWidgetLibList	->setColumnWidth(0,48);
	ui.tableWidgetLibList	->setColumnWidth(1,120);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempVCutInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);

	//?a?E?\?|???I???e?I??
	LangSolver.SetUI(this);
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

VCutImagePropertyForm::~VCutImagePropertyForm()
{

}

VCutInspectionBase	*VCutImagePropertyForm::GetVCutInspectionBase(void)
{
	return (VCutInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"PCB",/**/"VCutInspection");
}

void	VCutImagePropertyForm::SetLibFolder(int LibFolderID ,const QString &LinFolderName)
{
	SlotSelectLibFolder(LibFolderID ,LinFolderName);
}
void	VCutImagePropertyForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibList->setRowCount(0);
	VCutInspectionBase	*BBase=GetVCutInspectionBase();
	if(BBase!=NULL){
		CmdGetVCutInspectionLibraryListPacket	Packet(GetLayersBase());
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
void	VCutImagePropertyForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddVCutInspectionAreaPacket	*MaskAP=dynamic_cast<AddVCutInspectionAreaPacket *>(packet);
	if(MaskAP!=NULL){
		AddVCutAreaDialog	M(GetLayersBase(),this);
		if(M.exec()==(int)true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromVector(MaskAP->Vector,PageList);
			GetLayersBase()->TF_SetCurrentScanPhaseNumber(MaskAP->CurrentPhase); // phase function
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata = GetLayersBase()->GetPageDataPhase(MaskAP->CurrentPhase)->GetPageData(P->GetValue());
				VectorLineBase	*A=MaskAP->Vector->CreateDup();
				pdata->ClipMoveVectorFromGlobal(A);
				if(A->GetLength()>0){
					GUICmdAddVCutInspectionArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),pdata->GetPage());
					Cmd.Vector=A;
					Cmd.ThresholdShift	=M.ThresholdShift;
					Cmd.ThresholdLevel	=M.ThresholdLevel;
					Cmd.ThresholdLength	=M.ThresholdLength;
					Cmd.LibID			=M.SelectedLibID;
					Cmd.Send(NULL,pdata->GetPage(),0);
				}
			}
			ShowAreaGrid();
			GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
		}
		return;
	}
}
void	VCutImagePropertyForm::BuildForShow(void)
{
	ShowAreaGrid();
}
void	VCutImagePropertyForm::ShowInEdit(void)
{
	ShowAreaGrid();
}

void	VCutImagePropertyForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	VCutInfo.RemoveAll();
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendVCutInspectionList	**BmpReceiver=new GUICmdSendVCutInspectionList*[GetParamGlobal()->PageNumb];
	GUICmdReqVCutInspectionList		**BmpRequester=new GUICmdReqVCutInspectionList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]	=new GUICmdSendVCutInspectionList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]	=new GUICmdReqVCutInspectionList	(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}
	int row=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
			&& BmpReceiver[page]->IsReceived()==true){
				VCutInfo+=BmpReceiver[page]->VCutInfo;
			}
		}
		ui.tableWidgetVCutList->setRowCount(VCutInfo.GetNumber());
		for(;row<VCutInfo.GetCount();row++){
			SetDataToTable(ui.tableWidgetVCutList,0,row,QString::number(phase));
		}
	}
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	row=0;
	int	Numb=VCutInfo.GetNumber();
	ui.tableWidgetVCutList->setRowCount(Numb);
	for(VCutInspectionList *L=VCutInfo.GetFirst();L!=NULL;L=L->GetNext() ,row++){
		SetDataToTable(ui.tableWidgetVCutList ,1,row,QString::number(L->Page));
		QString	s=QString(/**/"(")
				+ QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
				+ QString(/**/")-(")
				+ QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
				+ QString(/**/")");
		SetDataToTable(ui.tableWidgetVCutList ,2,row,s);
		SetDataToTable(ui.tableWidgetVCutList ,3,row,QString::number(L->ThresholdLevel));
		SetDataToTable(ui.tableWidgetVCutList ,4,row,QString::number(L->ThresholdShift));
		SetDataToTable(ui.tableWidgetVCutList ,5,row,QString::number(L->ThresholdLength));
	}

	ReEntrant=false;
}


void VCutImagePropertyForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadVCutInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VCutInspectionBase	*BBase=GetVCutInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(VCutImagePropertyForm_LS,LID_2)/*"Library error"*/, LangSolver.GetString(VCutImagePropertyForm_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void VCutImagePropertyForm::on_tableWidgetVCutList_clicked(const QModelIndex &MIndex)
{
///////////// test
	//VCutInspectionList *L=VCutInfo.GetItem(MIndex.row());
	//if(L==NULL)
	//	return;

	//DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	//if(P!=NULL){
	//	CmdDrawImageRectPacket	Cmd( GetLayersBase()
	//								,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
	//								,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
	//	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"VCutImagePanel",/**/"");
	//	if(GProp!=NULL)
	//		GProp->TransmitDirectly(&Cmd);
	//	//CmdDrawImageActivate	ACmd(L->Page,0,L->ItemID);
	//	CmdDrawImageActivate ACmd(GetLayersBase(),L->Page,0,L->GetNumber());
	//	if(GProp!=NULL)
	//		GProp->TransmitDirectly(&ACmd);
	//}
////////////
}

void	VCutImagePropertyForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	VCutInspectionLibrary	*ALib=dynamic_cast<VCutInspectionLibrary *>(data.GetLibrary());
	ui.EditThresholdShift		->setValue(ALib->ThresholdShift);
	ui.EditThresholdLevel		->setValue(ALib->ThresholdLevel);
	ui.EditThresholdLength		->setValue(ALib->ThresholdLength);
}

void	VCutImagePropertyForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	VCutInspectionLibrary	*ALib=dynamic_cast<VCutInspectionLibrary *>(data.GetLibrary());
	ALib->ThresholdShift	=ui.EditThresholdShift	->value();
	ALib->ThresholdLevel	=ui.EditThresholdLevel	->value();
	ALib->ThresholdLength=ui.EditThresholdLength	->value();
}

void VCutImagePropertyForm::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearVCutInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	VCutInspectionBase	*BBase=GetVCutInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void VCutImagePropertyForm::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(VCutImagePropertyForm_LS,LID_4)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(VCutImagePropertyForm_LS,LID_5)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteVCutInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VCutInspectionBase	*BBase=GetVCutInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void VCutImagePropertyForm::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(VCutImagePropertyForm_LS,LID_6)/*"Warning"*/
																	, LangSolver.GetString(VCutImagePropertyForm_LS,LID_7)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertVCutInspectionLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	VCutInspectionBase	*BBase=GetVCutInspectionBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void VCutImagePropertyForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(VCutImagePropertyForm_LS,LID_8)/*"Warning"*/
																	, LangSolver.GetString(VCutImagePropertyForm_LS,LID_9)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertVCutInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VCutInspectionBase	*BBase=GetVCutInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateVCutInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		VCutInspectionBase	*BBase=GetVCutInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}