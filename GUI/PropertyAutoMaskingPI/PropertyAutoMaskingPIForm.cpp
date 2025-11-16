/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoMaskingPI\PropertyAutoMaskingPIForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyAutoMaskingPIResource.h"
#include "PropertyAutoMaskingPIForm.h"
#include "XDisplayImage.h"
#include <QMessageBox>
#include "XGUI.h"
#include "PropertyAutoMaskingPI.h"
#include "XPropertyAutoMaskingPIPacket.h"
#include "XAutoMaskingPIPacket.h"
//#include "SelectLibraryInMaskForm.h"
#include "XGeneralDialog.h"
#include "ImageControlTools.h"
#include <omp.h>
#include "XDisplayImagePacket.h"
#include "XAutoMaskingPIPacket.h"
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyAutoMaskingPIForm::PropertyAutoMaskingPIForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.tableWidgetMaskingList->setColumnWidth (0,40);
	ui.tableWidgetMaskingList->setColumnWidth (1,40);
	ui.tableWidgetMaskingList->setColumnWidth (2,150);

	LibFolderID =-1;
	AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	pLibFolderForm=new GeneralLibFolderForm(LibType,GetLayersBase(),ui.frameLibFolder);
	connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
	pLibFolderForm->SetCurrentLibFolder(GetLayersBase()->GetLibFolderID());

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAutoMaskingPILibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

PropertyAutoMaskingPIForm::~PropertyAutoMaskingPIForm()
{

}
AutoMaskingPIBase	*PropertyAutoMaskingPIForm::GetAutoMaskingPIBase(void)
{
	return (AutoMaskingPIBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoMaskingPI");
}


void	PropertyAutoMaskingPIForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
	LibFolderID=libFolderID;
	//ui.tableWidgetLibList->clear();
	ui.tableWidgetLibList->setRowCount(0);
	AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
	if(BBase!=NULL){
		CmdGetAutoMaskingPILibraryListPacket	Packet(GetLayersBase());
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
void	PropertyAutoMaskingPIForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AddAutoMaskingPIAreaPacket	*MaskAP=dynamic_cast<AddAutoMaskingPIAreaPacket *>(packet);
	if(MaskAP!=NULL){
		if(ui.toolButtonEffectiveMask->isChecked()==true
		|| ui.toolButtonIneffectiveMask->isChecked()==true){
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(MaskAP->Area,PageList);

			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				DataInPage	*pdata=GetLayersBase()->GetPageData(P->GetValue());
				FlexArea	A=MaskAP->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdAddAutoMaskingPIArea	Cmd(GetLayersBase(),sRoot,sName,pdata->GetPage());
					Cmd.MaskArea=A;
					if(ui.toolButtonEffectiveMask->isChecked()==true)
						Cmd.Effective	=true;
					if(ui.toolButtonIneffectiveMask->isChecked()==true)
						Cmd.Effective	=false;
					//Cmd.LimitedLib	=DForm->Libs.SelectedList;
					Cmd.Send(NULL,pdata->GetPage(),0);
				}
			}
			ShowAreaGrid();
		}
		return;
	}
	CmdAutoMaskingPIDrawOnOffPacket	*MDrawOnOff=dynamic_cast<CmdAutoMaskingPIDrawOnOffPacket *>(packet);
	if(MDrawOnOff!=NULL){
		if(ui.toolButtonAutoMask->isChecked()==true)
			MDrawOnOff->AutoGenMode=true;
		if(ui.toolButtonEffectiveMask->isChecked()==true)
			MDrawOnOff->Effective=true;
		if(ui.toolButtonIneffectiveMask->isChecked()==true)
			MDrawOnOff->Ineffective=true;
		if(ui.toolButtonCompositeMask->isChecked()==true)
			MDrawOnOff->CompositeMask=true;
		return;
	}
	CmdSetAutoMaskingPIShowingState	*CmdSetAutoMaskingPIShowingStateVar=dynamic_cast<CmdSetAutoMaskingPIShowingState *>(packet);
	if(CmdSetAutoMaskingPIShowingStateVar!=NULL){
		switch(CmdSetAutoMaskingPIShowingStateVar->ModeShowingButton){
			case CmdSetAutoMaskingPIShowingState::_AutoMask:
				ui.toolButtonAutoMask->setChecked(true);
				break;
			case CmdSetAutoMaskingPIShowingState::_EffectiveMask:
				ui.toolButtonEffectiveMask->setChecked(true);
				break;
			case CmdSetAutoMaskingPIShowingState::_IneffectiveMask:
				ui.toolButtonIneffectiveMask->setChecked(true);
				break;
		}
		BroadcastBuildForShow();
		return;
	}
}
void	PropertyAutoMaskingPIForm::BuildForShow(void)
{
	ShowAreaGrid();
}
void	PropertyAutoMaskingPIForm::ShowInEdit(void)
{
	ShowAreaGrid();
}

void	PropertyAutoMaskingPIForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendAutoMaskPIList	**BmpReceiver=new GUICmdSendAutoMaskPIList*[GetParamGlobal()->PageNumb];
	GUICmdReqAutoMaskPIList		**BmpRequester=new GUICmdReqAutoMaskPIList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendAutoMaskPIList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqAutoMaskPIList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		if(ui.toolButtonEffectiveMask->isChecked()==true)
			BmpRequester[page]->EffectiveMode=true;
		if(ui.toolButtonIneffectiveMask->isChecked()==true)
			BmpRequester[page]->IneffectiveMode=true;
	}

	MaskInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			MaskInfo+=BmpReceiver[page]->MaskInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=MaskInfo.GetNumber();
	ui.tableWidgetMaskingList->setRowCount(Numb);
	AutoMaskingPIListForPacket **LTable=new AutoMaskingPIListForPacket*[Numb];
	int	n=0;
	for(AutoMaskingPIListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}
	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int i=0;i<N;i++){
			AutoMaskingPIListForPacket *L=LTable[i];
		//for(MaskingListForPacket *L=MaskInfo.GetFirst();L!=NULL;L=L->GetNext()){
			QTableWidgetItem *w;
			w=ui.tableWidgetMaskingList->item (i, 0);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,0,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(QString::number(L->Page));
		
			w=ui.tableWidgetMaskingList->item (i, 1);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,1,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			if(L->Effective==true)
				w->setText(/**/"ON");
			else
				w->setText(/**/"OFF");
	
			w=ui.tableWidgetMaskingList->item (i, 2);
			if(w==NULL){
				ui.tableWidgetMaskingList->setItem(i,2,(w=new QTableWidgetItem()));
				w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			w->setText(	 QString(/**/"(")
						+QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
						+QString(/**/")-(")
						+QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
						+QString(/**/")"));
		}
	}
	delete	[]LTable;

	ReEntrant=false;
}

void PropertyAutoMaskingPIForm::on_tableWidgetMaskingList_clicked(const QModelIndex &MIndex)
{
	AutoMaskingPIListForPacket *L=MaskInfo.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AutoMaskingPIImagePanel",/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyAutoMaskingPIForm::on_tableWidgetMaskingList_doubleClicked(QModelIndex)
{
	/*
	QModelIndex	RIndex=ui.tableWidgetMaskingList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	AutoMaskingPIListForPacket *L=MaskInfo.GetItem(R);
	if(L==NULL)
		return;
	SelectLibraryInMaskForm	*DForm=new SelectLibraryInMaskForm(GetLayersBase());
	GeneralDialog	D(GetLayersBase(),DForm,this);
	DForm->SetSelected(L->LimitedLib);
	D.exec();
	if(DForm->RetOK==false)
		return;

	GUICmdChangeAutoMaskingPIAttr	Cmd(GetLayersBase(),sRoot,sName,L->Page);
	Cmd.ItemID		=L->ItemID;
	Cmd.GlobalPage	=L->Page;
	Cmd.Effective	=DForm->Effective;
	Cmd.LimitedLib	=DForm->Libs.SelectedList;
	Cmd.Send(NULL,L->Page,0);
	*/
	ShowAreaGrid();
}



void PropertyAutoMaskingPIForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAutoMaskingPILibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
				ui.ButtonLibSave	->setEnabled(true);
				ui.ButtonLibDelete	->setEnabled(true);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_0)/*"Library error"*/, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_1)/*"Not loaded this library record"*/);
			}
		}
	}
}


void	PropertyAutoMaskingPIForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	AutoMaskingPILibrary	*ALib=dynamic_cast<AutoMaskingPILibrary *>(data.GetLibrary());
	ui.EditColDiffRate		->setValue(ALib->ColDiffRate);
	ui.EditNoizeSize		->setValue(ALib->NoiseSize);
	ui.EditEnLargeDot		->setValue(ALib->EnLargeDot);
	ui.EditEnSmallDot		->setValue(ALib->EnSmallDot);
	ui.EditMinSlitDot		->setValue(ALib->MinSlitDot);
	ui.EditMinSlitSize		->setValue(ALib->MinSlitSize);
	ui.EditMinSlitWidth		->setValue(ALib->MinSlitWidth);
	ui.EditMaxLakeSize		->setValue(ALib->MaxLakeSize);
	ui.EditMinClusterSize	->setValue(ALib->MinClusterSize);
	ui.EditMinClusterArea	->setValue(ALib->MinClusterArea);

	ui.checkBDefaultMask	->setChecked(ALib->DefaultMask);
	ui.checkBPickupDarker	->setChecked(ALib->PickupDarker);

	ui.checkEnLargeDot		->setChecked(ALib->chkEnLargeDot);
}

void	PropertyAutoMaskingPIForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	AutoMaskingPILibrary	*ALib=dynamic_cast<AutoMaskingPILibrary *>(data.GetLibrary());
	ALib->ColDiffRate	=ui.EditColDiffRate		->value();
	ALib->NoiseSize		=ui.EditNoizeSize		->value();
	ALib->EnLargeDot	=ui.EditEnLargeDot		->value();
	ALib->EnSmallDot	=ui.EditEnSmallDot		->value();
	ALib->MinSlitDot	=ui.EditMinSlitDot		->value();
	ALib->MinSlitSize	=ui.EditMinSlitSize		->value();
	ALib->MinSlitWidth	=ui.EditMinSlitWidth	->value();
	ALib->MaxLakeSize	=ui.EditMaxLakeSize		->value();
	ALib->MinClusterSize=ui.EditMinClusterSize	->value();
	ALib->MinClusterArea=ui.EditMinClusterArea	->value();
	ALib->DefaultMask	=ui.checkBDefaultMask	->isChecked();
	ALib->PickupDarker	=ui.checkBPickupDarker	->isChecked();
	ALib->chkEnLargeDot	=ui.checkEnLargeDot		->isChecked();
}

void PropertyAutoMaskingPIForm::on_ButtonLibNew_clicked()
{
	if(TempLib==NULL)
		return;
	TempLib->Reset();
	CmdClearAutoMaskingPILibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ShowLibrary(*TempLib);
	ui.ButtonLibSave	->setEnabled(false);
	ui.ButtonLibDelete	->setEnabled(false);
}

void PropertyAutoMaskingPIForm::on_ButtonLibDelete_clicked()
{
	if(TempLib==NULL)
		return;
	if(TempLib->GetLibID()<0)
		return;
	QString  msg=LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_2)/*"Delete OK?"*/;
	int	ret=QMessageBox::question(NULL, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_3)/*"Choose"*/
					, msg
					, QMessageBox::Yes , QMessageBox::No, QMessageBox::NoButton);
	if(ret==QMessageBox::Yes){
		CmdDeleteAutoMaskingPILibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			on_ButtonLibNew_clicked();
			SlotSelectLibFolder(LibFolderID ,/**/"");
		}
	}
}

void PropertyAutoMaskingPIForm::on_ButtonLibSaveNew_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);

	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_4)/*"Warning"*/
																	, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_5)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	TempLib->SetLibFolderID(LibFolderID);
	CmdInsertAutoMaskingPILibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);		
		ShowLibrary(*TempLib);
		ui.ButtonLibSave	->setEnabled(true);
		ui.ButtonLibDelete	->setEnabled(true);
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void PropertyAutoMaskingPIForm::on_ButtonLibSave_clicked()
{
	if(TempLib==NULL)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_6)/*"Warning"*/
																	, LangSolver.GetString(PropertyAutoMaskingPIForm_LS,LID_7)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	if(TempLib->GetLibID()<0){
		TempLib->SetLibFolderID(LibFolderID);

		CmdInsertAutoMaskingPILibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			ShowLibrary(*TempLib);
			ui.ButtonLibSave	->setEnabled(true);
			ui.ButtonLibDelete	->setEnabled(true);
		}
	}
	else{
		CmdUpdateAutoMaskingPILibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
		}
	}
	SlotSelectLibFolder(LibFolderID ,/**/"");
}

void PropertyAutoMaskingPIForm::on_pushButtonGenerateLib_clicked()
{
	int	R=ui.tableWidgetLibList->currentRow();
	if(0<=R){
		AlgorithmLibraryList	*a=LibList.GetItem(R);
		if(a!=NULL){
			CmdGenerateAutoMaskingPILibraryPacket	Packet(GetLayersBase());
			Packet.LibID=a->GetLibID();
			AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
			if(BBase!=NULL){
				BBase->TransmitDirectly(&Packet);
			}
			ui.toolButtonAutoMask->setChecked(true);
		}
	}
}

void PropertyAutoMaskingPIForm::on_pushButtonGenerateDefault_clicked()
{
	CmdGenerateAutoMaskingPILibraryPacket	Packet(GetLayersBase());
	Packet.LibID=-1;
	AutoMaskingPIBase	*BBase=GetAutoMaskingPIBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	ui.toolButtonAutoMask->setChecked(true);
}

void PropertyAutoMaskingPIForm::on_toolButtonAutoMask_clicked()
{
	BroadcastBuildForShow();
}

void PropertyAutoMaskingPIForm::on_toolButtonEffectiveMask_clicked()
{
	BroadcastBuildForShow();
}

void PropertyAutoMaskingPIForm::on_toolButtonIneffectiveMask_clicked()
{
	BroadcastBuildForShow();
}

void PropertyAutoMaskingPIForm::on_toolButtonCompositeMask_clicked()
{
	BroadcastBuildForShow();
}